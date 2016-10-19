/*
 * Options.h
 *
 *  Created on: 16/12/2014
 *      Author: jorge
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_
#include "GPUMacros.h"
#include "Utils.h"

class Options {
public:
	Options();
	Options(int argc, char* argv[]);
	virtual ~Options();

	inline int getGPUIndex()
	{
		return _gpuIndex;
	}

	inline string& getTPEDFileName() {
		return _tpedFileName;
	}

	inline string& getTFAMFileName(){
		return _tfamFileName;
	}

	// To parse the command line
	bool parse(int argc, char* argv[]);

	// To print the help for the users
	void printUsage();

private:
	string _tpedFileName;
	string _tfamFileName;

	int _gpuIndex;

	/*private member functions*/
	void _setDefaults();
};

#endif /* OPTIONS_H_ */
