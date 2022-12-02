#include <stdio.h>
#include <stdlib.h>


char ** firstnumlines(FILE * inputfp, unsigned int num){
	char ** headbuff = (char **) calloc(num, sizeof(char *));
	int i=0;
	int j=1;
	while(j<=num){

		if(feof(inputfp)){
			printf("\nGiven Size is Greater than the input file\n\n");
			for(int i =0;i<num;i++){
				free(headbuff[i]);
			}
			free(headbuff);

			return NULL;
		}
		else{
			headbuff[i] = (char *) calloc(255, sizeof(char));
			fgets(headbuff[i],255,inputfp);
			i++;
			j++;
		}
	}
	return headbuff;

}



int main() {
	FILE * inputfp = fopen("input.txt", "r");

	int num;
	scanf("%d",&num);
	printf("\n");

	char ** firstlines = firstnumlines(inputfp,num);

	if(firstlines==NULL){
		return 0;
	}

	for(int i=0;i<num;i++){
		if(firstlines[i] != NULL){
			printf("%s",firstlines[i]);
		}
	}

	for(int i =0;i<num;i++){
		free(firstlines[i]);
	}
	free(firstlines);

	fclose(inputfp);

}
