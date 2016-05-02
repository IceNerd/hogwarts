TITLE Boolean Calculator (CH06N08.asm)

;Program Description:  This program will do boolean algebra to integers
;
;Author: Alberto Martinez
;Date Created:   10.26.03
;Last Modification Date:   10.26.03

INCLUDE Irvine32.inc

.DATA
StartMSG BYTE "Boolean Calculator",0

CaseTable  BYTE   '1'
           DWORD   CMD_AND
           BYTE   '2'
           DWORD   CMD_OR
           BYTE   '3'
           DWORD   CMD_NOT
           BYTE   '4'
           DWORD   CMD_XOR
NumberOfEntries=4

Menu01 BYTE "1:   x AND y",0
Menu02 BYTE "2:   x OR y",0
Menu03 BYTE "3:   NOT x",0
Menu04 BYTE "4:   x XOR y",0
Menu05 BYTE "5:   Exit Program",0

.CODE
main PROC
MENU:
	call Write_Menu
	
	mov ebx,OFFSET CaseTable
	mov ecx,NumberOfEntries
L1:
	cmp al,5
	je L3
	cmp al,[ebx]
	jne L2
	call NEAR PTR [ebx + 1]
	jmp MENU
L2:
	add ebx,5
	loop L1

L3:	call clrscr
exit
main ENDP



;-----------------------------------------------
Write_Menu PROC
;
; Reads:
; Receives: nothing
; Returns:
;-----------------------------------------------
	call clrscr
	mov edx, OFFSET StartMSG
	call WriteString
	call Crlf
	mov edx, OFFSET Menu01
	call WriteString
	call Crlf
	mov edx, OFFSET Menu02
	call WriteString
	call Crlf	 
	mov edx, OFFSET Menu03
	call WriteString
	call Crlf	
	mov edx, OFFSET Menu04
	call WriteString
	call Crlf	
	mov edx, OFFSET Menu05
	call WriteString
	call Crlf
	call ReadCHAR	
ret
Write_Menu ENDP



;-----------------------------------------------
CMD_AND PROC
;
; Reads:
; Receives: nothing
; Returns:
;-----------------------------------------------
	call clrscr
	mov edx, OFFSET Menu01
	call WriteString
	call crlf
	call ReadINT
	mov EBX, EAX
	call ReadINT
	AND EAX, EBX
	call WriteINT
	call ReadCHAR
ret
CMD_AND ENDP



;-----------------------------------------------
CMD_OR PROC
;
; Reads:
; Receives: nothing
; Returns:
;-----------------------------------------------
	call clrscr
	mov edx, OFFSET Menu02
	call WriteString
	call crlf
	call ReadINT
	mov EBX, EAX
	call ReadINT
	OR EAX, EBX
	call WriteINT
	call ReadCHAR 
ret
CMD_OR ENDP



;-----------------------------------------------
CMD_NOT PROC
;
; Reads:
; Receives: nothing
; Returns:
;-----------------------------------------------
	call clrscr
	mov edx, OFFSET Menu03
	call WriteString
	call crlf
	call ReadINT
	NOT EAX
	call WriteINT
	call ReadCHAR 
ret
CMD_NOT ENDP



;-----------------------------------------------
CMD_XOR PROC
;
; Reads:
; Receives: nothing
; Returns:
;-----------------------------------------------
	call clrscr
	mov edx, OFFSET Menu04
	call WriteString
	call crlf
	call ReadINT
	mov EBX, EAX
	call ReadINT
	XOR EAX, EBX
	call WriteINT
	call ReadCHAR 
ret
CMD_XOR ENDP

END main