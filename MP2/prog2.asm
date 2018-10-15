;This program is a stack calculator.
;It reads values from the keyboard, if it's an operand, push it onto the stack,
;If it's an operator, pop 2 values from the stack, apply the operator
;and push the result back on the stack
;The program will stop when an equal sign is reached.
;If the input is invalid, an error message will be displayed


.ORIG x3000		

GET_INPUT			IN						;get the input value

					JSR EVALUATE			;evaluate the value and react differently
	
LOAD_RESULT			AND R5, R5, #0
					ADD R5, R5, R0			;duplicate the result in R0 to R5

PRINT_RESULT		JSR PRINT_HEX			;print the final result in hex

STOP				HALT					



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	LD R0, ASCII_X		; print the x before the hex number
	OUT
	
	AND R3, R3, #0		; 
	ADD R3, R3, R5		; load the number to be printed into R3
	LD R1,NUM_DIGITS	; set digit counter R1 to 4

DIGIT_LOOP_COUNT
	ADD R1,R1,#0		; if digit counter is 0,
	BRz STOP			; finish printing
	
	LD R2,NUM_DIGITS	; set bit counter R2 to 4
	AND R6,R6,#0		; empty R6 for later use

BIT_LOOP_COUNT
	ADD R2,R2,#0		; if bit counter is 0,
	BRz PRINT_DIGIT		; go to print next digit

	ADD R6,R6,R6		; shift R6 left
	ADD R3,R3,#0		; if R3 is positive or zero,
	BRzp #1				; skip next step

	ADD R6,R6,#1		; add 1 to digit R6	
	ADD R3,R3,R3		; shift R3 left
	ADD R2,R2,#-1		; decrement bit counter
	BRnzp BIT_LOOP_COUNT
	
PRINT_DIGIT
	ADD R0,R6,#-9		; get R6-9
	BRnz #2				; if it is not positive (digit<=9),skip next 2 steps
	LD R0,A_MINUS_TEN	; add 'A'-10 to R0
	BRnzp #1			
	LD R0,ZERO			; add '0' to R0
	ADD R0,R6,R0		; print the letter with ASCII value R0+R6
	OUT
	ADD R1,R1,#-1		; decrement digit counter
	BRnzp DIGIT_LOOP_COUNT




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

	AND R3, R3, #0				;empty R2, R3, R4 for future use
	AND R4, R4, #0
	AND R2, R2, #0

CHECK_EQUAL
	LD R6, ASCII_EQUAL			;load the negative of ASCII value to R6
	ADD R2, R0, R6				;subtract R2 with ASCII value with the checked character
	BRnp CHECK_SPACE			;if the result is not 0, do the next check
	JSR POP						
	LD R3, STACK_TOP
	LD R4, STACK_START
	NOT R4, R4			
	ADD R4, R4, #1
	ADD R3, R3, R4				;check if the stack is empty now
	BRnp INVALID				;if there's not only one value is stack, invalid
	BRnzp LOAD_RESULT			

CHECK_SPACE
	LD R6, ASCII_SPACE			
	ADD R2, R0, R6		
	BRz GET_INPUT				;if it is space, get a new input

CHECK_NUMBER
	LD R6, ASCII_0				
	ADD R2, R0, R6
	BRn CHECK_PLUS
	LD R6, ASCII_9
	ADD R2, R0, R6
	BRp CHECK_PLUS
	LD R6, ASCII_0 				;if the value is between 0 and 9,
	ADD R0, R0, R6
	JSR PUSH					;push it to the stack
	BRnzp GET_INPUT

CHECK_PLUS
	LD R6, ASCII_PLUS
	ADD R2, R0, R6
	BRnp #11					;if it's not plus sign, ignore all steps below
	JSR POP						;POP first time,
	ADD R5, R5, #0
	BRp INVALID					;and check underflow
	ADD R4, R4, R0
	JSR POP						;second pop and second underflow check
	ADD R5, R5, #0
	BRp INVALID
	ADD R3, R3, R0
	JSR PLUS					;if it's valid, perform the plus step
	JSR PUSH
	BRnzp GET_INPUT

CHECK_MIN
	LD R6, ASCII_MIN			;similar to CHECK_PLUS
	ADD R2, R0, R6
	BRnp #11
	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R4, R4, R0
	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R3, R3, R0
	JSR MIN
	JSR PUSH
	BRnzp GET_INPUT

CHECK_MUL
	LD R6, ASCII_MUL			;similar to CHECK_PLUS
	ADD R2, R0, R6
	BRnp #11
	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R4, R4, R0
	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R3, R3, R0
	JSR MUL
	JSR PUSH
	BRnzp GET_INPUT

CHECK_DIV
	LD R6, ASCII_DIV			;similar to CHECK_PLUS
	ADD R2, R0, R6
	BRnp #11
	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R4, R4, R0
	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R3, R3, R0
	JSR DIV
	JSR PUSH
	BRnzp GET_INPUT

CHECK_EXP
	LD R6, ASCII_EXP			;similar to CHECK_PLUS
	ADD R2, R0, R6
	BRnp #11
	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R4, R4, R0
	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R3, R3, R0
	JSR EXP
EXP_RETURN	JSR PUSH
	BRnzp GET_INPUT


INVALID			LEA R0, INVALID_INPUT
				PUTS
				BRnzp STOP

EXIT_EVA		RET







;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
	ADD R0, R3, R4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	NOT R4, R4
	ADD R4, R4, #1
	ADD R0, R3, R4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
	AND R0, R0, #0
	AND R5, R5, #0
	ADD R5, R5, R4				;Move value in R4 to R5 to make sure R4 stays unchanged
	BRz	#3
	ADD R0, R0, R3
	ADD R5, R5, #-1
	BRnzp #-4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
	AND R0, R0, #0
	NOT R1, R4
	ADD R1, R1, #1
	ADD R3, R3, R1				;R3 = R3 - R1
	BRn #2						;Exit the division if R3 becomes negative
	ADD R0, R0, #1
	BRnzp #-4
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	AND R0, R0, #0			
	ADD R0, R0, #1			;Set initial value of R0 to 1
	AND R1, R1, #0			
	ADD R1, R1, R4			;Move exponent value in R4 to R1
	BRz EXIT_EXP
	AND R4, R4, #0
	ADD R4, R4, R3			;Move base value R3 to R4
	AND R3, R3, #0
	ADD R3, R3, R0	
	JSR MUL					;R0 = R3 * R4
	AND R3, R3, #0
	ADD R3, R3, R0			;Duplicate value in R0 to R3
	ADD R1, R1, #-1
	BRz EXIT_EXP			;If exponent counter counts to 0, exit EXP
	BRnzp #-6				;Go back to multiply steps			
EXIT_EXP	BRnzp EXP_RETURN
	






;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3			;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

ASCII_PLUS	.FILL #-43
ASCII_MIN	.FILL #-45
ASCII_MUL	.FILL #-42
ASCII_DIV	.FILL #-47
ASCII_EXP	.FILL #-94
ASCII_EQUAL	.FILL #-61
ASCII_0		.FILL #-48
ASCII_9		.FILL #-57
ASCII_SPACE	.FILL #-32
ASCII_X		.FILL #120

NUM_DIGITS	.FILL #4	; 4 loop iterations
A_MINUS_TEN	.FILL #55	; the ASCII value of 'A'-10
ZERO		.FILL #48	; the ASCII value of '0'


INVALID_INPUT	.STRINGZ "Invalid input."


.END
