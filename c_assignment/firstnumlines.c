#include <stdio.h>
#include <stdlib.h>

char ** firstnumlines(FILE * inputfp, unsigned int num);

int main()
{
   FILE * fp = fopen("file.txt", "r");
   // Assume fp is not NULL
   char ** firstlines = firstnumlines(fp, 10);
   for (int i = 0; i < 10; i++) {
        if (firstlines[i] != NULL) {
            printf("%s", firstlines[i]);
        }
   }
   printf("\n");
   fclose(fp);
   free(firstlines);
}

char ** firstnumlines(FILE * inputfp, unsigned int num)
{
	char ** headbuff = calloc(num, sizeof(char *));
	for(unsigned int i = 0; i < num; i++) {
		   headbuff[i] = (char *) calloc(255, sizeof(char));
		   fgets(headbuff[i],255,inputfp);
	}
	return headbuff;
}
