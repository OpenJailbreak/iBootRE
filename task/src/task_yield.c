#include <stdio.h>
#include <stdint.h>

typedef enum Boolean {
	FALSE = 0,
	TRUE = 1
} Boolean;

typedef enum OnOff {
	OFF = 0,
	ON = 1
} OnOff;

#ifndef NULL
#define NULL 0
#endif
#define uSecPerSec 1000000

typedef struct Event Event;

typedef void (*TaskRoutineFunction)(void* opaque);
typedef void (*EventHandler)(Event* event, void* opaque);

typedef struct LinkedList {
	void* prev;
	void* next;
} LinkedList;

typedef struct TaskRegisterState {
	uint32_t	r4;
	uint32_t	r5;
	uint32_t	r6;
	uint32_t	r7;
	uint32_t	r8;
	uint32_t	r9;
	uint32_t	r10;
	uint32_t	r11;
	uint32_t	sp;
	uint32_t	lr;
} TaskRegisterState;

typedef enum TaskState {
	TASK_READY = 1,
	TASK_RUNNING = 2,
	TASK_SLEEPING = 4,
	TASK_STOPPED = 5
} TaskState;

#define TaskDescriptorIdentifier1 0x7461736b
#define TaskDescriptorIdentifier2 0x74736b32
#define StackIdentifier 0x7374616B

struct Event {
	LinkedList	list;
	uint64_t	deadline;
	uint64_t	interval;
	EventHandler	handler;
	void*		opaque;
};

typedef struct TaskDescriptor {
	uint32_t		identifier1;
	LinkedList		taskList;
	LinkedList		runqueueList;
	TaskState		state;
	uint32_t		criticalSectionNestCount;
	TaskRegisterState	savedRegisters;
	Event			sleepEvent;
	LinkedList		linked_list_3;
	uint32_t		exitState;
	TaskRoutineFunction	taskRoutine;
	void*			unknown_passed_value;
	void*			storage;
	uint32_t		storageSize;
	char			taskName[16];
	uint32_t		identifier2;
} TaskDescriptor;

TaskDescriptor* CurrentRunning;
TaskDescriptor* IdleTask;
uint32_t* ResetVector;
uint32_t* TaskCount;

LinkedList* TaskQueue;

void task_yield() {
    TaskDescriptor* new_task;
    TaskDescriptor* current_task;
    uint32_t task_count = *TaskCount;
    // are we the only running process, if so make sure we're running
    if(task_count != 0) {
        current_task = CurrentRunning;  
    } else {
        if(current_task->state != TASK_RUNNING) {
            return;
        }
    }
    
    // check and make sure the task magic hasn't changed
    if(current_running->identifier1 != TaskDescriptorIdentifier1) {
        if(*ResetVector != *((uint32_t*)0x0)) {
            panic("task_yield", "reset vector overwritten while executing task \'%s\' (0x%08x)", current_task->taskName);
        }
        if(*(current_task->storage) != StackIdentifier) {
            panic("task_yield", "task \'%s\' has overflowed its stack", current_task->taskName);
        }
    }
    
    enter_critical_section();
    // is this a normal task yielding or idle task?
    if(current_task != IdleTask && current_task->state == TASK_RUNNING) {
        current_task->state--;
        current_task->runqueueList.next = TaskQueue;
        current_task->runqueueList.prev = TaskQueue->prev;
        TaskQueue->prev = current_task->runqueueList;
        TaskQueue->prev->next = current_task->runqueueList;
        task_count += 1;
    }
    
    // check if taskqueue is empty or not
    if(TaskQueue->next != TaskQueue) {
        TaskQueue->prev = TaskQueue->next->prev;
        TaskQueue->next = TaskQueue->next->next;
        TaskQueue->next->next = 0;
        new_task = (void*)((*TaskQueue)-0xC);
        if(TaskQueue->next != NULL) {
            task_count -= 1;
        } else {
            new_task = IdleTask;
        }
    } else {
        new_task = IdleTask;
    }
    
    new_task->state = TASK_RUNNING;
    context_switch(current_task->savedRegisters, new_task->savedRegisters);
    current_task = new_task;
    exit_critical_section();
}

void context_switch(void* old_registers, void* new_registers) {
    __asm__("stmfd r0!, {r4-r11,sp,lr}");
    __asm__("ldmfd r1!, {r4-r11,sp,lr}");
}
