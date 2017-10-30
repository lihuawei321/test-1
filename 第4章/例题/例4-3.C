

 #define MAXSIZE  100         /* 定义三元顺序表的最大长度 */
 typedef int ElemType;
 
 typedef struct
 { int i;                     /* 行标 */
   int j;                     /* 列标 */
   ElemType e;                /* 非0元素值 */
 }tupletype;                  /* 三元组的数据类型 */    

 typedef struct
 { int rownum;
   int colnum;
   int nznum;
   int rpos[MAXSIZE];
   tupletype data[MAXSIZE];
 }table;

 
/* 写出输出以压缩方式存储的稀疏矩阵 */
 print(table *M)
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

  
/* 【例4.3】采用逻辑连接的三元组表存储矩阵，计算两个矩阵的乘积 */

void matrixmul(table *m, table *t, table *q)
{ int row,mrow,trow,qcol,qtemp[MAXSIZE],col,mcurrownz,tcurrownz,k;
  q->rownum=m->rownum; q->colnum=t->colnum; q->nznum=0;     /* 初始化 */
  if(m->nznum*t->nznum!=0)
  { for(mrow=0;mrow<m->rownum;mrow++)                       /* 处理m的每一行 */
    { for(k=0;k<q->colnum;k++)                              /* 当前各行累加器清零 */
        qtemp[k]=0;
      q->rpos[mrow]=q->nznum;
      if(mrow<m->rownum-1)
        mcurrownz=m->rpos[mrow+1];
      else mcurrownz=m->nznum;
      for(row=m->rpos[mrow];row<mcurrownz;row++)            /* 对当前行中每个非零元素 */
      { trow=m->data[row].j;                                /* 找到对应元在N中的行号 */
	if(trow<t->rownum-1)  tcurrownz=t->rpos[trow+1];
	else tcurrownz=t->nznum;
	for(col=t->rpos[trow]; col<tcurrownz;col++)
	{ qcol=t->data[col].j;                              /* 乘积元素在q中的列号 */
	  qtemp[qcol]+=m->data[row].e*t->data[col].e;
	}
      }
     for(qcol=0;qcol<q->colnum;qcol++)                      /* 压缩存储该行非零元 */
       if(qtemp[qcol]!=0)
       { q->data[q->nznum].i=mrow;
	 q->data[q->nznum].j=qcol;
	 q->data[q->nznum].e=qtemp[qcol];
         q->nznum++;
      }
    }
  }
}


 main()
 {
  table M,T,Q;                                               /* 以图4.10中的矩阵为例 */
  clrscr();
  M.rownum=3;
  M.colnum=4;
  M.nznum=4;
  M.data[0].i=0;M.data[0].j=0;M.data[0].e=3;
  M.data[1].i=0;M.data[1].j=3;M.data[1].e=5;
  M.data[2].i=1;M.data[2].j=1;M.data[2].e=-1;
  M.data[3].i=2;M.data[3].j=0;M.data[3].e=2;
  M.rpos[0]=0;M.rpos[1]=2;M.rpos[2]=3;;

  T.rownum=4;
  T.colnum=2;
  T.nznum=4;
  T.data[0].i=0;T.data[0].j=1;T.data[0].e=2;
  T.data[1].i=1;T.data[1].j=0;T.data[1].e=1;
  T.data[2].i=2;T.data[2].j=0;T.data[2].e=-2;
  T.data[3].i=2;T.data[3].j=1;T.data[3].e=4;
  T.rpos[0]=0;T.rpos[1]=1;T.rpos[2]=2;T.rpos[3]=4;
  printf("M=\n");
  print(&M);
  printf("\n");
  printf("N=\n");
  print(&T);
  printf("\n");
  matrixmul(&M,&T,&Q);
  printf("Q=\n");
  print(&Q);
 }