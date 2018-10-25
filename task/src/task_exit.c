

int task_exit(int state) {
    TaskDescriptor* current_task = *gTaskRunning;
    current_task.exitState = state;
    
    current_task.state = TASK_STOPPED;
    
    task_remove(current_task.linked_list_3);
    *task_stack--;
    
    task_yield();
    panic("task_exit", "task_exit: should not be here\n")'
}

int task_remove(LinkedList* list) {
    //PUSH    {R4-R7,LR}
    //ADD     R7, SP, #0xC
    //MOV     R6, R0
    //BL      enter_critical_section
    enter_critical_section();
    
    //LDR     R3, [R6,#LinkedList.next]
    //MOVS    R5, #0
    int cnt = 0;
    
    //SUB.W   R0, R3, #0xC
    TaskDescriptor* task = (void*) *gTaskList->next
    
    //LDR     R3, [R3,#LinkedList.next]
    //SUB.W   R4, R3, #0xC
    //B       loc_4FF19428
    
    //ADD.W   R3, R0, #0xC
    //CMP     R3, R6
    //BNE     loc_4FF19406
    while(task->taskList.next != *gTaskList) {
        //LDR     R2, [R0,#TaskDescriptor.runqueueList.next]
        next = task->next;
        
        //LDR     R3, [R0,#TaskDescriptor.runqueueList.prev]
        prev = task->prev;
        
        //ADDS    R5, #1
        cnt++;
        
        //STR     R3, [R2]
        task->next = prev;
        
        //LDR     R3, [R0,#TaskDescriptor.runqueueList.prev]
        prev = task->prev;
        
        //STR     R2, [R3,#LinkedList.next]
        task->prev->next = task->next;
        
        //MOVS    R3, #0
        //STR     R3, [R0,#TaskDescriptor.runqueueList.next]
        task->next = NULL;
        
        //STR     R3, [R0,#TaskDescriptor.runqueueList.prev]
        task->prev = NULL;
        
        //ADDS    R3, #TASK_READY
        //STR     R3, [R0,#TaskDescriptor.state]
        task->state = TASK_READY;
        
        //BL      task_add_queue
        task_add_queue(...);
        
        //LDR     R3, [R4,#TaskDescriptor.runqueueList.next]
        //MOV     R0, R4
        //SUB.W   R4, R3, #0xC
        task = task->next;
    }
    
    //BL      exit_critical_section
    exit_critical_section();
    
    //MOV     R0, R5
    return cnt;

}
