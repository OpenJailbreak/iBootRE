typedef enum {
    kNorContainer = 0x696D6733, // img3
    kImg3Container = 0x496D6733, // Img3
    k8900Container = 0x30303938, // 8900
    kImg2Container = 0x494D4732 // IMG2
} ImageContainer;

typedef enum {
    kIBootImage = 0x69626F74, // ibot
    kLLBImage = 0x696C6C62, // illb
    kDeviceTreeImage = 0x64747265, // dtre
    kNeedServiceImage = 0x6E737276,
    kRecoveryModeImage = 0x7265636D,
    kGlyphChargingImage = 0x676C7943,
    kGlyphPluginImage = 0x676c7950,
    kBatteryLow0Image = 0x62617430,
    kBatteryLow1Image = 0x62617431,
    kBatteryCharging0Image = 0x63686730,
    kBatteryCharging1Image = 0x63686731,
    kBatteryFullImage = 0x62617446,
    kAppleLogoImage = 0x6C6F676F // logo
    //kKernelImage = 0x // krnl
    //kRamdiskImage = 0x // rdsk
} ImageType;

typedef enum {
    kDataElement = 0x44415441, // DATA
    kTypeElement = 0x54595045, // TYPE
    kKbagElement = 0x4B424147, // KBAG
    kShshElement = 0x53485348, // SHSH
    kCertElement = 0x43455254, // CERT
    kChipElement = 0x43484950, // CHIP
    kProdElement = 0x50524F44, // PROD
    kSdomElement = 0x53444F4D // SDOM
    // BORD
    // SEPO
} ElementType;


typedef struct {
    unsigned int signature;
    unsigned char version[3];
    unsigned char format;
    unsigned int unk1;
    unsigned int dataSize;
    unsigned int footerSignatureOffset;
    unsigned int footerCertOffset;
    unsigned int footerCertSize;
    unsigned char salt[0x20];
    unsigned short unk2;
    unsigned short epoch;
    unsigned char headerSignature[0x10];
    unsigned char padding[0x7B0];
} Image8900Header;

typedef struct {
	unsigned int signature;        /* 0x0 */
	unsigned int imageType;        /* 0x4 */
	unsigned short unknown1;         /* 0x8 */
	unsigned short security_epoch;   /* 0xa */
	unsigned int flags1;           /* 0xc */
	unsigned int dataLenPadded;    /* 0x10 */
	unsigned int dataLen;          /* 0x14 */
	unsigned int unknown3;         /* 0x18 */
	unsigned int flags2;           /* 0x1c */ /* 0x01000000 has to be unset */
	unsigned char  reserved[0x40];   /* 0x20 */
	unsigned int unknown4;         /* 0x60 */ /* some sort of length field? */
	unsigned int header_checksum;  /* 0x64 */ /* standard crc32 on first 0x64 bytes */
	unsigned int checksum2;        /* 0x68 */
	unsigned char  unknown5[0x394]; /* 0x68 */
} Img2Header;

typedef struct {
    unsigned int signature;
    unsigned int fullSize;
    unsigned int dataSize;
    unsigned int shshOffset;
    unsigned int imageType;
} ImageHeader;

typedef struct {
    unsigned int signature;
    unsigned int fullSize;
    unsigned int dataSize;
} ImageElementHeader;

typedef struct {
    ImageElementHeader header;
    unsigned int state;
    unsigned int type;
    unsigned char iv[16];
    unsigned char key[32];
} ImageKbagElement;

struct ImageDescriptor {
    ImageDescriptor* prev;
    ImageDescriptor* next;
    void* bdev;
    unsigned int startAddress;
    unsigned int unk0x14;
    unsigned int dataSize;
    unsigned int imageSize;
    unsigned int imageIdentifier;
    unsigned int imageType;
    unsigned int unk0x28;
};

struct TempImage {
    void* imageData;
    unsigned int unk0x4; // = 0x1 | 0x20000 | 0x40000;
    unsigned int imageSize;
    unsigned int unk0x10;
    unsigned int unk0x14; // = 0;
    unsigned int unk0x18;
};

typedef enum {
    kMainHeader = 0,
    kSecondHeader = 1
} HeaderType;


int image_get_element(void* image_struct, unsigned int element, void** destination, unsigned int* size, unsigned int count);
int image_load(void* memz, ImageType signature, void* destination, unsigned int size_in, unsigned int size_out);
int image_validate(void* memz, ImageType signature, void* destination, unsigned int size_in, unsigned int size_out);
int image_parse_header(void** imageInfo, void* imageData, unsigned int imageSize, unsigned int headerType);
int image_parse_footer();

