CC := gcc
CFLAGS := -g -Wall -Wextra -Wpedantic

# 获取当前目录下所有.c文件
SOURCES := $(wildcard *.c)
# 将.c文件名转换为.o可执行文件名
EXECUTABLES := $(SOURCES:.c=.o)

# 默认目标：编译所有可执行文件
all: $(EXECUTABLES)

# 编译规则：将.c文件编译为.o文件
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

# 清理目标：删除所有.o可执行文件
clean:
	rm -f *.o 

# 声明伪目标
.PHONY: all clean
