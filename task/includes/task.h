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
	unsigned int taskBegin;
	struct TaskDescriptor* prevTask;
	struct TaskDescriptor* nextTask;
	struct TaskDescriptor* prevJob;
	struct TaskDescriptor* nextJob;
	enum TaskState taskState;
	unsigned int criticalSectionNestCount;
	struct TaskRegisterState taskRegisters;
	struct Event sleepEvent;
	struct LinkedList linked_list_3;
	unsigned int exitState;
	void* taskHandler;
	void* taskArg;
	void* taskStack;
	unsigned int stackSize;
	char taskName[0x10];
	unsigned int taskEnd;
};
