

#include <stdio.h>
#include <stdlib.h>

#include <../inc/zn_http.h>


int main(int argv,char *str[]){

	zn_download("http://testfiles.ourslinks.com/gateway/dtston.tar.gz", "dtston_1.tar.gz");
	printf("Download done!\n");


	char *buf = (char *)malloc(sizeof(char) * 102400) ;
//	zn_get("http://blog.csdn.net/fangquan1980/article/details/49363173",NULL,30,buf,102400);
	//printf("%s\n",buf);
	
	char postStr[1024];
	zn_base64_post_convert("mac=gttM+pj15tCIBl/BAm17kg==&rtime=1503483679&sign=4a349e34dd964746905e9427bafc86c2&uuid=010107E1061B00000057+",postStr,1024);
	zn_post("http://192.168.0.77/test.php",postStr,60,buf,102400);

	printf("%s\n",buf);

}	
