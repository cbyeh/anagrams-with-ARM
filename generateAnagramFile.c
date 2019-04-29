/*
* Filename: generateAnagramFile.c
* Author: Christopher Yeh
* UserId: cs30xfv
* Date: 2/23/2019
* Sources of help: None
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pa3.h"
#include "pa3Strings.h"

/* Helper method to see if string has valid characters */
int isWordAlpha( const char * word ) {
  
 size_t i;
 for ( i = 0 ; word[i] ; i++ ) {
   if ( !isalpha( word[i] ) ) {
     return 0;
   }
 }
 return 1;

}  

/*
 * Function Name: generateAnagramFile()
 * Function Prototype: int generateAnagramFile( const char * inFilename, 
 *                                              const char * outFilename );
 * Description: Read in one word at a time from inFilename, create an
 *             anagram struct for the word read in. Proceed to write the 
 *             write the anagram struct to outFilename. Repeat for all words.
 * Parameters: inFilename - number of command line arguments passed in
 *             outFilename - output file. Will be filled with anagram structs.
 * Side Effects: None
 * Error Conditions: Permission denied reading the input, invalid input name,
 *             error creating output file, or error writing an anagram to the
 *             output file are all causes of errors that will be caught.
 * Return Value: Returns -1 if an error occured.
 *             Otherwise, return the number of anagrams assembled.
 *             Words with non-alphabetic characters won't be counted or added.
 */ 
int generateAnagramFile( const char * inFilename, const char * outFilename ) {
  
  /* Allocate local vars on stack */
  errno = 0;
  FILE * fpIn;  
  FILE * fpOut;
  fpIn = fopen ( inFilename, "r" );

  /* Error if file doesn't have read permissions, error if doesn't exist */
  if ( errno == EACCES ) {
    fprintf( stderr, STR_ERR_IN_FILE_PERMISSION, inFilename );
    return -1;
  }

  if ( errno != 0 ) { // Check if file is invalid
    fprintf( stderr, STR_ERR_IN_FILE_INVALID, inFilename );
    return -1;
  }

  fpOut = fopen( outFilename, "wb" );

  if ( fpOut == NULL || errno != 0) { // Check if error occured opening out
    fprintf( stderr, STR_ERR_CREATE_ANAGRAM_FILE, outFilename );
    fclose( fpOut);
    return -1;
  }

  /* Files read and written (or created). Proceed with program */
  anagram_t anagram;
  memset( &anagram, 0, sizeof( anagram_t ) );
  int anagramsWritten = 0;
  char buffer[MAX_WORD_SIZE];

  while ( fgets( buffer, MAX_WORD_SIZE, fpIn ) != NULL ) { 
    /* Replace '\n' with '\0' */
    char * pos = strchr( buffer, '\n' );
    if ( pos != NULL ) {
      * pos = '\0';
    }
    /* Check if there are non alphabetic characters in word. If so, skip */
    if ( isWordAlpha( buffer ) != 0 ) { // Else write to outFilename
      assembleAnagram( buffer, &anagram );
      if ( fwrite( &anagram, sizeof( anagram_t ), 1, fpOut ) ) { 
        anagramsWritten++;
      } else {
        fclose( fpIn );
        fclose( fpOut );
        return -1;
      }
    }
  }
  
  fclose( fpIn );
  fclose( fpOut );
  return anagramsWritten;

}
