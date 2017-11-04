/** 
* @file zn_log.h
* @brief 基于 linux API 封装日志相关接口
* @author zhunian0322@163.com
* @date 19:22 2017/10/31
* @version 1
*/

#ifndef ZN_LOG_H_
#define ZN_LOG_H_


#include <stdint.h>

/** 日志配置项 */
struct zn_log_configs;
typedef struct zn_log_configs zn_log_config;

/** 日志等级 */
typedef enum {
	ZLL_CUSTOM, 	/**< 自定义级别，将日志打上自定义标记 */
	ZLL_DEBUG, 		/**< 调试级别 */
	ZLL_WARNIG, 	/**< 警告 */
	ZLL_ERROR			/**< 错误 */
} ZN_LOG_LEVEL;

/** 日志处理标识 */
typedef enum {
	ZLSF_NOT, 		/**< 不处理，不保存到文件也不输出到终端 */
	ZLSF_PRINT, 	/**< 输出到终端 */
	ZLSF_FLASH, 	/**< 保存到文件*/
	ZLSF_FULL			/**< 即输出到终端也保存到文件 */
} ZN_LOG_SAVE_FLAG;

/** 
 *  @breif	以 DEBUG 级别打印日志  
 *  @param[in] zlc  zn_log_config 结构体，日志配置项  
 *  @param[in] format 日志内容
 */
#define ZNLOG_DEBUG(zlc,format, ...) zn_log(__FILE__,__LINE__,zlc,ZLL_DEBUG,NULL,format, ##__VA_ARGS__)

/** 
 *  @breif	以 WARNIG 级别打印日志  
 *  @param[in] zlc  zn_log_config 结构体，日志配置项  
 *  @param[in] format 日志内容
 */
#define ZNLOG_WARNIG(zlc,format, ...) zn_log(__FILE__,__LINE__,zlc,ZLL_WARNIG,NULL,format, ##__VA_ARGS__)

/** 
 *  @breif	以 ERROR 级别打印日志  
 *  @param[in] zlc  zn_log_config 结构体，日志配置项  
 *  @param[in] format 日志内容
 */
#define ZNLOG_ERROR(zlc,format, ...) zn_log(__FILE__,__LINE__,zlc,ZLL_ERROR,NULL,format, ##__VA_ARGS__)

/** 
 *  @breif	以 CUSTOM 级别打印日志  
 *  @param[in] zlc  zn_log_config 结构体，日志配置项  
 *  @param[in] tag  日志标签，等同于日志级别标签
 *  @param[in] format 日志内容
 */
#define ZNLOG_CUSTOM(zlc,tag,format, ...) zn_log(__FILE__,__LINE__,zlc,ZLL_CUSTOM,tag,format, ##__VA_ARGS__)

/** 
 *  @breif	日志API初始化  
 *  @param[in] fileName  保存的日志名，如若不需要保存为日志可以将该参数设为 NULL  
 *  @param[in] saveFlag  保存标志，参考  日志处理标识  ZN_LOG_SAVE_FLAG
 *  @param[in] logBufSize 日志缓冲区最大范围
 *  @return  成功返回一个日志配置项结构体指针，失败返回NULL
 */
zn_log_config * zn_log_init(uint8_t *fileName, ZN_LOG_SAVE_FLAG saveFlag,
        uint16_t logBufSize);

/** 
 *  @breif	日志处理函数  
 *  @param[in] fileName  触发日志的文件名  
 *  @param[in] line  		 触发日志所在行
 *  @param[in] zlc 			 日志配置项，由 zn_log_init 返回
 *  @param[in] level		 日志级别, 参考 日志等级 ZN_LOG_LEVEL
 *  @param[in] tag			 日志标签，当日志等级为自定义时才有用，其它日志等级时将该参数设为 NULL 即可
 *  @param[in] format    日志内容
 *  @note  不建议使用该函数，需要日志功能，使用日志打印宏即可
 */
void zn_log(char *filename, int line, zn_log_config * zlc, uint8_t level,
        const uint8_t *tag, char *format, ...);

/** 
 *  @breif	日志配置项API销毁 
 *  @param[in] logConfig  日志配置项
 */
void zn_log_destory(zn_log_config ** logConfig);

#endif /* ZN_LOG_H_ */
