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
  int numlines = 0;
  int charcount = 0;

  char current[0];
  char store[10];
  char errmsg[100] = "There was an error opening ";

  filedesc = open(file_name, O_RDONLY);

  if(filedesc < 0) {
    strconcat(errmsg, errmsg, file_name);
    strconcat(errmsg, errmsg, "\n");
    write(2, errmsg, strlength(errmsg));
  }

  // Read through the file once to construct p_vec_array
  while(read(filedesc, current, 1) != 0) {
    if(*current == '\n') {
      numlines++;
    }
  }

  // Create p_vec_array
  *p_vec_array_ptr = (v_struct*)malloc(numlines * sizeof(v_struct));

  // Read each character until a comma or newline is hit and then store it
  while(read(filedesc, current, 1) != 0) {
    if(*current == ',') {
      // Store a magnitude
      (**p_vec_array_ptr).r = atof(store);
      charcount = 0;
    } else if(*current == '\n'){
      // Store a direction
      (**p_vec_array_ptr).theta = atof(store);

      // Ensure direction is -360 < theta < 360
      if((**p_vec_array_ptr).theta < -360) {
        (**p_vec_array_ptr).theta += 360;
      } else if((**p_vec_array_ptr).theta > 360) {
        (**p_vec_array_ptr).theta -= 360;
      }

      charcount = 0;
      numlines++;
    } else if(*current == ' ') {
      // Skip spaces
      continue;
    } else {
      store[charcount] = *current;
      charcount++;
    }
  }

  return numlines;
}

double x_component(v_struct* p_vector) {
  return 0.0;
}

double y_component(v_struct* p_vector) {
  return 0.0;
}

int strlength(char* s) {
  int length = 0;

  // Count all non-null characters
  while(*s != '\0') {
    length++;
    s++;
  }

  return length;
}

void strconcat(char* s, char* s1, char* s2) {
  // Put s1 into s
  while(*s1 != '\0') {
    *s = *s1;
    s++;
    s1++;
  }

  // Put s2 into s
  while(*s2 != '\0') {
    *s = *s2;
    s++;
    s2++;
  }

  *s = '\0';

  return;
}

void ftoa(char* str, double x, int d) {
  while(x >= 10) {
    x /= 10;
    d++;
  }

  while(d > 0) {
    *str = d;
    str++;
    write(2, str, 10);
    return;
    *str = (int)x % 10;
    x *= 10;
    str++;
    d--;
  }

  return;
}
