#define n 4
typedef int ElemType;

/*习题4-4-3 编写算法，将一个n阶矩阵A的元素从左上角开始按蛇形方式存储到一维数组B中。*/
 void func(int B[],int A[][n])
 { int i,j,k,m,g,gs;
   m=0;
   for(k=1;k<=2*n-1;k++)
   { if(k<n) gs=k;
     else gs=2*n-k;
     for(g=1;g<=gs;g++)
     { if(k%2==1)
       { i=gs-g;
	 j=g-1;
       }
       else
       { i=g-1;
	 j=gs-g;
       }
       if(k>n)
       { i=i+n-gs;
	 j=j+n-gs;
       }
       B[m]=A[i][j];m++;
     }
    }
  }





main()
{ ElemType A[n][n],B[n*n];
  int i,j;
  printf("input %d*%d maxtrix:\n",n,n);
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      scanf("%d",&A[i][j]);
  
  func(B,A);
  
  printf("array B:\n");
  for(i=0;i<n*n;i++)
   printf("%3d",B[i]);
}
