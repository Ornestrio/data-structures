// Started on September 28, 2025
// in an attempt to learn... please help thy sanity.
// goals: scalability, ease of editing if i want to edit something
// 

// sept 29
// i learned about enum. state menus are actually fucking cool lmao
// menu creation, stacksarray and exit
// as of sept 29 1:37 am shit already has 219 lines of code
// now its 220, but its already almost half of my CP5 bruh..


// todo
// menu trapping, user might input 29 for some dumbass reason

// October 2
// added several functions (for stacksArray)
// addElement, isUserDataStacksFull, isUserDataStacksEmpty, isUserIDValid, userInputStacksArray
// i realized i should probably use github lmaooooo



#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSPACE 10

typedef struct userDataStacksArray // stacks array
{
    char userName[50];
    char userID[8];
    int userAge;
    
} udSArray; // stands for userDataStacksArray

typedef struct userDataStacksSLL *udSSLL; // stacks SLL
struct userDataAStacksSLL
{
    char userName[50];
    char userID[8];
    int userAge;
    
    udSSLL next; // stands for userDataStacksSinglyLinkedList
} udGVSSLL; // this declares a global variable (udGVSLL) of the struct type.
        // access it with:   udGVSLL.userName   (because it's a struct, not a pointer).
        // if I had a pointer (udSLL datastruct), I’d use: datastruct->userName

typedef struct userDataQueuesArray // queues array
{
    char userName[50];
    char userID[8];
    int userAge;
    
} udQArray; // stands for userDataQueuesArray

typedef struct userDataQueuesSLL *udQSLL;
struct userDataQueuesSLL
{
        char userName[50];
    char userID[8];
    int userAge;
    
    udQSLL next; // stands for userDataQueuesSinglyLinkedList
} udGVQSLL;

typedef struct userDataBST *udBST;
struct studentNode
{
    int studentID;
    float CQPA;
    udBST left;
    udBST right;
    udBST parent;
} udGVBST; // stands for userDataGlobalVariableBinarySearchTree

// this is way helpful
enum menuState {mainMenu, stacksArrayMenu, stacksSLLMenu, queuesArrayMenu, queuesSLLMenu, binarySearchTree, exitMenu, exitConfirmed};

// Universal Functions
void printMenu(const char *title, const char *options[]);
int menuChoice(void);
void pressAndClear(void);
void printBox(const char *message);


// menu functions
void handleMainMenu(enum menuState *state);
void handleStacksArrayMenu(enum menuState *state, udSArray userDataStacksArray[MAXSPACE], bool *isArrayCreated, int *top);
void handleExitMenu(enum menuState *state);

// stack array functions
bool createStackArray(udSArray userDataStacksArray[MAXSPACE], int *top);
void addElement(udSArray userDataStacksArray[MAXSPACE], int *top);
bool isUserDataStacksFull(udSArray userDataStacksArray[MAXSPACE], int top);
bool isUserDataStacksEmpty(udSArray userDataStacksArray[MAXSPACE], int top);
bool isUserIDValid(char *userID);; // check if userID has the right format
udSArray userInputStacksArray();

int main(void)
{
    udSArray userDataStacksArray[MAXSPACE];
    udQArray userDataQueuesArray[MAXSPACE];

    udSSLL userDataStacksSLL;
    udQSLL userDataQueuesSLL;

    int top = -1;

    enum menuState state = mainMenu;
    bool isUDSArrayCreated = false;
    bool isUDQArrayCreated = false;
    bool isUDStacksSLLCreated = false;
    bool isUDQueuesSLLCreated = false;

    int choice;

    do 
    {
        switch(state)
        {
            case mainMenu:
                handleMainMenu(&state);
                break;
            
            case stacksArrayMenu:
                handleStacksArrayMenu(&state, &userDataStacksArray, &isUDSArrayCreated, &top);
                break;

            case exitMenu:
                handleExitMenu(&state);
                break;



            default:
                printf("Try again!");
        }
    } while (state != exitConfirmed);


}

void printMenu(const char *title, const char *options[])
{
    int i;
    int maxWidth = strlen(title) + 4; // current width is based on the title.

    // find the longest option
    for (i = 0; options[i] != NULL; i++)
    {
        int len = strlen(options[i]) + 6;
        if (len > maxWidth) // if somehow an option is bigger than the current width
        {                  // set width to the options width.
            maxWidth = len; 
        }
    }

    // top border
    printf("+");
    for (i = 0; i < maxWidth; i++)
    {
        printf("-");
    }
    printf("+\n");

    // title row
    printf("| %-*s | \n", maxWidth - 2, title);
    // %10s means print string at least 10 characters wide.
    // default alignment is to the right.
    // if added with -, then align to the left instead.
    // placing * means a placeholder variable for how much.
    // %-*s alignt to the left based on x amount.

    // separator
    printf("+");
    for (i = 0; i < maxWidth; i++)
    {
        printf("-");
    }
    printf("+\n");

    // menu options

    for (i = 0; options[i] != NULL; i++)
    {
        printf("| %i. %-*s |\n", i + 1, maxWidth - 5, options[i]);
    }

    // bottom border
    printf("+");
    for (i = 0; i < maxWidth; i++)
    {
        printf("-");
    }
    printf("+\n");
}

int menuChoice(void)
{
    int choice;
    printf("Enter operation: ");
    scanf("%i", &choice);
    while (getchar() != '\n'); // clear input buffer
    return choice;
}


void pressAndClear()
{
    printf("\nPress any key to continue.");
    getchar();
    system("cls");
}

void printBox(const char *message)
{
    int i;
    int maxWidth = strlen(message) + 4; // current width is based on the title.

    // top border
    printf("+");
    for (i = 0; i < maxWidth; i++)
    {
        printf("-");
    }
    printf("+\n");

    // title row
    printf("| %-*s | \n", maxWidth - 2, message);
    // %10s means print string at least 10 characters wide.
    // default alignment is to the right.
    // if added with -, then align to the left instead.
    // placing * means a placeholder variable for how much.
    // %-*s alignt to the left based on x amount.

    // separator
    printf("+");
    for (i = 0; i < maxWidth; i++)
    {
        printf("-");
    }
    printf("+\n");
}

void handleMainMenu(enum menuState *state)
{
    int choice;
    const char *menuOptions[] = {"Stacks Array", "Stacks SLL", "Queues Array", "Queues SLL", "Binary Search Tree", "Exit", NULL};
    system("cls");

    printMenu("User Data Info Editor ver. 1.49", menuOptions);
    choice = menuChoice();
    switch(choice)
    {
        case 1: *state = stacksArrayMenu; break;
        case 2: *state = mainMenu; break;
        case 3: *state = mainMenu; break;
        case 4: *state = mainMenu; break;
        case 5: *state = mainMenu; break;
        case 6: *state = exitMenu; break;

    }

}

void handleStacksArrayMenu(enum menuState *state, udSArray userDataStacksArray[MAXSPACE], bool *isArrayCreated, int *top)
{
    int choice;
    udSArray element;
    static char *menuOptions[] = {"Create", "Add Data", "Remove Data", "Check last data", "Display All","Back", NULL};
    bool isFull = isUserDataStacksFull(userDataStacksArray, *top);
    const char *yesNo[] = {"Yes", "No", NULL};
    system("cls");

    printMenu("Stacks Array Menu", menuOptions);

    choice = menuChoice();
    switch(choice)
    {
        case 1:

            system("cls");
            if (*isArrayCreated == true)
            {
                printMenu("Are you sure you want to wipe the current data?", yesNo);
                choice = menuChoice();
                switch(choice)
                {
                    case 1: system("cls"); printBox("Sucessfully wiped data."); createStackArray(userDataStacksArray, top); break;
                    case 2: system("cls"); printBox("Cancelled operation."); break;
                    default: system("cls"); printBox("Wrong Input."); break;
                }
                pressAndClear();
                break;
            }
            menuOptions[0] = "Wipe Data";
            *isArrayCreated = createStackArray(userDataStacksArray, top);
            printBox("Array has been Initialized!");

            pressAndClear();
            break;
        case 2: 
            
            system("cls");
            if (*isArrayCreated == false)
            {
                printBox("Array has not been created yet. Please initialize it first.");
                pressAndClear();
                break;
            }
            if (isFull == true)
            {
                printBox("Array is full. Please remove some data first.");
                pressAndClear();
                break;
            } 
            element = userInputStacksArray();
            break;

        // case 3: 
            
        //     // element = peek(userDataStacksArray, top);
        //     break;
        case 4: *state = mainMenu; break;
        case 5: *state = mainMenu; break;
        case 6: *state = mainMenu; break;
        default:
            printBox("Enter numbers only!");

            pressAndClear();
            return;


    } 
}



void handleExitMenu(enum menuState *state)
{
    int choice;
    const char *menuOptions[] = {"Yes", "No", NULL};
    system("cls");

    printMenu("Are you sure you want to exit?", menuOptions);
    choice = menuChoice();
    switch(choice)
    {
        case 1: *state = exitConfirmed; break;
        case 2: *state = mainMenu; break;
    }
}


bool createStackArray(udSArray userDataStacksArray[MAXSPACE], int *top)
{
    for (int i = 0; i < MAXSPACE; i++)
    {
        strcpy(userDataStacksArray[i].userName, " ");
        strcpy(userDataStacksArray[i].userID, " ");
        userDataStacksArray[i].userAge = 0;
    }
    *top = -1;
    return true;
}

udSArray peek(udSArray userDataStacksArray[MAXSPACE], int *top)
{
    udSArray element;
    element = userDataStacksArray[*top];
    return element;
}

udSArray displayElements(udSArray userDataStacksArray[MAXSPACE], int *top)
{
    int i;
    int maxWidth = strlen(userDataStacksArray[*top].userID) + 4; // current width is based on the title.

    int len = strlen(userDataStacksArray[*top].userName) + 6;
    if (len > maxWidth) // if somehow an option is bigger than the current width
    {                  // set width to the options width.
        maxWidth = len; 
    }


    // top border
    printf("+");
    for (i = 0; i < maxWidth; i++)
    {
        printf("-");
    }
    printf("+\n");

    // title row
    printf("| %-*s | \n", maxWidth - 2, userDataStacksArray[*top].userID);
    // %10s means print string at least 10 characters wide.
    // default alignment is to the right.
    // if added with -, then align to the left instead.
    // placing * means a placeholder variable for how much.
    // %-*s alignt to the left based on x amount.

    // separator
    printf("+");
    for (i = 0; i < maxWidth; i++)
    {
        printf("-");
    }
    printf("+\n");

    // bottom border
    printf("+");
    for (i = 0; i < maxWidth; i++)
    {
        printf("-");
    }
    printf("+\n");
}


void addElement(udSArray userDataStacksArray[MAXSPACE], int *top)
{
    bool isUserDataStacksArray = false;
}

bool isUserDataStacksFull(udSArray userDataAStacksArray[MAXSPACE], int top)
{
    return top == MAXSPACE - 1;
}

bool isUserDataStacksEmpty(udSArray userDataStacksArray[MAXSPACE], int top)
{
    return top == -1;
}

udSArray userInputStacksArray()
{
    char userName[50];
    char userID[8];
    int userAge;

    udSArray elements;
    
    printBox("Enter username: ");
    fgets(userName, sizeof(userName), stdin);
    userName[strcspn(userName, "\n")] = '\0'; 

    do
    {
        printBox("Enter ID: ");
        fgets(userID, sizeof(userID), stdin);
        userID[strcspn(userID, "\n")] = '\0';   

        if (isUserIDValid(userID) == false)
        {
            system("cls");
            printBox("User ID must have a # at the start. Example: (#ETRIEUS)");
        }
    } while (isUserIDValid(userID) == false);
    printBox("Enter age: ");
    scanf("%i", &userAge);

    strcpy(elements.userName, userName);
    strcpy(elements.userID, userID);

    return elements;
} 

bool isUserIDValid(char *userID) // check if userID has the right format
{
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char digits[] = "0123456789";

    if (strlen(userID) != 7) return false;
    if (userID[0] != "#") return false;

    return true;
}