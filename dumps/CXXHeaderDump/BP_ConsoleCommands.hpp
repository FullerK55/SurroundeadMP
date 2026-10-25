#ifndef UE4SS_SDK_BP_ConsoleCommands_HPP
#define UE4SS_SDK_BP_ConsoleCommands_HPP

class ABP_ConsoleCommands_C : public AActor
{
    FPointerToUberGraphFrame UberGraphFrame;                                          // 0x0298 (size: 0x8)
    class USceneComponent* DefaultSceneRoot;                                          // 0x02A0 (size: 0x8)

    void ReceiveBeginPlay();
    void ExecuteUbergraph_BP_ConsoleCommands(int32 EntryPoint);
}; // Size: 0x2A8

#endif
