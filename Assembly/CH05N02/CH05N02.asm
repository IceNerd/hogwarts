TITLE Integer Array Input     (CH05N02.asm)

; Program Description: This program inputs 10 integers, stores them
;		in an array, then outputs the array.
; Author: Cody Kaiser
; Date Created: 10/16/03
; Last Modification Date: 10/17/03

INCLUDE Irvine32.inc

.DATA

prompt BYTE "Please Input 10 Integers:", 0	       ;declare strings
display BYTE "Here are the values you just entered:", 0

.DATA?

intArray SDWORD 10 DUP(?)		;create integer array

.CODE

main PROC

	mov eax, 0			;initialize working regs to 0
	mov esi, 0
	mov ecx, 10

	mov edx, OFFSET prompt		;output integer prompt
	call WriteString
	call Crlf

	getInt:				;intput loop
		call ReadInt		;input integer
		mov intArray[esi], eax	;store in current element
		add esi, 4		;increment array offset
		loop getInt		;end intput loop

	mov ecx, 10			;reset loop counter
	mov esi, 0			;reset array offset

	mov edx, OFFSET display		;output display string
	call WriteString
	call Crlf

	displayInt:			;output loop
		mov eax, intArray[esi]	;output current element
		call WriteInt
		add esi, 4		;increment array offset
		call Crlf
		loop displayInt		;end output loop

	exit				; exit to operating system

main ENDP
END main
