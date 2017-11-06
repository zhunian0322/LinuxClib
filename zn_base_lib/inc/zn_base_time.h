/** 
* @file zn_base_time.h
* @brief 基于 linux API 封装时间相关接口
* @author zhunian0322@163.com
* @date 15:22 2017/10/22
* @version 1
*/

#ifndef ZN_BASE_TIME_H_
#define ZN_BASE_TIME_H_

#include <sys/time.h>



/** 时区 */
typedef enum {
	TZ_WEST_ELEVEN = -11,	/**< 西十一区 */
	TZ_WEST_TEN,			/**< 西十区 */
	TZ_WEST_NINE,			/**< 西九区 */
	TZ_WEST_EIGHT,			/**< 西八区 */
	TZ_WEST_SEVEN,			/**< 西七区 */
	TZ_WEST_SIX,            /**< 西六区 */
	TZ_WEST_FIVE,           /**< 西五区 */
	TZ_WEST_FOUR,           /**< 西四区 */
	TZ_WEST_THREE,          /**< 西三区 */
	TZ_WEST_TWO,            /**< 西二区 */
	TZ_WEST_ONE,            /**< 西一区 */
	TZ_EAST_WEST_TWELVE,    /**< 东西十二区 */
	TZ_EAST_ONE,            /**< 东一区 */
	TZ_EAST_TWO,            /**< 东二区 */
	TZ_EAST_THREE,          /**< 东三区 */
	TZ_EAST_FOUR,           /**< 东四区 */
	TZ_EAST_FIVE,           /**< 东五区 */
	TZ_EAST_SIX,            /**< 东六区 */
	TZ_EAST_SEVEN,          /**< 东七区 */
	TZ_EAST_EIGHT,          /**< 东八区 */
	TZ_EAST_NINE,           /**< 东九区 */
	TZ_EAST_TEN,            /**< 东十区 */
	TZ_EAST_ELEVEN          /**< 东十一区 */
} ZN_TIMEZONE;

typedef struct {
	struct timeval tv;
	struct timezone tz;
} zn_time_info ;

/** 
 *  @breif	获取当前系统时间，精确到毫秒，含时区信息  
 *  @param[out] zti  zn_time_info 结构体，存放获取的信息  
 *  @return 成功返回0，失败返回-1；
 */
int zn_base_getSystemNowTime(zn_time_info *zti);

/** 
 *  @breif	获取当前系统时间(格式化输出)
 *  @param[out] result  格式化结果缓冲区 
 *  @param[in] len  缓冲区最大长度  
 *  @param[in] format 输出格式
 *  @param[in] zti zn_time_info 结构体。
 *  @warning 需先调用 zn_base_getSystemNowTime();
 *  @note    format 说明
 *    	%a 星期几的简写 
 *		%A 星期几的全称 
 *		%b 月分的简写 
 * 		%B 月份的全称 
 *		%c 标准的日期的时间串 
 *		%C 年份的后两位数字 
 *		%d 十进制表示的每月的第几天 
 *		%D 月/天/年 
 *		%e 在两字符域中，十进制表示的每月的第几天 
 *		%F 年-月-日 
 *		%g 年份的后两位数字，使用基于周的年 
 *		%G 年分，使用基于周的年 
 *		%h 简写的月份名 
 *		%H 24小时制的小时 
 *		%I 12小时制的小时 
 *		%j 十进制表示的每年的第几天 
 *		%m 十进制表示的月份 
 *		%M 十时制表示的分钟数 
 *		%n 新行符 
 *		%p 本地的AM或PM的等价显示 
 *		%r 12小时的时间 
 *		%R 显示小时和分钟：hh:mm 
 *		%S 十进制的秒数 
 *		%t 水平制表符 
 *		%T 显示时分秒：hh:mm:ss 
 *		%u 每周的第几天，星期一为第一天 （值从0到6，星期一为0） 
 *		%U 第年的第几周，把星期日做为第一天（值从0到53） 
 *		%V 每年的第几周，使用基于周的年 
 *		%w 十进制表示的星期几（值从0到6，星期天为0） 
 *		%x 标准的日期串 
 *		%X 标准的时间串 
 *		%y 不带世纪的十进制年份（值从0到99） 
 *		%Y 带世纪部分的十进制年份 
 *		%z，%Z 时区名称，如果不能得到时区名称则返回空字符。 
 *		%% 百分号 
 */
void zn_base_getSystenNowTime_format(char *result,int len,const char *format,zn_time_info zti);

/** 
 *  @breif	获取当前系统时间，精确到毫秒，含时区信息  
 *  @param[in] zti  zn_time_info 结构体。  
 *  @return 返回所属时区信息
 *  @warning 需先调用 zn_base_getSystemNowTime();
 */
ZN_TIMEZONE zn_base_getSystemTimeZone(zn_time_info zti);

#endif /* ZN_BASE_TIME_H_ */
