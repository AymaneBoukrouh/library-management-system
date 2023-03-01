#include "member.h"
#include "general.h"
#include "book.h"
#include "loan.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

member members[1000];
int n_members = 0;

int member_count_loans (int member_id, int type) {
	int r = 0;
	for (int i=0; i<n_loans; i++) {
		if (loans[i].member_id==member_id) {
			switch (type) {
				case 1: r++; break;
				case 2: if (!loans[i].returned) r++; break;
				case 3: if (loans[i].returned) r++; break;

			}
		}
	}

	return r;
}

void list_members (int student, int status_active, int active_loans) {
	printf("—————————————————————————————————————————————————————————————————————————————————\n");
	printf(CYAN "| ID  | First Name      | Last Name       | Student | Status    | Total  | Active |\n" WHITE);
	printf("—————————————————————————————————————————————————————————————————————————————————\n");

	member members_[1000];	
	int counter = 0;
	for (int i=0; i<n_members; i++) {
		switch (student) {
			case 1: members_[counter++] = members[i]; break;
			case 2: if (members[i].student) members_[counter++] = members[i]; break;
			case 3: if (!members[i].student) members_[counter++] = members[i]; break;
		}
	}

	member members__[1000];
	int counter_ = 0;
	for (int i=0; i<counter; i++) {
		switch (status_active) {
			case 1: members__[counter_++] = members_[i]; break;
			case 2: if (members_[i].status) members__[counter_++] = members_[i]; break;
			case 3: if (!members_[i].status) members__[counter_++] = members_[i]; break;
		}
	}

	memset(members_, 0, sizeof(members_));
	counter = 0;
	for (int i=0; i<counter_; i++) {
		switch (active_loans) {
			case 1: members_[counter++] = members__[i]; break;
			case 2: if (member_count_loans(members__[i].id, 2)) members_[counter++] = members__[i]; break;
			case 3: if (!member_count_loans(members__[i].id, 2)) members_[counter++] = members__[i]; break;
		}
	}

	char ci[4];
	member *m;
	for (int i=0; i<counter; i++) {
		m = &members_[i];
		
		printf("| " MAGENTA "%d" WHITE, m->id); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", m->id);
		for (int j=0; j<4-strlen(ci); j++) printf(" ");

		printf("| %s", m->first_name);
		for (int j=0; j<16-strlen(m->first_name); j++) printf(" ");

		printf("| %s", m->last_name);
		for (int j=0; j<16-strlen(m->last_name); j++) printf(" ");

		if (m->student) {
			printf("| " GREEN "Yes" WHITE);
			for (int j=0; j<8-strlen("Yes"); j++) printf(" ");
		}

		else {
			printf("| " RED "No" WHITE);
			for (int j=0; j<8-strlen("No"); j++) printf(" ");
		}

		if (m->status) {
			printf("| " GREEN "Active" WHITE);
			for (int j=0; j<10-strlen("Active"); j++) printf(" ");
		}

		else {
			printf("| " RED "Inactive" WHITE);
			for (int j=0; j<10-strlen("Inactive"); j++) printf(" ");
		}

		printf("| " YELLOW "%d" WHITE, member_count_loans(m->id, 1)); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", member_count_loans(m->id, 1));
		for (int j=0; j<7-strlen(ci); j++) printf(" ");

		printf("| " YELLOW "%d" WHITE, member_count_loans(m->id, 2)); memset(ci, 0, sizeof(ci)); sprintf(ci, "%d", member_count_loans(m->id, 2));
		for (int j=0; j<7-strlen(ci); j++) printf(" ");

		printf("|\n");
	}

	printf("—————————————————————————————————————————————————————————————————————————————————\n");
	printf("\n");
}

void cli_list_members () {
	char selected[16];
	bool filter;
	parse_input(&selected, "Select (all, filter): ");
	if (!strcmp(selected, "all")) filter = false;
	else if (!strcmp(selected, "filter")) filter = true;
	else {
		printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, selected);
		return;
	}

	if (filter) {
		char student[16], status[16], active_loans[16];
		int is_student, status_active, has_active_loans;
		parse_input(&student, "EMSI Student (all, yes, no): ");
		if (!strcmp(student, "all")) is_student = 1;
		else if (!strcmp(student, "yes")) is_student = 2;
		else if (!strcmp(student, "no")) is_student = 3;
		else {
			printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, student);
			return;
		}

		parse_input(&status, "Status (all, active, inactive): ");
		if (!strcmp(status, "all")) status_active = 1;
		else if (!strcmp(status, "active")) status_active = 2;
		else if (!strcmp(status, "inactive")) status_active = 3;
		else {
			printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, status);
			return;
		}

		parse_input(&active_loans, "Active Loans (all, yes, no): ");
		if (!strcmp(active_loans, "all")) has_active_loans = 1;
		else if (!strcmp(active_loans, "yes")) has_active_loans = 2;
		else if (!strcmp(active_loans, "no")) has_active_loans = 3;
		else {
			printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, active_loans);
			return;
		}

		list_members(is_student, status_active, has_active_loans);
	}

	else list_members(1, 1, 1);
}

void cli_view_member_details () {
	int member_id;
	printf("Member ID: ");
	scanf("%d", &member_id);
	getchar();
	if (1<=member_id && member_id<=n_members) {
		member m = members[member_id-1];
		printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", m.id);
		printf(CYAN "    First Name" WHITE ": %s\n", m.first_name);
		printf(CYAN "    Last Name" WHITE ": %s\n", m.last_name);
		printf(CYAN "    EMSI Student" WHITE ": ");
		if (m.student) printf(GREEN "Yes\n" WHITE);
		else printf(RED "No\n" WHITE);
		printf(CYAN "    Status" WHITE ": ");
		if (m.status) printf(GREEN "Active\n" WHITE);
		else printf(RED "Inactive\n" WHITE);
		printf(CYAN "    Total Loans" WHITE ": " YELLOW "%d\n" WHITE, member_count_loans(member_id, 1));
		printf(CYAN "    Active Loans" WHITE ": " YELLOW "%d\n" WHITE, member_count_loans(member_id, 2));
	}

	else printf(RED "Invalid choice! Try again later.\n" WHITE);
}

void cli_add_member () {
	member m; m.id = n_members+1;
	m.status = 1;
	char student[4];

	parse_input(&m.first_name, "First Name: ");
	parse_input(&m.last_name, "Last Name: ");

	parse_input(&student, "EMSI Student (yes, no): ");
	if (!strcmp(student, "yes")) m.student = 1;
	else if (!strcmp(student, "no")) m.student = 0;
	else {
		printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, student);
		return;
	}

	printf("\n");
	printf("You're about to add this member to the library: \n");
	printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", m.id);
	printf(CYAN "    First Name" WHITE ": %s\n", m.first_name);
	printf(CYAN "    Last Name" WHITE ": %s\n", m.last_name);
	printf(CYAN "    EMSI Student" WHITE ": ");
	if (m.student) printf(GREEN "Yes\n");
	else printf(RED "No\n");
	printf(CYAN "    Status" WHITE ": " GREEN "Active\n" WHITE);
	char proceed[4];
	parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
	if (!strcmp(proceed, "yes")) {
		members[n_members++] = m;
		printf(GREEN "Member successfully added!\n" WHITE);
	}

	else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No member has been added.\n" WHITE);
	else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
}

void cli_modify_member_details () {
	int member_id;
	printf("Member ID: ");
	scanf("%d", &member_id);
	getchar();
	if (1<=member_id && member_id<=n_members) {
		char first_name[32], last_name[24], student[4];
		bool is_student;
		parse_input(&first_name, "New First Name: ");
		parse_input(&last_name, "New Last Name: ");
		
		parse_input(&student, "New EMSI Student (yes, no): ");
		if (!strcmp(student, "yes")) is_student = true;
		else if (!strcmp(student, "no")) is_student = false;
		else {
			printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, student);
			return;
		}

		member *m = &members[member_id-1];
		printf("\n");
		printf("You're about to modify this member:\n");
		printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", m->id);
		printf(RED "    Old First Name" WHITE ": %s\n", m->first_name);
		printf(CYAN "    New First Name" WHITE ": %s\n", first_name);
		printf(RED "    Old Last Name" WHITE ": %s\n", m->last_name);
		printf(CYAN "    New Last Name" WHITE ": %s\n", last_name);
		printf(RED "    Old EMSI Student" WHITE ": ");
		if (m->student) printf(GREEN "Yes\n" WHITE);
		else printf(RED "No\n" WHITE);
		printf(CYAN "    New EMSI Student" WHITE ": ");
		if (is_student) printf(GREEN "Yes\n" WHITE);
		else printf(RED "No\n" WHITE);
		printf(CYAN "    Status: " WHITE ": ");
		if (m->status) printf(GREEN "Active\n" WHITE);
		else printf(RED "Inactive\n" WHITE);
		printf(CYAN "    Total Loans" WHITE ": " YELLOW "%d\n" WHITE, member_count_loans(m->id, 1));
		printf(CYAN "    Active Loans" WHITE ": " YELLOW "%d\n" WHITE, member_count_loans(m->id, 2));

		char proceed[4];
		parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
		if (!strcmp(proceed, "yes")) {
			strcpy(m->first_name, first_name);
			strcpy(m->last_name, last_name);
			m->student = is_student;
			printf(GREEN "Member successfully modified!\n" WHITE);
		}

		else if (!strcmp(proceed, "no")) printf(RED "Operation cancelled! No member has been modified.\n" WHITE);
		else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
	}

	else printf(RED "Invalid choice! Try again later.\n" WHITE);
}

void cli_activate_deactivate_member (int type) {
	int member_id;
	printf("Member ID: ");
	scanf("%d", &member_id);
	getchar();
	if (1<=member_id && member_id<=n_members) {
		if (type&&members[member_id-1].status || !type&&!members[member_id-1].status) {
			if (type) printf(RED "Member with ID %d is already Active! Operation terminated.\n", member_id);
			else printf(RED "Member with ID %s is already Inactive! Operation terminated.\n", member_id);
			return;
		}

		printf("You're about to ");
		if (type) printf("activate");
		else printf("deactivate");
		printf(" this member:\n");
		member m = members[member_id-1];
		printf(CYAN "    ID" WHITE ": " MAGENTA "%d\n", m.id);
		printf(CYAN "    First Name" WHITE ": %s\n", m.first_name);
		printf(CYAN "    Last Name" WHITE ": %s\n", m.last_name);
		printf(CYAN "    EMSI Student" WHITE ": ");
		if (m.student) printf(GREEN "Yes\n" WHITE);
		else printf(RED "No\n" WHITE);
		printf(CYAN "    Old Status" WHITE ": ");
		if (m.status) printf(GREEN "Active\n" WHITE);
		else printf(RED "Inactive\n" WHITE);
		printf(CYAN "    New Status" WHITE ": ");
		if (!m.status) printf(GREEN "Active\n" WHITE);
		else printf(RED "Inactive\n" WHITE);

		char proceed[4];
		parse_input(&proceed, "\nAre you sure you want to proceed? (yes, no): ");
		if (!strcmp(proceed, "yes")) {
			members[m.id-1].status = !members[m.id-1].status;
			printf(GREEN "Member successfully ");
			if (type) printf("activated!\n" WHITE);
			else printf("deactivated!\n" WHITE);
		}

		else if (!strcmp(proceed, "no")) {
			printf(RED "Operation cancelled! No member has been ");
			if (type) printf("activated.\n" WHITE);
			else printf("deactivated.\n" WHITE);
		}

		else printf(RED "Option \"%s\" not found! Try again later.\n" WHITE, proceed);
	}

	else printf(RED "Invalid choice! Try again later.\n" WHITE);
}