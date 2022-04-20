# User Manual

# Agora RTC Tool

* Select Tool in menu
* Agora Rtc Tool
* Show a Dialog for rtc

# Main UI

* Start Streaming to Agora

     Start Streaming, you need to set basic information when first Start Streaming.

* Settings
     
     Show settings dialog. Set basic information for rtc in this dialoig including audio, video and rtmp streaming information.

* Exit

      Close dialog for rtc.

# Setting UI


## General

Fill user basic information

* Load configure file (fill channel information manually)

    * Load configure file, [download url](https://github.com/AgoraIO/OBS/releases/download/3.3.0/AgoraObs.zip)
    * Unzio file, fill information such as Appid etc.
    * Clicj Load button, it'll load information to the dialo.
    * configure：

            AppId=       
            AppToken=    
            UID=         
            ChannelName= 
            RtmpUrl=     
    
    
* Get Channel InformationMode

    * Input Information Manually
    
         fill information manually 
    * Get Infomation by http get request
     
          When user click, "Start Streaming to Agora",it'll call http request.
          Customer need build a http server for http request. User input a http url, then http server 
          response json string including channel information. Json format：

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

    Agora appid. After register agora account, you can create project, then it'll generate an appid.

* initialize

  Initialize agora rtc engine. If user wants to set playback device before Start Streaming to Agora, Initialize first.
  
*  AppToken  

   Calculate token by appid, app certificate, channel Name and Uid.   
 

* Channel Name 

     Join Channel need channel Name.

* Uid

      user id.


* camera uid
    
    If only send obs camera video, you need to set an camera user id. 
* camera token  

    a token for camera user id
* send camera vieo

    If check this, it'll send obs camera video alone, beside send the whole obs video.If audience run app backend, app need to show video on a samll window.
    
    Audience app can decide to show camera video or main video depending that app run backend or not.    

* CPU Threshold

    If cpu reach the threshold value multiple times in two minutes, obs will show a information dialog to tell user need close some unused windows application.   
 
* Audio and Video log interval

     Log obs push audio and video time in this inverval.    

* Mute all remote audio and video

    If broadcaster doesn't want to receive audio and video from remote user. Check this check box.

* Save all Setings except APPID, including audio video and rtmp settings

       When close obs, it'll save basic informations except APPID and load information automatically when start obs next time.      

* Dual Stream

      Send high and low obs video stream.
* Persist Save APPID

      Save appid locally permanetly, not suggested. 
 


## Audio

* Sample Rate

    Unused, use 48kHz.
* Channels

    For audio profile parameter, need to use with high quality. For example: if select stereo, it'll setAudioProfile parameter:     

        AUDIO_PROFILE_MUSIC_STANDARD_STEREO or AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO

    If set mono, it'll set:

        AUDIO_PROFILE_MUSIC_STANDARD or AUDIO_PROFILE_MUSIC_HIGH_QUALITY

* Audio Scenario

     Audio Profile

* High Quality

     If check this, Audio Profile will be

        AUDIO_PROFILE_MUSIC_HIGH_QUALITY or AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO

* Save OBS PCM Data

     Save pcm file in obs log folder.

**Note**

    If you need to know more about audio profile parameter, you can reference setAudioProfile paramter on agora.io  


 * Playout Device Settings

       You need click Initialize button, when start plugin first time. Or you can Start Streaming to Agora, you can set play device and adjust playback device volume. 

* loopback

     Agora sdk capture playback device. If check this, obs desktop audio need to mute.   

## Video

  video encoder configuraion

*  First Output Bitrate

    * Use Agora Bitrate

          Agora SDK will calculate video bitrate.
    * Use OBS Bitrate

         Use bitrate in obs setting dialog.
* Second Output Bitrate

   
    Reference VideoEncoderConfiguration on agora.io：

        COMPATIBLE_BITRATE
        STANDARD_BITRATE
        DEFAULT_MIN_BITRATE

* Camera Encoder Resolution

    In General, only valid when check Send Obs Camera Video. You can set camera VideoEncoderConfiguration dimension.

* Camera Encoder Bitrate
    
       In General, only valid when check Send Obs Camera Video.You can set camera VideoEncoderConfiguration Bitrate.

*Camera Encoder FPS

       In General, only valid when check Send Obs Camera Video.You can set camera VideoEncoderConfiguration frameRate.


## Agora Rtmp

  SetLiveTranscoding Parameter
  
* Url 

   Agora rtmp url, addPublishStreamUrl.
   
* FPS

    rtmp FPS

* width and height

    rtmp width and height

## Network Test

  
* Start Network Test

    Network Test before joinchannel, you'll get network test result. Need Initlize first.  

    Stop Network Test before start Streaming.
