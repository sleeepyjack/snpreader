/*
 * SNP.h
 *
 *  Created on: 16/12/2014
 *      Author: jorge
 *
 *	Refactored on: Oct 19, 2016
 *			Author: djuenger
 */

#ifndef SNP_H_
#define SNP_H_

#include "Macros.h"

// Structure to store all the information of one SNP
struct SNP
{
	SNP(){
		_case0Values = NULL;
		_ctrl0Values = NULL;
		_case1Values = NULL;
		_ctrl1Values = NULL;
		_case2Values = NULL;
		_ctrl2Values = NULL;
		_name = new uint8_t[SNP_MAX_NAME_SIZE];
		_nameLength = 0;
	}

	~SNP(){
		if (_name){
			delete[] _name;
		}

		if(_case0Values){
			delete[] _case0Values;
		}

		if(_case1Values){
			delete[] _case1Values;
		}

		if(_case2Values){
			delete[] _case2Values;
		}

		if(_ctrl0Values){
			delete[] _ctrl0Values;
		}

		if(_ctrl1Values){
			delete[] _ctrl0Values;
		}

		if(_ctrl2Values){
			delete[] _ctrl2Values;
		}
	}

	void setName(uint8_t* name){
			if ((_nameLength = strlen((char*) name)) > SNP_MAX_NAME_SIZE) {
			printf("Name too long in function %s line %d\n",
						__FUNCTION__, __LINE__);
			fflush(stdout);
			exit(1);
		}
		else{
			strcpy((char*) _name, (char*) name);
		}
	}

	// Be careful because the size is length/32
	void setCaseValues(uint32_t* case0Values, uint32_t* case1Values, uint32_t* case2Values, size_t size){
		if(_case0Values){
			delete[] _case0Values;
		}

		if(_case1Values){
			delete[] _case1Values;
		}

		if(_case2Values){
			delete[] _case2Values;
		}

		_case0Values = new uint32_t[size];
		memcpy(_case0Values, case0Values, size*sizeof(uint32_t));

		_case1Values = new uint32_t[size];
		memcpy(_case1Values, case1Values, size*sizeof(uint32_t));

		_case2Values = new uint32_t[size];
		memcpy(_case2Values, case2Values, size*sizeof(uint32_t));
	}

	// Be careful because the size is length/32
	void setCtrlValues(uint32_t* ctrl0Values, uint32_t* ctrl1Values, uint32_t* ctrl2Values, size_t size){
		if(_ctrl0Values){
			delete[] _ctrl0Values;
		}

		_ctrl0Values = new uint32_t[size];
		memcpy(_ctrl0Values, ctrl0Values, size*sizeof(uint32_t));

		if(_ctrl1Values){
			delete[] _ctrl1Values;
		}

		_ctrl1Values = new uint32_t[size];
		memcpy(_ctrl1Values, ctrl1Values, size*sizeof(uint32_t));

		if(_ctrl2Values){
			delete[] _ctrl2Values;
		}

		_ctrl2Values = new uint32_t[size];
		memcpy(_ctrl2Values, ctrl2Values, size*sizeof(uint32_t));
	}

	// SIZE represents the number of uint8 -> The length is larger!!!
	uint8_t* _name;
	uint16_t _nameLength;

	// Each position keeps 32 binary values (each binary value for one individual)
	// They are separated to calculate the two parts of the contingency table
	uint32_t *_case0Values;
	uint32_t *_case1Values;
	uint32_t *_case2Values;
	uint32_t *_ctrl0Values;
	uint32_t *_ctrl1Values;
	uint32_t *_ctrl2Values;
};



#endif /* SNP_H_ */
