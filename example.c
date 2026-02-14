#include <math.h>
#include <stdio.h>
#include "variant.h"

typedef double Ok;
typedef const char* Error;
VARIANT_DEFINE(Result, Ok, Error);

Ok unwrap_or(const Result result, const Ok alt) {
  switch (result.tag) {
    case VARIANT_TAG(Result, Ok): {
      return VARIANT_UNWRAP(result, Ok);
    } break;
    case VARIANT_TAG(Result, Error): {
      return alt;
    } break;
  }
}

Ok unwrap_or_else(const Result result, Ok (*const alt)(const Result)) {
  switch (result.tag) {
    case VARIANT_TAG(Result, Ok): {
      return VARIANT_UNWRAP(result, Ok);
    } break;
    case VARIANT_TAG(Result, Error): {
      return alt(result);
    } break;
  }
}

Result get_inverse(const double x) {
  return x != 0 ? VARIANT_WRAP(Result, Ok, 1 / x)
                : VARIANT_WRAP(Result, Error, "x is 0");
}

void print_inverse(const double x) {
  const Result result = get_inverse(x);
  switch (result.tag) {
    case VARIANT_TAG(Result, Ok): {  // ok
      printf("%f\n", VARIANT_UNWRAP(result, Ok));
    } break;
    case VARIANT_TAG(Result, Error): {  // error
      printf("%s\n", VARIANT_UNWRAP(result, Error));
    } break;
  }
}

int main() {
  print_inverse(57.45);
  print_inverse(0.0);

  return 0;
}
