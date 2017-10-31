一、单个模块目录结构
.
├── example			示例
│   └── bin			
├── inc				头文件
├── lib				静态库
└── src				源文件


二、单个模块简介
zn_net_lib			网络库、目前支持 TCP UDP
zn_base_lib			基础库、目前支持 获取时间，自定义格式输出时间
zn_log_lib			日志库、目前支持 4 个级别，支持文件记录和终端输出

三、编译变量
make 						编译所有
make net_lib		网络库
make base_lib 	基础库
make log_lib		日志库
make clean			清除所有	   