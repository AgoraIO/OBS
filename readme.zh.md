# obs studio集成声网sdk

*English: [English](README.md)*

* 基于win32
* agora sdk版本2.2.1
* obs stduio 版本21.1

## 编译环境

* CMake 2.8.12以上
* vs2013
* QT 5.8(可选，如果不需要界面，可以不需要QT。默认是有界面的)

配好环境，CMake上选择源码路径和生成路径，编译器选择vs2013，编译即可生成vs解决方案。


## 如何在自己的obs studio中集成声网sdk
上面大概介绍了一些obs studio集成agora sdk的编译环境，接下来从脚本和代码层面做一些说明作为参考，以便用户在自己的obs studio库中集成声网sdk。

### 在应用层初始化 Agora Service Settings

可以参考 window-basic-main.cpp 文件中的源码(OBSBasic::InitAgoraServiceSettings).

* agora\_video\_bitrate

    视频码率
* fps

    视频帧率
* agora\_out\_cx and agora\_out\_cy

    视频输出分辨率宽高
* agora\_appid
    
    声网 appid
* agora\_uid

    调用joinChannel时，使用的声网用户id
* agora\_channel

     调用joinChannel时，使用的声网channel

* enableWebSdkInteroperability

   允许web sdk和windows/ios/android sdk互通

### 如何创建win-agora插件
* 源码
* 声网sdk
* 编译配置

#### 实现插件的源码
 （1）在plugins下创建win-agora文件夹，在目录下创建agora-plugin.cpp文件，obs.dll会自动加载plugins下的所有插件（生成目录下的plugins）。

（2） 包含头文件obs-module.h，OBS_DECLARE_MODULE用来声明插件，obs_load_module函数中注册agora_pcm、agora_yuv、agora_service、agora_output，在obs.dll加载win-agora.dll时，会注册这些插件。

（3）编码器最重要的是obs_encoder_info.encode（AgoraPCM_Encode和AgoraYUV_Encode），obs裸数据会在这两个接口中调用裸数据接口即可将数据送入agora sdk。
agora-pcm-encoder.cpp和agora-yuv-encoder.cpp分别实现了音频和视频编码器。

（4）agora service除了配置一些信息外，所有的sdk接口功能都通过agora service调用。
通过obs添加接口提供给应用层调用，agora service的实现最终都会调用agora sdk api。agora-service.cpp

（5）agora ouput，实际上就是一个null output，主要用来控制整个连麦过程的开始结束。obs studio库最后会操作与agora output相关联的encoder和service。agora-output.cpp

### 声网sdk


* dll  动态库拷贝obs studio依赖库到dependencies2013\win32\bin
* lib  lib拷贝到dependencies2013\win32\bin
* include 在dependencies2013\win32\include下创建agora文件夹存放声网头文件

注意： 注意头文件要包含IAgoraRtcEngine2.h用来自定义输出分辨率的接口

#### 编译选项配置

* 创建win-agora编译配置文件FindAgora.cmake，主要用来找到win-agora依赖的库以及配置一些编译环境变量。放在CMake\Modules文件夹目录下
* CMakeLists.txt 插件源码win-agora目录下的CMakeLists.txt，用来配置要编译的源码文件
* CopyMSVCBins.cmake添加拷贝win-agora插件依赖的声网sdk配置，生成插件时会将声网dll拷贝到指定的运行目录。放在CMake\Modules文件夹目录下



### 总结

总结一下，用户如何利用声网提供的demo：

* 将plugins下的整个win-agora拷贝到自己的plugins目录下
* 将agora dll和lib拷贝到dependencies2013\win32\bin下，agora头文件拷贝到dependencies2013\win32\include
* 将FindAgora.cmake拷贝到CMake\Modules下，将CopyMSVCBins.cmake中包含agora的部分拷贝到自己的CopyMSVCBins.cmake文件中
* 在obs.h、obs.cpp、obs-service.h中搜索agora,并把对应的代码拷贝到自己的obs studio库中。

如果按照以上操作，就可以用CMake编译生成obs库了，也可以包含界面，可以自行选择。现在的demo在应用层加了一个界面，也修改了CMakeLists.txt。应用层如何使用的win-agora可以参考。

##用户自己添加声网sdk接口和回调函数
声网的接口和回调函数，如果应用层需要处理，就需要自己来添加了。目前只添加了几个需要用到的接口和回调函数。一些接口，比如：InitEngine、JoinChannel等都封装在了插件底层。回调函数要从底层插件上传到应用层可见，利用了obs库的signal机制。

目前已经封装的接口和回调如下：

**接口：**
* setupRemoteVideo
* addPublishStreamUrl
* removePublishStreamUrl

**回调函数：**
* onJoinChannelSuccess
* onUserOffline
* onUserJoined
* onFirstRemoteVideoDecoded

#### 如何添加一个声网sdk接口

* obs-service.h中，为obs\_service\_info添加新的成员函数声明
* 在agora-service.cpp中，为agora\_service添加一个成员，该成员是个函数，会调用声网对应的接口。
* 在obs.h中，声明该接口，接口第一个参数为obs\_service\_t*
* 在obs.cpp中，实现该接口。接口中会调用在agora service中新添加的成员。
* 应用层调用新声明的接口即可。

可以参考setupRemoteVideo，具体实现obs_service_info.setup_agora_remote_video和obs接口obs\_service\_agora\_setup\_remote\_video

#### 如何添加声网的回调函数

 业务逻辑有时候要等到回调函数之后再进行下一步操作，比如：收到onUserJoined回调函数之后才会设置远端的视频画布，用来显示远端的视频。

* 在obs-service.c中，常量字符串数组service_signals中添加响应函数对应的信号声明，包括函数返回类型和函数名。
* agorartcengine.cpp，声网回调函数想应用层发出signal，调用signal\_handler\_signal，通过calldata结构体设置多个参数。

下面是应用层需要做的：

* 调用signal\_handler\_connect将声明的信号和对应的应用层声明的响应函数相关联。注意，关联的回调函数为静态函数，需要通过应用层的消息机制传给主线程（界面线程）做最后处理

**以onUserJoined为例，添加回调函数：**

* service\_signals字符串数组加入"void userJoined()"

* 在agorartcengine.cpp中重写onUserJoined，设置对应的参数param，然后调用signal\_handler\_signal(obs_service_get_signal_handler(m_engine.agoraService), "userJoined", &params);
回调函数会传到应用层。
* 在应用层将对应的回调函数和signal相关联，调用signal\_handler\_connect(obs\_service\_get\_signal\_handler(agoraService), "userJoined", AgoraUserJoined, &params); 
* 收到userJoined信号后会调用AgoraUserJoined静态成员函数
在AgoraUserJoined中再通过qt的signal/slot 函数通知主线程。QMetaObject::invokeMethod(App()->GetMainWindow(), "OnUserJoined", Q\_ARG(long long, uid));
* 最后会调用主线程的函数OBSBasic::OnUserJoined

**注解：**
应用层调用signal\_handler\_connect和底层插件调用signal\_handler\_signal第一个参数都是obs\_service\_get\_signal\_handler(obs\_service\_t*)。获取的是相同的service signal hanlder
