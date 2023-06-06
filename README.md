![minishell part (1)](https://github.com/Mustapha-Moumanis/minishell/assets/86886160/080821c5-377a-4787-bceb-625efbc4eea7)
## Project Summary :
This project offers a step-by-step guide to creating your own bash shell, providing valuable insights and information based on our experience. Get ready to embark on the journey of building your very own simple shell.
## Installation :
you need to install brew from here https://github.com/kube/42homebrew 
and use this cmd `brew install readline`to use readline function
Makefile : 
`FLAGS = -Wall -Wextra -Werror -lreadline 
-I $(HOME)/.brew/Cellar/readline/8.2.1/include
-L $(HOME)/.brew/Cellar/readline/8.2.1/leb`
* The -I option is used to add additional include paths
* The -L option is used to add additional library paths
## Display a prompt :
`char *readline (char *prompt);`
The function `readline` will read a line from the terminal and return it, using prompt as a prompt.  If prompt is NULL or the empty string, no prompt is issued.  The line returned is allocated with malloc(3); the caller must free it when finished.  The line returned has the final newline removed, so only the text of the line remains.
That how you'll get the user input.
`char *input;

input = readline("minishell : ");`
## Lexer - Tokenization :
The **lexer**, also known as **tokenization**, is responsible for converting a sequence of characters into a sequence of lexical tokens. In our implementation, we traverse the input line character by character and tokenize it. Tokenizing involves assigning names to different elements such as words, pipes, and more. At this stage, the focus is not on determining if it's a valid command or identifying the specific command; rather, our goal is to discover and categorize the elements present in the input.
Let's explore how we can achieve this :
- we create to store our lexer.
1 - The code you provided defines a structure named s_lexer, which is used to store information about the input line and keep track of the last position accessed when working with the lexer.
```
typedef struct s_lexer
{
	char	*input;
	int		len;
	int		position;
}			t_lexer;
```
**input**: which is used to store the input line. It points to the first character of the input.
**len**: It holds the total number of characters in the input.
**position**: This integer that indicates the current position in the input line. It stores the index of the last character accessed.
2 - This is a list element:
`typedef struct s_elem
{
	char			*content;
	enum e_type		type;
	enum e_state	state;
	struct s_elem	*next;
}					t_elem;
`
**content**: a pointer to the string stored in a node.
**type**: the content token.
 * here we defined the tokens type that we’ll need.
 `enum e_type
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
};`
**state**: we choose to add this information, the content state, if it's inside/outside (double/single) quotes.


