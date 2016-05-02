TITLE Simple Addition     (ch5num3.asm)

; Program Description: This program prompts for two integers, in
;		the middle of the screen, then displays the sum.
; Author: Cody Kaiser
; Date Created: 10/16/03
; Last Modification Date: 10/17/03

INCLUDE Irvine32.inc

.DATA

prompt1 BYTE "Enter the first integer: ", 0	;declare prompts
prompt2 BYTE "Enter the second integer: ", 0
sum BYTE "The sum of the integers is: ", 0

.CODE

main PROC

	mov dl, 20		;set x and y values
	mov dh, 10

	call Clrscr		;clear screen
	call Gotoxy		;place cursor
	mov edx, OFFSET prompt1	;output prompt 1
	call WriteString
	call ReadInt		;input integer 1

	mov ebx, eax		;save integer 1
	mov dl, 19		;reset x and y
	mov dh, 11

	call Gotoxy		;place cursor
	mov edx, OFFSET prompt2 ;output prompt 2
	call WriteString	
	call ReadInt		;intput integer 2

	add eax, ebx		;add integers
	mov dl, 17		;reset x and y
	mov dh, 12

	call Gotoxy		;place cursor
	mov edx, OFFSET sum	;output sum statement and sum
	call WriteString
	call WriteInt
	call Crlf

	exit				; exit to operating system

main ENDP
END main
