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
 *
 *  @param int argc The number of arguments passed to the program.
 *  @param char** argv The list of arguments passed to the program.
 *
 *  @return int The exit status of the program.
 */

int main(int argc, char** argv) {
  /*
   Steps to be performed
   	1. Define variables (including arrays)
	2. Using read() function in utils.h, read vectors defined in text file
		- the location of the text file (i.e. vectors.txt) must be defined in argv[1]
	3. Loop through array of vector structs and print to console:
	   - vector magnitude (using only 2 decimal places)
	   - vector direction (in radians using only 2 decimal places)
	   - vector direction (in degrees using only 2 decimal places)
	   - Using compute_x() function in utils.h, x component
             value (using only 2 decimal places)
	   - Using compute_y() function in utils.h, y component
             value (using only 2 decimal places) in the following format
		r = <value>, theta = <value> degrees, <value> radians, x_comp = <value>, y_comp = <value>

	     For example:
		r = 10.00, theta = 180.00 degrees, theta = 3.14 radians, x_comp = -10.00, y_comp = 0.00
  */

  int i;
  int num_vecs;
  v_struct* p_vec_array;

  num_vecs = readVect("vectors.tx", &p_vec_array);

  for(i=0; i<num_vecs; i++) {
    write(1, "YAY!\n", 5);
  }

  return 0;

}
