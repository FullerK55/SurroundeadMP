#ifndef UE4SS_SDK_MainMenu_HPP
#define UE4SS_SDK_MainMenu_HPP

class AMainMenu_C : public ALevelScriptActor
{
    FPointerToUberGraphFrame UberGraphFrame;                                          // 0x02A0 (size: 0x8)
    class UMenuWidget_C* MainMenu;                                                    // 0x02A8 (size: 0x8)
    class AAmbientSound* AmbientSound_2_ExecuteUbergraph_MainMenu_RefProperty;        // 0x02B0 (size: 0x8)
    class AEmitter* Emitter_3_ExecuteUbergraph_MainMenu_RefProperty;                  // 0x02B8 (size: 0x8)
    class ACameraActor* CameraActor_1_ExecuteUbergraph_MainMenu_RefProperty;          // 0x02C0 (size: 0x8)

    void ReceiveBeginPlay();
    void CreateMenu();
    void Event_KeyDown();
    void Event_DOFToggle(bool NewValue);
    void ExecuteUbergraph_MainMenu(int32 EntryPoint);
}; // Size: 0x2C8

#endif
