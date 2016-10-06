#ifndef GLOBAL_H_
#define GLOBAL_H_

const char *toBin(int x)
{
  static char b[9];
  b[0] = '\0';

  for (int z = 128; z > 0; z >>= 1)
  {
    strcat(b, ((x & z) == z) ? "1" : "0");
  }

  return b;
}

#endif /* GLOBAL_H_ */
