/**
 *  utils.h
 *
 *  Contains constants and struct declarations with the function prototypes.
 *
 *  @author Daniel Nemergut
 *  CSIS 614 - Assignment 1
 */

#define PI 3.14159265
#define DEBUG 0

typedef struct {
  double r;
  double theta;
} v_struct;

/**
 *  Reads a CSV file and parses each line as a vector.
 *
 *  @param char* file_name: The name of the CSV file to parse.
 *  @param v_struct** p_vec_array_ptr: The vector struct to store the values.
 *
 *  @return int num_lines: The number of lines read.
 */
int readVect(char* file_name, v_struct** p_vec_array_ptr);

/**
 *  Calculates the X component of a vector given the radius and angle in degrees.
 *
 *  @param v_struct* p_vector: The vector within a struct to retrieve the values.
 *
 *  @return double x: The value of the X component.
 */
double x_component(v_struct* p_vector);

/**
 *  Calculates the Y component of a vector given the radius and angle in degrees.
 *
 *  @param v_struct* p_vector: The vector within a struct to retrieve the values.
 *
 *  @return double y: The value of the Y component.
 */
double y_component(v_struct* p_vector);

/**
 *  Calculates the length of a given string.
 *
 *  @param char* s: The string to be measured.
 *
 *  @return int length: The length of the string.
 */
int strlength(char* s);

/**
 *  Combines two strings into one.
 *
 *  @param char* s: The string to hold the concatenated ones.
 *  @param char* s1: The first string to be concatenated.
 *  @param char* s2: The second string to be concatenated.
 */
void strconcat(char* s, char* s1, char* s2);

/**
 *  Converts a double to a string with a specified number of decimal places.
 *
 *  @param char* str: The string to hold the converted one.
 *  @param double x: The double to be converted.
 *  @param int d: The number of decimal places to keep.
 */
void ftoa(char* str, double x, int d);
