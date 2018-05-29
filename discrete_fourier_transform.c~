#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

struct complex {
  double re;
  double im;
};

struct matrix {
  size_t n, m;
  struct complex **self;
};

struct vector {
  size_t n;
  double *data;
};

struct even_odd_pair {
  size_t n;
  char computed;
  struct complex even, odd;
};

void free_matrix(struct matrix *to_free);

void free_vector(struct vector *to_free);

void free_even_odds(struct even_odd_pair *to_free);

struct matrix *create_matrix(const size_t n, const size_t m, const char IS_DFT_MATRIX);

struct vector *create_vector(const size_t n, const char initialize_with_random_values);

struct even_odd_pair *create_even_odds(const size_t n);

// struct vector *dft_vector(const size_t n);

void print_matrix(struct matrix *to_print, const char magnitude);

void print_vector(struct vector *to_print);

struct matrix  *DFT_vector(struct vector *input_vector);

void print_complex(struct complex *to_print, const char magnitude) {
  if(!magnitude) {
    printf("( %.3f + %.3fi ) ", to_print -> re, to_print -> im);
  } else {
    printf("%.3f ", sqrt(pow(to_print -> re, 2) + pow(to_print -> im, 2)));
  }
  
}

struct even_odd_pair *create_even_odds(const size_t n) {
  struct even_odd_pair *array = malloc(n * sizeof(struct even_odd_pair));
  for(register size_t i = 0; i < n; ++i) {
    array[i].even.re = 0;
    array[i].even.im = 0;
    array[i].odd.re = 0;
    array[i].odd.im = 0;
    array[i].computed = 0;
  }
  return array;
}

void free_even_odds(struct even_odd_pair *to_free) {
  free(to_free);
}

void free_vector(struct vector *to_free) {
  free(to_free -> data);
  free(to_free);
}



struct matrix *DFT_vector(struct vector *input_vector) {
  struct matrix *DFT_MATRIX = create_matrix(input_vector -> n, input_vector -> n, 1);
  if(!DFT_MATRIX) {
    printf("we could not initialize DFT_MATRIX, exiting with NULL.\n");
    return NULL;
  }
  printf("For input vector x: ");
  print_vector(input_vector);
  printf("We have the following DFT matrix:\n");
  print_matrix(DFT_MATRIX, 0);
  struct matrix *DFT_VECTOR = create_matrix(input_vector -> n, 1, 0);
  if(!DFT_VECTOR) {
    printf("couldn't initialize DFT_VECTOR, exiting with NULL\n");
    free_matrix(DFT_MATRIX);
    return NULL;
  }
  printf("computing... ");
  for(register size_t k = 0; k < input_vector -> n; ++k) {
    for(register size_t n = 0; n < input_vector -> n; ++n) {
      DFT_VECTOR -> self[k][0].re += (input_vector -> data[n]) * (DFT_MATRIX -> self[k][n].re); 
      DFT_VECTOR -> self[k][0].im += (input_vector -> data[n]) * (DFT_MATRIX -> self[k][n].im); 
    }
  }
  printf("done.\nRemoving DFT_MATRIX... ");
  free_matrix(DFT_MATRIX);
  printf("done\n");
  return DFT_VECTOR;
}

struct matrix *DFT_vector_radix(struct vector *input_vector) {
  size_t N = input_vector -> n;
  struct matrix *DFT_VECTOR = create_matrix(N, 1, 0);
  struct even_odd_pair *computed_vector = create_even_odds(N);
  double a = 0, b = 0, c = 0, d = 0;
  for(size_t k = 0; k < N; ++k) {
    /* essentially a while loop until the last value has been computed */
    if(computed_vector[N - 1].computed) {
      free(computed_vector);
      return DFT_VECTOR;
    }
    a = cos(2 * PI * k / N);
    b = sin(2 * PI * k / N);
    c = 0;
    d = 0;
    if(computed_vector[k].computed) {
      /* do stuff here */
      if(k + N/2 < N) {
	c = computed_vector[k].odd.re;
	d = computed_vector[k].odd.im;
	DFT_VECTOR -> self[k + N/2][0].re = computed_vector[k].even.re - (a * c - b * d);
	DFT_VECTOR -> self[k + N/2][0].im = computed_vector[k].odd.im - (b * c + a * d);
	computed_vector[k + N/2].even.re = computed_vector[k].even.re;
	computed_vector[k + N/2].even.im = computed_vector[k].even.im;
	computed_vector[k + N/2].odd.re = computed_vector[k].odd.re;
	computed_vector[k + N/2].odd.im = computed_vector[k].odd.im;
	computed_vector[k + N/2].computed = 1;
      }
    }
    
    /* should loop through and get every element from [0, N - 1] */
    printf("k: %lu even: ", k);
    for(register size_t i = 0; i < N; i += 2) {
      if(i != 0) {
	printf("+ ");
      }
      printf("(%.3f + %.3fi) ", input_vector -> data[i] * cos(4 * PI * i * k / N), input_vector -> data[i] * sin(4 * PI * i * k / N)); 
      computed_vector[k].even.re += input_vector -> data[i] * cos(4 * PI * i * k / N); /* f */
      computed_vector[k].even.im += input_vector -> data[i] * sin(4 * PI * i * k / N); /* g */
      if(i + 1 < N) {
        computed_vector[k].odd.re += input_vector -> data[i+1] * cos(4 * PI * i * k / N); /* c */
        computed_vector[k].odd.im += input_vector -> data[i+1] * sin(4 * PI * i * k / N); /* d */
      }
    }
    printf("= %.3f + %.3fi\n", computed_vector[k].even.re, computed_vector[k].even.im);
    c = computed_vector[k].odd.re;
    d = computed_vector[k].odd.im;
    computed_vector[k].computed = 1;
    DFT_VECTOR -> self[k][0].re = computed_vector[k].even.re + (a * c - b * d);
    DFT_VECTOR -> self[k][0].im = computed_vector[k].even.im + (b * c + a * d);
    if(k + N/2 < N) {
      DFT_VECTOR -> self[k + N/2][0].re = computed_vector[k].even.re - (a * c - b * d);
      DFT_VECTOR -> self[k + N/2][0].im = computed_vector[k].even.im - (b * c + a * d);
      computed_vector[k + N/2].even.re = computed_vector[k].even.re;
      computed_vector[k + N/2].even.im = computed_vector[k].even.im;
      computed_vector[k + N/2].odd.re = c;
      computed_vector[k + N/2].odd.im = d;
      computed_vector[k + N/2].computed = 1;
    }
  }
  free(computed_vector);
  return DFT_VECTOR;
}

struct vector *create_vector(const size_t n, const char initialize_with_random_values) {
  struct vector *to_create = malloc(sizeof(struct vector));
  if(to_create) {
    to_create -> n = n;
    to_create -> data = malloc(n * sizeof(double));
    if(to_create) {
      for(register size_t i = 0; i < n; ++i) {
	to_create -> data[i] = initialize_with_random_values ?
	  ((double)(rand() % 161))/10 : 0.0;
      }
    } else {
      free(to_create);
    }
  }
  return to_create;
}



struct matrix *create_matrix(const size_t n, const size_t m, const char DFT_MATRIX) {
  if(DFT_MATRIX && (n != m || !n || !m)) {
    printf("invalid dimensions %lu x %lu for DFT matrix\n", n, m);
    return NULL;
  } else {
    struct matrix *M = malloc(sizeof(struct matrix));
    if(M) {
      M -> n = n;
      M -> m = m;
      M -> self = malloc(n * sizeof(struct complex *));
      if(M -> self) {
	for(register size_t i = 0; i < n; ++i) {
	  M -> self[i] = malloc(m * sizeof(struct complex));
	  if(M -> self[i]) { /* if we successfully allocated a list of m complex numbers */
	    for(register size_t j = 0; j < m; ++j) {
	      /* initialize the values, since malloc does not clear */ 
	      // M -> self[i][j].computed = 0;
	      if(DFT_MATRIX) {
		(M -> self[i][j]).re = cos(2 * PI * i * j / n);
		(M -> self[i][j]).im = -sin(2 * PI * i * j / n);
	      } else {
		(M -> self[i][j]).re = 0.0;
		(M -> self[i][j]).im = 0.0;
	      }
	    }
	  } else { /* otherwise we remove that which we have allocated*/
	    for(register size_t k = i; k != ULONG_MAX; --i) {
	      free(M -> self[k]);
	    }
	    free(M -> self);
	    free(M);
	    M = NULL;
	  }
	}
      } else { /* otherwise we free the memory we tried to allocate*/
	free(M);
      }
    }
    return M;
  }
}

void free_matrix(struct matrix *to_free) {
  for(register size_t i = to_free -> n - 1; i != ULONG_MAX; --i) {
    free(to_free -> self[i]);
  }
  free(to_free -> self);
  free(to_free);
}

void print_matrix(struct matrix *to_print, const char magnitude) {
  for(size_t i = 0; i < to_print -> n; ++i) {
    printf("[ ");
    for(register size_t j = 0; j < to_print -> m; ++j) {
      
      print_complex(&(to_print -> self[i][j]), magnitude);
      //printf("( %4.1f + %4.1fi ) ", to_print -> self[i][j].re, to_print -> self[i][j].im);
    }
    printf("]\n");
  }
  printf("\n");
}

void print_vector(struct vector *to_print) {
  printf("< ");
  for(register size_t i = 0; i < to_print -> n; ++i) {
    printf("%.3f", to_print -> data[i]);
    if(i + 1 != to_print -> n) {
      printf(", ");
    }
  }
  printf(" >\n");
}


int main(void) {
  struct vector *my_input_vector = create_vector(4, 0);
  my_input_vector -> data [0] = 8;
  my_input_vector -> data [1] = 4;
  my_input_vector -> data [2] = 8;
  my_input_vector -> data [3] = 0;
  struct matrix *my_dft_vector = DFT_vector(my_input_vector), *radix_matrix = DFT_vector_radix(my_input_vector);
  printf("Matrix method: \n");
  print_matrix(my_dft_vector, 0);
  printf("Radix Vector: \n");
  print_matrix(radix_matrix, 0);
  free_matrix(radix_matrix);
  free_matrix(my_dft_vector);
  free_vector(my_input_vector);
  return 0;
}
