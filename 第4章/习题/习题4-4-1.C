
#define N 4                /* ��4�׾���Ϊ�� */
typedef int ElemType;

/*ϰ��4-4-1 ��д�㷨,�������ʽ���������ѹ���洢��n�������Ǿ��� */
printj(ElemType a[],int n)
{ int i,j;
  for(i=0;i<n;i++)
    { for(j=0;j<n;j++)
       if(i>=j) printf("%4d",a[i*(i+1)/2+j]);
       else printf("%4d",a[n*(n+1)/2]);
     printf("\n");
    }
 }


 main()
 { ElemType a[N*(N+1)+1]={1,2,3,4,5,6,7,8,9,10,-1};

  printj(a,4);
  printf("\n");
}


