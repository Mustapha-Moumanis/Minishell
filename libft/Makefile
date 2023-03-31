# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 16:37:16 by mmoumani          #+#    #+#              #
#    Updated: 2023/03/31 00:11:03 by mmoumani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

BFILES = ft_lstnew_bonus.c 	ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = $(FILES:.c=.o)
BOBJS = $(BFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(BOBJS)
	@ar rc $(NAME) $(OBJS) $(BOBJS)
	@ranlib $(NAME)

$(OBJS) : $(FILES)
	@cc -Wall -Wextra -Werror -c $(FILES)

$(BOBJS) : $(BFILES)
	@cc -Wall -Wextra -Werror -c $(BFILES)

# bonus: $(BOBJS)
# 	ar rc $(NAME) $(BOBJS)
# 	@ranlib $(NAME)

clean:
	@echo "cleaning OBJS files"
	@rm -f $(OBJS) $(BOBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all