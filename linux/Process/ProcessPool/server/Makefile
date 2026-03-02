CC := gcc
CFLAGS := -g -Wall -Wextra -Wpedantic
LDFLAGS := -lpthread

# 获取当前目录下所有.c文件
SOURCES := $(wildcard *.c)
# 将.c文件名转换为.o文件名
OBJECTS := $(SOURCES:.c=.o)

# 最终生成server可执行文件
server.out: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# 编译规则：将.c文件编译为.o文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标：删除所有.o文件和server可执行文件
clean:
	rm -f *.o server.out

# 声明伪目标
.PHONY: server.out clean
