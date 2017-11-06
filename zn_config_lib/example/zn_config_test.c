
#include <stdio.h>
#include <stdlib.h>

#include "../external_lib/inc/iniparser.h"


int main(){
	dictionary *config_file = NULL;
	// 加载配置文件
	config_file = iniparser_load("test_config");
	if(config_file == NULL){
		fprintf(stderr, "can not open %s file!\n","test_config");
		exit(EXIT_FAILURE);
	}

	// 获取 dictionary 对象的 section 个数 ，并打印每个 section 的名字
	int scount = iniparser_getnsec(config_file);
	for(int i = 0; i < scount ; ++i)
		printf("%d\t%s\n",i+1,iniparser_getsecname(config_file, i));

	// 获取 dictionary 对象某个 section 下的 key 个数 ， 并打印每个 key 的名字
	int kcount = iniparser_getsecnkeys(config_file, iniparser_getsecname(config_file, 1));
	const char **keys = malloc(20*1024);
	iniparser_getseckeys(config_file,iniparser_getsecname(config_file, 1),keys);
	for(int i = 0; i < kcount ;++i)
		printf("%d\t\%s\n",i+1,keys[i]);
	
	// 输出 key 的值
	printf("Server Host %s\n",iniparser_getstring(config_file, keys[0], NULL));
	printf("Server Port %d\n",iniparser_getint(config_file, keys[1], -1));

	// 释放 dictionary 对象(内存)
	iniparser_freedict(config_file);
	
	
}


