// create a program that lets the user select choices using the arrow keys
// and display the selected choice


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>

// define the choices
#define CHOICE_1 "Choice 1"
#define CHOICE_2 "Choice 2"
#define CHOICE_3 "Choice 3"
#define CHOICE_4 "Choice 4"

// define the choices array
char *choices[] = {CHOICE_1, CHOICE_2, CHOICE_3, CHOICE_4};

// define the number of choices
#define NUM_CHOICES 4

// define the max length of a choice
#define MAX_LEN 20

// define the max length of the menu
#define MAX_MENU_LEN (MAX_LEN * NUM_CHOICES)

// define function prototypes
void display_menu(char *menu[], int num_choices);
void get_choice(char *menu[], int num_choices, int *choice);
void get_arrow_key(int *key);
void clear_screen();

// display_menu: display the menu
void display_menu(char *menu[], int num_choices) {
    int i;
    for (i = 0; i < num_choices; i++) {
        printf("%s\n", menu[i]);
    }
}

// get_choice: get the choice from the user
void get_choice(char *menu[], int num_choices, int *choice) {
    int key;
    while (1) {
        get_arrow_key(&key);
        if (key == '\e') {
            break;
        } else if (key == '\n') {
            *choice = 0;
            break;
        } else if (key == '\b') {
            if (*choice > 0) {
                *choice -= 1;
            }
        } else if (key == '\177') {
            if (*choice < num_choices - 1) {
                *choice += 1;
            }
        }
    }
}

// get_arrow_key: get the arrow key from the user
void get_arrow_key(int *key) {
    struct termios old_settings, new_settings;
    tcgetattr(0, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
    *key = getchar();
    tcsetattr(0, TCSANOW, &old_settings);
}

// clear_screen: clear the screen
void clear_screen() {
    printf("\e[1;1H\e[2J");
}

// main: main function
int main() {
    int choice;
    char menu[MAX_MENU_LEN];
    int i;
    for (i = 0; i < NUM_CHOICES; i++) {
        strcat(menu, choices[i]);
        strcat(menu, "\n");
    }
    while (1) {
        clear_screen();
        display_menu(choices, NUM_CHOICES);
        get_choice(choices, NUM_CHOICES, &choice);
        if (choice == 0) {
            break;
        }
    }
    return 0;
}
