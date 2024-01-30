#include <common.h>
#include <token.h>
#include <lexer.h>
#include <color.h>
static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */

void init_regex()
{
  int i;
  char error_msg[128];
  int ret;
  for (i = 0; i < NR_REGEX; i++)
  {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0)
    {
      regerror(ret, &re[i], error_msg, 128);
      printf("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
      exit(-1);
    }
  }
}

void make_lines(char *e, Line *lines, int *nr_line)
{
  char *token = strtok(e, "\n");
  int line_num = 0;
  while (token != NULL)
  {
    strncpy(lines[line_num].str, token, sizeof(lines[line_num].str));
    lines[line_num].str[sizeof(lines[line_num].str)] = '\0';
    lines[line_num].line_number = line_num + 1;
    size_t len = strlen(lines[line_num].str);
    if (len < sizeof(lines[line_num].str) - 1)
    {
      lines[line_num].str[len] = '\n';
      lines[line_num].str[len + 1] = '\0';
    }
    line_num++;
    token = strtok(NULL, "\n");
  }
  *nr_line = line_num;
}

bool make_token(Line *lines, int *nr_line, Token *tokens, int *nr_token)
{
  int position = 0;
  int i, j;
  regmatch_t pmatch;
  *nr_token = 0;

  for (i = 0; i < *nr_line; i++)
  {
    position = 0;
    while (lines[i].str[position] != '\0')
    {
      char *e = lines[i].str;
      /* Try all rules one by one. */
      for (j = 0; j < NR_REGEX; j++)
      {
        if (regexec(&re[j], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
        {
          char *substr_start = e + position;
          int substr_len = pmatch.rm_eo;
          if (rules[j].token_type != TK_NOTYPE)
            printf("match rules[%d] = \"%s\" at position %d with len %d: %.*s\n",
                   j, rules[j].regex, position, substr_len, substr_len, substr_start);
          position += substr_len;
          /* TODO: Now a new token is recognized with rules[i]. Add codes
           * to record the token in the array `tokens'. For certain types
           * of tokens, some extra actions should be performed.
           */
          tokens[*nr_token].line_number = lines[i].line_number;
          tokens[*nr_token].type = rules[j].token_type;
          strncpy(tokens[*nr_token].str, substr_start, substr_len);
          tokens[*nr_token].str[substr_len] = '\0';
          (*nr_token)++;
          break;
        }
      }
      if (j == NR_REGEX)
      {
        set_color(PR_RED);
        printf("no match at line %d position %d\n%s%*.s^\n", i, position, e, position, "");
        return false;
      }
    }
  }
  return true;
}
