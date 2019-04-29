/*
 * Filename: testcountsCmp.c
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */

#include <stdio.h>
#include "pa3.h"
#include <string.h>
#include "test.h"

/*
 * Unit Test for countsCmp.s
 *
 * int countsCmp( const void * p1, const void * p2 );
 *
 * Compares two counts[] arrays by a call to memcmp
 *
 * Returns the value of memcmp 
 */
void testcountsCmp() {

  /* Create two anagrams to test with */
  anagram_t anagram1;
  anagram_t anagram2;

  /* Start with all the letter counts at zero */
  for( int i = 0 ; i < ALPHABET_SIZE ; i++ ) {
    anagram1.counts[i] = (unsigned char)0;
    anagram2.counts[i] = (unsigned char)0;
  }

  TEST( countsCmp( &anagram1, &anagram2 ) == 0 );

  /* Test when one is empty, other is populated */
  anagram1.counts[12] = (unsigned char)12;

  TEST( countsCmp( &anagram1, &anagram2 ) == 
    memcmp( &anagram1.counts, &anagram2.counts, 26 ) );

  /* Test when two counts are the same */
  anagram2.counts[12] = (unsigned char)12;

  TEST( countsCmp( &anagram1, &anagram2 ) == 0 );
  
  /* Test when anagram1 > anagram2  */
  anagram1.counts[13] = (unsigned char)5;

  TEST( countsCmp( &anagram1, &anagram2 ) == 
    memcmp( &anagram1.counts, &anagram2.counts, 26 ) );

  /* Test when anagram1 < anagram2 */
  anagram2.counts[13] = (unsigned char)6;
  anagram2.counts[14] = (unsigned char)12;

  TEST( countsCmp( &anagram1, &anagram2 ) == 
    memcmp( &anagram1.counts, &anagram2.counts, 26 ) );

}

int main() {
  fprintf( stderr, "Running tests for countsCmp...\n" );
  testcountsCmp();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
} 
