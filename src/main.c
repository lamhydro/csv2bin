#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "csv2bin.h"

int main(int argc, char *argv[])
{

	//csvd ts;
	//char *filename;
	tfile tsf, tsfb;
	clock_t t;
	double time_taken;

	/* Assigning ext arg to variables */
	if( argc != 4 ) {
      printf("Bad number of arguments supplied.\n");
	  return -1;
	}
	tsf.dirname = argv[1]; //"/home/luis/Documents/cpp/HYDATsfana/dayUnregLongFLOWSandCatch/";
	tsf.filename = argv[2]; //"01BJ001_DLY_FLOWS.csv";

	
	/* Reading CSV file */ 
	#if CLOCKT
	t = clock();
	#endif
	csvd *data = readCSVFile(&tsf);
	#if CLOCKT
	t = clock()-t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Time for reading CVS = %f\n", time_taken);
	#endif

	/* Write BIN file */
	tsfb.dirname = argv[1];
	tsfb.filename = argv[3];
	tsfb.nrows = tsf.nrows-1;
	if (writeCsv2Bin(&tsfb, data)) 
		return -1;

	#if READBIN
	/* Read BIN file */
	#if CLOCKT
	t = clock();
	#endif
	readBINFile(&tsfb);
	#if CLOCKT
	t = clock()-t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Time for reading BIN = %f\n", time_taken);
	#endif
	#endif

	/* Freeing heap memory */
	//freeMemCSV(&ts);
	
	return 0;
}

