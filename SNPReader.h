/*
 * SNPReader.h
 *
 *  Created on: Dec 16, 2014
 *      Author: gonzales
 */

#ifndef SNPREADER_H_
#define SNPREADER_H_

#include "SNP.h"
#include "MyFile.h"
#include "LineReader.h"

class SNPReader {
public:
	SNPReader(string tpedFileName, string tfamFileName);
	virtual ~SNPReader();

	// Loads all the SNPs in the reader
	void loadSNPSet();

	inline uint32_t getNumSnp(){
		return _numSnp;
	}

	inline uint16_t getNumCases(){
		return _numCases;
	}

	inline uint16_t getNumCtrls(){
		return _numCtrls;
	}

	inline vector<SNP*> getSnpSet(){
		return _snpSet;
	}

private:
	// Load the information of which individuals are control and case from the tfam file
	void _loadIndsClass();
	inline void _resizeBoolArr(size_t nsize){
		if(nsize< _boolArrSize){
			return;
		}

		// Allocate a new buffer
		_boolArrSize = nsize*2;
		bool* nbuffer = new bool[_boolArrSize];
		if (!nbuffer) {
			printf("Memory reallocation failed in file %s in line %d\n",
					__FUNCTION__, __LINE__);
			exit(1);
		}
		// Copy the old data
		memcpy(nbuffer, _indsClass, (_boolArrSize/2)*sizeof(bool));

		// Release the old buffer
		delete[] _indsClass;
		_indsClass = nbuffer;
	}

	string _tpedFileName;
	string _tfamFileName;
	vector<SNP*> _snpSet;
	// File handler
	MyFilePt _fpTfam;
	MyFilePt _fpTped;
	LineReader* _lineReader;

	// Array to keep which values are cases
	// False cases, true controls
	bool* _indsClass;
	size_t _boolArrSize;

	// To store the dimensions of the problem
	uint32_t _numSnp;
	uint16_t _numCases;
	uint16_t _numCtrls;
};

#endif /* SNPREADER_H_ */
