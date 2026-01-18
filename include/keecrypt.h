#ifndef KEECRYPT_H
#define KEECRYPT_H

#include <stdbool.h>

#define MAX_PWD_INPUT 128
#define ID_INPUT_LEN 4
#define MIN_PWD_LEN 8

/**
 * Password validation for the following requirements:
 * - Minimum of 8 characters
 * - At least one uppercase letter
 * - At least one special symbol 
 * */
bool validate_password(const char *pwd);

/**
 * ID validation for the following requirements:
 * - 3 characters
 * - First 2 characters are digits (0-9)
 * - Last digit is a letter (a-z, A-Z)
 */
bool validate_id(const char *id);

#endif