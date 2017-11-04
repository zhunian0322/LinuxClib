


MAJOR_VERSION = 
MINOR_VERSION = 
VERSION = ${MAJOR_VERSION}.${MINOR_VERSION}
DATAGETHER_A_LIB_C_TARGE = libdatagather.a

SAMPLE_LINKLIST = linklist_test


SAMPLE_DIR = example
SAMPLE_SOURCES_LINKLIST = ${SAMPLE_DIR}/${SAMPLE_LINKLIST}.c




LIB_SOURCES = $(wildcard src/*.c)
LIB_OBJS = $(patsubst %.c,%.o,${LIB_SOURCES})

INCLUDES = inc

LIBS =
CC = gcc
CXX = g++
AR = ar
CFLAGS = -g -Wall -std=gnu99 -static -I${INCLUDES}


all:${DATAGETHER_A_LIB_C_TARGE} \
	${SAMPLE_LINKLIST}

${DATAGETHER_A_LIB_C_TARGE}:${LIB_OBJS}
	${AR} cru ${DATAGETHER_A_LIB_C_TARGE} ${LIB_OBJS}
	test -d lib || mkdir lib
	mv ${DATAGETHER_A_LIB_C_TARGE} lib/${DATAGETHER_A_LIB_C_TARGE}
	
${LIB_OBJS}:${LIB_SOURCES}
	${CC} -c ${CFLAGS} $*.c -o $@ ${LIBS}
	
${SAMPLE_LINKLIST}:
	${CC} -c ${CFLAGS} ${SAMPLE_SOURCES_LINKLIST} ${LIBS}
	${CC} ${SAMPLE_LINKLIST}.o -o ${SAMPLE_LINKLIST} -L lib -ldatagather
	test -d ${SAMPLE_DIR}/bin || mkdir ${SAMPLE_DIR}/bin
	mv ${SAMPLE_LINKLIST} ${SAMPLE_DIR}/bin
	

clean:
	rm -rf lib \
			src/*.o \
			*.o \
			*. ${SAMPLE_DIR}/bin