//-----------------------------------------------------------------------------------//
//                                TP2025 - City Graph MAPPP                               //
//-----------------------------------------------------------------------------------//
// Year: 2025
// Lab 1 Submission: April 2, 2025
// University: ESI (École Supérieure d'Informatique)
// Encadred by: Bouzian Radia
// Authors: Kellil Douaa and Toudert Emilia
// 
// Description:
// This program implements some of basics of map system using linked list
// It provides functions to:
//   - Add cities and paths (direct or indirect).
//   - Display the graph of cities and their connections.
//   - Find reachable cities (directly or indirectly).
//   - Check if a path exists between two cities and display it.
//   - Find the shortest path between two cities.
//   - Delete cities and their paths.
//   - little of Load and save graph data from/to a file for persistence.
//





#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <conio.h>   // For getch()
#include <windows.h> // For system("cls") and Sleep()

// fot the color for terminal output
#define ANSI_COLOR_GRAY "\033[90m" // ANSI code for gray
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_LIGHT_BLUE "\033[94m"
#define ANSI_COLOR_WHITE "\033[37m"
#define ANSI_COLOR_RESET "\033[0m"
// some constants for menu navigation
#define MAX_OPTIONS 10
#define KEY_ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

//----------------------------- UTILITY FUNCTIONS -----------------------------//
// these functions handle console output, such as clearing the screen and changing text colors

// for clear the console screen
void clearScreen()
{
    system("cls");
}
// Functions to change text color in the console
void yellow() { printf(ANSI_COLOR_YELLOW); }
void green()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void white()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void blue()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
}
void gray()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
}
void red()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void resetColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("\033[0m");
}

//----------------------------- DATA STRUCTURES -----------------------------//
// these structures represent the graph, including cities (nodes) and paths (edges)

// stack structure for storing the path of cities in function of finding if there is path
typedef struct stack
{
    char elem[100][50]; // this is to store the cities path
    int top;
} stack;
// Node structure for linked list (paths between cities)
typedef struct node
{
    char city2[50];    // name of the city
    int data;          // distance between the two cities
    struct node *next; // next path in the list
} node;

// Doubly linked list structure for cities
typedef struct dnode
{
    char city1[50];      // name of the city
    struct dnode *prevd; // previous city in the list
    struct dnode *nextd; // next city in the list
    struct node *path;   // path to the next city
} dnode;

// Typedefs for easier usage
typedef struct dnode *ptr1; // pointer to the doubly linked list node (city of the graph)
typedef struct node *ptr2;  // pointer to the singly linked list node (path)

//---------------------------------------machine abstract----------------------------------------//
//-----------------------------graph operations ------------------------------------//
// ----------------------------machine abstract of the double linked list------------------------//
// allocate memory for a new city
void allocated(ptr1 *p1)
{
    *p1 = (struct dnode *)malloc(sizeof(struct dnode));
    (*p1)->nextd = NULL;
    (*p1)->prevd = NULL;
    (*p1)->path = NULL;
};
// free the memory of the city
void freed(ptr1 p1)
{
    free(p1);
};
// assign the name of the city to the node
void ass_city1d(ptr1 *p1, const char namecity[50])
{
    strcpy((*p1)->city1, namecity);
};
// assign the next and previous pointers for cities
void ass_nextd(ptr1 p1, ptr1 pp)
{
    p1->nextd = pp;
};
void ass_prevd(ptr1 p1, ptr1 pp)
{
    p1->prevd = pp;
};
// assign a path to a city
void ass_path(ptr1 p1, ptr2 pp)
{
    p1->path = pp;
}
// get the path from a city
ptr2 get_path(ptr1 p1)
{
    return p1->path;
}
// move to the next or previous city in the doubly linked list
void nextd(ptr1 *p)
{
    *p = (*p)->nextd;
};

void prevd(ptr1 *p)
{
    *p = (*p)->prevd;
}
// get the name of a city
char *namecityd(ptr1 p1)
{ // velue , data of the node
    return p1->city1;
};

//----------------------------- branch operations -----------------------------//
// ----------------------------machine abstract of the linked list------------------------//

// allocate memory for a new path (linked list node)
void allocate(ptr2 *p2)
{
    *p2 = (struct node *)malloc(sizeof(struct node));
    (*p2)->next = NULL;
};
// free memory for a path
void freenode(ptr2 p2)
{
    free(p2);
};
// assign a destination city and distance to a path
void ass_city2(ptr2 p2, char namecity2[50])
{
    strcpy(p2->city2, namecity2);
}
void ass_data(ptr2 p2, int dis) // data is distance
{
    p2->data = dis;
}
// assign the next pointer for a path
void ass_next(ptr2 p2, ptr2 pp)
{
    p2->next = pp;
}
// move to the next path in the linked list
void next(ptr2 *p2)
{
    *p2 = (*p2)->next;
}
// get the destination city and distance from a path
char *namecity(ptr2 p2)
{
    return p2->city2;
}

int distancecity(ptr2 p2)
{
    return p2->data;
}

//----------------------------- stack operations -------------------------------//
//--------------------------machine abstract of the stack-----------------------//
// initialize a stack
void creatstack(stack *s)
{
    s->top = -1;
}
// check if the stack is empty
bool emptystack(stack s)
{
    return (s.top == -1);
}
// push a city onto the stack
void push(stack *s, const char *elem)
{

    if (s->top < 99)
    {

        strcpy(s->elem[++s->top], elem);
    }
}
// pop a city from the stack
void pop(stack *s)
{
    if (s->top >= 0)
    {
        s->top--;
    }
}
// get the top city from the stack
char *getelem(stack *s)
{
    if (!emptystack(*s))
    {
        return s->elem[s->top];
    }
    return NULL;
}

//--------------dome headers--------------
void adddirpath(const char *filename, ptr1 *head);
void addtofile(FILE *fp, char city1[50], char city2[50], int distance);
void addpath(ptr1 sourcecity, const char *destination, int distance);

//----------------------------- file operations -----------------------------//
// these functions handle file input/output for saving and loading the graph

// to open the file with the mode R read
FILE *openingread(const char *filename)
{ // file* becaus file isnt include in void and it is pointer returne(fp pointer )
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("error opening file");
        return NULL;
    }
    return fp;
}
// to open the file with the mode of A append
FILE *openingwrite(const char *filename)
{ // file* becaus file isnt include in void and it is pointer returne(fp pointer )
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        perror("error opening file");
        return NULL;
    }
    return fp;
}
// to read the whole file
// read to display the contents of a file
void read(FILE *fp)
{
    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
}

// display the contents of a file
void displayfile(const char *filename)
{
    FILE *fp = openingread(filename);
    read(fp);
    fclose(fp);
};

//----------------------------- main functions -----------------------------//
// the main functions for managing the graph , handling the tasks of the lab

// Check if city1 already exists in the graph
ptr1 existcity(ptr1 currentcity, const char city1[50]) // current city is the head of the graph
{
    // iterate through the graph to find the city
    while (currentcity != NULL)
    {
        if (strcmp(currentcity->city1, city1) == 0) // string compare of the current city's name with the target city name
        {
            return currentcity; // city exist return the node
        }
        nextd(&currentcity); // move to the next city in the graph
    }
    return NULL; // city doesnt exist
}

//----------------------------- read file and build graph -----------------------------//
// this function reads a file and builds the graph by adding cities and paths
void readfileandbuildgraph(const char *filename, ptr1 *head)
{
    FILE *fp = openingread(filename);

    char city1[50], city2[50];
    int distance;
    // read the file line by line
    while (fscanf(fp, "%49s %49s %d", city1, city2, &distance) == 3)
    {
        // Ensure city1 exists in the graph
        ptr1 city1n = existcity(*head, city1);
        // doesnt exist ! inserting at the begginng
        if (!city1n)
        {
            allocated(&city1n);
            ass_city1d(&city1n, city1);
            ass_nextd(city1n, *head);
            if (*head)
            {
                ass_prevd(*head, city1n);
            }
            *head = city1n; // update the head of the graph
        }
        // check if city2 exists in the graph
        ptr1 city2n = existcity(*head, city2);
        if (!city2n)
        {
            allocated(&city2n);
            ass_city1d(&city2n, city2);
            ass_nextd(city2n, *head);
            if (*head)
            {
                ass_prevd(*head, city2n);
            }
            *head = city2n;
        }
        // add a path from city1 to city2 with the given distance
        addpath(city1n, city2, distance);
    };
    // close the file after reading
    fclose(fp);
}

//----------------------------- display graph -----------------------------//
// this function displays the entire graph, including cities and their paths

void displaygraph(ptr1 head)
{
    // check if the graph is empty
    if (head == NULL)
    {
        red();
        printf("there is NO MAP !");
        resetColor();
        return;
    }
    // iterate through the graph and display each city and its paths
    ptr1 city0 = head;
    while (city0 != NULL)
    {
        blue();
        printf("\n City: %s\n", namecityd(city0));
        resetColor();

        // get the paths from the current city
        ptr2 pathcity = get_path(city0);

        if (pathcity == NULL) // if the city has no paths
        {
            printf("  ->X ..This city has no paths\n");
        }
        else
        {
            // iterate through the paths and display them
            while (pathcity != NULL)
            {
                printf("    -> %s (%d KM)\n", namecity(pathcity), distancecity(pathcity));
                next(&pathcity);
            }
        }
        // move to the next city in the graph
        nextd(&city0);
    }
}
//-------------------------------------main function--------------------------------------------------

void display_graph(ptr1 head)
{
    printf("\n------ Current Graph ------\n");
    displaygraph(head);
    printf("---------------------------\n");
}

//-------------------------------------------------------------------------------------------------------//
//-------------------------------function of the adding paths----------------------------------
// this function adds a path from one city to another
void addpath(ptr1 sourcecity, const char *destination, int distance)
{
    // allocate memory for a new path
    ptr2 newPath;
    allocate(&newPath);
    ass_city2(newPath, destination);
    ass_data(newPath, distance);

    // link path to the city
    ass_next(newPath, get_path(sourcecity));
    ass_path(sourcecity, newPath);
}

//-----------------
void adddirpath(const char *filename, ptr1 *head)
{
    char city1[50], city2[50];
    int distance;

    printf("enter the source city: ");
    scanf("%49s", city1);
    printf("enter the destination city: ");
    scanf("%49s", city2);
    printf("enter the distance: ");
    scanf("%d", &distance);

    // Check if the source city exists in the graph
    ptr1 sourcecity = existcity(*head, city1);
    if (!sourcecity)
    {
        printf("city '%s' does not exist in the graph!\n", city1);
        return;
    }

    // Add the path to the source city
    addpath(sourcecity, city2, distance);

    // Update the file
    FILE *fp = openingwrite(filename);
    addtofile(fp, city1, city2, distance);
}

//---------indirectly :

// Function to add an indirect path between two cities
void addindirpath(const char *filename, ptr1 *head)
{
    char city1[50], city2[50], intermediate[50];
    int num, distance;

    printf("enter the source city: ");
    scanf("%49s", city1);
    printf("enter the destination city: ");
    scanf("%49s", city2);
    printf("enter the number of intermediate cities: ");
    scanf("%d", &num);

    char currentcity[50];
    strcpy(currentcity, city1);
    int i ; 
    for ( i = 1; i <= num; i++)
    {
        printf("enter the name of intermediate city %d: ", i);
        scanf("%49s", intermediate);
        printf("enter the distance between %s and %s: ", currentcity, intermediate);
        scanf("%d", &distance);

        // Check if the current city exists in the graph
        ptr1 sourcecity = existcity(*head, currentcity);
        if (!sourcecity)
        {
            printf("the city '%s' does not exist in the graph\n", currentcity);
            return;
        }

        // Add the path to the current city
        addpath(sourcecity, intermediate, distance);

        // Update the file
        FILE *fp = openingwrite(filename);
        addtofile(fp, currentcity, intermediate, distance);

        strcpy(currentcity, intermediate); // Move to the next city
    }
    // Add the final path to the destination city
    printf("enter the distance between %s and %s: ", currentcity, city2);
    scanf("%d", &distance);

    ptr1 sourcecity = existcity(*head, currentcity);
    if (!sourcecity)
    {
        printf("The city '%s' does not exist in the graph!\n", currentcity);
        return;
    }

    addpath(sourcecity, city2, distance);
    // Update the file
    FILE *fp = openingwrite(filename);
    addtofile(fp, currentcity, city2, distance);
}

//------function to add paths to file
// remark : a doesnt delete byt w is for the deleting then adding

void addtofile(FILE *fp, char city1[50], char city2[50], int distance)
{
    // Get user input
    green();
    fprintf(fp, "\n %s %s %d", city1, city2, distance);
    printf(" Successfully added: %s -> %s (%d km)\n", city1, city2, distance);
    resetColor();
    fclose(fp);
}

//-------------------------main function to add paths -----------------------------//
// this function allows the user to add a new path between two cities
void add_path(const char *filename, ptr1 *head)
{
    char choice[10];

    printf("do you want to add a direct path or an indirect path?  ");
    scanf("%9s", choice);

    if (strcmp(choice, "direct") == 0)
    {
        adddirpath(filename, head);
    }
    else if (strcmp(choice, "indirect") == 0)
    {
        addindirpath(filename, head);
    }
    else
    {
        printf("Please enter 'direct' or 'indirect',try again\n");
    }
}

//-------------------------------------------------------------------------------------------------------//

//---------------------------------------adding city------------------------------------------//
// this function adds a new city to the graph if it doesn't already exist
void addcity(const char *filename, ptr1 *head, const char *cityname)
{

    ptr1 city1n = existcity(*head, cityname);
    if (city1n == NULL) // if the city does not exist
    {

        allocated(&city1n);
        ass_city1d(&city1n, cityname);
        // link the new city to the graph
        city1n->nextd = *head; // next newnode become first node
        if (*head != NULL)
        {
            (*head)->prevd = city1n;
        }
        *head = city1n; // update head
        green();
        printf("the city '%s'is added successfully.\n", cityname);
        resetColor();
        gray();
        printf("be careful this data will be deleted when you end the program unless you add path to this city :=)");
        resetColor();
    }
    else
    { // the city exist
        printf("City '%s' already exists!\n", cityname);
        return;
    }
}
//--------------------------------------------------main function--------------------------------------------------
void add_city(const char *filename, ptr1 *head)
{
    char city1[50];
    printf("add city... ");
    printf("Enter City1: ");
    scanf("%49s", city1);

    addcity(filename, head, city1);
}

//------------------------------------free graph-------------------------------------------------//
// this function frees all memory allocated for the graph
// needed in the end of the program
void freegraph(ptr1 head)
{
    ptr1 forfree = head;
    while (forfree) // free all paths associated with the current city
    {
        ptr2 temp = get_path(forfree);
        while (temp)
        {
            ptr2 temp2 = temp;
            next(&temp);
            freenode(temp2);
        }
        ptr1 tempp = forfree; // free the current city node
        nextd(&forfree);
        freed(tempp);
    }
}

//------------------------------------------------------------------------------------------------------//
//---------------------------------------reachable cities ------------------------------------------//
// this function displays all cities that can be reached directly from a given city

// the cities that can be reached from given city directly the indirectly
// DIRECTLY :
void reachedcitiesdir(ptr1 head, const char *cityname)
{
    // find the city in the graph
    ptr1 temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->city1, cityname) == 0)
        {
            break; // city found
        }
        nextd(&temp); // move to the next city
    }
    if (!temp) // if the city doent exist
    {
        printf("City '%s' not found!\n", cityname);
        return;
    }
    // display all cities reachable directly from the given city
    printf("cities reachable from %s: \n", temp->city1);
    ptr2 paths = temp->path;
    while (paths != NULL)
    {
        printf("==> %s ( %d KM) \n", paths->city2, paths->data);
        next(&paths); // move to the next path
    }
}
// INDIRECTLY :
//--------this is for reached but in indirect path--------------------

// check if there is a city that we visit in the array , we nned it for later to avoid infinit loop when checking recursively
bool isitvisited(const char *namecity, char visited[][50], int size) // visited is an array store names of the cities been visited (50of there names and the other is for the index(size))
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(namecity, visited[i]) == 0)
        {
            return true; // city has already been visited
        }
    }
    return false; // city has not been visited
}

// this function recursively finds all cities that can be reached indirectly
void indirect(ptr1 head, const char *cityname, char visited[][50], int *size, char thepath[], int distance)
{
    ptr1 temp = existcity(head, cityname); // find the city in the graph
    if (temp == NULL)
    {
        printf("city doent exist , try tp enter existing city ..");
        return; // city doesnt exist
    }
    ptr2 paths = temp->path;
    char secondpath[256];
    while (paths != NULL)
    {
        if (!isitvisited(paths->city2, visited, *size))
        {                                         // here to check if we visited or not if visited we avoid the loop infinite
                                                  //  if didnt visit
            strcpy(visited[*size], paths->city2); // make it as visited by adding it to the array
            (*size)++;                            //+1 to the size

            // make the string to creat the path to be printed
            // the idea here is to create new small string then added to the father string that store the path with the distance
            // by defaul the string is 256 as pascal
            snprintf(secondpath, sizeof(secondpath), "%s -> %s", thepath, paths->city2); // here nlase9 the string jdid bl 9dim
            printf("%s (%d km ) \n", secondpath, distance + paths->data);                // print the path with the data 9dima + jdida ta3 new city
            // here the recursivity to get all the paths
            indirect(head, paths->city2, visited, size, secondpath, (distance + paths->data)); // paramater of the second city in graph
        }
        next(&paths); // next pathc ity
    }
}

void reachedcitiesindir(ptr1 head, const char *cityname)
{

    // Initialize
    char visited[100][50]; // 100 is the size of the array (100 capability of storing cities)&&(the 50 is size of the city name )
    int size = 0;

    strcpy(visited[size], cityname); // the start function , sshould be stored as the first visited city , also to avoid the infinite loop
    size++;

    printf("the cities that reachable from %s indirectly are : \n", cityname);
    indirect(head, cityname, visited, &size, cityname, 0); // distance at first is 0 && we start from the city sourcr
}

//----------------------main function of reachable cities--------------------------//
void reachable_cities(ptr1 head)
{
    char typepath[10];
    char cityreached[50];
    printf("do you want direct path or indirect path?\n");
    scanf("%s", typepath);
    if (strcmp(typepath, "direct") == 0)
    {
        // the direct path
        printf("enter the city : ");
        scanf("%49s", cityreached);
        reachedcitiesdir(head, cityreached);
    }
    else if (strcmp(typepath, "indirect") == 0)
    {
        printf("enter the city : ");
        scanf("%49s", cityreached);
        reachedcitiesindir(head, cityreached);
    }
    else
    {
        printf("invalide path type , please renter 'direct' or 'indirect' \n");
    }
}

//---------------------------------------------------------------------------------------//

//-----------this is for chechking path between two cities--------------------------------//
// notice that :
// here check if exist path or not and creat the stack that contain the path clearly
// here we only need to find hyst one path to say it exist or not

// the function is recursive and use the stack to store the path
bool pathexist(ptr1 head, const char *city1, const char *city2, char visited2[][50], int *size, stack *ofpath)
{
    if (strcmp(city1, city2) == 0)
    {
        push(ofpath, city2); // the first same as it , and push for the pupose to use in the great function that use stack to show the path
        return true;
    }
    ptr1 temp = existcity(head, city1);
    if (temp == NULL)
    {
        return false; // doesnt exist
    }
    // iterate through all paths from the source city
    ptr2 paths = temp->path;
    while (paths != NULL)
    {
        // check if the destination city has already been visited
        if (!isitvisited(paths->city2, visited2, *size))
        {
            strcpy(visited2[*size], paths->city2);
            (*size)++;

            if (pathexist(head, paths->city2, city2, visited2, size, ofpath))
            {                        // here check recursivly if there is path from paths name of city to city target
                push(ofpath, city1); // push the city to the stack to store the path
                return true;         // path exists
            }
            (*size)--; // this is else of if , if we didnt find the target we remov ir from visited array
        }
        next(&paths); // next pathcity
    }
    return false; // not found any path
}

// this function checks if there is a path between two cities and displays it
// here we at least search for a path , to confirm that there is a path , so this function doesnt do all the cases
void checkpath(ptr1 head)
{
    char city1[50], city2[50];
    stack ofpath;
    char visited2[100][50];
    int size = 0;
    printf("checking the path...\n");

    printf("Enter the start city: ");
    scanf("%49s", city1);
    printf("Enter the end city: ");
    scanf("%49s", city2);
    // mark the source city as visited
    strcpy(visited2[size], city1);
    size++;

    creatstack(&ofpath);
    // check if a path exists
    if (pathexist(head, city1, city2, visited2, &size, &ofpath))
    {
        printf("there is path : path between %s and %s:\n", city1, city2);
        // display the path stored in the stack
        while (!emptystack(ofpath))
        {
            printf("%s", getelem(&ofpath));
            pop(&ofpath);
            if (!emptystack(ofpath))
            {
                printf("->");
            }
        }
        printf("\n");
    }
    else
    {
        printf("there is no path");
    }
}
//---------------------------------------------------------------------------------------------------//

//------------------------------------this is for the best path-------------------------------------//
// this function finds the shortest path (best path) between two cities
// it uses recursion to explore all possible paths and keeps track of the shortest one

void bestpath(ptr1 head, const char *source, const char *distination, char visited[][50], int *size, char path[], int distance, char bestpaths[], int *bestdistance)
{
    // if the source city is the same as the destination city //base case
    if (strcmp(source, distination) == 0)
    {
        // update the best path and distance if this path is shorter
        if (*bestdistance == 0 || distance < *bestdistance)
        {

            *bestdistance = distance;
            strcpy(bestpaths, path);
        }
        return;
    }
    // find the source city in the graph
    ptr1 temp = existcity(head, source);
    if (temp == NULL)
    {
        return; // city doenot exist
    }

    // iterate through all paths from the source city
    ptr2 paths = temp->path;
    char newpath[256];
    while (paths != NULL)
    {
        // check if the destination city has already been visited
        if (!isitvisited(paths->city2, visited, *size))
        {
            // mark the city as visited
            strcpy(visited[*size], paths->city2);
            (*size)++;

            snprintf(newpath, sizeof(newpath), "%s -> %s", path, paths->city2); // create a new path string
            // recursively find the best path from the current city to the destination
            bestpath(head, paths->city2, distination, visited, size, newpath, distance + paths->data, bestpaths, bestdistance);
            (*size)--; // remove the city from the visited array
        }
        next(&paths); // move to the next path
    }
}
//-----------------------------------main function -------------------------------------
// this function handles user input and displays the best path between two cities
void best_path(ptr1 head)
{
    char source[50];
    char distination[50];
    // the data from user
    printf("enter the start city: \n");
    scanf("%s", source);
    printf("enter the end city: \n");
    scanf("%s", distination);

    // initialize variables for tracking the best path
    char visited[100][50];
    int size = 0;
    char path[512];
    char bestpaths[512];
    int bestdistance = 0;

    // mark the source city as visited
    strcpy(visited[size], source);
    size++;

    strcpy(path, source);
    // find the best path
    bestpath(head, source, distination, visited, &size, path, 0, bestpaths, &bestdistance);

    // this for display the result
    if (bestdistance == 0)
    {
        printf("No path found between %s and %s.\n", source, distination);
    }
    else
    {
        printf("Best path between %s and %s: %s (%d KM)\n", source, distination, bestpaths, bestdistance);
    }
}

//----------------------------------------------------------------------------------------------//

//------------------------------------deleting city-------------------------------------------------------------//
// this function deletes a city from the graph and removes all paths associated with it
void deletecity(ptr1 *head, const char *cityname)
{
    if (*head == NULL)
    {
        printf("Graph is empty!\n");
        return;
    }
    // find the city in the graph
    ptr1 temp = *head;

    while (temp != NULL && strcmp(temp->city1, cityname) != 0)
    {
        nextd(&temp);
    }
    if (temp == NULL)
    {
        printf("city doesnt exist \n", cityname);
        return;
    }
    // we remove  the paths related to other cities
    ptr1 city = *head;
    while (city != NULL)
    {
        ptr2 path = city->path;
        ptr2 prev = NULL;
        while (path != NULL)
        {
            if (strcmp(path->city2, cityname) == 0)
            {
                if (prev == NULL)
                { // citygraph stay the first and linked by the second path ( we remove the first )
                    city->path = path->next;
                }
                else
                {
                    prev->next = path->next; // we linke the previous path by the next path , to delete the path
                }
                ptr2 delete = path;
                next(&path);
                freenode(delete);
            }
            else
            {
                prev = path;
                next(&path);
            } // to check the next
        }
        nextd(&city); // check the others citygraph to remove the path
    }
    // we delete the city from the graph
    ptr2 path = temp->path; // here we remove there paths
    while (path != NULL)
    {
        ptr2 nextpath = path->next;
        freenode(path);
        path = nextpath;
    }

    if (temp->prevd != NULL)
    {                                     // not the first city
        temp->prevd->nextd = temp->nextd; // temp->prev ( we get the previous city) ->nextd ( we go its ointer and fill it with the next ) =>>>> delete when it is in the middle
    } // go to previous node and modify the pointer next
    else
    {
        *head = temp->nextd; // it is the first node city in the graph
    }

    if (temp->nextd != NULL)
    { // the last node in the graph && the prev update
        temp->nextd->prevd = temp->prevd;
    } // update the previous pointer of the next nodecity in the graph , to not lose the connection :)
    freed(temp);

    printf("it is done deleting ! \n");
    gray();
    printf("warning ! the data in the file would not change..");
    resetColor();
}

//-------------------------main function deletecity ---------------------------------------//

void delete_city(ptr1 *head)
{
    char cityname[50];
    printf("enter the cityname you want to delete ? : \n");
    scanf("%49s", cityname);

    deletecity(head, cityname);
}

//---------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//----------------------------------------MENUU------------------------------------------------

//-----this for displaying the menu and handling user input for menu navigation

// this function displays the menu and highlights the selected option
void displayMenu(int highlightedOption)
{

    /* The menu, offering users the ability to select their desired options */
    system("cls");
    int i;
    // display the menu header

    printf(ANSI_COLOR_BLUE);
    printf("\n       _ __ ___   ___ _ __  _   _  \n");
    printf("      | '_ ` _ \\ / _ \\ '_ \\| | | | \n");
    printf("      | | | | | |  __/ | | | |_| | \n");
    printf("      |_| |_| |_|\\___|_| |_|\\__,_| \n\n");
    printf(ANSI_COLOR_RESET);

    char *menuItems[] = {
        "1. Display City Graph",
        "2. Add New City",
        "3. Add New Path",
        "4. Show Reachable Cities",
        "5. is there a path between two cities ",
        "6. the shortest path",
        "7. deleting a city",
        "8. Exit Program"};

    for (i = 0; i < 8; i++)
    {
        if (i == highlightedOption)
        {
            printf(ANSI_COLOR_LIGHT_BLUE "[-->] " ANSI_COLOR_WHITE);
        }
        else
        {
            printf(ANSI_COLOR_WHITE "[   ] ");
        }
        printf("%s\n", menuItems[i]);
    }
};
// for the menu navigation
//  this function handles user input for menu navigation and returns the selected option
int getMenuChoice()
{

    int ch = 0;
    int selected;
    selected = 0; // default to the first menu option

    do
    {
        displayMenu(selected);
        ch = getch(); // get user input

        if (ch == 0 || ch == 224)
        {
            ch = getch();
            switch (ch)
            {
            case KEY_UP:
                if (selected > 0)
                    selected--; // move up in the menu
                break;
            case KEY_DOWN:
                if (selected < 7)
                    selected++;
                break;
            }
        }
        else if (ch == KEY_ENTER) // handle enter key
        {
            return selected;
        }
        else if (ch == KEY_ESC)
        {
            return 7; // exit the program
        }
    } while (1); // keep looping until a valid input is received
};

//------------------------------------------------------------------
//------------------------------------------------------------------

//--------------------------------------------MAIN PROGRAM-----------------------------------------------------
//handel all the previous functions , confirming it is user friendly and easy to use
int main()
{
    ptr1 head = NULL;
    int choice;
    char filename[70];

    do
    {
        yellow();
        printf("Welcome to the City Graph Program!\n");
        printf("Please note: All city names should be entered in lowercase letters (a-z).\n");
        printf("  - Use the UP and DOWN arrow keys to move between options.\n");
        printf("  - Press ENTER to select an option.\n");
        printf("  - Press ESC to exit the program or choose the last option.\n\n");
        resetColor();
        printf("Enter the file name to load the city graph data: ");
        scanf("%s", filename);

        FILE *fp = openingread(filename);
        if (fp != NULL)
        {
            fclose(fp); // file exists, close
            green();
            printf("File '%s' loaded successfully!\n", filename);
            resetColor();
            break;
        }

        red();
        printf("Oops  :( , didnt find the file ,Please try again \n");
        resetColor();

    } while (1); // Keep asking until a valid file is given

    readfileandbuildgraph(filename, &head);
    do
    {
        choice = getMenuChoice();
        switch (choice)
        {
        case 0:
            printf("\nDisplaying the current city graph...\n");
            display_graph(head);
            break;
        case 1:
            printf("\nAdding a new city to the graph...\n");
            add_city(filename, &head);
            break;
        case 2:
            printf("\nAdding a new path between two cities...\n");
            add_path(filename, &head);
            break;
        case 3:
            printf("\nFinding reachable cities...\n");
            reachable_cities(head);
            break;

        case 4:
            printf("\nChecking if a path exists between two cities...\n");
            checkpath(head);
            break;
        case 5:
            printf("\nFinding the shortest path between two cities...\n");
            best_path(head);
            break;
        case 6:
            printf("\nDeleting a city from the graph...\n");
            delete_city(&head);
            break;
        case 7:
            printf("\nThank you for using the City Graph Program!\n");
            printf("Exiting...\n");
            freegraph(head);
            break;
        }

        if (choice != 7)
        {
            printf("\nPress any key to continue...");
            getch();
        }

    } while (choice != 7);
    return 0;
}
//----------------------end :) -----------------------------------------------//
