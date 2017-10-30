/* 教材【例4.1】将压缩存储在一维数组 a中的4阶对称阵按矩阵格式输出 */
print(int a[])
{ int i,j;
  for(i=0;i<4;i++)
    { for(j=0;j<4;j++)
       if(i>=j) printf("%4d",a[i*(i+1)/2+j]);
       else printf("%4d",a[j*(j+1)/2+i]);
     printf("\n");
    }
 }


 main()
 { int a[10],i;
   printf("input 10 data:");
   for(i=0;i<10;i++)
    scanf("%d",a+i);
   print(a);
}