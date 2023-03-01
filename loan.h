#include <stdbool.h>

#ifndef LOAN
#define LOAN

typedef struct {
	int id;
	int member_id;
	int book_id;
	bool returned;
} loan;

extern loan loans[1000];
extern int n_loans;

void cli_list_loans ();
void cli_view_loan_details ();
void cli_add_loan ();
void cli_modify_loan_details ();
void cli_confirm_loan ();

#endif