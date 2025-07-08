#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  void* data;
  size_t elem_size;
  size_t len;
  size_t cap;
} da;

da* da_new(size_t elem_size) {
  da* dynarr = malloc(sizeof(da));

  dynarr->data = malloc(elem_size);
  dynarr->elem_size = elem_size;
  dynarr->len = 0;
  dynarr->cap = 1;

  return dynarr;
}

void da_push(da* dynarr, void* elem) {
  if (dynarr->len == dynarr->cap) {
    dynarr->cap *= 2;
    dynarr->data = realloc(dynarr->data, dynarr->elem_size * dynarr->cap);
  }

  memcpy(dynarr->data + dynarr->elem_size * dynarr->len++, elem, dynarr->elem_size);
}

void* da_at(da* dynarr, size_t i) {
  return dynarr->data + dynarr->elem_size * i;
}

int main() {
  da* dynarr = da_new(sizeof(int));

  char* num1 = 123;
  char* num2 = 456;
  char* num3 = 789;

  da_push(dynarr, &num1);
  da_push(dynarr, &num2);
  da_push(dynarr, &num3);

  for (size_t i = 0; i < dynarr->len; i++)
    printf("elem %d: %d\n", i, *(int*)da_at(dynarr, i));

  printf("\nlen: %d; cap: %d\n\n", dynarr->len, dynarr->cap);

  da* dynarr2 = da_new(sizeof(char*));

  char* msg1 = "hello";
  char* msg2 = "world";
  char* msg3 = "test";

  da_push(dynarr2, &msg1);
  da_push(dynarr2, &msg2);
  da_push(dynarr2, &msg3);

  for (size_t i = 0; i < dynarr2->len; i++)
    printf("elem %d: %s\n", i, *(char**)da_at(dynarr2, i));

  printf("\nlen: %d; cap: %d\n", dynarr2->len, dynarr2->cap);

  return 0;
}
