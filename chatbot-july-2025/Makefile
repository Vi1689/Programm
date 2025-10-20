all:
	make -C src/error_handler
	make -C src/database
	make -C src/my_parse
	make -C src/my_analyzer
	make -C src/my_network
	make -C src/ui
	make -C src/server_parallelism
	make -C src/client
	make -C src/server

form:
	clang-format -i src/*/*.c
	clang-format -i include/*/*.h
	clang-format -i src/*/*/*.c

clean:
	make clean -C src/error_handler
	make clean -C src/database
	make clean -C src/my_parse
	make clean -C src/my_analyzer
	make clean -C src/my_network
	make clean -C src/ui
	make clean -C src/server_parallelism
	make clean -C src/client
	make clean -C src/server

rebuild: clean all