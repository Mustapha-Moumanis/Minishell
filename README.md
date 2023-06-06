![minishell part (1)](https://github.com/Mustapha-Moumanis/minishell/assets/86886160/080821c5-377a-4787-bceb-625efbc4eea7)
## Project Summary
This project offers a step-by-step guide to creating your own bash shell, providing valuable insights and information based on our experience. Get ready to embark on the journey of building your very own simple shell.
### Installation
you need to install brew from here https://github.com/kube/42homebrew 
and use this cmd `brew install readline`to use readline function
Makefile : 
```FLAGS = -Wall -Wextra -Werror -lreadline 
-I $(HOME)/.brew/Cellar/readline/8.2.1/include
-L $(HOME)/.brew/Cellar/readline/8.2.1/leb```
=> The -I option is used to add additional include paths
=> The -L option is used to add additional library paths
