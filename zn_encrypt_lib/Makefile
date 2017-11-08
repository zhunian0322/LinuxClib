

MAJOR_VERSION = 
MINOR_VERSION = 
VERSION = ${MAJOR_VERSION}.${MINOR_VERSION}
ENCRYPT_A_LIB_C_TARGE = libencrypt.a

SAMPLE_ENCRY_TEST = zn_encry_test


SAMPLE_DIR = example
SAMPLE_SOURCES_ENCRY_TEST = ${SAMPLE_DIR}/${SAMPLE_ENCRY_TEST}.c




LIB_SOURCES = $(wildcard src/*.c)
LIB_OBJS = $(patsubst %.c,%.o,${LIB_SOURCES})

INCLUDES = inc

LIBS = 
CC = gcc
CXX = g++
AR = ar
CFLAGS = -g -Wall -std=gnu99 -static -I${INCLUDES}


all:${ENCRYPT_A_LIB_C_TARGE} \
	${SAMPLE_ENCRY_TEST}

${ENCRYPT_A_LIB_C_TARGE}:${LIB_OBJS}
	${AR} cru ${ENCRYPT_A_LIB_C_TARGE} ${LIB_OBJS}
	test -d lib || mkdir lib
	mv ${ENCRYPT_A_LIB_C_TARGE} lib/${ENCRYPT_A_LIB_C_TARGE}
	
${LIB_OBJS}:${LIB_SOURCES}
	${CC} -c ${CFLAGS}  $*.c -o $@ 
	
${SAMPLE_ENCRY_TEST}:
	${CC} -c ${CFLAGS} ${SAMPLE_SOURCES_ENCRY_TEST} 
	${CC} ${SAMPLE_ENCRY_TEST}.o  -o ${SAMPLE_ENCRY_TEST}   -Llib -lencrypt  -lcrypto
	test -d ${SAMPLE_DIR}/bin || mkdir ${SAMPLE_DIR}/bin
	mv ${SAMPLE_ENCRY_TEST} ${SAMPLE_DIR}/bin
	cp ${SAMPLE_DIR}/OpenSSL.rar ${SAMPLE_DIR}/bin
	

clean:
	rm -rf lib \
			src/*.o \
			*.o \
			*. ${SAMPLE_DIR}/bin