#ifndef UE4SS_SDK_NewGameDifficultySelectionPage_HPP
#define UE4SS_SDK_NewGameDifficultySelectionPage_HPP

class UNewGameDifficultySelectionPage_C : public UUserWidget
{
    FPointerToUberGraphFrame UberGraphFrame;                                          // 0x02C0 (size: 0x8)
    class UButton* BackButton;                                                        // 0x02C8 (size: 0x8)
    class UTextBlock* BackText;                                                       // 0x02D0 (size: 0x8)
    class UVerticalRadioSelect_C* CategorySelect;                                     // 0x02D8 (size: 0x8)
    class UWidgetSwitcher* CategorySwitcher;                                          // 0x02E0 (size: 0x8)
    class UDifficulty_AI_C* Difficulty_AI_UI;                                         // 0x02E8 (size: 0x8)
    class UDifficulty_General_C* Difficulty_GeneralUI;                                // 0x02F0 (size: 0x8)
    class UDifficulty_Loot_C* Difficulty_Loot;                                        // 0x02F8 (size: 0x8)
    class UDifficulty_Player_C* Difficulty_Player;                                    // 0x0300 (size: 0x8)
    class UDifficulty_Vehicles_C* Difficulty_Vehicles;                                // 0x0308 (size: 0x8)
    class UButton* EasyButton;                                                        // 0x0310 (size: 0x8)
    class UTextBlock* EasyText;                                                       // 0x0318 (size: 0x8)
    class UButton* HardenedButton;                                                    // 0x0320 (size: 0x8)
    class UTextBlock* HardenedText;                                                   // 0x0328 (size: 0x8)
    class UButton* NightmareButton;                                                   // 0x0330 (size: 0x8)
    class UTextBlock* NightmareText;                                                  // 0x0338 (size: 0x8)
    class UButton* PeacefulButton;                                                    // 0x0340 (size: 0x8)
    class UTextBlock* PeacefulText;                                                   // 0x0348 (size: 0x8)
    class UButton* PlayButton;                                                        // 0x0350 (size: 0x8)
    class UTextBlock* PlayText;                                                       // 0x0358 (size: 0x8)
    class USettingRowBig_C* SettingRowBig;                                            // 0x0360 (size: 0x8)
    class USettingRowBig_C* SettingRowBig_1;                                          // 0x0368 (size: 0x8)
    class UButton* StandardButton;                                                    // 0x0370 (size: 0x8)
    class UTextBlock* StandardText;                                                   // 0x0378 (size: 0x8)

    void SetupPlayerLooks();
    void Exit();
    void Construct();
    void BndEvt__BackButton_K2Node_ComponentBoundEvent_11_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__BackButton_K2Node_ComponentBoundEvent_13_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__DifficultySelectionPage_PlayButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__DifficultySelectionPage_PlayButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__DifficultySettingsPage_PeacefulButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__DifficultySettingsPage_StandardButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__DifficultySettingsPage_HardenedButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__DifficultySettingsPage_NightmareButton_K2Node_ComponentBoundEvent_7_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__DifficultySettingsPage_PeacefulButton_K2Node_ComponentBoundEvent_9_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__DifficultySettingsPage_StandardButton_K2Node_ComponentBoundEvent_10_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__DifficultySettingsPage_HardenedButton_K2Node_ComponentBoundEvent_13_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__DifficultySettingsPage_NightmareButton_K2Node_ComponentBoundEvent_14_OnButtonClickedEvent__DelegateSignature();
    void CategoryChanged(FString Value);
    void BndEvt__NewGameDifficultySelectionPage_EasyButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature();
    void Tick(FGeometry MyGeometry, float InDeltaTime);
    void ExecuteUbergraph_NewGameDifficultySelectionPage(int32 EntryPoint);
}; // Size: 0x380

#endif
