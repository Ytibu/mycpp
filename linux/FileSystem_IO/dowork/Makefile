# 获取当前目录下所有.c文件
SOURCES := $(wildcard *.c)
# 将.c文件名转换为.out可执行文件名
EXECUTABLES := $(SOURCES:.c=.out)

# 默认目标：编译所有可执行文件
all: $(EXECUTABLES)

# 编译规则：将.c文件编译为.out文件
%.out: %.c
	gcc -o $@ $<

# 清理目标：删除所有.out可执行文件
clean:
	rm -f *.out 

# 声明伪目标
.PHONY: all clean
