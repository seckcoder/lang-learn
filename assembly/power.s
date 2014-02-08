# example from Programming Group up
    .section __TEXT,__text,regular,pure_instructions
    .globl _power
    .align 4, 0x90
_power:
    pushl %ebp
    movl %esp, %ebp  # ebp = esp
    subl $4, %esp  # get room for local storage
    movl 8(%ebp), %ebx # ebx = base
    movl 12(%ebp), %ecx # ecx = power
    movl %ebx, -4(%ebp) # store current result
    
power_loop_start:
    cmpl $1, %ecx
    je end_power
    movl -4(%ebp), %eax # move current result to %eax
    imull %ebx, %eax # eax *= ebx
    movl %eax, -4(%ebp) # update current result
    decl %ecx # power-=1
    jmp power_loop_start

end_power:
    movl -4(%ebp), %eax # eax = result
    movl %ebp, %esp # (dispose all local variables)
    popl %ebp # restore stack pointer and base pointer
    # top of stack is return address
    ret  # popl %eip; jmp $eip

    .globl _main
    .align 4, 0x90
_main:
    pushl $3
    pushl $2
    call _power
    addl $8, %esp
    pushl %eax
    pushl $2
    pushl $5
    call _power
    addl $8, %esp
    popl %ebx
    addl %eax, %ebx
    # exit
    movl $1, %eax
    int $0x80
