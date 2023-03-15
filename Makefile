MAKEFLAGS		:=	--no-print-directory
.DEFAULT_GOAL	:=	all

.DELETE_ON_ERROR:
.SECONDEXPANSION:

UNAME	:=	$(shell uname)

ifneq ($(UNAME), Linux)
WIN	:=	42
endif

#=================================COMPILATION==================================#
CC					:=	g++
CPPFLAGS			:=	-MP -MMD -I SFML_linux/include -I includes -g3
LIBFSMLFLAG			:=	-L SFML_linux/lib -lsfml-graphics -lsfml-window -lsfml-system
LIBFSMLFLAGWINDOWS	:=	-L SFML_windows/lib -lsfml-graphics -lsfml-window -lsfml-system

#=====================================NAME=====================================#
NAME	:=	minigame

#==================================DIRECTORIES=================================#
BUILD				:= build

EXEC_DIR_LINUX		:=	linux_executable/
EXEC_LINUX			:=	$(EXEC_DIR_LINUX)$(NAME)

EXEC_DIR_WINDOWS	:=	windows_executable/
EXEC_WINDOWS		:=	$(EXEC_DIR_WINDOWS)$(NAME).exe

#====================================TARGETS===================================#
SRCS	:=	srcs/main.cpp

OBJS 	:=	${SRCS:srcs/%.cpp=$(BUILD)/%.o}
DEPS	:=	$(SRCS:srcs/%.cpp=$(BUILD)/%.d)
DIRS	:=	$(BUILD)

#====================================COLORS====================================#
NOC			= \033[0m
BOLD		= \033[1m
UNDERLINE	= \033[4m
BLINK		= \e[5m
BLACK		= \033[1;30m
RED			= \e[1m;31m;
GREEN		= \e[1m;32m;
YELLOW		= \e[1m;33m;
RED			= \e[1m\e[38;5;196m
GREEN		= \e[1m\e[38;5;76m
YELLOW		= \e[1m\e[38;5;220m
BLUE		= \e[1m\e[38;5;33m
VIOLET		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m

#=================================COUNTER UTILS================================#
NB_COMPIL		:=	0

ifndef WIN
ifndef	RECURSIVE
TOTAL_COMPIL		:=	$(shell expr $$(make -n RECURSIVE=1 | grep $(CC) | wc -l) - 1)
endif
endif
ifndef TOTAL_COMPIL
TOTAL_COMPIL		:=	$(words $(OBJS))
endif

#=====================================RULES====================================#
$(DIRS):
	@mkdir $@

ifdef WIN

$(OBJS) : $(BUILD)/%.o : srcs/%.cpp | $$(@D)
	@echo Compiling $<
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(EXEC_WINDOWS): $(OBJS)
	@echo Creation of binary
	@g++ $^ $(LIBFSMLFLAGWINDOWS) -o $(EXEC_WINDOWS)
	@echo Done

all : $(EXEC_WINDOWS)

clean :
	@echo Deleting objects
	@rmdir /s /q $(BUILD)

fclean : clean
	@echo Deleting binary

re : fclean all

run: $(EXEC_WINDOWS)
	@echo Launch game
	@cd $(EXEC_DIR_WINDOWS) && $(NAME).exe
	@echo Have a nice day :)


win :
	g++ -static $(SRCS) $(CPPFLAGS) $(LIBFSMLFLAGWINDOWS) -o $(EXEC_WINDOWS)

winrun :
	cd $(EXEC_DIR_WINDOWS) && $(NAME).exe

.PHONY : all clean fclean re run win winrun

else

$(OBJS) : $(BUILD)/%.o : srcs/%.cpp | $$(@D)
	$(if $(filter $(NB_COMPIL),0), @echo "$(BLUE)Compiling$(NOC)")
	$(eval NB_COMPIL=$(shell expr $(NB_COMPIL) + 1))
	@echo "$(WHITE)[$(NB_COMPIL)/$(TOTAL_COMPIL)] $(VIOLET)Compiling $< $(NOC)"
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(EXEC_LINUX): $(OBJS)
	@echo "$(BLUE)Creation of binary$(NOC)"
	@mkdir $(EXEC_DIR_LINUX) 2>/dev/null || echo -n
	@g++ $^ $(LIBFSMLFLAG) -o $(EXEC_LINUX)
	@echo "$(GREEN)Done$(NOC)"

all : $(EXEC_LINUX)

clean :
	@echo "$(RED)Deleting objects$(NOC)"
	@rm -rf $(BUILD) 2>/dev/null || echo -n

fclean : clean
	@echo "$(RED)Deleting binary$(NOC)"
	@rm -f $(EXEC_LINUX)
	@rmdir $(EXEC_DIR_LINUX) 2>/dev/null || echo -n

re :
	@clear
	@make fclean
	@make

run: $(EXEC_LINUX)
	@echo "$(BLUE)Launch game$(NOC)"
	@export LD_LIBRARY_PATH=../SFML_linux/lib/ && cd $(EXEC_DIR_LINUX) && ./$(NAME)
	@echo "$(GREEN)Have a nice day :)$(NOC)"

runval: $(EXEC_LINUX)
	@echo "$(BLUE)Debug$(NOC)"
	@export LD_LIBRARY_PATH=../SFML_linux/lib/ && cd $(EXEC_DIR_LINUX) && valgrind ./$(NAME)

linux-win :
	x86_64-w64-mingw32-g++ -static $(SRCS) $(CPPFLAGS) $(LIBFSMLFLAGWINDOWS) -o $(EXEC_WINDOWS)

.PHONY : all clean fclean re run runval linux-win

endif

-include $(DEPS)

