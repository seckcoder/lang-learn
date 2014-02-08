    .section __TEXT,__text,regular,pure_instructions
    .globl _start
    .align 4, 0x90
_start:
    push $3
    push $2
    call power

.type power, @function
power:
    push %ebp
    movl %esp, %ebp  # ebp = esp
    subl $4, $esp  # get room for local storage
    movl 8(%ebp), %ebx # ebx = base
    movl 12(%ebp), %ecx # ecx = power
    movl %ebx, -4(%ebp) # store current result
    
power_loop_start
    cmpl $1,$ecx
    je end_power
    movl -4($ebp), %eax # move current result to %eax
    immull %ebx, %eax # eax *= ebx
    movl %eax, -4(%ebp) # update current result
    decl %ecx # power-=1
    jmp power_loop_start

end_power:
    movl -4(%ebp), %eax # eax = result
    movl %ebp, %esp # (dispose all local variables)
    popl %ebp # restore stack pointer and base pointer
    # top of stack is return address
    ret  # popl %eip; jmp $eip
