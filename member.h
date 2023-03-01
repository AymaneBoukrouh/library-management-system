#include <stdbool.h>

#ifndef MEMBER
#define MEMBER

typedef struct {
	int id;
	char first_name[16];
	char last_name[16];
	bool student;
	bool status;
} member;

extern member members[1000];
extern int n_members;

int member_count_loans (int memeber_id, int type); // 1: all, 2: active, 3: inactive
void list_members (int student, int status_active, int active_loans); // 1: both, 2: yes, 3: no

void cli_list_members ();
void cli_view_member_details ();
void cli_add_member ();
void cli_modify_member_details ();
void cli_activate_deactivate_member (int type); // 1: activate, 2: deactivate

#endif