// assigned by USB Org
#define VENDOR_APPLE 0x5AC

// assigned by Apple
#define PRODUCT_IPHONE 0x1280
#define DEVICE_IPHONE 0x1103

// values we're using
#define USB_MAX_PACKETSIZE 64
#define USB_SETUP_PACKETS_AT_A_TIME 1
#define CONTROL_SEND_BUFFER_LEN 0x80
#define CONTROL_RECV_BUFFER_LEN 0x80
#define TX_QUEUE_LEN 0x80

// one packet at a time
#define USB_MULTICOUNT 1

#define USB_LANGID_ENGLISH_US 0x0409

#define USBError 0xEEE

enum USBState {
	USBStart = 0,
	USBPowered = 1,
	USBDefault = 2,
	USBAddress = 3,
	USBConfigured = 4,

	// Values higher than USBError(0xEEE) are error conditions
	USBUnknownDescriptorRequest = 0xEEE,
	USBUnknownRequest = 0xEEF
};

enum USBDirection {
	USBOut = 0,
	USBIn = 1,
	USBBiDir = 2
};

enum USBTransferType {
	USBControl = 0,
	USBIsochronous = 1,
	USBBulk = 2,
	USBInterrupt = 3
};

enum USBSynchronisationType {
	USBNoSynchronization = 0,
	USBAsynchronous = 1,
	USBAdaptive = 2,
	USBSynchronous = 3
};

enum USBUsageType {
	USBDataEndpoint = 0,
	USBFeedbackEndpoint = 1,
	USBExplicitFeedbackEndpoint = 2
};

enum USBDescriptorType {
	USBDeviceDescriptorType = 1,
	USBConfigurationDescriptorType = 2,
	USBStringDescriptorType = 3,
	USBInterfaceDescriptorType = 4,
	USBEndpointDescriptorType = 5,
	USBDeviceQualifierDescriptorType = 6
};

enum USBSpeed {
	USBHighSpeed = 0,
	USBFullSpeed = 1,
	USBLowSpeed = 2
};

struct USBEndpointHandlerInfo {
	void*	handler;
	unsigned int		token;
};

struct USBEPRegisters {
	unsigned int control;
	unsigned int field_4;
	unsigned int interrupt;
	unsigned int field_8;
	unsigned int transferSize;
	void* dmaAddress;
	unsigned int field_18;
	unsigned int field_1C;	
};

struct USBDeviceDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned short bcdUSB;
	unsigned char bDeviceClass;
	unsigned char bDeviceSubClass;
	unsigned char bDeviceProtocol;
	unsigned char bMaxPacketSize;
	unsigned short idVendor;
	unsigned short idProduct;
	unsigned short bcdDevice;
	unsigned char iManufacturer;
	unsigned char iProduct;
	unsigned char iSerialNumber;
	unsigned char bNumConfigurations;
};

struct USBConfigurationDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned short wTotalLength;
	unsigned char bNumInterfaces;
	unsigned char bConfigurationValue;
	unsigned char iConfiguration;
	unsigned char bmAttributes;
	unsigned char bMaxPower;
};

struct USBInterfaceDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned char bInterfaceNumber;
	unsigned char bAlternateSetting;
	unsigned char bNumEndpoints;
	unsigned char bInterfaceClass;
	unsigned char bInterfaceSubClass;
	unsigned char bInterfaceProtocol;
	unsigned char iInterface;
};

struct USBEndpointDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned char bEndpointAddress;
	unsigned char bmAttributes;
	unsigned short wMaxPacketSize;
	unsigned char bInterval;
};

struct USBDeviceQualifierDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned short bcdUSB;
	unsigned char bDeviceClass;
	unsigned char bDeviceSubClass;
	unsigned char bDeviceProtocol;
	unsigned char bMaxPacketSize;
	unsigned char bNumConfigurations;
	unsigned char bReserved;
};

struct USBStringDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	char bString[];
};

struct USBFirstStringDescriptor {
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned short wLANGID[];
};

struct USBInterface {
	USBInterfaceDescriptor descriptor;
	USBEndpointDescriptor* endpointDescriptors;
};

struct USBConfiguration {
	USBConfigurationDescriptor descriptor;
	USBInterface* interfaces;
};

struct USBSetupPacket {
	unsigned char bmRequestType; //0x0
	unsigned char bRequest; //0x4
	unsigned short wValue; //0x8
	unsigned short wIndex; //0xC
	unsigned short wLength; //0x10
};

struct RingBuffer {
	char* writePtr; //0x0
	char* readPtr; //0x4
	unsigned int count; //0x8
	unsigned int size; // 0x10
	char* bufferStart; // 0x14
	char* bufferEnd; // 0x18
};

#define USBSetupPacketHostToDevice 0
#define USBSetupPacketDeviceToHost 1
#define USBSetupPacketStandard 0
#define USBSetupPacketClass 1
#define USBSetupPacketVendor 2
#define USBSetupPacketRecpientDevice 0
#define USBSetupPacketRecpientInterface 1
#define USBSetupPacketRecpientEndpoint 2
#define USBSetupPacketRecpientOther 3

#define USB_GET_STATUS 0
#define USB_CLEAR_FEATURE 1
#define USB_SET_FEATURE 3
#define USB_SET_ADDRESS 5
#define USB_GET_DESCRIPTOR 6
#define USB_SET_DESCRIPTOR 7
#define USB_GET_CONFIGURATION 8
#define USB_SET_CONFIGURATION 9
#define USB_GET_INTERFACE 10
#define USB_SET_INTERFACE 11
#define USB_SYNCH_FRAME 12

