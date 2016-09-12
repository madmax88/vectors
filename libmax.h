#ifndef MLIB_H
#define MLIB_H

/* error handler typedef */
typedef void (*error_handler)();

/* vector structure */
struct vector {
  size_t num_elements;
  size_t table_size;
  size_t element_size;
  void *elements;
};

typedef struct vector vector;

/* sets the out of memory handler */
void set_mem_out_handler(error_handler handler);

/* allocates memory */
void* xmalloc(size_t bytes);

void* xrealloc(void *ptr, size_t bytes);

/* makes a vector */
vector make_n_vector(size_t bytes);

/* useful macro
 * This is the preferred way to create a vector
 * As an example, simply give the macro a type and it will return a vector
 * that can hold an arbitrary number of that type.
 *    e.g. MAKE_VECTOR(int);
 */
#define MAKE_VECTOR(type) make_n_vector(sizeof(type));

#define TABLE_CAPACITY_BYTES(v) (v->table_size * v->element_size)
#define POSITION_LEVEL_BYTES(v) (v->num_elements * v->element_size)
#define TABLE_POSITION(pos, v) (v->element_size * pos)

/* inserts into a vector */
void insert_vector(void *data, vector *v);

/* access vector */
void access_vector(void *result, size_t position, vector *v);

/* delete an element */
void delete_vector(size_t position, vector *v);

#define INSERT_ELEMENT(e, v) insert_vector(&e, &v)
#define ACCESS_ELEMENT(p, t, v) access_vector((void*) &t, p, &v)

#endif
                                   
