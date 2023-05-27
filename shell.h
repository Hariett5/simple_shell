#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Read/write buffer sizes */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Command chaining types */
#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Convert number flags */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flag to indicate usage of system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

typedef struct list_string
{
	int num;
	char *str;
	struct list_string *next;
} list_t;

typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_num;
	int linecount_flag;
	char *filename;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **command_buffer;
	int command_buffer_type;
	int read_fd;
	int hist_count;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin_command
{
	char *type;
	int (*function)(info_t *);
} builtin_table;


/* Function prototypes */
int shell(info_t *, char **);
int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* Error handling */
void print_error_message(char *);
int print_character_to_fd(char, int);
int print_string_to_fd(char *, int);

/* String manipulation */
int get_string_length(char *);
int compare_strings(char *, char *);
char *starts_with_string(const char *, const char *);
char *concatenate_strings(char *, char *);

/* Memory management */
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int print_character(char);

/* Conversion functions */
char *copy_n_characters(char *, char *, int);
char *concatenate_n_characters(char *, char *, int);
char *find_character(char *, char);

/* Tokenization */
char **split_string(char *, char *);
char **split_string_alternative(char *, char);

/* Realloc and free */
char *set_memory(char *, char, unsigned int);
void free_strings(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* Integer conversion */
int is_interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int convert_to_integer(char *);

/* Error handling */
int error_atoi(char *);
void print_error(info_t *, char *);
int print_integer(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Builtin commands */
int exit_shell(info_t *);
int change_directory(info_t *);
int display_help(info_t *);

/* Builtin commands */
int display_history(info_t *);
int handle_alias(info_t *);

/* Input reading */
ssize_t get_input_line(info_t *);
int get_line(info_t *, char **, size_t *);
void handle_sigint(int);

#endif
