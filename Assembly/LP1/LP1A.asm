TITLE Days of the Week	(problem3.asm)
INCLUDE Irvine32.inc

.data
Day00 EQU "Monday "
Day01 EQU "Tuesday "
Day02 EQU "Wednesday "
Day03 EQU "Thursday "
Day04 EQU "Friday "
Day05 EQU "Saturday "
Day06 EQU "Sunday "

Days BYTE Day00, Day01, Day02, Day03, Day04, Day05, Day06, 0

.code
main PROC

   mov edx, OFFSET Days
   call WriteString
   call Crlf
   exit

main ENDP
END main