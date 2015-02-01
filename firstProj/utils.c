/**
 *  utils.c
 *
 *  Loads system libraries and implements function prototypes.
 *
 *  @author Daniel Nemergut
 *  CSIS 614 - Assignment 1
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"


int readVect(char* file_name, v_struct** p_vec_array_ptr) {
  int filedesc;
  char errmsg[100] = "There was an error opening ";

  filedesc = open(file_name, O_RDONLY);

  if(filedesc < 0) {
    strconcat(errmsg, errmsg, file_name);
    strconcat(errmsg, errmsg, "\n");
    write(2, errmsg, strlength(errmsg));
  }

  return filedesc;
}

double x_component(v_struct* p_vector) {
  return 0.0;
}

double y_component(v_struct* p_vector) {
  return 0.0;
}

int strlength(char* s) {
  int length = 0;

  while(*s != '\0') {
    length++;
    s++;
  }

  return length;
}

void strconcat(char* s, char* s1, char* s2) {
  while(*s1 != '\0') {
    *s = *s1;
    s++;
    s1++;
  }

  while(*s2 != '\0') {
    *s = *s2;
    s++;
    s2++;
  }

  *s = '\0';

  return;
}
