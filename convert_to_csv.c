#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNumRecords(const char*);
int getRecordLength(const char*);

void load_and_convert(const char* filename){
	//create file pointer to text file 
	FILE* tp;

	//create file pointer to csv file 
	FILE* cp;
	
	//open csv file in write to mode 
	cp= fopen("output.csv","wt");
	
	if (cp ==NULL) exit(1);
	//open text file in read mode
	//tp = fopen(filename, "rt");


	//create 2D array of Strings (3D array of chars)
	char*** arr; 
	
	int records = getNumRecords(filename);
	
	//allocate memory for first "layer" of storage array
	arr = (char***) calloc(records, sizeof(char**));

	int i;
	int recordLength= getRecordLength(filename);

	for(i=0; i< records ; i++){
		arr[i]= (char **) calloc (recordLength, sizeof(char*));	
	}
	
	i=0;
	int  j=0, wordlength=0;
	char c;
	char buffer[1000];
	tp =fopen(filename, "r");
	if (tp ==NULL) exit(1);

	while(!feof(tp)){
		while(!feof(tp) && (c=fgetc(tp)) != '\n'){
			buffer[wordlength]=c;
			wordlength++;
			if(c == ' '){
				arr[i][j]= (char*) calloc(wordlength, sizeof(char));
				buffer[wordlength-1]= '\0';
				strcpy(arr[i][j], buffer);
				i++;
				wordlength=0;	
			}
			
		}
		
		arr[i][j]= (char*) calloc(wordlength + 1, sizeof(char));	
		buffer[wordlength]= '\0';
		
		strcpy(arr[i][j], buffer);
		
		i=0;
		wordlength =0;
		j++;
		

	
		if(( j == (recordLength))&& ( i == 0)){
			break;
		}



	}

	//add array into output file 
	
	

	for (i=0; i<records; i++){
		for( j=0; j<recordLength; j++){
			if (j== recordLength-1){
				fprintf(cp, " %s", arr[i][j]);
				fprintf(cp, " \n");
			}else{
			fprintf(cp,"%s, ", arr[i][j]);
			}
		}
	
	}
	fclose(tp);
	fclose(cp);


}

//method that returns number of records
int getNumRecords(const char* filename ){
	
	FILE* p; 
	p= fopen(filename, "r");
	if(p ==NULL) exit(1);
	
	int i=0;
	char c;
	
	//while not newline


	while(( c= fgetc(p)) != '\n'){
		if( c == ' '){
			i++;
		}
	}
	i++;
	fclose(p);
	return i;
}



int getRecordLength(const char* filename){
	FILE *p;
	p=fopen(filename, "r");
	if (p ==NULL) exit (1);

	int i=0;

	while( !feof(p)){
		if (fgetc(p) == '\n'){
			i++;
		}

	}
	fclose(p);
	return i;
}
