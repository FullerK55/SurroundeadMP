#ifndef UE4SS_SDK_AssetTags_HPP
#define UE4SS_SDK_AssetTags_HPP

#include "AssetTags_enums.hpp"

class UAssetTagsSubsystem : public UEngineSubsystem
{

    void K2_GetCollectionsContainingAsset(const FSoftObjectPath& AssetPath);
    void GetCollectionsContainingAssetPtr(const class UObject* AssetPtr);
    void GetCollectionsContainingAssetData(const FAssetData& AssetData);
    void GetCollectionsContainingAsset(const FName AssetPathName);
    void GetCollections();
    void GetAssetsInCollection(const FName Name);
    void CollectionExists(const FName Name);
}; // Size: 0x30

#endif
