TITLE Flag (LP3.asm)
INCLUDE Irvine16.inc

mScroll MACRO lines, attribute, uplf_col, uplf_row, lort_col, lort_row
	mov ah, 6
	mov al, lines

	IFNB<attribute>
		mov bh, attribute
	ELSE
		mov bh, 7
	ENDIF

	mov ch, uplf_row
	mov cl, uplf_col
	mov dh, lort_row
	mov dl, lort_col
	int 10h
ENDM

.code
main PROC
	mov ax, @data
	mov ds, ax

	call Clrscr
	mScroll 0, 32, 0, 0, 20, 20
	mov dh, 0
	mov dl, 20
	call Gotoxy

exit
main ENDP
END main