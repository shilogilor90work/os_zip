all: task21

run:
	./check_pid

task21: check_pid.c just_run.c
	gcc -o check_pid check_pid.c
	gcc -o just_run just_run.c

clean:
	-rm check_pid
	-rm just_run
