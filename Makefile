# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 15:52:51 by jpiquet           #+#    #+#              #
#    Updated: 2025/02/27 17:07:31 by jpiquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -g3 -MMD -MP

SRCDIR = src
LIBFTDIR = Libft
MLXDIR = mlx-linux
OBJDIR = obj
INCDIR = inc

SRC =	$(SRCDIR)/main.c

OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
LIBFT = $(LIBFTDIR)/libft.a

.DEFAULT_GOAL = all

DEPS = $(OBJ:.o=.d)

CLEAN_MARKER = .clean_done
FCLEAN_MARKER = .fclean_done

-include $(DEPS)


define animate_dots
	@for i in 1 2 3; do \
		printf "." && sleep 0.5; \
	done; \
	echo
endef

# define progress_bar
# 	@echo -n "Compiling $(NAME) "
# 	@for i in {1..10}; do \
# 		sleep 0.1; \
# 		echo -n "#"; \
# 	done
# 	@echo "$(NAME) done successfully ✅"
# endef

#---------------------------------------------#

all : $(LIBFT) $(NAME)


$(NAME) : $(OBJ) inc/pipex.h
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(MLXDIR) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS) 2>/dev/null


$(LIBFTDIR)/libft.a :
	@echo -n "Compiling Libft"
	@$(call animate_dots)
	@$(MAKE) -s -C $(LIBFTDIR)
	@echo "Libft done successfully ✅"


$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	@echo -n "Compiling $(NAME)"
	@$(call animate_dots)
	@$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $< 2>/dev/null
	@echo "$(NAME) done successfully ✅"
	

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean : $(CLEAN_MARKER)

$(CLEAN_MARKER) :
	@echo -n "Cleaning object files"
	@$(call animate_dots)
	@rm -rf $(OBJDIR) 2>/dev/null
	@$(MAKE) -s -C $(LIBFTDIR) clean
	@echo "Clean done 🗑️"
	@touch $(CLEAN_MARKER)

fclean : $(FCLEAN_MARKER)

$(FCLEAN_MARKER) : $(CLEAN_MARKER)
	@echo -n "Cleaning executable and libraries"
	@$(call animate_dots)
	@rm -f $(NAME) 2>/dev/null
	@$(MAKE) -s -C $(LIBFTDIR) fclean
	@echo "Full clean done 🗑️"
	@touch $(FCLEAN_MARKER)

re: 
	@$(MAKE) -s fclean
	@$(MAKE) -s all
	@rm -f $(CLEAN_MARKER) $(FCLEAN_MARKER)

.PHONY : clean fclean re