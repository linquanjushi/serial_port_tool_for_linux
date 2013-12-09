#for compile hello
CC=gcc  
PROG_NAME=stool
#STOOL_NAME=stool

INCS=./ui/ui.h \
	 ./ui/event.h \
	 ./serial/serial.h
 
SRCS=./ui/ui.c \
	 ./ui/event.c \
	./serial/serial.c \
	 stool.c 





#从xx.c 文件得到 xx.o 文件 
#OBJS=${SRCS:.c=.o}
#OBJS := $(wildcard *.o)
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
OBJS1=ui.o event.o serial.o stool.o 
#编译GTK程序时要用到的库 
LIBS=gtk+-2.0
#---- 用户修改区域 结束

CFLAGS=`pkg-config --cflags ${LIBS}` -g -Wall -lpthread
LDFLAGS=`pkg-config --libs ${LIBS}`  -g -Wall -lpthread

all: ${PROG_NAME}

${PROG_NAME}:${OBJS1}
	${CC} -o ${PROG_NAME} ${OBJS1} ${LDFLAGS} 
#注意：上边”${CC}" 的前边有一个TAB键，而不是空格

#如果有头文件进行修改，则自动编译源文件 
${OBJS1}:${INCS}

${OBJS1}:${SRCS}
	${CC} -c ${SRCS}  ${CFLAGS}

clean:
	rm -f *.o  ${PROG_NAME}

rebuild: clean all
