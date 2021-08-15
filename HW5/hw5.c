#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Lnode{
    char term[1024];
    struct Lnode *next;
};

char words[100][1024];
int wordcnt[100][2];
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
void L_print(char words[][1024],int wordcnt[][2])
{
    for(int i=0;i<Cnt;i++)
    {
        printf("%s: %d\n",words[wordcnt[i][1]],wordcnt[i][0]);
    }
}

void calculate(struct Lnode *L)
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
        wordcnt[i][0]=word_cnt[i];
    }
}

int cmp_asc(const void *a,const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    return c[0] - d[0];
}

int cmp_desc(const void *a,const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    return d[0] - c[0];
}

int main(int argc,char **argv)
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
    calculate(termlist);
    for(int i=0 ; i < Cnt ; i++ )
    {
        wordcnt[i][1] = i;
    }
    if(strcmp(*(argv+1),"asc")==0)
    {
        qsort(wordcnt,Cnt,sizeof(wordcnt[0]),cmp_asc);
    }
    if(strcmp(*(argv+1),"desc")==0)
    {
        qsort(wordcnt,Cnt,sizeof(wordcnt[0]),cmp_desc);
    }

    L_print(words,wordcnt);



    return 0;
}
