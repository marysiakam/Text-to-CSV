#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void read_csv(const char* csv_filename){
	FILE* p;
	
	p=fopen(csv_filename, "rt");
	
	if (p==NULL) exit(1);
	
	char c;
	
	char record[1000];
	fgets(record, 999, p);

	printf("\n");

	while(!feof(p)){

		printf("%s", record);
		fgets(record, 999, p);
	}
	printf("\n");
	fclose(p);
}
