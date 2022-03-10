#include "utils.h"

const unsigned char CRC4tab[16] = {0, 3, 6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2};

bool checkCRC4(const unsigned char *data, int len)
{
    unsigned char crc = 0;

    for (int i = 0; i < len-1; i++)
    {
        const unsigned char b = data[i];
        crc = CRC4tab[crc] ^ (b >> 4);
        crc = CRC4tab[crc] ^ (b & 0x0F);
    }

    crc = CRC4tab[crc] ^ (data[len-1] >> 4);
    crc = CRC4tab[crc];

    return (crc == (data[len-1] & 0x0F));
}
