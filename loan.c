#include "loan.h"
#include "general.h"
#include "member.h"
#include "book.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

loan loans[1000];
int n_loans = 0;

void list_loans (int type) {
	printf("——————————————————————————————————————————————————————————————————————————————————\n");
	printf("| ID  | MID | First Name      | BID | Title                          | Returned  |\n");
	printf("——————————————————————————————————————————————————————————————————————————————————\n");

	loan loans_[1000];
	int counter = 0;

	if (type==1) {
		memcpy(loans_, loans, sizeof(loans));
		counter = n_loans;
	}

	else {
		for (int i=0; i<n_loans; i++) {
			if (type==2 && loans[i].returned) loans_[counter++] = loans[i];
			if (type==3 && !loans[i].returned) loans_[counter++] = loans[i];
		}
	}

	char ci[4];
	loan *l;
	for (int i=0; i<counter; i++) {
		l = &loans_[i];
		
		printf("| " MAGENTA "%d" WHITE, l->id); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", l->id);
		for (int j=0; j<4-strlen(ci); j++) printf(" ");

		printf("| " YELLOW "%d" WHITE, l->member_id); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", l->member_id);
		for (int j=0; j<4-strlen(ci); j++) printf(" ");

		printf("| %s", members[l->member_id-1].first_name);
		for (int j=0; j<16-strlen(members[l->member_id-1].first_name); j++) printf(" ");

		printf("| " YELLOW "%d" WHITE, l->book_id); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", l->book_id);
		for (int j=0; j<4-strlen(ci); j++) printf(" ");

		printf("| %s", books[l->book_id-1].title);
		for (int j=0; j<32-strlen(books[l->book_id-1].title); j++) printf(" ");

		if (l->returned) {
			printf("| " GREEN "Yes" WHITE);
			for (int j=0; j<9-strlen("Yes"); j++) printf(" ");
		}

		else {
			printf("| " RED "No" WHITE);
			for (int j=0; j<9-strlen("No"); j++) printf(" ");
		}

		printf("|\n");
	}

	printf("——————————————————————————————————————————————————————————————————————————————————\n");
	printf("\n");
}

void cli_list_loans () {
	char selected[16];
	parse_input(&selected, "Select (all, active, inactive): ");
	if (!strcmp(selected, "all")) list_loans(1);
	else if (!strcmp(selected, "active")) list_loans(2);
	else if (!strcmp(selected, "inactive")) list_loans(3);
	else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, selected);
}

void cli_view_loan_details () {
	int loan_id;
	printf("Loan ID: ");
	scanf("%d", &loan_id);
	getchar();
	if (1<=loan_id && loan_id<=n_loans) {
		loan l = loans[loan_id-1];
		printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", l.id);
		printf(CYAN "    Member ID" WHITE ": " YELLOW "%d\n", l.member_id);
		printf(CYAN "    Full Name:" WHITE ": %s %s\n", members[l.member_id-1].first_name, members[l.member_id-1].last_name);
		printf(CYAN "    Book ID" WHITE ": " YELLOW "%d\n", l.book_id);
		printf(CYAN "    Title" WHITE ": %s\n", books[l.book_id-1].title);
		printf(CYAN "    Returned" WHITE ": ");
		if (l.returned) printf(GREEN "Yes\n" WHITE);
		else printf(RED "No" WHITE);
		printf("\n");
	}

	else printf(RED "Invalid choice! Try again later.\n" WHITE);
}

void cli_add_loan () {
	loan l; l.id = n_loans+1;
	l.returned = false;
	int member_id, book_id;
	printf("Member ID: ");
	scanf("%d", &member_id);
	if (1<=member_id && member_id<=n_members) l.member_id = member_id;
	else {
		printf(RED "Invalid choice! Try again later.\n" WHITE);
		return;
	}

	printf("Book ID: ");
	scanf("%d", &book_id);
	getchar();
	if (1<=book_id && book_id<=n_books) l.book_id = book_id;
	else{
		printf(RED "Invalid choice! Try again later.\n" WHITE);
		return;
	}

	if (!book_count_available(book_id)) {
		printf(RED "This book isn't available right now! Try again later." WHITE);
		return;
	}

	printf("\n");
	printf("You're about to add this loan: \n");
	printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", l.id);
	printf(CYAN "    Member ID" WHITE ": " YELLOW "%d\n", member_id);
	printf(CYAN "    Full Name" WHITE ": %s %s\n", members[member_id-1].first_name, members[member_id-1].last_name);
	printf(CYAN "    Book ID" WHITE ": " YELLOW "%d\n", book_id);
	printf(CYAN "    Book Title" WHITE ": %s\n", books[book_id-1].title);
	printf("\n");

	char proceed[4];
	parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
	if (!strcmp(proceed, "yes")) {
		loans[n_loans++] = l;
		printf(GREEN "Loan successfully added!\n" WHITE);
	}

	else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No loan has been added.\n" WHITE);
	else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
}

void cli_modify_loan_details () {
	int loan_id;
	printf("Loan ID: ");
	scanf("%d", &loan_id);
	getchar();
	if (1<=loan_id && loan_id<=n_loans) {
		int member_id, book_id;
		printf("New Member ID: ");
		scanf("%d", &member_id);
		if (!(1<=member_id && member_id<=n_members)) {
			printf(RED "Invalid choice! Try again later.\n" WHITE);
			return;
		}

		printf("New Book ID: ");
		scanf("%d", &book_id);
		if (!(1<=book_id && book_id<=n_books)) {
			printf(RED "Invalid choice! Try again later.\n" WHITE);
			return;
		}

		if (!book_count_available(book_id)) {
			printf(RED "This book isn't available right now! Try again later." WHITE);
			return;
		}

		loan *l = &loans[loan_id-1];
		printf("\n");
		printf("You're about to modify this loan:\n");
		printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", l->id);

		printf(RED "    Old Member ID" WHITE ": " YELLOW "%d\n", l->member_id);
		printf(CYAN "    New Member ID" WHITE ": " YELLOW "%d\n", member_id);
		printf(RED "    Old Full Name:" WHITE ": %s %s\n", members[l->member_id-1].first_name, members[l->member_id-1].last_name);
		printf(RED "    New Full Name:" WHITE ": %s %s\n", members[member_id-1].first_name, members[member_id-1].last_name);
		printf(RED "    Old Book ID" WHITE ": " YELLOW "%d\n", l->book_id);
		printf(CYAN "    Old Book ID" WHITE ": " YELLOW "%d\n", book_id);
		printf(RED "    Old Title" WHITE ": %s\n", books[l->book_id-1].title);
		printf(CYAN "    New Title" WHITE ": %s\n", books[book_id-1].title);
		printf(CYAN "    Returned" WHITE ": ");
		if (l->returned) printf(GREEN "Yes\n" WHITE);
		else printf(RED "No" WHITE);
		printf("\n");

		char proceed[4];
		parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
		if (!strcmp(proceed, "yes")) {
			l->member_id = member_id;
			l->book_id = book_id;
			printf(GREEN "Loan successfully modified!\n" WHITE);
		}

		else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No book has been modified.\n" WHITE);
		else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
	}

	else printf(RED "Invalid choice! Try again later.\n" WHITE);
}

void cli_confirm_loan () {
	int loan_id;
	printf("Loan ID: ");
	scanf("%d", &loan_id);
	getchar();

	if (1<=loan_id && loan_id<=n_loans) {
		if (loans[loan_id-1].returned) {
			printf(GREEN "Loan is already confirmed!\n" WHITE);
			return;
		}

		loan l = loans[loan_id-1];
		printf("You're about to confirm this loan: \n");
		printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", l.id);
		printf(CYAN "    Member ID" WHITE ": " YELLOW "%d\n", l.member_id);
		printf(CYAN "    Full Name" WHITE ": %s %s\n", members[l.member_id-1].first_name, members[l.member_id-1].last_name);
		printf(CYAN "    Book ID" WHITE ": " YELLOW "%d\n", l.book_id);
		printf(CYAN "    Book Title" WHITE ": %s\n", books[l.book_id-1].title);
		printf("\n");

		char proceed[4];
		parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
		if (!strcmp(proceed, "yes")) {
			loans[loan_id-1].returned = true;
			printf(GREEN "Loan successfully confirmed!\n" WHITE);
		}

		else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No loan has been added.\n" WHITE);
		else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
	}

	else {
		printf(RED "Invalid choice! Try again later.\n" WHITE);
		return;
	}
}