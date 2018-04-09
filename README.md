# Learning C
I've decided to become a C developer, because C most fits the needs I have for programs I'd like to write.

## Maxims

1. C is not C++
1. C++ is not C
2. C gives developers the greatest amount of control over the machine at the cost of being more time-consuming to develop software in.
3. C encourages applications suited to highly specific requirements.
4. C avails itself to compiling programs that work on non-standard architectures, such as embedded systems.
5. C sidesteps the problem of imperative vs. functional languages, by forcing the developer to make this decision. Although feels natural to write imperative code in C, functional code can still be written if the developer deems it necessary and puts in the extra work. This is sensible, because computers are not merely language describing actions or math describing functions. A bit is not functional, but imperative. A bit simply is. But it can be described mathematically and functionally when working with combinations of other bits together. Neither mere imperative statements nor mere functional declarations are sufficient to explain everything happening at the machine level., but the whole point of software development is to get something to happen at the machine level. It makes sense, then, that the language will be most powerful which can posit both types of interactions and compile them to work on the machine in either a functional or an imperative way, depending on the needs of the situation. 

 
## Dictums

1. A program is a set of instructions that a computer can follow. The goal of developing software is to write the best possible program(s) for a given (set of) application(s). C is my language of choice because it brings the stringent developer closest to approximating that reality.
2. To the extent that a computer is "ordered around" by software, all programming languages eventually compile to some form of bytecode that the computer can understand.
3. To the extent that a particular programming language utilizes abstractions that allow for shortcuts will any software written in that language inherit the biases and blind-spots of the paradigm(s) of that language.
4. Any high-level language replaces a person's natural interaction with the machine with a set of abstractions that are not chosen by the developer, but by the language(s) author(s).
5. To the extent that machine operations are abstracted away from the developer will the developer inherit the paradigm not of the machine, but of the abstractions that make up the language they code in.
6. This contributes to the problem of dogmatic attitudes among developers that certain languages are bad, and other ones are good (even when there's just as many developers that would switch preferences.)
7. Talking through a high level language is like talking through a translator. The best translator will give you the most latitude and greatest specificity with what you say. C does this.
8. If you only talk through a translator but never learn the native language, you do yourself and your understanding of computers a measurable disservice.

## Purpose

The goal of this repository is for me to learn C and show the world what it can do. Although I've combed through much code over the years, and learned many languages briefly (and usually just for the sake of curiosity,) the only language I've ever wanted to master is C. Maybe it's because of the best-in-class software written in C (Unix, VIm, etc.) Or maybe it's because C doesn't allow me to take shortcuts where I don't have to code as much but the computer uses more resources, but I prefer to be thorough. Sometimes a picture is worth a thousand words, so let's compare a "Hello, World!" program written in C with one written in C++ and see if we can learn something.

### "Hello, World!" in C

```
#include <stdio.h>

int main()
{
    printf("Hello, world!\n");   
}
```

### "Hello, World!" in C++

```
int main() 
{
    std::cout << "Hello, World!";
}
```

At face value, this looks pretty innocuous, doesn't it? C++ seems as though it might make even more sense to code in. But let's see what's happening at the machine level, shall we?

#### Helloworld.c Assembly

```
	.file	"helloworld.c"
	.section	.rodata
.LC0:
	.string	"Hello, world!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
```

#### Helloworld.cpp Assembly

```
	.file	"helloworld.cpp"
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
.LC0:
	.string	"Hello, World!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1493:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1493:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1977:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L5
	cmpl	$65535, -8(%rbp)
	jne	.L5
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
.L5:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1977:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB1978:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1978:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
```

Although this example may be simplistic, it demonstrates how large of a gap there can be between what the compiler is telling a computer, and what the developer thinks the compiler is telling the computer. This factual discrepancy cannot be ignored if you want your bugs to be your own fault (and therefore, fixable by you) rather than someone else's fault (the designers of some particular language.)

All computer programming languages are sets of abstractions that make sense for the developer and can be broken down for the computer. C keeps a tighter set of abstractions than most computer programming languages. This means more control for the diligent developer and less left up to chance by the whims of a language's creator.
