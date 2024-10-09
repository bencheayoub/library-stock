#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book {
    char title[100];
    int quantity;
};

struct Library {
    struct Book *books;
    int numBooks;
    int c;
};


void initLibrary(struct Library *library, int initialCapacity) {
    library->numBooks = 0;
    library->c = initialCapacity;
    library->books = (struct Book *)malloc(initialCapacity * sizeof(struct Book));
}



void addBook(struct Library *library, char *title) {

    if (library->numBooks == library->c) {
        library->c *= 2;
        library->books = (struct Book *)realloc(library->books, library->c * sizeof(struct Book));
    }


    for (int i = 0; i < library->numBooks; i++) {
        if (strcmp(library->books[i].title, title) == 0) {
            library->books[i].quantity++;
            return;
        }
    }


    strcpy(library->books[library->numBooks].title, title);
    library->books[library->numBooks].quantity = 1;
    library->numBooks++;
}


void retBook(struct Library *library, char *title) {
    int nf = 0;
    for (int i = 0; i < library->numBooks; i++) {
        if (strcmp(library->books[i].title, title) == 0) {
            nf = 1;
            library->books[i].quantity--;

            if (library->books[i].quantity == 0) {
                for (int j = i; j < library->numBooks - 1; j++) {
                    strcpy(library->books[j].title, library->books[j + 1].title);
                    library->books[j].quantity = library->books[j + 1].quantity;
                }
                library->numBooks--;
            }
            break;
        }
    }

    if (!nf)
        printf("the book \"%s\" doesn't exist in the library.\n", title);
}


int main() {
    struct Library library;
    int initialCapacity = 10;
    initLibrary(&library, initialCapacity);

    char title[100];
    int choice;

    printf("enter the information for the books:\n");

    do {
        printf("enter title of the book: ");
        scanf("%s", title);
        addBook(&library, title);

        printf("do you want to add another book? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
    } while (choice != 0);


    printf("\nbooks in the library:\n");
    for (int i = 0; i < library.numBooks; i++) {
        printf("%s (%d)\n", library.books[i].title, library.books[i].quantity);
    }

    printf("do you wanna remove a book from libraby enter the information for the books:\n");
    do {
        printf("enter title of the book: ");
        scanf("%s", title);
        retBook(&library, title);

        printf("do you want to remove another book? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
    } while (choice != 0);

    printf("\nbooks in the library:\n");
    for (int i = 0; i < library.numBooks; i++) {
        printf("%s (%d)\n", library.books[i].title, library.books[i].quantity);
    }

    return 0;
}
