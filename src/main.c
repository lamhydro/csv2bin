#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "csv2bin.h"

int main(int argc, char *argv[])
{

	/*csvd ts;
	char *filename;*/
	tfile tsf, tsfb;
	clock_t t;
	double time_taken;
	csvd *data;
	int i;

	/* Assigning ext arg to variables */
	if( argc != 4 ) {
      printf("Bad number of arguments supplied.\n");
	  return -1;
	}
	tsf.dirname = argv[1]; 
	tsf.filename = argv[2]; 

	
	/* Reading CSV file */ 
	#if CLOCKT
	t = clock();
	#endif
	data = readCSVFile(&tsf);
	#if CLOCKT
	t = clock()-t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Time for reading CVS = %f\n", time_taken);
	#endif

	/* Write BIN file */
	tsfb.dirname = argv[1];
	tsfb.filename = argv[3];
	tsfb.nrows = tsf.nrows-NHEADER;
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
	/*freeMemCSV(&ts);*/
	
	/* Allocate header array */
	for(i = 0; i < NHEADER; i++){
		free(header[i]);
	}

	return 0;
}

