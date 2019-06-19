#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_csv.h"
#include "read_csv.h"


void find_name(const char*, const char*);
void add_record(const char*, const char*, const int, const char*);
void delete_record( const char*, const char*);

int main ()
{
	/* Question 1 */
	load_and_convert("tester");
	
	/* Question 2 */
       	read_csv("output.csv");
	
	 /* Question 3.1*/
	 find_name("output.csv", "Maria");
	 find_name("output.csv", "Jason");

	 /* Question 3.2 */
	 add_record("output.csv", "Jason", 36, "Skookumchuk");
	 read_csv("output.csv"); 

	/* Question 3.3 */
	delete_record("output.csv", "Maria");
       	read_csv("output.csv");



	return 0; 

}

void find_name(const char* csv_filename, const char* name){

	FILE* p;
	p = fopen(csv_filename, "rt");
	if (p==NULL) exit(1); 
	

	char record [1000];
	char nameFile [100];

	int i =0,j =0;
	int ifName=0;
	//read line in from csv file into array
	//keep reading line by line until EOF
	fgets(record, 999, p);
	while(!feof(p)){
		//run through array until reach , 
		while(record[i] != ','){
			//add stuff in the record file into name file
			nameFile[j] = record[i];
			i++;
			j++;
		}
		//once reach, you have added entire name in and add '\0' to array
			nameFile[j]= '\0';
			//compare name string and namefile 
			if (strcmp(name,nameFile) ==0){
			       ifName=1;
			       printf("Name exists: %s\n",record); 
			}	       

			j=0;
			i=0;	
		fgets(record, 999, p);
	}
	if (ifName == 0){
		printf("Name not found\n");
	}

	
	fclose(p);
}

void add_record(const char* csv_filename, const char* name, const int age, const char* city){


	//open file using pointer but to append to mode (add to the end)
	FILE*p = fopen(csv_filename, "at");
	if (p==NULL) exit(1);
	//use file print to print the string " " to the file using the passed variables
	fprintf(p,"%s, %d, %s \n", name, age, city);
	fclose(p);	

}

void delete_record(const char* csv_filename, const char* name){

//open two files (one from passed pointer) and the other is a new one that you will be writing to 
FILE* p = fopen(csv_filename, "rt");
FILE* temp = fopen ("temp.csv", "wt");

if (p ==NULL || temp == NULL) exit(1);

//two arrays 
char record [1000];
char nameFile[100];

//read line of file into array record and keep doing it one by one until EOF
fgets(record, 999, p);
int i=0, j=0, enterLoop=1;

while(!feof(p)){

	while(record[i] != ','){
		nameFile[j]= record[i];
		i++;
		j++;

	}
		nameFile[j]= '\0';

		
		if (enterLoop==0){
			fprintf(temp, "%s",record);

		}
		if (!(strcmp(name, nameFile) ==0)&& enterLoop==1){
			fprintf(temp,"%s", record);
	
		}		

		if(strcmp(name, nameFile) ==0){
			enterLoop=0;	
		}

		i=0;
		j=0;
		fgets(record, 999,p);

}

remove("output.csv");
rename("temp.csv", "output.csv");

fclose(p);
fclose(temp);

}
