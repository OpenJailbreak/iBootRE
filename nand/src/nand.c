#include "nand.h"

int nand_reset_bank(void* fmi, unsigned int bank) {
	int ret = 0;
	int status = 0;
	
	FMI0_CTRL0(1 << (bank & 7);
	FMI0_CMD(0xFF);
	FMI0_CTRL1(1);
	
	status = wait_for_done(fmi, 0x40044, 1, 1);
	usleep(20000);
	FMI0_CTRL0(0);
	
	// return (((status - 1) & ~(status)) >> 0x1F) ^ 1;
	ret = status - 1;
	ret &= ~status;
	ret >>= 0x1F;
	ret ^= 1;
	return ret;
}

int wait_for_done(void* fmi, void* reg, unsigned int mask, unsigned int val) {
	unsigned long long start = timer_get_microseconds();
	while(1) {
		if((GET_REG(fmi->base + reg) & mask) == val) break;
		if(timer_has_elapsed(fmi, bank, start)) return -1;
	}
	return 0;
}

int nand_read_chip_id(void* fmi, int bank, int* chip_id) {
	FMI0_CTRL(1 << (bank & 0x7);
	FMI0_CMD(FMI_CMD_READID)
	fmi->base + 0x40018 = 0x0;
	fmi->base + 0x40020 = 0x0;
	FMI0_CTRL1(0x9);
	
	int id;
	int ret = 0;
	int status = wait_for_done(fmi, fmi->base + 0x40044, 0x9, 0x9);
	if(status != 0) {
		nand_pio_read_sector(fmi, 5, &id);
		/*
		LDRB    R3, [R5,#3]
		LSLS    R2, R3, #0x18
		LDRB    R3, [R5,#2]
		LSLS    R3, R3, #0x10
		ORRS    R2, R3
		LDRB    R3, [R5]
		ORRS    R2, R3
		LDRB    R3, [R5,#1]
		LSLS    R3, R3, #8
		ORRS    R3, R2
		MOVS    R2, #1
		STR     R3, [R6]
		*/

	} else {
		ret = 0;
	}

	FMI0_CTRL0(0);
	return ret;
}

int nand_pio_read_sector(void* fmi, unsigned int num, void* var) {
	int count = 0;
	fmi->base + 0x240024 = 0;
	while(count != num) {
		FMI0_CTRL1(0x50);
		var[count] = FMI0_GET_FIFO0;
		count++;
		FMI0_CTRL1(0);
	}
}

int nand_read_block(void* fmi, unsigned int bank, unsigned int page) {

}

int nand_read_bootpage(void* fmi, unsigned int bank, void* destination, unsigned int* size) {
	unsigned int pagesRead = 0;
	unsigned int remaining = *size;
	while(remaining > 0x5FF) {
		
	}
	
	nand_close_gate(fmi);
	*size = (((pagesRead << 1) + pagesRead) << 9) + 0xFFFFF400
	if(*size != 0) return 0;
	return -1;
}
