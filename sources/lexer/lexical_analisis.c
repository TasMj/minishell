/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analisis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:36:17 by tas               #+#    #+#             */
/*   Updated: 2023/03/03 10:40:15 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* étapes */

//1 chaîne de caractères de la ligne de commande lue et stockée
//2 elimination des caractères blancs (espace, tab, retour à la ligne)
//3 détéction des guillemets
//4 division en tokens
//5 retour des tokens

/* read and stock input */
char    *get_input(void)
{
    char* input;

    input = readline("$");
    if (input == NULL) {
        printf("Erreur de lecture de la input.\n");
        exit(EXIT_FAILURE);
    }
	add_history(input);
    return input;
}

/* return 1 si c'est un espace, un retour de ligne */
int is_a_separator(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

/* ajoute à la liste le mot déjà découpé */
void    add_list(t_list **list_token, char *stockage)
{
    (*list_token) = ft_lstnew((*list_token), stockage);
    ft_lstadd_back(list_token, (*list_token));
}

/* découpe le mot en fonction de si il s'agit d'un mot simple ou entre quote (single ou double)*/
char    *detect_token(char *stockage)
{
    char *resize;
    
    if (check_pair_double_quote(stockage) == 0) //pas de quote
        resize = ft_strdup_size(stockage, ft_strlen(stockage));
    else if (check_pair_double_quote(stockage) == 1 || check_pair_single_quote(stockage) == 1) //cas boucle > (plus tard gerer ce cas)
        return (NULL); //null
    else if (check_pair_single_quote(stockage) == 2 && stockage[0] == 39) //double quote
        resize = word_quote(stockage, 34);
    else if (check_pair_double_quote(stockage) == 2 && stockage[0] == 34) //double quote
        resize = word_quote(stockage, 39);
    return (resize);
}

/* parcours toute la chaîne et crée les tokens*/
void    create_token(t_list **list_token, char *input)
{
    int i;
    int start;
    int end;
    int stop;
    int flag_quote;
    char *stockage;
    char *word_ready;

    i = 0;
    start = 0;
    end = 0;
    flag_quote = 0;
    stop = 0;
    stockage = NULL;
    word_ready = NULL;
    while(i < ft_strlen(input) && stop == 0)
    {
        if (is_a_separator(input[i]) == 1)
            i++;
        else
        {
            start = i;
            while (is_a_separator(input[i]) == 0 || flag_quote == 1)
            {
                if (input[i] == 34)
                    flag_quote++;
                if (i == ft_strlen(input) - 1)
                {
                    stop = 1;
                    break;
                }
                i++;
            }
            if (stop == 1)
                end = i + 1;
            else
                end = i;
            stockage = ft_strdup_size(input + start, (end - start));
            word_ready = detect_token(stockage);
            free(stockage);
            add_list(list_token, word_ready);
            (*list_token) = (*list_token)->next;
        }
        flag_quote = 0;
    }
}

// ls -la | grep "is eating" | wc -l
// a gerer: espace avant '     "blabla"'