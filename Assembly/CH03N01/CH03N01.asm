TITLE AddSub (CH03N01.asm)
;Program Description:  This program subtracts 3 integers.
;
;Author: Alberto Martinez
;Date Created: 10.09.03
;Last Modification Date: 10.09.03
INCLUDE Irvine16.inc

.CODE
main PROC

  mov ax,@data
  mov ds,ax

  mov ax,8h		; AX = 8h
  sub ax,5h		; AX = 3h
  sub ax,1h		; AX = 2h

  call DumpRegs

exit

main ENDP
END main