#include "get_next_line.h"

char *get_next_line(int fd){
    char *line=NULL;
    static int last_offset;
    char t;
    int str_size=0;
    int n=0;
    lseek(fd,last_offset,SEEK_SET);
    do{
        n=read(fd,&t,1);
        if(n==-1){printf("Read error\n");exit(0);}
        if(n==0 && str_size==0){return NULL;}
        str_size++;
    }while(t!='\n' && t!='\0');
    if(lseek(fd,last_offset,SEEK_SET)!=-1){
        line = (char*)malloc(str_size+1);
        last_offset += str_size;
        read(fd,line,str_size);
        line[str_size]='\0';
    }
    return line;
}

char* get_next_line2(int fd){
    char *str;
    char buff;
    int n=0;
    str = malloc(1);
    char *t = str;
    int size=0;
    while(n=read(fd,&buff,1)>0){
        *t = buff;
        if(buff=='\0')
            break;
        size++;
        str = (char *)realloc(str,size+1);
        if(!str){printf("realloc failed\n");exit(0);}
        t = str+size;
        if(buff=='\n')
            break;
    }
    if(n==0 && size==0){return NULL;}
    (*t)='\0';
    return str;
}
