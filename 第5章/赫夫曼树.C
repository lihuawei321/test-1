/*��д�㷨�����������,��д������������*/
/* ���磬������ȨֵΪ w={5,29,7,8,14,23,3,11},n=8;*/
#include "string.h"
#include "stdio.h"
typedef struct
 {
  unsigned int weight;
  unsigned int parent,lchild,rchild;
 } HTNode,*Huffmantree;

typedef char **Huffmancode;




HuffmanCoding(Huffmantree HT,Huffmancode HC,int *w,int n)
{ int i,j,m,c,start,s1,s2,f,cdlen;
  Huffmantree p;
  char *cd;
  m=2*n-1;
  /*Ϊ�����������ٴ洢�ռ�*/
  HT=(Huffmantree)malloc((m+1)*sizeof(HTNode));
  /*Ϊ����������ǰn����㸳��ֵ*/
  for(p=HT,i=1;i<=n;i++) {p[i].weight=w[i];p[i].parent=0;p[i].lchild=0;p[i].rchild=0;}
  /*Ϊ���������ĺ�m-n����㸳��ֵ*/
  for(;i<=m;i++) {p[i].weight=0;p[i].parent=0;p[i].lchild=0;p[i].rchild=0;}
  for(i=n+1;i<=m;i++)
  { j=1;p=HT;
    while(j<=i-1&&p[j].parent!=0) j++;
    s1=j;
    while(j<=i-1)
    { if(p[j].parent==0&&p[j].weight<p[s1].weight) s1=j;
      j++;
    }
    p[s1].parent=i;
    j=1;p=HT;
    while(j<=i-1&&p[j].parent!=0) j++;
    s2=j;
    while(j<=i-1)
    { if(p[j].parent==0&&p[j].weight<p[s2].weight) s2=j;
      j++;
    }
    if(s1>s2)
    { j=s1;s1=s2;s2=j;}
    HT[s1].parent=i; HT[s2].parent=i;
    HT[i].lchild=s1; HT[i].rchild=s2;
    HT[i].weight=HT[s1].weight+HT[s2].weight;
  }
  HC=(Huffmancode)malloc((n+1)*sizeof(char *));
  cd=(char *)malloc(n*sizeof(char));
  cd[n-1]='\0';
  for(i=1;i<=n;i++)
  { start=n-1;
    for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
      if(HT[f].lchild==c) cd[--start]='0';
      else cd[--start]='1';
    HC[i]=(char *)malloc((n-start)*sizeof(char));
    strcpy(HC[i],cd+start);
  }
 

  printf("the create press:\n");    /* ��������������ɹ��� */
  printf("   NO  W   PA  LC  RC\n");  
  for(i=1;i<=m;i++)
    printf("%4d%4d%4d%4d%4d\n",i,p[i].weight,p[i].parent,p[i].lchild,p[i].rchild);
  getchar();
  

/*��д���������������㷨*/
/*free(HC);free(cd);*/
  HC=(Huffmancode)malloc((n+1)*sizeof(char *));
  j=m; cdlen=0;
  for(i=1;i<=m;i++) HT[i].weight=0;
  while(j)
  { if(HT[j].weight==0)
    { HT[j].weight=1;
      if(HT[j].lchild!=0)
      { j=HT[j].lchild;cd[cdlen++]='0';}
      else if(HT[j].rchild==0)
	   { cd[cdlen]='\0';
	     HC[j]=(char *)malloc((cdlen+1)*sizeof(char));
	     strcpy(HC[j],cd);
	   }
    }
    else if(HT[j].weight==1)
	 { HT[j].weight=2;
	   if(HT[j].rchild!=0)
	   { j=HT[j].rchild;cd[cdlen++]='1';}
	 }
	else
	{ HT[j].weight=0;j=HT[j].parent;cdlen--;}
   }
  

  printf("the huffman code are:\n");    /* ������������� */
  for(i=1;i<=n;i++)
  {  printf("%c   ",'A'+i-1);
    puts(HC[i]);
  }
  getchar();
}

main()
{ int w[]={0,5,29,7,8,14,23,3,11},n=8;   /* ������5.24��Ϊ�� */
  int i;
  Huffmantree HT=NULL;
  Huffmancode HC=NULL;
  HuffmanCoding(HT,HC,w,n);
}