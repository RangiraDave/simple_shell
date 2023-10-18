#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

/*
 * This comment describes the elements typically included in the shell
 * such as environment variables, proram name, global varibles,
 * and history count.
 */

extern char **environ;
extern char *name;
extern int hist;

/**
 * struct list_s - This structure type introduces a linked list
 * that represents dicrectories.
 *
 * @node: A directory path
 * @next: A pointer to another struct list_s.
 */

typedef struct list_s
{
	char *node;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A newly introduced structure type that defines
 * built-in commands.
 *
 * @b_node: The name of builtin command.
 * @f: A function pointer for the built-in command.
 */

typedef struct builtin_s
{
	char *b_node;
	int (*f)(char **argv, char **front);
} builtin_list;

/**
 * struct alias_s - This structure defines aliases within the shell.
 *
 * @a_node: The name of the alias.
 * @a_value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */

typedef struct alias_s
{
	char *a_node;
	char *a_value;
	struct alias_s *next;
} alias_list;

/*
 * This comment suggests the presence of a linked list
 * to store global alliases
 */
extern alias_list *aliases;

/* Functions for Main runner */
ssize_t _getline(char **lineptr, size_t *n, FILE *channel);
void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz);
char **_strtok(char *line, char *delim);
char *get_path(char *command);
list_t *path_directory(char *path);
int cmd_executor(char **args, char **front);
void free_list(list_t *head);
char *_atoi(int num);

/* Functions for Handling args */
void handle_input(char **line, ssize_t read);
void find_op(char *line, ssize_t *new_len);
int handle_args(int *executed_ret);
char *get_args(char *line, int *executed_ret);
int invoke(char **args, char **front, int *executed_ret);
int check_args(char **args);
void variable_replacement(char **args, int *executed_ret);
int execute_args(char **args, char **front, int *executed_ret);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* Functions for String helper */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Functions for Builtins */
int (*get_builtins(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_alias(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/* Functions For Environment */
char **copy_env(void);
void free_env(void);
char **_getenv(const char *var);

/* Functions For Errors*/
int create_error(char **args, int er);
char *env_error(char **args);
char *alias_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Functions For Linked_lists */
alias_list *add_alias_end(alias_list **head, char *name, char *value);
void free_alias_list(alias_list *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void helper_all(void);
void helper_alias(void);
void helper_cd(void);
void helper_exit(void);
void helper_help(void);
void helper_env(void);
void helper_setenv(void);
void helper_unsetenv(void);
void helper_history(void);

int file_commands(char *file_path, int *executed_ret);

/*Additionals*/
void sig_handler(int sig);

#endif
