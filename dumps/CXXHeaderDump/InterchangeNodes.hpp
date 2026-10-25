#ifndef UE4SS_SDK_InterchangeNodes_HPP
#define UE4SS_SDK_InterchangeNodes_HPP

#include "InterchangeNodes_enums.hpp"

struct FInterchangeAnimationPayLoadKey
{
    FString UniqueID;                                                                 // 0x0000 (size: 0x10)
    EInterchangeAnimationPayLoadType Type;                                            // 0x0010 (size: 0x1)

}; // Size: 0x18

struct FInterchangeMeshPayLoadKey
{
    FString UniqueID;                                                                 // 0x0000 (size: 0x10)
    EInterchangeMeshPayLoadType Type;                                                 // 0x0010 (size: 0x1)

}; // Size: 0x18

class UInterchangeAnimationTrackBaseNode : public UInterchangeBaseNode
{

    void SetCustomCompletionMode(const int32& AttributeValue);
    void GetCustomCompletionMode(int32& AttributeValue);
}; // Size: 0x70

class UInterchangeAnimationTrackNode : public UInterchangeAnimationTrackBaseNode
{

    void SetCustomTargetedProperty(const int32& TargetedProperty);
    void SetCustomFrameCount(const int32& AttributeValue);
    void SetCustomAnimationPayloadKey(FString InUniqueId, const EInterchangeAnimationPayLoadType& InType);
    void SetCustomActorDependencyUid(FString DependencyUid);
    void GetCustomTargetedProperty(int32& TargetedProperty);
    void GetCustomFrameCount(int32& AttributeValue);
    void GetCustomAnimationPayloadKey(FInterchangeAnimationPayLoadKey& AnimationPayLoadKey);
    void GetCustomActorDependencyUid(FString& DependencyUid);
}; // Size: 0xC0

class UInterchangeAnimationTrackSetInstanceNode : public UInterchangeAnimationTrackBaseNode
{

    void SetCustomTrackSetDependencyUid(FString AttributeValue);
    void SetCustomTimeScale(const float& AttributeValue);
    void SetCustomStartFrame(const int32& AttributeValue);
    void SetCustomDuration(const int32& AttributeValue);
    void GetCustomTrackSetDependencyUid(FString& AttributeValue);
    void GetCustomTimeScale(float& AttributeValue);
    void GetCustomStartFrame(int32& AttributeValue);
    void GetCustomDuration(int32& AttributeValue);
}; // Size: 0xB0

class UInterchangeAnimationTrackSetNode : public UInterchangeBaseNode
{

    void SetCustomFrameRate(const float& AttributeValue);
    void RemoveCustomAnimationTrackUid(FString AnimationTrackUid);
    void GetCustomFrameRate(float& AttributeValue);
    void GetCustomAnimationTrackUids(TArray<FString>& OutAnimationTrackUids);
    void GetCustomAnimationTrackUidCount();
    void GetCustomAnimationTrackUid(const int32 Index, FString& OutAnimationTrackUid);
    void AddCustomAnimationTrackUid(FString AnimationTrackUid);
}; // Size: 0x90

class UInterchangeBaseLightNode : public UInterchangeBaseNode
{

    void SetCustomUseTemperature(bool AttributeValue);
    void SetCustomTemperature(float AttributeValue);
    void SetCustomLightColor(const FLinearColor& AttributeValue);
    void SetCustomIntensity(float AttributeValue);
    void GetCustomUseTemperature(bool& AttributeValue);
    void GetCustomTemperature(float& AttributeValue);
    void GetCustomLightColor(FLinearColor& AttributeValue);
    void GetCustomIntensity(float& AttributeValue);
}; // Size: 0xA0

class UInterchangeDirectionalLightNode : public UInterchangeBaseLightNode
{
}; // Size: 0xA0

class UInterchangeFunctionCallShaderNode : public UInterchangeShaderNode
{

    void SetCustomMaterialFunction(FString AttributeValue);
    void GetCustomMaterialFunction(FString& AttributeValue);
}; // Size: 0x80

class UInterchangeLightNode : public UInterchangeBaseLightNode
{

    void SetCustomIntensityUnits(const EInterchangeLightUnits& AttributeValue);
    void SetCustomIESTexture(FString AttributeValue);
    void SetCustomAttenuationRadius(float AttributeValue);
    void GetCustomIntensityUnits(EInterchangeLightUnits& AttributeValue);
    void GetCustomIESTexture(FString& AttributeValue);
    void GetCustomAttenuationRadius(float& AttributeValue);
}; // Size: 0xD0

class UInterchangeMaterialInstanceNode : public UInterchangeBaseNode
{

    void SetCustomParent(FString AttributeValue);
    void GetVectorParameterValue(FString ParameterName, FLinearColor& AttributeValue);
    void GetTextureParameterValue(FString ParameterName, FString& AttributeValue);
    void GetStaticSwitchParameterValue(FString ParameterName, bool& AttributeValue);
    void GetScalarParameterValue(FString ParameterName, float& AttributeValue);
    void GetCustomParent(FString& AttributeValue);
    void AddVectorParameterValue(FString ParameterName, const FLinearColor& AttributeValue);
    void AddTextureParameterValue(FString ParameterName, FString AttributeValue);
    void AddStaticSwitchParameterValue(FString ParameterName, bool AttributeValue);
    void AddScalarParameterValue(FString ParameterName, float AttributeValue);
}; // Size: 0x70

class UInterchangeMeshNode : public UInterchangeBaseNode
{

    void SetSlotMaterialDependencyUid(FString SlotName, FString MaterialDependencyUid);
    void SetSkinnedMesh(const bool bIsSkinnedMesh);
    void SetSkeletonDependencyUid(FString DependencyUid);
    void SetSceneInstanceUid(FString DependencyUid);
    void SetPayLoadKey(FString PayloadKey, const EInterchangeMeshPayLoadType& PayLoadType);
    void SetMorphTargetName(FString MorphTargetName);
    void SetMorphTargetDependencyUid(FString DependencyUid);
    void SetMorphTarget(const bool bIsMorphTarget);
    void SetCustomVertexCount(const int32& AttributeValue);
    void SetCustomUVCount(const int32& AttributeValue);
    void SetCustomPolygonCount(const int32& AttributeValue);
    void SetCustomHasVertexTangent(const bool& AttributeValue);
    void SetCustomHasVertexNormal(const bool& AttributeValue);
    void SetCustomHasVertexColor(const bool& AttributeValue);
    void SetCustomHasVertexBinormal(const bool& AttributeValue);
    void SetCustomHasSmoothGroup(const bool& AttributeValue);
    void SetCustomBoundingBox(const FBox& AttributeValue);
    void RemoveSlotMaterialDependencyUid(FString SlotName);
    void RemoveSkeletonDependencyUid(FString DependencyUid);
    void RemoveSceneInstanceUid(FString DependencyUid);
    void RemoveMorphTargetDependencyUid(FString DependencyUid);
    void IsSkinnedMesh();
    void IsMorphTarget();
    void GetSlotMaterialDependencyUid(FString SlotName, FString& OutMaterialDependency);
    void GetSlotMaterialDependencies(TMap<FString, FString>& OutMaterialDependencies);
    void GetSkeletonDependency(const int32 Index, FString& OutDependency);
    void GetSkeletonDependencies(TArray<FString>& OutDependencies);
    void GetSkeletonDependeciesCount();
    void GetSceneInstanceUidsCount();
    void GetSceneInstanceUids(TArray<FString>& OutDependencies);
    void GetSceneInstanceUid(const int32 Index, FString& OutDependency);
    void GetMorphTargetName(FString& OutMorphTargetName);
    void GetMorphTargetDependency(const int32 Index, FString& OutDependency);
    void GetMorphTargetDependencies(TArray<FString>& OutDependencies);
    void GetMorphTargetDependeciesCount();
    void GetCustomVertexCount(int32& AttributeValue);
    void GetCustomUVCount(int32& AttributeValue);
    void GetCustomPolygonCount(int32& AttributeValue);
    void GetCustomHasVertexTangent(bool& AttributeValue);
    void GetCustomHasVertexNormal(bool& AttributeValue);
    void GetCustomHasVertexColor(bool& AttributeValue);
    void GetCustomHasVertexBinormal(bool& AttributeValue);
    void GetCustomHasSmoothGroup(bool& AttributeValue);
    void GetCustomBoundingBox(FBox& AttributeValue);
}; // Size: 0x1E8

class UInterchangePhysicalCameraNode : public UInterchangeBaseNode
{

    void SetCustomSensorWidth(const float& AttributeValue);
    void SetCustomSensorHeight(const float& AttributeValue);
    void SetCustomFocalLength(const float& AttributeValue);
    void SetCustomEnableDepthOfField(const bool& AttributeValue);
    void GetCustomSensorWidth(float& AttributeValue);
    void GetCustomSensorHeight(float& AttributeValue);
    void GetCustomFocalLength(float& AttributeValue);
    void GetCustomEnableDepthOfField(bool& AttributeValue);
}; // Size: 0xA0

class UInterchangePointLightNode : public UInterchangeLightNode
{

    void SetCustomUseInverseSquaredFalloff(bool AttributeValue);
    void SetCustomLightFalloffExponent(float AttributeValue);
    void GetCustomUseInverseSquaredFalloff(bool& AttributeValue);
    void GetCustomLightFalloffExponent(float& AttributeValue);
}; // Size: 0xF0

class UInterchangeRectLightNode : public UInterchangeLightNode
{

    void SetCustomSourceWidth(float AttributeValue);
    void SetCustomSourceHeight(float AttributeValue);
    void GetCustomSourceWidth(float& AttributeValue);
    void GetCustomSourceHeight(float& AttributeValue);
}; // Size: 0xF0

class UInterchangeSceneNode : public UInterchangeBaseNode
{

    void SetSlotMaterialDependencyUid(FString SlotName, FString MaterialDependencyUid);
    void SetMorphTargetCurveWeight(FString MorphTargetName, const float& Weight);
    void SetCustomTimeZeroLocalTransform(const class UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue, bool bResetCache);
    void SetCustomLocalTransform(const class UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue, bool bResetCache);
    void SetCustomGeometricTransform(const FTransform& AttributeValue);
    void SetCustomBindPoseLocalTransform(const class UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& AttributeValue, bool bResetCache);
    void SetCustomAssetInstanceUid(FString AttributeValue);
    void SetCustomAnimationAssetUidToPlay(FString AttributeValue);
    void RemoveSpecializedType(FString SpecializedType);
    void RemoveSlotMaterialDependencyUid(FString SlotName);
    void IsSpecializedTypeContains(FString SpecializedType);
    void GetSpecializedTypes(TArray<FString>& OutSpecializedTypes);
    void GetSpecializedTypeCount();
    void GetSpecializedType(const int32 Index, FString& OutSpecializedType);
    void GetSlotMaterialDependencyUid(FString SlotName, FString& OutMaterialDependency);
    void GetSlotMaterialDependencies(TMap<FString, FString>& OutMaterialDependencies);
    void GetMorphTargetCurveWeights(TMap<FString, float>& OutMorphTargetCurveWeights);
    void GetCustomTimeZeroLocalTransform(FTransform& AttributeValue);
    void GetCustomTimeZeroGlobalTransform(const class UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue, bool bForceRecache);
    void GetCustomLocalTransform(FTransform& AttributeValue);
    void GetCustomGlobalTransform(const class UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue, bool bForceRecache);
    void GetCustomGeometricTransform(FTransform& AttributeValue);
    void GetCustomBindPoseLocalTransform(FTransform& AttributeValue);
    void GetCustomBindPoseGlobalTransform(const class UInterchangeBaseNodeContainer* BaseNodeContainer, const FTransform& GlobalOffsetTransform, FTransform& AttributeValue, bool bForceRecache);
    void GetCustomAssetInstanceUid(FString& AttributeValue);
    void GetCustomAnimationAssetUidToPlay(FString& AttributeValue);
    void AddSpecializedType(FString SpecializedType);
}; // Size: 0x320

class UInterchangeSceneVariantSetsNode : public UInterchangeBaseNode
{

    void RemoveCustomVariantSetUid(FString VariantUid);
    void GetCustomVariantSetUids(TArray<FString>& OutVariantUids);
    void GetCustomVariantSetUidCount();
    void GetCustomVariantSetUid(const int32 Index, FString& OutVariantUid);
    void AddCustomVariantSetUid(FString VariantUid);
}; // Size: 0x80

class UInterchangeShaderGraphNode : public UInterchangeShaderNode
{

    void SetCustomTwoSidedTransmission(const bool& AttributeValue);
    void SetCustomTwoSided(const bool& AttributeValue);
    void SetCustomScreenSpaceReflections(const bool& AttributeValue);
    void SetCustomOpacityMaskClipValue(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomIsAShaderFunction(const bool& AttributeValue);
    void GetCustomTwoSidedTransmission(bool& AttributeValue);
    void GetCustomTwoSided(bool& AttributeValue);
    void GetCustomScreenSpaceReflections(bool& AttributeValue);
    void GetCustomOpacityMaskClipValue(float& AttributeValue);
    void GetCustomIsAShaderFunction(bool& AttributeValue);
}; // Size: 0xC0

class UInterchangeShaderNode : public UInterchangeBaseNode
{

    void SetCustomShaderType(FString AttributeValue);
    void GetCustomShaderType(FString& AttributeValue);
}; // Size: 0x70

class UInterchangeShaderPortsAPI : public UObject
{

    void MakeInputValueKey(FString InputName);
    void MakeInputName(FString InputKey);
    void MakeInputConnectionKey(FString InputName);
    void IsAnInput(FString AttributeKey);
    void HasInput(const class UInterchangeBaseNode* InterchangeNode, const FName& InInputName);
    void GetInputConnection(const class UInterchangeBaseNode* InterchangeNode, FString InputName, FString& OutExpressionUid, FString& OutputName);
    void GatherInputs(const class UInterchangeBaseNode* InterchangeNode, TArray<FString>& OutInputNames);
    void ConnectOuputToInputByName(class UInterchangeBaseNode* InterchangeNode, FString InputName, FString ExpressionUid, FString OutputName);
    void ConnectOuputToInputByIndex(class UInterchangeBaseNode* InterchangeNode, FString InputName, FString ExpressionUid, int32 OutputIndex);
    void ConnectDefaultOuputToInput(class UInterchangeBaseNode* InterchangeNode, FString InputName, FString ExpressionUid);
}; // Size: 0x28

class UInterchangeSkeletalAnimationTrackNode : public UInterchangeAnimationTrackBaseNode
{

    void SetCustomSkeletonNodeUid(FString AttributeValue);
    void SetCustomAnimationStopTime(const double& StopTime);
    void SetCustomAnimationStartTime(const double& StartTime);
    void SetCustomAnimationSampleRate(const double& SampleRate);
    void SetAnimationPayloadKeyForSceneNodeUid(FString SceneNodeUid, FString InUniqueId, const EInterchangeAnimationPayLoadType& InType);
    void SetAnimationPayloadKeyForMorphTargetNodeUid(FString MorphTargetNodeUid, FString InUniqueId, const EInterchangeAnimationPayLoadType& InType);
    void GetSceneNodeAnimationPayloadKeys(TMap<FString, FString>& OutSceneNodeAnimationPayloadKeyUids, TMap<FString, uint8>& OutSceneNodeAnimationPayloadKeyTypes);
    void GetMorphTargetNodeAnimationPayloadKeys(TMap<FString, FString>& OutMorphTargetNodeAnimationPayloadKeyUids, TMap<FString, uint8>& OutMorphTargetNodeAnimationPayloadKeyTypes);
    void GetCustomSkeletonNodeUid(FString& AttributeValue);
    void GetCustomAnimationStopTime(double& StopTime);
    void GetCustomAnimationStartTime(double& StartTime);
    void GetCustomAnimationSampleRate(double& SampleRate);
}; // Size: 0x290

class UInterchangeSpotLightNode : public UInterchangePointLightNode
{

    void SetCustomOuterConeAngle(float AttributeValue);
    void SetCustomInnerConeAngle(float AttributeValue);
    void GetCustomOuterConeAngle(float& AttributeValue);
    void GetCustomInnerConeAngle(float& AttributeValue);
}; // Size: 0x110

class UInterchangeStandardCameraNode : public UInterchangeBaseNode
{

    void SetCustomWidth(const float& AttributeValue);
    void SetCustomProjectionMode(const EInterchangeCameraProjectionType& AttributeValue);
    void SetCustomNearClipPlane(const float& AttributeValue);
    void SetCustomFieldOfView(const float& AttributeValue);
    void SetCustomFarClipPlane(const float& AttributeValue);
    void SetCustomAspectRatio(const float& AttributeValue);
    void GetCustomWidth(float& AttributeValue);
    void GetCustomProjectionMode(EInterchangeCameraProjectionType& AttributeValue);
    void GetCustomNearClipPlane(float& AttributeValue);
    void GetCustomFieldOfView(float& AttributeValue);
    void GetCustomFarClipPlane(float& AttributeValue);
    void GetCustomAspectRatio(float& AttributeValue);
}; // Size: 0xC0

class UInterchangeTexture2DArrayNode : public UInterchangeTextureNode
{
}; // Size: 0x90

class UInterchangeTexture2DNode : public UInterchangeTextureNode
{

    void SetCustomWrapV(const EInterchangeTextureWrapMode& AttributeValue);
    void SetCustomWrapU(const EInterchangeTextureWrapMode& AttributeValue);
    void GetSourceBlocks();
    void GetCustomWrapV(EInterchangeTextureWrapMode& AttributeValue);
    void GetCustomWrapU(EInterchangeTextureWrapMode& AttributeValue);
}; // Size: 0x128

class UInterchangeTextureBlurNode : public UInterchangeTexture2DNode
{
}; // Size: 0x128

class UInterchangeTextureCubeArrayNode : public UInterchangeTextureNode
{
}; // Size: 0x90

class UInterchangeTextureCubeNode : public UInterchangeTextureNode
{
}; // Size: 0x90

class UInterchangeTextureLightProfileNode : public UInterchangeTextureNode
{
}; // Size: 0x90

class UInterchangeTextureNode : public UInterchangeBaseNode
{

    void SetPayLoadKey(FString PayloadKey);
    void SetCustomSRGB(const bool& AttributeValue);
    void SetCustomFilter(const EInterchangeTextureFilterMode& AttributeValue);
    void SetCustombFlipGreenChannel(const bool& AttributeValue);
    void GetCustomSRGB(bool& AttributeValue);
    void GetCustomFilter(EInterchangeTextureFilterMode& AttributeValue);
    void GetCustombFlipGreenChannel(bool& AttributeValue);
}; // Size: 0x90

class UInterchangeTransformAnimationTrackNode : public UInterchangeAnimationTrackNode
{

    void SetCustomUsedChannels(const int32& AttributeValue);
    void GetCustomUsedChannels(int32& AttributeValue);
}; // Size: 0xD0

class UInterchangeVariantSetNode : public UInterchangeBaseNode
{

    void SetCustomVariantsPayloadKey(FString PayloadKey);
    void SetCustomDisplayText(FString AttributeValue);
    void RemoveCustomDependencyUid(FString DependencyUid);
    void GetCustomVariantsPayloadKey(FString& PayloadKey);
    void GetCustomDisplayText(FString& AttributeValue);
    void GetCustomDependencyUids(TArray<FString>& OutDependencyUids);
    void GetCustomDependencyUidCount();
    void GetCustomDependencyUid(const int32 Index, FString& OutDependencyUid);
    void AddCustomDependencyUid(FString DependencyUid);
}; // Size: 0xA0

class UInterchangeVolumeTextureNode : public UInterchangeTextureNode
{
}; // Size: 0x90

#endif
