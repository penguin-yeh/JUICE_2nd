
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 
char *getword(char *text,char *word)
{
    char *ptr;
    char *qtr;
    char *textend;
    ptr=text;
    qtr=word;
    textend=text+strlen(text);
    word[0]='\0';
    while(isspace(*ptr))  ptr++;
    while(!isspace(*ptr) && ptr<textend)
    {
        *qtr++=*ptr++;
    }
    *qtr='\0';
    if(word[0]=='\0')
    {
        return NULL;
    }
    return ptr;
}
struct info
{
    //int number;
    char name[32];
    char email[128];
    char url[128];
    char phone[16];
};
void printfINF(struct info inf)
{
    printf("%s\t%s\t%s\t%s\n",inf.name,inf.email,inf.url,inf.phone);
}
int main(int argc,char **argv)
{
    int i=0;
    char line[1024];
    char *ptr;
    char word[256];
    char words[256][256];
    struct info inf[100];
    for( i=0;i<atoi(argv[1]);i++)
    {
        //inf[i].number=i+1;
        scanf("%s\t%s\t%s\t%s",inf[i].name,inf[i].email,inf[i].url,inf[i].phone);
    }
    while((fgets(line,1024,stdin))!=NULL)
    {
        int k=0;
        ptr=line;
        while((ptr=getword(ptr,word))!=NULL)
        {
            strcpy(words[k],word);
            k++;
           // printf("words.0  %s\n",words[0]);
        }
        if(words[0][0]=='i')
        {
            //inf[i].number=i+1;
            strcpy(inf[i].name,words[1]);
            strcpy(inf[i].email,words[2]);
            strcpy(inf[i].url,words[3]);
            strcpy(inf[i].phone,words[4]);
            i++;
            //printf("i=>%d",i);
        }
        if(words[0][0]=='u')
        {
            for(int j=0;j<i;j++)
            {

                if(strcmp(inf[j].name,words[1])==0)
                {
                    strcpy(inf[j].email,words[2]);
                    strcpy(inf[j].url,words[3]);
                    strcpy(inf[j].phone,words[4]);
                }
            }
        }
        if(words[0][0]=='d')
        {
            for(int j=0;j<i;j++)
            {
                if(strcmp(inf[j].name,words[1])==0)
                strcpy(inf[j].name,"0");
            }
            //i--;
            //printf("i=>%d",i);
        }
        if(words[0][0]=='p')
        {
            int k=0;
            printf("number\tname\temail\tsite\tphone number\n");
            printf("----------------------------------------------------\n");

            for(int j=0;j<i;j++)
            {
                if(strcmp(inf[j].name,"0")!=0)
                {
                    k++;
                }
                if(strcmp(inf[j].name,"0")==0)
                {
                    continue;
                }
                printf("[%d] ",k);
                printfINF(inf[j]);
            }
            printf("\n");
            }
        if(words[0][0]=='f')
        {
            int flag=0;
            for(int j=0;j<i;j++)
            {
                if(strstr(inf[j].name,words[1])!=NULL)
                {
                   flag=1;
                }
            }
            if(flag==1)
            {
                printf("Find %s result: ",words[1]);
                for(int j=0;j<i;j++)
                {
                   if(strstr(inf[j].name,words[1])!=NULL)
                {
                   printf("%s ",inf[j].name);
                }
                }
                printf("\n");
            }
            if(flag==0)
            {
                printf("%s not found!\n",words[1]);
            }
        }
        if(words[0][0]=='s')
        {
            if(words[1][0]=='n')
            {
                for(int j=0;j<i-1;j++)
                {
                    for(int k=0;k<i-1-j;k++)
                    {
                        if(strcmp(inf[k].name,inf[k+1].name)>0)
                        {
                            struct info tmp;
                            tmp=inf[k];
                            inf[k]=inf[k+1];
                            inf[k+1]=tmp;
                        }
                        
                    }
                }
            }
            if(words[1][0]=='e')
            {
                for(int j=0;j<i-1;j++)
                {
                    for(int k=0;k<i-1-j;k++)
                    {
                        if(strcmp(inf[k].email,inf[k+1].email)>0)
                        {
                            struct info tmp;
                            tmp=inf[k];
                            inf[k]=inf[k+1];
                            inf[k+1]=tmp;
                        }
                        
                    }
                }
            }
            if(words[1][0]=='u')
            {
                for(int j=0;j<i-1;j++)
                {
                    for(int k=0;k<i-1-j;k++)
                    {
                        if(strcmp(inf[k].url,inf[k+1].url)>0)
                        {
                            struct info tmp;
                            tmp=inf[k];
                            inf[k]=inf[k+1];
                            inf[k+1]=tmp;
                        }
                        
                    }
                }
            }
            if(words[1][0]=='p')
            {
                for(int j=0;j<i-1;j++)
                {
                    for(int k=0;k<i-1-j;k++)
                    {
                        if(atoi(inf[k].phone)>atoi(inf[k+1].phone))
                        {
                            struct info  tmp;
                            tmp=inf[k];
                            inf[k]=inf[k+1];
                            inf[k+1]=tmp;
                        }
                        
                    }
                }
            }
        }
        if(words[0][0]=='q')
        {
            break;
        }
    }
    
    return 0;
}

