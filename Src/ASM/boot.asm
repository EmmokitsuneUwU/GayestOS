[org 0x7c00]                        
KERNEL_LOCATION equ 0x10000
                                    
mov [BOOT_DISK], dl                 

mov ah,0x0e
mov al,'P'
int 0x10
mov al,'r'
int 0x10
mov al,'e'
int 0x10
mov al,'s'
int 0x10
mov al,'s'
int 0x10
mov al,' '
int 0x10
mov al,'A'
int 0x10
mov al,'n'
int 0x10
mov al,'y'
int 0x10
mov al,' '
int 0x10
mov al,'K'
int 0x10
mov al,'e'
int 0x10
mov al,'y'
int 0x10
mov al,' '
int 0x10
mov al,'T'
int 0x10
mov al,'o'
int 0x10
mov al,' '
int 0x10
mov al,'B'
int 0x10
mov al,'o'
int 0x10
mov al,'o'
int 0x10
mov al,'t'
int 0x10

; Sorry for that, im a lazy girl

mov ah,0x00
int 0x16

xor ax, ax                          
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov ax, 0x1000
mov es, ax
xor bx, bx
mov dh, 21 ; Sector ammount

mov ah, 0x02
mov al, dh 
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [BOOT_DISK]
int 0x13                
                                    
mov ah, 0x0
mov al, 0x3
int 0x10                ; text mode

CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

jmp $
                                    
BOOT_DISK: db 0

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start


[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
    mov ebp, 0xC0000   ; 32-bit stack base pointer
    mov esp, ebp

    jmp KERNEL_LOCATION

times 510-($-$$) db 0              
dw 0xaa55
