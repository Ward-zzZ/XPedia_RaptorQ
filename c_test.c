
#include <stdio.h>

union uu
{
  char ch;
  int n;
};

int main(int argc, char *argv[])
{
  union uu u1 = {1};
  printf("&u1=%p \n", &u1);
  if (u1.ch)
  {
    printf("u1.ch=%d  是小端序\n", u1.ch); //注意打印的是u1.ch的ASCII码值
  }
  else
  {
    printf("u1.ch=%d  是大端序\n", u1.ch);
  }

  return 0;
}
