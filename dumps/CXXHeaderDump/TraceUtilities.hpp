#ifndef UE4SS_SDK_TraceUtilities_HPP
#define UE4SS_SDK_TraceUtilities_HPP

class UTraceUtilLibrary : public UBlueprintFunctionLibrary
{

    void TraceMarkRegionStart(FString Name);
    void TraceMarkRegionEnd(FString Name);
    void TraceBookmark(FString Name);
    void ToggleChannel(FString ChannelName, bool Enabled);
    void StopTracing();
    void StartTraceToFile(FString Filename, const TArray<FString>& Channels);
    void StartTraceSendTo(FString Target, const TArray<FString>& Channels);
    void ResumeTracing();
    void PauseTracing();
    void IsTracing();
    void IsChannelEnabled(FString ChannelName);
    void GetEnabledChannels();
    void GetAllChannels();
}; // Size: 0x28

#endif
