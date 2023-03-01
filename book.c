#include "book.h"
#include "general.h"
#include "member.h"
#include "loan.h"
#include <stdio.h>
#include <string.h>

book books[1000];
int n_books = 0;

int book_count_available (int book_id) {
	int books_loaned = 0;
	for (int i=0; i<n_loans; i++) if (loans[i].book_id==book_id && !loans[i].returned) books_loaned++;
	return books[book_id-1].copies-books_loaned;
}

void list_books (int type) {
	printf("———————————————————————————————————————————————————————————————————————————————————————————————\n");
	printf(CYAN "| ID  | Title                   | Author                  | Type        | Copies  | Available |\n" WHITE);
	printf("———————————————————————————————————————————————————————————————————————————————————————————————\n");

	book books_[1000];
	int counter = 0;

	if (type==1) {
		memcpy(books_, books, sizeof(books));
		counter = n_books;
	}

	else {
		for (int i=0; i<n_books; i++) {
			if (type==2 && book_count_available(books[i].id)) books_[counter++] = books[i];
			if (type==3 && !book_count_available(books[i].id)) books_[counter++] = books[i];
		}
	}

	char ci[4];
	book *b;
	for (int i=0; i<counter; i++) {
		b = &books_[i];
		char title_temp[20];
		
		printf("| " MAGENTA "%d" WHITE, b->id); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", b->id);
		for (int j=0; j<4-strlen(ci); j++) printf(" ");

		if (strlen(b->title)<=24) {
			printf("| %s", b->title);
			for (int j=0; j<24-strlen(b->title); j++) printf(" ");
		}

		else {
			for (int i=0; i<20; i++) title_temp[i] = b->title[i];
			title_temp[20] = '.';
			title_temp[21] = '.';
			title_temp[22] = '.';
			title_temp[23] = ' ';
			printf("| %s", title_temp);
		}

		printf("| %s", b->author);
		for (int j=0; j<24-strlen(b->author); j++) printf(" ");

		printf("| %s", b->type);
		for (int j=0; j<12-strlen(b->type); j++) printf(" ");

		printf("| " YELLOW "%d" WHITE, b->copies); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", b->copies);
		for (int j=0; j<8-strlen(ci); j++) printf(" ");

		printf("| " YELLOW "%d" WHITE, book_count_available(b->id)); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", book_count_available(b->id));
		for (int j=0; j<10-strlen(ci); j++) printf(" ");

		printf("|\n");
	}

	printf("———————————————————————————————————————————————————————————————————————————————————————————————\n");
	printf("\n");
}


void cli_list_books () {
	char selected[16];
	parse_input(&selected, "Select (all, available, unavailable): ");
	if (!strcmp(selected, "all")) list_books(1);
	else if (!strcmp(selected, "available")) list_books(2);
	else if (!strcmp(selected, "unavailable")) list_books(3);
	else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, selected);
}

void cli_view_book_details () {
	int book_id;
	printf("Book ID: ");
	scanf("%d", &book_id);
	getchar();
	if (1<=book_id && book_id<=n_books) {
		book b = books[book_id-1];
		printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", b.id);
		printf(CYAN "    Title" WHITE ": %s\n", b.title);
		printf(CYAN "    Author" WHITE ": %s\n", b.author);
		printf(CYAN "    Type" WHITE ": %s\n", b.type);
		printf(CYAN "    Copies" WHITE ": " YELLOW "%d\n", b.copies);
		printf(CYAN "    Available" WHITE ": " YELLOW "%d\n" WHITE, book_count_available(book_id));
	}

	else printf(RED "Invalid choice! Try again later.\n" WHITE);
}

void cli_add_book () {
	book b; b.id = n_books+1;

	parse_input(&b.title, "Title: ");
	parse_input(&b.author, "Author: ");
	parse_input(&b.type, "Type: ");
	printf("Copies: ");
	scanf("%d", &b.copies);
	getchar();

	printf("\n");
	printf("You're about to add this book to the library: \n");
	printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", b.id);
	printf(CYAN "    Title" WHITE ": %s\n", b.title);
	printf(CYAN "    Author" WHITE ": %s\n", b.author);
	printf(CYAN "    Type" WHITE ": %s\n", b.type);
	printf(CYAN "    Copies" WHITE ": " YELLOW "%d\n" WHITE, b.copies);
	char proceed[4];
	parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
	if (!strcmp(proceed, "yes")) {
		books[n_books++] = b;
		printf(GREEN "Book successfully added!\n" WHITE);
	}

	else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No book has been added.\n" WHITE);
	else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
}

void cli_modify_book_details () {
	int book_id;
	printf("Book ID: ");
	scanf("%d", &book_id);
	getchar();
	if (1<=book_id && book_id<=n_books) {
		char title[32], author[24], type[16];
		parse_input(&title, "New Title: ");
		parse_input(&author, "New Author: ");
		parse_input(&type, "New Type: ");

		book *b = &books[book_id-1];
		printf("\n");
		printf("You're about to modify this book:\n");
		printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", b->id);
		printf(RED "    Old Title" WHITE ": %s\n", b->title);
		printf(CYAN "    New Title" WHITE ": %s\n", title);
		printf(RED "    Old Author" WHITE ": %s\n", b->author);
		printf(CYAN "    New Author" WHITE ": %s\n", author);
		printf(RED "    Old Type" WHITE ": %s\n", b->type);
		printf(CYAN "    New Type" WHITE ": %s\n", type);
		printf(CYAN "    Copies" WHITE ": " YELLOW "%d\n" WHITE, b->copies);

		char proceed[4];
		parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
		if (!strcmp(proceed, "yes")) {
			strcpy(b->title, title);
			strcpy(b->author, author);
			strcpy(b->type, type);
			printf(GREEN "Book successfully modified!\n" WHITE);
		}

		else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No book has been modified.\n" WHITE);
		else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
	}

	else printf(RED "Invalid choice! Try again later.\n" WHITE);
}

void cli_add_remove_book_copies (int type) {
	int book_id;
	printf("Book ID: ");
	scanf("%d", &book_id);
	getchar();
	if (1<=book_id && book_id<=n_books) {
		int copies;
		printf("Number of copies to ");
		if (type) printf("add");
		else printf("remove");
		printf(": ");
		scanf("%d", &copies);
		getchar();
		if (copies>0) {
			book b = books[book_id-1];
			if (type) printf("You're about to add copies of this book:\n");
			else {
				if (book_count_available(b.id)-copies>=0) printf("You're about to remove copies of this book:\n");
				else {
					printf(RED "Number of copies must be superior to the number of available copies! Try again later.\n" WHITE);
					return;
				}
			} 

			printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", b.id);
			printf(CYAN "    Title" WHITE ": %s\n", b.title);
			printf(CYAN "    Author" WHITE ": %s\n", b.author);
			printf(CYAN "    Type" WHITE ": %s\n", b.type);
			printf(RED "    Old Copies" WHITE ": " YELLOW "%d\n", b.copies);
			int new_copies;
			if (type) new_copies = b.copies+copies;
			else new_copies = b.copies-copies;
			printf(CYAN "    New Copies" WHITE ": " YELLOW "%d\n" WHITE, new_copies);

			char proceed[4];
			parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
			if (!strcmp(proceed, "yes")) {
				books[book_id-1].copies = new_copies;
				printf(GREEN "Successfully ");
				if (type) printf("added %d to", copies);
				else printf("removed %d from", copies);
				printf(" book with ID %d!\n" WHITE, b.id);
			}

			else if (!strcmp(proceed, "no")) {
				printf(RED "Operation cancelled! No book has been ");
				if (type) printf("added");
				else printf("removed");
				printf(".\n" WHITE);
			}
			else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
		}

		else printf(RED "Number must be strictlly superior than 0! Try again later.\n" WHITE);
	}

	else printf(RED "Invalid choice! Try again later.\n" WHITE);
}