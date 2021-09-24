
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//------------------------------------------------------------------------
// strlen_
//------------------------------------------------------------------------
// Return the number of characters in the given string (str). The
// trailing underscore is to avoid a namespace conflict with the strlen
// function in the standard C library.

int strlen_( const char* str )
{
  int i = 0;
  while ( str[i] != '\0' )
    i++;
  return i;
}

//------------------------------------------------------------------------
// strdup_
//------------------------------------------------------------------------
// Duplicate the given string (str) by allocating a new string on the
// heap with the exact same contents. Return a pointer to this newly
// allocated string. The trailing underscore is to avoid a namespace
// conflict with the strdup function in the standard C library.

char* strdup_( const char* str )
{
  // Determine length of given string
  int len = strlen_( str );

  // Allocate new string on the heap
  char* new_str = malloc( (len+1) * sizeof(char) );

  // Copy all of the characters to new string
  for ( int i = 0; i < len; i++ )
    new_str[i] = str[i];

  // Add final null terminator delimitor!
  new_str[len] = '\0';

  return new_str;
}

//------------------------------------------------------------------------
// strcmp_v1
//------------------------------------------------------------------------
// Compare the two given strings (str0,str1). Return 0 if all characters
// match and zero if any characters do not match. Note that the strcmp
// function in the standard C library has different semantics.

int strcmp_v1( const char* str0, const char* str1 )
{
  // Determine length of given strings
  int len0 = strlen_( str0 );
  int len1 = strlen_( str1 );

  // If string lengths do not match, then strings to not match
  if ( len0 != len1 )
    return 0;

  // Check each character
  for ( int i = 0; i < len0; i++ ) {
    if ( str0[i] != str1[i] )
      return 0;
  }

  // Strings match!
  return 1;
}

int strcmp_v2( const char* str0, const char* str1 )
{
  int i = 0;
  int j = 0;

  // Iterate until reach first null terminator
  while ( (str0[i] != '\0') && (str1[j] != '\0') ) {
    if ( str0[i] != str1[j] )
      return 0;
    i++;
    j++;
  }

  // Final check to make sure final characters are equal
  if ( str0[i] != str1[j] )
    return 0;

  return 1;
}

//------------------------------------------------------------------------
// read_words
//------------------------------------------------------------------------
// Read words from a file with the given filename into an array of
// dynamically allocated strings. Each word in the file is duplicated on
// the heap and the corresponding pointer is stored in the given array of
// char pointers (words). max_num_words is the size of the words array.
// Reading the file should stop when either we reach the end of the file
// or we have read max_num_words. The function should return the number
// of words read from the file.

int read_words( char** words, int max_num_words, const char* filename )
{
  FILE* fp = fopen( filename, "r" );

  int  i = 0;
  char buf[256];
  while ( (i < max_num_words) && (fscanf( fp, "%s", buf ) != EOF) ) {
    words[i] = strdup_( strdup_( buf ) );
    i++;
  }

  fclose(fp);
  return i;
}

//------------------------------------------------------------------------
// contains_word
//------------------------------------------------------------------------
// Search the given array of words for the given word. Return 1 if the
// word is found, and 0 if the word is not found.

int contains_word( char** words, int* lens, int num_words, const char* word )
{
  for ( int i = 0; i < num_words; i++ ) {
    if ( strcmp_v1( words[i], word ) )
        return 1;
  }

  return 0;
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( void )
{
  // Read words from file

  char* words[1024];
  int num_words = read_words( words, 1024, "overview.txt" );

  int lens[1024];
  for ( int i = 0; i < num_words; i++ )
    lens[i] = strlen_( words[i] );

  // Setup the experiment

  int    result      = -1;
  int    ntrials     = 5;
  int    nsubtrials  = 1e5;
  double elapsed_avg = 0.0;

  for ( int i = 0; i < ntrials; i++ ) {

    // Start tracking time

    struct timeval start;
    gettimeofday( &start, NULL );

    // Run the experiment

    for ( int j = 0; j < nsubtrials; j++ ) {
      result = contains_word( words, lens, num_words, "flower" );
    }

    // Stop tracking time

    struct timeval end;
    gettimeofday( &end, NULL );

    // Calculate elapsed time

    double elapsed = ( end.tv_sec - start.tv_sec ) +
                     ( ( end.tv_usec - start.tv_usec ) / 1000000.0 );

    elapsed_avg += elapsed;

    printf( "Elapsed time for trial %d is %fs\n", i, elapsed );

  }

  // Calculate average elapsed time per trial

  elapsed_avg = elapsed_avg / ntrials;

  printf( "Average elapsed time is %fs\n", elapsed_avg );

  // Verify result

  if ( result == 0 )
    printf( "Verification passed\n" );
  else if ( result == 1 )
    printf( "Verification failed\n" );
  else
    printf( "Verification not run correctly\n" );

  // Every malloc must have a free!

  for ( int i = 0; i < num_words; i++ )
    free( words[i] );

  return 0;
}
