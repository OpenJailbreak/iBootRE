#define CLOCK_GATE_BASE  0xBF100078
#define CLOCK_GATE_MAX   0xBF100144

void clock_gate_switch(unsigned int gate, unsigned int value) {
    void* clockgate = ((gate << 2) + CLOCK_GATE_BASE);
    if(clockgate < CLOCK_GATE_MAX) {
        if(value) *clockgate |= 0xF;
        else *clockgate &= ~0xF;
    }
}
