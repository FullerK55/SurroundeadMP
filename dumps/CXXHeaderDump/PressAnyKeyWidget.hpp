#ifndef UE4SS_SDK_PressAnyKeyWidget_HPP
#define UE4SS_SDK_PressAnyKeyWidget_HPP

class UPressAnyKeyWidget_C : public UUserWidget
{
    FPointerToUberGraphFrame UberGraphFrame;                                          // 0x02C0 (size: 0x8)
    class UWidgetAnimation* FadeInAnim;                                               // 0x02C8 (size: 0x8)
    class UWidgetAnimation* TextFadeInOut;                                            // 0x02D0 (size: 0x8)
    class UWidgetAnimation* FadeOutAnimation;                                         // 0x02D8 (size: 0x8)
    FPressAnyKeyWidget_CEventKeyDown EventKeyDown;                                    // 0x02E0 (size: 0x10)
    void EventKeyDown();

    void OnKeyDown(FGeometry MyGeometry, FKeyEvent InKeyEvent);
    void OnInitialized();
    void Tick(FGeometry MyGeometry, float InDeltaTime);
    void ExecuteUbergraph_PressAnyKeyWidget(int32 EntryPoint);
    void EventKeyDown__DelegateSignature();
}; // Size: 0x2F0

#endif
