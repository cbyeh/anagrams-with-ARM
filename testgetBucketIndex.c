/*
 * Filename: testgetBucketIndex.c
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */ 

#include <stdio.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for getBucketIndex.s
 *
 * unsigned int getBucketIndex( unsigned int hashcode, size_t tablesize );
 *
 * Returns the location in a queryTable given a hashcode and tablesize.
 * The location uses a call to getURemainder
 *
 * Returns the index in the hashtable of an anagram
 */
void testgetBucketIndex() {

  unsigned int hashcode = 2130705176;
  size_t tableSize = 1000;

  /* Call function, store in uRemainder */
  unsigned int bucketIndex = getBucketIndex( hashcode, tableSize );
  
  /* Test for a standard case */
  TEST( bucketIndex == 176 );
  
  /* Test for case where hashcode = tableSize */
  TEST( getBucketIndex( 2130705176, 2130705176 ) == 0 );

  /* Test for case where tableSize is small */
  TEST( getBucketIndex( 2130705176, 1 ) == 0 );
  
  /* Test case for where tableSize is bigger than hashcode */
  TEST( getBucketIndex( 2130705176, 3333333333 ) == 2130705176 ); 

}


int main( void ) {

  fprintf( stderr, "Running tests for countChars...\n" );
  testgetBucketIndex();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
