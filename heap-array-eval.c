
#include <sys/time.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <stdlib.h>
#include <stddef.h>

int* rand_array( size_t size )
{
  int* a = malloc( size * sizeof(int) );
  for ( size_t i = 0; i < size; i++ )
    a[i] = rand() % 1000;
  return a;
}

int avg_array( int* a, size_t size )
{
  int sum = 0;
  for ( size_t i = 0; i < size; i++ )
    sum += a[i];
  return sum / size;
}

int main( void )
{
  // Run many trials so we can average the run times. Within each trial,
  // run enough subtrials so that the total runtime of the trial is at
  // least a few seconds. This avoids precision issues with
  // gettimeofday().

  int ntrials    = 5;
  int nsubtrials = 1e5;

  double elapsed_avg = 0.0;

  for ( int i = 0; i < ntrials; i++ ) {

    // Track time using timers

    struct timeval start;
    struct timeval end;

    // Start tracking time

    gettimeofday( &start, NULL );

    // Run the experiment

    int x = 0;

    for ( int j = 0; j < nsubtrials; j++ ) {
      int* array = rand_array( 1000 );
      x = avg_array( array, 1000 );
    }

    // Stop tracking time

    gettimeofday( &end, NULL );

    // Calculate elapsed time

    double elapsed = ( end.tv_sec - start.tv_sec ) +
                   ( ( end.tv_usec - start.tv_usec ) / 1000000.0 );

    elapsed_avg += elapsed;

    printf( "Elapsed time for trial %d is %f\n", i, elapsed );

    // Print average

    printf(" avg_array = %d \n", x );
  }

  // Calculate average elapsed time per trial

  elapsed_avg = elapsed_avg / ntrials;

  printf( "Elapsed time (averaged) is %f\n", elapsed_avg );

  return 0;
}

