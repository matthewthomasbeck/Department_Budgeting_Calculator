# Makefile comments……
PROGRAMS = driver
CC = gcc
CFLAGS = -Wall -g
all: $(PROGRAMS)
clean:
	rm -f *.o
# C compilations
queue.o: queue.c queue.h item.h
	$(CC) $(CFLAGS) -c queue.c
priorityQueueDepartment.o: priorityQueueDepartment.c priorityQueueDepartment.h department.h
	$(CC) $(CFLAGS) -c priorityQueueDepartment.c
resourceManagement.o: resourceManagement.c resourceManagement.h queue.h priorityQueueDepartment.h department.h
	$(CC) $(CFLAGS) -c resourceManagement.c
driver.o: driver.c resourceManagement.c resourceManagement.h
	$(CC) $(CFLAGS) -c driver.c
# Executable programs
driver: driver.o queue.o priorityQueueDepartment.o resourceManagement.o
	$(CC) $(CFLAGS) -o driver driver.o queue.o priorityQueueDepartment.o resourceManagement.o
