#include <stdio.h>
#include <termios.h>

#define CLEAR_SCREEN "\e[1;1H\e[2J"
#define CHOICE_1 "|| LIKE THIS VIDEO"
#define CHOICE_2 "|| SHARE THIS VIDEO"
#define CHOICE_3 "|| SUBSCRIBE TO MY CHANNEL"
#define CHOICE_4 "|| START CODING"

#define NUM_CHOICES 4

char *choices[] = {
  CHOICE_1,
  CHOICE_2,
  CHOICE_3,
  CHOICE_4
};

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

void arrowHere(int realPosition, int arrowPosition) {
  if (realPosition == arrowPosition) {
    printf(" -----> - %d ", realPosition);
  } else {
    printf("          ");
  }
}

void menu() {

  printf("%s", CLEAR_SCREEN);

  printf("\n\n\n");

  int keyPressed = 0;
  int position = 1;
  int maxOption = 4;

  while (keyPressed != '\n') {
    printf("%s", CLEAR_SCREEN);
    printf("\n\n");
  
    for (int i = 0; i < NUM_CHOICES; i++) {
      arrowHere(i + 1, position); printf("%s\n", choices[i]);
    }
  
    // printf("%c\n", keyPressed);
    keyPressed = getch();
  
    if (keyPressed == 'B' && position != maxOption) {
      position++;
    } else if(keyPressed == 'A' && position != 1) {
      position--;
    } else {
      position = position;
    }
  }

  printf("\n\nYou have selected option %s\n", choices[position - 1]);

  getch();
}

int main() {
  menu();
  return 0;
}

