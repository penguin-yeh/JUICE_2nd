#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Lnode{
    char term[1024];
    struct Lnode *next;
};

char words[100][1024];
int Cnt=0;

struct Lnode *L_Added(struct Lnode *L,char *term)
{
    if(Cnt==0)
    {
        strcpy(words[Cnt],term);
        Cnt++;
    }
    else if(Cnt!=0)
    {
        int flag=0;
        for(int i=0;i<Cnt;i++)
        {
            if(strcmp(words[i],term)==0)  
            {
                flag=1;
                break;
            }
        }
            if(flag==0)
            {
                strcpy(words[Cnt],term);
                Cnt++;
            }
        
    }
    struct Lnode *p;
    p = (struct Lnode *)malloc(sizeof(struct Lnode));
    strcpy(p->term,term);
    p -> next = L;
    return p;
}
struct Lnode *L_minus(struct Lnode *L,char *term)
{
    struct Lnode *p ;
    struct Lnode *prev;
    if(strcmp(L->term,term)==0)
    {
        p = L->next;
        return p;
    }
    prev=L;
    p=L->next;
    while(p)
    {
        if(strcmp(p->term,term)==0)
        {
            prev->next=p->next;
            free(p);
            return L;
        }
        prev = p;
        p = p->next;
    }
    return NULL;
}
void L_print(struct Lnode *L)
{
    int word_cnt[100];
    memset(word_cnt,0,sizeof(word_cnt));
    struct Lnode *p;
    for(int i=0;i<Cnt;i++)
    {
        p = L;
        while(p)
        {
            if(strcmp(p->term,words[i])==0)
            {
                word_cnt[i]++;
            }
            p = p ->next;
        }
    }
    for(int i=0;i<Cnt;i++)
    {
        printf("%s: %d\n",words[i],word_cnt[i]);
    }
}

int main()
{
    char line[1024];
    struct Lnode *termlist = NULL;

    while(fgets(line,1024,stdin)!=NULL)
    {
        int len=strlen(line);
        if(line[len-1]=='\n')   line[len-1]='\0';
        if(line[0]!='-')
        {
                termlist = L_Added(termlist,line);
        }
        if(line[0]=='-')
        {
                termlist = L_minus(termlist,line+1);
        }
    }
    L_print(termlist);


    return 0;
}
