#include "general.h"
#include "member.h"
#include "book.h"
#include "loan.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

bool parse_input (char (*p)[], char s[100]) {
	printf("%s", s);
	char string[100];
	fgets(string, sizeof(string), stdin);
	string[strlen(string)-1] = 0;
	if (!strcmp(string, "exit")) {
		save_data();
		return 0;
	}

	strcpy(*p, string);
	return 1;
}

void init_data () {
	if (!opendir("data")) {
		printf("\n");
		printf(GREEN "\nInitializing Database... ");
		mkdir("data", 0755);

		FILE *f;
		f = fopen("data/members", "w"); fclose(f);
		f = fopen("data/books", "w"); fclose(f);
		f = fopen("data/loans", "w"); fclose(f);

		f = fopen("data/admin_password.txt", "w");
		fputs("pass1234", f);
		fclose(f);

		printf("Done!\n");
		printf("Default Admin Password (can be changed later): pass1234\n");
		printf("Login as Admin to load test data, or to clear all data (this will NOT reset the admin password).\n" WHITE);
		printf("\n");
	}
}

void load_data () {
	FILE *f;

	f = fopen("data/members", "r");
	member m;
	while (fread(&m, sizeof(m), 1, f)) members[n_members++] = m;
	fclose(f);

	f = fopen("data/books", "r");
	book b;
	while (fread(&b, sizeof(b), 1, f)) books[n_books++] = b;
	fclose(f);

	f = fopen("data/loans", "r");
	loan l;
	while (fread(&l, sizeof(l), 1, f)) loans[n_loans++] = l;
	fclose(f);
}

void save_data () {
	FILE *f;

	f = fopen("data/members", "w");
	for (int i=0; i<n_members; i++) fwrite(&members[i], sizeof(members[i]), 1, f);
	fclose(f);

	f = fopen("data/books", "w");
	for (int i=0; i<n_books; i++) fwrite(&books[i], sizeof(books[i]), 1, f);
	fclose(f);

	f = fopen("data/loans", "w");
	for (int i=0; i<n_loans; i++) fwrite(&loans[i], sizeof(loans[i]), 1, f);
	fclose(f);
}

void load_test_data () {
	reset_data();

	members[0] = (member) {1, "Carl", "Craig", 1, 1};
	members[1] = (member) {2, "Charlie", "Casey", 1, 1};
	members[2] = (member) {3, "Max", "Carroll", 0, 1};
	members[3] = (member) {4, "Oscar", "Kelly", 1, 0};
	members[4] = (member) {5, "Nicole", "Clark", 0, 0};
	members[5] = (member) {6, "Sabrina", "Mayson", 0, 1};
	members[6] = (member) {7, "Ryan", "Spencer", 0, 0};
	members[7] = (member) {8, "Walter", "Gray", 1, 1};
	members[8] = (member) {9, "Spike", "Adams", 1, 1};
	members[9] = (member) {10, "George", "Wilson", 0, 0};
	n_members = 10;

	books[0] = (book) {1, 5, "Don't Close Your Eyes", "Lynessa Layne", "Fantasy"};
	books[1] = (book) {2, 2, "Complicated Moonlight", "Lynessa Layne", "Mystery"};
	books[2] = (book) {3, 7, "The Great Gatsby", "Scott Fitzgerald", "Mystery"};
	books[3] = (book) {4, 3, "Boulevard Dreams", "Ryan Janz", "Fantasy"};
	books[4] = (book) {5, 5, "The Killer Angels", "Michael Shaara", "Mystery"};
	books[5] = (book) {6, 1, "Dead By Morning", "Kayla Krantz", "Thriller"};
	books[6] = (book) {7, 9, "The Remains Of The Day", "Kazuo Ishiguro", "Mystery"};
	books[7] = (book) {8, 3, "Masada", "Ernest K. Gann", "Horror"};
	books[8] = (book) {9, 6, "The Midnight Watch", "David Dyer", "Thriller"};
	books[9] = (book) {10, 3, "The Purse", "Julie A. Burns", "Horror"};
	n_books = 10;

	loans[0] = (loan) {1, 1, 6, 1};
	loans[1] = (loan) {2, 4, 2, 1};
	loans[2] = (loan) {3, 7, 8, 1};
	loans[3] = (loan) {4, 2, 4, 1};
	loans[4] = (loan) {5, 8, 3, 0};
	loans[5] = (loan) {6, 1, 8, 0};
	loans[6] = (loan) {7, 8, 4, 0};
	loans[7] = (loan) {8, 4, 8, 1};
	loans[8] = (loan) {9, 8, 4, 1};
	loans[9] = (loan) {10, 9, 2, 1};
	loans[10] = (loan) {11, 1, 9, 0};
	loans[11] = (loan) {12, 4, 6, 0};
	loans[12] = (loan) {13, 7, 3, 1};
	loans[13] = (loan) {14, 3, 8, 1};
	loans[14] = (loan) {15, 7, 4, 1};
	loans[15] = (loan) {16, 3, 2, 1};
	loans[16] = (loan) {17, 8, 8, 0};
	loans[17] = (loan) {18, 3, 4, 1};
	loans[18] = (loan) {19, 8, 2, 0};
	loans[19] = (loan) {20, 2, 8, 0};
	n_loans = 20;

	save_data();
}

void reset_data () {
	memset(members, 0, sizeof(members));
	n_members = 0;

	memset(books, 0, sizeof(books));
	n_books = 0;

	memset(loans, 0, sizeof(loans));
	n_loans = 0;

	save_data();
}

void cli_load_test_data () {
	char proceed[4];
	parse_input(&proceed, "\nLoading test data will delete all current data, are you sure you want to proceed? (yes, no): ");
	if (!strcmp(proceed, "yes")) {
		load_test_data();
		printf(GREEN "Successfully loaded test data!\n" WHITE);
	}

	else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No data has been deleted/loaded.\n" WHITE);
	else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
}

void cli_reset_data () {
	char proceed[4];
	parse_input(&proceed, "\nYou're about to delete all data, are you sure you want to proceed? (yes, no): ");
	if (!strcmp(proceed, "yes")) {
		reset_data();
		printf(GREEN "All data has been deleted!\n" WHITE);
	}

	else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No data has been deleted.\n" WHITE);
	else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
}