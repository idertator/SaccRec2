#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdlib.h>

#include "bitalino.h"
#include "utils.h"

#define MAX_DEVS 255


BITalino::VDevInfo BITalino::find(void) {
    VDevInfo devs;
    DevInfo  devInfo;

    int dev_id = hci_get_route(NULL);
    int sock = hci_open_dev(dev_id);
    if (dev_id < 0 || sock < 0)
        throw Exception(Exception::PORT_INITIALIZATION);

    inquiry_info ii[MAX_DEVS];
    inquiry_info *pii = ii;

    int num_rsp = hci_inquiry(dev_id, 8, MAX_DEVS, NULL, &pii, IREQ_CACHE_FLUSH);
    if(num_rsp < 0) {
        ::close(sock);
        throw Exception(Exception::PORT_INITIALIZATION);
    }

    for (int i = 0; i < num_rsp; i++) {
        char addr[19], name[248];

        ba2str(&ii[i].bdaddr, addr);
        if (hci_read_remote_name(sock, &ii[i].bdaddr, sizeof name, name, 0) >= 0) {
            devInfo.macAddr = addr;
            devInfo.name = name;
            devs.push_back(devInfo);
        }
    }

    ::close(sock);
    if (pii != ii)
        free(pii);

    return devs;
}


BITalino::BITalino(const char *address) {
    if (memcmp(address, "/dev/", 5) == 0) {
        fd = open(address, O_RDWR | O_NOCTTY | O_NDELAY);
        if (fd < 0)
            throw Exception(Exception::PORT_COULD_NOT_BE_OPENED);

        if (fcntl(fd, F_SETFL, 0) == -1) {
            close();
            throw Exception(Exception::PORT_INITIALIZATION);
        }

        termios term;
        if (tcgetattr(fd, &term) != 0) {
            close();
            throw Exception(Exception::PORT_INITIALIZATION);
        }

        cfmakeraw(&term);
        term.c_oflag &= ~(OPOST);

        term.c_cc[VMIN] = 1;
        term.c_cc[VTIME] = 1;

        term.c_iflag &= ~(INPCK | PARMRK | ISTRIP | IGNCR | ICRNL | INLCR | IXON | IXOFF | IMAXBEL); // no flow control
        term.c_iflag |= (IGNPAR | IGNBRK);

        term.c_cflag &= ~(CRTSCTS | PARENB | CSTOPB | CSIZE); // no parity, 1 stop bit
        term.c_cflag |= (CLOCAL | CREAD | CS8);    // raw mode, 8 bits

        term.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOPRT | ECHOK | ECHOKE | ECHONL | ECHOCTL | ISIG | IEXTEN | TOSTOP);  // raw mode

        if (cfsetspeed(&term, B115200) != 0) {
            close();
            throw Exception(Exception::PORT_INITIALIZATION);
        }

        if (tcsetattr(fd, TCSANOW, &term) != 0) {
            close();
            throw Exception(Exception::PORT_INITIALIZATION);
        }

        isTTY = true;
    } else {
        sockaddr_rc so_bt;
        so_bt.rc_family = AF_BLUETOOTH;
        if (str2ba(address, &so_bt.rc_bdaddr) < 0)
            throw Exception(Exception::INVALID_ADDRESS);

        so_bt.rc_channel = 1;

        fd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        if (fd < 0)
            throw Exception(Exception::PORT_INITIALIZATION);

        if (connect(fd, (const sockaddr*)&so_bt, sizeof so_bt) != 0) {
            close();
            throw Exception(Exception::PORT_COULD_NOT_BE_OPENED);
        }

        isTTY = false;
    }

    // check if device is BITalino2
    const std::string ver = version();
    const std::string::size_type pos = ver.find("_v");
    if (pos != std::string::npos)
    {
        const char *xver = ver.c_str() + pos + 2;
        if (atoi(xver) >= 5)
            isBitalino2 = true;
    }
}

BITalino::~BITalino(void) {
    try {
        if (nChannels != 0)
            stop();
    } catch (Exception) {}

    close();
}

std::string BITalino::version(void) {
    if (nChannels != 0)
        throw Exception(Exception::DEVICE_NOT_IDLE);

    const char *header = "BITalino";

    const size_t headerLen = strlen(header);

    send(0x07);

    std::string str;
    while(1) {
        char chr;
        if (recv(&chr, sizeof chr) != sizeof chr)
            throw Exception(Exception::CONTACTING_DEVICE);

        const size_t len = str.size();
        if (len >= headerLen) {
            if (chr == '\n')  return str;
            str.push_back(chr);
        } else if (chr == header[len]) {
            str.push_back(chr);
        } else {
            str.clear();
            if (chr == header[0])
                str.push_back(chr);
        }
    }
}

void BITalino::start(int samplingRate, const Vint &channels, bool simulated) {
    if (nChannels != 0)
        throw Exception(Exception::DEVICE_NOT_IDLE);

    unsigned char cmd;
    switch (samplingRate) {
    case 1:
        cmd = 0x03;
        break;
    case 10:
        cmd = 0x43;
        break;
    case 100:
        cmd = 0x83;
        break;
    case 1000:
        cmd = 0xC3;
        break;
    default:
        throw Exception(Exception::INVALID_PARAMETER);
    }

    char chMask;
    if (channels.empty()) {
        chMask = 0x3F;
        nChannels = 6;
    } else {
        chMask = 0;
        nChannels = 0;
        for(Vint::const_iterator it = channels.begin(); it != channels.end(); it++) {
            int ch = *it;
            if ((ch < 0) || (ch > 5))
                throw Exception(Exception::INVALID_PARAMETER);

            const char mask = 1 << ch;
            if (chMask & mask)
                throw Exception(Exception::INVALID_PARAMETER);

            chMask |= mask;
            nChannels++;
        }
    }

    send(cmd);
    send((chMask << 2) | (simulated ? 0x02 : 0x01));
}


void BITalino::stop(void) {
    if (nChannels == 0)
        throw Exception(Exception::DEVICE_NOT_IN_ACQUISITION);

    send(0x00);

    nChannels = 0;

    version();
}

int BITalino::read(VFrame &frames) {
    if (nChannels == 0)
        throw Exception(Exception::DEVICE_NOT_IN_ACQUISITION);

    unsigned char buffer[8];

    if (frames.empty())
        frames.resize(100);

    char nBytes = nChannels + 2;
    if (nChannels >= 3 && nChannels <= 5)
        nBytes++;

    for(VFrame::iterator it = frames.begin(); it != frames.end(); it++) {
        if (recv(buffer, nBytes) != nBytes)
            return int(it - frames.begin());

        while (!checkCRC4(buffer, nBytes)) {
            memmove(buffer, buffer+1, nBytes-1);
            if (recv(buffer+nBytes-1, 1) != 1)
                return int(it - frames.begin());
        }

        Frame &f = *it;
        f.seq = buffer[nBytes-1] >> 4;
        for(int i = 0; i < 4; i++)
            f.digital[i] = ((buffer[nBytes-2] & (0x80 >> i)) != 0);

        f.analog[0] = (short(buffer[nBytes-2] & 0x0F) << 6) | (buffer[nBytes-3] >> 2);
        if (nChannels > 1)
            f.analog[1] = (short(buffer[nBytes-3] & 0x03) << 8) | buffer[nBytes-4];
        if (nChannels > 2)
            f.analog[2] = (short(buffer[nBytes-5]) << 2) | (buffer[nBytes-6] >> 6);
        if (nChannels > 3)
            f.analog[3] = (short(buffer[nBytes-6] & 0x3F) << 4) | (buffer[nBytes-7] >> 4);
        if (nChannels > 4)
            f.analog[4] = ((buffer[nBytes-7] & 0x0F) << 2) | (buffer[nBytes-8] >> 6);
        if (nChannels > 5)
            f.analog[5] = buffer[nBytes-8] & 0x3F;
    }

    return (int) frames.size();
}

void BITalino::battery(int value) {
    if (nChannels != 0)
        throw Exception(Exception::DEVICE_NOT_IDLE);

    if ((value < 0) || (value > 63))
        throw Exception(Exception::INVALID_PARAMETER);

    send(value << 2);
}


void BITalino::trigger(const Vbool &digitalOutput) {
    unsigned char cmd;
    const size_t len = digitalOutput.size();

    if (isBitalino2) {
        if (len != 0 && len != 2)
            throw Exception(Exception::INVALID_PARAMETER);

        cmd = 0xB3;
    } else {
        if (len != 0 && len != 4)
            throw Exception(Exception::INVALID_PARAMETER);

        if (nChannels == 0)
            throw Exception(Exception::DEVICE_NOT_IN_ACQUISITION);

        cmd = 0x03;
    }

    for(size_t i = 0; i < len; i++)
        if (digitalOutput[i])
            cmd |= (0x04 << i);

    send(cmd);
}

void BITalino::pwm(int pwmOutput) {
    if (!isBitalino2)
        throw Exception(Exception::NOT_SUPPORTED);

    if ((pwmOutput < 0) || (pwmOutput > 255))
        throw Exception(Exception::INVALID_PARAMETER);

    send((char) 0xA3);
    send(pwmOutput);
}

BITalino::State BITalino::state(void) {
#pragma pack(1)

    struct StateX
    {
        unsigned short analog[6], battery;
        unsigned char  batThreshold, portsCRC;
    } statex;

#pragma pack()

    if (!isBitalino2)
        throw Exception(Exception::NOT_SUPPORTED);

    if (nChannels != 0)
        throw Exception(Exception::DEVICE_NOT_IDLE);

    send(0x0B);

    if (recv(&statex, sizeof statex) != sizeof statex)
        throw Exception(Exception::CONTACTING_DEVICE);

    if (!checkCRC4((unsigned char *) &statex, sizeof statex))
        throw Exception(Exception::CONTACTING_DEVICE);

    State state;

    for(int i = 0; i < 6; i++)
        state.analog[i] = statex.analog[i];

    state.battery = statex.battery;
    state.batThreshold = statex.batThreshold;

    for(int i = 0; i < 4; i++)
        state.digital[i] = ((statex.portsCRC & (0x80 >> i)) != 0);

    return state;
}

const char* BITalino::Exception::getDescription(void) {
    switch (code) {
    case INVALID_ADDRESS:
        return "The specified address is invalid.";

    case BT_ADAPTER_NOT_FOUND:
        return "No Bluetooth adapter was found.";

    case DEVICE_NOT_FOUND:
        return "The device could not be found.";

    case CONTACTING_DEVICE:
        return "The computer lost communication with the device.";

    case PORT_COULD_NOT_BE_OPENED:
        return "The communication port does not exist or it is already being used.";

    case PORT_INITIALIZATION:
        return "The communication port could not be initialized.";

    case DEVICE_NOT_IDLE:
        return "The device is not idle.";

    case DEVICE_NOT_IN_ACQUISITION:
        return "The device is not in acquisition mode.";

    case INVALID_PARAMETER:
        return "Invalid parameter.";

    case NOT_SUPPORTED:
        return "Operation not supported by the device.";

    default:
        return "Unknown error.";
    }
}

void BITalino::send(char cmd) {
    usleep(150000);

    if (write(fd, &cmd, sizeof cmd) != sizeof cmd)
        throw Exception(Exception::CONTACTING_DEVICE);
}

int BITalino::recv(void *data, int nbyttoread) {
    timeval  readtimeout;
    readtimeout.tv_sec = 5;
    readtimeout.tv_usec = 0;

    fd_set   readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    int n = 0;
    while(n < nbyttoread) {
        int state = select(FD_SETSIZE, &readfds, NULL, NULL, &readtimeout);

        if(state < 0)
            throw Exception(Exception::CONTACTING_DEVICE);

        if (state == 0)
            return n;

        ssize_t ret = ::read(fd, (char *) data + n, nbyttoread - n);

        if(ret <= 0)
            throw Exception(Exception::CONTACTING_DEVICE);

        n += ret;
    }

    return nbyttoread;
}


void BITalino::close(void) {
    ::close(fd);
}
