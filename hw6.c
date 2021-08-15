#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int cmp(const void *p,const void *q)
{
    // int**x=(int**)p;
    // int**y=(int**)q;

    // return x>y;

    int x = ((int *)p)[0];
    int y = ((int *)q)[0];
    return x < y;
}

struct tnode{
    char term[256];
    int cnt;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *insert(struct tnode *tree,char *term)
{
    struct tnode *p;
    if(tree == NULL)
    {
        p = (struct tnode*)malloc(sizeof(struct tnode));
        strcpy(p->term,term);
        p->cnt=1;
        p->left=NULL;
        p->right=NULL;
        return p;
    }
    int c =strcmp(tree->term,term);
    if(c>0)
    {
        tree->left=insert(tree->left,term);
    }
    else if(c<0)
    {
        tree->right=insert(tree->right,term);
    }

    return tree;
}

struct tnode *check(struct tnode *tree,char *term)
{
    if(tree==NULL)
    {
        return NULL;
    }
    int c =strcmp(tree->term,term);
    if(c==0)  return tree;
    else if(c<0)
    {
          return check(tree->right,term);
    }
    else if(c>0)
    {
         return check(tree->left,term);
    }

    return NULL;
}

void inorder(struct tnode *tree)
{
    if(tree==NULL)
    {
        return;
    }
    inorder(tree->left);
    printf("%d %s\n",tree->cnt,tree->term);
    inorder(tree->right);
}
int i = 0;
void inorder_char(struct tnode *tree,char word[][70])
{

    if(tree==NULL)
    {
        return;
    }
    inorder_char(tree->left,word);
    strcpy(word[i++],tree->term);
    inorder_char(tree->right,word);
}

void inorder_int(struct tnode *tree,int Cnt[][2])
{

    if(tree==NULL)
    {
        return;
    }
    inorder_int(tree->left,Cnt);
    Cnt[i][0] = tree->cnt;
    Cnt[i][1] = i;
    i++;
   inorder_int(tree->right,Cnt);
}


int main()
{
    char line[1024];
    char word[1200][70];
    int Cnt[1200][2];
    int cnt=0;
    struct tnode *tree = NULL;
    struct tnode *ptr;
    while(fgets(line,1024,stdin)!=NULL)
    {
        int len = strlen(line);
        if(line[len-1]=='\n')
        {
            line[len-1]='\0';
        }
        ptr=check(tree,line);
        if(ptr==NULL && line[0]!='-')
        {
            tree = insert(tree,line);
            cnt++;
        }
        else if(ptr!=NULL && line[0]!='-')
        {
            struct tnode *p = check(tree,line);
            p->cnt++;
        }
        else if(line[0]=='-')
        {
            struct tnode *p = check(tree,(line+1));
            p->cnt--;
        }
    }
    printf("Inorder traversal:\n");
    inorder(tree);
    printf("\n");
    printf("Count sorting:\n");
    i = 0;
    inorder_char(tree,word);
    i = 0;
    inorder_int(tree,Cnt);
    qsort(Cnt,cnt,sizeof(int)*2,cmp);
    for(int i=0;i<cnt;i++)
    {
       //printf("%s\n",word[i]);
       printf("%d %s\n",Cnt[i][0],word[Cnt[i][1]]);
       //printf("%s\n", word[Cnt[i][1]]);
    }
    free(tree);
    return 0;
}