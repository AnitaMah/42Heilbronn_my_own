#include <stdlib.h>
#include <stdio.h>

int get_count(char *s)
{
    int count = 0;
    while (*s)
    {
      while (*s == ' ' || *s == '\t' || *s == '\n')
			{
        s++;
      }
        if (*s)
			{
        count++;
      }
        while (*s && *s != ' ' && *s != '\t' && *s != '\n')
			{
        s++;
      }
    }
    return (count);
}

void free_all(char **arr)
{
    int i = 0;
    while (arr[i])
    {
      free(arr[i++]);
    }
    free(arr);
}

char *fill_words(char *s)
{
    int len = 0;
    int i;
    while (s[len] && s[len] != ' ' && s[len] != '\t' && s[len] != '\n')
    {
      len++;
    }
    char *word = malloc(len + 1);
    if (!word)
    {
		  return NULL;
    }
    i = 0;
    while (i < len)
    {
      word[i++] = *s++;
    }
    word[i] = '\0';
    return word;
}

char **ft_split(char *str)
{
    int i = 0;
    char **res = malloc(sizeof(char *) * (get_count(str) + 1));
	  printf("%d\n", get_count(str));
    if (!res)
		{
      return NULL;
    }
    while (*str)
    {
      while (*str == ' ' || *str == '\t' || *str == '\n')
			{
        str++;
      }
      if (!*str)
      {
			  break;
      }
      res[i] = fill_words(str);
      if (!res[i])
      {
			  return(free_all(res), NULL);
		  }
      while (*str && *str != ' ' && *str != '\t' && *str != '\n')
      {
        str++;
      }
      i++;
    }
    res[i] = NULL;
    return res;
}

int main(int argc, char **argv)
{
	char **str;
	int iter = 0;
	if (argc == 2)
	{
		str = ft_split(argv[1]);
	}
	while(str[iter])
	{
		printf("%s\n", str[iter]);
		iter++;
	}
}
