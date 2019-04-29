/*
* Filename: queryAnagramMain.c
* Author: Christopher Yeh
* UserId: cs30xfv
* Date: 2/24/2019
* Sources of help: None 
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include "pa3.h"
#include "pa3Strings.h"

#define EXTRA_ARG 5

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: The main function will drive the rest of the program. 
 *             It will first perform input checking by parsing the commandline 
 *             arguments and flags, checking for errors. 
 *             If all inputs are valid and we pass all the error checks,
 *             proceed to allocate memory for a queryTable and set up its
 *             struct elements and call loadQueryTable;
 *             Enter the interactive mode with a call to queryLoop;
 *             Then free all the memory allocated from every function call and
 *             the pointers declared here.
 *             Otherwise, it will print the corresponding error message 
 *             and return right away.
 * Parameters: argc - number of command line arguments passed in.
 *             argv - command line arguments passed in.
 * Side Effects: None
 * Error Conditions: If an unknown flag is entered, too many or not the correct
 *             amount of arguments are entered, the tableSize is too big,
 *             the size is non-numeric, the size is not in the bounds of
 *             1-1000, not enough memory for the buckets can be allocated, the 
 *             filename wasn't set, or the output file in an .ano extension.
 * Return Value: Returns error if it meets the error cases.
 *             Otherwise, execute and return success.
 */ 
int main( int argc, char * argv[] ) {

  errno = 0;
  char * endPtr;
  char printErr[BUFSIZ];
  int opt;
  char * filename; 
  int filenameSet = 0;
  unsigned int size = QUERY_TABLE_DEFAULT_SIZE;

  /* Parse the flags. If passed an unrecognized flag, throw error and exit */
  while ( ( opt = getopt( argc, argv, QUERY_ARG_STR ) ) != -1 ) { 
    switch( opt ) {
      case HELP_FLAG:
        fprintf( stdout, STR_QUERY_USAGE_LONG, argv[0], QUERY_TABLE_MIN_SIZE, 
                 QUERY_TABLE_MAX_SIZE, QUERY_TABLE_DEFAULT_SIZE );
        return EXIT_SUCCESS;
      
      case ANAGRAM_FILE_FLAG:
        filename = optarg; 
        filenameSet = 1;
        break;

      case SIZE_FLAG:
        size = strtol( optarg, &endPtr, BASE );
        if ( errno != 0 ) { // Error parsing size
          snprintf( printErr, BUFSIZ, STR_ERR_CONVERTING, optarg, BASE );
          fprintf( stderr, "\n" );
          perror( printErr );
          fprintf( stderr, "\n");
          return EXIT_FAILURE;
        } 
        // Check if size contains non-numerical characters
        if ( * endPtr != '\0' ) {
        fprintf( stderr, STR_ERR_NOTINT, optarg, BASE );
        return EXIT_FAILURE;
        }
        break;

      case '?': // Catch all unknown flags
      default: 
        fprintf( stderr, STR_QUERY_USAGE_SHORT, argv[0], argv[0] );
        return EXIT_FAILURE;
    }
  }
  if ( optind < argc ) { 
    fprintf( stderr, STR_ERR_EXTRA_ARGS, argv[optind] );
    fprintf( stderr, STR_QUERY_USAGE_SHORT, argv[0], argv[0] );
    return EXIT_FAILURE;
  }

  /* Check if table size is within 1-1000 inclusive */
  if ( isInBounds( size, QUERY_TABLE_MIN_SIZE, QUERY_TABLE_MAX_SIZE ) == 0 ) {
    fprintf( stderr, STR_ERR_TABLE_SIZE_BOUNDS, size, 
             QUERY_TABLE_MIN_SIZE, QUERY_TABLE_MAX_SIZE );
    return EXIT_FAILURE;
  }

  /* Check if filename was set */
  if ( filenameSet != 1 ) {
    fprintf( stderr, STR_ERR_FILENAME_NOT_ENTERED );
    fprintf( stderr, STR_QUERY_USAGE_SHORT, argv[0], argv[0] );
    return EXIT_FAILURE;
  }

  /* See if output file ends in .ano */
  char * dot = strchr( filename, '.' );
  // If does not end in .ano or does not contain dot
  if ( !dot || strncmp( dot, ANAGRAM_FILE_EXT, ANAGRAM_FILE_EXT_LEN ) != 0 ) {
    fprintf( stderr, STR_ERR_ANAGRAM_FILE_EXT, ANAGRAM_FILE_EXT );
    return EXIT_FAILURE;
  }

  /* Begin the HEAP. Build the queryTable */
  bucket_t * bPtr = ( bucket_t * ) calloc( size, sizeof( bucket_t ) );
  if ( bPtr == NULL ) {
    fprintf( stderr, STR_ERR_MEM );
    return EXIT_FAILURE;
  }
  queryTable_t * qPtr = ( queryTable_t * ) malloc( sizeof( queryTable_t ) );
  if ( qPtr == NULL ) {
    fprintf( stderr, STR_ERR_MEM );
    return EXIT_FAILURE;
  }
  queryTable_t * queryTable = qPtr;
  queryTable->tablePtr = bPtr;
  queryTable->size = size;
  int query = loadQueryTable( filename, queryTable );
  if ( query != 0 ) {
    return EXIT_FAILURE;
  }

  /* Load interactive mode, then free all the memory when done */
  queryLoop( queryTable );
  size_t i;
  for ( i = 0; i < size; i++ ) {
    free( queryTable->tablePtr[i].dataPtr );
  }
  free( bPtr );
  free( qPtr );

}
