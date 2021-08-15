#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc,char** argv)
{
    char line[1025];
    char word[256];
    char *ptr;
    char *qtr;
    char *rtr;
    int len;
    if(argc==3)
    {
        while(fgets(line,1024,stdin)!=NULL)
        {
            if(strstr(line,*(argv+1))!=NULL)
            {
                ptr=strstr(line,*(argv+1));
                qtr=ptr+strlen(*(argv+1));
                len=strlen(line)-strlen(ptr);
                for(int i=0;i<len;i++)
                {
                    printf("%c",line[i]);
                }
                printf("%s",*(argv+2));
                printf("%s",qtr);
            }
            else if(strstr(line,*(argv+1))==NULL)
            {
                printf("%s",line);
            }
        }
    }
    if(argc==4 && *(*(argv+1)+1)!='g')
    {
        printf("Usage:\n./sed [-g(optional)] [-source(required)] [-target(required)]\n");
    }
    if( argc<=2 || argc>=5)
    {
        printf("Usage:\n./sed [-g(optional)] [-source(required)] [-target(required)]\n");  
    }
    if(argc==4 && *(*(argv+1)+1)=='g')
    {
        while(fgets(line,1024,stdin)!=NULL)
        {
            if(strstr(line,*(argv+2))==NULL)
            {
                printf("%s",line);
                break;
            }
                ptr=strstr(line,*(argv+2));
                qtr=ptr+strlen(*(argv+2));
                len=strlen(line)-strlen(ptr);
                for(int i=0;i<len;i++)
                {
                    printf("%c",line[i]);
                }
                printf("%s",*(argv+3));
                
            while((strstr(qtr,*(argv+2)))!=NULL)
            {
                rtr=qtr;
                ptr=strstr(qtr,*(argv+2));
                qtr=ptr+strlen(*(argv+2));
                len=strlen(rtr)-strlen(ptr);
                for(int i=0;i<len;i++)
                {
                    printf("%c",*(rtr+i));
                }
                printf("%s",*(argv+3));
            }
            printf("%s",qtr);
        }

    }
    return 0;

}
