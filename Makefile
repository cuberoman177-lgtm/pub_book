CC = gcc
src = src
inc = include
bin = book
val_flags = -s --leak-check=full --errors-for-leak-kinds=all --error-exitcode=1
build_d = build
eflags = -Werror -Wformat -Wall
cflags = $(eflags) -Og -ggdb -fanalyzer
rcflags = $(eflags) -O2 -s
lflags = -lcurl -lcjson 

all: debug

debug: format build_dir
	$(CC) -c -o $(build_d)/book_utils.o $(src)/book_utils.c $(cflags) $(lflags) -I$(inc)
	$(CC) -c -o $(build_d)/main.o $(src)/main.c $(cflags) $(lflags) -I$(inc)
	$(CC) -o $(build_d)/$(bin).out $(build_d)/*.o $(cflags) $(lflags) -I$(inc)

test: debug
	valgrind $(val_flags) $(build_d)/$(bin).out

build_dir:
	mkdir -p $(build_d)

release: test clean format
	$(MAKE) build_dir
	$(CC) -c -o $(build_d)/book_utils.o $(src)/book_utils.c $(rcflags) $(lflags) -I$(inc)
	$(CC) -c -o $(build_d)/main.o $(src)/main.c $(rcflags) $(lflags) -I$(inc)
	$(CC) -o $(build_d)/$(bin).out $(build_d)/*.o $(rcflags) $(lflags) -I$(inc)
	install -s -v $(build_d)/$(bin).out $(build_d)/$(bin)

format:
	indent -kr $(src)/*.c $(inc)/*.h

clean:
	$(RM) -r $(build_d)
	$(RM) $(src)/*~
	$(RM) $(inc)/*~
