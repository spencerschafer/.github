/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 15:13:23 by hstander          #+#    #+#             */
/*   Updated: 2017/09/14 12:49:13 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
** saves the name of the program to the header struct if it passes all the
** tests.
*/

void	ft_name(t_args *ag, int i)
{
	int		j;
	char	*temp;

	/*
	** Note: if-statement
	** Checks that the second occurence of '"' is greater than the first
	** occurence, if there is a second occurence (otherwise j == i), and returns
	** its index which is stored into j.
	*/ 
	if ((j = ft_chrn_i(ag->trim_str, '"')) > i)
	{
		/*
		** Note: if-statement
		** Makes sure the string is null-terminated. If it isn't, it calls the 
		** my_error() function which prints the message corresponding to the
		** value passed.
		*/

		if (ag->trim_str[j + 1] != '\0')
			my_error(8, ag); // see 'error.c'
		
		/*
		** Note: temp
		** Stores the substring starting from the index (i + 1) until (j - 1).
		** The reason for the +1/-1 is to avoid including the quotation marks in
		** the string. Also, (j - i) determines how many times to iterate from
		** the value i.
		*/

		temp = ft_strsub(ag->trim_str, (i + 1), (j - i - 1));
		
		/*
		** Note: if-statement
		** PROG_NAME_LENGTH is the maximum length a name can be. Therefore, checks
		** to see the name adheres to this rule. Prints error message if true.
		*/

		if (ft_strlen(temp) > PROG_NAME_LENGTH)
		{
			ft_printf_fd(2, "Name to big:\n%s\n", ag->trim_str);
			free(temp);
			exit(6);
		}

		/*
		** Copies temp string to ag->header->prog_name)
		*/

		ft_strcpy(ag->header->prog_name, temp);
		ag->name_f = 1;
		free(temp);
	}
	else
		my_error(5, ag); // see 'error.c'

}

/*
** saves the comment of the program to the header struct if it passes all the
** tests.
*/

void	ft_comment(t_args *ag, int i)
{
	int		j;
	char	*temp;

	/*
	** Note: if-statement
	** Checks that the second occurence of '"' is greater than the first
	** occurence, if there is a second occurence (otherwise j == i), and returns
	** its index which is stored into j.
	*/

	if ((j = ft_chrn_i(ag->trim_str, '"')) > i)
	{
		/*
		** Note: if-statement
		** Makes sure the string is null-terminated. If it isn't, it calls the 
		** my_error() function which prints the message corresponding to the
		** value passed.
		*/

		if (ag->trim_str[j + 1] != '\0')
			my_error(8, ag); // see 'error.c'
			
		/*
		** Note: temp
		** Stores the substring starting from the index (i + 1) until (j - 1).
		** The reason for the +1/-1 is to avoid including the quotation marks in
		** the string. Also, (j - i) determines how many times to iterate from
		** the value i.
		*/

		temp = ft_strsub(ag->trim_str, (i + 1), (j - i - 1));
		
		/*
		** Note: if-statement
		** COMMENT_LENGTH is the maximum length a name can be. Therefore, checks
		** to see the name adheres to this rule. Prints error message if true.
		*/

		if (ft_strlen(temp) > COMMENT_LENGTH)
		{
			ft_printf_fd(2, "comment to big:\n%s\n", ag->trim_str);
			free(temp);
			exit(6);
		}

		/*
		** Copies temp string to ag->header->comment)
		*/

		ft_strcpy(ag->header->comment, temp);
		ag->comment_f = 1;
		free(temp);
	}
	else
		my_error(5, ag); // see 'error.c'
}

/*
** prints a error message depending on the input integer.
*/

int		ft_exit_nmcm(t_args *ag, int i)
{
	if (i == -1)
		ft_printf_fd(2, "Invalid name:\n%s\n", ag->trim_str);
	if (i == -2)
		ft_printf_fd(2, "Invalid comment:\n%s\n", ag->trim_str);
	if (i == -3)
		ft_printf_fd(2, "Invalid command %s\n", ag->trim_str);
	return (i);
}

/*
** If a line starts with a '.' it checks if the line is the program 'name' or
** the program comments, and calls the relevant function to save the name or
** comment into the header struct.
*/

void	ft_nm_com(t_args *ag)
{
	int		i;

	/*
	** Note: if-statements.
	** Compares the first 5 characters, counting from 0, to see if they match
	** the string '.name'. If they do, call function ft_name (see above),
	** otherwise it calls the exit function which calls the ft_exit_nmcm (see
	** above). Subsequent if-statements check for '.comment' and calls the
	** ft_comment function. If neither '.name' or '.comment' are met, call
	** function ft_exit_nmcm().
	**
	** Note: ft_chr_i() (Note: ft_chrn_i finds last occurence)
	** Finds the first occurence of the input character, otherwise returns -1.
	**
	** Note: ft_exit_nmcm(); 
	** Prints an error message  depending on the exi code. i.e -1, -2, or -3.
	*/

	if (ft_strncmp(ag->trim_str, ".name", 5) == 0)
	{
		/*
		** Note: ft_name();
		** Does various test to ensure string is valid. If valid, copies string
		** inside quotations to ag->header->prog_name otherwise prints error
		** message.
		*/

		if ((i = ft_chr_i(ag->trim_str, '"')) > -1)
			ft_name(ag, i);
		else
			exit(ft_exit_nmcm(ag, -1));
	}
	else if (ft_strncmp(ag->trim_str, ".comment", 8) == 0)
	{
		/*
		** Note: ft_comment();
		** Does various test to ensure string is valid. If valid, copies string
		** inside quotations to ag->header->comment otherwise prints error 
		** message.
		*/

		if ((i = ft_chr_i(ag->trim_str, '"')) > -1)
			ft_comment(ag, i);
		else
			exit(ft_exit_nmcm(ag, -2));
	}
	else
		exit(ft_exit_nmcm(ag, -3));
}

void	check_nm_com(t_args *ag)
{
	if (ag->name_f == 0)
	{
		ft_printf_fd(2, "No name present\nAborting ...\n");
		exit(-1);
	}
	if (ag->comment_f == 0)
	{
		ft_printf_fd(2, "No comment present\nAborting ...\n");
		exit(-1);
	}
}