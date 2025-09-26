#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/

#define MAX_LIBRARY_SIZE 20  /* 20 books max */
#define MAX_TITLE_SIZE   15  /* +1 for '\0' */
#define MAX_AUTHOR_SIZE  15
#define MAX_ISBN_SIZE    11  /* 10 digits + '\0' */
#define MAX_GENRE_SIZE   10

#define DB_FILENAME "library.txt"

/*******************************************************************************
 * List structs
*******************************************************************************/
typedef struct publication_date {
    int month; /* 1–12 inclusive */
    int year;  /* 1950–2024 inclusive */
} date_t;

typedef struct book {
    char title[MAX_TITLE_SIZE+1];
    char author[MAX_AUTHOR_SIZE+1];
    char isbn[MAX_ISBN_SIZE+1];
    date_t publication_date;
    char genre[MAX_GENRE_SIZE+1];
} book_t;

book_t booklist[MAX_LIBRARY_SIZE];
int bookCount = 0;

/*******************************************************************************
 * Function prototypes
*******************************************************************************/
void printMenu(void);
void clearInputBuffer(void);
void readLine(char *buffer, int size);
unsigned int readUnsignedInt(unsigned int minValue, unsigned int maxValue, const char* prompt);
int isValidISBN(const char *isbn);

void addBook(void);
void removeLastBook(void);
void displayBookList(void);
void saveToFile(void);
void loadFromFile(void);
void exitProgram(void);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void) {
    int choice = 0;

    while (1) {
        printMenu();
        printf("Enter your choice>\n");
        fflush(stdout);

        if (scanf("%d", &choice) != 1) {
            return 0;
        }
        (void)getchar(); /* clear newline */

        switch (choice) {
            case 1: addBook(); break;
            case 2: removeLastBook(); break;
            case 3: displayBookList(); break;
            case 4: saveToFile(); break;
            case 5: loadFromFile(); break;
            case 6: exitProgram(); return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}

/*******************************************************************************
 * Menu + helpers
*******************************************************************************/
void printMenu(void) {
    printf("\nLibrary Management System\n"
           "1. Add book\n"
           "2. Delete last book\n"
           "3. Display book list\n"
           "4. Save the book list to the database\n"
           "5. Read the book list from the database\n"
           "6. Exit the program\n");
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0'; /* strip newline */
}

unsigned int readUnsignedInt(unsigned int minValue, unsigned int maxValue, const char* prompt) {
    char line[128];
    unsigned int value;
    while (1) {
        printf("%s", prompt);
        readLine(line, sizeof(line));
        if (sscanf(line, "%u", &value) == 1) {
            if (value >= minValue && value <= maxValue) {
                return value;
            }
        }
        printf("Invalid input.\n");
    }
}

int isValidISBN(const char *isbn) {
    int length = strlen(isbn);
    int i;
    if (length != 10) { /* force exactly 10 digits */
        printf("Invalid ISBN.\n");
        return 0;
    }
    for (i = 0; i < length; i++) {
        if (isbn[i] < '0' || isbn[i] > '9') {
            printf("Invalid ISBN.\n");
            return 0;
        }
    }
    return 1;
}

/*******************************************************************************
 * Core functionality
*******************************************************************************/
void addBook(void) {
    book_t newBook;

    if (bookCount >= MAX_LIBRARY_SIZE) {
        printf("List is full\n");
        return;
    }

    clearInputBuffer();

    printf("Title: >");
    fflush(stdout);
    readLine(newBook.title, MAX_TITLE_SIZE + 1);

    printf("Author: >");
    fflush(stdout);
    readLine(newBook.author, MAX_AUTHOR_SIZE + 1);

    printf("ISBN: >");
    fflush(stdout);
    readLine(newBook.isbn, MAX_ISBN_SIZE + 1);
    if (!isValidISBN(newBook.isbn)) {
        return;
    }

    newBook.publication_date.month =
        readUnsignedInt(1, 12, "Publication_date(month): >");

    newBook.publication_date.year =
        readUnsignedInt(1950, 2024, "Publication_date(year): >");

    printf("Genre: >");
    fflush(stdout);
    readLine(newBook.genre, MAX_GENRE_SIZE + 1);

    booklist[bookCount] = newBook;
    bookCount++;

    printf("Book added successfully!\n");
}

void removeLastBook(void) {
    if (bookCount > 0) {
        bookCount--;
        printf("Last book removed.\n");
    } else {
        printf("List is empty\n");
    }
}

void displayBookList(void) {
    int i;
    char dateBuffer[20];

    if (bookCount == 0) {
        printf("List is empty\n");
        return;
    }

    printf("Title          Author         ISBN       Pub. Date Genre\n");
    printf("----------     ----------     ---------- --------- --------\n");

    for (i = 0; i < bookCount; i++) {
        sprintf(dateBuffer, "%02u-%04u",
                booklist[i].publication_date.month,
                booklist[i].publication_date.year);

        printf("%-14.10s %-14.14s %-10.11s %-9s %s\n",
               booklist[i].title,
               booklist[i].author,
               booklist[i].isbn,
               dateBuffer,
               booklist[i].genre);
    }
}

void saveToFile(void) {
    FILE *fp = fopen(DB_FILENAME, "w");
    int i;
    if (fp == NULL) {
        printf("Write error\n");
        return;
    }

    fprintf(fp, "%d\n", bookCount);
    for (i = 0; i < bookCount; i++) {
        fprintf(fp, "%s\n", booklist[i].title);
        fprintf(fp, "%s\n", booklist[i].author);
        fprintf(fp, "%s\n", booklist[i].isbn);
        fprintf(fp, "%u %u\n",
                booklist[i].publication_date.month,
                booklist[i].publication_date.year);
        fprintf(fp, "%s\n", booklist[i].genre);
    }
    fclose(fp);
    printf("Library saved.\n");
}

void loadFromFile(void) {
    FILE *fp = fopen(DB_FILENAME, "r");
    char titlebuf[MAX_TITLE_SIZE+1], authorbuf[MAX_AUTHOR_SIZE+1];
    char isbnbuf[MAX_ISBN_SIZE+1], genrebuff[MAX_GENRE_SIZE+1];
    unsigned int monthv, yearv;
    int count = 0, i;

    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }

    if (fscanf(fp, "%d\n", &count) != 1) {
        printf("Error: invalid file format.\n");
        fclose(fp);
        return;
    }

    if (count > MAX_LIBRARY_SIZE) {
        count = MAX_LIBRARY_SIZE;
    }

    for (i = 0; i < count; i++) {
        if (fgets(titlebuf, sizeof(titlebuf), fp) == NULL) { count = i; break; }
        titlebuf[strcspn(titlebuf, "\n")] = '\0';

        if (fgets(authorbuf, sizeof(authorbuf), fp) == NULL) { count = i; break; }
        authorbuf[strcspn(authorbuf, "\n")] = '\0';

        if (fgets(isbnbuf, sizeof(isbnbuf), fp) == NULL) { count = i; break; }
        isbnbuf[strcspn(isbnbuf, "\n")] = '\0';

        if (fscanf(fp, "%u %u\n", &monthv, &yearv) != 2) { count = i; break; }

        if (fgets(genrebuff, sizeof(genrebuff), fp) == NULL) { count = i; break; }
        genrebuff[strcspn(genrebuff, "\n")] = '\0';

        strncpy(booklist[i].title, titlebuf, MAX_TITLE_SIZE);
        booklist[i].title[MAX_TITLE_SIZE] = '\0';

        strncpy(booklist[i].author, authorbuf, MAX_AUTHOR_SIZE);
        booklist[i].author[MAX_AUTHOR_SIZE] = '\0';

        strncpy(booklist[i].isbn, isbnbuf, MAX_ISBN_SIZE);
        booklist[i].isbn[MAX_ISBN_SIZE] = '\0';

        booklist[i].publication_date.month = monthv;
        booklist[i].publication_date.year = yearv;

        strncpy(booklist[i].genre, genrebuff, MAX_GENRE_SIZE);
        booklist[i].genre[MAX_GENRE_SIZE] = '\0';
    }

    bookCount = count;
    fclose(fp);
    printf("Library loaded. %d record(s).\n", bookCount);
}

void exitProgram(void) {
    printf("Exiting program.\n");
}
