TITLE Fibonacci Numbers (FibNums.asm)
;Program Description:  This program displays the
;	first 7 parts of the fibonacci number pattern.
;
;Author: Alberto Martinez
;Date Created: 10.09.03
;Last Modification Date: 10.09.03

INCLUDE Irvine16.inc

.code
main PROC

	mov ax, @data
	mov ds, ax

	mov ax, 1h	;initialize registers
	mov bx, 0h
	mov dx, 1h
	mov cx, 7h

MOO:
	call DumpRegs	;Display
	add ax, bx
	mov bx, dx
	mov dx, ax
loop MOO

exit

main ENDP
END main


