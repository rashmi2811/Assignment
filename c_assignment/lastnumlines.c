#include <stdio.h>
#include <stdlib.h>

char ** lastnumlines(FILE * inputfp, unsigned int num){
	char ** tailbuff = (char **) calloc(num, sizeof(char *));
	char ** temp = (char **) calloc(num, sizeof(char *));
	int i=0;
	while(i<num){

		if(feof(inputfp)){
			printf("\nGiven Size is Greater than the input file\n\n");
			for(int i =0;i<num;i++){
				free(temp[i]);
			}
			free(temp);
			free(tailbuff);

			return NULL;
		}
		else{
			temp[i] = (char *) calloc(255, sizeof(char));
			fgets(temp[i],255,inputfp);
			i++;
		}
	}

	int lines = sizeof(temp)/sizeof(temp[0]);

	for(int a = 0, b = lines-num; b < num; a++, b++) {
		tailbuff[a] = (char *) calloc(255, sizeof(char));
		tailbuff[a] = temp[b];
	}
	return tailbuff;

}



int main() {
	FILE * inputfp = fopen("input.txt", "r");

	int num;
	scanf("%d",&num);
	printf("\n");

	char ** lastlines = lastnumlines(inputfp,num);

	if(lastlines==NULL){
		return 0;
	}

	for(int i=0;i<num;i++){
		if(lastlines[i] != NULL){
			printf("%s",lastlines[i]);
		}
	}

	for(int i =0;i<num;i++){
		free(lastlines[i]);
	}
	free(lastlines);

	fclose(inputfp);

}
