/*
* Filename: countChars.c
* Author: Christopher Yeh
* UserId: cs30xfv
* Date: 2/14/2019
* Sources of help: 
*/

#include <stdio.h>
#include <strings.h>
#include <ctype.h>
#include "pa3.h"

/*
 * Function Name: countChars() 
 * Function Prototype: void countChars( unsigned char counts[], 
 *                                      const char * word );
 * Description: Counts occurences of each character in word and stores them
 *             in counts, counting the number of each character in the word.
 * Parameters: counts - Array will be passed counts[26]. Holds amount letters.
 *             word - The string we are counting.
 * Side Effects: None 
 * Error Conditions: word is null. Immediately return, counts should be all 0s.
 * Return Value: None, but counts now stores the counted characters.
 */ 

void countChars( unsigned char counts[], const char * word ) {

  /* Set local vars */
  int i = 0; // Index of array of 26
  int letter; // For counting number of occurences of letter

  /* Initialize all elements initially to 0 */
  for ( ; i < ALPHABET_SIZE ; i++ ) {
    counts[i] = 0;
  }
  
  if ( word != '\0' ) {
    i = 0; // Begin next loop
    /* Start counting characters per index */
    while ( word[i] != '\0' ) {
      if ( tolower(word[i]) >= 'a' && tolower( word[i] ) <= 'z' ) {
        letter = tolower( word[i] ) - 'a';
        counts[letter]++;
      }
      i++;
   }
  }

}
