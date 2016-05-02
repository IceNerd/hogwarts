TITLE Array (HW01N05.asm)
;Program Description:  This program is a demonstration
;	of direct-offset addressing.
;
;Author: Alberto Martinez
;Date Created: 10.09.03

;Last Modification Date: 10.09.03
INCLUDE Irvine16.inc

.DATA

Uarray	WORD	1000h, 2000h, 3000h, 4000h
Sarray	SWORD	-1, -2, -3, -4

.code

main PROC

  mov ax, @data
  mov ds, ax

  mov ax, [Uarray]		;Start of Array into mem
  mov bx, [Uarray + 2]		;Direct-Offset to get other parts
  mov cx, [Uarray + 4]
  mov dx, [Uarray + 6]

  call DumpRegs			;Display

  mov ax, [Sarray]		;Start of Array
  mov bx, [Sarray + 2]		;Direct-Offset to get other parts
  mov cx, [Sarray + 4]
  mov dx, [Sarray + 6]

  call DumpRegs			;Display

  exit

main ENDP
END main

