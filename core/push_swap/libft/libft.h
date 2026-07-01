/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:16:36 by username          #+#    #+#             */
/*   Updated: 2026/04/30 15:52:31 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/* ========================================================= */
/*                      PART 1 - CHAR                       */
/* ========================================================= */

/* Returns non-zero if c is an alphabetic letter (a-z or A-Z), 0 otherwise. */
int		ft_isalpha(int c);

/* Returns non-zero if c is a decimal digit (0-9), 0 otherwise. */
int		ft_isdigit(int c);

/* Returns non-zero if c is alphanumeric (letter or digit), 0 otherwise. */
int		ft_isalnum(int c);

/* Returns non-zero if c is a valid ASCII character (0-127), 0 otherwise. */
int		ft_isascii(int c);

/* Returns non-zero if c is a printable character (32-126), 0 otherwise. */
int		ft_isprint(int c);

/* Returns the uppercase equivalent of c if it is a lowercase letter,
** otherwise returns c unchanged. */
int		ft_toupper(int c);

/* Returns the lowercase equivalent of c if it is an uppercase letter,
** otherwise returns c unchanged. */
int		ft_tolower(int c);

/* ========================================================= */
/*                      PART 2 - STRING                     */
/* ========================================================= */

/* Returns the number of characters in the string s, not including
** the terminating NUL byte. */
size_t	ft_strlen(const char *s);

/* Returns a pointer to the first occurrence of character c in string s,
** or NULL if c is not found. The NUL terminator is considered part of s. */
char	*ft_strchr(const char *s, int c);

/* Returns a pointer to the last occurrence of character c in string s,
** or NULL if c is not found. The NUL terminator is considered part of s. */
char	*ft_strrchr(const char *s, int c);

/* Compares up to n characters of s1 and s2.
** Returns 0 if equal, a positive value if s1 > s2, negative if s1 < s2. */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* Copies up to size - 1 characters from src to dst, always NUL-terminating.
** Returns the total length of src (not the number of bytes written). */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/* Appends src to dst, reading at most size - strlen(dst) - 1 characters.
** Returns the total length of the string it tried to create. */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* Allocates and returns a duplicate of the string s1.
** Returns NULL if allocation fails. */
char	*ft_strdup(const char *s1);

/* Locates the first occurrence of the null-terminated string little
** in the string big, searching at most len characters.
** Returns big if little is empty, NULL if not found, else pointer to match. */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/* ========================================================= */
/*                      PART 3 - MEMORY                     */
/* ========================================================= */

/* Fills the first len bytes of memory area b with the byte value c.
** Returns a pointer to b. */
void	*ft_memset(void *b, int c, size_t len);

/* Sets the first n bytes of memory area s to zero. */
void	ft_bzero(void *s, size_t n);

/* Copies n bytes from src to dest. Memory areas must not overlap.
** Returns a pointer to dest. Undefined behavior if either pointer is NULL
** (mirrors standard memcpy behavior). */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/* Copies n bytes from src to dest, handling overlapping memory areas safely.
** Returns a pointer to dest. */
void	*ft_memmove(void *dest, const void *src, size_t n);

/* Scans the first n bytes of memory area s for the byte value c.
** Returns a pointer to the matching byte, or NULL if not found. */
void	*ft_memchr(const void *s, int c, size_t n);

/* Compares the first n bytes of memory areas s1 and s2.
** Returns 0 if equal, positive if s1 > s2, negative if s1 < s2. */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/* Allocates memory for count elements of size bytes each, zero-initialized.
** Returns a pointer to the allocated memory, or NULL on failure. */
void	*ft_calloc(size_t count, size_t size);

/* ========================================================= */
/*                      PART 4 - CONVERT                    */
/* ========================================================= */

/* Converts the initial portion of the string str to an int.
** Skips leading whitespace. Handles optional leading '+' or '-'.
** Undefined behavior on overflow (mirrors standard atoi). */
int		ft_atoi(const char *str);

/* Allocates and returns a string representation of the integer n.
** Returns NULL if allocation fails. */
char	*ft_itoa(int n);

/* ========================================================= */
/*                      PART 5 - OUTPUT                     */
/* ========================================================= */

/* Writes the character c to file descriptor fd. */
void	ft_putchar_fd(char c, int fd);

/* Writes the string s to file descriptor fd. */
void	ft_putstr_fd(char *s, int fd);

/* Writes the string s followed by a newline to file descriptor fd. */
void	ft_putendl_fd(char *s, int fd);

/* Writes the integer n as a decimal string to file descriptor fd. */
void	ft_putnbr_fd(int n, int fd);

/* ========================================================= */
/*              PART 2 EXTRA - STRING ALLOCATION            */
/* ========================================================= */

/* Allocates and returns a substring of s starting at index start
** with maximum length len. Returns NULL if allocation fails. */
char	*ft_substr(const char *s, size_t start, size_t len);

/* Allocates and returns a new string that is the concatenation of s1 and s2.
** Returns NULL if allocation fails. */
char	*ft_strjoin(char const *s1, char const *s2);

/* Allocates and returns a copy of s with all leading and trailing characters
** present in set removed. Returns NULL if allocation fails. */
char	*ft_strtrim(char const *s1, char const *set);

/* Allocates and returns an array of strings obtained by splitting s
** using delimiter c. The array is terminated by a NULL pointer.
** Returns NULL if allocation fails. */
char	**ft_split(char const *s, char c);

/* Applies function f to each character of string s (with its index),
** returning a new string with the results. Returns NULL on failure. */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* Applies function f to each character of string s in-place,
** passing the character's index and a pointer to the character. */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/* ========================================================= */
/*                      PART 6 - LIST                 */
/* ========================================================= */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* Allocates and returns a new list node with content set to content.
** The next pointer is initialized to NULL. Returns NULL on failure. */
t_list	*ft_lstnew(void *content);

/* Adds node new at the beginning of the list pointed to by lst. */
void	ft_lstadd_front(t_list **lst, t_list *new);

/* Returns the number of nodes in the list lst. */
int		ft_lstsize(t_list *lst);

/* Returns a pointer to the last node in the list lst. */
t_list	*ft_lstlast(t_list *lst);

/* Adds node new at the end of the list pointed to by lst. */
void	ft_lstadd_back(t_list **lst, t_list *new);

/* Frees a single node lst using del to free its content.
** Does NOT free adjacent nodes. */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/* Deletes and frees all nodes in the list, setting *lst to NULL.
** Uses del to free each node's content. */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/* Applies function f to the content of each node in list lst. */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/* Applies f to each node's content and builds a new list from the results.
** Uses del to free content if an allocation fails mid-way.
** Returns the new list, or NULL on failure. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
