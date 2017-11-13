一、单个模块目录结构
.
├── example			示例
│   └── bin			
├── inc				头文件
├── lib				静态库
└── src				源文件


二、单个模块简介
zn_net_lib			网络库、目前支持 TCP UDP MQTT
zn_base_lib			基础库、目前支持 获取时间，自定义格式输出时间
zn_log_lib			日志库、目前支持 4 个级别，支持文件记录和终端输出
zn_data_gather  数据结构、目前以实现 单链表
zn_config_lib   基于第三方库(iniparser)应用示例，内含第三方库源码
zn_encrypt_lib  加解密库、 目前支持 AES 256 CBC padding5 加解密、base64编码解码、 md5 校验(文件、字符串)


三、编译变量
make 						编译所有
make net_lib		网络库
make base_lib 	基础库
make log_lib		日志库
make data_lib   数据结构相关
make config_lib 配置文件读取设置示例(基于第三方库)
make encrypt_lib 加解密库
make clean			清除所有	   