#include "stdio.h"

#define M 3
#define N 4
#define Max ((M)>(N)?(M):(N))

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

/* 按链表格式输出十字链表 */

list1(manode *h)
{ manode *p,*q;
  p=h->tag.link;
  while(p!=h)
  { q=p->right;
    while(p!=q)
    { printf("%4d%4d%4d    ",q->row,q->col,q->tag.value);
      q=q->right;
    }
    printf("\n");
    p=p->tag.link;
  }
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



main()
{ int A[M][N]={{3,0,0,5},{0,-1,0,0},{2,0,0,0}};  /* 以图4.10中的矩阵M为例 */
  manode *h[5],*r;
  r=creacroslist(h,A);
  list(r);                                       /* 按矩阵格式输出 */

  printf("\n");

  list1(r);                                      /* 按矩链表式输出 */
  printf("\n");
}
