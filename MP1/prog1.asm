	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop










; The following code prints the final histogram in hexadecimal to the monitor.
; Using several loops, the code gets the number of times every letter appears,
; break them into group of four bits, convert them into a hexadecimal digit,
; calculates the corresponding ASCII character,
; and print them to the monitor.


PRINT_HIST

;R0 as temporary digit magnitude checker
;R1 as print counter
;R2 stores the ASCII value for next letter to print
;R3 stores the address of the number to be printed
;R4 stores the number to be printed
;R5 as digit counter
;R6 as bit counter
;R7 stores the actual digit magnitude


; initialization for printing
	LD R1,NUM_BINS		; set print counter to 27
	LD R2,THE_AT		; set R2 to the ASCII value of '@'
	LD R3,HIST_ADDR		; set R3 to histogram starting address

COUNT_PRINT_LOOP
	ADD R1,R1,#0		; if the print counter is 0,
	BRz DONE			; end the program

	ADD R0,R2,#0		; print the letter at the start of this line
	OUT
	LD R0,SPACE			; print a space after the letter
	OUT

; print the number in hexadecimal
	
	LDR R4,R3,#0		; load the number to be printed into R4
	LD R5,NUM_DIGITS	; set digit counter to 4

DIGIT_LOOP_COUNT
	ADD R5,R5,#0		; if digit counter is 0,
	BRz GET_NEXT_PRINT	; go to print the next number on next line
	
	LD R6,NUM_DIGITS	; set bit counter to 4
	AND R7,R7,#0		; empty R7 for later use

BIT_LOOP_COUNT
	ADD R6,R6,#0		; if bit counter is 0,
	BRz PRINT_DIGIT		; go to print next digit

	ADD R7,R7,R7		; shift R7 left
	ADD R4,R4,#0		; if R4 is positive or zero,
	BRzp #1				; skip next step

	ADD R7,R7,#1		; sdd 1 to digit R7	
	ADD R4,R4,R4		; shift R4 left
	ADD R6,R6,#-1		; decrement bit counter
	BRnzp BIT_LOOP_COUNT
	

PRINT_DIGIT
	ADD R0,R7,#-9		; get R7-9
	BRnz #2				; if it is not positive (digit<=9),skip next 2 steps
	LD R0,A_MINUS_TEN	; add 'A'-10 to R0
	BRnzp #1			
	LD R0,ZERO			; add '0' to R0
	ADD R0,R7,R0		; print the letter with ASCII value R0+R7
	OUT
	ADD R5,R5,#-1		; decrement digit counter
	BRnzp DIGIT_LOOP_COUNT

GET_NEXT_PRINT
	LD R0,C_RETURN		; print a new line character
	OUT
	ADD R1,R1,#-1		; decrement print counter
	ADD R2,R2,#1		; increment the ASCII value for next letter to print
	ADD R3,R3,#1		; increment the address of the number to be printed
	BRnzp COUNT_PRINT_LOOP
	
DONE	HALT			; done, halt the program





; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address


; the data added by me
C_RETURN    .FILL x000A ; the ASCII value of the new line character
SPACE       .FILL x0020 ; the ASCII value of space
THE_AT		.FILL x0040 ; the ASCII value of '@'
NUM_DIGITS	.FILL #4	; 4 lopp iterations
A_MINUS_TEN	.FILL #55	; the ASCII value of 'A'-10
ZERO		.FILL #48	; the ASCII value of '0'












; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
