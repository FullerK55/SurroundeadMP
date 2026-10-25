#ifndef UE4SS_SDK_AssetRegistry_HPP
#define UE4SS_SDK_AssetRegistry_HPP

struct FAssetRegistryDependencyOptions
{
    bool bIncludeSoftPackageReferences;                                               // 0x0000 (size: 0x1)
    bool bIncludeHardPackageReferences;                                               // 0x0001 (size: 0x1)
    bool bIncludeSearchableNames;                                                     // 0x0002 (size: 0x1)
    bool bIncludeSoftManagementReferences;                                            // 0x0003 (size: 0x1)
    bool bIncludeHardManagementReferences;                                            // 0x0004 (size: 0x1)

}; // Size: 0x5

struct FTagAndValue
{
    FName Tag;                                                                        // 0x0000 (size: 0x8)
    FString Value;                                                                    // 0x0008 (size: 0x10)

}; // Size: 0x18

class IAssetRegistry : public IInterface
{

    void WaitForPackage(FString PackageName);
    void WaitForCompletion();
    void UseFilterToExcludeAssets(TArray<FAssetData>& AssetDataList, const FARFilter& Filter);
    void SearchAllAssets(bool bSynchronousSearch);
    void ScanPathsSynchronous(const TArray<FString>& InPaths, bool bForceRescan, bool bIgnoreDenyListScanFilters);
    void ScanModifiedAssetFiles(const TArray<FString>& InFilePaths);
    void ScanFilesSynchronous(const TArray<FString>& InFilePaths, bool bForceRescan);
    void RunAssetsThroughFilter(TArray<FAssetData>& AssetDataList, const FARFilter& Filter);
    void PrioritizeSearchPath(FString PathToPrioritize);
    void K2_GetReferencers(FName PackageName, const FAssetRegistryDependencyOptions& ReferenceOptions, TArray<FName>& OutReferencers);
    void K2_GetDependencies(FName PackageName, const FAssetRegistryDependencyOptions& DependencyOptions, TArray<FName>& OutDependencies);
    void K2_GetAssetByObjectPath(const FSoftObjectPath& ObjectPath, bool bIncludeOnlyOnDiskAssets, bool bSkipARFilteredAssets);
    void IsSearchAsync();
    void IsSearchAllAssets();
    void IsLoadingAssets();
    void HasAssets(const FName PackagePath, const bool bRecursive);
    void GetSubPaths(FString InBasePath, TArray<FString>& OutPathList, bool bInRecurse);
    void GetDerivedClassNames(const TArray<FTopLevelAssetPath>& ClassNames, const TSet<FTopLevelAssetPath>& ExcludedClassNames, TSet<FTopLevelAssetPath>& OutDerivedClassNames);
    void GetAssetsByPaths(TArray<FName> PackagePaths, TArray<FAssetData>& OutAssetData, bool bRecursive, bool bIncludeOnlyOnDiskAssets);
    void GetAssetsByPath(FName PackagePath, TArray<FAssetData>& OutAssetData, bool bRecursive, bool bIncludeOnlyOnDiskAssets);
    void GetAssetsByPackageName(FName PackageName, TArray<FAssetData>& OutAssetData, bool bIncludeOnlyOnDiskAssets, bool bSkipARFilteredAssets);
    void GetAssetsByClass(FTopLevelAssetPath ClassPathName, TArray<FAssetData>& OutAssetData, bool bSearchSubClasses);
    void GetAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssetData, bool bSkipARFilteredAssets);
    void GetAssetByObjectPath(const FName ObjectPath, bool bIncludeOnlyOnDiskAssets);
    void GetAncestorClassNames(FTopLevelAssetPath ClassPathName, TArray<FTopLevelAssetPath>& OutAncestorClassNames);
    void GetAllCachedPaths(TArray<FString>& OutPathList);
    void GetAllAssets(TArray<FAssetData>& OutAssetData, bool bIncludeOnlyOnDiskAssets);
}; // Size: 0x28

class UAssetRegistryHelpers : public UObject
{

    void ToSoftObjectPath(const FAssetData& InAssetData);
    void SetFilterTagsAndValues(const FARFilter& InFilter, const TArray<FTagAndValue>& InTagsAndValues);
    void IsValid(const FAssetData& InAssetData);
    void IsUAsset(const FAssetData& InAssetData);
    void IsRedirector(const FAssetData& InAssetData);
    void IsAssetLoaded(const FAssetData& InAssetData);
    void GetTagValue(const FAssetData& InAssetData, const FName& InTagName, FString& OutTagValue);
    void GetFullName(const FAssetData& InAssetData);
    void GetExportTextName(const FAssetData& InAssetData);
    void GetClass(const FAssetData& InAssetData);
    void GetBlueprintAssets(const FARFilter& InFilter, TArray<FAssetData>& OutAssetData);
    void GetAssetRegistry();
    void GetAsset(const FAssetData& InAssetData);
    void FindAssetNativeClass(const FAssetData& AssetData);
    void CreateAssetData(const class UObject* InAsset, bool bAllowBlueprintClass);
}; // Size: 0x28

class UAssetRegistryImpl : public UObject
{
}; // Size: 0xD78

#endif
