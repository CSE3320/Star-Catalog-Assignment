findAngular: src/main.c
	gcc src/main.c src/utility.c -o findAngular -lpthread -lm

clean:
	rm ./findAngular

test: msh test_paths test_quit test_exit test_ls test_cp test_cd test_blank


