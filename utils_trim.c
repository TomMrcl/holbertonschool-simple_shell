#include "main.h"

/**
 * trim_whitespace - Removes leading and trailing whitespace
 * @str: String to trim
 *
 * Return: Pointer to trimmed string
 */
char *trim_whitespace(char *str)
{
	char *start, *end, *dst;

	if (str == NULL)
		return (NULL);

	start = str;
	while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')
		start++;

	if (*start == '\0')
	{
		str[0] = '\0';
		return (str);
	}

	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' ||
		*end == '\n' || *end == '\r'))
		end--;

	*(end + 1) = '\0';

	if (start != str)
	{
		dst = str;
		while (*start)
			*dst++ = *start++;
		*dst = '\0';
	}

	return (str);
}
