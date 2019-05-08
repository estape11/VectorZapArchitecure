//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 06/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************

#include <ControlUnit.hpp>

void ControlUnit::Input(bit *pInput){
	apInput = pInput;

}

bit *ControlUnit::Output(void){
	return apOutput;

}

bit *ControlUnit::FetchControl(void){
	return apFetchControl;

}

bit *ControlUnit::DecodeControl(void){
	return apDecodeControl;

}

bit *ControlUnit::FetchDecodeEn(void){
	return apFetchDecodeEn;

}

bit *ControlUnit::DecodeExecuteEn(void){
	return apDecodeExecuteEn;

}

bit *ControlUnit::ExecuteMemoryEn(void){
	return apExecuteMemoryEn;

}

bit *ControlUnit::MemoryWriteBackEn(void){
	return apMemoryWriteBackEn;

}

void ControlUnit::Initialize(void){
	// Modify every time is a signal added
	apOutput = (bit *) malloc(sizeof(bit)*10);

	apFetchControl = (bit *) malloc(sizeof(bit)*1);
	*apFetchControl = 1;
	apDecodeControl = (bit *) malloc(sizeof(bit)*2); // For vector/scalar
	memset(apDecodeControl, 0, 2);
	apFetchDecodeEn = (bit *) malloc(sizeof(bit));
	apDecodeExecuteEn = (bit *) malloc(sizeof(bit));
	apExecuteMemoryEn = (bit *) malloc(sizeof(bit));
	apMemoryWriteBackEn = (bit *) malloc(sizeof(bit));

	// Sets the pipe-registers enable
	*apFetchDecodeEn = 1;
	*apDecodeExecuteEn = 1;
	*apExecuteMemoryEn = 1;
	*apMemoryWriteBackEn = 1;	

}

void ControlUnit::Run(void){
	aRun = true;
	while (aRun) {
		// Mode
		if (apInput[1] == 0 && apInput[0] == 0) { // NOP
			if(apInput[3] == 1 && apInput[2] == 1) { // Halt
				// Stops the pipeline				
				*apFetchControl = 0;
				*apFetchDecodeEn = 0;
				*apDecodeExecuteEn = 0;
				*apExecuteMemoryEn = 0;
				*apMemoryWriteBackEn = 0;

			} else { // NOP
				memset(apOutput, 0, 10);
				*apDecodeControl = 0;
				
			}

		} else if (apInput[1] == 0 && apInput[0] == 1) { // Scalar - Scalar
			if(apInput[3] == 0 && apInput[2] == 0) { // Type A
				memcpy(apOutput, apInput+5, 4); // Alu Sel
				apOutput[4] = 1; // Scalar Reg Write
				*apDecodeControl = 1;

			}

		} else if (apInput[1] == 1 && apInput[0] == 0) { // Vector - Vector
			memset(apOutput, 0, 10);
			*apDecodeControl = 0;

		} else if (apInput[1] == 1 && apInput[0] == 1) { // Vector - Scalar
			memset(apOutput, 0, 10);
			*apDecodeControl = 0;

		} else {
			memset(apOutput, 0, 10);
			*apDecodeControl = 0;
			printf("Error: Unknown mode\n");

		}

	}

}

void ControlUnit::RunMutex(void){
	// Mode
	if (apInput[1] == 0 && apInput[0] == 0) { // NOP
		if(apInput[3] == 1 && apInput[2] == 1) { // Halt
			// Stops the pipeline				
			*apFetchControl = 0;
			*apFetchDecodeEn = 0;
			*apDecodeExecuteEn = 0;
			*apExecuteMemoryEn = 0;
			*apMemoryWriteBackEn = 0;

		} else { // NOP
			memset(apOutput, 0, 10);
			*apDecodeControl = 0;
			
		}

	} else if (apInput[1] == 0 && apInput[0] == 1) { // Scalar - Scalar
		if(apInput[3] == 0 && apInput[2] == 0) { // Type A
			memcpy(apOutput, apInput+5, 4); // Alu Sel
			apOutput[4] = 1; // Scalar Reg Write
			*apDecodeControl = 1;

		}

	} else if (apInput[1] == 1 && apInput[0] == 0) { // Vector - Vector
		memset(apOutput, 0, 10);
		*apDecodeControl = 0;

	} else if (apInput[1] == 1 && apInput[0] == 1) { // Vector - Scalar
		memset(apOutput, 0, 10);
		*apDecodeControl = 0;

	} else {
		memset(apOutput, 0, 10);
		*apDecodeControl = 0;
		printf("Error: Unknown mode\n");

	}

}