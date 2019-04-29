/*
 * Filename: testassembleAnagram.c
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */ 

#include <stdio.h>
#include "pa3.h"
#include <string.h>
#include <stdlib.h>
#include "test.h"

/*
 * Unit Test for assembleAnagram.s
 *
 * void assembleAnagram( const char * originalWord, anagram_t * anagram );
 *
 * Assemble an anagram_t given a word, and a pointer to the
 * anagram being assembled*
 *
 * Returns nothing, but anagram will be assembled with originalWord,
 * counts, and hashcode
 */
void testassembleAnagram1( ) {

  /* Test for standard word "og" that is under 48 chars  */

  /* Setting up function call */
  const char originalWord[] = "og";
  anagram_t anagram;

  /* Call function */
  assembleAnagram( originalWord, &anagram );

  printf( "%s\n", originalWord );
  printf( "%s\n", anagram.originalWord );
  
  /* Test originalWord is the same */
  TEST( strncmp( originalWord, anagram.originalWord, 
                 strlen( anagram.originalWord ) ) == 0 );

  /* Test counts is correct */
  unsigned char ogCounts[26];
  countChars( ogCounts, originalWord );
  int i = 0;
  for ( ; i < ALPHABET_SIZE; i++ ) {

    TEST( ogCounts[i] == anagram.counts[i] );

  }

  /* Test hashcode is same */
  TEST( getHashcode( ogCounts ) == anagram.hashcode );

}

void testassembleAnagram2() {

  /* Test for word at 47 length */

  /* Setting up function call */
  const char originalWord[] =
    "Baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  anagram_t anagram;

  /* Call function */
  assembleAnagram( originalWord, &anagram );

  printf( "%s\n", originalWord );
  printf( "%s\n", anagram.originalWord );
  
  /* Test we have 47 length */
  TEST( strncmp( "Baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                anagram.originalWord, strlen( anagram.originalWord ) ) == 0 );

  /* Test counts is correct */
  unsigned char ogCounts[26];
  countChars( ogCounts, originalWord );
  int i = 0;
  for ( ; i < ALPHABET_SIZE; i++ ) {

    TEST( ogCounts[i] == anagram.counts[i] );

  }

  /* Test hashcode is same */
  TEST( getHashcode( ogCounts ) == anagram.hashcode );

}

void testassembleAnagram3() {

  /* Test for word at 48 length */

  /* Setting up function call */
  const char originalWord[] =
    "Baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  anagram_t anagram;

  /* Call function */
  assembleAnagram( originalWord, &anagram );

  printf( "%s\n", originalWord );
  printf( "%s\n", anagram.originalWord );
  
  /* Test we have 47 length */
  TEST( strncmp( "Baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                anagram.originalWord, strlen( anagram.originalWord ) ) == 0 );

  /* Test counts is correct */
  unsigned char ogCounts[26];
  countChars( ogCounts, originalWord );
  int i = 0;
  for ( ; i < ALPHABET_SIZE; i++ ) {

    TEST( ogCounts[i] == anagram.counts[i] );

  }

  /* Test hashcode is same */
  TEST( getHashcode( ogCounts ) == anagram.hashcode );

}

void testassembleAnagram4() {

  /* Test for word at 49 length */

  /* Setting up function call */
  const char originalWord[] =
    "Baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  anagram_t anagram;

  /* Call function */
  assembleAnagram( originalWord, &anagram );

  printf( "%s\n", originalWord );
  printf( "%s\n", anagram.originalWord );
  
  /* Test we have 47 length */
  TEST( strncmp( "Baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                anagram.originalWord, strlen( anagram.originalWord ) ) == 0 );

  /* Test counts is correct */
  unsigned char ogCounts[26];
  countChars( ogCounts, originalWord );
  int i = 0;
  for ( ; i < ALPHABET_SIZE; i++ ) {

    TEST( ogCounts[i] == anagram.counts[i] );

  }

  /* Test hashcode is same */
  TEST( getHashcode( ogCounts ) == anagram.hashcode );

}

int main( void ) {

  fprintf( stderr, "Running tests for assembleAnagram...\n" );
  fprintf( stderr, "Testing for standard string \"og\"...\n" );
  testassembleAnagram1();
  fprintf( stderr, "Testing for string of 47 length...\n" );
  testassembleAnagram2();
  fprintf( stderr, "Testing for string of 48 length...\n" );
  testassembleAnagram3();
  fprintf( stderr, "Testing for string of 49 length...\n" );
  testassembleAnagram4();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
