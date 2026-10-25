#ifndef UE4SS_SDK_BlueprintFileUtils_HPP
#define UE4SS_SDK_BlueprintFileUtils_HPP

class UBlueprintFileUtilsBPLibrary : public UBlueprintFunctionLibrary
{

    void MoveFile(FString DestFilename, FString SrcFilename, bool bReplace, bool bEvenIfReadOnly);
    void MakeDirectory(FString Path, bool bCreateTree);
    void GetUserDirectory();
    void FindRecursive(FString StartDirectory, TArray<FString>& FoundPaths, FString Wildcard, bool bFindFiles, bool bFindDirectories);
    void FindFiles(FString Directory, TArray<FString>& FoundFiles, FString FileExtension);
    void FileExists(FString Filename);
    void DirectoryExists(FString Directory);
    void DeleteFile(FString Filename, bool bMustExist, bool bEvenIfReadOnly);
    void DeleteDirectory(FString Directory, bool bMustExist, bool bDeleteRecursively);
    void CopyFile(FString DestFilename, FString SrcFilename, bool bReplace, bool bEvenIfReadOnly);
}; // Size: 0x28

#endif
