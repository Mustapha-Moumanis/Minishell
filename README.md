![minishell part](https://github.com/Mustapha-Moumanis/minishell_md/assets/86886160/e634f444-b03b-43a5-958e-e1250c742512)
# Project Summary :
This project offers a step-by-step guide to creating your own bash shell, providing valuable insights and information based on our experience. Get ready to embark on the journey of building your very own simple shell.
## Installation :
you need to install brew from here https://github.com/kube/42homebrew 
and use this cmd `brew install readline`to use readline function
Makefile : 
```Makefile
FLAGS = -Wall -Wextra -Werror -lreadline 
-I $(HOME)/.brew/Cellar/readline/8.2.1/include
-L $(HOME)/.brew/Cellar/readline/8.2.1/leb
```
* The -I option is used to add additional include paths
* The -L option is used to add additional library paths
## Display a prompt :
```c
char *readline (char *prompt);
```
The function `readline` will read a line from the terminal and return it, using prompt as a prompt.  If prompt is NULL or the empty string, no prompt is issued.  The line returned is allocated with malloc(3); the caller must free it when finished.  The line returned has the final newline removed, so only the text of the line remains.
That how you'll get the user input.
```c
char *input;

input = readline("minishell : ");
```
## Lexer - Tokenization :
The **lexer**, also known as **tokenization**, is responsible for converting a sequence of characters into a sequence of lexical tokens. In our implementation, we traverse the input line character by character and tokenize it. Tokenizing involves assigning names to different elements such as words, pipes, and more. At this stage, the focus is not on determining if it's a valid command or identifying the specific command; rather, our goal is to discover and categorize the elements present in the input.
Let's explore how we can achieve this : <br>
=> we create to store our lexer. <br>
1 - The code you provided defines a structure named s_lexer, which is used to store information about the input line and keep track of the last position accessed when working with the lexer.<br>
```c
typedef struct s_lexer
{
	char	*input;
	int		len;
	int		position;
}			t_lexer;
```
**input**: which is used to store the input line. It points to the first character of the input.<br>
**len**: It holds the total number of characters in the input.<br>
**position**: This integer that indicates the current position in the input line. It stores the index of the last character accessed.<br>
2 - This is a list element:
```c
typedef struct s_elem
{
	char			*content;
	enum e_type		type;
	enum e_state	state;
	struct s_elem	*next;
}					t_elem;
```
**content**: a pointer to the string stored in a node. <br>
**type**: the content token. <br>
 * here we defined the tokens type that we’ll need.
 ```c
 enum e_type
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	DQUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	EXIT_STATUS,
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
	OR,
	AND
};
```
**state**: we choose to add this information, the content state, if it's inside/outside (double/single) quotes.
```c
enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL
};
```
> Example of how a line is tokenized :
```shell
echo "$USER" $$'$PATH' > file | cat  << limiter > file | cat < file >> out_file
```
![lexer_exemple](https://github.com/Mustapha-Moumanis/minishell/assets/86886160/f8ed4ef1-8668-4125-ab53-e6545e6f5c36)
## Syntax errors :
1. redirection followed by pipe <br>
	`< |`, `> |`, `>> |`, `<< |`, and this one `| |` pipe afte pipe <br>
	`syntax error near unexpected token '|'` <br>
2. redirection following another redirection <br>
	`echo < >>`, `echo > >>`, `echo >> >>`, `echo << >>` <br>
	`syntax error near unexpected token '>>'` <br>
	msg : depends on the 2nd redirection token <br>
3. redirection without any string afterwards <br>
	`echo <` , `echo >`, `echo >>` , `echo <<`, `echo |` <br>
	`syntax error near unexpected token 'newline'` <br>

## Parser 
Using the lexer, you can initialize this linked list by parsing the input and extracting relevant information to populate the list. The lexer breaks down the input into tokens, allowing you to identify different components of the command, such as input/output files and the full command itself.
> Command list

![parsing_part](https://github.com/Mustapha-Moumanis/minishell_md/assets/86886160/028f0659-a762-45ef-a26b-a4d597245824)

* Command struct

```c
typedef struct s_cmd
{
	int				in_file;
	int				out_file;
	char				**full_cmd;
	struct s_cmd	*next;
}					t_cmd;
```

**in_file**: Used to store the file descriptor when there is a redirection operation involving input, such as `REDIR_IN <`, or `HERE_DOC <<`. <br>
**out_file**: Used to store the file descriptor when there is a redirection operation involving output, such as `REDIR_OUT >`, or `DREDIR_OUT >>`. <br>
**full_cmd**: This is a 2D array to store the arguments. <br>

> Example :

![example](https://github.com/Mustapha-Moumanis/minishell_md/assets/86886160/7a2f303f-9ddd-4fbf-9b0c-2cbd1ba694a1)

## Execution :

![comming_soon](https://github.com/Mustapha-Moumanis/minishell_md/assets/86886160/05215d54-5226-498b-ab47-32bb2f137b30)

