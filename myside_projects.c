#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// my side projects
// here are my github desktops

// Structure to store book information
struct Book {
    int id;
    char title[50];
    char author[50];
    int is_available;  // 1 if available, 0 if borrowed
};
// done it with the help of AI
// Function prototypes
void addBook(FILE *file);
void displayBooks(FILE *file);
void searchBook(FILE *file);
void borrowBook(FILE *file);
void returnBook(FILE *file);

// creating my C projects

int main() {
    FILE *file;
    int choice;

    // Open file in append and read mode
    file = fopen("library.dat", "ab+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

// i am returnning this file

    while(1) {
        printf("\n=== Library Management System ===\n");
        printf("1. Add New Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Borrow Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook(file);
                break;
            case 2:
                displayBooks(file);
                break;
            case 3:
                searchBook(file);
                break;
            case 4:
                borrowBook(file);
                break;
            case 5:
                returnBook(file);
                break;
            case 6:
                fclose(file);
                printf("Thank you for using the system!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addBook(FILE *file) {
    struct Book book;

    printf("Enter Book ID: ");
    scanf("%d", &book.id);

    printf("Enter Book Title: ");
    scanf(" %[^\n]s", book.title);

    printf("Enter Author Name: ");
    scanf(" %[^\n]s", book.author);

    book.is_available = 1;  // New book is available by default

    fwrite(&book, sizeof(struct Book), 1, file);
    printf("Book added successfully!\n");
}

void displayBooks(FILE *file) {
    struct Book book;

    rewind(file);  // Move file pointer to beginning

    printf("\nBook ID\tTitle\tAuthor\tStatus\n");
    printf("--------------------------------\n");

    while(fread(&book, sizeof(struct Book), 1, file)) {
        printf("%d\t%s\t%s\t%s\n",
               book.id,
               book.title,
               book.author,
               book.is_available ? "Available" : "Borrowed");
    }
}

void searchBook(FILE *file) {
    struct Book book;
    int id, found = 0;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    rewind(file);

    while(fread(&book, sizeof(struct Book), 1, file)) {
        if(book.id == id) {
            printf("\nBook Found!\n");
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            printf("Status: %s\n", book.is_available ? "Available" : "Borrowed");
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Book not found!\n");
    }
}

void borrowBook(FILE *file) {
    struct Book book;
    int id, found = 0;
    long pos;

    printf("Enter Book ID to borrow: ");
    scanf("%d", &id);

    rewind(file);

    while(fread(&book, sizeof(struct Book), 1, file)) {
        if(book.id == id) {
            pos = ftell(file) - sizeof(struct Book);
            found = 1;
            break;
        }
    }

    if(found) {
        if(book.is_available) {
            book.is_available = 0;
            fseek(file, pos, SEEK_SET);
            fwrite(&book, sizeof(struct Book), 1, file);
            printf("Book borrowed successfully!\n");
        } else {
            printf("Book is already borrowed!\n");
        }
    } else {
        printf("Book not found!\n");
    }
}

void returnBook(FILE *file) {
    struct Book book;
    int id, found = 0;
    long pos;

    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    rewind(file);

    while(fread(&book, sizeof(struct Book), 1, file)) {
        if(book.id == id) {
            pos = ftell(file) - sizeof(struct Book);
            found = 1;
            break;
        }
    }

    if(found) {
        if(!book.is_available) {
            book.is_available = 1;
            fseek(file, pos, SEEK_SET);
            fwrite(&book, sizeof(struct Book), 1, file);
            printf("Book returned successfully!\n");
        } else {
            printf("Book is already in library!\n");
        }
    } else {
        printf("Book not found!\n");
    }
}
