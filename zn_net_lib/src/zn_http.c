/** 
* @file zn_http.c
* @brief 基于libghttp二次封装
* @author zhunian0322@163.com
* @date 14:14 2017/11/14
* @version 1
*/



#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <ghttp.h>
#include <ghttp_constants.h>

int zn_download(const char *uri, const char *saveFileName){
	if(uri == NULL || saveFileName == NULL)
		return -1;

	FILE *fp =  fopen(saveFileName,"w");
	if(fp == NULL)
		return -2;

	ghttp_request *request = NULL;
	ghttp_status status;


	if((request = ghttp_request_new()) == NULL)
		goto exit_error;


	if(ghttp_set_uri(request, (char *)uri) == -1)
		goto exit_error;

	if(ghttp_set_type(request, ghttp_type_get) == -1)
		goto exit_error;

	ghttp_prepare(request);

	if((status = ghttp_process(request)) == ghttp_error)
		goto exit_error;

	char *buf = ghttp_get_body(request);
	int bLen = ghttp_get_body_len(request);

	fwrite(buf, bLen, 1, fp);
	fflush(fp);
	fclose(fp);

	ghttp_clean(request);
	ghttp_request_destroy(request);
	return bLen;
	

exit_error:
	fclose(fp);
	return -3;

	
}

int zn_get(const char *uri, const char *params, int timeout, char *result, int resultLen){
	if(uri == NULL || result == NULL)
		return -1;

	ghttp_request *request = NULL;
	
	request = ghttp_request_new();
	 if(params != NULL && strlen(params) > 0){
		char tmp[1024] = {'\0'};
		strcpy(tmp,uri);
		if(strchr(tmp,'?') == NULL)
			strcat(tmp, "?");
		strcat(tmp,params);
		ghttp_set_uri(request,tmp);
	 }
	 else{
	 	ghttp_set_uri(request,(char *)uri);
	 }
	
	 ghttp_set_type(request, ghttp_type_get);

	 ghttp_set_header(request, http_hdr_Connection, "close");
	
	 char timeoutStr[10];
	 snprintf(timeoutStr,10,"%d",timeout);
	 ghttp_set_header(request, http_hdr_Timeout, timeoutStr);
	
	 ghttp_prepare(request);
	 ghttp_process(request);
	
	char *tmp  = ghttp_get_body(request);
	resultLen = ghttp_get_body_len(request);
	memcpy(result, tmp, resultLen);

	 
	 ghttp_clean(request);
	 ghttp_request_destroy(request);

	
	 return resultLen;	
}

int zn_post(const char *uri, const char *params, int timeout, char *result, int resultLen){
	if(uri == NULL || params == NULL)
		return -1;

	ghttp_request *request = NULL;
	ghttp_status status;

	request = ghttp_request_new();

	if(ghttp_set_uri(request, (char *)uri)  == -1)
		return -1;
	if(ghttp_set_type(request, ghttp_type_post) == -1)
		return -1;

	ghttp_set_header(request, http_hdr_Content_Type, "application/x-www-form-urlencoded");

	char timeoutStr[10];
	snprintf(timeoutStr, 10, "%d",timeout);

	ghttp_set_header(request, http_hdr_Timeout, timeoutStr);

	ghttp_set_body(request, (char *)params, strlen(params));
	ghttp_prepare(request);
	if((status = ghttp_process(request)) == ghttp_error)
		return -1;

	char *tmp  = ghttp_get_body(request);
	resultLen = ghttp_get_body_len(request);
	memcpy(result, tmp, resultLen);

	
	ghttp_clean(request);
	ghttp_request_destroy(request);
	return resultLen;

}



char *zn_base64_post_convert(char *base64Str,char resBuf[], int resBufLen){
	if(base64Str == NULL)
		return NULL;

	int len = strlen(base64Str);
	if((len * 4) > resBufLen)
		return NULL;

	int i = 0, j = 0;
	for(; i < len; ++i,++j){
		if(base64Str[i] == '+'){
			resBuf[j] = '%';
			resBuf[++j] = '2';
			resBuf[++j] = 'B';
		}
		else
			resBuf[j] = base64Str[i];
	}

	resBuf[j] = '\0';

	return resBuf;
}

