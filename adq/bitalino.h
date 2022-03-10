#ifndef _BITALINOHEADER_
#define _BITALINOHEADER_

#include <string>
#include <vector>

class BITalino
{
public:
   typedef std::vector<bool>  Vbool;
   typedef std::vector<int>   Vint;

   struct DevInfo
   {
      std::string macAddr;
      std::string name;
   };
   typedef std::vector<DevInfo> VDevInfo;

   struct Frame
   {
      char  seq;
      bool  digital[4];
      short analog[6];
   };
   typedef std::vector<Frame> VFrame;

   /// Current device state returned by BITalino::state()
   struct State
   {
      int   analog[6],     // Array of analog inputs values (0...1023)
            battery,       // Battery voltage value (0...1023)
            batThreshold;  // Low-battery LED threshold (last value set with BITalino::battery())
      // Array of digital ports states (false for low level or true for high level).
      // The array contents are: I1 I2 O1 O2.
      bool  digital[4];
   };

   class Exception
   {
   public:
      enum Code
      {
         INVALID_ADDRESS = 1,       // The specified address is invalid
         BT_ADAPTER_NOT_FOUND,      // No Bluetooth adapter was found
         DEVICE_NOT_FOUND,          // The device could not be found
         CONTACTING_DEVICE,         // The computer lost communication with the device
         PORT_COULD_NOT_BE_OPENED,  // The communication port does not exist or it is already being used
         PORT_INITIALIZATION,       // The communication port could not be initialized
         DEVICE_NOT_IDLE,           // The device is not idle
         DEVICE_NOT_IN_ACQUISITION, // The device is not in acquisition mode
         INVALID_PARAMETER,         // Invalid parameter
         NOT_SUPPORTED,             // Operation not supported by the device
      } code;  // %Exception code.

      Exception(Code c) : code(c) {}      // Exception constructor.
      const char* getDescription(void);   // Returns an exception description string
   };

   static VDevInfo find();

   BITalino(const char *address);
   ~BITalino();

   std::string version(void);

   void start(int samplingRate = 1000, const Vint &channels = Vint(), bool simulated = false);
   void stop(void);
   int read(VFrame &frames);
   void battery(int value = 0);
   void trigger(const Vbool &digitalOutput = Vbool());
   void pwm(int pwmOutput = 100);
   State state(void);

private:
   void send(char cmd);
   int  recv(void *data, int nbyttoread);
   void close(void);

   char nChannels = 0;
   bool isBitalino2 = false;
   int fd = 0;
   bool isTTY = false;
};

#endif // _BITALINOHEADER_
