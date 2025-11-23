	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 26, 0	sdk_version 26, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	str	xzr, [sp]
Lloh0:
	adrp	x19, l_.str@PAGE
Lloh1:
	add	x19, x19, l_.str@PAGEOFF
	mov	x0, x19
	bl	_printf
	mov	w8, #1                          ; =0x1
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w8, #2                          ; =0x2
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w8, #3                          ; =0x3
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w8, #4                          ; =0x4
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w8, #5                          ; =0x5
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w8, #6                          ; =0x6
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w8, #7                          ; =0x7
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w8, #8                          ; =0x8
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w8, #9                          ; =0x9
	str	x8, [sp]
	mov	x0, x19
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"%d\n"

.subsections_via_symbols
