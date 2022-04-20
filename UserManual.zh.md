# 用户手册

# 开启声网连麦工具

* 在菜单栏选择工具
* 选择声网连麦
* 然后会弹出连麦对话框

# 主界面

* 开始推流到声网

     开始连麦，第一次运行需要预先设置一下基本信息。

* 设置
     
     显示设置界面，用来设置连麦基本信息，音视频参数和旁路推流信息。

* 退出

     关闭连麦对话框

# 设置界面


## 通用

用填写基本信息

* 加载配置文件（手动输入频道信息的方式）

    * 先下载配置文件， [下载地址](https://github.com/AgoraIO/OBS/releases/download/3.3.0/AgoraObs.zip)
    * 然后解压，填写上Appid等对应的信息
    * 点击 加载，会自动在界面填写对应的信息
    * 配置文件：

            AppId=       
            AppToken=    
            UID=         
            ChannelName= 
            RtmpUrl=     
    
    
* 获取频道信息的方式

    * 手动输入频道信息的方式，手动填写信息或者通过ini加载
    * http get 请求获取频道信息，需要客户有一个对应的http 服务器，填写对应的url，通过http get请求获取对应的信息，
         返回的信息是json串，对应的格式：

            {
            	"code": 0,
            	"data": {
            		"appID": "xxxx",
            		"channelName": "xxxxx",
	            	"uid": "1200433",
	            	"token": "xxxx",
	            	"cameraUid": "1303713",
	            	"cameraToken": "xxxxxx"
	            }
            }
*  APPID  

    声网 appid，注册账号之后可以创建 项目会生成对应的appid

* 初始化

    会先初始化声网引擎，操作音频播放设备需要先初始化

*  AppToken  

    通过appid appcertificate 以及频道号和uid计算之后的token

* 频道 

     频道号，加入同一频道号可以，进行连麦，或者观看主播 

* 用id 

      uid，在同一频道uid 必须相同，无符号32位整数


* 摄像头uid
    
    单发送obs摄像头视频的uid。
* 摄像头token  

    对应摄像头uid的计算之后的token
* 发送摄像头视频

    除了发送整个obs合图画面外，单独发送一路摄像头视频。主要是用于当观众端APP在后台运行时，只显示一个小窗口的视频。
    
    观众端可以根据是在前台还是后台运行决定订阅哪一路视频

* CPU阈值

    当系统CPU 在两分钟内有多次达到这个阈值的时候，就会提示CPU过高。用户可以根据提示关掉一些暂时不使用的程序

* 音视频日志时间间隔

     每过一段时间记录一次推音频流和视频流给声网SDK的时间点

* 不接收远端音视频

      有些主播不希望和别人连麦，只想推流，就可以选中该选项。

* 保存APPID以外的其他所有设置，包括音频，视频，旁路推流设置

      程序推出之后，会保存之前设置的一些信息，下次运行会自动加载。
* 发送大小流

      同时发送obs主画面的大流和小流
* 永久保存APPID

      也是为了下次运行自动加载APPID，一般不建议保存到本地。  
 


## 音频

* 采样率

    暂时无用，插件默认使用48kHz
* 声道

     用来判断设置Audio Profile的参数，配合高音质一起使用。比如：双声道插件内部可以设置

        AUDIO_PROFILE_MUSIC_STANDARD_STEREO或者AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO

     如果是单声道，插件内部可以设置

        AUDIO_PROFILE_MUSIC_STANDARD或者AUDIO_PROFILE_MUSIC_HIGH_QUALITY

* 音频场景

     对应Audio Profile的场景

* 设置Audio Profile

    选中Audio Profile，加入频道前才会调用setAudioProfile设置。


* 高音质

     如果选中高音质，Audio Profile可以是

        AUDIO_PROFILE_MUSIC_HIGH_QUALITY 或者AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO

* 保存音频原始数据

     在obs日志路径下保存pcm数据的文件。

**注意**

    上面参数主要是针对setAudioProfile的参数设置，可以参考官网文档查询setAudioProfile和对应的参数

 * 扬声器设置

     每次启动运行，需要显示初始化，或者开始推流到声网再停止推流到声网，就可以显示扬声器设备。

     用来切换播放远端音频的扬声器，设置扬声器音量。

     如果只是推流，不需要设置。这个设置会影响养生设备的音量。

* loopback

     声网SDK 采集扬声器声音，选中loopback时，obs不要采集桌面音频

## 视频

  用来视频输出编码参数

*  第一个输出码率

    用来选择输出码率的设置方式

    * 使用声网码率

          由SDK根据 输出码率自行计算码率大小。此时可以选择输出码率
    * 使用OBS 码率

          再OBS设置界面设置对应的码率
* 第二个输出码率

    对应SDK VideoEncoderConfiguration的参数。参数官网文档说明：

        COMPATIBLE_BITRATE
        STANDARD_BITRATE
        DEFAULT_MIN_BITRATE

* 摄像头编码分辨率

    当在通用中，选中发送摄像头的时候，才需要设置。设置摄像头输出的分辨率

* 摄像头编码码率。

      当在通用中，选中发送摄像头的时候，才需要设置。设置摄像头输出的编码码率。

      参数和第二个输出码率一样

* 摄像头编码帧率

    当在通用中，选中发送摄像头的时候，才需要设置。设置摄像头输出的帧率。



## 旁路推流

  对应声网的旁路推流参数
  
* Url 地址

    旁路推流地址，cdn 推流地址。addPublishStreamUrl的第一个参数。和obs直接推送到定制

* 帧率

    推流到cdn的帧率

* 宽和高

    推流到cdn的分辨率 宽和高

## 网络测试

  
* 开始网络测试

    加入频道前先进性网络测试，然后会给出网络测试结果，可以提前了解到网络测试结果。

    测试之后需要停止网络测试。
