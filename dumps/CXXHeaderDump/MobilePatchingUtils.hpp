#ifndef UE4SS_SDK_MobilePatchingUtils_HPP
#define UE4SS_SDK_MobilePatchingUtils_HPP

class UMobileInstalledContent : public UObject
{

    void Mount(int32 PakOrder, FString MountPoint);
    void GetInstalledContentSize();
    void GetDiskFreeSpace();
}; // Size: 0x48

class UMobilePatchingLibrary : public UBlueprintFunctionLibrary
{

    void RequestContent(FString RemoteManifestURL, FString CloudURL, FString InstallDirectory, FRequestContentOnSucceeded OnSucceeded, FRequestContentOnFailed OnFailed);
    void HasActiveWiFiConnection();
    void GetSupportedPlatformNames();
    void GetInstalledContent(FString InstallDirectory);
    void GetActiveDeviceProfileName();
}; // Size: 0x28

class UMobilePendingContent : public UMobileInstalledContent
{

    void StartInstall(FStartInstallOnSucceeded OnSucceeded, FStartInstallOnFailed OnFailed);
    void GetTotalDownloadedSize();
    void GetRequiredDiskSpace();
    void GetInstallProgress();
    void GetDownloadStatusText();
    void GetDownloadSpeed();
    void GetDownloadSize();
}; // Size: 0x88

#endif
