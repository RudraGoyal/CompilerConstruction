#include <stdio.h>
#include <stdlib.h>


FILE *getStream(FILE* fp,char* buffer,int bsize)
{
	int count;
	if(!feof(fp))
		count=fread(buffer,1,bsize,fp);

	if(count<bsize)
	buffer[count] = '\0';

	return fp;

}

void removeComments(FILE *fp){
    char c = fgetc(fp);
    while (c!=EOF)
    {
        if(c=='%'){
            while(c!='\n' && c!=EOF){
                c=fgetc(fp);
            }
        }
        if(c==EOF)
        break;
        printf("%c",c);
        c=fgetc(fp);
    }
    printf("\n");
    
}

int main()
{
    FILE *fp = fopen("t2.txt","r");
    int bufsize=5;
    char *buffer = (char*)malloc(bufsize);
    if(fp==NULL){
        printf("error opening file");
    }
    // while(!feof(fp)){
	// 	memset(buffer, 0, sizeof(buffer));
    //     fp = getStream(fp,buffer,bufsize);
    //     printf("%s\n",buffer);
    // }
    removeComments(fp);
    fclose(fp);
    // printf("hello\n");

    return 0;
}