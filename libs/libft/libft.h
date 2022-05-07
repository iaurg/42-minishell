/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 07:38:35 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/06 21:44:06 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 1

/**
 * @brief A list of nodes with content.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

char		*get_next_line(int fd);
void		free_and_reset(void *var);
ssize_t		read_line(char **holder, char **buffer, char **final_line, int fd);
char		*split_line(char **holder);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *b, int c, size_t len);
int			ft_memcmp(const void *b1, const void *b2, size_t len);
char		*ft_strnstr(const char	*big, const char *little, size_t len);
int			ft_atoi(const char *nptr);
void		*ft_calloc(size_t number, size_t size);
char		*ft_strdup(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_getenv(const char *env);
char		*ft_strtok(char *str, char *delim);
/**
 * @brief Allocates (with malloc(3)) and returns a new element.
 * The variable ’content’ is initialized with the value of the
 * parameter ’content’. The variable ’next’ is initialized to NULL.
 *
 * @param content The content to create the new element with
 * @return t_list* The new element
 */
t_list		*ft_lstnew(void *content);

/**
 * @brief Adds the element ’new’ at the beginning of the list.
 *
 * @param lst The address of a pointer to the first link of a list
 * @param new The address of a pointer to the element to be added to the list
 */
void		ft_lstunshift(t_list **lst, t_list *new);

/**
 * @brief Counts the number of elements in a list.
 *
 * @param lst The beginning of a list
 * @return int Returns the length of a list
 */
int			ft_lstsize(t_list *lst);

/**
 * @brief Returns the last element of the list.
 *
 * @param lst The beginning of the list
 * @return t_list* Returns the last element of the list.
 * Returns NULL if `lst` is empty
 * or is already in the last element.
 */
t_list		*ft_lstlast(t_list *lst);

/**
 * @brief Adds the `new` element at the end of the list.
 *
 * @param lst The address of a pointer to the first link of a list
 * @param new The address of a pointer to the element to be
 * added to the list.
 */
void		ft_lstpush(t_list **lst, t_list *new);

/**
 * @brief Takes as a parameter an element and frees the
 * memory of the element’s content using the function
 * ’del’ given as a parameter and free the element.
 * The memory of ’next’ must not be freed.
 *
 * @param lst The element to free
 * @param del The address of the function used to delete the content.
 */
void		ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief Deletes and frees the given element and every
 * successor of that element, using the function ’del’ and free(3).
 * Finally, the pointer to the list must be set to NULL.
 *
 * @param lst The adress of a pointer to an element
 * @param del The adress of the function used to delete
 * the content of the element.
 */
void		ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * @brief Iterates the list ’lst’ and applies the function
 * ’f’ to the content of each element.
 *
 * @param lst The adress of a pointer to an element
 * @param f The adress of the function used to iterate on the list
 */
void		ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function ’f’
 * to the content of each element. Creates a new list resulting
 * of the successive applications of the function ’f’.
 * The ’del’ function is used to delete the content of an element if needed.
 *
 * @param lst	The adress of a pointer to an element
 * @param f		The adress of the function used to iterate on the list
 * @param del	The adress of the function used to delete the
 * content of an element if needed
 * @return t_list* Returns the new list or NULL if the allocation fails.
 */
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
