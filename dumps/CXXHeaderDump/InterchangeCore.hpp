#ifndef UE4SS_SDK_InterchangeCore_HPP
#define UE4SS_SDK_InterchangeCore_HPP

#include "InterchangeCore_enums.hpp"

struct FInterchangePipelinePropertyStatePerContext
{
    bool bVisible;                                                                    // 0x0000 (size: 0x1)

}; // Size: 0x1

struct FInterchangePipelinePropertyStates
{
    bool bLocked;                                                                     // 0x0000 (size: 0x1)
    FInterchangePipelinePropertyStatePerContext ImportStates;                         // 0x0001 (size: 0x1)
    FInterchangePipelinePropertyStatePerContext ReimportStates;                       // 0x0002 (size: 0x1)

}; // Size: 0x3

struct FInterchangeUserDefinedAttributeInfo
{
    FString Name;                                                                     // 0x0000 (size: 0x10)

}; // Size: 0x30

class UInterchangeBaseNode : public UObject
{

    void SetParentUid(FString ParentUid);
    void SetEnabled(const bool bIsEnabled);
    void SetDisplayLabel(FString DisplayName);
    void SetAssetName(FString AssetName);
    void RemoveTargetNodeUid(FString AssetUid);
    void RemoveAttribute(FString NodeAttributeKey);
    void IsEnabled();
    void InitializeNode(FString UniqueID, FString DisplayLabel, const EInterchangeNodeContainerType NodeContainerType);
    void GetVector2Attribute(FString NodeAttributeKey, FVector2f& OutValue);
    void GetUniqueID();
    void GetTargetNodeUids(TArray<FString>& OutTargetAssets);
    void GetTargetNodeCount();
    void GetStringAttribute(FString NodeAttributeKey, FString& OutValue);
    void GetParentUid();
    void GetNodeContainerType();
    void GetLinearColorAttribute(FString NodeAttributeKey, FLinearColor& OutValue);
    void GetInt32Attribute(FString NodeAttributeKey, int32& OutValue);
    void GetGuidAttribute(FString NodeAttributeKey, FGuid& OutValue);
    void GetFloatAttribute(FString NodeAttributeKey, float& OutValue);
    void GetDoubleAttribute(FString NodeAttributeKey, double& OutValue);
    void GetDisplayLabel();
    void GetBooleanAttribute(FString NodeAttributeKey, bool& OutValue);
    void GetAssetName();
    void AddVector2Attribute(FString NodeAttributeKey, const FVector2f& Value);
    void AddTargetNodeUid(FString AssetUid);
    void AddStringAttribute(FString NodeAttributeKey, FString Value);
    void AddLinearColorAttribute(FString NodeAttributeKey, const FLinearColor& Value);
    void AddInt32Attribute(FString NodeAttributeKey, const int32& Value);
    void AddGuidAttribute(FString NodeAttributeKey, const FGuid& Value);
    void AddFloatAttribute(FString NodeAttributeKey, const float& Value);
    void AddDoubleAttribute(FString NodeAttributeKey, const double& Value);
    void AddBooleanAttribute(FString NodeAttributeKey, const bool& Value);
}; // Size: 0x60

class UInterchangeBaseNodeContainer : public UObject
{
    TMap<FString, UInterchangeBaseNode*> Nodes;                                       // 0x0028 (size: 0x50)

    void SetNodeParentUid(FString NodeUniqueID, FString NewParentNodeUid);
    void SaveToFile(FString Filename);
    void ResetChildrenCache();
    void ReplaceNode(FString NodeUniqueID, class UInterchangeFactoryBaseNode* NewNode);
    void LoadFromFile(FString Filename);
    void IsNodeUidValid(FString NodeUniqueID);
    void GetRoots(TArray<FString>& RootNodes);
    void GetNodes(const UClass* ClassNode, TArray<FString>& OutNodes);
    void GetNodeChildrenUids(FString NodeUniqueID);
    void GetNodeChildrenCount(FString NodeUniqueID);
    void GetNodeChildren(FString NodeUniqueID, int32 ChildIndex);
    void GetNode(FString NodeUniqueID);
    void GetFactoryNode(FString NodeUniqueID);
    void ComputeChildrenCache();
    void AddNode(class UInterchangeBaseNode* Node);
}; // Size: 0xC8

class UInterchangeFactoryBase : public UObject
{
    class UInterchangeResultsContainer* Results;                                      // 0x0028 (size: 0x8)

    void GetFactoryClass();
}; // Size: 0x30

class UInterchangeFactoryBaseNode : public UInterchangeBaseNode
{

    void UnsetSkipNodeImport();
    void UnsetForceNodeReimport();
    void ShouldSkipNodeImport();
    void ShouldForceNodeReimport();
    void SetSkipNodeImport();
    void SetReimportStrategyFlags(const EReimportStrategyFlags& ReimportStrategyFlags);
    void SetForceNodeReimport();
    void SetCustomSubPath(FString AttributeValue);
    void SetCustomReferenceObject(const FSoftObjectPath& AttributeValue);
    void RemoveFactoryDependencyUid(FString DependencyUid);
    void GetReimportStrategyFlags();
    void GetFactoryDependency(const int32 Index, FString& OutDependency);
    void GetFactoryDependenciesCount();
    void GetFactoryDependencies(TArray<FString>& OutDependencies);
    void GetCustomSubPath(FString& AttributeValue);
    void GetCustomReferenceObject(FSoftObjectPath& AttributeValue);
    void AddFactoryDependencyUid(FString DependencyUid);
}; // Size: 0x140

class UInterchangePipelineBase : public UObject
{
    class UInterchangeResultsContainer* Results;                                      // 0x0030 (size: 0x8)
    TMap<FName, FInterchangePipelinePropertyStates> PropertiesStates;                 // 0x0038 (size: 0x50)

    void ScriptedSetReimportSourceIndex(UClass* ReimportObjectClass, const int32 SourceFileIndex);
    void ScriptedExecutePreImportPipeline(class UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas);
    void ScriptedExecutePostImportPipeline(const class UInterchangeBaseNodeContainer* BaseNodeContainer, FString FactoryNodeKey, class UObject* CreatedAsset, bool bIsAReimport);
    void ScriptedExecutePostFactoryPipeline(const class UInterchangeBaseNodeContainer* BaseNodeContainer, FString FactoryNodeKey, class UObject* CreatedAsset, bool bIsAReimport);
    void ScriptedExecutePipeline(class UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas);
    void ScriptedExecuteExportPipeline(class UInterchangeBaseNodeContainer* BaseNodeContainer);
    void ScriptedCanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask);
    void FindOrAddPropertyStates(const FName PropertyPath);
    void DoesPropertyStatesExist(const FName PropertyPath);
}; // Size: 0xE8

class UInterchangeResult : public UObject
{
    FString SourceAssetName;                                                          // 0x0028 (size: 0x10)
    FString DestinationAssetName;                                                     // 0x0038 (size: 0x10)
    UClass* AssetType;                                                                // 0x0048 (size: 0x8)
    FString InterchangeKey;                                                           // 0x0050 (size: 0x10)

}; // Size: 0x60

class UInterchangeResultDisplay_Generic : public UInterchangeResultSuccess
{
    FText Text;                                                                       // 0x0060 (size: 0x18)

}; // Size: 0x78

class UInterchangeResultError : public UInterchangeResult
{
}; // Size: 0x60

class UInterchangeResultError_Generic : public UInterchangeResultError
{
    FText Text;                                                                       // 0x0060 (size: 0x18)

}; // Size: 0x78

class UInterchangeResultError_ReimportFail : public UInterchangeResultError
{
}; // Size: 0x60

class UInterchangeResultSuccess : public UInterchangeResult
{
}; // Size: 0x60

class UInterchangeResultWarning : public UInterchangeResult
{
}; // Size: 0x60

class UInterchangeResultWarning_Generic : public UInterchangeResultWarning
{
    FText Text;                                                                       // 0x0060 (size: 0x18)

}; // Size: 0x78

class UInterchangeResultsContainer : public UObject
{
    TArray<UInterchangeResult*> Results;                                              // 0x0050 (size: 0x10)

}; // Size: 0x60

class UInterchangeSourceData : public UObject
{
    FString Filename;                                                                 // 0x0028 (size: 0x10)

    void SetFilename(FString InFilename);
    void GetFilename();
}; // Size: 0x50

class UInterchangeSourceNode : public UInterchangeBaseNode
{

    void SetCustomSourceTimelineStart(const double& AttributeValue);
    void SetCustomSourceTimelineEnd(const double& AttributeValue);
    void SetCustomSourceFrameRateNumerator(const int32& AttributeValue);
    void SetCustomSourceFrameRateDenominator(const int32& AttributeValue);
    void SetCustomImportUnusedMaterial(const bool& AttributeValue);
    void SetCustomAnimatedTimeStart(const double& AttributeValue);
    void SetCustomAnimatedTimeEnd(const double& AttributeValue);
    void InitializeSourceNode(FString UniqueID, FString DisplayLabel);
    void GetCustomSourceTimelineStart(double& AttributeValue);
    void GetCustomSourceTimelineEnd(double& AttributeValue);
    void GetCustomSourceFrameRateNumerator(int32& AttributeValue);
    void GetCustomSourceFrameRateDenominator(int32& AttributeValue);
    void GetCustomImportUnusedMaterial(bool& AttributeValue);
    void GetCustomAnimatedTimeStart(double& AttributeValue);
    void GetCustomAnimatedTimeEnd(double& AttributeValue);
}; // Size: 0xD0

class UInterchangeTranslatorBase : public UObject
{
    class UInterchangeResultsContainer* Results;                                      // 0x0028 (size: 0x8)
    class UInterchangeSourceData* SourceData;                                         // 0x0030 (size: 0x8)

}; // Size: 0x38

class UInterchangeUserDefinedAttributesAPI : public UObject
{

    void RemoveUserDefinedAttribute(class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName);
    void GetUserDefinedAttributeInfos(const class UInterchangeBaseNode* InterchangeNode, TArray<FInterchangeUserDefinedAttributeInfo>& UserDefinedAttributeInfos);
    void GetUserDefinedAttribute_Int32(const class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, int32& OutValue, FString& OutPayloadKey);
    void GetUserDefinedAttribute_FString(const class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, FString& OutValue, FString& OutPayloadKey);
    void GetUserDefinedAttribute_Float(const class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, float& OutValue, FString& OutPayloadKey);
    void GetUserDefinedAttribute_Double(const class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, double& OutValue, FString& OutPayloadKey);
    void GetUserDefinedAttribute_Boolean(const class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, bool& OutValue, FString& OutPayloadKey);
    void DuplicateAllUserDefinedAttribute(const class UInterchangeBaseNode* InterchangeSourceNode, class UInterchangeBaseNode* InterchangeDestinationNode, bool bAddSourceNodeName);
    void CreateUserDefinedAttribute_Int32(class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, const int32& Value, FString PayloadKey);
    void CreateUserDefinedAttribute_FString(class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, FString Value, FString PayloadKey);
    void CreateUserDefinedAttribute_Float(class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, const float& Value, FString PayloadKey);
    void CreateUserDefinedAttribute_Double(class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, const double& Value, FString PayloadKey);
    void CreateUserDefinedAttribute_Boolean(class UInterchangeBaseNode* InterchangeNode, FString UserDefinedAttributeName, const bool& Value, FString PayloadKey);
}; // Size: 0x28

class UInterchangeWriterBase : public UObject
{
}; // Size: 0x28

#endif
