# obs-studio for HQ

*中文: [中文](readme.zh.md)*

**Build guideline**

* Requirements for using obs-studio for building HQ on windows
    * dependencies2013.zip
    
        Download link：[dependencies2013.zip](https://obsproject.com/downloads/dependencies2013.zip)
   
    * Cmake of Windows version
   
    * visual studio 2013 
    
* Build project with CMake-gui：

    * Start CMake-gui, select source code and project path, then configure
    
    * Set variables in windows environment:
        * DepsPath 

               The path where win32 is located after decompressing dedependencies2013.zip 
        
        * Uncheck Enable\_UI and ENABLE\_SCRIPTING
        * After configure is ok, vs project can be generated.


## How to use agora sdk in your own obs studio

In order to use agora sdk in your own obs studio, there's statement about compile and source code.

### How to create win-agora plugin

* Source code
* Agora SDK
* Compile configuration
            
#### win-agora plugin source code

* Create a folder named win-agora in plugins folder of obs studio, the create agora-plugin.cpp file. obs.dll will automatically load all dll in the plugins folder.

* Include header file obs-module.h, write OBS\_DECLARE\_MODULE to declare win-agora plugin. Register agora\_pcm、agora\_yuv、agora\_service、agora\_output in obs\_load\_module function. When obs.dll load win-agora.dll plugin, it'll register these plugins.

* The most important thing for encoder is obs\_encoder\_info.encode(AgoraPCM\_Encode and AgoraYUV\_Encode). OBS will call agora sdk api in these two function and send audio and video data to agora sdk.
Audio and Video encoders are implemented in agora-pcm-encoder.cpp and agora-yuv-encoder.cpp.

* Besides configure some information for agora sdk by agora\_service, call agora\_service member function to use agora sdk api.
* Add apis in obs.h for agora sdk api, application will call obs api. These new apis will call agora\_service member function.agora\_service is implemented in agora_service.cpp.

* agora ouput is actually a null output.It's used to start or stop agora communication. OBS studio library associated encoder and service with agora output. agora\_service is implemented in agora-output.cpp  

#### Agora sdk            

* dll  copy agora\_rtc\_sdk.dll and agora\_sig\_sdk.dll to dependencies2013\win32\bin
* lib  copy agora\_rtc\_sdk.lib to dependencies2013\win32\bin
* include Create agora folder in dependencies2013\win32\include, then copy agora header files to here.

**Note:If you want to set custom video profile, include IAgoraRtcEngine2.h.**

#### Set compile configurations

* Create a file FindAgora.cmake for win-agora plugin. It's used to search  agora dll that win-agora plugin depends, then set some compile configurations, copy it to CMake\Modules.
* CMakeLists.txt in win-agora folder is used to compile win-agora source code. 
* Configure agora sdk that win-agora plugin depends in CopyMSVCBins.cmake file. When generating win-agora, copy agora dll to CMake\Modules folders.

### Summary

how to use obs studio demo that use agora sdk：

* Copy win-agora folder in plugins to you own plugins folder.
* Copy agora dll and lib folder to dependencies2013\win32\bin. Create agora folder in dependencies2013\win32\include, then copy agora header files here.
* Copy FindAgora.cmake file to CMake\Modules. Copy text including agora in CopyMSVCBins.cmake to you own file CopyMSVCBins.cmake.
* In files obs.h、obs.cpp、obs-service.h,search agora, copy the source code to to you own corresponding files.

After that, you use CMake to compile obs, then generate vs project.UI is optional, you decide by youselft. How to use win-agora plugin, you can reference demo.

##how add agora sdk api and callback

If you need to call agora sdk api and do something in the callback, add these by yourself. Now I just add several necessary apis and callbacks.  Callbacks send signals to the application by signal of obs studio.Some apis, for example, initEngine, joinChannel etc, are encapsulated in win-agora plugin. You don't need to call these apis in the application.


Currently encapsulated apis and callbacks:

**apis：**

* setupRemoteVideo
* addPublishStreamUrl
* removePublishStreamUrl

**callbacks：**

* onJoinChannelSuccess
* onUserOffline
* onUserJoined
* onFirstRemoteVideoDecoded

####how to add agora sdk apis

* In the file obs-service.h，add new memeber function declaration to obs\_service\_info
* In the file agora-service.cpp，Add memeber function implement for agora\_service, the member fucntion will call agora sdk api.
* In the file obs.h, declare api, the first parameter type of this api is obs\_service\_t*
* In the file obs.cpp, implement the api. This api will call new adding member fuction for agora service.
* Then the application call new adding api in obs.h .

You can reference setupRemoteVideo, it's implemented in obs\_service\_agora\_setup\_remote\_video
 and obs\_service\_info.setup\_agora\_remote\_video.

####how to add agora callbacks

After calling some apis, you'll receive agora callbacks. Sometimes you must first  receive callbacks, then you can call other agora apis. For example, after receiving onUserJoined callback, you can call setupRemoteVideo to show remote video.

* In the file obs-service.c, in constant character array service_signals, add callbacks correspond to signals, including return type and function name.
* agorartcengine.cpp，声网回调函数想应用层发出signal，调用signal_handler_signal，通过calldata结构体设置多个参数。

what to do int the application:

* Call signal_handler_connect, connect new adding service signal to the application callback. Note, these callbacks are static member functions, you need notify the main thread(UI thread) by aaplication message(Signal/Slot of QT).

For example, onUserJoined, add callback：

* Add "void userJoined()" in service\_signals.
* In the file agorartcengine.cpp, override onUserJoined, set parameter of the callback, then call

         signal_handler_signal(obs_service_get_signal_handler(m_engine.agoraService), "userJoined", &params);
    you'll receive the signal in the aaplication.

* In the application, associate callback with new signal, call
         
        signal_handler_connect(obs_service_get_signal_handler(agoraService), "userJoined", AgoraUserJoined, &params); 
after receive userJoined signal, it'll call AgoraUserJoined static member function.

* In the member function AgoraUserJoined, notify main thread by qt signal/slot.

        QMetaObject::invokeMethod(App()->GetMainWindow(), "OnUserJoined", Q_ARG(long long, uid));
Now you can do something in OBSBasic::OnUserJoined* 
            
