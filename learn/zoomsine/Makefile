
CC = /opt/arm-2009q1/bin/arm-none-linux-gnueabi-gcc
APP = zoomsine

SRC = ../../../cc/src/sinewave/

OBJS1 = $(APP).o
OBJS2 = $(SRC)sinewave.o

OBJS=$(OBJS1) $(OBJS2)

CFLAGS=-g -o

LINKOPTS =  -lm -lpthread -dl

MY_INC=-I/root/srcp/minigui/build-minigui-3.2-138/build/include -I$(SRC)
MY_LIBS=-L /root/code/tslib/build/lib/ -lts -L /root/srcp/minigui/build-minigui-3.2-138/build/lib/ -lminigui_ths -ljpeg -lpng -lz -lfreetype

MY_DEPS=$(MY_LIBS) $(MY_INC)

$(APP):$(OBJS)
	$(CC) $(CFLAGS) $@  $(OBJS) $(MY_DEPS) $(LINKOPTS)

$(OBJS2): $(SRC)%.o:$(SRC)%.c
	$(CC) -c $< $(MY_INC) $(CFLAGS) $@

$(OBJS1): %.o:%.c
	$(CC) -c $< $(MY_INC) $(CFLAGS) $@

#clean
.PHONY : clean
clean:
	rm -f $(OBJS) $(APP)
