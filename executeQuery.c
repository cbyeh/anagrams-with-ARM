/*
* Filename: executeQuery.c
* Author: Christopher Yeh
* UserId: cs30xfv
* Date: 2/23/2019
* Sources of help: None
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: executeQuery()
 * Function Prototype: int executeQuery( queryTable_t * queryTable,
 *                                       anagram_t * needle );
 * Description: The heart of the program, finding and printing the matching
 *             anagrams. Given the proverbial needle keyword, search the 
 *             proverbial haystack for a proverbial match via bsearch. As the
 *             match is random and may be the same word stored by needle, the
 *             program will traverse the sorted bucket backwards until it finds
 *             the first instance of an anagram match ot it reaches the first
 *             anagram in the bucket. It will them proceed to traverse forwards
 *             while storing all matching anagrams that are not iterations of
 *             needle, then printing the matching anagrams. If needle contains
 *             non-alphabetic characters or its only match in the dictionary is
 *             itself, print no anagrams found. Otherwise, print the matching
 *             anagrams in qsort sorted order.
 * Parameters: queryTable - the passed in queryTable.
 *             needle - the proverbial key.
 * Side Effects: See 'Description'
 * Error Conditions: None
 * Return Value: None
 */ 
void executeQuery( queryTable_t * queryTable, anagram_t * needle ) {
  
  /* Calculate the index needle would be in queryTable */ 
  unsigned int index = getBucketIndex( needle->hashcode, queryTable->size );

  /* Proceed to search for anagram matches. If none found, exit */
  anagram_t * foundPtr = bsearch( needle, queryTable->tablePtr[index].dataPtr,
                                  queryTable->tablePtr[index].anagramCount,
                                  sizeof( anagram_t ), anagramCmp ) ;
  if ( foundPtr == NULL ) {
    fprintf( stdout, STR_NO_ANAGRAMS_FOUND );
    return;
  }

  /* Else we found an anagram, find the first in the bucket */
  anagram_t * previousAnagram = foundPtr; 
  anagram_t * firstAnagram = previousAnagram;
  // While previous anagram is not the first anagram and are anagrams
  while ( previousAnagram != queryTable->tablePtr[index].dataPtr - 1 &&
          anagramCmp( needle, previousAnagram ) == 0 ) 
  {
    firstAnagram = previousAnagram;
    previousAnagram = ( previousAnagram - 1 );
  }
  
  /* Traverse forward and print each matching anagram */
  int notSameWordCounter = 0;
  char * anagrams[BUFSIZ];
  anagram_t * nextAnagram = firstAnagram;
  while( nextAnagram != queryTable->tablePtr[index].dataPtr +
         queryTable->tablePtr[index].anagramCount && // - 1 && 
         anagramCmp( needle, nextAnagram ) == 0 )
  {
    if (strcasecmp( needle->originalWord, nextAnagram->originalWord ) != 0 ) {
      anagrams[notSameWordCounter] = nextAnagram->originalWord;
      notSameWordCounter++;
      // fprintf( stdout, " %s", nextAnagram->originalWord );
    }
      nextAnagram = ( nextAnagram + 1 );
  }
  /* Print the string if anagrams found. If not, print 'No anagrams found.' */
  if ( notSameWordCounter == 0 ) {
    fprintf( stdout, STR_NO_ANAGRAMS_FOUND );
    return;
  }
  fprintf( stdout, STR_ANAGRAMS_FOUND );
  int i;
  for ( i = 0 ; i < notSameWordCounter ; i++ ) {
    fprintf( stdout, " %s", anagrams[i] );
  }
  fprintf( stdout, STR_NEWLINE_CHAR );

}

 /* CODE I MIGHT NEED LATER
for ( int i = 0; i < queryTable->tablePtr[index].anagramCount; i++ )
fprintf( stdout, " %s", queryTable->tablePtr[index].dataPtr[i].originalWord );
*/
