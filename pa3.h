/*
 * Filename: pa3.h
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/14/2019
 * Sources of help: None
 */
#ifndef PA3_H
#define PA3_H

#include <stdlib.h>
#include <ctype.h>

// =============================================================================
// Constants
// =============================================================================

// Feel free to add your own constants (:

// Anagram constants.
#define MAX_WORD_SIZE 48
#define ALPHABET_SIZE 26

#define HASH_START_VAL 7
#define HASH_PRIME     31

// Generate Anagram: constants for scanning flags (command line args)
#define GENERATE_ARG_STR "i:o:h"
#define IN_FILE_FLAG 'i'
#define OUT_FILE_FLAG 'o'
// Query: constants for scanning flags (command line args)
#define QUERY_ARG_STR "s:f:h"
#define SIZE_FLAG 's'
#define ANAGRAM_FILE_FLAG 'f'
// Common constants for scanning flags
#define HELP_FLAG 'h'

// Hash table constants
#define QUERY_TABLE_MAX_SIZE 1000
#define QUERY_TABLE_MIN_SIZE 1
#define QUERY_TABLE_DEFAULT_SIZE 80

// File constants
#define IN_FILE_DEFAULT "/usr/share/dict/words"
#define OUT_FILE_DEFAULT "anagrams.ano"

// Anagram file extension constants
#define ANAGRAM_FILE_EXT ".ano"
#define ANAGRAM_FILE_EXT_LEN 4

#define BASE 10

// =============================================================================
// Struct Definitions
// =============================================================================
struct anagram {
  char originalWord[MAX_WORD_SIZE];    // Copy of the original word.
  unsigned char counts[ALPHABET_SIZE]; // Letter counts of the word.
  unsigned int hashcode;               // Hashcode computed from letter counts.
};
typedef struct anagram anagram_t;

struct bucket {
  anagram_t * dataPtr; // The array of anagrams contained in this bucket.
  size_t anagramCount; // The number of anagrams in this bucket.
};
typedef struct bucket bucket_t;

struct queryTable {
  bucket_t * tablePtr; // Points to the table of buckets.
  size_t size;         // The number of available buckets in the table.
};
typedef struct queryTable queryTable_t;

// =============================================================================
// Function Prototypes
// =============================================================================

// Generate function prototypes.
int generateAnagramFile( const char * inFilename, const char * outFilename );

// Query function prototypes.
void executeQuery( queryTable_t * queryTable, anagram_t * needle );
unsigned int getBucketIndex( unsigned int hashcode, size_t tableSize );
int insertIntoBucket( bucket_t * bucket, anagram_t * anagram );
int loadQueryTable( const char * anagramFilename, queryTable_t * queryTable );
void queryLoop( queryTable_t * queryTable );

// Utility functions (most are used by both executables).
void assembleAnagram( const char * originalWord, anagram_t * anagram );
void countChars( unsigned char counts[], const char * word );
unsigned int getHashcode( unsigned char counts[] );
int isInBounds( int value, int minBound, int maxBound );

int anagramCmp( const void * p1, const void * p2 );
int countsCmp( const void * p1, const void * p2 );
int hashcodeCmp( const void * p1, const void * p2 );

unsigned int getURemainder( unsigned int dividend, unsigned int divisor );

#endif // PA3_H
