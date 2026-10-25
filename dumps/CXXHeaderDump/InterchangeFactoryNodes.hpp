#ifndef UE4SS_SDK_InterchangeFactoryNodes_HPP
#define UE4SS_SDK_InterchangeFactoryNodes_HPP

#include "InterchangeFactoryNodes_enums.hpp"

class UInterchangeActorFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetCustomMobility(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomGlobalTransform(const FTransform& AttributeValue, bool bAddApplyDelegate);
    void SetCustomActorClassName(FString AttributeValue);
    void GetCustomMobility(uint8& AttributeValue);
    void GetCustomGlobalTransform(FTransform& AttributeValue);
    void GetCustomActorClassName(FString& AttributeValue);
}; // Size: 0x170

class UInterchangeAnimSequenceFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetCustomSkeletonSoftObjectPath(const FSoftObjectPath& AttributeValue);
    void SetCustomSkeletonFactoryNodeUid(FString AttributeValue);
    void SetCustomRemoveCurveRedundantKeys(const bool& AttributeValue);
    void SetCustomMaterialDriveParameterOnCustomAttribute(const bool& AttributeValue);
    void SetCustomImportBoneTracksSampleRate(const double& AttributeValue);
    void SetCustomImportBoneTracksRangeStop(const double& AttributeValue);
    void SetCustomImportBoneTracksRangeStart(const double& AttributeValue);
    void SetCustomImportBoneTracks(const bool& AttributeValue);
    void SetCustomImportAttributeCurves(const bool& AttributeValue);
    void SetCustomDoNotImportCurveWithZero(const bool& AttributeValue);
    void SetCustomDeleteExistingNonCurveCustomAttributes(const bool& AttributeValue);
    void SetCustomDeleteExistingMorphTargetCurves(const bool& AttributeValue);
    void SetCustomDeleteExistingCustomAttributeCurves(const bool& AttributeValue);
    void SetCustomAddCurveMetadataToSkeleton(const bool& AttributeValue);
    void SetAnimationPayloadKeysForSceneNodeUids(const TMap<FString, FString>& SceneNodeAnimationPayloadKeyUids, const TMap<FString, uint8>& SceneNodeAnimationPayloadKeyTypes);
    void SetAnimationPayloadKeysForMorphTargetNodeUids(const TMap<FString, FString>& MorphTargetAnimationPayloadKeyUids, const TMap<FString, uint8>& MorphTargetAnimationPayloadKeyTypes);
    void SetAnimatedMaterialCurveSuffixe(FString MaterialCurveSuffixe);
    void SetAnimatedAttributeStepCurveName(FString AttributeStepCurveName);
    void SetAnimatedAttributeCurveName(FString AttributeCurveName);
    void RemoveAnimatedMaterialCurveSuffixe(FString MaterialCurveSuffixe);
    void RemoveAnimatedAttributeStepCurveName(FString AttributeStepCurveName);
    void RemoveAnimatedAttributeCurveName(FString AttributeCurveName);
    void InitializeAnimSequenceNode(FString UniqueID, FString DisplayLabel);
    void GetSceneNodeAnimationPayloadKeys(TMap<FString, FInterchangeAnimationPayLoadKey>& OutSceneNodeAnimationPayloadKeys);
    void GetObjectClass();
    void GetMorphTargetNodeAnimationPayloadKeys(TMap<FString, FInterchangeAnimationPayLoadKey>& OutMorphTargetNodeAnimationPayloads);
    void GetCustomSkeletonSoftObjectPath(FSoftObjectPath& AttributeValue);
    void GetCustomSkeletonFactoryNodeUid(FString& AttributeValue);
    void GetCustomRemoveCurveRedundantKeys(bool& AttributeValue);
    void GetCustomMaterialDriveParameterOnCustomAttribute(bool& AttributeValue);
    void GetCustomImportBoneTracksSampleRate(double& AttributeValue);
    void GetCustomImportBoneTracksRangeStop(double& AttributeValue);
    void GetCustomImportBoneTracksRangeStart(double& AttributeValue);
    void GetCustomImportBoneTracks(bool& AttributeValue);
    void GetCustomImportAttributeCurves(bool& AttributeValue);
    void GetCustomDoNotImportCurveWithZero(bool& AttributeValue);
    void GetCustomDeleteExistingNonCurveCustomAttributes(bool& AttributeValue);
    void GetCustomDeleteExistingMorphTargetCurves(bool& AttributeValue);
    void GetCustomDeleteExistingCustomAttributeCurves(bool& AttributeValue);
    void GetCustomAddCurveMetadataToSkeleton(bool& AttributeValue);
    void GetAnimatedMaterialCurveSuffixesCount();
    void GetAnimatedMaterialCurveSuffixes(TArray<FString>& OutMaterialCurveSuffixes);
    void GetAnimatedMaterialCurveSuffixe(const int32 Index, FString& OutMaterialCurveSuffixe);
    void GetAnimatedAttributeStepCurveNamesCount();
    void GetAnimatedAttributeStepCurveNames(TArray<FString>& OutAttributeStepCurveNames);
    void GetAnimatedAttributeStepCurveName(const int32 Index, FString& OutAttributeStepCurveName);
    void GetAnimatedAttributeCurveNamesCount();
    void GetAnimatedAttributeCurveNames(TArray<FString>& OutAttributeCurveNames);
    void GetAnimatedAttributeCurveName(const int32 Index, FString& OutAttributeCurveName);
}; // Size: 0x480

class UInterchangeAnimationTrackSetFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetCustomFrameRate(const float& AttributeValue);
    void RemoveCustomAnimationTrackUid(FString AnimationTrackUid);
    void GetObjectClass();
    void GetCustomFrameRate(float& AttributeValue);
    void GetCustomAnimationTrackUids(TArray<FString>& OutAnimationTrackUids);
    void GetCustomAnimationTrackUidCount();
    void GetCustomAnimationTrackUid(const int32 Index, FString& OutAnimationTrackUid);
    void AddCustomAnimationTrackUid(FString AnimationTrackUid);
}; // Size: 0x170

class UInterchangeBaseLightFactoryNode : public UInterchangeActorFactoryNode
{

    void SetCustomUseTemperature(bool AttributeValue, bool bAddApplyDelegate);
    void SetCustomTemperature(float AttributeValue, bool bAddApplyDelegate);
    void SetCustomLightColor(const FColor& AttributeValue, bool bAddApplyDelegate);
    void SetCustomIntensity(float AttributeValue, bool bAddApplyDelegate);
    void GetCustomUseTemperature(bool& AttributeValue);
    void GetCustomTemperature(float& AttributeValue);
    void GetCustomLightColor(FColor& AttributeValue);
    void GetCustomIntensity(float& AttributeValue);
}; // Size: 0x1B0

class UInterchangeBaseMaterialFactoryNode : public UInterchangeFactoryBaseNode
{
}; // Size: 0x140

class UInterchangeCommonPipelineDataFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetCustomGlobalOffsetTransform(const class UInterchangeBaseNodeContainer* NodeContainer, const FTransform& AttributeValue);
    void SetBakeMeshes(const class UInterchangeBaseNodeContainer* NodeContainer, const bool& AttributeValue);
    void GetCustomGlobalOffsetTransform(FTransform& AttributeValue);
    void GetBakeMeshes(bool& AttributeValue);
}; // Size: 0x160

class UInterchangeDirectionalLightFactoryNode : public UInterchangeBaseLightFactoryNode
{
}; // Size: 0x1B0

class UInterchangeLightFactoryNode : public UInterchangeBaseLightFactoryNode
{

    void SetCustomIntensityUnits(ELightUnits AttributeValue, bool bAddApplyDelegate);
    void SetCustomIESTexture(FString AttributeValue);
    void SetCustomAttenuationRadius(float AttributeValue, bool bAddApplyDelegate);
    void GetCustomIntensityUnits(ELightUnits& AttributeValue);
    void GetCustomIESTexture(FString& AttributeValue);
    void GetCustomAttenuationRadius(float& AttributeValue);
}; // Size: 0x1E0

class UInterchangeMaterialExpressionFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetCustomExpressionClassName(FString AttributeValue);
    void GetCustomExpressionClassName(FString& AttributeValue);
}; // Size: 0x150

class UInterchangeMaterialFactoryNode : public UInterchangeBaseMaterialFactoryNode
{

    void SetCustomTwoSided(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomTranslucencyLightingMode(const TEnumAsByte<ETranslucencyLightingMode>& AttributeValue, bool bAddApplyDelegate);
    void SetCustomShadingModel(const TEnumAsByte<EMaterialShadingModel>& AttributeValue, bool bAddApplyDelegate);
    void SetCustomScreenSpaceReflections(const bool& AttributeValue);
    void SetCustomRefractionMethod(const TEnumAsByte<ERefractionMode>& AttributeValue, bool bAddApplyDelegate);
    void SetCustomOpacityMaskClipValue(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomBlendMode(const TEnumAsByte<EBlendMode>& AttributeValue, bool bAddApplyDelegate);
    void GetTransmissionColorConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetTangentConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetSubsurfaceConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetSpecularConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetRoughnessConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetRefractionConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetOpacityConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetOcclusionConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetObjectClass();
    void GetNormalConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetMetallicConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetFuzzColorConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetEmissiveColorConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetCustomTwoSided(bool& AttributeValue);
    void GetCustomTranslucencyLightingMode(TEnumAsByte<ETranslucencyLightingMode>& AttributeValue);
    void GetCustomShadingModel(TEnumAsByte<EMaterialShadingModel>& AttributeValue);
    void GetCustomScreenSpaceReflections(bool& AttributeValue);
    void GetCustomRefractionMethod(TEnumAsByte<ERefractionMode>& AttributeValue);
    void GetCustomOpacityMaskClipValue(float& AttributeValue);
    void GetCustomBlendMode(TEnumAsByte<EBlendMode>& AttributeValue);
    void GetClothConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetClearCoatRoughnessConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetClearCoatNormalConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetClearCoatConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetBaseColorConnection(FString& ExpressionNodeUid, FString& OutputName);
    void GetAnisotropyConnection(FString& ExpressionNodeUid, FString& OutputName);
    void ConnectToTransmissionColor(FString AttributeValue);
    void ConnectToTangent(FString ExpressionNodeUid);
    void ConnectToSubsurface(FString ExpressionNodeUid);
    void ConnectToSpecular(FString ExpressionNodeUid);
    void ConnectToRoughness(FString ExpressionNodeUid);
    void ConnectToRefraction(FString AttributeValue);
    void ConnectToOpacity(FString AttributeValue);
    void ConnectToOcclusion(FString AttributeValue);
    void ConnectToNormal(FString ExpressionNodeUid);
    void ConnectToMetallic(FString AttributeValue);
    void ConnectToFuzzColor(FString AttributeValue);
    void ConnectToEmissiveColor(FString ExpressionNodeUid);
    void ConnectToCloth(FString AttributeValue);
    void ConnectToClearCoatRoughness(FString AttributeValue);
    void ConnectToClearCoatNormal(FString AttributeValue);
    void ConnectToClearCoat(FString AttributeValue);
    void ConnectToBaseColor(FString AttributeValue);
    void ConnectToAnisotropy(FString ExpressionNodeUid);
    void ConnectOutputToTransmissionColor(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToTangent(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToSubsurface(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToSpecular(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToRoughness(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToRefraction(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToOpacity(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToOcclusion(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToNormal(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToMetallic(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToFuzzColor(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToEmissiveColor(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToCloth(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToClearCoatRoughness(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToClearCoatNormal(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToClearCoat(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToBaseColor(FString ExpressionNodeUid, FString OutputName);
    void ConnectOutputToAnisotropy(FString ExpressionNodeUid, FString OutputName);
}; // Size: 0x1B0

class UInterchangeMaterialFunctionCallExpressionFactoryNode : public UInterchangeMaterialExpressionFactoryNode
{

    void SetCustomMaterialFunctionDependency(FString AttributeValue);
    void GetCustomMaterialFunctionDependency(FString& AttributeValue);
}; // Size: 0x160

class UInterchangeMaterialFunctionFactoryNode : public UInterchangeBaseMaterialFactoryNode
{

    void GetObjectClass();
    void GetInputConnection(FString InputName, FString& ExpressionNodeUid, FString& OutputName);
}; // Size: 0x140

class UInterchangeMaterialInstanceFactoryNode : public UInterchangeBaseMaterialFactoryNode
{

    void SetCustomParent(FString AttributeValue);
    void SetCustomInstanceClassName(FString AttributeValue);
    void GetCustomParent(FString& AttributeValue);
    void GetCustomInstanceClassName(FString& AttributeValue);
}; // Size: 0x160

class UInterchangeMeshActorFactoryNode : public UInterchangeActorFactoryNode
{

    void SetSlotMaterialDependencyUid(FString SlotName, FString MaterialDependencyUid);
    void SetCustomGeometricTransform(const FTransform& AttributeValue);
    void SetCustomAnimationAssetUidToPlay(FString AttributeValue);
    void RemoveSlotMaterialDependencyUid(FString SlotName);
    void GetSlotMaterialDependencyUid(FString SlotName, FString& OutMaterialDependency);
    void GetSlotMaterialDependencies(TMap<FString, FString>& OutMaterialDependencies);
    void GetCustomGeometricTransform(FTransform& AttributeValue);
    void GetCustomAnimationAssetUidToPlay(FString& AttributeValue);
}; // Size: 0x208

class UInterchangeMeshFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetSlotMaterialDependencyUid(FString SlotName, FString MaterialDependencyUid);
    void SetCustomVertexColorReplace(const bool& AttributeValue);
    void SetCustomVertexColorOverride(const FColor& AttributeValue);
    void SetCustomVertexColorIgnore(const bool& AttributeValue);
    void SetCustomUseMikkTSpace(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomUseHighPrecisionTangentBasis(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomUseFullPrecisionUVs(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomUseBackwardsCompatibleF16TruncUVs(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomRemoveDegenerates(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomRecomputeTangents(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomRecomputeNormals(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomLODGroup(const FName& AttributeValue, bool bAddApplyDelegate);
    void SetCustomComputeWeightedNormals(const bool& AttributeValue, bool bAddApplyDelegate);
    void RemoveSlotMaterialDependencyUid(FString SlotName);
    void RemoveLodDataUniqueId(FString LodDataUniqueId);
    void GetSlotMaterialDependencyUid(FString SlotName, FString& OutMaterialDependency);
    void GetSlotMaterialDependencies(TMap<FString, FString>& OutMaterialDependencies);
    void GetLodDataUniqueIds(TArray<FString>& OutLodDataUniqueIds);
    void GetLodDataCount();
    void GetCustomVertexColorReplace(bool& AttributeValue);
    void GetCustomVertexColorOverride(FColor& AttributeValue);
    void GetCustomVertexColorIgnore(bool& AttributeValue);
    void GetCustomUseMikkTSpace(bool& AttributeValue);
    void GetCustomUseHighPrecisionTangentBasis(bool& AttributeValue);
    void GetCustomUseFullPrecisionUVs(bool& AttributeValue);
    void GetCustomUseBackwardsCompatibleF16TruncUVs(bool& AttributeValue);
    void GetCustomRemoveDegenerates(bool& AttributeValue);
    void GetCustomRecomputeTangents(bool& AttributeValue);
    void GetCustomRecomputeNormals(bool& AttributeValue);
    void GetCustomLODGroup(FName& AttributeValue);
    void GetCustomComputeWeightedNormals(bool& AttributeValue);
    void AddLodDataUniqueId(FString LodDataUniqueId);
}; // Size: 0x2B0

class UInterchangePhysicalCameraFactoryNode : public UInterchangeActorFactoryNode
{

    void SetCustomSensorWidth(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomSensorHeight(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomFocusMethod(const ECameraFocusMethod& AttributeValue, bool bAddApplyDelegate);
    void SetCustomFocalLength(const float& AttributeValue, bool bAddApplyDelegate);
    void GetCustomSensorWidth(float& AttributeValue);
    void GetCustomSensorHeight(float& AttributeValue);
    void GetCustomFocusMethod(ECameraFocusMethod& AttributeValue);
    void GetCustomFocalLength(float& AttributeValue);
}; // Size: 0x1B0

class UInterchangePhysicsAssetFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetCustomSkeletalMeshUid(FString AttributeValue);
    void InitializePhysicsAssetNode(FString UniqueID, FString DisplayLabel, FString InAssetClass);
    void GetObjectClass();
    void GetCustomSkeletalMeshUid(FString& AttributeValue);
}; // Size: 0x170

class UInterchangePointLightFactoryNode : public UInterchangeLightFactoryNode
{

    void SetCustomUseInverseSquaredFalloff(bool AttributeValue, bool bAddApplyDelegate);
    void SetCustomLightFalloffExponent(float AttributeValue, bool bAddApplyDelegate);
    void GetCustomUseInverseSquaredFalloff(bool& AttributeValue);
    void GetCustomLightFalloffExponent(float& AttributeValue);
}; // Size: 0x200

class UInterchangeRectLightFactoryNode : public UInterchangeLightFactoryNode
{

    void SetCustomSourceWidth(float AttributeValue, bool bAddApplyDelegate);
    void SetCustomSourceHeight(float AttributeValue, bool bAddApplyDelegate);
    void GetCustomSourceWidth(float& AttributeValue);
    void GetCustomSourceHeight(float& AttributeValue);
}; // Size: 0x200

class UInterchangeSceneImportAssetFactoryNode : public UInterchangeFactoryBaseNode
{
}; // Size: 0x140

class UInterchangeSceneVariantSetsFactoryNode : public UInterchangeFactoryBaseNode
{

    void RemoveCustomVariantSetUid(FString VariantUid);
    void GetObjectClass();
    void GetCustomVariantSetUids(TArray<FString>& OutVariantUids);
    void GetCustomVariantSetUidCount();
    void GetCustomVariantSetUid(const int32 Index, FString& OutVariantUid);
    void AddCustomVariantSetUid(FString VariantUid);
}; // Size: 0x160

class UInterchangeSkeletalMeshFactoryNode : public UInterchangeMeshFactoryNode
{

    void SetCustomUseHighPrecisionSkinWeights(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomThresholdUV(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomThresholdTangentNormal(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomThresholdPosition(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomSkeletonSoftObjectPath(const FSoftObjectPath& AttributeValue);
    void SetCustomPhysicAssetSoftObjectPath(const FSoftObjectPath& AttributeValue);
    void SetCustomMorphThresholdPosition(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomImportMorphTarget(const bool& AttributeValue);
    void SetCustomImportContentType(const EInterchangeSkeletalMeshContentType& AttributeValue);
    void SetCustomCreatePhysicsAsset(const bool& AttributeValue);
    void SetCustomBoneInfluenceLimit(const int32& AttributeValue, bool bAddApplyDelegate);
    void InitializeSkeletalMeshNode(FString UniqueID, FString DisplayLabel, FString InAssetClass);
    void GetObjectClass();
    void GetCustomUseHighPrecisionSkinWeights(bool& AttributeValue);
    void GetCustomThresholdUV(float& AttributeValue);
    void GetCustomThresholdTangentNormal(float& AttributeValue);
    void GetCustomThresholdPosition(float& AttributeValue);
    void GetCustomSkeletonSoftObjectPath(FSoftObjectPath& AttributeValue);
    void GetCustomPhysicAssetSoftObjectPath(FSoftObjectPath& AttributeValue);
    void GetCustomMorphThresholdPosition(float& AttributeValue);
    void GetCustomImportMorphTarget(bool& AttributeValue);
    void GetCustomImportContentType(EInterchangeSkeletalMeshContentType& AttributeValue);
    void GetCustomCreatePhysicsAsset(bool& AttributeValue);
    void GetCustomBoneInfluenceLimit(int32& AttributeValue);
}; // Size: 0x378

class UInterchangeSkeletalMeshLodDataNode : public UInterchangeFactoryBaseNode
{

    void SetCustomSkeletonUid(FString AttributeValue);
    void RemoveMeshUid(FString MeshName);
    void RemoveAllMeshes();
    void GetMeshUidsCount();
    void GetMeshUids(TArray<FString>& OutMeshNames);
    void GetCustomSkeletonUid(FString& AttributeValue);
    void AddMeshUid(FString MeshName);
}; // Size: 0x170

class UInterchangeSkeletonFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetCustomUseTimeZeroForBindPose(const bool& AttributeValue);
    void SetCustomSkeletalMeshFactoryNodeUid(FString AttributeValue);
    void SetCustomRootJointUid(FString AttributeValue);
    void InitializeSkeletonNode(FString UniqueID, FString DisplayLabel, FString InAssetClass);
    void GetObjectClass();
    void GetCustomUseTimeZeroForBindPose(bool& AttributeValue);
    void GetCustomSkeletalMeshFactoryNodeUid(FString& AttributeValue);
    void GetCustomRootJointUid(FString& AttributeValue);
}; // Size: 0x190

class UInterchangeSpotLightFactoryNode : public UInterchangePointLightFactoryNode
{

    void SetCustomOuterConeAngle(float AttributeValue, bool bAddApplyDelegate);
    void SetCustomInnerConeAngle(float AttributeValue, bool bAddApplyDelegate);
    void GetCustomOuterConeAngle(float& AttributeValue);
    void GetCustomInnerConeAngle(float& AttributeValue);
}; // Size: 0x220

class UInterchangeStandardCameraFactoryNode : public UInterchangeActorFactoryNode
{

    void SetCustomWidth(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomProjectionMode(const TEnumAsByte<ECameraProjectionMode::Type>& AttributeValue, bool bAddApplyDelegate);
    void SetCustomNearClipPlane(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomFieldOfView(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomFarClipPlane(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAspectRatio(const float& AttributeValue, bool bAddApplyDelegate);
    void GetCustomWidth(float& AttributeValue);
    void GetCustomProjectionMode(TEnumAsByte<ECameraProjectionMode::Type>& AttributeValue);
    void GetCustomNearClipPlane(float& AttributeValue);
    void GetCustomFieldOfView(float& AttributeValue);
    void GetCustomFarClipPlane(float& AttributeValue);
    void GetCustomAspectRatio(float& AttributeValue);
}; // Size: 0x1D0

class UInterchangeStaticMeshFactoryNode : public UInterchangeMeshFactoryNode
{

    void SetCustomSupportFaceRemap(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomSrcLightmapIndex(const int32& AttributeValue, bool bAddApplyDelegate);
    void SetCustomMinLightmapResolution(const int32& AttributeValue, bool bAddApplyDelegate);
    void SetCustomMaxLumenMeshCards(const int32& AttributeValue, bool bAddApplyDelegate);
    void SetCustomGenerateLightmapUVs(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomGenerateDistanceFieldAsIfTwoSided(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomDstLightmapIndex(const int32& AttributeValue, bool bAddApplyDelegate);
    void SetCustomDistanceFieldResolutionScale(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomDistanceFieldReplacementMesh(const FSoftObjectPath& AttributeValue, bool bAddApplyDelegate);
    void SetCustomBuildScale3D(const FVector& AttributeValue, bool bAddApplyDelegate);
    void SetCustomBuildReversedIndexBuffer(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomBuildNanite(const bool& AttributeValue, bool bAddApplyDelegate);
    void RemoveSocketUd(FString SocketUid);
    void InitializeStaticMeshNode(FString UniqueID, FString DisplayLabel, FString InAssetClass);
    void GetSocketUids(TArray<FString>& OutSocketUids);
    void GetSocketUidCount();
    void GetObjectClass();
    void GetCustomSupportFaceRemap(bool& AttributeValue);
    void GetCustomSrcLightmapIndex(int32& AttributeValue);
    void GetCustomMinLightmapResolution(int32& AttributeValue);
    void GetCustomMaxLumenMeshCards(int32& AttributeValue);
    void GetCustomGenerateLightmapUVs(bool& AttributeValue);
    void GetCustomGenerateDistanceFieldAsIfTwoSided(bool& AttributeValue);
    void GetCustomDstLightmapIndex(int32& AttributeValue);
    void GetCustomDistanceFieldResolutionScale(float& AttributeValue);
    void GetCustomDistanceFieldReplacementMesh(FSoftObjectPath& AttributeValue);
    void GetCustomBuildScale3D(FVector& AttributeValue);
    void GetCustomBuildReversedIndexBuffer(bool& AttributeValue);
    void GetCustomBuildNanite(bool& AttributeValue);
    void AddSocketUids(const TArray<FString>& InSocketUids);
    void AddSocketUid(FString SocketUid);
}; // Size: 0x398

class UInterchangeStaticMeshLodDataNode : public UInterchangeFactoryBaseNode
{

    void SetOneConvexHullPerUCX(bool AttributeValue);
    void SetImportCollision(bool AttributeValue);
    void RemoveSphereCollisionMeshUid(FString MeshName);
    void RemoveMeshUid(FString MeshName);
    void RemoveConvexCollisionMeshUid(FString MeshName);
    void RemoveCapsuleCollisionMeshUid(FString MeshName);
    void RemoveBoxCollisionMeshUid(FString MeshName);
    void RemoveAllSphereCollisionMeshes();
    void RemoveAllMeshes();
    void RemoveAllConvexCollisionMeshes();
    void RemoveAllCapsuleCollisionMeshes();
    void RemoveAllBoxCollisionMeshes();
    void GetSphereCollisionMeshUidsCount();
    void GetSphereCollisionMeshUids(TArray<FString>& OutMeshNames);
    void GetOneConvexHullPerUCX(bool& AttributeValue);
    void GetMeshUidsCount();
    void GetMeshUids(TArray<FString>& OutMeshNames);
    void GetImportCollision(bool& AttributeValue);
    void GetConvexCollisionMeshUidsCount();
    void GetConvexCollisionMeshUids(TArray<FString>& OutMeshNames);
    void GetCapsuleCollisionMeshUidsCount();
    void GetCapsuleCollisionMeshUids(TArray<FString>& OutMeshNames);
    void GetBoxCollisionMeshUidsCount();
    void GetBoxCollisionMeshUids(TArray<FString>& OutMeshNames);
    void AddSphereCollisionMeshUid(FString MeshName);
    void AddMeshUid(FString MeshName);
    void AddConvexCollisionMeshUid(FString MeshName);
    void AddCapsuleCollisionMeshUid(FString MeshName);
    void AddBoxCollisionMeshUid(FString MeshName);
}; // Size: 0x200

class UInterchangeTexture2DArrayFactoryNode : public UInterchangeTextureFactoryNode
{

    void SetCustomAddressZ(const uint8 AttributeValue, bool bAddApplyDelegate);
    void GetCustomAddressZ(uint8& AttributeValue);
    void GetCustomAddressY(uint8& AttributeValue);
    void GetCustomAddressX(uint8& AttributeValue);
}; // Size: 0x400

class UInterchangeTexture2DFactoryNode : public UInterchangeTextureFactoryNode
{

    void SetSourceBlocks(const TMap<int32, FString>& InSourceBlocks);
    void SetSourceBlockByCoordinates(int32 X, int32 Y, FString InSourceFile);
    void SetSourceBlock(int32 BlockIndex, FString InSourceFile);
    void SetCustomAddressY(const TEnumAsByte<TextureAddress> AttributeValue, bool bAddApplyDelegate);
    void SetCustomAddressX(const TEnumAsByte<TextureAddress> AttributeValue, bool bAddApplyDelegate);
    void GetSourceBlocks();
    void GetSourceBlockByCoordinates(int32 X, int32 Y, FString& OutSourceFile);
    void GetSourceBlock(int32 BlockIndex, FString& OutSourceFile);
    void GetCustomAddressY(TEnumAsByte<TextureAddress>& AttributeValue);
    void GetCustomAddressX(TEnumAsByte<TextureAddress>& AttributeValue);
}; // Size: 0x468

class UInterchangeTextureCubeArrayFactoryNode : public UInterchangeTextureFactoryNode
{
}; // Size: 0x3D0

class UInterchangeTextureCubeFactoryNode : public UInterchangeTextureFactoryNode
{
}; // Size: 0x3D0

class UInterchangeTextureFactoryNode : public UInterchangeFactoryBaseNode
{

    void SetCustomVirtualTextureStreaming(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomTranslatedTextureNodeUid(FString AttributeValue);
    void SetCustomSRGB(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomPreferCompressedSourceData(const bool& AttributeValue);
    void SetCustomPowerOfTwoMode(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomPaddingColor(const FColor& AttributeValue, bool bAddApplyDelegate);
    void SetCustomMipLoadOptions(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomMipGenSettings(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomMaxTextureSize(const int32& AttributeValue, bool bAddApplyDelegate);
    void SetCustomLossyCompressionAmount(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomLODGroup(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomLODBias(const int32& AttributeValue, bool bAddApplyDelegate);
    void SetCustomFilter(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomDownscaleOptions(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomDownscale(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomDeferCompression(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomCompressionSettings(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomCompressionQuality(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomCompressionNoAlpha(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomCompositeTextureMode(const uint8& AttributeValue, bool bAddApplyDelegate);
    void SetCustomCompositePower(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomChromaKeyThreshold(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomChromaKeyColor(const FColor& AttributeValue, bool bAddApplyDelegate);
    void SetCustombUseLegacyGamma(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustombPreserveBorder(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustombFlipGreenChannel(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustombDoScaleMipsForAlphaCoverage(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustombChromaKeyTexture(const bool& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAlphaCoverageThresholds(const FVector4& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAllowNonPowerOfTwo(const bool& AttributeValue);
    void SetCustomAdjustVibrance(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAdjustSaturation(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAdjustRGBCurve(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAdjustMinAlpha(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAdjustMaxAlpha(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAdjustHue(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAdjustBrightnessCurve(const float& AttributeValue, bool bAddApplyDelegate);
    void SetCustomAdjustBrightness(const float& AttributeValue, bool bAddApplyDelegate);
    void InitializeTextureNode(FString UniqueID, FString DisplayLabel, FString InAssetName);
    void GetObjectClass();
    void GetCustomVirtualTextureStreaming(bool& AttributeValue);
    void GetCustomTranslatedTextureNodeUid(FString& AttributeValue);
    void GetCustomSRGB(bool& AttributeValue);
    void GetCustomPreferCompressedSourceData(bool& AttributeValue);
    void GetCustomPowerOfTwoMode(uint8& AttributeValue);
    void GetCustomPaddingColor(FColor& AttributeValue);
    void GetCustomMipLoadOptions(uint8& AttributeValue);
    void GetCustomMipGenSettings(uint8& AttributeValue);
    void GetCustomMaxTextureSize(int32& AttributeValue);
    void GetCustomLossyCompressionAmount(uint8& AttributeValue);
    void GetCustomLODGroup(uint8& AttributeValue);
    void GetCustomLODBias(int32& AttributeValue);
    void GetCustomFilter(uint8& AttributeValue);
    void GetCustomDownscaleOptions(uint8& AttributeValue);
    void GetCustomDownscale(float& AttributeValue);
    void GetCustomDeferCompression(bool& AttributeValue);
    void GetCustomCompressionSettings(uint8& AttributeValue);
    void GetCustomCompressionQuality(uint8& AttributeValue);
    void GetCustomCompressionNoAlpha(bool& AttributeValue);
    void GetCustomCompositeTextureMode(uint8& AttributeValue);
    void GetCustomCompositePower(float& AttributeValue);
    void GetCustomChromaKeyThreshold(float& AttributeValue);
    void GetCustomChromaKeyColor(FColor& AttributeValue);
    void GetCustombUseLegacyGamma(bool& AttributeValue);
    void GetCustombPreserveBorder(bool& AttributeValue);
    void GetCustombFlipGreenChannel(bool& AttributeValue);
    void GetCustombDoScaleMipsForAlphaCoverage(bool& AttributeValue);
    void GetCustombChromaKeyTexture(bool& AttributeValue);
    void GetCustomAlphaCoverageThresholds(FVector4& AttributeValue);
    void GetCustomAllowNonPowerOfTwo(bool& AttributeValue);
    void GetCustomAdjustVibrance(float& AttributeValue);
    void GetCustomAdjustSaturation(float& AttributeValue);
    void GetCustomAdjustRGBCurve(float& AttributeValue);
    void GetCustomAdjustMinAlpha(float& AttributeValue);
    void GetCustomAdjustMaxAlpha(float& AttributeValue);
    void GetCustomAdjustHue(float& AttributeValue);
    void GetCustomAdjustBrightnessCurve(float& AttributeValue);
    void GetCustomAdjustBrightness(float& AttributeValue);
}; // Size: 0x3D0

class UInterchangeTextureLightProfileFactoryNode : public UInterchangeTexture2DFactoryNode
{

    void SetCustomTextureMultiplier(const float AttributeValue, bool bAddApplyDelegate);
    void SetCustomBrightness(const float AttributeValue, bool bAddApplyDelegate);
    void GetCustomTextureMultiplier(float& AttributeValue);
    void GetCustomBrightness(float& AttributeValue);
}; // Size: 0x488

class UInterchangeVolumeTextureFactoryNode : public UInterchangeTextureFactoryNode
{
}; // Size: 0x3D0

#endif
