/*
 * Options.cpp
 *
 *  Created on: 16/12/2014
 *      Author: jorge
 */

#include "Options.h"

Options::Options() {
	_setDefaults();
}

Options::Options(int argc, char* argv[]) {
	_setDefaults();

	// Parse the command line
	parse(argc, argv);
}

Options::~Options() {
}

void Options::printUsage() {
	fprintf(stderr,
			"--------------------------------------------------------------------------------\n\n");
	fprintf(stderr,
			"Preliminary program to read the information of SNPs from files with TPED/TFAM format\n");

	fprintf(stderr,
			"--------------------------------------------------------------------------------\n\n");

	fprintf(stderr, "Usage: SNPReader -rp srcTPEDFile -rf srcTFAMFile -gid GPUId\n");

	// Input
	fprintf(stderr, "\tsrcTPEDFile: the file name for the SNPs inputs with -tped format\n");
	fprintf(stderr, "\tsrcTFAMFile: the file name for the individuals information with -tfam format\n");

	fprintf(stderr, "\t-gid <int> [int] ... (index of the GPUs. Default = %d)\n",
			_gpuIndex);

	fprintf(stderr, "Others:\n");
	fprintf(stderr, "\t-h <print out the usage of the program)\n");
}

void Options::_setDefaults() {
	// Empty string means outputing to STDOUT
	_tpedFileName = "";
	_tfamFileName = "";
	_gpuIndex = 0;
}

bool Options::parse(int argc, char* argv[]) {
	int intVal, i, j;
	double doubleVal;
	float floatVal;
	int argind = 1;

	if (argc < 2) {
		return false;
	}

	// Check the help
	if (!strcmp(argv[argind], "-h") || !strcmp(argv[argind], "-?")) {
		return false;
	}

	// Print out the command line
	fprintf(stderr, "Command: ");
	for (int i = 0; i < argc; ++i) {
		fprintf(stderr, "%s ", argv[i]);
	}
	fputc('\n', stderr);

	/*check the availability of GPUs*/
	GPUInfo *gpuInfo = GPUInfo::getGPUInfo();
	if (gpuInfo->getNumGPUs() == 0) {
		Utils::exit("No compatible GPUs are available in your machine\n");
	}

	// For the other options
	while (argind < argc) {
		// Input file
		if (!strcmp(argv[argind], "-rp")) {
			argind++;
			if (argind < argc) {
				_tpedFileName = argv[argind];
				argind++;
			} else {
				Utils::log("not specify value for the parameter %s\n", argv[argind - 1]);
				return false;
			}
		}
		else if (!strcmp(argv[argind], "-rf")) {
			argind++;
			if (argind < argc) {
				_tfamFileName = argv[argind];
				argind++;
			} else {
				Utils::log("not specify value for the parameter %s\n", argv[argind - 1]);
				return false;
			}
		}else if (!strcmp(argv[argind], "-gid")) {
			argind++;
			if (argind < argc) {
				sscanf(argv[argind], "%d", &intVal);
				if ((intVal < 0) || (intVal>=gpuInfo->getNumGPUs())){
					Utils::log("value %d not valid for GPU index\n", intVal);
					return false;
				}
				_gpuIndex = intVal;
			} else {
				Utils::log("not specify enough values for the parameter -gid\n");
				return false;
			}
			argind++;
		}
	}

	Utils::log("GPU index: %d\n", _gpuIndex);

	if(!strcmp(_tfamFileName.c_str(), "") || !strcmp(_tpedFileName.c_str(), "")){
		Utils::log("Input files not specified!!!\n");
		return false;
	}

	return true;
}
