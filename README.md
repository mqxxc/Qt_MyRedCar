# Qt_MyRedCar
基于Qt框架的Windows动态桌面应用程序
开发环境：

​	操作系统：Windows10

​	开发工具：配置好Qt的VS2019社区版

​	Qt音视频解码器：K-Lite_Codec_Pack_1725_Standard

文件：

awaken_client：exe项目，负责唤醒主窗口

getScreenInformation：dll项目，获取一些信息，如程序所在路径，显示器物理大小等

Loading：exe项目，负责实现加载界面

playVideo：dll项目，负责播放本地视频文件

Qt-MyRedCar：exe项目，主项目。负责主窗口，替换桌面，以及托盘类。

SaveOrRead：dll项目，负责保存数据到本地或者读取数据到程序

Screenshot：dll项目，负责截取视频的某一帧保存合适大小图片至本地。

编译后文件夹功能：

data：存放视频/图片资源

init：存放记录数据的文件

rc：存放程序使用本地图片

awaken_client.exe：辅助唤醒程序

Loading.exe：加载界面动画窗口程序

Qt-MyRedCar：程序入口
