/* Source Translation into Assembly for Multiple Functions - Call by Reference */
#include <stdio.h>

void swap(int *a, int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}


int main()
{
  int a = 10,b= 20;
  swap(&a,&b);
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
  subl    $4, %esp
  /* Copy first argument pointer in eax */
  movl	8(%ebp), %eax
  /* Dereference the pointer in eax and save the value back in eax *
  movl	(%eax), %eax
  /* Save this value in stack */
  movl	%eax, -4(%ebp)
  /* Copy second argument pointer in eax */	
  movl	12(%ebp), %eax
  /* Dereference the pointer in eax and save the value in edx */  
  movl	(%eax), %edx
  /* Copy first argument pointer in eax */
  movl	8(%ebp), %eax
  /* Copy eax content or second argument directly in first address */  
  movl	%edx, (%eax)
  /* Copy second argument pointer in eax */	
  movl	12(%ebp), %eax
  /* Copy the saved first argument from stack and bring to edx */	
  movl	-4(%ebp), %edx
  /* Copy the edx value i.e first argument directly in second argument address */
  movl	%edx, (%eax)
  
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
  subl    $8, %esp
  /* Save 10 in [ebp-offset(8)] - Variable 'a' */
  movl	$10, -8(%ebp)
  /* Save 20 in [ebp-offset(4)] - Variable 'b' */        
  movl    $20, -4(%ebp)
  /* Save address of the second argument (pointer) in eax */        
  leal	-4(%ebp), %eax
  /* Save this argument pointer in stack */        
  pushl	%eax
  /* Save address of the first argument (pointer) in eax */	
  leal	-8(%ebp), %eax
  /* Save this argument pointer in stack */        
  pushl   %eax
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
#endif

