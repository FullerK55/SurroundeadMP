#ifndef UE4SS_SDK_MetasoundEngine_HPP
#define UE4SS_SDK_MetasoundEngine_HPP

#include "MetasoundEngine_enums.hpp"

struct FDefaultMetaSoundAssetAutoUpdateSettings
{
    FSoftObjectPath Metasound;                                                        // 0x0000 (size: 0x20)

}; // Size: 0x20

struct FMetaSoundAssetDirectory
{
    FDirectoryPath Directory;                                                         // 0x0000 (size: 0x10)

}; // Size: 0x10

struct FMetaSoundAsyncAssetDependencies
{
    class UObject* Metasound;                                                         // 0x0008 (size: 0x8)

}; // Size: 0x30

struct FMetaSoundBuilderNodeInputHandle : public FMetasoundFrontendVertexHandle
{
}; // Size: 0x20

struct FMetaSoundBuilderNodeOutputHandle : public FMetasoundFrontendVertexHandle
{
}; // Size: 0x20

struct FMetaSoundBuilderOptions
{
    FName Name;                                                                       // 0x0000 (size: 0x8)
    bool bForceUniqueClassName;                                                       // 0x0008 (size: 0x1)
    bool bAddToRegistry;                                                              // 0x0009 (size: 0x1)
    TScriptInterface<class IMetaSoundDocumentInterface> ExistingMetaSound;            // 0x0010 (size: 0x10)

}; // Size: 0x20

struct FMetaSoundNodeHandle
{
    FGuid NodeId;                                                                     // 0x0000 (size: 0x10)

}; // Size: 0x10

struct FMetaSoundOutput : public FSoundGeneratorOutput
{
}; // Size: 0x10

class UMetaSoundAssetSubsystem : public UEngineSubsystem
{
    TArray<FMetaSoundAsyncAssetDependencies> LoadingDependencies;                     // 0x0038 (size: 0x10)

    void UnregisterAssetClassesInDirectories(const TArray<FMetaSoundAssetDirectory>& Directories);
    void RegisterAssetClassesInDirectories(const TArray<FMetaSoundAssetDirectory>& Directories);
}; // Size: 0x1E0

class UMetaSoundBuilderBase : public UObject
{
    FMetaSoundFrontendDocumentBuilder Builder;                                        // 0x0028 (size: 0x30)
    bool bIsAttached;                                                                 // 0x0058 (size: 0x1)

    void SetNodeInputDefault(const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);
    void SetGraphInputDefault(FName InputName, const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);
    void RemoveNodeInputDefault(const FMetaSoundBuilderNodeInputHandle& InputHandle, EMetaSoundBuilderResult& OutResult);
    void RemoveNode(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult);
    void RemoveInterface(FName InterfaceName, EMetaSoundBuilderResult& OutResult);
    void RemoveGraphOutput(FName Name, EMetaSoundBuilderResult& OutResult);
    void RemoveGraphInput(FName Name, EMetaSoundBuilderResult& OutResult);
    void NodesAreConnected(const FMetaSoundBuilderNodeOutputHandle& OutputHandle, const FMetaSoundBuilderNodeInputHandle& InputHandle);
    void NodeOutputIsConnected(const FMetaSoundBuilderNodeOutputHandle& OutputHandle);
    void NodeInputIsConnected(const FMetaSoundBuilderNodeInputHandle& InputHandle);
    void IsPreset();
    void InterfaceIsDeclared(FName InterfaceName);
    void GetReferencedPresetAsset();
    void GetNodeOutputData(const FMetaSoundBuilderNodeOutputHandle& OutputHandle, FName& Name, FName& DataType, EMetaSoundBuilderResult& OutResult);
    void GetNodeInputDefault(const FMetaSoundBuilderNodeInputHandle& InputHandle, EMetaSoundBuilderResult& OutResult);
    void GetNodeInputData(const FMetaSoundBuilderNodeInputHandle& InputHandle, FName& Name, FName& DataType, EMetaSoundBuilderResult& OutResult);
    void GetNodeInputClassDefault(const FMetaSoundBuilderNodeInputHandle& InputHandle, EMetaSoundBuilderResult& OutResult);
    void FindNodeOutputsByDataType(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult, FName DataType);
    void FindNodeOutputs(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult);
    void FindNodeOutputParent(const FMetaSoundBuilderNodeOutputHandle& OutputHandle, EMetaSoundBuilderResult& OutResult);
    void FindNodeOutputByName(const FMetaSoundNodeHandle& NodeHandle, FName OutputName, EMetaSoundBuilderResult& OutResult);
    void FindNodeInputsByDataType(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult, FName DataType);
    void FindNodeInputs(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult);
    void FindNodeInputParent(const FMetaSoundBuilderNodeInputHandle& InputHandle, EMetaSoundBuilderResult& OutResult);
    void FindNodeInputByName(const FMetaSoundNodeHandle& NodeHandle, FName InputName, EMetaSoundBuilderResult& OutResult);
    void FindNodeClassVersion(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult);
    void FindInterfaceOutputNodes(FName InterfaceName, EMetaSoundBuilderResult& OutResult);
    void FindInterfaceInputNodes(FName InterfaceName, EMetaSoundBuilderResult& OutResult);
    void FindGraphOutputNode(FName OutputName, EMetaSoundBuilderResult& OutResult);
    void FindGraphInputNode(FName InputName, EMetaSoundBuilderResult& OutResult);
    void DisconnectNodesByInterfaceBindings(const FMetaSoundNodeHandle& FromNodeHandle, const FMetaSoundNodeHandle& ToNodeHandle, EMetaSoundBuilderResult& OutResult);
    void DisconnectNodes(const FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilderResult& OutResult);
    void DisconnectNodeOutput(const FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, EMetaSoundBuilderResult& OutResult);
    void DisconnectNodeInput(const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilderResult& OutResult);
    void ConvertToPreset(const TScriptInterface<class IMetaSoundDocumentInterface>& ReferencedNodeClass, EMetaSoundBuilderResult& OutResult);
    void ConvertFromPreset(EMetaSoundBuilderResult& OutResult);
    void ContainsNodeOutput(const FMetaSoundBuilderNodeOutputHandle& Output);
    void ContainsNodeInput(const FMetaSoundBuilderNodeInputHandle& Input);
    void ContainsNode(const FMetaSoundNodeHandle& Node);
    void ConnectNodesByInterfaceBindings(const FMetaSoundNodeHandle& FromNodeHandle, const FMetaSoundNodeHandle& ToNodeHandle, EMetaSoundBuilderResult& OutResult);
    void ConnectNodes(const FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilderResult& OutResult);
    void ConnectNodeOutputToGraphOutput(FName GraphOutputName, const FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, EMetaSoundBuilderResult& OutResult);
    void ConnectNodeOutputsToMatchingGraphInterfaceOutputs(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult);
    void ConnectNodeInputToGraphInput(FName GraphInputName, const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilderResult& OutResult);
    void ConnectNodeInputsToMatchingGraphInterfaceInputs(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult);
    void AddNodeByClassName(const FMetasoundFrontendClassName& ClassName, int32 MajorVersion, EMetaSoundBuilderResult& OutResult);
    void AddNode(const TScriptInterface<class IMetaSoundDocumentInterface>& NodeClass, EMetaSoundBuilderResult& OutResult);
    void AddInterface(FName InterfaceName, EMetaSoundBuilderResult& OutResult);
    void AddGraphOutputNode(FName Name, FName DataType, FMetasoundFrontendLiteral DefaultValue, EMetaSoundBuilderResult& OutResult, bool bIsConstructorOutput);
    void AddGraphInputNode(FName Name, FName DataType, FMetasoundFrontendLiteral DefaultValue, EMetaSoundBuilderResult& OutResult, bool bIsConstructorInput);
}; // Size: 0x60

class UMetaSoundBuilderSubsystem : public UEngineSubsystem
{
    TMap<FName, UMetaSoundBuilderBase*> NamedBuilders;                                // 0x0038 (size: 0x50)
    TMap<FName, TWeakObjectPtr<class UMetaSoundBuilderBase>> AssetBuilders;           // 0x0088 (size: 0x50)

    void UnregisterSourceBuilder(FName BuilderName);
    void UnregisterPatchBuilder(FName BuilderName);
    void UnregisterBuilder(FName BuilderName);
    void RegisterSourceBuilder(FName BuilderName, class UMetaSoundSourceBuilder* Builder);
    void RegisterPatchBuilder(FName BuilderName, class UMetaSoundPatchBuilder* Builder);
    void RegisterBuilder(FName BuilderName, class UMetaSoundBuilderBase* Builder);
    void IsInterfaceRegistered(FName InInterfaceName);
    void FindSourceBuilder(FName BuilderName);
    void FindPatchBuilder(FName BuilderName);
    void FindBuilder(FName BuilderName);
    void CreateStringMetaSoundLiteral(FString Value, FName& DataType);
    void CreateStringArrayMetaSoundLiteral(const TArray<FString>& Value, FName& DataType);
    void CreateSourcePresetBuilder(FName BuilderName, const TScriptInterface<class IMetaSoundDocumentInterface>& ReferencedSourceClass, EMetaSoundBuilderResult& OutResult);
    void CreateSourceBuilder(FName BuilderName, FMetaSoundBuilderNodeOutputHandle& OnPlayNodeOutput, FMetaSoundBuilderNodeInputHandle& OnFinishedNodeInput, TArray<FMetaSoundBuilderNodeInputHandle>& AudioOutNodeInputs, EMetaSoundBuilderResult& OutResult, EMetaSoundOutputAudioFormat OutputFormat, bool bIsOneShot);
    void CreatePatchPresetBuilder(FName BuilderName, const TScriptInterface<class IMetaSoundDocumentInterface>& ReferencedPatchClass, EMetaSoundBuilderResult& OutResult);
    void CreatePatchBuilder(FName BuilderName, EMetaSoundBuilderResult& OutResult);
    void CreateObjectMetaSoundLiteral(class UObject* Value);
    void CreateObjectArrayMetaSoundLiteral(const TArray<UObject*>& Value);
    void CreateMetaSoundLiteralFromParam(const FAudioParameter& Param);
    void CreateIntMetaSoundLiteral(int32 Value, FName& DataType);
    void CreateIntArrayMetaSoundLiteral(const TArray<int32>& Value, FName& DataType);
    void CreateFloatMetaSoundLiteral(float Value, FName& DataType);
    void CreateFloatArrayMetaSoundLiteral(const TArray<float>& Value, FName& DataType);
    void CreateBoolMetaSoundLiteral(bool Value, FName& DataType);
    void CreateBoolArrayMetaSoundLiteral(const TArray<bool>& Value, FName& DataType);
}; // Size: 0xD8

class UMetaSoundOutputSubsystem : public UTickableWorldSubsystem
{
    TArray<UMetasoundGeneratorHandle*> TrackedGenerators;                             // 0x0040 (size: 0x10)

    void WatchOutput(class UAudioComponent* AudioComponent, FName OutputName, const FWatchOutputOnOutputValueChanged& OnOutputValueChanged, FName AnalyzerName, FName AnalyzerOutputName);
}; // Size: 0x50

class UMetaSoundPatch : public UObject
{
    FMetasoundFrontendDocument RootMetaSoundDocument;                                 // 0x0098 (size: 0x1C8)
    TSet<FString> ReferencedAssetClassKeys;                                           // 0x0260 (size: 0x50)
    TSet<UObject*> ReferencedAssetClassObjects;                                       // 0x02B0 (size: 0x50)
    TSet<FSoftObjectPath> ReferenceAssetClassCache;                                   // 0x0300 (size: 0x50)
    FGuid AssetClassID;                                                               // 0x0350 (size: 0x10)

}; // Size: 0x360

class UMetaSoundPatchBuilder : public UMetaSoundBuilderBase
{

    void Build(class UObject* Parent, const FMetaSoundBuilderOptions& Options);
}; // Size: 0x60

class UMetaSoundSettings : public UDeveloperSettings
{
    bool bAutoUpdateEnabled;                                                          // 0x0038 (size: 0x1)
    TArray<FMetasoundFrontendClassName> AutoUpdateDenylist;                           // 0x0040 (size: 0x10)
    TArray<FDefaultMetaSoundAssetAutoUpdateSettings> AutoUpdateAssetDenylist;         // 0x0050 (size: 0x10)
    bool bAutoUpdateLogWarningOnDroppedConnection;                                    // 0x0060 (size: 0x1)
    TArray<FDirectoryPath> DirectoriesToRegister;                                     // 0x0068 (size: 0x10)
    int32 DenyListCacheChangeID;                                                      // 0x0078 (size: 0x4)

}; // Size: 0x80

class UMetaSoundSource : public USoundWaveProcedural
{
    FMetasoundFrontendDocument RootMetaSoundDocument;                                 // 0x04F0 (size: 0x1C8)
    TSet<FString> ReferencedAssetClassKeys;                                           // 0x06B8 (size: 0x50)
    TSet<UObject*> ReferencedAssetClassObjects;                                       // 0x0708 (size: 0x50)
    TSet<FSoftObjectPath> ReferenceAssetClassCache;                                   // 0x0758 (size: 0x50)
    EMetaSoundOutputAudioFormat OutputFormat;                                         // 0x07A8 (size: 0x1)
    FGuid AssetClassID;                                                               // 0x07AC (size: 0x10)

}; // Size: 0x890

class UMetaSoundSourceBuilder : public UMetaSoundBuilderBase
{

    void SetFormat(EMetaSoundOutputAudioFormat OutputFormat, EMetaSoundBuilderResult& OutResult);
    void GetLiveUpdatesEnabled();
    void Build(class UObject* Parent, const FMetaSoundBuilderOptions& Options);
    void Audition(class UObject* Parent, class UAudioComponent* AudioComponent, FAuditionOnCreateGenerator OnCreateGenerator, bool bLiveUpdatesEnabled);
}; // Size: 0x68

class UMetasoundEditorGraphBase : public UEdGraph
{
}; // Size: 0x60

class UMetasoundGeneratorHandle : public UObject
{

    void WatchOutput(FName OutputName, const FWatchOutputOnOutputValueChanged& OnOutputValueChanged, FName AnalyzerName, FName AnalyzerOutputName);
    void OnOutputValueChangedMulticast__DelegateSignature(FName Name, const FMetaSoundOutput& Output);
    void CreateMetaSoundGeneratorHandle(class UAudioComponent* OnComponent);
    void ApplyParameterPack(class UMetasoundParameterPack* Pack);
}; // Size: 0xE0

class UMetasoundOutputBlueprintAccess : public UBlueprintFunctionLibrary
{

    void IsTime(const FMetaSoundOutput& Output);
    void IsString(const FMetaSoundOutput& Output);
    void IsInt32(const FMetaSoundOutput& Output);
    void IsFloat(const FMetaSoundOutput& Output);
    void IsBool(const FMetaSoundOutput& Output);
    void GetTimeSeconds(const FMetaSoundOutput& Output, bool& Success);
    void GetString(const FMetaSoundOutput& Output, bool& Success);
    void GetInt32(const FMetaSoundOutput& Output, bool& Success);
    void GetFloat(const FMetaSoundOutput& Output, bool& Success);
    void GetBool(const FMetaSoundOutput& Output, bool& Success);
}; // Size: 0x28

#endif
