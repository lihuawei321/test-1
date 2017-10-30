
 /* 稀疏矩阵的压缩存储 三元顺序表 (只存放非0元素的行标,列标和值) */

 #define MAXSIZE  20             /* 定义三元顺序表的最大长度 */
 typedef int ElemType;           /* 三元组的数据类型 */
 typedef struct
 { int i;      /* 行标 */
   int j;      /* 列标 */
   ElemType e; /* 非0元素值 */
 }tupletype;
typedef struct
 { int rownum;
   int colnum;
   int nznum;
   tupletype data[MAXSIZE];
 }table;

 #define M1 6   /* 行数 */
 #define N1 7   /* 列数 */

/*从一个二维矩阵创建一个三元组*/
 void creatable(table *M,ElemType A[M1][N1])
 { int i,j;
   M->rownum=M1;
   M->colnum=N1;
   M->nznum=0;
   for(i=0;i<M1;i++)
     for(j=0;j<N1;j++)
       if(A[i][j]!=0)
       { M->data[M->nznum].i=i;
	 M->data[M->nznum].j=j;
	 M->data[M->nznum].e=A[i][j];
	 M->nznum++;
       }
 }



 /* 写出输出以压缩方式存储的稀疏矩阵 */
 list(table *M)
 {int i,j,k,e;
  for(i=0;i<M->rownum;i++)
   {
    for(j=0;j<M->colnum;j++)
     { e=0;
      for(k=0;k<M->nznum;k++)
	 if(i==M->data[k].i&&j==M->data[k].j)
	    {e=M->data[k].e;break;}
	 printf("%4d",e);
     }

    printf("\n");
   }
}


 /*习题4－4－5 已知矩阵A和B是两个按三元组形式存储的稀疏矩阵，编写算法，计算A-B */
sub(table *a,table *b,table *c)
{ int r=0,cl=0,k=0,v;
  if(a->rownum!=b->rownum||a->colnum!=b->colnum)
    return 0;
  c->rownum=a->rownum;
  c->colnum=a->colnum;
  while(r<a->nznum&&cl<b->nznum)                   
  { if(a->data[r].i==b->data[cl].i)                
    { if(a->data[r].j<b->data[cl].j)           /* 行标相等，且a的列标小，从a中取 */
      { c->data[k].i=a->data[r].i;
	c->data[k].j=a->data[r].j;
	c->data[k].e=a->data[r].e;
	k++;r++;
      }
      else if(a->data[r].j>b->data[cl].j)      /* 行标相等，且b的列标小，从b中取，元素值取相反数  */
	   { c->data[k].i=b->data[cl].i;
	     c->data[k].j=b->data[cl].j;
	     c->data[k].e=-(b->data[cl].e);
	     k++;cl++;
	   }
	   else
	   { v=a->data[r].e-b->data[cl].e;      
	     if(v!=0)                         /*  行标列标都相等,且元素差值不为0 */ 
	     { c->data[k].i=a->data[r].i;
	       c->data[k].j=a->data[r].j;
	       c->data[k].e=v;
	       k++;
             }
	     r++;cl++;
	  }
     }
     else if(a->data[r].i<b->data[cl].i)      /* 行标列标都不相等，且a的列标小，从a中取 */
	  { c->data[k].i=a->data[r].i;
	    c->data[k].j=a->data[r].j;
	    c->data[k].e=a->data[r].e;
	    k++;r++;
	  }
	  else                                /* 行标列标都不相等，且b的列标小，从b中取，元素值取相反数  */
	  { c->data[k].i=b->data[cl].i;
	    c->data[k].j=b->data[cl].j;
	    c->data[k].e=-(b->data[cl].e);
	    k++;cl++;
	   }
    }
    while(r<a->nznum)                         /* b已处理完，处理a中剩余部分 */
    { c->data[k].i=a->data[r].i;
      c->data[k].j=a->data[r].j;
      c->data[k].e=a->data[r].e;
      k++;r++;
    }
    while(cl<b->nznum)                        /* a已处理完，处理b中剩余部分 */
    { c->data[k].i=b->data[cl].i;
      c->data[k].j=b->data[cl].j;
      c->data[k].e=-(b->data[cl].e);
      k++;cl++;
    }
    c->nznum=k;
 }


 main()
 { table M,T,H;
   ElemType x;
   ElemType A[M1][N1]={{0,12,9,0,0,0,10},
		       {0,10,0,0,0,0,0},
		       {3,0,0,0,0,1,0},
		       {0,0,24,0,0,0,0},
		       {0,18,0,0,0,0,0},
		       {5,0,0,7,0,0,0}};

   ElemType B[M1][N1]={{10,12,9,0,0,0,0},
		       {0,0,0,0,0,0,0},
		       {3,10,0,0,0,1,0},
		       {0,0,24,0,0,0,0},
		       {0,18,0,0,0,0,10},
		       {5,0,0,7,10,10,10}};


  creatable(&M,A);
  printf("A=\n");
  list(&M);
  printf("\n");

  creatable(&T,B);
  printf("B=\n");
  list(&T);
  printf("\n");

  sub(&M,&T,&H);
  printf("A-B=\n");
  list(&H);
  printf("\n");
 }


