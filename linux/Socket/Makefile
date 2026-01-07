CC := gcc

# 默认目标
.PHONY: clean


# 模式规则：匹配任何目标，自动编译对应的.c文件
%: %.c
	$(CC) -o $@ $<

ip_addr : ip_addr.c
	$(CC) -o $@ $^
	./$@
	-rm $@


socket_Server : sesocket_Server.c
	$(CC) -o $@ $^


socket_Client : socket_Client.c
	$(CC) -o $@ $^


select_Server : select_Server.c
	$(CC) -o $@ $^

select_Client : select_Client.c
	$(CC) -o $@ $^


clean:
	-rm -f socket_Server
	-rm -f socket_Client
	-rm -f ip_addr
	-rm -f select_Server
	-rm -f select_Client