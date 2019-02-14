#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stddef.h>
#include <locale.h>

//来自Zeal上的demo
//<lihf> 这个案例很好地说明了sscanf的灵活性
int main(void)
{
    int i, j;
    float x, y;
    char str1[10], str2[4];
    wchar_t warr[2];
    setlocale(LC_ALL, "en_US.utf8");
 
    char input[] = "25 54.32E-1 Thompson 56789 0123 56??";
    /* parse as follows:
       %d: an integer
       %f: a floating-point value
       %9s: a string of at most 9 non-whitespace characters
       
       <lihf> 这两个有意思，可以指定提取某一部分
       %2d: two-digit integer (digits 5 and 6)
       %f:  a floating-point value (digits 7, 8, 9)
       
       %*d: an integer which isn't stored anywhere
       
       <lihf> 下面几个格式可以学习一下，没有接触过
       ' ': all consecutive whitespace
       %3[0-9]: a string of at most 3 decimal digits (digits 5 and 6) <lihf>第一个数字限定了数量，第二个是字符集；
       %2lc: two wide characters, using multibyte to wide conversion  <lihf>第一个数字限定了数量，第二个是提取的类型*/
    int ret = sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]%2lc",
                     &i, &x, str1, &j, &y, str2, warr);
    
    printf("Converted %d fields:\ni = %d\nx = %f\nstr1 = %s\n"
           "j = %d\ny = %f\nstr2 = %s\n"
           "warr[0] = U+%x warr[1] = U+%x\n",
           ret, i, x, str1, j, y, str2, warr[0], warr[1]);
 
#ifdef __STDC_LIB_EXT1__
    int n = sscanf_s(input, "%d%f%s", &i, &x, str1, (rsize_t)sizeof str1);
    // writes 25 to i, 5.432 to x, the 9 bytes "thompson\0" to str1, and 3 to n.
#endif
}