
CC = /opt/arm-2009q1/bin/arm-none-linux-gnueabi-gcc
APP = combobox

OBJS = $(APP).o

LINKOPTS = -g  -lm -lpthread -dl

MY_INC=-I/root/srcp/minigui/build-minigui-3.2-138/build/include
MY_LIBS=-L /root/code/tslib/build/lib/ -lts -L /root/srcp/minigui/build-minigui-3.2-138/build/lib/ -lminigui_ths -ljpeg -lpng -lz -lfreetype


MY_DEPS=$(MY_LIBS) $(MY_INC)

$(APP):$(OBJS)
	$(CC) -o $@  $(OBJS) $(MY_DEPS) $(LINKOPTS)

$(OBJS): %.o:%.c
	$(CC) -c $< $(MY_INC)


#clean
.PHONY : clean
clean:
	rm -f $(OBJS) $(APP)
