section .text
    [bits 32]
    global _start ;kernel entry es clave

    _start:
        extern main
        call main
    .hang:
        jmp .hang
