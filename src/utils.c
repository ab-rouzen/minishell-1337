/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:24:06 by arouzen           #+#    #+#             */
/*   Updated: 2022/11/30 18:53:50 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*allocates a new token_lst and returns it*/
t_list	*new_token_lst(enum token token, char *line, int n_char)
{
	t_token *new_tkn_lst;

	new_tkn_lst = malloca(sizeof(t_token));
	if (new_tkn_lst == NULL)
		return (NULL);
	new_tkn_lst->tkn = token;
	new_tkn_lst->n_char = n_char;
	new_tkn_lst->val = copy_token_val(line, n_char);
	return (ft_lstnew_falloc(new_tkn_lst, malloca));
}

/*assigns an index to each token based on the number of characters it has*/
void	index_token(t_list *tok_lst)
{
	int index;

	index = 0;
	while (tok_lst)
	{
		(*(t_token*)tok_lst->content).index = index;
		index += (*(t_token*)tok_lst->content).n_char;
		tok_lst = tok_lst->next;
	}
}

/*copies 'size' bytes from 'line' to allocated 'buffer' and returns it*/
char	*copy_token_val(char *line, int	size)
{
	int		i;
	char	*buff;

	i = 0;
	buff = malloca(size + 1);
	while (i < size)
	{
		buff[i] = line[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

void	join_token(t_list *start, t_list *end, enum token quote)
{
	int	i;
	t_list	*tmp;
	char	*val;
	char	*buff;

	i = 0;
	tmp = start->next;
	val = NULL;
	/*segfaults here?*/
	//assert(((t_token*)tmp->content)->tkn != TOK_SQUOTE);
	if (((t_token*)tmp->content)->tkn != quote)
	{
		val = ft_strdup(((t_token*)tmp->content)->val);
		tmp = tmp->next;
		while (tmp && ((t_token*)tmp->content)->tkn != quote)
		{
			buff = val;
			val = ft_strjoin(val, ((t_token*)tmp->content)->val);
			free(buff);
			tmp = tmp->next;
		}
	}
	//should free bellow??
	//free(((t_token*)start->content)->val);
	((t_token*)start->content)->val = val;
	//printf("val here is %s ^ %s\n", ((t_token*)start->content)->val, val);
	//delete_token(start->next, end);
}

void	delete_token(t_list	*start, t_list *end)
{
	t_list	*tmp;

	while (start != end)
	{
		tmp = start->next;
		free(start->content);
		free(start);
		start = tmp;
	}
	free(end->content);
	free(end);
}

void	expand_env_var(t_list **tok_l, char **environ)
{
	t_list	*tmp;

	if (*tok_l && ((t_token*)(*tok_l)->content)->tkn == TOK_DOLLAR)
	{
		if ((*tok_l)->next && ((t_token*)(*tok_l)->next->content)->tkn == TOK_WORD)
		{
			tmp = (*tok_l)->next->next;
			((t_token*)(*tok_l)->content)->val =  get_env_val(environ,  ((t_token*)(*tok_l)->next->content)->val);
			//free ((*tok_l)->next);
			if (((t_token*)(*tok_l)->content)->val == NULL)
			{
				//printf("was here?\n");
				(*tok_l) = tmp;
			}
			else
			{
				(*tok_l)->next = tmp;
				((t_token*)(*tok_l)->content)->tkn = TOK_WORD;
			}	
			//printf("val is:%s\n", ((t_token*)(*tok_l)->content)->val);
			//not the proper way to free?
			//assert(!tmp);
		}
		else
			*tok_l = (*tok_l)->next;
	}
}

char	*get_env_val(char *environ[], char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	while (environ[i])
	{
		tmp = ft_split(environ[i], '=');
		if (!ft_strcmp(tmp[0], var))
		{
			free(tmp[0]);
			return (tmp[1]);
		}
		free(tmp[0]);
		free(tmp[1]);
		i++;
	}
	return (NULL);
}

void	delete_element(t_list **tok_l, enum token token)
{
	while (*tok_l)
	{
		if (((t_token*)(*tok_l)->content)->tkn == token)
		{
			*tok_l = (*tok_l)->next;
			//should free here
		}
		else
			tok_l = &(*tok_l)->next;
	}
}

int	get_words_num(t_list *tok_l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tok_l && ((t_token*)tok_l->content)->tkn != TOK_PIPE)
	{
		if (((t_token*)tok_l->content)->tkn == TOK_WORD)
			i++;
		else
			j++;
		tok_l = tok_l->next;
	}
	return (i - j);
}

void	join_adjacent_quotes(t_list **tok_l)
{
	t_list	*head;
	char	*tmp;

	head = *tok_l;
	while(*tok_l)
	{
		//tok_l;
		if (((t_token*)(*tok_l)->content)->tkn == TOK_QUOTE)
		{
			if ((*tok_l)->next && ((t_token*)(*tok_l)->next->content)->tkn == TOK_QUOTE)
			{
				//some frees here
				tmp = ((t_token*)(*tok_l)->content)->val;
				((t_token*)(*tok_l)->content)->val =  ft_strjoin(((t_token*)(*tok_l)->content)->val, ((t_token*)(*tok_l)->next->content)->val);
				free(tmp);
				free(((t_token*)(*tok_l)->next->content)->val);
				(*tok_l)->next = (*tok_l)->next->next;
				continue ;
			}
		}
		tok_l = &(*tok_l)->next;
	}
	replace_element(head, TOK_QUOTE, TOK_WORD);
}

void	replace_element(t_list *tok_l, enum token token_1, enum token token_2)
{
	while (tok_l)
	{
		if (((t_token*)tok_l->content)->tkn == token_1)
			((t_token*)tok_l->content)->tkn = token_2;
		tok_l = tok_l->next;
	}
}

t_list	*ft_lstnew_falloc(void *content, void*(*alloc)(size_t))
{
	t_list	*new_list;

	new_list = alloc(sizeof(t_list));
	new_list->next = NULL;
	new_list->content = content;
	return (new_list);
}

char	*ft_strdup_alloca(const char *src, void*(alloc)(size_t))
{
	int		i;
	char	*n_str;
	char	*nsrc;

	i = 0;
	nsrc = (char *) src;
	if (src == NULL)
		return (NULL);
	n_str = alloc((ft_strlen(nsrc) + 1) * sizeof(char));
	if (n_str == NULL)
		return (NULL);
	while (nsrc[i])
	{
		n_str[i] = nsrc[i];
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}