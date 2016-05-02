TITLE Months of the Year(lp1b.asm)
INCLUDE Irvine32.inc

   Month00 TEXTEQU <"January">
   Month01 TEXTEQU <"February">
   Month02 TEXTEQU <"March">
   Month03 TEXTEQU <"April">
   Month04 TEXTEQU <"May">
   Month05 TEXTEQU <"June">
   Month06 TEXTEQU <"July">
   Month07 TEXTEQU <"August">
   Month08 TEXTEQU <"September">
   Month09 TEXTEQU <"October">
   Month10 TEXTEQU <"November">
   Month11 TEXTEQU <"December">
   
.data
   M00 BYTE Month00,0
   M01 BYTE Month01,0
   M02 BYTE Month02,0
   M03 BYTE Month03,0
   M04 BYTE Month04,0
   M05 BYTE Month05,0
   M06 BYTE Month06,0
   M07 BYTE Month07,0
   M08 BYTE Month08,0
   M09 BYTE Month09,0
   M10 BYTE Month10,0
   M11 BYTE Month11,0

.code
main PROC

   mov edx, OFFSET M00
   call WriteString
   call Crlf

   mov edx, OFFSET M01
   call WriteString
   call Crlf

   mov edx, OFFSET M02
   call WriteString
   call Crlf

   mov edx, OFFSET M03
   call WriteString
   call Crlf

   mov edx, OFFSET M04
   call WriteString
   call Crlf

   mov edx, OFFSET M05
   call WriteString
   call Crlf

   mov edx, OFFSET M06
   call WriteString
   call Crlf

   mov edx, OFFSET M07
   call WriteString
   call Crlf

   mov edx, OFFSET M08
   call WriteString
   call Crlf

   mov edx, OFFSET M09
   call WriteString
   call Crlf

   mov edx, OFFSET M10
   call WriteString
   call Crlf

   mov edx, OFFSET M11
   call WriteString
   call Crlf

  exit
main ENDP
END main