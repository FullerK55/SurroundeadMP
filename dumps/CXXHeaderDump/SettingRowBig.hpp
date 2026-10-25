#ifndef UE4SS_SDK_SettingRowBig_HPP
#define UE4SS_SDK_SettingRowBig_HPP

class USettingRowBig_C : public UUserWidget
{
    FPointerToUberGraphFrame UberGraphFrame;                                          // 0x02C0 (size: 0x8)
    class UBorder* AlternatingRowBorder;                                              // 0x02C8 (size: 0x8)
    class USizeBox* ContentSize;                                                      // 0x02D0 (size: 0x8)
    class UTextBlock* LabelText;                                                      // 0x02D8 (size: 0x8)
    class UTextBlock* LabelText_1;                                                    // 0x02E0 (size: 0x8)
    class UNamedSlot* SettingContent;                                                 // 0x02E8 (size: 0x8)
    FText Label;                                                                      // 0x02F0 (size: 0x18)
    double MinDesiredWidth;                                                           // 0x0308 (size: 0x8)
    int32 Index;                                                                      // 0x0310 (size: 0x4)
    FText Label_Small;                                                                // 0x0318 (size: 0x18)

    void PreConstruct(bool IsDesignTime);
    void ExecuteUbergraph_SettingRowBig(int32 EntryPoint);
}; // Size: 0x330

#endif
