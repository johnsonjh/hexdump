#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void
hexdump(char *buf, ssize_t size)
{
  int  num = 0;
  char ch  = 0;
  char s[80 + 1];

  for (int i = 0; i < size; i++)
    {
      if (num == 0)
        {
          for (int j = 0; j < 80; j++)
              s[j] = ' ';
          s[80] = 0;
        }

      s[num * 3] =
          (ch = ((buf[i] >> 4) & 0x0f)) > 9
              ? ch + 'a' - 10
              : ch + '0';

      s[num * 3 + 1] =
          (ch =  (buf[i] & 0x0f)) > 9
              ? ch + 'a' - 10
              : ch + '0';

      if (buf[i] < 0x7f && buf[i] > ' ')
          s[num + 60] = buf[i];
      else
          s[num + 60] = '.';

      if ((i + 1) % 20 == 0)
        {
          (void)fprintf(stdout, "%s\n", s);
          num = 0;
        }
      else
          num++;
    }

  if (num != 0)
      (void)fprintf(stdout, "%s\n", s);
}

#define BUFSIZE 20

int
main(void)
{
  char*   buffer;
  ssize_t ret;

  buffer = malloc(BUFSIZE);

  while ((ret = read(0, buffer, BUFSIZE)) > 0)
      hexdump(buffer, ret);

  free(buffer);

  return EXIT_SUCCESS;
}
