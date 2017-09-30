

MAJOR_VERSION = 
MINOR_VERSION = 
VERSION = ${MAJOR_VERSION}.${MINOR_VERSION}
NET_A_LIB_C_TARGE = libnet.a

SAMPLE_TCP_CLINET = tcpClient
SAMPLE_TCP_SERVER = tcpServer

SAMPLE_DIR = example
SAMPLE_SOURCES_TCP_CLINET = ${SAMPLE_DIR}/${SAMPLE_TCP_CLINET}.c
SAMPLE_SOURCES_TCP_SERVER = ${SAMPLE_DIR}/${SAMPLE_TCP_SERVER}.c

LIB_SOURCES = $(wildcard src/*.c)
LIB_OBJS = $(patsubst %.c,%.o,${LIB_SOURCES})

INCLUDES = inc

LIBS =
CC = gcc
CXX = g++
AR = ar
CFLAGS = -g -Wall -std=gnu99 -static -I${INCLUDES}


all:${NET_A_LIB_C_TARGE} ${SAMPLE_TCP_CLINET} ${SAMPLE_TCP_SERVER}

${NET_A_LIB_C_TARGE}:${LIB_OBJS}
	${AR} cru ${NET_A_LIB_C_TARGE} ${LIB_OBJS}
	test -d lib || mkdir lib
	mv ${NET_A_LIB_C_TARGE} lib/${NET_A_LIB_C_TARGE}
	
${LIB_OBJS}:${LIB_SOURCES}
	${CC} -c ${CFLAGS} $*.c -o $@ ${LIBS}
	
${SAMPLE_TCP_CLINET}:
	${CC} -c ${SAMPLE_SOURCES_TCP_CLINET} ${LIBS}
	${CC} ${SAMPLE_TCP_CLINET}.o -o ${SAMPLE_TCP_CLINET} -L lib -lnet
	test -d ${SAMPLE_DIR}/bin || mkdir ${SAMPLE_DIR}/bin
	mv ${SAMPLE_TCP_CLINET} ${SAMPLE_DIR}/bin
	
${SAMPLE_TCP_SERVER}:
	${CC} -c ${SAMPLE_SOURCES_TCP_SERVER} ${LIBS}
	${CC} ${SAMPLE_TCP_SERVER}.o -o ${SAMPLE_TCP_SERVER} -L lib -lnet
	test -d ${SAMPLE_DIR}/bin || mkdir ${SAMPLE_DIR}/bin
	mv ${SAMPLE_TCP_SERVER} ${SAMPLE_DIR}/bin
	
clean:
	rm -rf lib \
			src/*.o \
			*.o \
			*. ${SAMPLE_DIR}/bin
