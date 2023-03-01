#include "general.h"
#include "member.h"
#include "book.h"
#include "loan.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
	printf(WHITE);
	init_data();
	load_data();
	printf("Type \"help\" to see available commands.\n");

	char input[100];
	int login_type = 0; // 1: admin, 2: librarian
	while (parse_input(&input, "\n-> ")) {
		if (!login_type) {
			if (!strcmp(input, "help")) {
				printf("help                            show this help\n");
				printf("clear                           clear screen\n");
				printf("admin                           login as admin\n");
				printf("librarian                       login as librarian\n");
				printf("exit                            exit program\n");
			}

			else if (!strcmp(input, "clear")) system("clear");

			else if (!strcmp(input, "admin")) {
				FILE *f = fopen("data/admin_password.txt", "r");
				char c = fgetc(f), admin_password[16], input_password[16];
				int i = 0, attempts = 3;
				while (c!=EOF) {
					admin_password[i++] = c;
					c = fgetc(f);
				}

				fclose(f);

				printf("%s", admin_password);
				printf("Password: "); scanf("%s", &input_password);
				while (strcmp(input_password, admin_password) && attempts) {
					printf(RED "Wrong password! Try again (attempts left: %d): " WHITE, attempts--);
					scanf("%s", &input_password);
				}

				getchar();

				if (!strcmp(input_password, admin_password)) {
					printf(GREEN "\nWelcome Admin! Type \"help\" to see available commands.\n" WHITE);
					login_type = 1;
				}

				else {
					printf(RED "You have made 3 failed attempts to login as Admin, exiting!\n" WHITE);
					exit(0);
				}
			}

			else if (!strcmp(input, "librarian")) {
				printf(GREEN "Welcome Librarian! Type \"help\" to see available commands.\n" WHITE);
				login_type = 2;
			}

			else {
				printf(RED"Command \"%s\" not found! Type \"help\" to see available commands.\n" WHITE, input);
			}
		}

		else if (login_type==1) {
			if (!strcmp(input, "help")) {
				printf("GENERAL\n");
				printf("    help\n");
				printf("    clear\n");
				printf("    change password\n");
				printf("    load test data\n");
				printf("    reset data\n");
				printf("    logout\n");
				printf("    exit\n");
				printf("\n");
				printf("BOOKS\n");
				printf("    list books\n");
				printf("    view book details\n");
				printf("    add book\n");
				printf("    modify book details\n");
				printf("    add book copies\n");
				printf("    remove book copies\n");
				printf("\n");
				printf("MEMBERS\n");
				printf("    list members\n");
				printf("    view member details\n");
				printf("\n");
				printf("LOANS\n");
				printf("    list loans\n");
				printf("    view loan details\n");
			}

			else if (!strcmp(input, "clear")) system("clear");
			else if (!strcmp(input, "change password")) {
				char password1[16], password2[16];
				printf("New Password: ");
				scanf("%s", &password1);
				printf("Confirm Password: ");
				scanf("%s", &password2);

				if (!strcmp(password1, password2)) {
					FILE *f = fopen("data/admin_password.txt", "w");
					fputs(password1, f);
					fclose(f);

					printf(GREEN "Password successfully changed!\n" WHITE);
				}

				else printf(RED "You passwords do not match! Try again later.\n" WHITE);
				getchar();
			}

			else if (!strcmp(input, "load test data")) cli_load_test_data();
			else if (!strcmp(input, "reset data")) cli_reset_data();

			else if (!strcmp(input, "logout")) {
				printf(GREEN "Bye Admin!\n" WHITE);
				printf("Type \"help\" to see available commands.\n");
				login_type = 0;
			}

			else if (!strcmp(input, "list books")) cli_list_books();
			else if (!strcmp(input, "view book details")) cli_view_book_details();
			else if (!strcmp(input, "add book")) cli_add_book();
			else if (!strcmp(input, "modify book details")) cli_modify_book_details();
			else if (!strcmp(input, "add book copies")) cli_add_remove_book_copies(1);
			else if (!strcmp(input, "remove book copies")) cli_add_remove_book_copies(0);
			else if (!strcmp(input, "list members")) cli_list_members();
			else if (!strcmp(input, "view member details")) cli_view_member_details();
			else if (!strcmp(input, "list loans")) cli_list_loans();
			else if (!strcmp(input, "view loan details")) cli_view_loan_details();
			else printf(RED "Command \"%s\" not found! Type \"help\" to see available commands.\n" WHITE, input);
		}

		else {
			if (!strcmp(input, "help")) {
				printf("GENERAL\n");
				printf("    help\n");
				printf("    clear\n");
				printf("    logout\n");
				printf("    exit\n");
				printf("\n");
				printf("MEMBERS\n");
				printf("    list members\n");
				printf("    view member details\n");
				printf("    add member\n");
				printf("    modify member details\n");
				printf("    activate member\n");
				printf("    deactivate member\n");
				printf("\n");
				printf("LOANS\n");
				printf("    list loans\n");
				printf("    view loan details\n");
				printf("    add loan\n");
				printf("    modify loan details\n");
				printf("    confirm loan\n");
				printf("\n");
				printf("BOOKS\n");
				printf("    list books\n");
				printf("    view book details\n");
			}

			else if (!strcmp(input, "clear")) system("clear");
			else if (!strcmp(input, "logout")) {
				printf(GREEN "Bye Librarian!\n" WHITE);
				printf("Type \"help\" to see available commands.\n");
				login_type = 0;
			}

			else if (!strcmp(input, "list members")) cli_list_members();
			else if (!strcmp(input, "view member details")) cli_view_member_details();
			else if (!strcmp(input, "add member")) cli_add_member();
			else if (!strcmp(input, "modify member details")) cli_modify_member_details();
			else if (!strcmp(input, "activate member")) cli_activate_deactivate_member(1);
			else if (!strcmp(input, "deactivate member")) cli_activate_deactivate_member(0);
			else if (!strcmp(input, "list loans")) cli_list_loans();
			else if (!strcmp(input, "view loan details")) cli_view_loan_details();
			else if (!strcmp(input, "add loan")) cli_add_loan();
			else if (!strcmp(input, "modify loan details")) cli_modify_loan_details();
			else if (!strcmp(input, "confirm loan")) cli_confirm_loan();
			else if (!strcmp(input, "list books")) cli_list_books();
			else if (!strcmp(input, "view book details")) cli_view_book_details();

			else {
				printf(RED "Command \"%s\" not found! Type \"help\" to see available commands.\n" WHITE, input);
			}
		}

		save_data ();
	}

	return 0;
}
