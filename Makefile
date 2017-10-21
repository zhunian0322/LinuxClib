
NET_LIB_DIR = zn_net_lib

all:net_lib

net_lib:
	${MAKE} -C ${NET_LIB_DIR}

clean:
	${MAKE} -C ${NET_LIB_DIR} clean
