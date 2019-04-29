/*
 * Filename: testhashcodeCmp.c
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */ 

#include <stdio.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for hashcodeCmp.s
 *
 * int hashcodeCmp( const void * p1, const void * p2 );
 *
 * Takes two void pointers, but will be passed const anagram_t *
 * Compares the two, returning an int representing p1 same, smaller, or larger.
 * 
 * Returns -1 if p2 has a larger hashcode
 *         +1 if p1 has a larger hashcode
 *          0 if the two anagrams have the same hashcode
 */
void testhashcodeCmp() {

  /* Create two anagrams to test with */
  anagram_t anagram1;
  anagram_t anagram2;

  /* Test when two hashcodes are the same */
  anagram1.hashcode = 2222222222222222222222222222;
  anagram2.hashcode = 2222222222222222222222222222;

  TEST( hashcodeCmp( &anagram1, &anagram2 ) == 0 );

  /* Test when p1's hashcode > p2's hashcode */
  anagram1.hashcode = 2222222228;
  anagram2.hashcode = 2222222222;

  TEST( hashcodeCmp( &anagram1, &anagram2 ) == 1 );

  /* Test when p1's hashcode < p2's hashcode */
  anagram2.hashcode = 2222223333;

  TEST( hashcodeCmp( &anagram1, &anagram2 ) == -1 );
  
}


int main( void ) {

  fprintf( stderr, "Running tests for hashcodeCmp...\n" );
  testhashcodeCmp();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
