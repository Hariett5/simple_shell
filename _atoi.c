#include "shell.h"

/**
 * isShellInteractive - checks if the shell is running in interactive mode
 * @info: pointer to info_t struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int isShellInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if it is a delimiter, 0 otherwise
 */
int isDelimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * isAlphabetic - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if it is alphabetic, 0 otherwise
 */
int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * stringToInteger - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int stringToInteger(char *s)
{
	int i, sign = 1, flag = 0, result = 0, output;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

