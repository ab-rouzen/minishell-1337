/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imittous <imittous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 10:28:42 by arouzen           #+#    #+#             */
/*   Updated: 2022/12/28 18:17:04 by imittous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define  TYPES_H

typedef int		t_bool;

typedef struct s_env_list
{
	void				*variable;
	void				*value;
	t_bool				exported;
	struct s_env_list	*next;
}					t_env_list;

enum e_token
{
	TOK_WORD,
	TOK_WHITESPACE,
	TOK_PIPE,
	TOK_REDI_I,
	TOK_REDI_O,
	TOK_REDI_O_APP,
	TOK_HEREDOC,
	TOK_QUOTE,
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_DOLLAR,
	TOK_NULL
};

typedef struct s_shell
{
	char		*pwd;
	int			exit_status;
	t_env_list	*env_lst;
	int			**fd_heredoc;
	int			hdoc_cmd_no;
	int			close_hdc;
	t_bool		exec;
}				t_shell;

typedef struct s_token_lst
{
	enum e_token	tkn;
	int				n_char;
	int				index;
	char			*val;
}					t_token;

typedef struct s_redir_list
{
	enum e_token	tok;
	char			*file;
}					t_redir_list;

typedef struct s_cmd_lst
{
	char		*cmd_name;
	char		**cmd_args;
	t_list		*redir_lst;
	int			fd_in;
	int			fd_out;
}				t_cmd_lst;

#endif