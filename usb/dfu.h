struct usb_device_callbacks {
	void* usb_send_file;
	void* usb_receive_file;
	void* usb_unknown_0x8;
	void* usb_unknown_0xC;
	void* usb_unknown_0x10;
	void* usb_unknown_0x14;
	void* usb_idle;
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
