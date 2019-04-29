/*
 * Filename: testgetHashcode.c
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/14/2019
 * Sources of Help: None
 */ 

#include <stdio.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for getHashcode.s
 *
 * Generates a hashcode from counts. 
 *
 * Returns the hashcode that corresponds to counts.	
 */
void testgetHashcode1() {

  /* Setting up function call */
  unsigned char counts[ALPHABET_SIZE];

  /* Setting up values for "abbZ" */
  counts[0] = 1;
  counts[1] = 2;
  counts[25] = 1;

  /* Put expected hash value in var hash */
  unsigned int hash = HASH_START_VAL;
  for ( int i = 0 ; i < ALPHABET_SIZE ; i++ ) {
    hash = hash * HASH_PRIME + counts[i];
  }

  /* Call getHashcode, return to hashTest */
  unsigned int hashTest = getHashcode( counts );

  /* Test value of hash */
  TEST( hashTest == hash );
  
}

void testgetHashcode2() {

  /* Setting up function call */
  unsigned char counts[ALPHABET_SIZE];

  /* Setting up values for "abcdefghijklmnopqrstuvwxyz" */
  for ( int i = 0 ; i < ALPHABET_SIZE ; i++ ) {
    counts[i] = 1;
  }

  /* Put expected hash value in var hash */
  unsigned int hash = HASH_START_VAL;
  for ( int i = 0 ; i < ALPHABET_SIZE ; i++ ) {
    hash = hash * HASH_PRIME + counts[i];
  }

  /* Call getHashcode, return to hashTest */
  unsigned int hashTest = getHashcode( counts );
  
  /* Test value of hash */
  TEST( hashTest == hash );

}

void testgetHashcode3() {

  /* Setting up function call */
  unsigned char counts[ALPHABET_SIZE];

  /* Setting up values for "aaaaaaaaaaaaaaaaaaaaaaaaa..." */
  counts[0] = 333;

  /* Put expected hash value in var hash */
  unsigned int hash = HASH_START_VAL;
  for ( int i = 0 ; i < ALPHABET_SIZE ; i++ ) {
    hash = hash * HASH_PRIME + counts[i];
  }

  /* Call getHashcode, return to hashTest */
  unsigned int hashTest = getHashcode( counts );

  /* Test value of hash */
  TEST( hashTest == hash );

}

int main( void ) {

  fprintf( stderr, "Running tests for getHashcode...\n" );
  fprintf( stderr, "Getting hash for char array counted with \"abbZ\"\n" );
  testgetHashcode1();
  fprintf( stderr, "Getting hash for char array counted with \"abc...z\"\n" );
  testgetHashcode2();
  fprintf( stderr, "Getting hash for char array counted with \"aaaa...\"\n" );
  testgetHashcode3();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
