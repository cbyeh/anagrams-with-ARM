/*
* Filename: queryLoop.c
* Author: Christopher Yeh
* UserId: cs30xfv
* Date: 2/23/2019
* Sources of help: None
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 * Function Name: queryLoop()
 * Function Prototype: void queryLoop( queryTable_t * queryTable );
 * Description: The interactive mode of the program. Prompts the user for a 
 *             keyword from stdin. Assembles it into an anagram then calls
 *             executeQuery to see if we have any matches in the dictionary.
 *             Repeat until the user force closes.
 * Parameters: queryTable - the passed in queryTable.
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None 
 */ 
void queryLoop( queryTable_t * queryTable ) {
  
  /* Prompt user for input */
  fprintf( stdout, STR_USER_PROMPT );

  /* Read word entered by user */
  char buffer[BUFSIZ];
  while ( fgets( buffer, BUFSIZ, stdin ) != NULL ) { 
    /* Replace '\n' with '\0' */
    char * pos = strchr( buffer, '\n' );
    if ( pos != NULL ) {
      * pos = '\0';
    }
    if ( isWordAlpha( buffer ) != 1 ) { // If word contains non alphabetic char
      fprintf( stdout, STR_NO_ANAGRAMS_FOUND );
    } else {
      anagram_t anagram; 
      memset( &anagram, 0, sizeof( anagram_t ) );
      assembleAnagram( buffer, &anagram ); 
      executeQuery( queryTable, &anagram );
    }
      fprintf( stdout, STR_USER_PROMPT );
  }

  fprintf( stdout, STR_NEWLINE_CHAR );
  
}
