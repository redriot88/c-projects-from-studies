/* Lib_Mng.c
   Library management program implementing the assignment specification.
   Uses only: stdio.h, stdlib.h, string.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIBRARY_SIZE 20
#define MAX_TITLE_SIZE  16   /* 15 chars + '\\0' */
#define MAX_AUTHOR_SIZE 16
#define MAX_ISBN_SIZE   12   /* up to 11 digits + '\\0' */
#define MAX_GENRE_SIZE  11   /* 10 chars + '\\0' */
#define DB_FILENAME     "library"

typedef struct {
    unsigned int month;   /* 1..12 */
    unsigned int year;    /* 1950..2024 */
} date_t;

typedef struct {
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
    char isbn[MAX_ISBN_SIZE];
    date_t publication_date;
    char genre[MAX_GENRE_SIZE];
} book_t;

/* Function prototypes */
void printMenu(void);
void clearInputBuffer(void);
void addBook(book_t booklist[], int *bookcount);
void removeLastBook(book_t booklist[], int *bookcount);
void displayBookList(const book_t booklist[], int bookcount);
void saveToFile(const book_t booklist[], int bookcount);
void loadFromFile(book_t booklist[], int *bookcount);

/* Helper prototypes */
void readLineTrim(char *buf, int size);
unsigned int readUnsignedInRange(unsigned int minv, unsigned int maxv, const char *prompt);

int main(void)
{
    book_t booklist[MAX_LIBRARY_SIZE];
    int bookcount;
    int choice;
    bookcount = 0;

    while (1) {
        printMenu();
        printf("Enter your choice> ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice < 1 || choice > 6) {
            printf("Invalid choice.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addBook(booklist, &bookcount);
                break;
            case 2:
                removeLastBook(booklist, &bookcount);
                break;
            case 3:
                displayBookList(booklist, bookcount);
                break;
            case 4:
                saveToFile(booklist, bookcount);
                break;
            case 5:
                loadFromFile(booklist, &bookcount);
                break;
            case 6:
                /* Exit gracefully */
                return 0;
            default:
                /* unreachable */
                break;
        }
    }

    return 0;
}

/* Print menu exactly as required */
void printMenu(void)
{
    printf("\nLibrary Management System\n");
    printf("1. Add book\n");
    printf("2. Delete last book\n");
    printf("3. Display book list\n");
    printf("4. Save the book list to the database\n");
    printf("5. Read the book list from the database\n");
    printf("6. Exit the program\n");
}

/* Clear remaining characters on stdin until newline */
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

/* Read a line into buf (including spaces), trim trailing newline */
void readLineTrim(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL) {
        /* EOF or error: ensure empty string */
        buf[0] = '\0';
        return;
    }
    /* remove trailing newline if present */
    buf[strcspn(buf, "\n")] = '\0';
}

/* Read unsigned integer with range checking using fgets+sscanf */
unsigned int readUnsignedInRange(unsigned int minv, unsigned int maxv, const char *prompt)
{
    char line[128];
    unsigned int val;
    while (1) {
        printf("%s", prompt);
        readLineTrim(line, sizeof(line));
        if (sscanf(line, "%u", &val) == 1) {
            if (val >= minv && val <= maxv) {
                return val;
            } else {
                printf("Invalid value. Please enter a number between %u and %u.\n", minv, maxv);
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
        }
    }
}

/* Add book: prompt user and store in array */
void addBook(book_t booklist[], int *bookcount)
{
    book_t nb;
    if (*bookcount >= MAX_LIBRARY_SIZE) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    /* Read strings with fgets to allow spaces */
    printf("Title: >");
    readLineTrim(nb.title, MAX_TITLE_SIZE);

    printf("Author: >");
    readLineTrim(nb.author, MAX_AUTHOR_SIZE);

    printf("ISBN: >");
    readLineTrim(nb.isbn, MAX_ISBN_SIZE);

    /* Publication date: month and year with validation */
    nb.publication_date.month = readUnsignedInRange(1, 12, "Publication date(month): >");
    nb.publication_date.year = readUnsignedInRange(1950, 2024, "Publication date(year): >");

    printf("Genre: >");
    readLineTrim(nb.genre, MAX_GENRE_SIZE);

    /* Store the book */
    booklist[*bookcount] = nb;
    (*bookcount)++;
    printf("Book added successfully!\n");
}

/* Remove the last book (decrement count) */
void removeLastBook(book_t booklist[], int *bookcount)
{
    if (*bookcount <= 0) {
        printf("No books to remove.\n");
        return;
    }
    (*bookcount)--;
    printf("Last book removed.\n");
}

/* Display list with strict formatting */
void displayBookList(const book_t booklist[], int bookcount)
{
    int i;
    char datebuf[16];

    if (bookcount == 0) {
        printf("Library is empty.\n");
        return;
    }

    /* Header: align to column widths */
    /* Title 15 left, Author 15 left, ISBN 11, Publication Date (we reserve 20), Genre 10 */
    printf("%-15s %-15s %-11s %-20s %-10s\n",
           "Title", "Author", "ISBN", "Publication Date", "Genre");
    printf("--------------- --------------- ----------- -------------------- ----------\n");

    for (i = 0; i < bookcount; i++) {
        /* format date as MM-YYYY into datebuf then print left-aligned in 20 char column */
        snprintf(datebuf, sizeof(datebuf), "%02u-%04u",
                 booklist[i].publication_date.month,
                 booklist[i].publication_date.year);

        /* Print each row ensuring the field width limits are respected by storing/truncation rules */
        printf("%-15s %-15s %-11s %-20s %-10s\n",
               booklist[i].title,
               booklist[i].author,
               booklist[i].isbn,
               datebuf,
               booklist[i].genre);
    }
}

/* Save to file named "library" (text). Format:
   first line: bookcount
   then for each book 5 lines:
     title
     author
     isbn
     month year
     genre
*/
void saveToFile(const book_t booklist[], int bookcount)
{
    FILE *fp;
    int i;

    fp = fopen(DB_FILENAME, "w");
    if (fp == NULL) {
        printf("Error: cannot open file for writing.\n");
        return;
    }

    fprintf(fp, "%d\n", bookcount);
    for (i = 0; i < bookcount; i++) {
        fprintf(fp, "%s\n", booklist[i].title);
        fprintf(fp, "%s\n", booklist[i].author);
        fprintf(fp, "%s\n", booklist[i].isbn);
        fprintf(fp, "%u %u\n",
                booklist[i].publication_date.month,
                booklist[i].publication_date.year);
        fprintf(fp, "%s\n", booklist[i].genre);
    }

    fclose(fp);
    printf("Library saved to file.\n");
}

/* Load from file created by this program */
void loadFromFile(book_t booklist[], int *bookcount)
{
    FILE *fp;
    char line[256];
    int i;
    int count;
    char titlebuf[MAX_TITLE_SIZE];
    char authorbuf[MAX_AUTHOR_SIZE];
    char isbnbuf[MAX_ISBN_SIZE];
    char genrebuff[MAX_GENRE_SIZE];
    unsigned int monthv, yearv;

    fp = fopen(DB_FILENAME, "r");
    if (fp == NULL) {
        printf("Error: cannot open file for reading.\n");
        return;
    }

    /* Read first line for count (use fgets+sscanf for safety) */
    if (fgets(line, sizeof(line), fp) == NULL) {
        printf("Invalid file format.\n");
        fclose(fp);
        return;
    }
    if (sscanf(line, "%d", &count) != 1) {
        printf("Invalid file format.\n");
        fclose(fp);
        return;
    }
    if (count < 0 || count > MAX_LIBRARY_SIZE) {
        printf("Invalid file content.\n");
        fclose(fp);
        return;
    }

    /* Read each record */
    for (i = 0; i < count; i++) {
        /* title */
        if (fgets(titlebuf, sizeof(titlebuf), fp) == NULL) { count = i; break; }
        titlebuf[strcspn(titlebuf, "\n")] = '\0';

        /* author */
        if (fgets(authorbuf, sizeof(authorbuf), fp) == NULL) { count = i; break; }
        authorbuf[strcspn(authorbuf, "\n")] = '\0';

        /* isbn */
        if (fgets(isbnbuf, sizeof(isbnbuf), fp) == NULL) { count = i; break; }
        isbnbuf[strcspn(isbnbuf, "\n")] = '\0';

        /* month year */
        if (fgets(line, sizeof(line), fp) == NULL) { count = i; break; }
        if (sscanf(line, "%u %u", &monthv, &yearv) != 2) { count = i; break; }

        /* genre */
        if (fgets(genrebuff, sizeof(genrebuff), fp) == NULL) { count = i; break; }
        genrebuff[strcspn(genrebuff, "\n")] = '\0';

        /* copy into booklist with truncation safety */
        strncpy(booklist[i].title, titlebuf, MAX_TITLE_SIZE - 1);
        booklist[i].title[MAX_TITLE_SIZE - 1] = '\0';

        strncpy(booklist[i].author, authorbuf, MAX_AUTHOR_SIZE - 1);
        booklist[i].author[MAX_AUTHOR_SIZE - 1] = '\0';

        strncpy(booklist[i].isbn, isbnbuf, MAX_ISBN_SIZE - 1);
        booklist[i].isbn[MAX_ISBN_SIZE - 1] = '\0';

        booklist[i].publication_date.month = monthv;
        booklist[i].publication_date.year = yearv;

        strncpy(booklist[i].genre, genrebuff, MAX_GENRE_SIZE - 1);
        booklist[i].genre[MAX_GENRE_SIZE - 1] = '\0';
    }

    *bookcount = count;
    fclose(fp);
    printf("Library loaded from file. %d record(s) read.\n", *bookcount);
}
