TITLE Fast Multiply                (CH07N05.asm)

;Program Description:  This program will multiply two integers
;	using shifts and adds only.
;
;Author: Alberto Martinez
;Date Created:   10.26.03
;Last Modification Date:   10.26.03

INCLUDE Irvine32.inc

.data
StartMSG BYTE "This program will multiply two positive integers.",0
.code
main PROC
	mov edx, OFFSET StartMSG
	call WriteString
	Call CRLF

	call ReadINT
	mov ebx,eax
	call CRLF
	Call ReadINT
	call CRLF
	mov cl,0
	mov edx,0
	push ebx
	push 0

L1:	shr eax,1
	jnc L2

	shl ebx,cl
	pop edx
	add edx,ebx
	pop ebx
	push ebx
	push edx
	

L2:	inc cl
	cmp cl,32
	jne L1

	pop eax
	pop ebx
	call WriteINT
	call Crlf
	exit
main ENDP
END main