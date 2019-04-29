/*
* Filename: insertIntoBucket.c 
* Author: Christopher Yeh
* UserId: cs30xfv
* Date: 2/23/2019
* Sources of help: None 
*/

#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: insertIntoBucket()
 * Function Prototype: int insertIntoBucket( bucket_t * bucket,
 *                                           anagram_t * anagram );
 * Description: Insert the passed in anagram to the passed in bucket.
 *             Allocate the necessary memory on the heap and append it to the
 *             end. Increment the bucket's count of anagrams.
 * Parameters: bucket - the passed in bucket pointer
 *             anagram - the passed in anagram pointer 
 * Side Effects: None
 * Error Conditions: We fail to allocate memory on the heap for more space.
 * Return Value: Returns -1 if an error occurs.
 *             Otherwise, return 0.
 */ 
int insertIntoBucket( bucket_t * bucket, anagram_t * anagram ) {
  
  /* Allocate more space */
  anagram_t * ptr;
  int size = sizeof( anagram_t );
  ptr = realloc( bucket->dataPtr, ( size * ( bucket->anagramCount + 1 ) ) );
  if ( ptr == NULL ) { // realloc failure
    fprintf( stderr, STR_ERR_MEM );
    free( bucket->dataPtr );
    return -1;
  }

  /* Memory allocation successful, dataPtr pts to new memory, store anagram */
  bucket->dataPtr = ptr;
  bucket->anagramCount++;
  bucket->dataPtr[bucket->anagramCount - 1] = * anagram;
  return 0;

}
