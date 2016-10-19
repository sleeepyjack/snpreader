/*
 * SNPReader.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: gonzales
 */

#include "SNPReader.h"

SNPReader::SNPReader(string tpedFileName, string tfamFileName) {
	_tpedFileName = tpedFileName;
	_tfamFileName = tfamFileName;
	_snpSet.resize(DEFAULT_NUM_SNPS);

	if((_fpTfam = myfopen(_tfamFileName.c_str(), "r")) == NULL){
		printf("TFAM file: file %s could not be opened\n", _tfamFileName.c_str());
		fflush(stdout);
		exit(1);
	}

	if((_fpTped = myfopen(_tpedFileName.c_str(), "r")) == NULL){
		printf("TPED file: file %s could not be opened\n", _tpedFileName.c_str());
		fflush(stdout);
		exit(1);
	}

	_indsClass = new bool[DEFAULT_NUM_INDS];
	_boolArrSize = DEFAULT_NUM_INDS;
	_lineReader = new LineReader();

	_numSnp = 0;
	_numCases = 0;
	_numCtrls = 0;
}

SNPReader::~SNPReader() {

	myfclose(_fpTfam);
	myfclose(_fpTped);
}

void SNPReader::_loadIndsClass(){
	// Load the information from a TFAM file about the cases and controls
	int numInds = 0;
	int retValue;
	_numCases = 0;
	_numCtrls = 0;
	while((retValue = _lineReader->readTFAMLine(_fpTfam, numInds)) >= 0){
		if(numInds >= _boolArrSize){
			_resizeBoolArr(_boolArrSize);
		}
		if(retValue){
			_numCtrls++;
			_indsClass[numInds] = true;
		}
		else{
			_numCases++;
			_indsClass[numInds] = false;
		}
		numInds++;
	}

	printf("Loaded information of %ld individuals (%ld/%ld cases/controls)\n", numInds, _numCases, _numCtrls);
#ifdef DEBUG
	for(int i=0; i<numInds; i++){
		if(_indsClass[i]){
			printf("control ");
		}
		else{
			printf("case ");
		}
	}
	printf("\n");
#endif
}

void SNPReader::loadSNPSet(){

	// Load the information of which individuals are cases and controls
	_loadIndsClass();

	SNP* readSNP;

	_numSnp = 0;
	while(1){
		readSNP = new(SNP);

		if(!_lineReader->readTPEDLine(_fpTped, readSNP, _numSnp, _numCases+_numCtrls, _indsClass)){
			delete readSNP;
			break;
		}

		if(_snpSet.size() <= _numSnp){
			_snpSet.resize(_snpSet.size()+DEFAULT_NUM_SNPS);
		}
		_snpSet[_numSnp] = readSNP;
		_numSnp++;
	}

#ifdef DEBUG
	int j;
	uint16_t casesAa, ctrlsAa;
	for(int i=0; i<_numSnp; i++){
		printf("SNP %d:\n   name %s\n   cases 0", i, (char *)_snpSet[i]->_name);
		for(j=0; j<(_numCases/32+((_numCases%32)>0)); j++){
			printf("%u ", _snpSet[i]->_case0Values[j]);
		}

		printf("\n   cases 1 ");
		for(j=0; j<(_numCases/32+((_numCases%32)>0)); j++){
			printf("%u ", _snpSet[i]->_case1Values[j]);
		}

		printf("\n   cases 2 ");
		for(j=0; j<(_numCases/32+((_numCases%32)>0)); j++){
			printf("%u ", _snpSet[i]->_case2Values[j]);
		}
		printf("\n   controls 0 ");
		for(j=0; j<(_numCtrls/32+((_numCtrls%32)>0)); j++){
			printf("%u ", _snpSet[i]->_ctrl0Values[j]);
		}

		printf("\n   controls 1 ");
		for(j=0; j<(_numCtrls/32+((_numCtrls%32)>0)); j++){
			printf("%u ", _snpSet[i]->_ctrl1Values[j]);
		}

		printf("\n   controls 2 ");
		for(j=0; j<(_numCtrls/32+((_numCtrls%32)>0)); j++){
			printf("%u ", _snpSet[i]->_ctrl2Values[j]);
		}
	}
#endif
}
