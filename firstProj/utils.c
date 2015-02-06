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
#include <stdio.h>

#include "utils.h"


int readVect(char* file_name, v_struct** p_vec_array_ptr) {
  int filedesc;
  int filedesc2;
  int numlines = 0;
  int charcount = 0;

  char current[1];
  char store[10];
  char errmsg[100] = "There was an error opening ";

  filedesc = open(file_name, O_RDONLY);

  if(filedesc < 0) {
    strconcat(errmsg, errmsg, file_name);
    strconcat(errmsg, errmsg, "\n");
    write(2, errmsg, strlength(errmsg));
  }

  // Read through the file once to construct p_vec_array
  while(read(filedesc, current, 1) > 0) {
    if(*current == '\n') {
      numlines++;
    }
  }

  // Create p_vec_array
  *p_vec_array_ptr = (v_struct*)malloc(numlines * sizeof(v_struct));

  // Reset the file for reading
  close(filedesc);
  filedesc2 = open(file_name, O_RDONLY);

  if(filedesc2 < 0) {
    strconcat(errmsg, errmsg, file_name);
    strconcat(errmsg, errmsg, "\n");
    write(2, errmsg, strlength(errmsg));
  }

  // Read each character until a comma or newline is hit and then store it
  while(read(filedesc2, current, 1) > 0) {
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

      // Use next v_struct
      (*p_vec_array_ptr)++;
      charcount = 0;
    } else if(*current == ' ') {
      // Skip spaces
      continue;
    } else {
      store[charcount] = *current;
      charcount++;
    }
  }

  close(filedesc2);

  // Store final direction before EOF
  (**p_vec_array_ptr).theta = atof(store);

  // Ensure direction is -360 < theta < 360
  if((**p_vec_array_ptr).theta < -360) {
    (**p_vec_array_ptr).theta += 360;
  } else if((**p_vec_array_ptr).theta > 360) {
    (**p_vec_array_ptr).theta -= 360;
  }

  // Reset the pointer location
  (*p_vec_array_ptr) -= numlines;

  return numlines;
}

double x_component(v_struct* p_vector) {
  return (*p_vector).r * cos(degtorad((*p_vector).theta));
}

double y_component(v_struct* p_vector) {
  return (*p_vector).r * sin(degtorad((*p_vector).theta));
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

void ftoa(char* str, double x) {
  sprintf(str, "%.2lf", x);

  return;
}

double degtorad(double degrees) {
  double radians = degrees * M_PI / 180.0;

  return radians;
}
