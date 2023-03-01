#ifndef BOOK
#define BOOK

typedef struct {
	int id;
	int copies;
	char title[100];
	char author[24];
	char type[16];
} book;

extern book books[1000];
extern int n_books;

int book_count_available (int book_id);
void list_books (int type); // 1: all, 2: available, 3: unavailable

void cli_list_books ();
void cli_view_book_details ();
void cli_add_book ();
void cli_modify_book_details ();
void cli_add_remove_book_copies (int type); // 0: remove, 1: add

#endif