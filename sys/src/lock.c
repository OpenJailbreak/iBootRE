void enter_critical_section() {
	TaskDescriptor* current_task = *gTaskRunning;
	if(current_task->irq_disable_count < 0
			&& current_task->irq_disable_count > 1000) {
		panic("enter_critical_section", "ASSERT FAILED at (%s:%s:%d): %s\n", 
			"sys/lock.c", "enter_critical_section", LINE_NUMBER, 
			"current_task->irq_disable_count >= 0");
	}

	current_task->irq_disable_count++;
	if(current_task->irq_disable_count == 1) {
		disable_irq();
	}
}

void exit_critical_section() {
	TaskDescriptor* current_task = *gTaskRunning;
	if(current_task->irq_disable_count < 0
			&& current_task->cirq_disable_count > 1000) {
		panic("exit_critical_section", "ASSERT FAILED at (%s:%s:%d): %s\n", 
			"sys/lock.c", "exit_critical_section", LINE_NUMBER, 
			"current_task->irq_disable_count > 0");
	}

	current_task->irq_disable_count--;
	if(current_task->irq_disable_count == 0) {
		enable_irq();
	}
}

void enable_irq() {
	__asm__("mrs r0, cpsr");
	__asm__("bic r1, r0, #0x80");
	__asm__("msr cpsr_c, r1");
	__asm__("and r0, r0, #0x80");
}

void disable_irq() {
	__asm__("mrs r0, cpsr");
	__asm__("orr r1, r0, #0x80");
	__asm__("msr cpsr_c, R1");
	__asm__("and r0, r0, #0x80");
}

