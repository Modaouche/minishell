/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:22:43 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf/includes/ft_printf.h"
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <pwd.h>
# include <signal.h>
# define BUFFER 1

typedef struct		s_list
{
	char			*var_elem;
	struct s_list	*next;
}					t_list;

int					g_error_no;

/*
** Parsing:
*/

char				***ft_parse_stdin(t_list **env, int i, int j);
char				*ft_read_stdin(void);
char				*ft_search_cmd(char *cmd, t_list *env);
int					ft_parse_path_cmd(char *cmd, int bt);
void				ft_remove_bad_dollars(char *readed_cmd, t_list **env);

/*
** execution:
*/

void				ft_exec_cmd(char **cmd, t_list **env);
void				ft_exec_ve(char **command, t_list *env);
void				ft_error_message(char *cmd, char *arg, int btn);
void				exit_msg(char *cmd, char *arg, int btn);
int					is_in_exec(char c);

/*
** handling:
*/

t_list				*ft_tab_to_list(char **env);
t_list				*ft_list_new(char *data);
void				ft_list_add(t_list **list, char *data);
t_list				*ft_list_dup(t_list **list);
int					ft_list_search_replace_c(t_list **list, char **var, int c);
void				ft_list_remove_if_c(t_list **begin_list, char *var, int c);
void				ft_print_env(t_list *env);
char				**ft_list_to_tabstr(t_list *list);
t_list				*ft_list_find(t_list *begin_list, char *data_ref);
void				ft_add_shlvl(t_list **new_envp);
void				ft_add_starter_var(t_list **new_env);
void				ft_freetab_str(char ***tabstr);
void				free_cmd(char ****cmd);
void				ft_free_list(t_list **to_remove);
char				**ft_tab_strdup(char **tab);
void				ft_printab(char **tabstr);
int					ft_arglen(char **arg);
int					tab_strslen(const char **arg, const char *s);
int					ft_exec_shell(char **cmd, t_list **env);
int					ft_strscmp(const char *s1, const char *s2, char c);
char				*get_prompt(const char *current_prompt);
void				signal_handle(int bt);

/*
** builtins :
*/

int					ft_bt_env(char **cmd, t_list **env);
int					ft_bt_setenv(char **cmd, t_list **env);
int					ft_bt_unsetenv(char **cmd, t_list **env);
int					ft_bt_echo(char **cmd);
int					ft_bt_exit(char **cmd, t_list **env);
int					ft_bt_pwd_print(int bt);
char				*ft_bt_pwd(int bt);
int					ft_bt_cd(char **cmd, t_list **env);
void				ft_replace_var(char *strpwd, t_list **env);
void				ft_remove_slash(char *strpwd, int bt);
void				ft_add_slash(char **src, char *to_add);
void				ft_full_path(t_list **env);
void				ft_change_cwd(char *path, int opt, t_list **env);
int					ft_check_valid_path(char *path, char *new_path,\
					t_list *pwd_var, int i);
void				ft_symb_link_path(char *path, t_list **env, int i);

#endif
