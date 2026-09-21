FLAGS= -Wall -Wextra -g

run: minishell
	@./minishell

debug: minishell
	@gdb minishell	

main.o: src/main.c
	@echo "main.c changes compiling..."
	@gcc $(FLAGS) -c src/main.c

builtins.o: src/builtins.c
	@echo "builtins.c changes compiling..."
	@gcc $(FLAGS) -c src/builtins.c

utils.o: src/utils.c
	@echo "Utils.c changes compiling..."
	@gcc $(FLAGS) -c src/utils.c

executor.o: src/executor.c
	@echo "executor.c changes compiling..."
	@gcc $(FLAGS) -c src/executor.c

parser.o: src/parser.c
	@echo "parser.c changes compiling..."
	@gcc $(FLAGS) -c src/parser.c

minishell: main.o parser.o builtins.o executor.o utils.o
	@gcc $(FLAGS) main.o parser.o builtins.o executor.o utils.o -o minishell

clean: 
	@rm *.o minishell
