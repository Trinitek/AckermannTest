
#include <stdio.h>
#include <stdint.h>
#include <windows.h>

typedef uint64_t (*ACKERMANN)(uint64_t m, uint64_t n);
void testAck(uint64_t m, uint64_t n);

ACKERMANN ack;

int main(void) {
    
    HMODULE ackDll = LoadLibrary("ackermann.dll");
    if (ackDll == NULL) {
        printf("Could not import ACKERMANN.DLL: 0x%x\n", GetLastError());
        return 1;
    } else {
        printf("Imported ACKERMANN.DLL\n");
    }
    
    ack = (ACKERMANN) GetProcAddress(ackDll, "ack");
    if (ack == NULL) {
        printf("Could not find 'ACK' in library: 0x%x\n", GetLastError());
        return 1;
    } else {
        printf("'ACK' found at 0x%x\n", ack);
    }
    
    for (int x = 0; x <= 4; x++)
        for (int y = 0; y <= 5; y++)
            testAck(x,y);
    
    return 0;
}

void testAck(uint64_t m, uint64_t n) {
    
    uint64_t i = ack(m, n);
    printf("ack(%llu, %llu) = %llu\n", m, n, i);
    
    return;
}
