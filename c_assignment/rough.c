#include <stdio.h>
#include <stdlib.h>

char ** lastnumlines(FILE * inputfp, unsigned int num){
	char ** tailbuff = (char **) calloc(num, sizeof(char *));
	char ** temp = (char **) calloc(100, sizeof(char *));
	int i=0;
	while(!feof(inputfp)){

		temp[i] = (char *) calloc(255, sizeof(char));
		fgets(temp[i],255,inputfp);
		//printf("%s", temp[i]);
		i++;
	}
	
	if(num < i){
	for(int a = 0, b = i-num-1;b < i-1; a++, b++) {
		tailbuff[a] = (char *) calloc(255, sizeof(char));
		tailbuff[a] = temp[b];
		//printf("%s\n",tailbuff[a]);
	}
	}
	else{
	//	printf("%p", tailbuff);
		free(temp);
		return NULL;
	}
	
	/*for(int j = 0; j <= i; j++){
		free(temp[j]);
	}

	free(temp);*/

	return tailbuff;

}


int main() {
	FILE * inputfp = fopen("input.txt", "r");

	int num;
	scanf("%d",&num);
	printf("\n");

	char ** lastlines = lastnumlines(inputfp,num);

	if(lastlines==NULL){
		free(lastlines);
	  fclose(inputfp);
	  return 0;
	 }

	for(int i=0;i<num;i++){
		//if(lastlines[i] != NULL){
			printf("%d %s\n",i, lastlines[i]);
		//}
	}

	//printf("%p",lastlines);
	for(int i=1;i<num;i++){
		//printf("%p",lastlines[i]);
		free(lastlines[i]);
	}
	free(lastlines);

	fclose(inputfp);

}
