#ifndef __CSV2BIN_H__
#define __CSV2BIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAXCHAR 1000

typedef struct typicalFile{
	char *dirname;
	char *filename;
	int nrows; 
} tfile;

typedef struct csvData2{
	unsigned n;
	int *year, *month, *day;
	float *var;
	//char **var_symbol;
} csvd2;

typedef struct csvData{
	int year, month, day;
	float var;
} csvd;


/*
Count number of rows in a file
*/
int nrowsFile(char *filename);

/*
/Read data from a csv file
*/
csvd *readCSVFile(tfile *tsf);

/*
Save a tserie struct into a binary file
*/
int writeCsv2Bin(tfile *tsf, csvd *data);

/*
Read and display bin file with tserie
*/
int readBINFile(tfile *tsf);

#endif
