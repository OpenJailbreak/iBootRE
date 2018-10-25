enum Boolean {
	FALSE = 0,
	TRUE = 1
};

enum OnOff {
	OFF = 0,
	ON = 1
};

typedef struct LinkedList {
	void* prev;
	void* next;
};

void panic(const char* function, char* message, ...);
