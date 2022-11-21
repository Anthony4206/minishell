/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:17:12 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/21 06:59:55 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

t_token	*ft_lst_new_token(void);
t_token	*ft_token_last(t_token *lst);
void	ft_token_add_back(t_token **lst, t_token *new);

#endif
