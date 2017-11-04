
NET_LIB_DIR = zn_net_lib
BASE_LIB_DIR = zn_base_lib
LOG_LIB_DIR = zn_log_lib
DATAGATHER_LIB_DIR = zn_data_gather

all:net_lib \
	base_lib \
	log_lib \
	data_lib

net_lib:
	${MAKE} -C ${NET_LIB_DIR}

base_lib:
	${MAKE} -C ${BASE_LIB_DIR}
	
log_lib:
	${MAKE} -C ${LOG_LIB_DIR}

data_lib:
	${MAKE} -C ${DATAGATHER_LIB_DIR}

clean:
	${MAKE} -C ${NET_LIB_DIR} clean
	${MAKE} -C ${BASE_LIB_DIR} clean
	${MAKE} -C ${LOG_LIB_DIR} clean
	${MAKE} -C ${DATAGATHER_LIB_DIR} clean