#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <openssl/sha.h>
#include "../include/keecrypt.h"

#define MAX_PWD_INPUT 128
#define ID_INPUT_LEN 4
#define MIN_PWD_LEN 8
#define KEY_SIZE 32

void set_stdin_echo(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable) {
        tty.c_lflag &= ~ECHO;
    } else {
        tty.c_lflag |= ECHO;
    }
    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

bool validate_password(const char *pwd) {
    int len = strlen(pwd);
    if (len < MIN_PWD_LEN) 
        return false;

    bool has_upper = false;
    bool has_special = false;

    for (int i = 0; i < len; i++) {
        if (isupper(pwd[i])) has_upper = true;
        if (ispunct(pwd[i])) has_special = true;
    }
    return has_upper && has_special;
}

bool validate_id(const char *id) {

    if (strlen(id) != 3) 
        return false;
    
    if (isdigit(id[0]) && isdigit(id[1]) && islower(id[2])) {
        return true;
    }
    return false;
}

void generate_master_key(const char *pwd, const char *id, unsigned char *output) {
    char combined[MAX_PWD_INPUT + ID_INPUT_LEN];
    
    snprintf(combined, sizeof(combined), "%s%s", pwd, id);
    SHA256((unsigned char*)combined, strlen(combined), output);
    memset(combined, 0, sizeof(combined));
}

int main() {

    char password[MAX_PWD_INPUT]; 
    char id[ID_INPUT_LEN];        
    unsigned char master_key[KEY_SIZE];

    printf("=== KeeCrypt Engine 1.0 ===\n");

    printf("Password (min 8 chars, 1 capital, 1 symbol): ");
    fflush(stdout); 
    set_stdin_echo(false);
    scanf("%127s", password); 
    set_stdin_echo(true);
    printf("\n");

    bool pwd_status = validate_password(password);

    printf("ID (2 numbers + 1 letter, ex: 12e): ");

    scanf("%3s", id); 

    bool id_status = validate_id(id);

    if (pwd_status && id_status) {
        generate_master_key(password, id, master_key);
        printf("\n[SUCCESS] Master Key successfully generated.\n");
        printf("Key (Hex): ");
        for(int i = 0; i < KEY_SIZE; i++) {
            printf("%02x", master_key[i]);
        }
        printf("\n");
    } else {
        printf("\n[ERROR] Invalid credentials.\n");
    }
    
    memset(password, 0, sizeof(password));
    memset(master_key, 0, sizeof(master_key));

    return 0;
}