#include<stdio.h>
#include<string.h>

//定义一个获取next数组的函数，便于KMP算法中模式串与主串值不匹配的情况，能够快速有效的移动模式串到有效位置。
void getnext(char *T,int *next)
{
    
    next[0]=-1;
    //定义j初始值为指向模式串T的第一个字符。
    int i = 0;
    // -模式串指针j处在最左端位置，无法继续右移，需要移动一位主串，故使用-1来表示。k就是用来表示j回溯时的位置即next[k].
    int j = -1;
    //循环下标i不超过模式串T的长度
    while(i<strlen(T))
    {
        //指针i指向第一个字符或者回溯点的值T[j]与当前i指向的值相等，就会触发next[i+1] == next[i] + 1，而变量j就是表示i下一个移动点next[i];
        if (j==-1 || T[i]==T[j])
        {
            //也可以写成next[i+1]=j+1;i++;j++;
            next[++i] = ++j;
            
        }
        else
        //如果变量i不是在第一个字符或者T[I]与T[J]不相等，表示模式串j指向的值与主串不相等，此时就需要移动到下一个回溯值next[j]了。
        {
            j = next[j];
        }
    }
}
//定义KMP算法
int KMP(char *S,char *T)
{
    //初始化next方便调用getnext函数，100只是一个数组表示，可以任意修改，但是要保证大于主串的长度。
    int next[100];
    //调用next函数
    getnext(T,next);
    //对主串变量i和模式串变量j进行初始化，定义为1开始是为了防止第一个字符T[0]就与S[0]不相等的情况。
    int i=1;
    int j=1;
    //保证下标i和j不超过各自字符串的长度。
    while (i<=strlen(S) && j<=strlen(T))
    {
        //j==0:代表模式串的第一个字符就和指针i指向的字符不相等；或者S[i-1]==T[j-1],如果对应位置字符相等，指向当前测试的两个指针下标i和j都向后移
        if (j==0 || S[i-1] == T[j-1])
        {
            i++;
            j++;
        }
        //如果两者不匹配或不是首位字符，保持i位置不变，改变j位置，将j回溯到next[j]的位置
        else
        {
            j = next[j];
        }
    }
    //判断跳出循环后的j值是否大于或等于模式串的长度，如果大于则表示完全匹配返回i-j；如果小于则表示匹配未完成返回-1.
    //注意:由于字符串的长度输出可能涉及到‘\0’，所以尽量选择大于等于来避免运行失败。
    if (j>=strlen(T))
    //返回i-j表示模式串首位字符与主串匹配时的索引值。
        return i-j;
    else
        return -1;
}
//定义main函数，调用KMP算法函数，运行程序启动。
int main()
{
    //定义两个字符串
    char s[] = "helloworld!";
    char t[] = "or";
    //调用KMP函数并赋值于变量res便于输出
    int res = KMP(s,t);
    if (res !=-1)
        printf("模式串存在于主串的下标为:%d。",res);
    else
        printf("模式串不存在于主串中!");
}