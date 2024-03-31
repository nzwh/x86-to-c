%include "io64.inc"
section .bss
    vala resb 8
    valb resb 8
    vall resb 8
    
section .data
    zero dq 0.0
    a dq 2.0
    b dq 4.0
    
    dp: db "Dot product: %1f", 10, 0
    
section .text
    global main
    extern printf
    
main:
    sub rsp, 100 ; shift stack
    
    GET_UDEC 8, [vall]
    ;GET_UDEC 8, [vala]
    ;GET_UDEC 8, [valb]
   
    mov rsi, 0 ; reset ctr to 0
    movsd xmm0, [zero] ; set sum to 0
    
    dot_product:
        cmp rsi, [vall] ; compare value to limit
        je exit ; if equal, exit
        
        movsd xmm1, [a] ; move to xmm
        movsd xmm2, [b] ; move to xmm
        
        mulsd xmm1, xmm2 ; simulate a*b
        addsd xmm0, xmm1 ; add a*b to sum
        
        inc rsi ; increment rsi
        jmp dot_product ; loop
        
    exit:
        lea rcx, [dp] ; move X1 format to rcx
        movq rdx, xmm0 ; move value to rdx
        mov rax, 1 ; printf signal
        call printf ; print
     
        add rsp, 100 ; reset stack
        
    xor rax, rax
    ret