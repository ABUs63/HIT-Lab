#include <stdio.h>
#include <stdlib.h>

char *buffer;

int main()
{
    FILE *pf=NULL;
    int len=0;
    pf=fopen("hello.c","r");
    if(pf==NULL)
        return 0;
    else{
        fseek(pf,0L,SEEK_END);
        len=ftell(pf);
        rewind(pf);
        buffer=malloc(len+1);
        fread(buffer,len,1,pf);
        fclose(pf);
        for(int i=0;i<len;i+=16){
            if(i>=len)break;
            for(int j=0;j<16;j++){
                if(buffer[i+j]=='\n')printf("\\n    ");
                else if(buffer[i+j]==' ')printf("SP    ");
                else printf("%-6c",buffer[i+j]);
                if(i+j>=len-1)break;
            }printf("\n");
            for(int k=0;k<16;k++){
                if(buffer[i+k]>0xffffff00) printf("%-6x",buffer[i+k]-0xffffff00);
                else printf("%-6x",buffer[i+k]);
                if(k+i>=len-1)break;
            }printf("\n");
        }free(buffer);
    }return 1;
}
