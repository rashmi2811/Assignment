#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** lastnumlines(FILE * inputfp, unsigned int num){

	if(num <= 0)
		return NULL;

	char ** tailbuff = (char **) calloc(num, sizeof(char *));
	char ** temp = (char **) calloc(num, sizeof(char *));

	for(int j = 0; j < num; j++) {
		tailbuff[j] = (char *) calloc(255, sizeof(char));
		temp[j] = (char *) calloc(255, sizeof(char));
	}

	int i = 0, lines = 0;
	//printf("lines - i - tailbuff\n");
	while(!feof(inputfp)){

			if(lines % num == 0)
				i = 0;

			fgets(temp[i], 255, inputfp);
			//printf("%d     - %d     - %s\n", lines, i, temp[i]);

			//bcopy(fgets(tailbuff[i], 255, inputfp), tailbuff[i], sizeof(tailbuff[i]));

			//printf("%d %p\n",i, &temp[i]);
			i++;
			lines++;
	}

	//printf("%d\n",lines);
	//printf("%d\n",i);
	
	if(num >= lines){
		printf("Given input exceeds file size\n");
		for(int  j = 0; j < num; j++){
			free(temp[j]);
			free(tailbuff[j]);
		}
		free(temp);
		free(tailbuff);
		return NULL;
	}

	for(int a = 0, b = i-1; b < num; a++, b++)
		strcpy(tailbuff[a], temp[b]);

	for(int a = i, b = 0; b < i-1; a++, b++)
		strcpy(tailbuff[a], temp[b]);

	for(int j = 0; j < num; j++){
		free(temp[j]);
	}

	free(temp);
	
	return tailbuff;

}


int main(int argc, char ** argv) {
	FILE * inputfp = fopen(argv[1], "r");

	int num;
	scanf("%d",&num);
	printf("\n");

	char ** lastlines = lastnumlines(inputfp,num);

	if(lastlines==NULL){
		fclose(inputfp);
		return 0;
	}

	for(int i=0;i<num;i++){
		if(lastlines[i] != NULL){
		printf("%s",lastlines[i]);
		
		//printf("%d %p\n",i, &lastlines[i]);
		}
	}

	for(int i =0;i<num;i++){
		free(lastlines[i]);
	}
	free(lastlines);

	fclose(inputfp);

}
