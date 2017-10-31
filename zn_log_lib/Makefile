

MAJOR_VERSION = 
MINOR_VERSION = 
VERSION = ${MAJOR_VERSION}.${MINOR_VERSION}
LOG_A_LIB_C_TARGE = liblog.a

SAMPLE_LOG_TEST = log_test


SAMPLE_DIR = example
SAMPLE_SOURCES_LOG_TEST = ${SAMPLE_DIR}/${SAMPLE_LOG_TEST}.c




LIB_SOURCES = $(wildcard src/*.c)
LIB_OBJS = $(patsubst %.c,%.o,${LIB_SOURCES})

INCLUDES = inc

LIBS = 
CC = gcc
CXX = g++
AR = ar
CFLAGS = -g -Wall -std=gnu99 -static -I${INCLUDES}


all:${LOG_A_LIB_C_TARGE} \
	${SAMPLE_LOG_TEST}

${LOG_A_LIB_C_TARGE}:${LIB_OBJS}
	${AR} cru ${LOG_A_LIB_C_TARGE} ${LIB_OBJS}
	test -d lib || mkdir lib
	mv ${LOG_A_LIB_C_TARGE} lib/${LOG_A_LIB_C_TARGE}
	
${LIB_OBJS}:${LIB_SOURCES}
	${CC} -c ${CFLAGS}  $*.c -o $@ 
	
${SAMPLE_LOG_TEST}:
	${CC} -c ${CFLAGS} ${SAMPLE_SOURCES_LOG_TEST} 
	${CC} ${SAMPLE_LOG_TEST}.o  -o ${SAMPLE_LOG_TEST}   -Llib -llog 
	test -d ${SAMPLE_DIR}/bin || mkdir ${SAMPLE_DIR}/bin
	mv ${SAMPLE_LOG_TEST} ${SAMPLE_DIR}/bin
	

clean:
	rm -rf lib \
			src/*.o \
			*.o \
			*. ${SAMPLE_DIR}/bin