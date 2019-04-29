/*
 * Filename: testanagramCmp.c
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */

#include "pa3.h"
#include "test.h"
#include <stdio.h>

/*
 * Unit Test for anagramCmp.s
 *
 * int anagramCmp( const void * p1, const void * p2 );
 *
 * Compares two anagrams, first by hashcode, then by counts (as a tie-breaker).
 *
 * Returns -1 if anagram p1 has a smaller hashcode than anagram p2
 *         -1 if anagram p1 has the same hashcode but smaller countsCmp result
 *                than anagram p2
 *         +1 if anagram p1 has a larger hashcode than anagram p2
 *         +1 if anagram p1 has the same hashcode but larger countsCmp result
 *                than anagram p2
 *          0 if anagram p1 has the same hashcode and counts as anagram p2
 */
void testanagramCmp() {

  /* Create two anagrams to test with */
  anagram_t anagram1;
  anagram_t anagram2;

  /* Start with all the letter counts at zero */
  for( int i = 0 ; i < ALPHABET_SIZE ; i++ ){
    anagram1.counts[i] = (unsigned char)0;
    anagram2.counts[i] = (unsigned char)0;
  }


  /* Test when two anagrams are the same */
  anagram1.hashcode = 12;
  anagram2.hashcode = 12;
  anagram1.counts[12] = (unsigned char)12;
  anagram2.counts[12] = (unsigned char)12;

  TEST( anagramCmp( &anagram1, &anagram2 ) == 0 );

  /* Test when first anagram has smaller hashcode */
  anagram1.hashcode = 11;

  TEST( anagramCmp( &anagram1, &anagram2 ) == -1 );

  /* Test when first anagram has larger hashcode */
  anagram2.hashcode = 9;

  TEST( anagramCmp( &anagram1, &anagram2 ) == 1 );

  /* Test when same hashcode, but first anagram has smaller countsCmp */
  anagram2.hashcode = 11;
  anagram1.counts[12] = (unsigned char)1;
  
  TEST( anagramCmp( &anagram1, &anagram2 ) == -1 );

  /* Test when same hashcode, but first anagram has smaller countsCmp */
  anagram1.counts[12] = (unsigned char)22;

  TEST( anagramCmp( &anagram1, &anagram2 ) == 1 );

}

int main() {

  fprintf( stderr, "Running tests for anagramCmp...\n" );
  testanagramCmp();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

} 
