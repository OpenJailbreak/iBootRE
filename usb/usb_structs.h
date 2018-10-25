struct USBEPRegisters {
	unsigned int control;
	unsigned int field_4;
	unsigned int interrupt;
	unsigned int field_8;
	unsigned int transferSize;
	void* dmaAddress;
	unsigned int field_18;
	unsigned int field_1C
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
	unsigned char bmRequestType;
	unsigned char bRequest;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;
};

struct RingBuffer {
	char* writePtr;
	char* readPtr;
	unsigned int count
	unsigned int size;
	char* bufferStart;
	char* bufferEnd;
};

struct usb_controller_ops {
    void* start;                      // 0x0
    void* stop;                       // 0x4
    void* set_address;                // 0x8
    void* stall_endpoint;             // 0xC
    void* reset_endpoint_data_toggle; // 0x10
    void* is_endpoint_stalled;        // 0x14
    void* do_endpoint_io;             // 0x18
    void* activate_endpoint;          // 0x1C
    void* deactivate_endpoint;        // 0x20
    void* abort_endpoint;             // 0x24
    void* do_test_mode;               // 0x28
    void* get_connection_speed;       // 0x2C
};

struct usb_request {
	unsigned int unk0x0;
	void* data;
	unsigned int unk0x8;
	unsigned int unk0xC;
	unsigned int unk0x10;
	void* callback;
};
