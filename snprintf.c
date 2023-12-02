#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned int u32;
typedef unsigned char u8;

/*
function prototype:
   int snprintf ( char * str, size_t size, const char * format, ... );

parameters:
   str -- 目标字符串，用于存储格式化后的字符串的字符数组的指针。
   size -- 字符数组的大小。
   format -- 格式化字符串。
   ... -- 可变参数，可变数量的参数根据 format 中的格式化指令进行格式化。

返回值：
   写入成功：返回值为可变参数的实际长度，不一定是实际写入的长度
   写入失败：-1

注意：
snprintf() 函数返回的字符数并不包括字符串结尾的空字符 \0，因此如果需要将输出结果作为一个字符串使用，则需要在缓冲区的末尾添加一个空字符 \0
*/

#define LEN1 20
#define LEN2 4
int main()
{
   {
      char buffer[LEN1];
      char* s1 = "first";
      char* s2 = "second";
      u32 temp32=0xF10C;
      // example1
      int ret = snprintf(buffer, sizeof(buffer), "str1:%s str2 %s", s1,s2); //

      // 输出 buffer及字符数
      printf("string:\n%s\n character count = %d\n", buffer, ret);

      for(int i=0;i<LEN1;i++){
         //printf("buffer[%d]=%x\n",i,buffer[i]);
      }
   }
   {
      char buffer[LEN2];
      u32 temp32=0xF10C;
      // example1
      int ret = snprintf(buffer, sizeof(buffer), "%X", s1,s2); //

      // 输出 buffer及字符数
      printf("string:\n%s\n character count = %d\n", buffer, ret);

      for(int i=0;i<LEN2;i++){
         printf("buffer[%d]=%x\n",i,buffer[i]);
      }
   }
   return 0;
}