#ifndef UE4SS_SDK_MediaAssets_HPP
#define UE4SS_SDK_MediaAssets_HPP

#include "MediaAssets_enums.hpp"

struct FMediaCaptureDevice
{
    FText DisplayName;                                                                // 0x0000 (size: 0x18)
    FString URL;                                                                      // 0x0018 (size: 0x10)

}; // Size: 0x28

struct FMediaMetadataItemBPT
{
    FString LanguageCode;                                                             // 0x0000 (size: 0x10)
    FString MimeType;                                                                 // 0x0010 (size: 0x10)
    FString StringData;                                                               // 0x0020 (size: 0x10)
    TArray<uint8> BinaryData;                                                         // 0x0030 (size: 0x10)

}; // Size: 0x40

struct FMediaMetadataItemsBPT
{
    TArray<FMediaMetadataItemBPT> Items;                                              // 0x0000 (size: 0x10)

}; // Size: 0x10

struct FMediaSoundComponentSpectralData
{
    float FrequencyHz;                                                                // 0x0000 (size: 0x4)
    float Magnitude;                                                                  // 0x0004 (size: 0x4)

}; // Size: 0x8

struct FMediaSourceCacheSettings
{
    bool bOverride;                                                                   // 0x0000 (size: 0x1)
    float TimeToLookAhead;                                                            // 0x0004 (size: 0x4)

}; // Size: 0x8

class IMediaPlayerProxyInterface : public IInterface
{
}; // Size: 0x28

class IMediaSourceRendererInterface : public IInterface
{
}; // Size: 0x28

class UBaseMediaSource : public UMediaSource
{
    FName PlayerName;                                                                 // 0x0080 (size: 0x8)

}; // Size: 0x88

class UFileMediaSource : public UBaseMediaSource
{
    FString FilePath;                                                                 // 0x0088 (size: 0x10)
    bool PrecacheFile;                                                                // 0x0098 (size: 0x1)

    void SetFilePath(FString Path);
}; // Size: 0xB0

class UMediaBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{

    void EnumerateWebcamCaptureDevices(TArray<FMediaCaptureDevice>& OutDevices, int32 Filter);
    void EnumerateVideoCaptureDevices(TArray<FMediaCaptureDevice>& OutDevices, int32 Filter);
    void EnumerateAudioCaptureDevices(TArray<FMediaCaptureDevice>& OutDevices, int32 Filter);
}; // Size: 0x28

class UMediaComponent : public UActorComponent
{
    class UMediaTexture* MediaTexture;                                                // 0x00A0 (size: 0x8)
    class UMediaPlayer* MediaPlayer;                                                  // 0x00A8 (size: 0x8)

    void GetMediaTexture();
    void GetMediaPlayer();
}; // Size: 0xB0

class UMediaPlayer : public UObject
{
    FMediaPlayerOnEndReached OnEndReached;                                            // 0x0030 (size: 0x10)
    void OnMediaPlayerMediaEvent();
    FMediaPlayerOnMediaClosed OnMediaClosed;                                          // 0x0040 (size: 0x10)
    void OnMediaPlayerMediaEvent();
    FMediaPlayerOnMediaOpened OnMediaOpened;                                          // 0x0050 (size: 0x10)
    void OnMediaPlayerMediaOpened(FString OpenedUrl);
    FMediaPlayerOnMediaOpenFailed OnMediaOpenFailed;                                  // 0x0060 (size: 0x10)
    void OnMediaPlayerMediaOpenFailed(FString FailedUrl);
    FMediaPlayerOnPlaybackResumed OnPlaybackResumed;                                  // 0x0070 (size: 0x10)
    void OnMediaPlayerMediaEvent();
    FMediaPlayerOnPlaybackSuspended OnPlaybackSuspended;                              // 0x0080 (size: 0x10)
    void OnMediaPlayerMediaEvent();
    FMediaPlayerOnSeekCompleted OnSeekCompleted;                                      // 0x0090 (size: 0x10)
    void OnMediaPlayerMediaEvent();
    FMediaPlayerOnTracksChanged OnTracksChanged;                                      // 0x00A0 (size: 0x10)
    void OnMediaPlayerMediaEvent();
    FMediaPlayerOnMetadataChanged OnMetadataChanged;                                  // 0x00B0 (size: 0x10)
    void OnMediaPlayerMediaEvent();
    FTimespan CacheAhead;                                                             // 0x00C0 (size: 0x8)
    FTimespan CacheBehind;                                                            // 0x00C8 (size: 0x8)
    FTimespan CacheBehindGame;                                                        // 0x00D0 (size: 0x8)
    bool NativeAudioOut;                                                              // 0x00D8 (size: 0x1)
    bool PlayOnOpen;                                                                  // 0x00D9 (size: 0x1)
    uint8 Shuffle;                                                                    // 0x00DC (size: 0x1)
    uint8 Loop;                                                                       // 0x00DC (size: 0x1)
    class UMediaPlaylist* Playlist;                                                   // 0x00E0 (size: 0x8)
    int32 PlaylistIndex;                                                              // 0x00E8 (size: 0x4)
    FTimespan TimeDelay;                                                              // 0x00F0 (size: 0x8)
    float HorizontalFieldOfView;                                                      // 0x00F8 (size: 0x4)
    float VerticalFieldOfView;                                                        // 0x00FC (size: 0x4)
    FRotator ViewRotation;                                                            // 0x0100 (size: 0x18)
    FGuid PlayerGuid;                                                                 // 0x0140 (size: 0x10)

    void SupportsSeeking();
    void SupportsScrubbing();
    void SupportsRate(float Rate, bool Unthinned);
    void SetViewRotation(const FRotator& Rotation, bool Absolute);
    void SetViewField(float Horizontal, float Vertical, bool Absolute);
    void SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate);
    void SetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex, int32 FormatIndex);
    void SetTimeDelay(FTimespan TimeDelay);
    void SetRate(float Rate);
    void SetNativeVolume(float Volume);
    void SetMediaOptions(const class UMediaSource* Options);
    void SetLooping(bool Looping);
    void SetDesiredPlayerName(FName PlayerName);
    void SetBlockOnTime(const FTimespan& Time);
    void SelectTrack(EMediaPlayerTrack TrackType, int32 TrackIndex);
    void Seek(const FTimespan& Time);
    void Rewind();
    void Reopen();
    void Previous();
    void PlayAndSeek();
    void Play();
    void Pause();
    void OpenUrl(FString URL);
    void OpenSourceWithOptions(class UMediaSource* MediaSource, const FMediaPlayerOptions& Options);
    void OpenSourceLatent(const class UObject* WorldContextObject, FLatentActionInfo LatentInfo, class UMediaSource* MediaSource, const FMediaPlayerOptions& Options, bool& bSuccess);
    void OpenSource(class UMediaSource* MediaSource);
    void OpenPlaylistIndex(class UMediaPlaylist* InPlaylist, int32 Index);
    void OpenPlaylist(class UMediaPlaylist* InPlaylist);
    void OpenFile(FString FilePath);
    void Next();
    void IsReady();
    void IsPreparing();
    void IsPlaying();
    void IsPaused();
    void IsLooping();
    void IsConnecting();
    void IsClosed();
    void IsBuffering();
    void HasError();
    void GetViewRotation();
    void GetVideoTrackType(int32 TrackIndex, int32 FormatIndex);
    void GetVideoTrackFrameRates(int32 TrackIndex, int32 FormatIndex);
    void GetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex);
    void GetVideoTrackDimensions(int32 TrackIndex, int32 FormatIndex);
    void GetVideoTrackAspectRatio(int32 TrackIndex, int32 FormatIndex);
    void GetVerticalFieldOfView();
    void GetUrl();
    void GetTrackLanguage(EMediaPlayerTrack TrackType, int32 TrackIndex);
    void GetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex);
    void GetTrackDisplayName(EMediaPlayerTrack TrackType, int32 TrackIndex);
    void GetTimeStamp();
    void GetTimeDelay();
    void GetTime();
    void GetSupportedRates(TArray<FFloatRange>& OutRates, bool Unthinned);
    void GetSelectedTrack(EMediaPlayerTrack TrackType);
    void GetRate();
    void GetPlaylistIndex();
    void GetPlaylist();
    void GetPlayerName();
    void GetNumTracks(EMediaPlayerTrack TrackType);
    void GetNumTrackFormats(EMediaPlayerTrack TrackType, int32 TrackIndex);
    void GetMediaName();
    void GetMediaMetadataItems();
    void GetHorizontalFieldOfView();
    void GetDuration();
    void GetDisplayTimeStamp();
    void GetDisplayTime();
    void GetDesiredPlayerName();
    void GetAudioTrackType(int32 TrackIndex, int32 FormatIndex);
    void GetAudioTrackSampleRate(int32 TrackIndex, int32 FormatIndex);
    void GetAudioTrackChannels(int32 TrackIndex, int32 FormatIndex);
    void Close();
    void CanPlayUrl(FString URL);
    void CanPlaySource(class UMediaSource* MediaSource);
    void CanPause();
}; // Size: 0x168

class UMediaPlaylist : public UObject
{
    TArray<UMediaSource*> Items;                                                      // 0x0028 (size: 0x10)

    void Replace(int32 Index, class UMediaSource* Replacement);
    void RemoveAt(int32 Index);
    void Remove(class UMediaSource* MediaSource);
    void Num();
    void Insert(class UMediaSource* MediaSource, int32 Index);
    void GetRandom(int32& OutIndex);
    void GetPrevious(int32& InOutIndex);
    void GetNext(int32& InOutIndex);
    void Get(int32 Index);
    void AddUrl(FString URL);
    void AddFile(FString FilePath);
    void Add(class UMediaSource* MediaSource);
}; // Size: 0x38

class UMediaSoundComponent : public USynthComponent
{
    EMediaSoundChannels Channels;                                                     // 0x0900 (size: 0x4)
    bool DynamicRateAdjustment;                                                       // 0x0904 (size: 0x1)
    float RateAdjustmentFactor;                                                       // 0x0908 (size: 0x4)
    FFloatRange RateAdjustmentRange;                                                  // 0x090C (size: 0x10)
    class UMediaPlayer* MediaPlayer;                                                  // 0x0920 (size: 0x8)

    void SetSpectralAnalysisSettings(TArray<float> InFrequenciesToAnalyze, EMediaSoundComponentFFTSize InFFTSize);
    void SetMediaPlayer(class UMediaPlayer* NewMediaPlayer);
    void SetEnvelopeFollowingsettings(int32 AttackTimeMsec, int32 ReleaseTimeMsec);
    void SetEnableSpectralAnalysis(bool bInSpectralAnalysisEnabled);
    void SetEnableEnvelopeFollowing(bool bInEnvelopeFollowing);
    void GetSpectralData();
    void GetNormalizedSpectralData();
    void GetMediaPlayer();
    void GetEnvelopeValue();
    void BP_GetAttenuationSettingsToApply(FSoundAttenuationSettings& OutAttenuationSettings);
}; // Size: 0x9E0

class UMediaSource : public UObject
{

    void Validate();
    void SetMediaOptionString(const FName& Key, FString Value);
    void SetMediaOptionInt64(const FName& Key, int64 Value);
    void SetMediaOptionFloat(const FName& Key, float Value);
    void SetMediaOptionBool(const FName& Key, bool Value);
    void GetUrl();
}; // Size: 0x80

class UMediaTexture : public UTexture
{
    TEnumAsByte<TextureAddress> AddressX;                                             // 0x01C8 (size: 0x1)
    TEnumAsByte<TextureAddress> AddressY;                                             // 0x01C9 (size: 0x1)
    bool AutoClear;                                                                   // 0x01CA (size: 0x1)
    FLinearColor ClearColor;                                                          // 0x01CC (size: 0x10)
    bool EnableGenMips;                                                               // 0x01DC (size: 0x1)
    uint8 NumMips;                                                                    // 0x01DD (size: 0x1)
    bool NewStyleOutput;                                                              // 0x01DE (size: 0x1)
    TEnumAsByte<MediaTextureOutputFormat> OutputFormat;                               // 0x01DF (size: 0x1)
    float CurrentAspectRatio;                                                         // 0x01E0 (size: 0x4)
    TEnumAsByte<MediaTextureOrientation> CurrentOrientation;                          // 0x01E4 (size: 0x1)
    class UMediaPlayer* MediaPlayer;                                                  // 0x01E8 (size: 0x8)

    void UpdateResource();
    void SetMediaPlayer(class UMediaPlayer* NewMediaPlayer);
    void GetWidth();
    void GetTextureNumMips();
    void GetMediaPlayer();
    void GetHeight();
    void GetAspectRatio();
}; // Size: 0x2B0

class UMediaTimeStampInfo : public UObject
{
    FTimespan Time;                                                                   // 0x0028 (size: 0x8)
    int64 SequenceIndex;                                                              // 0x0030 (size: 0x8)

}; // Size: 0x38

class UPlatformMediaSource : public UMediaSource
{
    class UMediaSource* MediaSource;                                                  // 0x0080 (size: 0x8)

}; // Size: 0x88

class UStreamMediaSource : public UBaseMediaSource
{
    FString StreamUrl;                                                                // 0x0088 (size: 0x10)

}; // Size: 0x98

class UTimeSynchronizableMediaSource : public UBaseMediaSource
{
    bool bUseTimeSynchronization;                                                     // 0x0088 (size: 0x1)
    int32 FrameDelay;                                                                 // 0x008C (size: 0x4)
    double TimeDelay;                                                                 // 0x0090 (size: 0x8)
    bool bAutoDetectInput;                                                            // 0x0098 (size: 0x1)

}; // Size: 0xA0

#endif
