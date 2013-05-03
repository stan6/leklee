	.file	"hello.bc"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:                                 # %bb.nph
	pushl	%esi
	subl	$8, %esp
	movl	$5, %esi
	.align	16, 0x90
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	movl	$str, (%esp)
	call	puts
	decl	%esi
	jne	.LBB1_1
# BB#2:                                 # %._crit_edge
	xorl	%eax, %eax
	addl	$8, %esp
	popl	%esi
	ret
	.size	main, .-main

	.type	str,@object
	.section	.rodata.str1.1,"aMS",@progbits,1
str:                                    # @str
	.asciz	 "hello world"
	.size	str, 12


	.section	.note.GNU-stack,"",@progbits
