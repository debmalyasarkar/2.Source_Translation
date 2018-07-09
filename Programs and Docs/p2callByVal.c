/* Source Translation into Assembly for Multiple Functions - Call by Value */

#include <stdio.h>

/* Source Code */
void swap(int a, int b)
{
  int temp;
  temp = a;
  a = b;
  b = temp;
}


int main()
{
  int a,b;
  a = 10;
  b = 20;
  swap(a,b);
  return 0;
}

/* Assembly Translation of the Source Code */
#if 0
swap:
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
  /* Copy first argument into eax */
  movl	8(%ebp), %eax
  /* Save this argument value in current stack */
  movl	%eax, -4(%ebp)
  /* Copy second argument into eax */
  movl	12(%ebp), %eax
  /* Copy this value directly into 1st argument location */
  movl	%eax, 8(%ebp)
  /* Bring the saved 1st argument into eax */
  movl	-4(%ebp), %eax
  /* Copy this directly into 2nd argument location */
  /* Value of 1st and 2nd arguments are exchanged now */
  movl	%eax, 12(%ebp)

  /* The next two lines are postamble / epilogue i.e. '}' in C Source */
  /* leave internally performs the following two steps */
  /* 1. Cleanup of local variables by writing esp with same value as ebp */
  /* 2. Update the previous ebp value (saved in 1st step) in ebp register */
  leave
  	-movl %ebp, %esp 
   	-popl %ebp 
  /* Return to caller function by updating eip from stack into eip register*/
  ret

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
  /* Save 10 in [ebp-offset(8)] - Variable 'a' */
  movl    $10, -8(%ebp)
  /* Save 20 in [ebp-offset(4)] - Variable 'b' */
  movl    $20, -4(%ebp)
  /* Save the rightmost argument in stack */
  pushl	-4(%ebp)
  /* Save the next argument to its left in stack */
  pushl	-8(%ebp)
  /* Save instruction pointer value in stack and jump to execute swap() */
  call	swap
  /* Delete the arguments from the calling function stack */
  addl	$8, %esp
  /* Return 0 by writing 0 to eax - Value retained in eax */
  movl	$0, %eax

  /* The next two lines are postamble / epilogue i.e. '}' in C Source */
  /* leave internally performs the following two steps */
  /* 1. Cleanup of local variables by writing esp with same value as ebp */
  /* 2. Update the previous ebp value (saved in 1st step) in ebp register */
  leave
  	-movl %ebp, %esp 
   	-popl %ebp 
  /* Return to caller function by updating eip from stack into eip register*/
  ret

