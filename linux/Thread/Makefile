CC := g++

thread : thread.c
	$(CC) -o $@ $^
	./$@
	-rm $@


pthread_cleanup : pthread_cleanup.c
	$(CC) -o $@ $^
	./$@
	-rm $@


race_condition : race_condition.c
	$(CC) -o $@ $^
	./$@
	-rm $@


pthread_mutex : pthread_mutex.c
	$(CC) -o $@ $^
	./$@ 
	-rm $@