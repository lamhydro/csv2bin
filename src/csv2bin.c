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
	int i = 0;
	char line[MAXCHAR];
	char *token;
	char seps[] = ",";
	char *newline;
	char *filename;

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
	
	csvd *data = (csvd *)malloc((tsf->nrows-1) * sizeof(csvd));

	/* Read the header's file*/
	fgets(line, MAXCHAR, fp); 
	/*printf("%s",line);*/
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
		//strcpy(ts->var_symbol[i], token);
		token = strtok(NULL,",");

		//printf("%d,%d,%d,%g,%s\n", ts->year[i], ts->month[i], ts->day[i], ts->var[i], ts->var_symbol[i]);
		//printf("%d,%d,%d,%g\n", ts->year[i], ts->month[i], ts->day[i], ts->var[i]);
	
		/*if (i == 80){
			break;
		}*/

		i++;
	}
	fclose(fp);
	return data;
}


/*
Save a csv struct into a binary file
*/
int writeCsv2Bin(tfile *tsf, csvd *data){ 
	unsigned i;
	FILE *fp;
	char *filename;
	//int tint;
	//double tdoub;

	/* Make up filename */
	filename = malloc(strlen(tsf->dirname) + strlen(tsf->filename));
	strcpy(filename, tsf->dirname);
	strcat(filename, tsf->filename);
	
	/* Write into *.csv file */
	if ((fp = fopen(filename,"wb")) == NULL){
		printf("Error writing %s stopping... \n", filename);
		return -1;
	}
	
	for(i = 0; i < tsf->nrows; i++){
		//printf("%d,%d,%d,%g\n", ts->year[i], ts->month[i], ts->day[i], ts->var[i]);
		//tint = data[i].year;
		//fwrite( &tint, sizeof(int), 1, fp );
		//tint = data[i].month;
		//fwrite( &tint, sizeof(int), 1, fp );
		//tint = data[i].day;
		//fwrite( &tint, sizeof(int), 1, fp );
		//tdoub = data[i].var;
		//fwrite( &tdoub, sizeof(double), 1, fp );
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
	//int year, month, day;
	//double var;
	char *filename;
	unsigned i;
	csvd rowcsv;

	/* Make up filename */
	filename = malloc(strlen(tsf->dirname) + strlen(tsf->filename));
	strcpy(filename, tsf->dirname);
	strcat(filename, tsf->filename);

	/* Open bin file */
	if ((fp = fopen(filename,"rb")) == NULL){
		printf("Error opening %s stopping... \n", filename);
		return -1;
	}

	//printf("Reading %s bin file \n", filename);
    // Read the object and store in the buffer
	i = 0;
	while (true){
	//while (!feof(fp)){
		//fread(&year, sizeof(int), 1, fp);
    	//fread(&month, sizeof(int), 1, fp);
    	//fread(&day, sizeof(int), 1, fp);
    	//fread(&var, sizeof(double), 1, fp);
    	fread(&rowcsv, sizeof(csvd), 1, fp);

		if (feof(fp))
			break;

		// Print each element of the object
    	printf("%d, %d, %d, %f\n", rowcsv.year, rowcsv.month, rowcsv.day, rowcsv.var);
		i++;
	}

    // Close the file
    fclose(fp);
    return 0;
}


