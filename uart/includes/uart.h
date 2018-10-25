
typedef enum {
	kUartModePoll = 0
} uart_mode;

typedef struct uart_settings {
	unsigned int ureg;
	unsigned int baud;
	unsigned int sample_rate;
	unsigned int flow_control;
	unsigned int fifo;
	unsigned int mode;
	unsigned int clock;
} uart_settings;

typedef struct uart_registers {
	unsigned int ULCON;
	unsigned int UCON;
	unsigned int UFCON;
	unsigned int UMCON;

	unsigned int UTRSTAT;
	unsigned int UERSTAT;
	unsigned int UFSTAT;
	unsigned int UMSTAT;

	unsigned int UTXH;
	unsigned int URXH;
	unsigned int UBAUD;
	unsigned int UINTP;
} uart_registers;

int uart_write(int ureg, const char *buffer, unsigned int length);
int uart_read(int ureg, char *buffer, unsigned int length, unsigned int timeout);

