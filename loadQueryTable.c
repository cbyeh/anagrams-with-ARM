/*
* Filename: loadQueryTable.c
* Author: Christopher Yeh
* UserId: cs30xfv
* Date: 2/23/2019
* Sources of help: None
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: loadQueryTable()
 * Function Prototype: int loadQueryTable( const char * anagramFilename, 
 *                                         queryTable_t * queryTable );
 * Description: Read in one anagram at a time from the passed in .ano file. 
 *             Proceed to set up the passed in queryTable, inserting each
 *             anagram into the correct bucket, finishing with sorting each
 *             individual bucket.
 * Parameters: anagramFilename - the passed in .ano file.
 *             queryTable - the passed in queryTable with a set size.
 * Side Effects: None
 * Error Conditions: Accounts for file not being divisible by the size of an
 *             anagram, calling insertIntoBucket fails, opening the .ano fails.
 * Return Value: Returns -1 if any of the above errors occured.
 *             Otherwise, return 0.
 */ 
int loadQueryTable( const char * anagramFilename, queryTable_t * queryTable ) {
  
  /* Allocate local vars on stack */
  errno = 0;
  FILE * fpanagramFile;  
  fpanagramFile = fopen ( anagramFilename, "rb" );

  /* Error if file doesn't have read permissions, error if doesn't exist */
  if ( errno == EACCES ) {
    fprintf( stderr, STR_ERR_IN_FILE_PERMISSION, anagramFilename );
    return -1;
  }

  if ( errno != 0 ) {
    fprintf( stderr, STR_ERR_IN_FILE_INVALID, anagramFilename );
    return -1;
  }

  /* Check if file is evenly divisible by anagram */
  anagram_t anagram;
  memset( &anagram, 0, sizeof( anagram_t ) );
  struct stat fileSize;
  int status = stat( anagramFilename, &fileSize );
  if ( status == 0 ) { // If size of file is fileSize.st_size;
    if ( getURemainder( fileSize.st_size, sizeof( anagram_t ) != 0 ) ) {
      fprintf( stderr, STR_ERR_ANAGRAM_FILE_CORRUPT, anagramFilename );
      return -1; // Not divisible by size of a single anagram
    }
  }

  /* Read in one anagram at a time */
  size_t i; 
  while ( fread( &anagram, sizeof( anagram_t ), 1, fpanagramFile ) != 0 ) {
    unsigned int index = getBucketIndex( anagram.hashcode, queryTable->size );
    if ( insertIntoBucket( &( queryTable->tablePtr[index] ), &anagram ) == -1 )
    {
     fprintf( stderr, STR_ERR_INSERT );
     return -1;
    }
  }

  /* Successfully read all anagrams and inserted to queryTable,
     proceed to sort each bucket's anagram array with q sort */
  for ( i = 0; i < queryTable->size; i++ ) {
    qsort( queryTable->tablePtr[i].dataPtr, 
           queryTable->tablePtr[i].anagramCount, 
           sizeof( anagram_t ), anagramCmp );
  }

  /* Success */
  fclose( fpanagramFile );
  return 0;

}
