/*
 * Filename: testcountChars.c
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/14/2019
 * Sources of Help: None
 */ 

#include <stdio.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for countChars.c
 *
 * void countChars( unsigned char counts[], const char * word )
 *
 * Counts occurences of each character in word and stores the in counts, 
 * counting the number of each character in the word.
 *
 * Returns nothing, but counts should be populated with the results. 
 */
void testcountChars1() {

  /* Setting up function call */
  unsigned char counts[ALPHABET_SIZE];
  const char * word = "abbZ";

  /* Call function */
  countChars( counts, word );

  /* Test all are in the correct place */
  TEST( counts[0] == 1 ); // a
  
  TEST( counts[1] == 2 ); // b

  TEST( counts[25] == 1 ); // z
  
  /* Test the rest are 0 */
  int i;
  for ( ; i < ALPHABET_SIZE ; i++ ) {
    if ( i != 0 && i != 1 && i != 25 ) {

      TEST( counts[i] == 0 );

    }
  }

}

void testcountChars2() {
  
  /* Setting up function call */
  unsigned char counts[ALPHABET_SIZE];
  const char * nullWord = '\0';
  
  /* Call function */
  countChars( counts, nullWord );
  
  /* Test all counts[i] is 0 */
  int i = 0;
  for ( ; i < ALPHABET_SIZE ; i++ ) {

    TEST( counts[i] == 0 );

  }

}

void testcountChars3() {
  
  /* Setting up function call */
  unsigned char counts[ALPHABET_SIZE];
  const char * allSameLetter = "ccccCCCC";
  
  /* Call function */
  countChars( counts, allSameLetter );
  
  /* Test all counts of c is right */
  TEST( counts[2] = 8 );
  
  /* Test the rest are 0 */
  int i = 0;

  for ( ; i < ALPHABET_SIZE ; i++ ) {
    if ( i != 2 ) {

      TEST( counts[i] == 0 );

    }
  }

}

void testcountChars4() {
  
  /* Setting up function call */
  unsigned char counts[ALPHABET_SIZE];
  const char * longAllLetters = "abcdefghijklmnopqrstuvwxyz\
                                 abcdefghijklmnopqrstuvwxyz\
                                 abcdefghijklmnopqrstuvwxyz";
  
  /* Call function */
  countChars( counts, longAllLetters );
  
  /* Test every letter has three counts */
  int i = 0;

  for ( ; i < ALPHABET_SIZE ; i++ ) {

      TEST( counts[i] == 3 );

    }

}


int main( void ) {

  fprintf( stderr, "Running tests for countChars...\n" );
  fprintf( stderr, "Testing for string \"abbZ\"...\n" );
  testcountChars1();
  fprintf( stderr, "Testing for null word...\n" );
  testcountChars2();
  fprintf( stderr, "Testing for word with only one letter...\n" );
  testcountChars3();
  fprintf( stderr, "Testing for long word with all letters...\n" );
  testcountChars4();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
