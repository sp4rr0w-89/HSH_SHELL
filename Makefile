FLAGS= -Wall -Wextra

run: minishell
	@./minishell

main.o: src/main.c
	@echo "main.c changes compiling..."
	@gcc $(FLAGS) -c src/main.c

minishell: main.o 
	@gcc $(FLAGS) main.o -o minishell

clean: 
	@rm *.o minishell
