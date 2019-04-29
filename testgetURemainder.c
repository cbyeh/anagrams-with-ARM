/*
 * Filename: testgetURemainder.c
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/15/2019
 * Sources of Help: None
 */ 

#include <stdio.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for getURemainder.s
 * 
 * int getURemainder( int dividend, int divisor);
 *
 * Returns an unsigned remainder given dividend an divisor
 */
void testgetURemainder() {

  unsigned int dividend = 7;
  unsigned int divisor = 5;

  /* Call function, store in uRemainder */
  unsigned int uRemainder = getURemainder( dividend, divisor );
  
  /* Test for a standard unsigned division */
  TEST( uRemainder == 2 );

  /* Test for a standard unsigned division with no remainder */
  TEST( getURemainder( 10, 2 ) == 0 );
  
  /* Test for case where dividend = divisor */
  TEST( getURemainder( 5, 5 ) == 0 );

  /* Test for case where dividend is negative */
  TEST( getURemainder( -5, 4 ) == 3 );

  /* Test for case where divisor is negative */
  TEST( getURemainder( 5, -4 ) == 5 );

}


int main( void ) {

  fprintf( stderr, "Running tests for countChars...\n" );
  testgetURemainder();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
