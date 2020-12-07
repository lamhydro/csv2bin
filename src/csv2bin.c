#include "csv2bin.h"

/*
Count number of rows in a file
*/
int nrowsFile(char *filename)
{
	FILE *fp;
	char ch;
	int nlines = 0;

	if ((fp = fopen(filename,"r")) == NULL){
		printf("Error reading %s stopping... \n", filename);
		return -1;
	}

	while((ch=fgetc(fp))!=EOF) {
		if(ch=='\n')
			nlines++;
	}
	fclose(fp);
	return nlines;
}

/*
/Read data from a csv file
*/
csvd *readCSVFile(tfile *tsf)
{
	FILE *fp;
	unsigned i;
	char line[MAXCHAR];
	char *token;
	char seps[] = ",";
	char *newline;
	char *filename;
	csvd *data;

	/* Make up filename */
	filename = malloc(strlen(tsf->dirname) + strlen(tsf->filename));
	strcpy(filename, tsf->dirname);
	strcat(filename, tsf->filename);

	/* Number of file rows */
	tsf->nrows = nrowsFile(filename); 
	
	/* Open file */
	if ((fp = fopen(filename,"r")) == NULL){
		printf("Error reading %s stopping... \n", filename);
		exit(1);
	}
	
	data = (csvd *)malloc((tsf->nrows-NHEADER) * sizeof(csvd));

	/* Allocate header array 
	for(i = 0; i < NHEADER; i++){
	}*/

	/* Read the header's file*/
	for(i = 0; i < NHEADER; i++){
		fgets(line, MAXCHAR, fp);
		/*printf("len = %d\n", strlen(line));*/
		lheader[i] = strlen(line)-1;
		header[i] = (char *)malloc(lheader[i] * sizeof(char));
		/*header[i] = (char *)malloc(MAXCHAR * sizeof(char));*/
		strcpy(header[i], line);
		/*printf("%s", header[i]);*/
	}

	/* Read main table */
	/*printf("%s",line);*/
	i = 0;
	while (fgets(line, MAXCHAR, fp) != NULL){
		/*printf("%s",line);*/
		newline = strchr(line, '\n' );
		if ( newline )
			*newline = 0;
		token = strtok(line,seps);
		data[i].year = atoi(token);
		token = strtok(NULL,",");
		data[i].month = atoi(token);
		token = strtok(NULL,",");
		data[i].day = atoi(token);
		token = strtok(NULL,",");
		if (strcmp(token, " ")==0){
			data[i].var = NAN;
		}else{
			data[i].var = atof(token);
		}
			
		token = strtok(NULL,",");
		strcpy(data[i].var_symbol, token);
		token = strtok(NULL,",");

		/*printf("%d,%d,%d,%g,%s\n", data[i].year, data[i].month, data[i].day, data[i].var, data[i].var_symbol);
		printf("%d,%d,%d,%g\n", ts->year[i], ts->month[i], ts->day[i], ts->var[i]);*/
	
		/*if (i == 80){
			break;
		}*/

		i++;
	}
	fclose(fp);
	free(filename);
	return data;
}


/*
Save a csv struct into a binary file
*/
int writeCsv2Bin(tfile *tsf, csvd *data){ 
	unsigned i;
	FILE *fp;
	char *filename;
	/*int tint;
	double tdoub;*/

	/* Make up filename */
	filename = malloc(strlen(tsf->dirname) + strlen(tsf->filename));
	strcpy(filename, tsf->dirname);
	strcat(filename, tsf->filename);
	
	/* Write into *.csv file */
	if ((fp = fopen(filename,"wb")) == NULL){
		printf("Error writing %s stopping... \n", filename);
		return -1;
	}
	
	/* Write header */
	for(i = 0; i < NHEADER; i++){
		/*printf("%s", header[i]);*/
		/*printf("here");*/
		fwrite( header[i], lheader[i]*sizeof(char), 1, fp );
		/*fwrite( str, sizeof(char), MAXCHAR, fp );*/
	}

	/* Write main table */
	for(i = 0; i < tsf->nrows-NHEADER+1; i++){
		/*printf("%d,%d,%d,%g\n", ts->year[i], ts->month[i], ts->day[i], ts->var[i]);
		//tint = data[i].year;
		//fwrite( &tint, sizeof(int), 1, fp );
		//tint = data[i].month;
		//fwrite( &tint, sizeof(int), 1, fp );
		//tint = data[i].day;
		//fwrite( &tint, sizeof(int), 1, fp );
		//tdoub = data[i].var;
		fwrite( &tdoub, sizeof(double), 1, fp ); */
		fwrite( &data[i], sizeof(csvd), 1, fp );
	}	

	fclose(fp);
	free(filename);

	return 0;
}

/*
Read and display bin file with tserie
*/
int readBINFile(tfile *tsf){

	FILE *fp;
	/*
	int year, month, day;
	double var;
	*/
	char *filename;
	unsigned i;
	csvd rowcsv;
	char *headerb;

	/* Make up filename */
	filename = malloc(strlen(tsf->dirname) + strlen(tsf->filename));
	strcpy(filename, tsf->dirname);
	strcat(filename, tsf->filename);

	/* Open bin file */
	if ((fp = fopen(filename,"rb")) == NULL){
		printf("Error opening %s stopping... \n", filename);
		return -1;
	}

	/* Read header */
	for(i = 0; i < NHEADER; i++){
		headerb = (char *)malloc(lheader[i]*sizeof(char));
    	fread(headerb, lheader[i]*sizeof(char), 1, fp);
		/*printf("%s\n", headerb);*/
		free(headerb);
	}

	/* Read main table */
	i = 0;
	while (true){
	/*
	//while (!feof(fp)){
		//fread(&year, sizeof(int), 1, fp);
    	//fread(&month, sizeof(int), 1, fp);
    	//fread(&day, sizeof(int), 1, fp);
    	//fread(&var, sizeof(double), 1, fp);
		*/
    	fread(&rowcsv, sizeof(csvd), 1, fp);

		if (feof(fp))
			break;

		/* Print each element of the object */
    	/*printf("%d, %d, %d, %f, %s\n", rowcsv.year, rowcsv.month, rowcsv.day, rowcsv.var, rowcsv.var_symbol);*/
		i++;
	}

    /* Close the file */
    fclose(fp);
	free(filename);
    return 0;
}


