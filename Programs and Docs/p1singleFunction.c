/* The source translation into assembly for a single function */

#include <stdio.h>

/* Source Code */
int main()
{
  int a = 10;
  int b = 20;
  int c;
  c = a + b;
  return 0;
}

/* Assembly Translation of the Source Code */
#if 0

Notes
-----
eax,edx,ebp,esp are registers.
  -eax - Extended Accumulator Register
  -edx - Extended Data Register
  -ebp - Extended Base Pointer
  -esp - Extended Stack Pointer

Stack Growing Downwards According to Sys V ABI

Base of Stack - Higher Address
Top of Stack  - Lower Address

GCC follows AT & T Assembly Syntax

C function calling convention is followed by Sys V ABI
-CDECL calling convention

Pictorial Representation
-------------------------

----------  0  Base of Stack (Higher Address)
c
---------- -4
b
---------- -8
a
---------- -12 Top of Stack (Lower Address)

main:
  /* The next two lines are preamble / prologue i.e. '{' in C Source */
  /* They can also be substituted by entry instruction */

  /* Save the ebp of previous stack frame */
  pushl   %ebp
  /* Initialize current stack frame by making ebp equal to esp */
  movl    %esp, %ebp

  /* Function Specific Instructions Start here */
  
  /* Allocate bytes according to symbol table.
  /* Access higher to lower address so subl is used */
  /* 16 instead of 12 due to alignment and padding by compiler */
  subl    $16, %esp
  /* Save 10 in [ebp-offset(12)] - Variable 'a' */
  movl    $10, -12(%ebp)
  /* Save 20 in [ebp-offset(8)]  - Variable 'b' */
  movl    $20, -8(%ebp)
  /* Save content of [ebp-offset(12)] in edx register */
  movl    -12(%ebp), %edx
  /* Save content of [ebp-offset(8)] in eax register*/
  movl    -8(%ebp), %eax
  /* Add the contents of edx and eax and save in eax*/
  addl    %edx, %eax
  /* Save eax result in [ebp-offset(4)] - Variable 'c'*/
  movl    %eax, -4(%ebp)
  /* Return 0 by writing 0 to eax - Val retained in eax */
  movl    $0, %eax
 
  /* The next two lines are postamble / epilogue i.e. '}' in C Source */
  /* leave internally performs the following two steps */
  /* 1. Cleanup of local variables by writing esp with same value as ebp */
  /* 2. Update the previous ebp value (saved in 1st step) in ebp register */
  leave
  	-movl %ebp, %esp 
   	-popl %ebp 
  /* Return to caller function by updating eip from stack into eip register*/
  ret
#endif
