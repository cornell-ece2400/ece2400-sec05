
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

int main( void)
{
  int ntrials    = 5;
  int nsubtrials = 1e5;

  double elapsed_avg = 0.0;

  int x;
  int y;

  for ( int i = 0; i < ntrials; i++ ) {

    // Track time using timers

    struct timeval start;
    struct timeval end;

    // Start tracking time

    gettimeofday( &start, NULL );

    // Run the experiment

    for ( int j = 0; j < nsubtrials; j++ ) {

      int array[1000];
      init_array( array, 1000 );

      int* parray[1000];
      init_parray( parray, array, 1000 );

      x = avg_array( array, 1000 );
      y = avg_parray( parray, 1000 );

    }

    // Stop tracking time

    gettimeofday( &end, NULL );

    // Calculate elapsed time

    double elapsed = ( end.tv_sec - start.tv_sec ) +
                   ( ( end.tv_usec - start.tv_usec ) / 1000000.0 );

    elapsed_avg += elapsed;

    printf( "Elapsed time for trial %d is %f\n", i, elapsed );
  }

  // Calculate average elapsed time per trial

  elapsed_avg = elapsed_avg / ntrials;

  printf( "Elapsed time (averaged) is %f\n", elapsed_avg );

  // Print results

  printf(" avg_array = %d, avg_parray = %d \n", x, y );

  return 0;
}

