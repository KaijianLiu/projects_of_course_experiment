CC = gcc
AR = ar
CFLAGES =  -Wall -std=c99

OBJS = cpuinfo.o kernelinfo.o cputime.o starttime.o meminfo.o diskrequest.o main.o 

TARGET = watch

$(TARGET):$(OBJS)
	$(CC)  -o  $(TARGET) $(OBJS)

$(OBJS):%.o:%.c
	$(CC) -c $<  $(CFLAGES) -o $@

clean:
	-$(RM) $(TARGET) $(OBJS)





