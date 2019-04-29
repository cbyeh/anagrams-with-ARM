/*
* Filename: generateAnagramMain.c
* Author: Christopher Yeh
* UserId: cs30xfv
* Date: 2/23/2019
* Sources of help: None 
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: The main function will drive the rest of the program. 
 *             It will first perform input checking by parsing the commandline 
 *             arguments and flags, checking for errors. 
 *             If all inputs are valid, read in one word at a time from 
 *             inFilename. Then, creates an anagram struct for the word and 
 *             writes it to outFilename which must be postfixed with .ano
 *             Otherwise, it will print the corresponding error message 
 *             and return right away.
 * Parameters: argc - number of command line arguments passed in.
 *             argv - command line arguments passed in.
 * Side Effects: None
 * Error Conditions: If an unknown flag is entered, too many or not the correct
 *             amount of arguments are entered, the output file does not end
 *             in an .ano extension, or calling generateAnagramFile returns -1.
 * Return Value: Returns error if it meets the error cases.
 *             Otherwise, execute and return success.
 */ 
int main( int argc, char * argv[] ) {

  int opt;
  char * inputFile = IN_FILE_DEFAULT;
  char * outputFile = OUT_FILE_DEFAULT;

  /* Parse the flags. If passed an unrecognized flag, throw error and exit */
  while ( ( opt = getopt( argc, argv, GENERATE_ARG_STR ) ) != -1 ) {
    switch( opt ) {
      case HELP_FLAG:
        fprintf( stdout, STR_GENERATE_ANAGRAM_USAGE_LONG, argv[0],
                 IN_FILE_DEFAULT, ANAGRAM_FILE_EXT, OUT_FILE_DEFAULT );
        return EXIT_SUCCESS;
      
      case IN_FILE_FLAG:
        inputFile = optarg; 
        break;

      case OUT_FILE_FLAG:
        outputFile = optarg;
        break;

      case '?': // Catch all unknown flags
        default:
        fprintf( stderr, STR_GENERATE_ANAGRAM_USAGE_SHORT, argv[0], argv[0] );
        return EXIT_FAILURE;
    }
  }
  if ( optind < argc ) { 
    fprintf( stderr, STR_ERR_EXTRA_ARGS, argv[optind] );
    fprintf( stderr, STR_GENERATE_ANAGRAM_USAGE_SHORT, argv[0], argv[0] );
    return EXIT_FAILURE;
  }

  /* See if output file ends in .ano */
  char * dot = strchr( outputFile, '.' );
  // If does not end in .ano or does not contain dot
  if ( !dot || strncmp( dot, ANAGRAM_FILE_EXT, ANAGRAM_FILE_EXT_LEN ) != 0 ) {
    fprintf( stderr, STR_ERR_ANAGRAM_FILE_EXT, ANAGRAM_FILE_EXT );
    return EXIT_FAILURE;
  }

  /* Generate the anagram file */
  int generate = generateAnagramFile( inputFile, outputFile );
  if ( generate == -1 ) { // If generate has error
    return EXIT_FAILURE;
  }
  
  fprintf( stdout, STR_ANAGRAM_FILE, outputFile, generate );
  return EXIT_SUCCESS;

}
