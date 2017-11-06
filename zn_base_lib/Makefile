

MAJOR_VERSION = 
MINOR_VERSION = 
VERSION = ${MAJOR_VERSION}.${MINOR_VERSION}
BASE_A_LIB_C_TARGE = libbase.a

SAMPLE_TIME = time
SAMPLE_SYSTEM = system
<<<<<<< HEAD

=======
>>>>>>> dev-gino

SAMPLE_DIR = example
SAMPLE_SOURCES_TIME = ${SAMPLE_DIR}/${SAMPLE_TIME}.c
SAMPLE_SOURCES_SYSTEM = ${SAMPLE_DIR}/${SAMPLE_SYSTEM}.c
<<<<<<< HEAD


=======
>>>>>>> dev-gino




LIB_SOURCES = $(wildcard src/*.c)
LIB_OBJS = $(patsubst %.c,%.o,${LIB_SOURCES})

INCLUDES = inc

LIBS =
CC = gcc
CXX = g++
AR = ar
CFLAGS = -g -Wall -std=gnu99 -static -I${INCLUDES}


all:${BASE_A_LIB_C_TARGE} \
	${SAMPLE_TIME} \
	${SAMPLE_SYSTEM}

${BASE_A_LIB_C_TARGE}:${LIB_OBJS}
	${AR} cru ${BASE_A_LIB_C_TARGE} ${LIB_OBJS}
	test -d lib || mkdir lib
	mv ${BASE_A_LIB_C_TARGE} lib/${BASE_A_LIB_C_TARGE}
	
${LIB_OBJS}:${LIB_SOURCES}
	${CC} -c ${CFLAGS} $*.c -o $@ ${LIBS}
	
${SAMPLE_TIME}:
	${CC} -c ${CFLAGS} ${SAMPLE_SOURCES_TIME} ${LIBS}
	${CC} ${SAMPLE_TIME}.o -o ${SAMPLE_TIME} -L lib -lbase
	test -d ${SAMPLE_DIR}/bin || mkdir ${SAMPLE_DIR}/bin
	mv ${SAMPLE_TIME} ${SAMPLE_DIR}/bin
<<<<<<< HEAD
	
=======

>>>>>>> dev-gino
${SAMPLE_SYSTEM}:
	${CC} -c ${CFLAGS} ${SAMPLE_SOURCES_SYSTEM} ${LIBS}
	${CC} ${SAMPLE_SYSTEM}.o -o ${SAMPLE_SYSTEM} -L lib -lbase
	test -d ${SAMPLE_DIR}/bin || mkdir ${SAMPLE_DIR}/bin
	mv ${SAMPLE_SYSTEM} ${SAMPLE_DIR}/bin

clean:
	rm -rf lib \
			src/*.o \
			*.o \
			*. ${SAMPLE_DIR}/bin