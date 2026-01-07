CC := gcc

race_condition : race_condition.c
	$(CC) -o $@ $^
	./$@ 
	-rm $@

pthread_mutex : pthread_mutex.c
	$(CC) -o $@ $^
	./$@ 
	-rm $@


conditionVariable : conditionVariable.c
	$(CC) -o $@ $^
	./$@ 
	-rm $@


PC_thread : PC_thread.c
	$(CC) -o $@ $^
	./$@ 
	-rm $@