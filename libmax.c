#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libmax.h"

static void default_memory_handler() {
  fprintf(stderr, "Error: out of memory. Exiting.\n");
  exit(1);
}

static void default_access_handler() {
  fprintf(stderr, "Error: bad access. Exiting.\n");
  exit(1);
}

/* handles the various errors */
static error_handler outofmem_handler = default_memory_handler;
static error_handler bad_access_handler = default_access_handler;

void set_mem_out_handler(error_handler fhandler) {
  outofmem_handler = fhandler;
}

void set_bad_access_handler(error_handler fhandler) {
  bad_access_handler = fhandler;
}

void* xmalloc(size_t bytes) {
  void *to_return = malloc(bytes);

  if (to_return == NULL) {
    outofmem_handler();
  }

  return to_return;
}

void* xrealloc(void *ptr, size_t bytes) {
  ptr = realloc(ptr, bytes);

  if (ptr == NULL) {
    outofmem_handler();
  }

  return ptr;
}

vector make_n_vector(size_t bytes) {
  vector vec;

  vec.num_elements = 0;
  vec.table_size = 1;
  vec.elements = xmalloc(bytes);
  vec.element_size = bytes;

  return vec;
}

void insert_vector(void *data, vector *v) {
  if (! (v->num_elements < v->table_size)) {
    v->elements = xrealloc(v->elements, TABLE_CAPACITY_BYTES(v) * 2);
    memset((char*) v->elements + TABLE_CAPACITY_BYTES(v), 0, TABLE_CAPACITY_BYTES(v));
    v->table_size *= 2;
  }

  memcpy((char*) v->elements + POSITION_LEVEL_BYTES(v), data, v->element_size);
  v->num_elements++;
}

void delete_vector(size_t position, vector *v) {
  /* make sure this insertion position makes sense */
  if (! (position < v->num_elements)) {
    return;
  }

  size_t i = position;
  size_t j = position + 1;

  while (j < v->num_elements) {
    memcpy((char*) v->elements + TABLE_POSITION(i, v),
           (char*) v->elements + TABLE_POSITION(j, v),
           v->element_size);
    i++;
    j++;
  }

  v->num_elements--;
}

void access_vector(void *result, size_t position, vector *v) {
  if (! (position < v->num_elements)) {
    return;
  }

  memcpy(result, (char*) v->elements + TABLE_POSITION(position, v), v->element_size);
}

void* access_bytes(size_t pos, vector* v) {
  if (pos > v->num_elements - 1) {
    return NULL;
  }

  return (char*) v->elements + TABLE_POSITION(pos, v);
}
