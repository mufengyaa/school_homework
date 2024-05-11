#include <stdio.h>                                                        
  #include <stdlib.h>
  #include <unistd.h>
  int A; //全局未初始化变量
  int B = 0;//全局初始化为0的变量
 int C= 2;//全局初始化变量
 static int D;//全局静态未初始化变量
 static int E =0;//全局静态初始化为0的变量
 static int F= 4;//全局静态初始化变量
 const int G = 5;//全局常量
 const char H=6;
 int main(void)
 {    
     int a;//局部未初始化变量
     int b=0;//局部初始化为ø的变量
     int c=2;//局部初始化变量
     static int d;//局部静态未初始化变量
     static int e=0;//局部静态初始化为0的变量
	 static int f = 4;//局部静态初始化变量
     const int g =5;//局部常量
     char char1[] = "abcde";//局部字符数组
     char *cptr = "123456";//p在栈上，13456在常量区
     int *heap = malloc(sizeof(int)*4);//堆
     printf("PID is :%d\n\n", getpid());
     printf("int A           A_addr = %p\n",&A);
     printf("int B=0         B_addr = %p\n",&B);
     printf("int C=2          C_addr - %p\n",&C);
     printf("static int D            D_addr= %p\n",&D);
     printf("static int E=0          E_addr=%p\n",&E);                     
     printf("static int F =4         F_addr=%p\n",&F);
     printf("const int G=5           G_addr =%p\n",&G);
     printf("const char H=6          H_addr = %p\n",&H);
     printf("\n");
     printf("int a           a_addr = %p\n",&a);
     printf("int b=0         b_addr = %p\n",&b);
     printf("int c=2         c_addr = %p\n",&c);
     printf("static int d            d_addr=%p\n",&d);
     printf("static int e = 0            e_addr = %p\n",&e);
    printf("static int f=4          f_addr = %p\n",&f);
     printf("const int g=5           g_addr= %p\n",&g);
     printf("\n");
     printf("char char1[] = 'abcde'\t\t\tchar1_addr - %p\n", char1);
     printf("char char1[] = 'abcde'\t\t\t&char1_addr = %p\n", &char1);
     printf("char *cptr = '1'\t\t\tcptr_addr%p\n", &cptr);
     printf("value of the cptr\t\t\tcptr_value -0x%p\n", cptr);
     printf("value of %p\t\t\tvalue_0x%p - %d\n", cptr,cptr,*cptr);        
     printf("int* heap = malloc(sizeof(int)*4)\theap_addr = %p\n", heap);
     printf("int* heap = malloc(sizeof(int)*4)\t&heap_addr = %p\n", &heap);
     pause(); //程序结束运行之后再回收堆内存，方便观察堆的地址
     free(heap);
     return 0;
 }    
