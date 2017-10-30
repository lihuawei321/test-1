
 /* 写出Ackermann函数的递归算法。Ackermann函数定义如下：
                       n+1                   m=0
           Ack(m，n)=  Ack(m-1,1)            m≠0,n=0
                       Ack(m-1,Ack(m,n-1))   m≠0,n≠0

*/

fun(int m,int n)
{ if(m==0) return (n+1);
  else if(n==0) return(fun(m-1,1));
       else return(fun(m-1,fun(m,n-1)));
}

main()
{ int m,n,f;
  printf("input m and n:");
  scanf("%d %d",&m,&n);
  f=fun(m,n);
  printf("Ack(%d,%d)=%d\n",m,n,f);
}