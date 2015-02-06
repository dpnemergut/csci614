/**
 *  hw1.c
 *
 *  Includes custom functions and calls them.
 *
 *  @author Daniel Nemergut
 *  CSIS 614 - Assignment 1
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "utils.h"


/**
 *  Main function.
 *  Goes through the file provided in argv[1] and constructs vectors from it.
 *  Then prints the vectors and components in a readable format.
 *
 *  @param int argc The number of arguments passed to the program.
 *  @param char** argv The list of arguments passed to the program.
 *
 *  @return int The exit status of the program.
 */
int main(int argc, char** argv) {
  int i;
  int num_vecs;

  double x;
  double y;

  char str[50];

  v_struct* p_vec_array;

  num_vecs = readVect(argv[1], &p_vec_array);

  for(i=0; i<=num_vecs; i++) {
    write(2, "r = ", 4);
    ftoa(str, (*p_vec_array).r);
    write(2, str, strlength(str));

    write(2, ", theta = ", 10);
    ftoa(str, (*p_vec_array).theta);
    write(2, str, strlength(str));

    write(2, " degrees, theta = ", 18);
    ftoa(str, degtorad((*p_vec_array).theta));
    write(2, str, strlength(str));

    write(2, " radians, x_comp = ", 19);
    x = x_component(p_vec_array);
    ftoa(str, x);
    write(2, str, strlength(str));

    write(2, ", y_comp = ", 11);
    y = y_component(p_vec_array);
    ftoa(str, y);
    strconcat(str, str, "\n");
    write(2, str, strlength(str));

    p_vec_array++;
  }

  return 0;

}
