#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

// Book structure
struct books {
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b;

// Student structure
struct student {
    int id;
    char sname[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
} s;

// Global file pointer
FILE *fp;

// Function declarations
void addBook();
void viewBookList();
void removeBook();
void issueBook();
void viewIssuedBooks();  // ? New function added

int main() {
    int ch;
    while (1) {
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1. Add Book\n");
        printf("2. View Book List\n");
        printf("3. Remove Book\n");
        printf("4. Issue Book\n");
        printf("5. View Issued Book List\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 0:
            exit(0);
        case 1:
            addBook();
            break;
        case 2:
            viewBookList();
            break;
        case 3:
            removeBook();
            break;
        case 4:
            issueBook();
            break;
        case 5:
            viewIssuedBooks();  // ? Fixed: properly added
            break;
        default:
            printf("Invalid Choice...\n\n");
        }

        printf("\n\nPress any key to continue...");
        getch();
    }
    return 0;
}

// Add Book Function
void addBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");
    if (fp == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Name: ");
    fflush(stdin);
    fgets(b.bookName, sizeof(b.bookName), stdin);
    b.bookName[strcspn(b.bookName, "\n")] = '\0';

    printf("Enter Author Name: ");
    fflush(stdin);
    fgets(b.authorName, sizeof(b.authorName), stdin);
    b.authorName[strcspn(b.authorName, "\n")] = '\0';

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("Book Added Successfully");
}

// View Book List Function
void viewBookList() {
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book ID", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    if (fp == NULL) {
        printf("No books found.\n");
        return;
    }

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

// Remove Book Function
void removeBook() {
    int id, found = 0;
    system("cls");
    printf("<== Remove Book ==>\n\n");
    printf("Enter Book ID to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    if (fp == NULL) {
        printf("No books to remove.\n");
        return;
    }

    ft = fopen("temp.txt", "wb");
    if (ft == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (id == b.id) {
            found = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found) {
        printf("\nBook Deleted Successfully");
    } else {
        printf("\nNo Book Found with ID %d", id);
    }
}

// Issue Book Function
void issueBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int found = 0;
    system("cls");
    printf("<== Issue Book ==>\n\n");
    printf("Enter Book ID to issue: ");
    scanf("%d", &s.id);

    fp = fopen("books.txt", "rb");
    if (fp == NULL) {
        printf("No books available.\n");
        return;
    }

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id == s.id) {
            strcpy(s.bookName, b.bookName);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("\nNo Book found with this ID.\n");
        return;
    }

    fp = fopen("issue.txt", "ab");
    if (fp == NULL) {
        printf("Unable to open issue file.\n");
        return;
    }

    printf("Enter Student Name: ");
    fflush(stdin);
    fgets(s.sname, sizeof(s.sname), stdin);
    s.sname[strcspn(s.sname, "\n")] = '\0';

    printf("Enter Student Class: ");
    fflush(stdin);
    fgets(s.sClass, sizeof(s.sClass), stdin);
    s.sClass[strcspn(s.sClass, "\n")] = '\0';

    printf("Enter Student Roll Number: ");
    scanf("%d", &s.sRoll);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nBook Issued Successfully!\n");
}

// ? View Issued Books Function (choice 5)
void viewIssuedBooks() {
    system("cls");
    printf("<== Issued Book List ==>\n\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.ID", "Name", "Class", "Roll.No", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    if (fp == NULL) {
        printf("No issued books found.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sname, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}

