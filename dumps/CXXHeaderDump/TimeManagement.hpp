#ifndef UE4SS_SDK_TimeManagement_HPP
#define UE4SS_SDK_TimeManagement_HPP

#include "TimeManagement_enums.hpp"

struct FTimedDataChannelSampleTime
{
}; // Size: 0x18

struct FTimedDataInputEvaluationData
{
    float DistanceToNewestSampleSeconds;                                              // 0x0000 (size: 0x4)
    float DistanceToOldestSampleSeconds;                                              // 0x0004 (size: 0x4)

}; // Size: 0x8

class UFixedFrameRateCustomTimeStep : public UEngineCustomTimeStep
{
}; // Size: 0x28

class UGenlockedCustomTimeStep : public UFixedFrameRateCustomTimeStep
{
    bool bAutoDetectFormat;                                                           // 0x0028 (size: 0x1)

}; // Size: 0x30

class UGenlockedFixedRateCustomTimeStep : public UGenlockedCustomTimeStep
{
    FFrameRate FrameRate;                                                             // 0x0030 (size: 0x8)
    bool bShouldBlock;                                                                // 0x0038 (size: 0x1)
    bool bForceSingleFrameDeltaTime;                                                  // 0x0039 (size: 0x1)

}; // Size: 0x50

class UGenlockedTimecodeProvider : public UTimecodeProvider
{
    bool bUseGenlockToCount;                                                          // 0x0030 (size: 0x1)

}; // Size: 0x58

class UTimeManagementBlueprintLibrary : public UBlueprintFunctionLibrary
{

    void TransformTime(const FFrameTime& SourceTime, const FFrameRate& SourceRate, const FFrameRate& DestinationRate);
    void Subtract_FrameNumberInteger(FFrameNumber A, int32 B);
    void Subtract_FrameNumberFrameNumber(FFrameNumber A, FFrameNumber B);
    void SnapFrameTimeToRate(const FFrameTime& SourceTime, const FFrameRate& SourceRate, const FFrameRate& SnapToRate);
    void Multiply_SecondsFrameRate(float TimeInSeconds, const FFrameRate& FrameRate);
    void Multiply_FrameNumberInteger(FFrameNumber A, int32 B);
    void IsValid_MultipleOf(const FFrameRate& InFrameRate, const FFrameRate& OtherFramerate);
    void IsValid_Framerate(const FFrameRate& InFrameRate);
    void GetTimecodeFrameRate();
    void GetTimecode();
    void Divide_FrameNumberInteger(FFrameNumber A, int32 B);
    void Conv_TimecodeToString(const FTimecode& InTimecode, bool bForceSignDisplay);
    void Conv_QualifiedFrameTimeToSeconds(const FQualifiedFrameTime& InFrameTime);
    void Conv_FrameRateToSeconds(const FFrameRate& InFrameRate);
    void Conv_FrameRateToInterval(const FFrameRate InFrameRate);
    void Conv_FrameNumberToInteger(const FFrameNumber& InFrameNumber);
    void Add_FrameNumberInteger(FFrameNumber A, int32 B);
    void Add_FrameNumberFrameNumber(FFrameNumber A, FFrameNumber B);
}; // Size: 0x28

class UTimeSynchronizationSource : public UObject
{
    bool bUseForSynchronization;                                                      // 0x0028 (size: 0x1)
    int32 FrameOffset;                                                                // 0x002C (size: 0x4)

}; // Size: 0x30

#endif
