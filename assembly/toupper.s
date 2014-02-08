    .section .data
    
    # system call numbers
    .equ SYS_OPEN, 5
    .equ SYS_WRITE, 4
    .equ SYS_READ, 3
    .equ SYS_CLOSE, 6
    .equ SYS_EXIT, 1


    #open mode
    .equ O_RDONLY, 0x0000
    .equ O_WRONLY, 0x0001
    .equ O_RDWR, 0x0002
    .equ O_ACCMODE, 0x0003

    # std file descriptors
    .equ STDIN, 0
    .equ STDOU, 1
    .equ STDERR, 2

    # interrupt
    .equ LINUX_SYSCALL, 0x80
    .equ END_OF_FILE, 0 # end of file
    .equ NUMBER_ARGUMENTS, 2
    
    .section .bss
    .equ BUFFER_SIZE, 500
    .lcomm BUFFER_DATA, BUFFER_SIZE
    

    .section __TEXT,__text,regular,pure_instructions
    .align 4, 0x90
    # stack positions
    .equ ST_SIZE_RESERVE, 8
    .equ ST_FD_IN, -4  # store read file descriptor
    .equ ST_FD_OUT, -8 # store write file descriptor
    .equ ST_ARGC, 0  # store num of args
    .equ ST_ARGV_0, 4 # store name of program
    .equ ST_ARGV_1, 8 # input fname
    .equ ST_ARGV_2, 12 # output fname
    .globl _main
_main:
    movl %esp, %ebp # enter main, initialize base pointer
    subl $ST_SIZE_RESERVE, %esp

open_files:
open_fd_in:
    movl $SYS_OPEN, %eax # sys call to eax
    movl ST_ARGV_1(%ebp), %ebx # input fname to ebx
    movl $O_RDONLY, %ecx # flag to ecx
    movl $0666, %edx # priviledge to edx
    int $LINUX_SYSCALL # open read sys call

store_fd_in:
    movl %eax, ST_FD_IN(%ebp)  # after open, we store fd in eax.

open_fd_out:
    movl $SYS_WRITE, %eax # sys call number to eax
    movl ST_ARGV_2(%ebp), %ebx # output fname to ebx
    movl $O_RDWR, %ecx # flag to ecx
    movl $0666, %edx
    int $LINUX_SYSCALL # open write sys call

store_fd_out:
    movl %eax, ST_FD_OUT(%ebp)

read_loop_begin:
    movl $SYS_READ, %eax
    movl ST_FD_IN(%ebp), %ebx # get input fd
    movl $BUFFER_DATA, %ecx # location to read to ecx
    movl $BUFFER_SIZE, %edx # buffer size to edx
    int $LINUX_SYSCALL

    cmpl $END_OF_FILE, %eax  # eax <= 0, error or end-of-file
    jle end_loop

continue_read_loop:
    # convert buffer to upper
    pushl $BUFFER_DATA # location of buffer
    pushl %eax # number of bytes in buffer(return after read)
    call _convert_to_upper
    popl %eax  # restore size to %eax
    addl $4, %esp # restore esp

    # write to buffer
    movl %eax, %edx # buffer size to edx
    movl $SYS_WRITE, %eax
    movl ST_FD_OUT(%ebp), %ebx # filename to ebx
    movl $BUFFER_DATA, %ecx  # buf address to ecx
    int $LINUX_SYSCALL # write sys call
    
    jmp read_loop_begin

end_loop:
    # close write
    movl $SYS_CLOSE, %eax # sys call to eax
    movl ST_FD_OUT(%ebp), %ebx # file to close
    int $LINUX_SYSCALL # 
    
    # close read
    movl $SYS_CLOSE, %eax
    movl ST_FD_IN(%ebp), %ebx
    int $LINUX_SYSCALL
    
    movl $SYS_EXIT, %eax
    movl $0, %ebx
    int $LINUX_SYSCALL
