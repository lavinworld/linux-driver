/*
navit-trunk github:
https://github.com/navit-gps/navit
*/

#include "stdio.h"
#include "stdlib.h"
#include <string.h>

int main(void)
{
    int ret = 0;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("./cmdlist.txt","r");
    if(fp == NULL){
        printf("open fail\r\n");
        exit(EXIT_FAILURE);
    }

    if (fp != NULL) {
        while (getline(&line,&len,fp) > 0) {
            int len=strlen(line);
            if (len > 0 && line[len-1] == '\n')
                line[len-1]='\0';
            printf("line=%s,len=%d\r\n",line,len);
 
        }
        if (line){
            free(line);
            line = NULL;
        }
            
        fclose(fp);
    }

    if(line){
        free(line);
        line = NULL;
    }
	exit(EXIT_SUCCESS);
   

    return ret;
}
