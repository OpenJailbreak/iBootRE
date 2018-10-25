enum Boolean {
	FALSE = 0,
	TRUE = 1
};

enum OnOff {
	OFF = 0,
	ON = 1
};

struct LinkedList {
	void* prev;
	void* next;
};

struct TaskRegisterState {
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int sp;
	unsigned int lr;
};

enum TaskState {
	TASK_READY = 1,
	TASK_RUNNING = 2,
	TASK_SLEEPING = 4,
	TASK_STOPPED = 5
};

struct Event {
	struct LinkedList list;
	unsigned int deadline_a;
	unsigned int deadline_b;
	unsigned int interval_a;
	unsigned int interval_b;
	void* handler;
	void* opaque;
};

struct TaskDescriptor {
	unsigned int identifier1;
	struct LinkedList taskList;
	struct LinkedList runqueueList;
	enum TaskState state;
	unsigned int criticalSectionNestCount;
	struct TaskRegisterState savedRegisters;
	struct Event sleepEvent;
	struct LinkedList linked_list_3;
	unsigned int exitState;
	void* taskRoutine;
	void* unknown_passed_value;
	void* storage;
	unsigned int storageSize;
	char taskName[16];
	unsigned int identifier2;
};
