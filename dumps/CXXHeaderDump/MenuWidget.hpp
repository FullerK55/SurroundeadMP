#ifndef UE4SS_SDK_MenuWidget_HPP
#define UE4SS_SDK_MenuWidget_HPP

class UMenuWidget_C : public UUserWidget
{
    FPointerToUberGraphFrame UberGraphFrame;                                          // 0x02C0 (size: 0x8)
    class UWidgetAnimation* VehicleFade;                                              // 0x02C8 (size: 0x8)
    class UWidgetAnimation* TutorialFade;                                             // 0x02D0 (size: 0x8)
    class UWidgetAnimation* ShootingRangeFade;                                        // 0x02D8 (size: 0x8)
    class UWidgetAnimation* CreditsFadeInAndOut;                                      // 0x02E0 (size: 0x8)
    class UWidgetAnimation* FadeIn;                                                   // 0x02E8 (size: 0x8)
    class UButton* ButtonDiscord;                                                     // 0x02F0 (size: 0x8)
    class UButton* ButtonRoadmap;                                                     // 0x02F8 (size: 0x8)
    class UButton* ButtonTrello;                                                      // 0x0300 (size: 0x8)
    class UButtonWidget_C* ButtonWidget_BackFromDesktop;                              // 0x0308 (size: 0x8)
    class UButtonWidget_C* ButtonWidget_BackFromGameModeSelect;                       // 0x0310 (size: 0x8)
    class UButton* ContinueGame;                                                      // 0x0318 (size: 0x8)
    class UTextBlock* ContinueGameText;                                               // 0x0320 (size: 0x8)
    class UTextBlock* Credits_Person;                                                 // 0x0328 (size: 0x8)
    class UTextBlock* Credits_Role;                                                   // 0x0330 (size: 0x8)
    class UScaleBox* CreditsBox;                                                      // 0x0338 (size: 0x8)
    class UButton* GameModes;                                                         // 0x0340 (size: 0x8)
    class UCanvasPanel* GameModeSelectionWidget;                                      // 0x0348 (size: 0x8)
    class UTextBlock* GameModesText;                                                  // 0x0350 (size: 0x8)
    class UImage* GameTitle;                                                          // 0x0358 (size: 0x8)
    class UButton* HordeButton;                                                       // 0x0360 (size: 0x8)
    class UTextBlock* HordeText;                                                      // 0x0368 (size: 0x8)
    class UButton* Load;                                                              // 0x0370 (size: 0x8)
    class UTextBlock* LoadText;                                                       // 0x0378 (size: 0x8)
    class UCanvasPanel* MainMenu;                                                     // 0x0380 (size: 0x8)
    class UButton* NewGame;                                                           // 0x0388 (size: 0x8)
    class UTextBlock* NewGameText;                                                    // 0x0390 (size: 0x8)
    class UButton* Quit;                                                              // 0x0398 (size: 0x8)
    class UTextBlock* QuitText;                                                       // 0x03A0 (size: 0x8)
    class UButtonWidget_C* QuitToDesktopNoButton;                                     // 0x03A8 (size: 0x8)
    class UCanvasPanel* QuitToDesktopWidget;                                          // 0x03B0 (size: 0x8)
    class UButtonWidget_C* QuitToDesktopYesButton;                                    // 0x03B8 (size: 0x8)
    class UImage* RoadmapImg;                                                         // 0x03C0 (size: 0x8)
    class USaveMenu_C* SaveMenu;                                                      // 0x03C8 (size: 0x8)
    class UButton* Settings;                                                          // 0x03D0 (size: 0x8)
    class USettingsMenu_C* SettingsMenu;                                              // 0x03D8 (size: 0x8)
    class UTextBlock* SettingsText;                                                   // 0x03E0 (size: 0x8)
    class UButton* ShootingRangeButton;                                               // 0x03E8 (size: 0x8)
    class UTextBlock* ShootingRangeText;                                              // 0x03F0 (size: 0x8)
    class UButton* TutorialButton;                                                    // 0x03F8 (size: 0x8)
    class UTextBlock* TutorialText;                                                   // 0x0400 (size: 0x8)
    class UButton* VehicleButton;                                                     // 0x0408 (size: 0x8)
    class UTextBlock* VehicleText;                                                    // 0x0410 (size: 0x8)
    bool EscapeKeyDown;                                                               // 0x0418 (size: 0x1)

    void ReturnToMenu();
    void BindEvents();
    void OnKeyUp(FGeometry MyGeometry, FKeyEvent InKeyEvent);
    void OnKeyDown(FGeometry MyGeometry, FKeyEvent InKeyEvent);
    void OnFailed_E146B6814333B39837D422955BF1D1E8();
    void OnCompleted_E146B6814333B39837D422955BF1D1E8();
    void BndEvt__Quit_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__Quit_K2Node_ComponentBoundEvent_10_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__Play_K2Node_ComponentBoundEvent_11_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__Settings_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__StartGame_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__Settings_K2Node_ComponentBoundEvent_13_OnButtonClickedEvent__DelegateSignature();
    void Construct();
    void BndEvt__MenuWidget_Continue_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__MenuWidget_Continue_K2Node_ComponentBoundEvent_14_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__MenuWidget_Button_58_K2Node_ComponentBoundEvent_15_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__MenuWidget_GameModes_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__MenuWidget_GameModes_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__MenuWidget_Button_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__MenuWidget_QuitToDesktopYesButton_K2Node_ComponentBoundEvent_7_ButtonPressed__DelegateSignature();
    void BndEvt__MenuWidget_QuitToDesktopNoButton_K2Node_ComponentBoundEvent_9_ButtonPressed__DelegateSignature();
    void BndEvt__ShootingRangeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__ShootingRangeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__ShootingRangeButton_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__LevelSelection_TutorialButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__LevelSelection_TutorialButton_K2Node_ComponentBoundEvent_7_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__LevelSelection_TutorialButton_K2Node_ComponentBoundEvent_8_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__LevelSelection_VehicleButton_K2Node_ComponentBoundEvent_9_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__LevelSelection_VehicleButton_K2Node_ComponentBoundEvent_10_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__LevelSelection_VehicleButton_K2Node_ComponentBoundEvent_14_OnButtonHoverEvent__DelegateSignature();
    void BndEvt__MenuWidget_ButtonWidget_BackFromGameModeSelect_K2Node_ComponentBoundEvent_11_ButtonPressed__DelegateSignature();
    void BndEvt__MenuWidget_ButtonWidget_BackFromDesktop_K2Node_ComponentBoundEvent_24_ButtonPressed__DelegateSignature();
    void BndEvt__MenuWidget_ContinueGame_K2Node_ComponentBoundEvent_25_OnButtonClickedEvent__DelegateSignature();
    void BndEvt__MenuWidget_ButtonTrello_K2Node_ComponentBoundEvent_26_OnButtonClickedEvent__DelegateSignature();
    void RestartCredits();
    void StartCredits();
    void ExecuteUbergraph_MenuWidget(int32 EntryPoint);
}; // Size: 0x419

#endif
