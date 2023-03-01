#include <stdbool.h>

#ifndef GENERAL
#define GENERAL

#define RED       "\x1B[31;1m"
#define GREEN     "\x1B[32;1m"
#define YELLOW    "\x1B[33;1m"
#define BLUE      "\x1B[34;1m"
#define MAGENTA   "\x1B[35;1m"
#define CYAN      "\x1B[36;1m"
#define WHITE     "\x1B[37;1m"

bool parse_input (char (*p)[], char s[100]);
void init_data ();
void load_data ();
void save_data ();
void load_test_data ();
void reset_data ();
void cli_load_test_data ();
void cli_reset_data ();

#endif