/*
 * Filename: pa3Strings.h
 * Author: Christopher Yeh
 * UserId: cs30xfv
 * Date: 2/14/2019
 * Sources of help: None
 */
#ifndef PA3_STRINGS_H
#define PA3_STRINGS_H

// =============================================================================
// Error strings used in both executables
// =============================================================================
#define STR_ERR_MEM "\n\tMemory limit exceeded.\n\n"

/* Report extra command line args after getopt has processed all flags */
#define STR_ERR_EXTRA_ARGS   "\n\tExtra argument '%s'.\n"

#define STR_ERR_ANAGRAM_FILE_EXT "\n"\
  "\tAnagram file must have extension \"%s\".\n\n"
#define STR_ERR_IN_FILE_PERMISSION "\n"\
  "\tError opening input file (%s); permission denied.\n\n"
#define STR_ERR_IN_FILE_INVALID "\n"\
  "\tError opening input file (%s); invalid file.\n\n"

// =============================================================================
// Strings used in generate executable
// =============================================================================
/* Usage strings for generate anagrams */
#define STR_GENERATE_ANAGRAM_USAGE_LONG "\n"\
  "Usage: %s [-i inputWordsFile] [-o outputAnagramFile] [-h]\n"\
  "Reads in the words file and outputs a corresponding file of anagrams.\n"\
  "  -i <inputWordsFile>    Name of the words file to use;\n"\
  "                         Each word in the file is separated by a newline.\n"\
  "                         Defaults to %s if unspecified.\n"\
  "  -o <outputAnagramFile> The name of the anagram file to output.\n"\
  "                         Must have extension \"%s\".\n"\
  "                         Defaults to %s if unspecified.\n"\
  "  -h                     Prints the long usage.\n"\
  "\n"
#define STR_GENERATE_ANAGRAM_USAGE_SHORT "\n"\
  "Usage: %s [-i inputWordsFile] [-o outputAnagramFile] [-h]\n"\
  "Try '%s -h' for more information.\n\n"

/* generateAnagramFile errors */
#define STR_ERR_CREATE_ANAGRAM_FILE "\n"\
  "\tError creating anagram file (%s).\n\n"
#define STR_ERR_WRITE_ANAGRAM "\n"\
  "\tError writing to anagram file (%s).\n\n"

/* generateAnagramMain normal output strings */
#define STR_ANAGRAM_FILE "\n"\
 "\tGenerated anagram file (%s) with %d anagrams.\n\n"

// =============================================================================
// Strings used in query executable
// =============================================================================
/* Query Usage strings */
#define STR_QUERY_USAGE_LONG "\n"\
  "Usage: %s [-s tableSize] [-h] -f anagramFile\n"\
  "Interactive anagram query.\n"\
  "  -s <tableSize>     The size of the hashtable to be used;\n"\
  "                     Must be a decimal value in the bounds [%d - %d].\n"\
  "                     Defaults to %d if unspecified.\n"\
  "  -f <anagramFile>   Name of the anagram file to use.\n"\
  "  -h                 Prints the long usage.\n"\
  "\n"
#define STR_QUERY_USAGE_SHORT "\n"\
  "Usage: %s [-s tableSize] [-h] -f anagramFile\n"\
  "Try '%s -h' for more information.\n\n"

/* Query error strings */
#define STR_ERR_TABLE_SIZE_BOUNDS "\n"\
  "\ttableSize (%d) is not in bounds [%d, %d]\n\n"
#define STR_ERR_FILENAME_NOT_ENTERED "\n\tNo anagram filename was entered.\n"
#define STR_ERR_CONVERTING "\n\tConverting \"%s\" base \"%d\""
#define STR_ERR_NOTINT "\n\t\"%s\" is not an unsigned integer in base %d\n\n"

/* loadQueryTable errors */
#define STR_ERR_ANAGRAM_FILE_CORRUPT "\n"\
  "\tError reading anagram file (%s); corrupt file (invalid file length).\n\n"
#define STR_ERR_INSERT "\n\tFailed to insert anagram into query table.\n\n"

/* Query prompt strings */
#define STR_USER_PROMPT "\nEnter a word to search for anagrams [^D to exit]: "
#define STR_NO_ANAGRAMS_FOUND "\nNo anagrams found.\n"
#define STR_ANAGRAMS_FOUND "\nAnagrams found: "
#define STR_SPACE_CHAR " "
#define STR_NEWLINE_CHAR "\n"

#endif // PA3_STRINGS_H
