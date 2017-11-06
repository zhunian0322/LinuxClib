



SAMPLE_CONFIG_FILE_TEST = zn_config_test


SAMPLE_DIR = example
SAMPLE_SOURCES_CONFIG_FILE = ${SAMPLE_DIR}/${SAMPLE_CONFIG_FILE_TEST}.c






INCLUDES = inc

LIBS = -L external_lib/lib -liniparser
CC = gcc
CXX = g++
AR = ar
CFLAGS = -g -Wall -std=gnu99 -static -I${INCLUDES}


all:${SAMPLE_CONFIG_FILE_TEST}


	
${SAMPLE_CONFIG_FILE_TEST}:
	${CC} -c ${CFLAGS} ${SAMPLE_SOURCES_CONFIG_FILE} 
	${CC} ${SAMPLE_CONFIG_FILE_TEST}.o  -o ${SAMPLE_CONFIG_FILE_TEST}   ${LIBS}
	test -d ${SAMPLE_DIR}/bin || mkdir ${SAMPLE_DIR}/bin
	mv ${SAMPLE_CONFIG_FILE_TEST} ${SAMPLE_DIR}/bin
	cp ${SAMPLE_DIR}/test_config ${SAMPLE_DIR}/bin
	

clean:
	rm -rf lib \
			src/*.o \
			*.o \
			*. ${SAMPLE_DIR}/bin