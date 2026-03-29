#include <stdio.h>
#include <string.h>

typedef struct book {
    char book_name[50];
    char authur_name[50];
    float price;
    int id;
} book;

typedef struct issue_book {
    char student_name[50];
    int issue_book_id;
    char book_name[50];
} issue;

void add_book() {
    FILE *fp = fopen("Book.txt", "a");
    book b;

    if (!fp) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter book name : ");
    scanf(" %[^\n]", b.book_name);

    printf("Enter author name : ");
    scanf(" %[^\n]", b.authur_name);

    printf("Enter price : ");
    scanf("%f", &b.price);

    printf("Enter id : ");
    scanf("%d", &b.id);

    fprintf(fp, "%s %s %.2f %d\n", b.book_name, b.authur_name, b.price, b.id);
    fclose(fp);
}

void show_book() {
    book b;
    FILE *fp = fopen("Book.txt", "r");

    if (!fp) {
        printf("No data found!\n");
        return;
    }

    printf("==== Book list ====\n");
    while (fscanf(fp, "%s %s %f %d", b.book_name, b.authur_name, &b.price, &b.id) != EOF) {
        printf("Book Name   = %s\n", b.book_name);
        printf("Author Name = %s\n", b.authur_name);
        printf("Price       = %.2f\n", b.price);
        printf("ID          = %d\n\n", b.id);
    }
    fclose(fp);
}

void delete_book() {
    book b;
    FILE *fp = fopen("Book.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int id, found = 0;

    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter book id: ");
    scanf("%d", &id);

    while (fscanf(fp, "%s %s %f %d", b.book_name, b.authur_name, &b.price, &b.id) != EOF) {
        if (b.id != id) {
            fprintf(temp, "%s %s %.2f %d\n", b.book_name, b.authur_name, b.price, b.id);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("Book.txt");
    rename("temp.txt", "Book.txt");

    if (found) printf("Book deleted successfully.\n");
    else printf("Book id not found.\n");
}

void issue_book() {
    int found = 0;
    issue B;
    book b;
    FILE *fp = fopen("Book.txt", "r");
    FILE *fp_issue = fopen("issue.txt", "a");
    FILE *fp_temp = fopen("temp.txt", "w");

    if (!fp || !fp_issue || !fp_temp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter student Name: ");
    scanf(" %[^\n]", B.student_name);

    printf("Enter book id: ");
    scanf("%d", &B.issue_book_id);

    while (fscanf(fp, "%s %s %f %d", b.book_name, b.authur_name, &b.price, &b.id) == 4) {
        if (b.id == B.issue_book_id) {
            fprintf(fp_issue, "%s %s %d\n", b.book_name, B.student_name, b.id);
            found = 1;
        } else {
            fprintf(fp_temp, "%s %s %.2f %d\n", b.book_name, b.authur_name, b.price, b.id);
        }
    }

    fclose(fp);
    fclose(fp_issue);
    fclose(fp_temp);

    remove("Book.txt");
    rename("temp.txt", "Book.txt");

    if (found) printf("Book issued successfully\n");
    else printf("Book is not available\n");
}

void show_issued_book() {
    issue B;
    FILE *fp_issue = fopen("issue.txt", "r");

    if (!fp_issue) {
        printf("No issued books found!\n");
        return;
    }

    printf("==== Issued book list ====\n");
    while (fscanf(fp_issue, "%s %s %d", B.book_name, B.student_name, &B.issue_book_id) != EOF) {
        printf("Book Name   = %s\n", B.book_name);
        printf("Student Name= %s\n", B.student_name);
        printf("Book ID     = %d\n\n", B.issue_book_id);
    }
    fclose(fp_issue);
}

void return_issue_book() {
    issue B;
    book b;
    FILE *fp = fopen("Book.txt", "a");
    FILE *fp_issue = fopen("issue.txt", "r");
    FILE *fp_temp = fopen("temp.txt", "w");
    int return_book_id, found = 0;

    if (!fp || !fp_issue || !fp_temp) {
        printf("File error!\n");
        return;
    }

    printf("Return Book Id: ");
    scanf("%d", &return_book_id);

    while (fscanf(fp_issue, "%s %s %d", B.book_name, B.student_name, &B.issue_book_id) == 3) {
        if (B.issue_book_id == return_book_id) {
            printf("Enter author name: ");
            scanf(" %[^\n]", b.authur_name);
            printf("Enter price: ");
            scanf("%f", &b.price);

            strcpy(b.book_name, B.book_name);
            b.id = return_book_id;

            fprintf(fp, "%s %s %.2f %d\n", b.book_name, b.authur_name, b.price, b.id);
            found = 1;
        } else {
            fprintf(fp_temp, "%s %s %d\n", B.book_name, B.student_name, B.issue_book_id);
        }
    }

    fclose(fp);
    fclose(fp_issue);
    fclose(fp_temp);

    remove("issue.txt");
    rename("temp.txt", "issue.txt");

    if (found) printf("Book returned successfully\n");
    else printf("Book ID not found\n");
}

int main() {
    int choice;

    while (1) {
        printf("=== Book Management System ===\n");
        printf("1. Add Book\n");
        printf("2. Show All Book\n");
        printf("3. Delete Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Show Issued Books\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_book(); break;
            case 2: show_book(); break;
            case 3: delete_book(); break;
            case 4: issue_book(); break;
            case 5: return_issue_book(); break;
            case 6: show_issued_book(); break;
            case 7: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    }
    return 0;
}
