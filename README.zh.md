# 声网连麦工具 (Windows)

*[English](README.md)*

声网连麦工具可以使 OBS Studio 支持连麦功能。

## 使用场景

实时视频聊天工具，该插件依赖于声网SDK。

插件只推一路摄像头视频给远端。 

详细信息可以从官网获取 [agora.io](https://www.agora.io/en)

**运行工具:**

* 先注册声网账户，可以获取一个 APPID。

* 打开OBS菜单栏工具下面的声网连麦，启动连麦对话框。

* 每次启动，第一次运行之前需要设置初始化信息，包括声网APPID，频道号和uid等等。

* 设置之后，可以开始推流到声网。

* 如果想要在连麦的时候推流到一个url，而OBS Studio正在使用这个url。需要先停止OBS Studio推流。声网才能正常向这个url推流。

* 如果连麦工具要使用的摄像头OBS Studio正在使用，会先禁止obs使用，结束连麦以后会再次打开。


## 下载安装包

**Windows**

可以直接安装OBS Stduio 对应版本的连麦工具

* [agora-tool-ui for windows](https://github.com/AgoraIO/OBS/releases/download/3.3.0/Agora-Tool-3.3.0-Installer.exe) (26.1 and later)



**注解：**

26.0.2及以下版本，测试了obs studio 以下几个版本25.0.8 26.0  26.0.2。更老的版本未测试，如果无法加载，建议升级到最新使用26.1及以上的版本。

**Mac**

可以直接安装OBS Stduio 对应版本的连麦工具

* [agora-tool-ui](https://github.com/AgoraIO/OBS/releases/download/3.3.1/Agora-Tool-3.3.1-Installer.dmg)(26.1 and later)


## 编译声网连麦工具

### 准备

1 下载依赖库

   下载[deps](https://github.com/AgoraIO/OBS/releases/download/3.3.0/deps.zip)，解压后将deps拷贝到agora-tool-ui下。如果要使用最新的SDK，到[agora sdk](https://docs.agora.io/cn/All/downloads?platform=All%20Platforms) 去下载,解压后替换r deps/Agora目录下的对应文件。 并且需要去适配声网SDK（如果版本差异太大，接口不同）


2 需要在电脑上安装[Qt 5.14.2](https://github.com/sbd021/Basic-Video-Broadcasting/releases/download/5.14.2/Qt5.14.2.zip),
[CMake](https://cmake.org/download/) 和一个可以工作的 [OBS Studio development environment](https://obsproject.com/wiki/install-instructions) 

**注意**

这个版本基于 obs studio [26.1.2](https://github.com/obsproject/obs-studio/tree/26.1.2)

### Windows

在 cmake-gui，需要设置下面的变量:

* QTDIR （路径）： 编译器对应的QT版本。比如：vs2017 x64
* LIBOBS_INCLUDE_DIR （路径） :OBS Studio源码路径下的子路径libobs。
* LIBOBS_LIB (路径) : libobs项目所在路径
* OBS_FRONTEND_LIB (路径) : obs-frontend-api项目所在路径 

举个例子, obs源码路径是obs-studio，build路径是obs-studio/build64。

* LIBOBS\_INCLUDE\_DIR 的值是 obs-studio/libobs
* LIBOBS\_LIB 的值是 obs-studio/build64/libobs, 
* OBS\_FRONTEND\_LIB 的值是 obs-studio/build64/UI/obs-frontend-api. 

cmake点击configure之后，会得到一个变量LibObs_DIR, 确保它的值是obs-studio/build64/libobs。

### Mac
在编译Mac版本的插件之前，一定要先编译OBS的源码，参考官网文档跑下CI/full-build-macos.sh的脚本

在 cmake-gui，需要设置下面的变量:

* QTDIR （路径）： 编译器对应的QT版本。比如：/usr/local/Cellar/qt/5.15.2/lib/cmake/Qt5
* LIBOBS_INCLUDE_DIR （路径） :OBS Studio源码路径下的子路径libobs。
* LIBOBS_LIB (路径) : libobs项目所在路径
* OBS_FRONTEND_LIB (路径) : obs-frontend-api项目所在路径 例如:obs-studio/UI/obs-frontend-api

举个例子, obs源码路径是obs-studio，build路径是obs-studio/build64。

* LIBOBS\_INCLUDE\_DIR 的值是 obs-studio/build/libobs
* LIBOBS\_LIB 的值是 obs-studio/build/libobs, 
* OBS\_FRONTEND\_LIB 的值是 obs-studio/build/UI/obs-frontend-api. 

cmake点击configure之后，会得到一个变量LibObs_DIR, 确保它的值是obs-studio/build/libobs。


## 运行声网连麦工具

1 启动obs

2 在菜单栏工具中选择“声网连麦工具”，弹出一个对话框。

3 点击设置，填上基本信息。

4 也可以下载配置文件，填上信息主要配置信息。
[AgoraObs.zip](https://github.com/AgoraIO/OBS/releases/download/3.3.0/AgoraObs.zip)

5 配置文件主要包括：

* appid
* token
* channel name
* uid
* rtmp url











