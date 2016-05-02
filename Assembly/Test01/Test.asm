TITLE Test     (Test.asm)

; Program Description:
; Author:
; Date Created:
; Last Modification Date:

INCLUDE Irvine32.inc


.data


.code
main PROC

	call ReadInt			;Get integer value from user(To EAX)
	call Crlf
	cmp eax,0
	ja POSI				;if input is Zero then we are done
	jb NEGA
	jmp DONE

NEGA:
	mov ebx,eax
	neg ebx
	sub ebx,1
MOO:
	imul ebx
	mov ecx,eax
	sub ebx,1
	cmp ebx,0
	je DONE
	jmp MOO


POSI:
	mov ebx,eax
	sub ebx,1
BAA:
	imul ebx
	mov ecx,eax
	sub ebx,1
	cmp ebx,0
	je DONE
	jmp BAA


DONE:	
	mov eax,ecx
	call WriteInt			;Write integer value from EAX
	exit	
main ENDP
END main