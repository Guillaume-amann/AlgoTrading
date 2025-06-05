.section __TEXT,__cstring
message:
    .asciz "Hello, World\n"
message_end:                // address directly after the end of previous label

.section __TEXT,__text
.globl _main
.align 2

_main:
    // macOS uses syscall 0x2000004 for write
    mov x0, #1              // stdout
    ldr x1, =message        // pointer to message
    ldr x2, =message_end
    sub x2, x2, x1          // length = message_end - message
    mov x16, #4             // syscall: write
    svc #0x80

    // exit(0)
    mov x0, #0              // return 0
    mov x16, #1             // syscall: exit
    svc #0x80