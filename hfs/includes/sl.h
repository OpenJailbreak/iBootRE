// Device Types
enum {
  kUnknownDeviceType = 0,
  kNetworkDeviceType = 1,
  kBlockDeviceType = 2
};

// File Permissions and Types
enum {
  kPermOtherExecute  = 0x1,
  kPermOtherWrite    = 0x2,
  kPermOtherRead     = 0x4,
  kPermGroupExecute  = 0x8,
  kPermGroupWrite    = 0x10,
  kPermGroupRead     = 0x20,
  kPermOwnerExecute  = 0x40,
  kPermOwnerWrite    = 0x80,
  kPermOwnerRead     = 0x100,
  kPermMask          = 0x1FF,
  kOwnerNotRoot      = 0x200,
  kFileTypeUnknown   = 0x0,
  kFileTypeFlat      = 0x10000,
  kFileTypeDirectory = 0x20000,
  kFileTypeLink      = 0x30000,
  kFileTypeMask      = 0x30000
};

// Key Numbers
enum {
    kCommandKey = 0x200,
    kOptKey     = 0x201,
    kShiftKey   = 0x202,
    kControlKey = 0x203,
    kDeleteKey  = 0x204
};

// Boot Modes
enum {
  kBootModeNormal = 0,
  kBootModeSafe = 1,
  kBootModeSecure = 2
};

// types for plist.c
typedef enum {
  kTagTypeNone = 0,
  kTagTypeDict = 1,
  kTagTypeKey = 2,
  kTagTypeString = 3,
  kTagTypeInteger = 4,
  kTagTypeData = 5,
  kTagTypeDate = 6,
  kTagTypeFalse = 7,
  kTagTypeTrue = 8,
  kTagTypeArray = 9
} TagType;

struct Tag {
  enum TagType     type;
  char       *string;
  struct Tag *tag;
  struct Tag *tagNext;
};
