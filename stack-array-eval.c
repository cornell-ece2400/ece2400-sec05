
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void init_array( int* a, size_t size )
{
  for ( size_t i = 0; i < size; i++ )
    a[i] = rand() % 1000;
}

void init_parray( int** pa, int* a, size_t size )
{
  for ( size_t i = 0; i < size; i++ )
    pa[i] = &(a[i]);
}

int avg_array( int* a, size_t size )
{
  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Implement this function
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  return 0;
}

int avg_parray( int** pa, size_t size )
{
  //'''' ASSIGNMENt TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Implement this function
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  return 0;
}

int main( void )
{
  srand(99);

  // Run an experiment

  int x = 0;
  int y = 0;

  int array[1000];
  init_array( array, 1000 );

  int* parray[1000];
  init_parray( parray, array, 1000 );

  x = avg_array( array, 1000 );
  y = avg_parray( parray, 1000 );

  // Print averages

  printf(" avg_array = %d, avg_parray = %d \n", x, y );

  return 0;
}



