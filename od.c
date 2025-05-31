#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BYTES_PER_LINE 16

static void
octaldump (char *buf, ssize_t size)
{
  int i, j, d1, d2, d3, pos;
  int num = 0;
  unsigned char line[80 + 1], byte;

  for (i = 0; i < size; i++) {
    if (num == 0) {
      for (j = 0; j < 80; j++)
        line[j] = ' ';

      line[80] = '\0';
    }

    byte = (unsigned char)buf[i];

    d1 = byte / 64;
    d2 = (byte % 64) / 8;
    d3 = byte % 8;

    pos = num * 4;
    line[pos] = (unsigned char)('0' + d1);
    line[pos + 1] = (unsigned char)('0' + d2);
    line[pos + 2] = (unsigned char)('0' + d3);

    if (byte >= 32 && byte < 127)
      line[64 + num] = byte;
    else
      line[64 + num] = '.';

    num++;

    if (num == BYTES_PER_LINE) {
      (void)fprintf (stdout, "%s\n", line);
      num = 0;
    }
  }

  if (num > 0)
    (void)fprintf (stdout, "%s\n", line);
}

int
main (void)
{
  char *buffer;
  ssize_t ret;

  buffer = malloc (BYTES_PER_LINE);
  if (!buffer) {
    perror ("malloc");
    return EXIT_FAILURE;
  }

  while ((ret = read (0, buffer, BYTES_PER_LINE)) > 0)
    octaldump (buffer, ret);

  free (buffer);
  return EXIT_SUCCESS;
}
