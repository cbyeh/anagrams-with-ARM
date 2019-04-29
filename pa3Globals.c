/*
 * Filename: pa3Globals.c
 * Date: 2/14/2019
 *
 * Global file for the assembly functions to access constants.
 */

#include "pa3.h"
#include <stddef.h>

// Offset of anagram struct memebers
int HASHCODE_OFFSET_G = offsetof( anagram_t, hashcode );
int COUNTS_OFFSET_G = offsetof( anagram_t, counts );
int ORIGINAL_WORD_OFFSET_G = offsetof( anagram_t, originalWord );

int MAX_WORD_SIZE_G = MAX_WORD_SIZE;
int ALPHABET_SIZE_G = ALPHABET_SIZE; 

int HASH_START_VAL_G = HASH_START_VAL;
int HASH_PRIME_G     = HASH_PRIME;
