#include "SNPReader.h"

int main(int argc, char* argv[])
{

	double stime, etime;

	/*get the startup time*/
	stime = Utils::getSysTime();

	// Class to read parameter information
	Options* options = new Options();

	/*parse the arguments*/
	if (!options->parse(argc, argv))
	{
		options->printUsage();
		return 0;
	}

	// The object that reads the biallelic information of the SNPs
	SNPReader* reader = new SNPReader(options);

	reader->loadSNPSet();

	etime = Utils::getSysTime();
	Utils::log("Overall time: %.2f seconds\n", etime - stime);

	delete reader;
	delete options;
	return 0;
}
