#include <stdio.h>
#include "Bytecode.h"
#include "IORLW.h"
#include "CException.h"

/**
*	
*	Function Name 	: iorlw
*	Input			: Bytecode
*	Output			: code.absoluteAddress
*	Destroy			: FSR[WREG]
*	
*	Description		: This fuction will do IOR operation for literal and WorkingRegister(WREG)
*
*
*
**/
int iorlw(Bytecode *code){
	
	int valueForCheck;
	if(code->operand3 == -1){
		if(code->operand2 == -1){
			if(code->operand1 >= 0x0 && code->operand1 <=0xff){
				
				valueForCheck  = FSR[WREG] | code->operand1;
				FSR[WREG] = FSR[WREG] | code->operand1;
				updateFlag(valueForCheck);
			}
			else
				Throw(INVALID_OP1);
		}
		else
			Throw(INVALID_OP2);
	}
	else
		Throw(INVALID_OP3);
		
	code->absoluteAddress++;
	return code->absoluteAddress;
}

void updateFlag (int value){
	
	FSR[STATUS] = 0;
	int valueCheck = value;
	//int valueNegative;
	
	//valueNegative = (valueCheck&0x80)>>7;
	
	if(valueCheck == 0)
	FSR[STATUS] = FSR[STATUS] | 0x04;
	
	if((valueCheck&0x80)>>7 == 1)
	FSR[STATUS] = FSR[STATUS] | 0x10;
	
}