#include <wdt.h>

void wdt_reboot() {
	*(0xBF10021C) = 0;
	*(0xBF100214) = 1;
	
	SETREG(WDT_CONTROL, WDT_ENABLE);
	
	*(0xBF10021C) = 4;
	*(0xBF100210) = 0;
}
