
format PE64 DLL
entry DllMain
stack 16384

include 'include/win64a.inc'

section '.text' code readable executable

proc DllMain hinstDLL, fdwReason, lpvReserved
    mov rax, 1
    ret
endp

proc ack

    define m rcx
    define n rdx
    define r rax
    
    call near .start
    ret
    
    .start:
        cmp m, 0                    ; while (m)
        jz .return
    
    .calc:
        cmp n, 0                    ; if (n == 0)
        jnz @f
        mov n, 1                    ; n = 1
        jmp .tail
        
        @@:                         ; else
        push m                      ; n = ack(m, n - 1)
        dec n
        call near .calc
        pop m
        mov n, r
        
    .tail:
        dec m                       ; m--
        cmp m, 0                    ; <duplicate test> while (m)
        jz .return
        jmp .calc
        
    .return:
        mov r, n                    ; return (n + 1)
        inc r
        retn
        
endp

section '.edata' export data readable

export 'ackermann.dll',\
    ack, 'ack'

data fixups
end data
