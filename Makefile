CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -O2
CC = gcc

# Since this is the first target, it will be executed by default.
.PHONY: all
all: Task1 Task2 #Task3 Task4 #include as many as you've done


#PHONY's are just to ensure, that the rule 'clean' is used, rather then the file 'clean'
.PHONY: clean
clean:
	rm -f Task1 Task2 Task3 Task4
	clear

#Here comes the tasks
Task1:
	$(CC) $(CFLAGS) Task1.c -o $@

Task2:
	$(CC) $(CFLAGS) Task2.c -o $@

Task3:
	$(CC) $(CFLAGS) Task3.c -o $@

Task4:
	$(CC) $(CFLAGS) Task4.c -o $@
