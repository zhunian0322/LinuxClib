
NET_LIB_DIR = zn_net_lib
BASE_LIB_DIR = zn_base_lib

all:net_lib \
	base_lib

net_lib:
	${MAKE} -C ${NET_LIB_DIR}

base_lib:
	${MAKE} -C ${BASE_LIB_DIR}
	
clean:
	${MAKE} -C ${NET_LIB_DIR} clean
	${MAKE} -C ${BASE_LIB_DIR} clean
