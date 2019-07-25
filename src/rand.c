#include <stdlib.h>

unsigned int rand_get(unsigned int modulo)
{
  return (rand() % modulo);
}