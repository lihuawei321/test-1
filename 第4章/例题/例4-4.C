#include "stdio.h"


#define M 3
#define N 4
#define Max ((M)>(N)?(M):(N))   /* 以3行4列矩阵为例 */

typedef struct mtxn
{ int row;
  int col;
  struct mtxn *right,*down;
  union
  {int value;
   struct mtxn *link;
  }tag;
}manode;                       /* 十字链表的结点类型定义 */



/* 从一个二维矩阵创建其十字链表表示 */
manode *creacroslist(manode *h[],int A[M][N])
{ int i,j;
  manode *p,*q;
  p=(manode *)malloc(sizeof(manode));
  h[0]=p;
  p->row=M;p->col=N;
  for(i=1;i<=Max;i++)
  { p=(manode *)malloc(sizeof(manode));
    p->row=p->col=-1;
    h[i]=p;h[i-1]->tag.link=p;
    p->down=p->right=p;
   }
   h[Max]->tag.link=h[0];
   for(i=0;i<M;i++)
       for(j=0;j<N;j++)
	 if(A[i][j]!=0)
	 { p=(manode *)malloc(sizeof(manode));
	   p->row=i;p->col=j;p->tag.value=A[i][j];
	   q=h[i+1];
	   while(q->right!=h[i+1]&&q->right->col<j)
	     q=q->right;
	   p->right=q->right;q->right=p;
	   q=h[j+1];
	   while(q->down!=h[j+1]&&q->down->row<i)
	     q=q->down;
	   p->down=q->down;q->down=p;
	 }
  return h[0];
}


/*  把采用十字链表存储的稀疏矩阵按矩阵格式输出  */
list(manode *h)
{ manode *p,*q;
  int i,j,e;
  p=h->tag.link;
  for(i=0;i<M;i++)
  { q=p->right;
    for(j=0;j<N;j++)
    { e=0;
      if(i==q->row&&j==q->col)
      { e=q->tag.value;
	q=q->right;
      }
      printf("%4d",e);
     }
    p=p->tag.link;
    printf("\n");
  }
}

/* 【例4.4】采用十字链表存储结构，设计实现矩阵加法的算法 */
manode *pred(manode *h[],int i,int j)
{ manode *p=h[j+1];
  while(p->down->col!=-1&&p->down->row<i-1)
    p=p->down;
  return p;
}
void matrixadd(manode *ha,manode *hb,manode *h[])
{ manode *p,*q,*ca,*cb,*pa,*pb,*qa;
  if(ha->row!=hb->row||ha->col!=hb->col)
   return ;
  ca=ha->tag.link;
  cb=hb->tag.link;
  do {
       pa=ca->right;
       pb=cb->right;
       qa=ca;
       while(pb->col!=-1)
	 if(pa->col!=-1&&pa->col<pb->col)
	 { qa=pa;pa=pa->right;}
	 else if(pa->col==-1||pa->col>pb->col)
	      { p=(manode *)malloc(sizeof(manode));
		p->row=pb->row;
		p->col=pb->col;
		p->tag.value=pb->tag.value;
		p->right=pa;
		qa->right=p;qa=p;q=pred(h,p->row,p->col);
		p->down=q->down;
		q->down=p;
		pb=pb->right;
	      }
	      else
	      { pa->tag.value+=pb->tag.value;
		if(pa->tag.value==0)
		{ qa->right=pa->right;
		  q=pred(h,pa->row,pa->col);
		  q->down=pa->down;
		  free(pa);
		}
		else qa=pa;
		pa=pa->right;pb=pb->right;
	    }
	    ca=ca->tag.link;
	    cb=cb->tag.link;
	 } while(ca->row==-1);
  }



main()
{ int A[M][N]={{1,0,0,2},{6,0,3,0},{0,0,2,4}};
  int B[M][N]={{1,0,0,2},{0,3,1,0},{5,0,1,0}};
  manode *h1[5],*h2[5],*r1,*r2;
  clrscr();

  r1=creacroslist(h1,A);
  printf("A=\n");
  list(r1);
  printf("\n");
  r2=creacroslist(h2,B);
  printf("B=\n");
  list(r2);
  printf("\n");
  matrixadd(r1,r2,h1);
  printf("A+B=\n");
  list(r1);
}
