TITLE Color Matrix     (ch5num3.asm)

; Program Description: This program displays a single character
; 		in all combinations of foreground and background
;		colors.
; Author: Cody Kaiser
; Date Created: 10/17/03
; Last Modification Date: 10/17/03

INCLUDE Irvine32.inc

.DATA

mover DWORD 16		;variable to multiply background with

.DATA?

count DWORD ?		;variable to store counter

.CODE

main PROC

	mov ecx, 16	;set outer loop counter
	mov ebx, 0	;initialize working regs to 0
	mov eax, 0

foreground:
	mov count, ecx	;save outer loop counter
	mov ecx, 16	;set inner loop counter

background:
		mov esi, eax		;save background color
		mul mover		;set eax as background
		add eax, ebx		;set eax as back/foreground

		call SetTextColor	;set text color and display
		mov al, 01h 
		call WriteChar
		mov eax, esi		;restore eax as background
		inc eax			;increment background color
		loop background		;end background loop

		inc ebx			;increment foreground color
		mov ecx, count		;restore outer loop count
		loop foreground		;end foreground loop

	mov eax,lightGray + (black * 16) ;restore default colors
	call SetTextColor
	call Crlf
	call WaitMsg			;wait for user

	exit				; exit to operating system

main ENDP
END main
