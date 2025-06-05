.section __TEXT,__text
.globl _main
.align 2

_main:
    mov x0, #1              // stdout (fd = 1)
    adrp x1, message@PAGE   // load page of message into x1
    add  x1, x1, message@PAGEOFF  // add offset within page
    mov x2, #13             // length of message
    mov x16, #4             // syscall: write
    svc #0x80               // make syscall

    mov x0, #0              // return code
    mov x16, #1             // syscall: exit
    svc #0x80

.section __TEXT,__cstring
message:
    .asciz "Hello, World\n"