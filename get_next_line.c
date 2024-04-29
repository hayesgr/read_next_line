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

typedef struct {
    char *str;
    int size;
}mFile;

mFile *read_file(int fd){
    mFile *F;
    F = malloc(sizeof(mFile));
    F->str = malloc(1);
    char * t = F->str;
    if(!F->str){printf("malloc error\n");exit(0);}
    char buff;
    int n=0;
    while (n=read(fd,&buff,1)>0){
        F->size++;
        *t=buff;
        t++;
        F->str = (char *)realloc(F->str,1);
    }
    F->size++;
    (*t)='\0';
    return F;
}
char *get_next_line2(int fd){
    static mFile *F;
    static int index;
    static int flag;
    if(flag==0){
        F = read_file(fd);
        flag++;
    }
    if(flag==2){free(F->str);free(F);return NULL;}
    int i=index,s=0;
    char *ret;
    while(F->str[i]!='\n' && F->str[i]!='\0'){
        i++;s++;
    }
    if(F->str[i]!='\0'){i++;s++;}
    if(F->str[i]=='\0'){flag++;}
    ret = malloc(s+1);
    for(int c=0;c<s;c++){
        ret[c]=F->str[c+index];
    }
    ret[s]='\0';
    index=i;
    return ret;
}
