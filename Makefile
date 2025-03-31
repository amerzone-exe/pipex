# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 15:52:51 by jpiquet           #+#    #+#              #
#    Updated: 2025/03/27 16:17:01 by jpiquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src
SRCDIR_bonus = src_bonus

LIBFTDIR = Libft
LIBFT_SRC = Libft/ft_atoi.c Libft/ft_bzero.c Libft/ft_calloc.c \
            Libft/ft_isalnum.c Libft/ft_isalpha.c Libft/ft_isascii.c \
            Libft/ft_isdigit.c Libft/ft_isprint.c Libft/ft_itoa.c \
            Libft/ft_memcpy.c Libft/ft_memmove.c Libft/ft_memset.c \
            Libft/ft_putchar_fd.c Libft/ft_putendl_fd.c Libft/ft_putnbr_fd.c \
            Libft/ft_putstr_fd.c Libft/ft_split.c Libft/ft_strchr.c \
            Libft/ft_strdup.c Libft/ft_strjoin.c Libft/ft_strlen.c \
            Libft/ft_strncmp.c Libft/ft_strnstr.c Libft/ft_strrchr.c \
            Libft/ft_substr.c Libft/ft_tolower.c Libft/ft_toupper.c

LIBFT_INC = Libft/libft.h

OBJDIR = obj
OBJDIR_bonus = obj_bonus

INCDIR = inc
INCDIR_bonus = inc_bonus

SRC =	$(SRCDIR)/main.c \
		$(SRCDIR)/parse.c \
		$(SRCDIR)/pipex.c \
		$(SRCDIR)/pipex_utils.c \
		$(SRCDIR)/error.c \
		$(SRCDIR)/close_fd.c

SRC_BONUS = $(SRCDIR_bonus)/main_bonus.c \
			$(SRCDIR_bonus)/parse_bonus.c \
			$(SRCDIR_bonus)/pipex_bonus.c \
			$(SRCDIR_bonus)/pipex_utils_bonus.c \
			$(SRCDIR_bonus)/error_bonus.c \
			$(SRCDIR_bonus)/close_fd_bonus.c

OBJ_bonus = $(patsubst $(SRCDIR_bonus)/%.c,$(OBJDIR_bonus)/%.o,$(SRC_BONUS))

OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

LIBFT = $(LIBFTDIR)/libft.a

#---------------------------------------------#

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ) inc/pipex.h
	$(CC) $(CFLAGS) -I $(INCDIR) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(NAME) done successfully ✅"

$(LIBFTDIR)/libft.a : $(LIBFT_SRC) $(LIBFT_INC)
	$(MAKE) -s -C $(LIBFTDIR)
	@echo "Libft done successfully ✅"

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

bonus : .bonus $(NAME)

.bonus : $(OBJ_bonus) inc_bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -I $(INCDIR_bonus) -o $(NAME) $(OBJ_bonus) $(LIBFT)
	@touch .bonus
	@echo "Pipex bonus done successfully ✅"

$(OBJDIR_bonus)/%.o : $(SRCDIR_bonus)/%.c | $(OBJDIR_bonus)
	$(CC) $(CFLAGS) -I $(INCDIR_bonus) -o $@ -c $<

$(OBJDIR_bonus):
	@mkdir -p $(OBJDIR_bonus)

clean :
	@rm -rf $(OBJDIR) $(OBJDIR_bonus) .bonus 2>/dev/null
	@$(MAKE) -s -C $(LIBFTDIR) clean
	@echo "Clean done 🗑️"

fclean : clean
	@rm -f $(NAME) $(BONUS) 2>/dev/null
	@$(MAKE) -s -C $(LIBFTDIR) fclean
	@echo "Full clean done 🗑️"

re: 
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY : clean fclean re