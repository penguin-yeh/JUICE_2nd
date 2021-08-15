#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int priority(char token)
{
     if( token=='+' || token=='-' )
     {
         return 1;
     }     
     else if( token =='*' || token== '/')
     {
         return 2;
     }
     else return 0;
}

int istoken(char token[])
{
    if(strcmp(token,"+")==0||strcmp(token,"-")==0||strcmp(token,"*")==0||strcmp(token,"/")==0)
    {
        return 1;
    }
    else return 0;
}

int isparentheses(char token[])
{
    if(strcmp(token,"(")==0 || strcmp(token,")")==0)
    {
        return 1;
    }
    return 0;
}

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
        if(*ptr=='(' || *ptr==')')
        {
            *qtr++=*ptr++;
            break;
        }
        if(*(ptr+1)==')')
        {
            *qtr++=*ptr++;
            break;
        }
        *qtr++=*ptr++;
    }
    *qtr='\0';
    if(word[0]=='\0')
    {
        return NULL;
    }
    return ptr;
}


int main()
{
    char line[1024];
    char word[256];
    char words[256][256];
    //char token[100][100];
    int  number[100];
    char *ptr;
    while(fgets(line,1024,stdin)!=NULL)
    {
        int i=0;
        int len=strlen(line);
        if(line[len-1]=='\n')
        {
            line[len-1]='\0';
        }
        ptr=line+3;
        if(line[0]=='i')
        {
            char stack[1024];
            memset(stack,'\0',sizeof(stack));
            int stack_cnt=0;
            int word_cnt=0;
            while((ptr=getword(ptr,word))!=NULL)
            {
                strcpy(words[word_cnt],word);
                word_cnt++;
            }
            for(int i=0;i<word_cnt;i++)
            {
                if(strcmp(words[i],"(")==0)
                {
                    stack[stack_cnt]=words[i][0];
                    stack_cnt++;
                }
                else if(istoken(words[i]))
                {
                    while(priority(stack[stack_cnt-1])>=priority(words[i][0]))
                    {
                        printf(" %c",stack[stack_cnt-1]);
                        stack_cnt--;
                    }
                    stack[stack_cnt]=words[i][0];
                    stack_cnt++;
                    printf(" ");
                }
                else if(strcmp(words[i],")")==0)
                {
                    while(stack[stack_cnt-1]!='(')
                    {
                        printf(" %c",stack[stack_cnt-1]);
                        stack_cnt--;
                    }
                    stack_cnt--;
                }
                else
                {
                      printf("%s",words[i]);
                }
            }
            stack_cnt--;
            while(stack_cnt>=0)
            {
                printf(" %c",stack[stack_cnt]);
                stack_cnt--;
            }
            printf(" \n");
        }
            else if(line[0]=='p')
            {
                int sum;
                while((ptr=getword(ptr,word))!=NULL)
                {
                    if(!istoken(word))
                    {
                        number[i]=atoi(word);
                        i++;
                    }
                    else if(istoken(word))
                    {
                        if(strcmp(word,"+")==0)
                        {
                            sum=number[i-2]+number[i-1];
                            number[i-2]=sum;
                            i--;
                        }
                        if(strcmp(word,"-")==0)
                        {
                            sum=number[i-2]-number[i-1];
                            number[i-2]=sum;
                            i--;
                        }
                        if(strcmp(word,"*")==0)
                        {
                            sum=number[i-2]*number[i-1];
                            number[i-2]=sum;
                            i--;
                        }
                        if(strcmp(word,"/")==0)
                        {
                            sum=number[i-2]/number[i-1];
                            number[i-2]=sum;
                            i--;
                        }
                    }
                }
                printf("%d\n",sum);
            }
    }
        return 0;
}