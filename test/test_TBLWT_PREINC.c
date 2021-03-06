#include "unity.h"
#include "Bytecode.h"
#include "TBLWT_PREINC.h"
#include "CException.h"


void setUp(void){}
void tearDown(void){}

void test_tblwt_preinc_should_write_value_into_table_with_pre_increment(void){
		
	Instruction instruction = {
								.mnemonic = TBLWT_PREINC,
								.name = "tblwt_preinc"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = -1,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x300
					 };
	int Exception;
	int absoluteCheck;
	
	//fixture to write
	FSR[TABLAT] = 0x50;
	
	//initialize pointer
	FSR[TBLPTRU] = 0x1f;
	FSR[TBLPTRH] = 0xff;
	FSR[TBLPTRL] = 0xfe;
	
	absoluteCheck = tblwt_preinc(&code);
	TEST_ASSERT_EQUAL(0x50,TABLE[0x1fffff]);
	TEST_ASSERT_EQUAL_HEX16(0x301,absoluteCheck);

	//second value
	FSR[TABLAT] = 0xa5;	
	
	absoluteCheck = tblwt_preinc(&code);
	TEST_ASSERT_EQUAL(0xa5,TABLE[0x200000]);
	TEST_ASSERT_EQUAL_HEX16(0x302,absoluteCheck);

	
	//3rd set of value should throw error out of table
	FSR[TABLAT] = 0xff;
	
	Try{
	absoluteCheck = tblwt_preinc(&code);
	TEST_ASSERT_EQUAL_HEX16(0x302,absoluteCheck);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(OUT_OF_TABLE,Exception);
	}
	

	//TEST_ASSERT_EQUAL(0xff,FSR[TABLAT]);
	//TEST_ASSERT_EQUAL_HEX16(0x303,PC);

	
}
