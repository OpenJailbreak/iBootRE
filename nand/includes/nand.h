#define FMI0_CTRL0(value) *((volatile unsigned int*)0x8124000C) = (volatile unsigned int*)value)
#define FMI0_CTRL1(value) *((volatile unsigned int*)0x81240010) = (volatile unsigned int*)value)
#define FMI0_CMD(value) *((volatile unsigned int*)0x81240014) = (volatile unsigned int*)value)
#define FMI0_UNK2(value) *((volatile unsigned int*)0x81240024) = (volatile unsigned int*)value)
#define FMI0_STATUS(value) *((volatile unsigned int*)0x81240044) = (volatile unsigned int*)value) 
#define FMI0_SET_FIFO0(value) *((volatile unsigned int*)0x81240048) = (volatile unsigned int*)value)
#define FMI0_GET_FIFO0 *((volatile unsigned int*)0x81240048)

#define FMI_CMD_READID 0x90

typedef struct NandController {
	void* base;
}
