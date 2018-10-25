#define kCmdStringArg 0
#define kCmdIntegerArg 1

typedef struct {
	signed int unk1;
	unsigned int uinteger;
	signed int integer;
	unsigned int type;
	unsigned char* string;
} CmdArg;

typedef int(*CmdFunction)(int argc, CmdArg* argv);

typedef struct {
	char* name;
	CmdFunction handler;
	char* description;
} CmdInfo;

//cmd_bootx(int argc, CmdArg* argv);
