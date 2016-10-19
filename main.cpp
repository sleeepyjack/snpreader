#include "SNPReader.h"

int main(int argc, char* argv[])
{
	// The object that reads the biallelic information of the SNPs
	SNPReader* reader = new SNPReader("samples/BOOSTTest1.tped", "samples/BOOSTTest1.tfam");

	reader->loadSNPSet();

	delete reader;
}
