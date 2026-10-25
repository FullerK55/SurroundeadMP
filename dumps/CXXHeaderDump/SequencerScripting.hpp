#ifndef UE4SS_SDK_SequencerScripting_HPP
#define UE4SS_SDK_SequencerScripting_HPP

#include "SequencerScripting_enums.hpp"

struct FSequencerScriptingRange
{
    uint8 bHasStart;                                                                  // 0x0000 (size: 0x1)
    uint8 bHasEnd;                                                                    // 0x0000 (size: 0x1)
    int32 InclusiveStart;                                                             // 0x0004 (size: 0x4)
    int32 ExclusiveEnd;                                                               // 0x0008 (size: 0x4)
    FFrameRate InternalRate;                                                          // 0x000C (size: 0x8)

}; // Size: 0x14

class UMovieSceneBindingExtensions : public UBlueprintFunctionLibrary
{

    void SetSpawnableBindingID(const FMovieSceneBindingProxy& InBinding, const FMovieSceneObjectBindingID& SpawnableBindingID);
    void SetSortingOrder(const FMovieSceneBindingProxy& InBinding, int32 SortingOrder);
    void SetParent(const FMovieSceneBindingProxy& InBinding, const FMovieSceneBindingProxy& InParentBinding);
    void SetName(const FMovieSceneBindingProxy& InBinding, FString InName);
    void SetDisplayName(const FMovieSceneBindingProxy& InBinding, const FText& InDisplayName);
    void RemoveTrack(const FMovieSceneBindingProxy& InBinding, class UMovieSceneTrack* TrackToRemove);
    void Remove(const FMovieSceneBindingProxy& InBinding);
    void MoveBindingContents(const FMovieSceneBindingProxy& SourceBindingId, const FMovieSceneBindingProxy& DestinationBindingId);
    void IsValid(const FMovieSceneBindingProxy& InBinding);
    void GetTracks(const FMovieSceneBindingProxy& InBinding);
    void GetSortingOrder(const FMovieSceneBindingProxy& InBinding);
    void GetPossessedObjectClass(const FMovieSceneBindingProxy& InBinding);
    void GetParent(const FMovieSceneBindingProxy& InBinding);
    void GetObjectTemplate(const FMovieSceneBindingProxy& InBinding);
    void GetName(const FMovieSceneBindingProxy& InBinding);
    void GetId(const FMovieSceneBindingProxy& InBinding);
    void GetDisplayName(const FMovieSceneBindingProxy& InBinding);
    void GetChildPossessables(const FMovieSceneBindingProxy& InBinding);
    void FindTracksByType(const FMovieSceneBindingProxy& InBinding, TSubclassOf<class UMovieSceneTrack> TrackType);
    void FindTracksByExactType(const FMovieSceneBindingProxy& InBinding, TSubclassOf<class UMovieSceneTrack> TrackType);
    void AddTrack(const FMovieSceneBindingProxy& InBinding, TSubclassOf<class UMovieSceneTrack> TrackType);
}; // Size: 0x28

class UMovieSceneDoubleVectorTrackExtensions : public UBlueprintFunctionLibrary
{

    void SetNumChannelsUsed(class UMovieSceneDoubleVectorTrack* Track, int32 InNumChannelsUsed);
    void GetNumChannelsUsed(class UMovieSceneDoubleVectorTrack* Track);
}; // Size: 0x28

class UMovieSceneEventTrackExtensions : public UBlueprintFunctionLibrary
{

    void GetBoundObjectPropertyClass(const FMovieSceneEvent& EventKey);
    void AddEventTriggerSection(class UMovieSceneEventTrack* InTrack);
    void AddEventRepeaterSection(class UMovieSceneEventTrack* InTrack);
}; // Size: 0x28

class UMovieSceneFloatVectorTrackExtensions : public UBlueprintFunctionLibrary
{

    void SetNumChannelsUsed(class UMovieSceneFloatVectorTrack* Track, int32 InNumChannelsUsed);
    void GetNumChannelsUsed(class UMovieSceneFloatVectorTrack* Track);
}; // Size: 0x28

class UMovieSceneFolderExtensions : public UBlueprintFunctionLibrary
{

    void SetFolderName(class UMovieSceneFolder* Folder, FName InFolderName);
    void SetFolderColor(class UMovieSceneFolder* Folder, FColor InFolderColor);
    void RemoveChildTrack(class UMovieSceneFolder* Folder, class UMovieSceneTrack* InTrack);
    void RemoveChildObjectBinding(class UMovieSceneFolder* Folder, const FMovieSceneBindingProxy InObjectBinding);
    void RemoveChildMasterTrack(class UMovieSceneFolder* Folder, class UMovieSceneTrack* InTrack);
    void RemoveChildFolder(class UMovieSceneFolder* TargetFolder, class UMovieSceneFolder* FolderToRemove);
    void GetFolderName(class UMovieSceneFolder* Folder);
    void GetFolderColor(class UMovieSceneFolder* Folder);
    void GetChildTracks(class UMovieSceneFolder* Folder);
    void GetChildObjectBindings(class UMovieSceneFolder* Folder);
    void GetChildMasterTracks(class UMovieSceneFolder* Folder);
    void GetChildFolders(class UMovieSceneFolder* Folder);
    void AddChildTrack(class UMovieSceneFolder* Folder, class UMovieSceneTrack* InTrack);
    void AddChildObjectBinding(class UMovieSceneFolder* Folder, FMovieSceneBindingProxy InObjectBinding);
    void AddChildMasterTrack(class UMovieSceneFolder* Folder, class UMovieSceneTrack* InTrack);
    void AddChildFolder(class UMovieSceneFolder* TargetFolder, class UMovieSceneFolder* FolderToAdd);
}; // Size: 0x28

class UMovieSceneMaterialTrackExtensions : public UBlueprintFunctionLibrary
{

    void SetMaterialIndex(class UMovieSceneComponentMaterialTrack* Track, const int32 MaterialIndex);
    void GetMaterialIndex(class UMovieSceneComponentMaterialTrack* Track);
}; // Size: 0x28

class UMovieScenePrimitiveMaterialTrackExtensions : public UBlueprintFunctionLibrary
{

    void SetMaterialIndex(class UMovieScenePrimitiveMaterialTrack* Track, const int32 MaterialIndex);
    void GetMaterialIndex(class UMovieScenePrimitiveMaterialTrack* Track);
}; // Size: 0x28

class UMovieScenePropertyTrackExtensions : public UBlueprintFunctionLibrary
{

    void SetPropertyNameAndPath(class UMovieScenePropertyTrack* Track, const FName& InPropertyName, FString InPropertyPath);
    void SetObjectPropertyClass(class UMovieSceneObjectPropertyTrack* Track, UClass* PropertyClass);
    void SetByteTrackEnum(class UMovieSceneByteTrack* Track, class UEnum* InEnum);
    void GetUniqueTrackName(class UMovieScenePropertyTrack* Track);
    void GetPropertyPath(class UMovieScenePropertyTrack* Track);
    void GetPropertyName(class UMovieScenePropertyTrack* Track);
    void GetObjectPropertyClass(class UMovieSceneObjectPropertyTrack* Track);
    void GetByteTrackEnum(class UMovieSceneByteTrack* Track);
}; // Size: 0x28

class UMovieSceneScriptingActorReferenceChannel : public UMovieSceneScriptingChannel
{

    void SetDefault(FMovieSceneObjectBindingID InDefaultValue);
    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void RemoveDefault();
    void HasDefault();
    void GetKeys();
    void GetDefault();
    void AddKey(const FFrameNumber InTime, FMovieSceneObjectBindingID NewValue, float SubFrame, ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingActorReferenceKey : public UMovieSceneScriptingKey
{

    void SetValue(const FMovieSceneObjectBindingID& InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingActualFloatKey : public UMovieSceneScriptingFloatKey
{
}; // Size: 0x60

class UMovieSceneScriptingBoolChannel : public UMovieSceneScriptingChannel
{

    void SetDefault(bool InDefaultValue);
    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void RemoveDefault();
    void HasDefault();
    void GetNumKeys();
    void GetKeys();
    void GetDefault();
    void EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate);
    void ComputeEffectiveRange();
    void AddKey(const FFrameNumber& InTime, bool NewValue, float SubFrame, ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingBoolKey : public UMovieSceneScriptingKey
{

    void SetValue(bool InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingByteChannel : public UMovieSceneScriptingChannel
{

    void SetDefault(uint8 InDefaultValue);
    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void RemoveDefault();
    void HasDefault();
    void GetKeys();
    void GetDefault();
    void AddKey(const FFrameNumber& InTime, uint8 NewValue, float SubFrame, ESequenceTimeUnit TimeUnit, EMovieSceneKeyInterpolation InInterpolation);
}; // Size: 0x60

class UMovieSceneScriptingByteKey : public UMovieSceneScriptingKey
{

    void SetValue(uint8 InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingChannel : public UObject
{
    FName ChannelName;                                                                // 0x0028 (size: 0x8)

}; // Size: 0x30

class UMovieSceneScriptingDoubleAsFloatKey : public UMovieSceneScriptingFloatKey
{
}; // Size: 0x60

class UMovieSceneScriptingDoubleChannel : public UMovieSceneScriptingChannel
{

    void SetPreInfinityExtrapolation(TEnumAsByte<ERichCurveExtrapolation> InExtrapolation);
    void SetPostInfinityExtrapolation(TEnumAsByte<ERichCurveExtrapolation> InExtrapolation);
    void SetDefault(double InDefaultValue);
    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void RemoveDefault();
    void HasDefault();
    void GetPreInfinityExtrapolation();
    void GetPostInfinityExtrapolation();
    void GetNumKeys();
    void GetKeys();
    void GetDefault();
    void EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate);
    void ComputeEffectiveRange();
    void AddKey(const FFrameNumber& InTime, double NewValue, float SubFrame, ESequenceTimeUnit TimeUnit, EMovieSceneKeyInterpolation InInterpolation);
}; // Size: 0x60

class UMovieSceneScriptingDoubleKey : public UMovieSceneScriptingKey
{

    void SetValue(double InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void SetTangentWeightMode(TEnumAsByte<ERichCurveTangentWeightMode> InNewValue);
    void SetTangentMode(TEnumAsByte<ERichCurveTangentMode> InNewValue);
    void SetLeaveTangentWeight(float InNewValue);
    void SetLeaveTangent(float InNewValue);
    void SetInterpolationMode(TEnumAsByte<ERichCurveInterpMode> InNewValue);
    void SetArriveTangentWeight(float InNewValue);
    void SetArriveTangent(float InNewValue);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
    void GetTangentWeightMode();
    void GetTangentMode();
    void GetLeaveTangentWeight();
    void GetLeaveTangent();
    void GetInterpolationMode();
    void GetArriveTangentWeight();
    void GetArriveTangent();
}; // Size: 0x60

class UMovieSceneScriptingEventChannel : public UMovieSceneScriptingChannel
{

    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void GetKeys();
    void AddKey(const FFrameNumber& InTime, FMovieSceneEvent NewValue, float SubFrame, ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingEventKey : public UMovieSceneScriptingKey
{

    void SetValue(const FMovieSceneEvent& InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingFloatChannel : public UMovieSceneScriptingChannel
{

    void SetPreInfinityExtrapolation(TEnumAsByte<ERichCurveExtrapolation> InExtrapolation);
    void SetPostInfinityExtrapolation(TEnumAsByte<ERichCurveExtrapolation> InExtrapolation);
    void SetDefault(float InDefaultValue);
    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void RemoveDefault();
    void HasDefault();
    void GetPreInfinityExtrapolation();
    void GetPostInfinityExtrapolation();
    void GetNumKeys();
    void GetKeys();
    void GetDefault();
    void EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate);
    void ComputeEffectiveRange();
    void AddKey(const FFrameNumber& InTime, float NewValue, float SubFrame, ESequenceTimeUnit TimeUnit, EMovieSceneKeyInterpolation InInterpolation);
}; // Size: 0x80

class UMovieSceneScriptingFloatKey : public UMovieSceneScriptingKey
{

    void SetValue(float InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void SetTangentWeightMode(TEnumAsByte<ERichCurveTangentWeightMode> InNewValue);
    void SetTangentMode(TEnumAsByte<ERichCurveTangentMode> InNewValue);
    void SetLeaveTangentWeight(float InNewValue);
    void SetLeaveTangent(float InNewValue);
    void SetInterpolationMode(TEnumAsByte<ERichCurveInterpMode> InNewValue);
    void SetArriveTangentWeight(float InNewValue);
    void SetArriveTangent(float InNewValue);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
    void GetTangentWeightMode();
    void GetTangentMode();
    void GetLeaveTangentWeight();
    void GetLeaveTangent();
    void GetInterpolationMode();
    void GetArriveTangentWeight();
    void GetArriveTangent();
}; // Size: 0x40

class UMovieSceneScriptingIntegerChannel : public UMovieSceneScriptingChannel
{

    void SetDefault(int32 InDefaultValue);
    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void RemoveDefault();
    void HasDefault();
    void GetKeys();
    void GetDefault();
    void AddKey(const FFrameNumber& InTime, int32 NewValue, float SubFrame, ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingIntegerKey : public UMovieSceneScriptingKey
{

    void SetValue(int32 InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingKey : public UObject
{
}; // Size: 0x40

class UMovieSceneScriptingObjectPathChannel : public UMovieSceneScriptingChannel
{

    void SetDefault(class UObject* InDefaultValue);
    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void RemoveDefault();
    void HasDefault();
    void GetKeys();
    void GetDefault();
    void AddKey(const FFrameNumber InTime, class UObject* NewValue, float SubFrame, ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingObjectPathKey : public UMovieSceneScriptingKey
{

    void SetValue(class UObject* InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingStringChannel : public UMovieSceneScriptingChannel
{

    void SetDefault(FString InDefaultValue);
    void RemoveKey(class UMovieSceneScriptingKey* Key);
    void RemoveDefault();
    void HasDefault();
    void GetKeys();
    void GetDefault();
    void AddKey(const FFrameNumber& InTime, FString NewValue, float SubFrame, ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneScriptingStringKey : public UMovieSceneScriptingKey
{

    void SetValue(FString InNewValue);
    void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame, ESequenceTimeUnit TimeUnit);
    void GetValue();
    void GetTime(ESequenceTimeUnit TimeUnit);
}; // Size: 0x60

class UMovieSceneSectionExtensions : public UBlueprintFunctionLibrary
{

    void SetStartFrameSeconds(class UMovieSceneSection* Section, float StartTime);
    void SetStartFrameBounded(class UMovieSceneSection* Section, bool bIsBounded);
    void SetStartFrame(class UMovieSceneSection* Section, int32 StartFrame);
    void SetRangeSeconds(class UMovieSceneSection* Section, float StartTime, float EndTime);
    void SetRange(class UMovieSceneSection* Section, int32 StartFrame, int32 EndFrame);
    void SetEndFrameSeconds(class UMovieSceneSection* Section, float EndTime);
    void SetEndFrameBounded(class UMovieSceneSection* Section, bool bIsBounded);
    void SetEndFrame(class UMovieSceneSection* Section, int32 EndFrame);
    void HasStartFrame(class UMovieSceneSection* Section);
    void HasEndFrame(class UMovieSceneSection* Section);
    void GetStartFrameSeconds(class UMovieSceneSection* Section);
    void GetStartFrame(class UMovieSceneSection* Section);
    void GetParentSequenceFrame(class UMovieSceneSubSection* Section, int32 InFrame, class UMovieSceneSequence* ParentSequence);
    void GetEndFrameSeconds(class UMovieSceneSection* Section);
    void GetEndFrame(class UMovieSceneSection* Section);
    void GetChannelsByType(class UMovieSceneSection* Section, TSubclassOf<class UMovieSceneScriptingChannel> ChannelType);
    void GetAutoSizeStartFrameSeconds(class UMovieSceneSection* Section);
    void GetAutoSizeStartFrame(class UMovieSceneSection* Section);
    void GetAutoSizeHasStartFrame(class UMovieSceneSection* Section);
    void GetAutoSizeHasEndFrame(class UMovieSceneSection* Section);
    void GetAutoSizeEndFrameSeconds(class UMovieSceneSection* Section);
    void GetAutoSizeEndFrame(class UMovieSceneSection* Section);
    void GetAllChannels(class UMovieSceneSection* Section);
}; // Size: 0x28

class UMovieSceneSequenceExtensions : public UBlueprintFunctionLibrary
{

    void SortMarkedFrames(class UMovieSceneSequence* Sequence);
    void SetWorkRangeStart(class UMovieSceneSequence* InSequence, float StartTimeInSeconds);
    void SetWorkRangeEnd(class UMovieSceneSequence* InSequence, float EndTimeInSeconds);
    void SetViewRangeStart(class UMovieSceneSequence* InSequence, float StartTimeInSeconds);
    void SetViewRangeEnd(class UMovieSceneSequence* InSequence, float EndTimeInSeconds);
    void SetTickResolutionDirectly(class UMovieSceneSequence* Sequence, FFrameRate TickResolution);
    void SetTickResolution(class UMovieSceneSequence* Sequence, FFrameRate TickResolution);
    void SetReadOnly(class UMovieSceneSequence* Sequence, bool bInReadOnly);
    void SetPlaybackStartSeconds(class UMovieSceneSequence* Sequence, float StartTime);
    void SetPlaybackStart(class UMovieSceneSequence* Sequence, int32 StartFrame);
    void SetPlaybackRangeLocked(class UMovieSceneSequence* Sequence, bool bInLocked);
    void SetPlaybackEndSeconds(class UMovieSceneSequence* Sequence, float EndTime);
    void SetPlaybackEnd(class UMovieSceneSequence* Sequence, int32 EndFrame);
    void SetMarkedFramesLocked(class UMovieSceneSequence* Sequence, bool bInLocked);
    void SetMarkedFrame(class UMovieSceneSequence* Sequence, int32 InMarkIndex, FFrameNumber InFrameNumber);
    void SetEvaluationType(class UMovieSceneSequence* InSequence, EMovieSceneEvaluationType InEvaluationType);
    void SetDisplayRate(class UMovieSceneSequence* Sequence, FFrameRate DisplayRate);
    void SetClockSource(class UMovieSceneSequence* InSequence, EUpdateClockSource InClockSource);
    void ResolveBindingID(class UMovieSceneSequence* RootSequence, FMovieSceneObjectBindingID InObjectBindingID);
    void RemoveTrack(class UMovieSceneSequence* Sequence, class UMovieSceneTrack* Track);
    void RemoveRootFolderFromSequence(class UMovieSceneSequence* Sequence, class UMovieSceneFolder* Folder);
    void RemoveMasterTrack(class UMovieSceneSequence* Sequence, class UMovieSceneTrack* Track);
    void MakeRangeSeconds(class UMovieSceneSequence* Sequence, float StartTime, float Duration);
    void MakeRange(class UMovieSceneSequence* Sequence, int32 StartFrame, int32 Duration);
    void LocateBoundObjects(class UMovieSceneSequence* Sequence, const FMovieSceneBindingProxy& InBinding, class UObject* Context);
    void IsReadOnly(class UMovieSceneSequence* Sequence);
    void IsPlaybackRangeLocked(class UMovieSceneSequence* Sequence);
    void GetWorkRangeStart(class UMovieSceneSequence* InSequence);
    void GetWorkRangeEnd(class UMovieSceneSequence* InSequence);
    void GetViewRangeStart(class UMovieSceneSequence* InSequence);
    void GetViewRangeEnd(class UMovieSceneSequence* InSequence);
    void GetTracks(class UMovieSceneSequence* Sequence);
    void GetTickResolution(class UMovieSceneSequence* Sequence);
    void GetSpawnables(class UMovieSceneSequence* Sequence);
    void GetRootFoldersInSequence(class UMovieSceneSequence* Sequence);
    void GetPossessables(class UMovieSceneSequence* Sequence);
    void GetPortableBindingID(class UMovieSceneSequence* RootSequence, class UMovieSceneSequence* DestinationSequence, const FMovieSceneBindingProxy& InBinding);
    void GetPlaybackStartSeconds(class UMovieSceneSequence* Sequence);
    void GetPlaybackStart(class UMovieSceneSequence* Sequence);
    void GetPlaybackRange(class UMovieSceneSequence* Sequence);
    void GetPlaybackEndSeconds(class UMovieSceneSequence* Sequence);
    void GetPlaybackEnd(class UMovieSceneSequence* Sequence);
    void GetMovieScene(class UMovieSceneSequence* Sequence);
    void GetMasterTracks(class UMovieSceneSequence* Sequence);
    void GetMarkedFrames(class UMovieSceneSequence* Sequence);
    void GetEvaluationType(class UMovieSceneSequence* InSequence);
    void GetDisplayRate(class UMovieSceneSequence* Sequence);
    void GetClockSource(class UMovieSceneSequence* InSequence);
    void GetBindings(class UMovieSceneSequence* Sequence);
    void GetBindingID(class UMovieSceneSequence* Sequence, const FMovieSceneBindingProxy& InBinding);
    void FindTracksByType(class UMovieSceneSequence* Sequence, TSubclassOf<class UMovieSceneTrack> TrackType);
    void FindTracksByExactType(class UMovieSceneSequence* Sequence, TSubclassOf<class UMovieSceneTrack> TrackType);
    void FindNextMarkedFrame(class UMovieSceneSequence* Sequence, FFrameNumber InFrameNumber, bool bForward);
    void FindMasterTracksByType(class UMovieSceneSequence* Sequence, TSubclassOf<class UMovieSceneTrack> TrackType);
    void FindMasterTracksByExactType(class UMovieSceneSequence* Sequence, TSubclassOf<class UMovieSceneTrack> TrackType);
    void FindMarkedFrameByLabel(class UMovieSceneSequence* Sequence, FString InLabel);
    void FindMarkedFrameByFrameNumber(class UMovieSceneSequence* Sequence, FFrameNumber InFrameNumber);
    void FindBindingByName(class UMovieSceneSequence* Sequence, FString Name);
    void FindBindingById(class UMovieSceneSequence* Sequence, FGuid BindingID);
    void DeleteMarkedFrames(class UMovieSceneSequence* Sequence);
    void DeleteMarkedFrame(class UMovieSceneSequence* Sequence, int32 DeleteIndex);
    void AreMarkedFramesLocked(class UMovieSceneSequence* Sequence);
    void AddTrack(class UMovieSceneSequence* Sequence, TSubclassOf<class UMovieSceneTrack> TrackType);
    void AddSpawnableFromInstance(class UMovieSceneSequence* Sequence, class UObject* ObjectToSpawn);
    void AddSpawnableFromClass(class UMovieSceneSequence* Sequence, UClass* ClassToSpawn);
    void AddRootFolderToSequence(class UMovieSceneSequence* Sequence, FString NewFolderName);
    void AddPossessable(class UMovieSceneSequence* Sequence, class UObject* ObjectToPossess);
    void AddMasterTrack(class UMovieSceneSequence* Sequence, TSubclassOf<class UMovieSceneTrack> TrackType);
    void AddMarkedFrame(class UMovieSceneSequence* Sequence, const FMovieSceneMarkedFrame& InMarkedFrame);
}; // Size: 0x28

class UMovieSceneTrackExtensions : public UBlueprintFunctionLibrary
{

    void SetTrackRowDisplayName(class UMovieSceneTrack* Track, const FText& InName, int32 RowIndex);
    void SetSortingOrder(class UMovieSceneTrack* Track, int32 SortingOrder);
    void SetSectionToKey(class UMovieSceneTrack* Track, class UMovieSceneSection* Section);
    void SetDisplayName(class UMovieSceneTrack* Track, const FText& InName);
    void SetColorTint(class UMovieSceneTrack* Track, const FColor& ColorTint);
    void RemoveSection(class UMovieSceneTrack* Track, class UMovieSceneSection* Section);
    void GetTrackRowDisplayName(class UMovieSceneTrack* Track, int32 RowIndex);
    void GetSortingOrder(class UMovieSceneTrack* Track);
    void GetSectionToKey(class UMovieSceneTrack* Track);
    void GetSections(class UMovieSceneTrack* Track);
    void GetDisplayName(class UMovieSceneTrack* Track);
    void GetColorTint(class UMovieSceneTrack* Track);
    void AddSection(class UMovieSceneTrack* Track);
}; // Size: 0x28

class USequencerScriptingRangeExtensions : public UBlueprintFunctionLibrary
{

    void SetStartSeconds(FSequencerScriptingRange& Range, float Start);
    void SetStartFrame(FSequencerScriptingRange& Range, int32 Start);
    void SetEndSeconds(FSequencerScriptingRange& Range, float End);
    void SetEndFrame(FSequencerScriptingRange& Range, int32 End);
    void RemoveStart(FSequencerScriptingRange& Range);
    void RemoveEnd(FSequencerScriptingRange& Range);
    void HasStart(const FSequencerScriptingRange& Range);
    void HasEnd(const FSequencerScriptingRange& Range);
    void GetStartSeconds(const FSequencerScriptingRange& Range);
    void GetStartFrame(const FSequencerScriptingRange& Range);
    void GetEndSeconds(const FSequencerScriptingRange& Range);
    void GetEndFrame(const FSequencerScriptingRange& Range);
}; // Size: 0x28

#endif
