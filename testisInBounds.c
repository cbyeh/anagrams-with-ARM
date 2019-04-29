/*
 * Filename: testisInBounds.c
 * Author: Christopher 
 * UserId: cs30xfv
 * Date: 1/23/2019
 * Sources of Help:
 */ 

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for isInBounds.s
 *
 * int isInBounds( int value, int minBound, int maxBound );
 *
 * Checks to see if value is within the bounds of minBound (inclusive)
 * to maxBound (inclusive).
 *
 * Returns -1 if minBound > maxBound.
 * Returns 1 if value is between minBound (inclusive) and maxBound (inclusive).
 * Returns 0 otherwise.
 */
void testisInBounds( ) {

  /* Test value in bounds */
  TEST( isInBounds( 1, 0, 2 ) == 1 );

  /* Test value in bounds */
  TEST( isInBounds( 0, 0, 1 ) == 1 );

  /* Test error with bound values */
  TEST( isInBounds( 0, 10, 4 ) == -1 );

  /* Test value is not in bounds */
  TEST( isInBounds( 5, 6, 10 ) == 0 );
  
}


int main( void ) {

  fprintf( stderr, "Running tests for isInBounds...\n" );
  testisInBounds();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
