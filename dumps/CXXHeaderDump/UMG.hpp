#ifndef UE4SS_SDK_UMG_HPP
#define UE4SS_SDK_UMG_HPP

#include "UMG_enums.hpp"

struct FAnchorData
{
    FMargin Offsets;                                                                  // 0x0000 (size: 0x10)
    FAnchors Anchors;                                                                 // 0x0010 (size: 0x20)
    FVector2D Alignment;                                                              // 0x0030 (size: 0x10)

}; // Size: 0x40

struct FAnimationEventBinding
{
    class UWidgetAnimation* Animation;                                                // 0x0000 (size: 0x8)
    FAnimationEventBindingDelegate Delegate;                                          // 0x0008 (size: 0x10)
    void WidgetAnimationDynamicEvent();
    EWidgetAnimationEvent AnimationEvent;                                             // 0x0018 (size: 0x1)
    FName UserTag;                                                                    // 0x001C (size: 0x8)

}; // Size: 0x28

struct FBlueprintWidgetAnimationDelegateBinding
{
    EWidgetAnimationEvent Action;                                                     // 0x0000 (size: 0x1)
    FName AnimationToBind;                                                            // 0x0004 (size: 0x8)
    FName FunctionNameToBind;                                                         // 0x000C (size: 0x8)
    FName UserTag;                                                                    // 0x0014 (size: 0x8)

}; // Size: 0x1C

struct FDelegateRuntimeBinding
{
    FString ObjectName;                                                               // 0x0000 (size: 0x10)
    FName PropertyName;                                                               // 0x0010 (size: 0x8)
    FName FunctionName;                                                               // 0x0018 (size: 0x8)
    FDynamicPropertyPath SourcePath;                                                  // 0x0020 (size: 0x38)
    EBindingKind Kind;                                                                // 0x0058 (size: 0x1)

}; // Size: 0x60

struct FDynamicPropertyPath : public FCachedPropertyPath
{
}; // Size: 0x38

struct FEventReply
{
}; // Size: 0xB8

struct FGameViewportWidgetSlot
{
    FAnchors Anchors;                                                                 // 0x0000 (size: 0x20)
    FMargin Offsets;                                                                  // 0x0020 (size: 0x10)
    FVector2D Alignment;                                                              // 0x0030 (size: 0x10)
    int32 ZOrder;                                                                     // 0x0040 (size: 0x4)

}; // Size: 0x48

struct FMovieScene2DTransformMask
{
    uint32 Mask;                                                                      // 0x0000 (size: 0x4)

}; // Size: 0x4

struct FNamedSlotBinding
{
    FName Name;                                                                       // 0x0000 (size: 0x8)
    class UWidget* Content;                                                           // 0x0008 (size: 0x8)

}; // Size: 0x10

struct FPaintContext
{
}; // Size: 0x30

struct FRadialBoxSettings
{
    float StartingAngle;                                                              // 0x0000 (size: 0x4)
    bool bDistributeItemsEvenly;                                                      // 0x0004 (size: 0x1)
    float AngleBetweenItems;                                                          // 0x0008 (size: 0x4)
    float SectorCentralAngle;                                                         // 0x000C (size: 0x4)

}; // Size: 0x10

struct FRichImageRow : public FTableRowBase
{
    FSlateBrush Brush;                                                                // 0x0010 (size: 0xD0)

}; // Size: 0xE0

struct FRichTextStyleRow : public FTableRowBase
{
    FTextBlockStyle TextStyle;                                                        // 0x0010 (size: 0x340)

}; // Size: 0x350

struct FSequenceTickManagerWidgetData
{
}; // Size: 0x2

struct FShapedTextOptions
{
    uint8 bOverride_TextShapingMethod;                                                // 0x0000 (size: 0x1)
    uint8 bOverride_TextFlowDirection;                                                // 0x0000 (size: 0x1)
    ETextShapingMethod TextShapingMethod;                                             // 0x0001 (size: 0x1)
    ETextFlowDirection TextFlowDirection;                                             // 0x0002 (size: 0x1)

}; // Size: 0x3

struct FSlateChildSize
{
    float Value;                                                                      // 0x0000 (size: 0x4)
    TEnumAsByte<ESlateSizeRule::Type> SizeRule;                                       // 0x0004 (size: 0x1)

}; // Size: 0x8

struct FSlateMeshVertex
{
    FVector2f Position;                                                               // 0x0000 (size: 0x8)
    FColor Color;                                                                     // 0x0008 (size: 0x4)
    FVector2f UV0;                                                                    // 0x000C (size: 0x8)
    FVector2f UV1;                                                                    // 0x0014 (size: 0x8)
    FVector2f UV2;                                                                    // 0x001C (size: 0x8)
    FVector2f UV3;                                                                    // 0x0024 (size: 0x8)
    FVector2f UV4;                                                                    // 0x002C (size: 0x8)
    FVector2f UV5;                                                                    // 0x0034 (size: 0x8)

}; // Size: 0x3C

struct FUserWidgetPool
{
    TArray<UUserWidget*> ActiveWidgets;                                               // 0x0000 (size: 0x10)
    TArray<UUserWidget*> InactiveWidgets;                                             // 0x0010 (size: 0x10)

}; // Size: 0x88

struct FWidgetAnimationBinding
{
    FName WidgetName;                                                                 // 0x0000 (size: 0x8)
    FName SlotWidgetName;                                                             // 0x0008 (size: 0x8)
    FGuid AnimationGuid;                                                              // 0x0010 (size: 0x10)
    bool bIsRootWidget;                                                               // 0x0020 (size: 0x1)

}; // Size: 0x24

struct FWidgetChild
{
    FName WidgetName;                                                                 // 0x0000 (size: 0x8)
    TWeakObjectPtr<class UWidget> WidgetPtr;                                          // 0x0008 (size: 0x8)

}; // Size: 0x10

struct FWidgetComponentInstanceData : public FSceneComponentInstanceData
{
}; // Size: 0xC8

struct FWidgetEventField
{
}; // Size: 0x1

struct FWidgetNavigationData
{
    EUINavigationRule Rule;                                                           // 0x0000 (size: 0x1)
    FName WidgetToFocus;                                                              // 0x0004 (size: 0x8)
    TWeakObjectPtr<class UWidget> Widget;                                             // 0x000C (size: 0x8)
    FWidgetNavigationDataCustomDelegate CustomDelegate;                               // 0x0014 (size: 0x10)
    void CustomWidgetNavigationDelegate(EUINavigation Navigation);

}; // Size: 0x24

struct FWidgetStateBitfield
{
}; // Size: 0x590

struct FWidgetTransform
{
    FVector2D Translation;                                                            // 0x0000 (size: 0x10)
    FVector2D Scale;                                                                  // 0x0010 (size: 0x10)
    FVector2D Shear;                                                                  // 0x0020 (size: 0x10)
    float Angle;                                                                      // 0x0030 (size: 0x4)

}; // Size: 0x38

class INamedSlotInterface : public IInterface
{
}; // Size: 0x28

class IUserListEntry : public IInterface
{

    void BP_OnItemSelectionChanged(bool bIsSelected);
    void BP_OnItemExpansionChanged(bool bIsExpanded);
    void BP_OnEntryReleased();
}; // Size: 0x28

class IUserObjectListEntry : public IUserListEntry
{

    void OnListItemObjectSet(class UObject* ListItemObject);
}; // Size: 0x28

class UAsyncTaskDownloadImage : public UBlueprintAsyncActionBase
{
    FAsyncTaskDownloadImageOnSuccess OnSuccess;                                       // 0x0030 (size: 0x10)
    void DownloadImageDelegate(class UTexture2DDynamic* Texture);
    FAsyncTaskDownloadImageOnFail OnFail;                                             // 0x0040 (size: 0x10)
    void DownloadImageDelegate(class UTexture2DDynamic* Texture);

    void DownloadImage(FString URL);
}; // Size: 0x50

class UBackgroundBlur : public UContentWidget
{
    FMargin Padding;                                                                  // 0x0198 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x01A8 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x01A9 (size: 0x1)
    bool bApplyAlphaToBlur;                                                           // 0x01AA (size: 0x1)
    float BlurStrength;                                                               // 0x01AC (size: 0x4)
    bool bOverrideAutoRadiusCalculation;                                              // 0x01B0 (size: 0x1)
    int32 BlurRadius;                                                                 // 0x01B4 (size: 0x4)
    FVector4 CornerRadius;                                                            // 0x01C0 (size: 0x20)
    FSlateBrush LowQualityFallbackBrush;                                              // 0x01E0 (size: 0xD0)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetLowQualityFallbackBrush(const FSlateBrush& InBrush);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
    void SetCornerRadius(FVector4 InCornerRadius);
    void SetBlurStrength(float InStrength);
    void SetBlurRadius(int32 InBlurRadius);
    void SetApplyAlphaToBlur(bool bInApplyAlphaToBlur);
}; // Size: 0x2C0

class UBackgroundBlurSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0038 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0048 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0049 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x60

class UBoolBinding : public UPropertyBinding
{

    void GetValue();
}; // Size: 0x70

class UBorder : public UContentWidget
{
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0198 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0199 (size: 0x1)
    uint8 bShowEffectWhenDisabled;                                                    // 0x019A (size: 0x1)
    FLinearColor ContentColorAndOpacity;                                              // 0x019C (size: 0x10)
    FBorderContentColorAndOpacityDelegate ContentColorAndOpacityDelegate;             // 0x01AC (size: 0x10)
    void GetLinearColor();
    FMargin Padding;                                                                  // 0x01BC (size: 0x10)
    FSlateBrush Background;                                                           // 0x01D0 (size: 0xD0)
    FBorderBackgroundDelegate BackgroundDelegate;                                     // 0x02A0 (size: 0x10)
    void GetSlateBrush();
    FLinearColor BrushColor;                                                          // 0x02B0 (size: 0x10)
    FBorderBrushColorDelegate BrushColorDelegate;                                     // 0x02C0 (size: 0x10)
    void GetLinearColor();
    FVector2D DesiredSizeScale;                                                       // 0x02D0 (size: 0x10)
    bool bFlipForRightToLeftFlowDirection;                                            // 0x02E0 (size: 0x1)
    FBorderOnMouseButtonDownEvent OnMouseButtonDownEvent;                             // 0x02E4 (size: 0x10)
    void OnPointerEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    FBorderOnMouseButtonUpEvent OnMouseButtonUpEvent;                                 // 0x02F4 (size: 0x10)
    void OnPointerEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    FBorderOnMouseMoveEvent OnMouseMoveEvent;                                         // 0x0304 (size: 0x10)
    void OnPointerEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    FBorderOnMouseDoubleClickEvent OnMouseDoubleClickEvent;                           // 0x0314 (size: 0x10)
    void OnPointerEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetShowEffectWhenDisabled(bool bInShowEffectWhenDisabled);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
    void SetDesiredSizeScale(FVector2D InScale);
    void SetContentColorAndOpacity(FLinearColor InContentColorAndOpacity);
    void SetBrushFromTexture(class UTexture2D* Texture);
    void SetBrushFromMaterial(class UMaterialInterface* Material);
    void SetBrushFromAsset(class USlateBrushAsset* Asset);
    void SetBrushColor(FLinearColor InBrushColor);
    void SetBrush(const FSlateBrush& InBrush);
    void GetDynamicMaterial();
}; // Size: 0x340

class UBorderSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0038 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0048 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0049 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x60

class UBrushBinding : public UPropertyBinding
{

    void GetValue();
}; // Size: 0x78

class UButton : public UContentWidget
{
    FButtonStyle WidgetStyle;                                                         // 0x01A0 (size: 0x3F0)
    FLinearColor ColorAndOpacity;                                                     // 0x0590 (size: 0x10)
    FLinearColor BackgroundColor;                                                     // 0x05A0 (size: 0x10)
    TEnumAsByte<EButtonClickMethod::Type> ClickMethod;                                // 0x05B0 (size: 0x1)
    TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;                                // 0x05B1 (size: 0x1)
    TEnumAsByte<EButtonPressMethod::Type> PressMethod;                                // 0x05B2 (size: 0x1)
    bool IsFocusable;                                                                 // 0x05B3 (size: 0x1)
    FButtonOnClicked OnClicked;                                                       // 0x05B8 (size: 0x10)
    void OnButtonClickedEvent();
    FButtonOnPressed OnPressed;                                                       // 0x05C8 (size: 0x10)
    void OnButtonPressedEvent();
    FButtonOnReleased OnReleased;                                                     // 0x05D8 (size: 0x10)
    void OnButtonReleasedEvent();
    FButtonOnHovered OnHovered;                                                       // 0x05E8 (size: 0x10)
    void OnButtonHoverEvent();
    FButtonOnUnhovered OnUnhovered;                                                   // 0x05F8 (size: 0x10)
    void OnButtonHoverEvent();

    void SetTouchMethod(TEnumAsByte<EButtonTouchMethod::Type> InTouchMethod);
    void SetStyle(const FButtonStyle& InStyle);
    void SetPressMethod(TEnumAsByte<EButtonPressMethod::Type> InPressMethod);
    void SetColorAndOpacity(FLinearColor InColorAndOpacity);
    void SetClickMethod(TEnumAsByte<EButtonClickMethod::Type> InClickMethod);
    void SetBackgroundColor(FLinearColor InBackgroundColor);
    void IsPressed();
}; // Size: 0x620

class UButtonSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0038 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0048 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0049 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x60

class UCanvasPanel : public UPanelWidget
{

    void AddChildToCanvas(class UWidget* Content);
}; // Size: 0x1A8

class UCanvasPanelSlot : public UPanelSlot
{
    FAnchorData LayoutData;                                                           // 0x0038 (size: 0x40)
    bool bAutoSize;                                                                   // 0x0078 (size: 0x1)
    int32 ZOrder;                                                                     // 0x007C (size: 0x4)

    void SetZOrder(int32 InZOrder);
    void SetSize(FVector2D InSize);
    void SetPosition(FVector2D InPosition);
    void SetOffsets(FMargin InOffset);
    void SetMinimum(FVector2D InMinimumAnchors);
    void SetMaximum(FVector2D InMaximumAnchors);
    void SetLayout(const FAnchorData& InLayoutData);
    void SetAutoSize(bool InbAutoSize);
    void SetAnchors(FAnchors InAnchors);
    void SetAlignment(FVector2D InAlignment);
    void GetZOrder();
    void GetSize();
    void GetPosition();
    void GetOffsets();
    void GetLayout();
    void GetAutoSize();
    void GetAnchors();
    void GetAlignment();
}; // Size: 0x88

class UCheckBox : public UContentWidget
{
    ECheckBoxState CheckedState;                                                      // 0x0198 (size: 0x1)
    FCheckBoxCheckedStateDelegate CheckedStateDelegate;                               // 0x019C (size: 0x10)
    void GetCheckBoxState();
    FCheckBoxStyle WidgetStyle;                                                       // 0x01B0 (size: 0xAD0)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0C80 (size: 0x1)
    TEnumAsByte<EButtonClickMethod::Type> ClickMethod;                                // 0x0C81 (size: 0x1)
    TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;                                // 0x0C82 (size: 0x1)
    TEnumAsByte<EButtonPressMethod::Type> PressMethod;                                // 0x0C83 (size: 0x1)
    bool IsFocusable;                                                                 // 0x0C84 (size: 0x1)
    FCheckBoxOnCheckStateChanged OnCheckStateChanged;                                 // 0x0C88 (size: 0x10)
    void OnCheckBoxComponentStateChanged(bool bIsChecked);

    void SetTouchMethod(TEnumAsByte<EButtonTouchMethod::Type> InTouchMethod);
    void SetPressMethod(TEnumAsByte<EButtonPressMethod::Type> InPressMethod);
    void SetIsChecked(bool InIsChecked);
    void SetClickMethod(TEnumAsByte<EButtonClickMethod::Type> InClickMethod);
    void SetCheckedState(ECheckBoxState InCheckedState);
    void IsPressed();
    void IsChecked();
    void GetCheckedState();
}; // Size: 0xCB0

class UCheckedStateBinding : public UPropertyBinding
{

    void GetValue();
}; // Size: 0x78

class UCircularThrobber : public UWidget
{
    int32 NumberOfPieces;                                                             // 0x0180 (size: 0x4)
    float Period;                                                                     // 0x0184 (size: 0x4)
    float Radius;                                                                     // 0x0188 (size: 0x4)
    FSlateBrush Image;                                                                // 0x0190 (size: 0xD0)
    bool bEnableRadius;                                                               // 0x0260 (size: 0x1)

    void SetRadius(float InRadius);
    void SetPeriod(float InPeriod);
    void SetNumberOfPieces(int32 InNumberOfPieces);
}; // Size: 0x280

class UColorBinding : public UPropertyBinding
{

    void GetSlateValue();
    void GetLinearValue();
}; // Size: 0x78

class UComboBox : public UWidget
{
    FScrollBarStyle ScrollBarStyle;                                                   // 0x0180 (size: 0x770)
    TArray<UObject*> Items;                                                           // 0x08F0 (size: 0x10)
    FComboBoxOnGenerateWidgetEvent OnGenerateWidgetEvent;                             // 0x0900 (size: 0x10)
    void GenerateWidgetForObject(class UObject* Item);
    bool bIsFocusable;                                                                // 0x0910 (size: 0x1)

}; // Size: 0x930

class UComboBoxKey : public UWidget
{
    TArray<FName> Options;                                                            // 0x0180 (size: 0x10)
    FName SelectedOption;                                                             // 0x0190 (size: 0x8)
    FComboBoxStyle WidgetStyle;                                                       // 0x01A0 (size: 0x660)
    FTableRowStyle ItemStyle;                                                         // 0x0800 (size: 0xD50)
    FScrollBarStyle ScrollBarStyle;                                                   // 0x1550 (size: 0x770)
    FSlateColor ForegroundColor;                                                      // 0x1CC0 (size: 0x14)
    FMargin ContentPadding;                                                           // 0x1CD4 (size: 0x10)
    float MaxListHeight;                                                              // 0x1CE4 (size: 0x4)
    bool bHasDownArrow;                                                               // 0x1CE8 (size: 0x1)
    bool bEnableGamepadNavigationMode;                                                // 0x1CE9 (size: 0x1)
    bool bIsFocusable;                                                                // 0x1CEA (size: 0x1)
    FComboBoxKeyOnGenerateContentWidget OnGenerateContentWidget;                      // 0x1CEC (size: 0x10)
    void GenerateWidgetEvent(FName Item);
    FComboBoxKeyOnGenerateItemWidget OnGenerateItemWidget;                            // 0x1CFC (size: 0x10)
    void GenerateWidgetEvent(FName Item);
    FComboBoxKeyOnSelectionChanged OnSelectionChanged;                                // 0x1D10 (size: 0x10)
    void OnSelectionChangedEvent(FName SelectedItem, TEnumAsByte<ESelectInfo::Type> SelectionType);
    FComboBoxKeyOnOpening OnOpening;                                                  // 0x1D20 (size: 0x10)
    void OnOpeningEvent();

    void SetSelectedOption(FName Option);
    void RemoveOption(FName Option);
    void OnSelectionChangedEvent__DelegateSignature(FName SelectedItem, TEnumAsByte<ESelectInfo::Type> SelectionType);
    void OnOpeningEvent__DelegateSignature();
    void IsOpen();
    void GetSelectedOption();
    void GenerateWidgetEvent__DelegateSignature(FName Item);
    void ClearSelection();
    void ClearOptions();
    void AddOption(FName Option);
}; // Size: 0x1D50

class UComboBoxString : public UWidget
{
    TArray<FString> DefaultOptions;                                                   // 0x0180 (size: 0x10)
    FString SelectedOption;                                                           // 0x0190 (size: 0x10)
    FComboBoxStyle WidgetStyle;                                                       // 0x01A0 (size: 0x660)
    FTableRowStyle ItemStyle;                                                         // 0x0800 (size: 0xD50)
    FScrollBarStyle ScrollBarStyle;                                                   // 0x1550 (size: 0x770)
    FMargin ContentPadding;                                                           // 0x1CC0 (size: 0x10)
    float MaxListHeight;                                                              // 0x1CD0 (size: 0x4)
    bool HasDownArrow;                                                                // 0x1CD4 (size: 0x1)
    bool EnableGamepadNavigationMode;                                                 // 0x1CD5 (size: 0x1)
    FSlateFontInfo Font;                                                              // 0x1CD8 (size: 0x58)
    FSlateColor ForegroundColor;                                                      // 0x1D30 (size: 0x14)
    bool bIsFocusable;                                                                // 0x1D44 (size: 0x1)
    FComboBoxStringOnGenerateWidgetEvent OnGenerateWidgetEvent;                       // 0x1D48 (size: 0x10)
    void GenerateWidgetForString(FString Item);
    FComboBoxStringOnSelectionChanged OnSelectionChanged;                             // 0x1D58 (size: 0x10)
    void OnSelectionChangedEvent(FString SelectedItem, TEnumAsByte<ESelectInfo::Type> SelectionType);
    FComboBoxStringOnOpening OnOpening;                                               // 0x1D68 (size: 0x10)
    void OnOpeningEvent();

    void SetSelectedOption(FString Option);
    void SetSelectedIndex(const int32 Index);
    void RemoveOption(FString Option);
    void RefreshOptions();
    void OnSelectionChangedEvent__DelegateSignature(FString SelectedItem, TEnumAsByte<ESelectInfo::Type> SelectionType);
    void OnOpeningEvent__DelegateSignature();
    void IsOpen();
    void GetSelectedOption();
    void GetSelectedIndex();
    void GetOptionCount();
    void GetOptionAtIndex(int32 Index);
    void FindOptionIndex(FString Option);
    void ClearSelection();
    void ClearOptions();
    void AddOption(FString Option);
}; // Size: 0x1DD0

class UContentWidget : public UPanelWidget
{

    void SetContent(class UWidget* Content);
    void GetContentSlot();
    void GetContent();
}; // Size: 0x198

class UDefault__WidgetBlueprintGeneratedClass
{
}; // Size: 0x0

class UDragDropOperation : public UObject
{
    FString Tag;                                                                      // 0x0028 (size: 0x10)
    class UObject* Payload;                                                           // 0x0038 (size: 0x8)
    class UWidget* DefaultDragVisual;                                                 // 0x0040 (size: 0x8)
    EDragPivot Pivot;                                                                 // 0x0048 (size: 0x1)
    FVector2D Offset;                                                                 // 0x0050 (size: 0x10)
    FDragDropOperationOnDrop OnDrop;                                                  // 0x0060 (size: 0x10)
    void OnDragDropMulticast(class UDragDropOperation* Operation);
    FDragDropOperationOnDragCancelled OnDragCancelled;                                // 0x0070 (size: 0x10)
    void OnDragDropMulticast(class UDragDropOperation* Operation);
    FDragDropOperationOnDragged OnDragged;                                            // 0x0080 (size: 0x10)
    void OnDragDropMulticast(class UDragDropOperation* Operation);

    void Drop(const FPointerEvent& PointerEvent);
    void Dragged(const FPointerEvent& PointerEvent);
    void DragCancelled(const FPointerEvent& PointerEvent);
}; // Size: 0x90

class UDynamicEntryBox : public UDynamicEntryBoxBase
{
    TSubclassOf<class UUserWidget> EntryWidgetClass;                                  // 0x0260 (size: 0x8)

    void Reset(bool bDeleteWidgets);
    void RemoveEntry(class UUserWidget* EntryWidget);
    void BP_CreateEntryOfClass(TSubclassOf<class UUserWidget> EntryClass);
    void BP_CreateEntry();
}; // Size: 0x268

class UDynamicEntryBoxBase : public UWidget
{
    FVector2D EntrySpacing;                                                           // 0x0180 (size: 0x10)
    TArray<FVector2D> SpacingPattern;                                                 // 0x0190 (size: 0x10)
    EDynamicBoxType EntryBoxType;                                                     // 0x01A0 (size: 0x1)
    FSlateChildSize EntrySizeRule;                                                    // 0x01A4 (size: 0x8)
    TEnumAsByte<EHorizontalAlignment> EntryHorizontalAlignment;                       // 0x01AC (size: 0x1)
    TEnumAsByte<EVerticalAlignment> EntryVerticalAlignment;                           // 0x01AD (size: 0x1)
    int32 MaxElementSize;                                                             // 0x01B0 (size: 0x4)
    FRadialBoxSettings RadialBoxSettings;                                             // 0x01B4 (size: 0x10)
    FUserWidgetPool EntryWidgetPool;                                                  // 0x01D8 (size: 0x88)

    void SetRadialSettings(const FRadialBoxSettings& InSettings);
    void SetEntrySpacing(const FVector2D& InEntrySpacing);
    void GetNumEntries();
    void GetAllEntries();
}; // Size: 0x260

class UEditableText : public UWidget
{
    FText Text;                                                                       // 0x0180 (size: 0x18)
    FEditableTextTextDelegate TextDelegate;                                           // 0x0198 (size: 0x10)
    void GetText();
    FText HintText;                                                                   // 0x01A8 (size: 0x18)
    FEditableTextHintTextDelegate HintTextDelegate;                                   // 0x01C0 (size: 0x10)
    void GetText();
    FEditableTextStyle WidgetStyle;                                                   // 0x01D0 (size: 0x2F0)
    bool IsReadOnly;                                                                  // 0x04C0 (size: 0x1)
    bool IsPassword;                                                                  // 0x04C1 (size: 0x1)
    float MinimumDesiredWidth;                                                        // 0x04C4 (size: 0x4)
    bool IsCaretMovedWhenGainFocus;                                                   // 0x04C8 (size: 0x1)
    bool SelectAllTextWhenFocused;                                                    // 0x04C9 (size: 0x1)
    bool RevertTextOnEscape;                                                          // 0x04CA (size: 0x1)
    bool ClearKeyboardFocusOnCommit;                                                  // 0x04CB (size: 0x1)
    bool SelectAllTextOnCommit;                                                       // 0x04CC (size: 0x1)
    bool AllowContextMenu;                                                            // 0x04CD (size: 0x1)
    TEnumAsByte<EVirtualKeyboardType::Type> KeyboardType;                             // 0x04CE (size: 0x1)
    FVirtualKeyboardOptions VirtualKeyboardOptions;                                   // 0x04CF (size: 0x1)
    EVirtualKeyboardTrigger VirtualKeyboardTrigger;                                   // 0x04D0 (size: 0x1)
    EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;                       // 0x04D1 (size: 0x1)
    TEnumAsByte<ETextJustify::Type> Justification;                                    // 0x04D2 (size: 0x1)
    ETextOverflowPolicy OverflowPolicy;                                               // 0x04D3 (size: 0x1)
    FShapedTextOptions ShapedTextOptions;                                             // 0x04D4 (size: 0x3)
    FEditableTextOnTextChanged OnTextChanged;                                         // 0x04D8 (size: 0x10)
    void OnEditableTextChangedEvent(const FText& Text);
    FEditableTextOnTextCommitted OnTextCommitted;                                     // 0x04E8 (size: 0x10)
    void OnEditableTextCommittedEvent(const FText& Text, TEnumAsByte<ETextCommit::Type> CommitMethod);

    void SetTextOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);
    void SetText(FText InText);
    void SetMinimumDesiredWidth(float InMinDesiredWidth);
    void SetJustification(TEnumAsByte<ETextJustify::Type> InJustification);
    void SetIsReadOnly(bool InbIsReadyOnly);
    void SetIsPassword(bool InbIsPassword);
    void SetHintText(FText InHintText);
    void SetFontOutlineMaterial(class UMaterialInterface* InMaterial);
    void SetFontMaterial(class UMaterialInterface* InMaterial);
    void SetFont(FSlateFontInfo InFontInfo);
    void OnEditableTextCommittedEvent__DelegateSignature(const FText& Text, TEnumAsByte<ETextCommit::Type> CommitMethod);
    void OnEditableTextChangedEvent__DelegateSignature(const FText& Text);
    void GetText();
    void GetJustification();
    void GetHintText();
    void GetFont();
}; // Size: 0x510

class UEditableTextBox : public UWidget
{
    FText Text;                                                                       // 0x0180 (size: 0x18)
    FEditableTextBoxTextDelegate TextDelegate;                                        // 0x0198 (size: 0x10)
    void GetText();
    FEditableTextBoxStyle WidgetStyle;                                                // 0x01B0 (size: 0xE80)
    FText HintText;                                                                   // 0x1030 (size: 0x18)
    FEditableTextBoxHintTextDelegate HintTextDelegate;                                // 0x1048 (size: 0x10)
    void GetText();
    bool IsReadOnly;                                                                  // 0x1058 (size: 0x1)
    bool IsPassword;                                                                  // 0x1059 (size: 0x1)
    float MinimumDesiredWidth;                                                        // 0x105C (size: 0x4)
    bool IsCaretMovedWhenGainFocus;                                                   // 0x1060 (size: 0x1)
    bool SelectAllTextWhenFocused;                                                    // 0x1061 (size: 0x1)
    bool RevertTextOnEscape;                                                          // 0x1062 (size: 0x1)
    bool ClearKeyboardFocusOnCommit;                                                  // 0x1063 (size: 0x1)
    bool SelectAllTextOnCommit;                                                       // 0x1064 (size: 0x1)
    bool AllowContextMenu;                                                            // 0x1065 (size: 0x1)
    TEnumAsByte<EVirtualKeyboardType::Type> KeyboardType;                             // 0x1066 (size: 0x1)
    FVirtualKeyboardOptions VirtualKeyboardOptions;                                   // 0x1067 (size: 0x1)
    EVirtualKeyboardTrigger VirtualKeyboardTrigger;                                   // 0x1068 (size: 0x1)
    EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;                       // 0x1069 (size: 0x1)
    TEnumAsByte<ETextJustify::Type> Justification;                                    // 0x106A (size: 0x1)
    ETextOverflowPolicy OverflowPolicy;                                               // 0x106B (size: 0x1)
    FShapedTextOptions ShapedTextOptions;                                             // 0x106C (size: 0x3)
    FEditableTextBoxOnTextChanged OnTextChanged;                                      // 0x1070 (size: 0x10)
    void OnEditableTextBoxChangedEvent(const FText& Text);
    FEditableTextBoxOnTextCommitted OnTextCommitted;                                  // 0x1080 (size: 0x10)
    void OnEditableTextBoxCommittedEvent(const FText& Text, TEnumAsByte<ETextCommit::Type> CommitMethod);

    void SetTextOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);
    void SetText(FText InText);
    void SetJustification(TEnumAsByte<ETextJustify::Type> InJustification);
    void SetIsReadOnly(bool bReadOnly);
    void SetIsPassword(bool bIsPassword);
    void SetHintText(FText InText);
    void SetForegroundColor(FLinearColor Color);
    void SetError(FText InError);
    void OnEditableTextBoxCommittedEvent__DelegateSignature(const FText& Text, TEnumAsByte<ETextCommit::Type> CommitMethod);
    void OnEditableTextBoxChangedEvent__DelegateSignature(const FText& Text);
    void HasError();
    void GetText();
    void ClearError();
}; // Size: 0x10A0

class UExpandableArea : public UWidget
{
    FExpandableAreaStyle Style;                                                       // 0x0190 (size: 0x1C0)
    FSlateBrush BorderBrush;                                                          // 0x0350 (size: 0xD0)
    FSlateColor BorderColor;                                                          // 0x0420 (size: 0x14)
    bool bIsExpanded;                                                                 // 0x0434 (size: 0x1)
    float MaxHeight;                                                                  // 0x0438 (size: 0x4)
    FMargin HeaderPadding;                                                            // 0x043C (size: 0x10)
    FMargin AreaPadding;                                                              // 0x044C (size: 0x10)
    FExpandableAreaOnExpansionChanged OnExpansionChanged;                             // 0x0460 (size: 0x10)
    void OnExpandableAreaExpansionChanged(class UExpandableArea* Area, bool bIsExpanded);
    class UWidget* HeaderContent;                                                     // 0x0470 (size: 0x8)
    class UWidget* BodyContent;                                                       // 0x0478 (size: 0x8)

    void SetIsExpanded_Animated(bool IsExpanded);
    void SetIsExpanded(bool IsExpanded);
    void GetIsExpanded();
}; // Size: 0x490

class UFloatBinding : public UPropertyBinding
{

    void GetValue();
}; // Size: 0x70

class UGameViewportSubsystem : public UEngineSubsystem
{

    void SetWidgetSlotPosition(FGameViewportWidgetSlot Slot, const class UWidget* Widget, FVector2D Position, bool bRemoveDPIScale);
    void SetWidgetSlotDesiredSize(FGameViewportWidgetSlot Slot, FVector2D Size);
    void SetWidgetSlot(class UWidget* Widget, FGameViewportWidgetSlot Slot);
    void RemoveWidget(class UWidget* Widget);
    void IsWidgetAdded(const class UWidget* Widget);
    void GetWidgetSlot(const class UWidget* Widget);
    void AddWidgetForPlayer(class UWidget* Widget, class ULocalPlayer* Player, FGameViewportWidgetSlot Slot);
    void AddWidget(class UWidget* Widget, FGameViewportWidgetSlot Slot);
}; // Size: 0xB0

class UGridPanel : public UPanelWidget
{
    TArray<float> ColumnFill;                                                         // 0x0198 (size: 0x10)
    TArray<float> RowFill;                                                            // 0x01A8 (size: 0x10)

    void SetRowFill(int32 RowIndex, float Coefficient);
    void SetColumnFill(int32 ColumnIndex, float Coefficient);
    void AddChildToGrid(class UWidget* Content, int32 InRow, int32 InColumn);
}; // Size: 0x1C8

class UGridSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0038 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0048 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0049 (size: 0x1)
    int32 Row;                                                                        // 0x004C (size: 0x4)
    int32 RowSpan;                                                                    // 0x0050 (size: 0x4)
    int32 Column;                                                                     // 0x0054 (size: 0x4)
    int32 ColumnSpan;                                                                 // 0x0058 (size: 0x4)
    int32 Layer;                                                                      // 0x005C (size: 0x4)
    FVector2D Nudge;                                                                  // 0x0060 (size: 0x10)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetRowSpan(int32 InRowSpan);
    void SetRow(int32 InRow);
    void SetPadding(FMargin InPadding);
    void SetNudge(FVector2D InNudge);
    void SetLayer(int32 InLayer);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
    void SetColumnSpan(int32 InColumnSpan);
    void SetColumn(int32 InColumn);
}; // Size: 0x78

class UHorizontalBox : public UPanelWidget
{

    void AddChildToHorizontalBox(class UWidget* Content);
}; // Size: 0x1A8

class UHorizontalBoxSlot : public UPanelSlot
{
    FSlateChildSize Size;                                                             // 0x0040 (size: 0x8)
    FMargin Padding;                                                                  // 0x0048 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0058 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0059 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetSize(FSlateChildSize InSize);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x60

class UImage : public UWidget
{
    FSlateBrush Brush;                                                                // 0x0180 (size: 0xD0)
    FImageBrushDelegate BrushDelegate;                                                // 0x0250 (size: 0x10)
    void GetSlateBrush();
    FLinearColor ColorAndOpacity;                                                     // 0x0260 (size: 0x10)
    FImageColorAndOpacityDelegate ColorAndOpacityDelegate;                            // 0x0270 (size: 0x10)
    void GetLinearColor();
    bool bFlipForRightToLeftFlowDirection;                                            // 0x0280 (size: 0x1)
    FImageOnMouseButtonDownEvent OnMouseButtonDownEvent;                              // 0x0284 (size: 0x10)
    void OnPointerEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

    void SetOpacity(float InOpacity);
    void SetDesiredSizeOverride(FVector2D DesiredSize);
    void SetColorAndOpacity(FLinearColor InColorAndOpacity);
    void SetBrushTintColor(FSlateColor TintColor);
    void SetBrushResourceObject(class UObject* ResourceObject);
    void SetBrushFromTextureDynamic(class UTexture2DDynamic* Texture, bool bMatchSize);
    void SetBrushFromTexture(class UTexture2D* Texture, bool bMatchSize);
    void SetBrushFromSoftTexture(TSoftObjectPtr<class UTexture2D> SoftTexture, bool bMatchSize);
    void SetBrushFromSoftMaterial(TSoftObjectPtr<class UMaterialInterface> SoftMaterial);
    void SetBrushFromMaterial(class UMaterialInterface* Material);
    void SetBrushFromAtlasInterface(TScriptInterface<class ISlateTextureAtlasInterface> AtlasRegion, bool bMatchSize);
    void SetBrushFromAsset(class USlateBrushAsset* Asset);
    void SetBrush(const FSlateBrush& InBrush);
    void GetDynamicMaterial();
}; // Size: 0x2E0

class UInputKeySelector : public UWidget
{
    FButtonStyle WidgetStyle;                                                         // 0x0180 (size: 0x3F0)
    FTextBlockStyle TextStyle;                                                        // 0x0570 (size: 0x340)
    FInputChord SelectedKey;                                                          // 0x08B0 (size: 0x20)
    FMargin Margin;                                                                   // 0x08D0 (size: 0x10)
    FText KeySelectionText;                                                           // 0x08E0 (size: 0x18)
    FText NoKeySpecifiedText;                                                         // 0x08F8 (size: 0x18)
    bool bAllowModifierKeys;                                                          // 0x0910 (size: 0x1)
    bool bAllowGamepadKeys;                                                           // 0x0911 (size: 0x1)
    TArray<FKey> EscapeKeys;                                                          // 0x0918 (size: 0x10)
    FInputKeySelectorOnKeySelected OnKeySelected;                                     // 0x0928 (size: 0x10)
    void OnKeySelected(FInputChord SelectedKey);
    FInputKeySelectorOnIsSelectingKeyChanged OnIsSelectingKeyChanged;                 // 0x0938 (size: 0x10)
    void OnIsSelectingKeyChanged();

    void SetTextBlockVisibility(const ESlateVisibility InVisibility);
    void SetSelectedKey(const FInputChord& InSelectedKey);
    void SetNoKeySpecifiedText(FText InNoKeySpecifiedText);
    void SetKeySelectionText(FText InKeySelectionText);
    void SetEscapeKeys(const TArray<FKey>& InKeys);
    void SetAllowModifierKeys(bool bInAllowModifierKeys);
    void SetAllowGamepadKeys(bool bInAllowGamepadKeys);
    void OnKeySelected__DelegateSignature(FInputChord SelectedKey);
    void OnIsSelectingKeyChanged__DelegateSignature();
    void GetIsSelectingKey();
}; // Size: 0x960

class UInt32Binding : public UPropertyBinding
{

    void GetValue();
}; // Size: 0x70

class UInvalidationBox : public UContentWidget
{
    bool bCanCache;                                                                   // 0x0198 (size: 0x1)

    void SetCanCache(bool CanCache);
    void InvalidateCache();
    void GetCanCache();
}; // Size: 0x1B0

class UListView : public UListViewBase
{
    FTableViewStyle WidgetStyle;                                                      // 0x0380 (size: 0xE0)
    FScrollBarStyle ScrollBarStyle;                                                   // 0x0460 (size: 0x770)
    TEnumAsByte<EOrientation> Orientation;                                            // 0x0BD0 (size: 0x1)
    TEnumAsByte<ESelectionMode::Type> SelectionMode;                                  // 0x0BD1 (size: 0x1)
    EConsumeMouseWheel ConsumeMouseWheel;                                             // 0x0BD2 (size: 0x1)
    bool bClearSelectionOnClick;                                                      // 0x0BD3 (size: 0x1)
    bool bIsFocusable;                                                                // 0x0BD4 (size: 0x1)
    bool bReturnFocusToSelection;                                                     // 0x0BD5 (size: 0x1)
    TArray<UObject*> ListItems;                                                       // 0x0BD8 (size: 0x10)
    float HorizontalEntrySpacing;                                                     // 0x0BF8 (size: 0x4)
    float VerticalEntrySpacing;                                                       // 0x0BFC (size: 0x4)
    FListViewBP_OnEntryInitialized BP_OnEntryInitialized;                             // 0x0C00 (size: 0x10)
    void OnListEntryInitializedDynamic(class UObject* Item, class UUserWidget* Widget);
    FListViewBP_OnItemClicked BP_OnItemClicked;                                       // 0x0C10 (size: 0x10)
    void SimpleListItemEventDynamic(class UObject* Item);
    FListViewBP_OnItemDoubleClicked BP_OnItemDoubleClicked;                           // 0x0C20 (size: 0x10)
    void SimpleListItemEventDynamic(class UObject* Item);
    FListViewBP_OnItemIsHoveredChanged BP_OnItemIsHoveredChanged;                     // 0x0C30 (size: 0x10)
    void OnItemIsHoveredChangedDynamic(class UObject* Item, bool bIsHovered);
    FListViewBP_OnItemSelectionChanged BP_OnItemSelectionChanged;                     // 0x0C40 (size: 0x10)
    void OnListItemSelectionChangedDynamic(class UObject* Item, bool bIsSelected);
    FListViewBP_OnItemScrolledIntoView BP_OnItemScrolledIntoView;                     // 0x0C50 (size: 0x10)
    void OnListItemScrolledIntoViewDynamic(class UObject* Item, class UUserWidget* Widget);
    FListViewBP_OnListViewScrolled BP_OnListViewScrolled;                             // 0x0C60 (size: 0x10)
    void OnListViewScrolledDynamic(float ItemOffset, float DistanceRemaining);

    void SetSelectionMode(TEnumAsByte<ESelectionMode::Type> SelectionMode);
    void SetSelectedIndex(int32 Index);
    void ScrollIndexIntoView(int32 Index);
    void RemoveItem(class UObject* Item);
    void OnListItemOuterEndPlayed(class AActor* ItemOuter, TEnumAsByte<EEndPlayReason::Type> EndPlayReason);
    void OnListItemEndPlayed(class AActor* Item, TEnumAsByte<EEndPlayReason::Type> EndPlayReason);
    void NavigateToIndex(int32 Index);
    void IsRefreshPending();
    void GetVerticalEntrySpacing();
    void GetNumItems();
    void GetListItems();
    void GetItemAt(int32 Index);
    void GetIndexForItem(const class UObject* Item);
    void GetHorizontalEntrySpacing();
    void ClearListItems();
    void BP_SetSelectedItem(class UObject* Item);
    void BP_SetListItems(const TArray<UObject*>& InListItems);
    void BP_SetItemSelection(class UObject* Item, bool bSelected);
    void BP_ScrollItemIntoView(class UObject* Item);
    void BP_NavigateToItem(class UObject* Item);
    void BP_IsItemVisible(class UObject* Item);
    void BP_GetSelectedItems(TArray<UObject*>& Items);
    void BP_GetSelectedItem();
    void BP_GetNumItemsSelected();
    void BP_ClearSelection();
    void BP_CancelScrollIntoView();
    void AddItem(class UObject* Item);
}; // Size: 0xC70

class UListViewBase : public UWidget
{
    FListViewBaseBP_OnEntryGenerated BP_OnEntryGenerated;                             // 0x0180 (size: 0x10)
    void OnListEntryGeneratedDynamic(class UUserWidget* Widget);
    TSubclassOf<class UUserWidget> EntryWidgetClass;                                  // 0x01A0 (size: 0x8)
    float WheelScrollMultiplier;                                                      // 0x01A8 (size: 0x4)
    bool bEnableScrollAnimation;                                                      // 0x01AC (size: 0x1)
    bool AllowOverscroll;                                                             // 0x01AD (size: 0x1)
    bool bEnableRightClickScrolling;                                                  // 0x01AE (size: 0x1)
    bool bEnableFixedLineOffset;                                                      // 0x01AF (size: 0x1)
    float FixedLineScrollOffset;                                                      // 0x01B0 (size: 0x4)
    bool bAllowDragging;                                                              // 0x01B4 (size: 0x1)
    FListViewBaseBP_OnEntryReleased BP_OnEntryReleased;                               // 0x01B8 (size: 0x10)
    void OnListEntryReleasedDynamic(class UUserWidget* Widget);
    FUserWidgetPool EntryWidgetPool;                                                  // 0x01C8 (size: 0x88)

    void SetWheelScrollMultiplier(float NewWheelScrollMultiplier);
    void SetScrollOffset(const float InScrollOffset);
    void SetScrollbarVisibility(ESlateVisibility InVisibility);
    void ScrollToTop();
    void ScrollToBottom();
    void RequestRefresh();
    void RegenerateAllEntries();
    void GetScrollOffset();
    void GetDisplayedEntryWidgets();
}; // Size: 0x298

class UListViewDesignerPreviewItem : public UObject
{
}; // Size: 0x28

class UMenuAnchor : public UContentWidget
{
    TSubclassOf<class UUserWidget> MenuClass;                                         // 0x0198 (size: 0x8)
    FMenuAnchorOnGetMenuContentEvent OnGetMenuContentEvent;                           // 0x01A0 (size: 0x10)
    void GetWidget();
    FMenuAnchorOnGetUserMenuContentEvent OnGetUserMenuContentEvent;                   // 0x01B0 (size: 0x10)
    void GetUserWidget();
    TEnumAsByte<EMenuPlacement> Placement;                                            // 0x01C0 (size: 0x1)
    bool bFitInWindow;                                                                // 0x01C1 (size: 0x1)
    bool ShouldDeferPaintingAfterWindowContent;                                       // 0x01C2 (size: 0x1)
    bool UseApplicationMenuStack;                                                     // 0x01C3 (size: 0x1)
    FMenuAnchorOnMenuOpenChanged OnMenuOpenChanged;                                   // 0x01C8 (size: 0x10)
    void OnMenuOpenChangedEvent(bool bIsOpen);

    void ToggleOpen(bool bFocusOnOpen);
    void ShouldOpenDueToClick();
    void SetPlacement(TEnumAsByte<EMenuPlacement> InPlacement);
    void Open(bool bFocusMenu);
    void IsOpen();
    void HasOpenSubMenus();
    void GetUserWidget__DelegateSignature();
    void GetMenuPosition();
    void FitInWindow(bool bFit);
    void Close();
}; // Size: 0x1E8

class UMouseCursorBinding : public UPropertyBinding
{

    void GetValue();
}; // Size: 0x70

class UMovieScene2DTransformPropertySystem : public UMovieScenePropertySystem
{
}; // Size: 0x58

class UMovieScene2DTransformSection : public UMovieSceneSection
{
    FMovieScene2DTransformMask TransformMask;                                         // 0x00F8 (size: 0x4)
    FMovieSceneFloatChannel Translation;                                              // 0x0100 (size: 0x220)
    FMovieSceneFloatChannel Rotation;                                                 // 0x0320 (size: 0x110)
    FMovieSceneFloatChannel Scale;                                                    // 0x0430 (size: 0x220)
    FMovieSceneFloatChannel Shear;                                                    // 0x0650 (size: 0x220)

}; // Size: 0x870

class UMovieScene2DTransformTrack : public UMovieScenePropertyTrack
{
}; // Size: 0xC8

class UMovieSceneMarginPropertySystem : public UMovieScenePropertySystem
{
}; // Size: 0x58

class UMovieSceneMarginSection : public UMovieSceneSection
{
    FMovieSceneFloatChannel TopCurve;                                                 // 0x00F8 (size: 0x110)
    FMovieSceneFloatChannel LeftCurve;                                                // 0x0208 (size: 0x110)
    FMovieSceneFloatChannel RightCurve;                                               // 0x0318 (size: 0x110)
    FMovieSceneFloatChannel BottomCurve;                                              // 0x0428 (size: 0x110)

}; // Size: 0x538

class UMovieSceneMarginTrack : public UMovieScenePropertyTrack
{
}; // Size: 0xC8

class UMovieSceneWidgetMaterialSystem : public UMovieSceneEntitySystem
{
}; // Size: 0x1A0

class UMovieSceneWidgetMaterialTrack : public UMovieSceneMaterialTrack
{
    TArray<FName> BrushPropertyNamePath;                                              // 0x00C0 (size: 0x10)
    FName TrackName;                                                                  // 0x00D0 (size: 0x8)

}; // Size: 0xD8

class UMultiLineEditableText : public UTextLayoutWidget
{
    FText Text;                                                                       // 0x01A0 (size: 0x18)
    FText HintText;                                                                   // 0x01B8 (size: 0x18)
    FMultiLineEditableTextHintTextDelegate HintTextDelegate;                          // 0x01D0 (size: 0x10)
    void GetText();
    FTextBlockStyle WidgetStyle;                                                      // 0x01E0 (size: 0x340)
    bool bIsReadOnly;                                                                 // 0x0520 (size: 0x1)
    bool SelectAllTextWhenFocused;                                                    // 0x0521 (size: 0x1)
    bool ClearTextSelectionOnFocusLoss;                                               // 0x0522 (size: 0x1)
    bool RevertTextOnEscape;                                                          // 0x0523 (size: 0x1)
    bool ClearKeyboardFocusOnCommit;                                                  // 0x0524 (size: 0x1)
    bool AllowContextMenu;                                                            // 0x0525 (size: 0x1)
    FVirtualKeyboardOptions VirtualKeyboardOptions;                                   // 0x0526 (size: 0x1)
    EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;                       // 0x0527 (size: 0x1)
    FMultiLineEditableTextOnTextChanged OnTextChanged;                                // 0x0528 (size: 0x10)
    void OnMultiLineEditableTextChangedEvent(const FText& Text);
    FMultiLineEditableTextOnTextCommitted OnTextCommitted;                            // 0x0538 (size: 0x10)
    void OnMultiLineEditableTextCommittedEvent(const FText& Text, TEnumAsByte<ETextCommit::Type> CommitMethod);

    void SetWidgetStyle(const FTextBlockStyle& InWidgetStyle);
    void SetText(FText InText);
    void SetIsReadOnly(bool bReadOnly);
    void SetHintText(FText InHintText);
    void SetFontOutlineMaterial(class UMaterialInterface* InMaterial);
    void SetFontMaterial(class UMaterialInterface* InMaterial);
    void SetFont(FSlateFontInfo InFontInfo);
    void OnMultiLineEditableTextCommittedEvent__DelegateSignature(const FText& Text, TEnumAsByte<ETextCommit::Type> CommitMethod);
    void OnMultiLineEditableTextChangedEvent__DelegateSignature(const FText& Text);
    void GetText();
    void GetHintText();
    void GetFont();
}; // Size: 0x560

class UMultiLineEditableTextBox : public UTextLayoutWidget
{
    FText Text;                                                                       // 0x01A0 (size: 0x18)
    FText HintText;                                                                   // 0x01B8 (size: 0x18)
    FMultiLineEditableTextBoxHintTextDelegate HintTextDelegate;                       // 0x01D0 (size: 0x10)
    void GetText();
    FEditableTextBoxStyle WidgetStyle;                                                // 0x01E0 (size: 0xE80)
    bool bIsReadOnly;                                                                 // 0x1060 (size: 0x1)
    bool AllowContextMenu;                                                            // 0x1061 (size: 0x1)
    FVirtualKeyboardOptions VirtualKeyboardOptions;                                   // 0x1062 (size: 0x1)
    EVirtualKeyboardDismissAction VirtualKeyboardDismissAction;                       // 0x1063 (size: 0x1)
    FMultiLineEditableTextBoxOnTextChanged OnTextChanged;                             // 0x1068 (size: 0x10)
    void OnMultiLineEditableTextBoxChangedEvent(const FText& Text);
    FMultiLineEditableTextBoxOnTextCommitted OnTextCommitted;                         // 0x1078 (size: 0x10)
    void OnMultiLineEditableTextBoxCommittedEvent(const FText& Text, TEnumAsByte<ETextCommit::Type> CommitMethod);

    void SetTextStyle(const FTextBlockStyle& InTextStyle);
    void SetText(FText InText);
    void SetIsReadOnly(bool bReadOnly);
    void SetHintText(FText InHintText);
    void SetForegroundColor(FLinearColor Color);
    void SetError(FText InError);
    void OnMultiLineEditableTextBoxCommittedEvent__DelegateSignature(const FText& Text, TEnumAsByte<ETextCommit::Type> CommitMethod);
    void OnMultiLineEditableTextBoxChangedEvent__DelegateSignature(const FText& Text);
    void GetText();
    void GetHintText();
}; // Size: 0x10A0

class UNamedSlot : public UContentWidget
{
}; // Size: 0x1A8

class UNativeWidgetHost : public UWidget
{
}; // Size: 0x190

class UOverlay : public UPanelWidget
{

    void ReplaceOverlayChildAt(int32 Index, class UWidget* Content);
    void AddChildToOverlay(class UWidget* Content);
}; // Size: 0x1A8

class UOverlaySlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0040 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0050 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0051 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x58

class UPanelSlot : public UVisual
{
    class UPanelWidget* Parent;                                                       // 0x0028 (size: 0x8)
    class UWidget* Content;                                                           // 0x0030 (size: 0x8)

}; // Size: 0x38

class UPanelWidget : public UWidget
{
    TArray<UPanelSlot*> Slots;                                                        // 0x0180 (size: 0x10)

    void RemoveChildAt(int32 Index);
    void RemoveChild(class UWidget* Content);
    void HasChild(class UWidget* Content);
    void HasAnyChildren();
    void GetChildrenCount();
    void GetChildIndex(const class UWidget* Content);
    void GetChildAt(int32 Index);
    void GetAllChildren();
    void ClearChildren();
    void AddChild(class UWidget* Content);
}; // Size: 0x198

class UProgressBar : public UWidget
{
    FProgressBarStyle WidgetStyle;                                                    // 0x0180 (size: 0x290)
    float Percent;                                                                    // 0x0410 (size: 0x4)
    TEnumAsByte<EProgressBarFillType::Type> BarFillType;                              // 0x0414 (size: 0x1)
    TEnumAsByte<EProgressBarFillStyle::Type> BarFillStyle;                            // 0x0415 (size: 0x1)
    bool bIsMarquee;                                                                  // 0x0416 (size: 0x1)
    FVector2D BorderPadding;                                                          // 0x0418 (size: 0x10)
    FProgressBarPercentDelegate PercentDelegate;                                      // 0x0428 (size: 0x10)
    void GetFloat();
    FLinearColor FillColorAndOpacity;                                                 // 0x0438 (size: 0x10)
    FProgressBarFillColorAndOpacityDelegate FillColorAndOpacityDelegate;              // 0x0448 (size: 0x10)
    void GetLinearColor();

    void SetPercent(float InPercent);
    void SetIsMarquee(bool InbIsMarquee);
    void SetFillColorAndOpacity(FLinearColor InColor);
}; // Size: 0x470

class UPropertyBinding : public UObject
{
    TWeakObjectPtr<class UObject> SourceObject;                                       // 0x0028 (size: 0x8)
    FDynamicPropertyPath SourcePath;                                                  // 0x0030 (size: 0x38)
    FName DestinationProperty;                                                        // 0x0068 (size: 0x8)

}; // Size: 0x70

class URetainerBox : public UContentWidget
{
    bool bRetainRender;                                                               // 0x0198 (size: 0x1)
    bool RenderOnInvalidation;                                                        // 0x0199 (size: 0x1)
    bool RenderOnPhase;                                                               // 0x019A (size: 0x1)
    int32 Phase;                                                                      // 0x019C (size: 0x4)
    int32 PhaseCount;                                                                 // 0x01A0 (size: 0x4)
    class UMaterialInterface* EffectMaterial;                                         // 0x01A8 (size: 0x8)
    FName TextureParameter;                                                           // 0x01B0 (size: 0x8)

    void SetTextureParameter(FName TextureParameter);
    void SetRetainRendering(bool bInRetainRendering);
    void SetRenderingPhase(int32 RenderPhase, int32 TotalPhases);
    void SetEffectMaterial(class UMaterialInterface* EffectMaterial);
    void RequestRender();
    void GetEffectMaterial();
}; // Size: 0x1C8

class URichTextBlock : public UTextLayoutWidget
{
    FText Text;                                                                       // 0x01A0 (size: 0x18)
    class UDataTable* TextStyleSet;                                                   // 0x01B8 (size: 0x8)
    TArray<TSubclassOf<class URichTextBlockDecorator>> DecoratorClasses;              // 0x01C0 (size: 0x10)
    bool bOverrideDefaultStyle;                                                       // 0x01D0 (size: 0x1)
    FTextBlockStyle DefaultTextStyleOverride;                                         // 0x01E0 (size: 0x340)
    float MinDesiredWidth;                                                            // 0x0520 (size: 0x4)
    ETextTransformPolicy TextTransformPolicy;                                         // 0x0524 (size: 0x1)
    ETextOverflowPolicy TextOverflowPolicy;                                           // 0x0525 (size: 0x1)
    FTextBlockStyle DefaultTextStyle;                                                 // 0x0530 (size: 0x340)
    TArray<URichTextBlockDecorator*> InstanceDecorators;                              // 0x0870 (size: 0x10)

    void SetTextTransformPolicy(ETextTransformPolicy InTransformPolicy);
    void SetTextStyleSet(class UDataTable* NewTextStyleSet);
    void SetTextOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);
    void SetText(const FText& InText);
    void SetMinDesiredWidth(float InMinDesiredWidth);
    void SetDefaultTextStyle(const FTextBlockStyle& InDefaultTextStyle);
    void SetDefaultStrikeBrush(const FSlateBrush& InStrikeBrush);
    void SetDefaultShadowOffset(FVector2D InShadowOffset);
    void SetDefaultShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity);
    void SetDefaultMaterial(class UMaterialInterface* InMaterial);
    void SetDefaultFont(FSlateFontInfo InFontInfo);
    void SetDefaultColorAndOpacity(FSlateColor InColorAndOpacity);
    void SetDecorators(const TArray<TSubclassOf<class URichTextBlockDecorator>>& InDecoratorClasses);
    void SetAutoWrapText(bool InAutoTextWrap);
    void RefreshTextLayout();
    void GetTextStyleSet();
    void GetText();
    void GetDefaultDynamicMaterial();
    void GetDecoratorByClass(TSubclassOf<class URichTextBlockDecorator> DecoratorClass);
    void ClearAllDefaultStyleOverrides();
}; // Size: 0x8A0

class URichTextBlockDecorator : public UObject
{
}; // Size: 0x28

class URichTextBlockImageDecorator : public URichTextBlockDecorator
{
    class UDataTable* ImageSet;                                                       // 0x0028 (size: 0x8)

}; // Size: 0x30

class USafeZone : public UContentWidget
{
    bool PadLeft;                                                                     // 0x0198 (size: 0x1)
    bool PadRight;                                                                    // 0x0199 (size: 0x1)
    bool PadTop;                                                                      // 0x019A (size: 0x1)
    bool PadBottom;                                                                   // 0x019B (size: 0x1)

    void SetSidesToPad(bool InPadLeft, bool InPadRight, bool InPadTop, bool InPadBottom);
}; // Size: 0x1B0

class USafeZoneSlot : public UPanelSlot
{
    bool bIsTitleSafe;                                                                // 0x0038 (size: 0x1)
    FMargin SafeAreaScale;                                                            // 0x003C (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HAlign;                                         // 0x004C (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VAlign;                                           // 0x004D (size: 0x1)
    FMargin Padding;                                                                  // 0x0050 (size: 0x10)

}; // Size: 0x70

class UScaleBox : public UContentWidget
{
    TEnumAsByte<EStretch::Type> Stretch;                                              // 0x0198 (size: 0x1)
    TEnumAsByte<EStretchDirection::Type> StretchDirection;                            // 0x0199 (size: 0x1)
    float UserSpecifiedScale;                                                         // 0x019C (size: 0x4)
    bool IgnoreInheritedScale;                                                        // 0x01A0 (size: 0x1)

    void SetUserSpecifiedScale(float InUserSpecifiedScale);
    void SetStretchDirection(TEnumAsByte<EStretchDirection::Type> InStretchDirection);
    void SetStretch(TEnumAsByte<EStretch::Type> InStretch);
    void SetIgnoreInheritedScale(bool bInIgnoreInheritedScale);
}; // Size: 0x1B8

class UScaleBoxSlot : public UPanelSlot
{
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0038 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0039 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x50

class UScrollBar : public UWidget
{
    FScrollBarStyle WidgetStyle;                                                      // 0x0180 (size: 0x770)
    bool bAlwaysShowScrollbar;                                                        // 0x08F0 (size: 0x1)
    bool bAlwaysShowScrollbarTrack;                                                   // 0x08F1 (size: 0x1)
    TEnumAsByte<EOrientation> Orientation;                                            // 0x08F2 (size: 0x1)
    FVector2D Thickness;                                                              // 0x08F8 (size: 0x10)
    FMargin Padding;                                                                  // 0x0908 (size: 0x10)

    void SetState(float InOffsetFraction, float InThumbSizeFraction);
}; // Size: 0x930

class UScrollBox : public UPanelWidget
{
    FScrollBoxStyle WidgetStyle;                                                      // 0x01A0 (size: 0x370)
    FScrollBarStyle WidgetBarStyle;                                                   // 0x0510 (size: 0x770)
    TEnumAsByte<EOrientation> Orientation;                                            // 0x0C80 (size: 0x1)
    ESlateVisibility ScrollBarVisibility;                                             // 0x0C81 (size: 0x1)
    EConsumeMouseWheel ConsumeMouseWheel;                                             // 0x0C82 (size: 0x1)
    FVector2D ScrollbarThickness;                                                     // 0x0C88 (size: 0x10)
    FMargin ScrollbarPadding;                                                         // 0x0C98 (size: 0x10)
    bool AlwaysShowScrollbar;                                                         // 0x0CA8 (size: 0x1)
    bool AlwaysShowScrollbarTrack;                                                    // 0x0CA9 (size: 0x1)
    bool AllowOverscroll;                                                             // 0x0CAA (size: 0x1)
    bool BackPadScrolling;                                                            // 0x0CAB (size: 0x1)
    bool FrontPadScrolling;                                                           // 0x0CAC (size: 0x1)
    bool bAnimateWheelScrolling;                                                      // 0x0CAD (size: 0x1)
    EDescendantScrollDestination NavigationDestination;                               // 0x0CAE (size: 0x1)
    float NavigationScrollPadding;                                                    // 0x0CB0 (size: 0x4)
    EScrollWhenFocusChanges ScrollWhenFocusChanges;                                   // 0x0CB4 (size: 0x1)
    bool bAllowRightClickDragScrolling;                                               // 0x0CB5 (size: 0x1)
    float WheelScrollMultiplier;                                                      // 0x0CB8 (size: 0x4)
    FScrollBoxOnUserScrolled OnUserScrolled;                                          // 0x0CC0 (size: 0x10)
    void OnUserScrolledEvent(float CurrentOffset);

    void SetWheelScrollMultiplier(float NewWheelScrollMultiplier);
    void SetScrollWhenFocusChanges(EScrollWhenFocusChanges NewScrollWhenFocusChanges);
    void SetScrollOffset(float NewScrollOffset);
    void SetScrollbarVisibility(ESlateVisibility NewScrollBarVisibility);
    void SetScrollbarThickness(const FVector2D& NewScrollbarThickness);
    void SetScrollbarPadding(const FMargin& NewScrollbarPadding);
    void SetOrientation(TEnumAsByte<EOrientation> NewOrientation);
    void SetNavigationDestination(const EDescendantScrollDestination NewNavigationDestination);
    void SetConsumeMouseWheel(EConsumeMouseWheel NewConsumeMouseWheel);
    void SetAnimateWheelScrolling(bool bShouldAnimateWheelScrolling);
    void SetAlwaysShowScrollbar(bool NewAlwaysShowScrollbar);
    void SetAllowOverscroll(bool NewAllowOverscroll);
    void ScrollWidgetIntoView(class UWidget* WidgetToFind, bool AnimateScroll, EDescendantScrollDestination ScrollDestination, float Padding);
    void ScrollToStart();
    void ScrollToEnd();
    void GetViewOffsetFraction();
    void GetViewFraction();
    void GetScrollOffsetOfEnd();
    void GetScrollOffset();
    void EndInertialScrolling();
}; // Size: 0xCF0

class UScrollBoxSlot : public UPanelSlot
{
    FSlateChildSize Size;                                                             // 0x0038 (size: 0x8)
    FMargin Padding;                                                                  // 0x0040 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0050 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0051 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x60

class USizeBox : public UContentWidget
{
    float WidthOverride;                                                              // 0x01A8 (size: 0x4)
    float HeightOverride;                                                             // 0x01AC (size: 0x4)
    float MinDesiredWidth;                                                            // 0x01B0 (size: 0x4)
    float MinDesiredHeight;                                                           // 0x01B4 (size: 0x4)
    float MaxDesiredWidth;                                                            // 0x01B8 (size: 0x4)
    float MaxDesiredHeight;                                                           // 0x01BC (size: 0x4)
    float MinAspectRatio;                                                             // 0x01C0 (size: 0x4)
    float MaxAspectRatio;                                                             // 0x01C4 (size: 0x4)
    uint8 bOverride_WidthOverride;                                                    // 0x01C8 (size: 0x1)
    uint8 bOverride_HeightOverride;                                                   // 0x01C8 (size: 0x1)
    uint8 bOverride_MinDesiredWidth;                                                  // 0x01C8 (size: 0x1)
    uint8 bOverride_MinDesiredHeight;                                                 // 0x01C8 (size: 0x1)
    uint8 bOverride_MaxDesiredWidth;                                                  // 0x01C8 (size: 0x1)
    uint8 bOverride_MaxDesiredHeight;                                                 // 0x01C8 (size: 0x1)
    uint8 bOverride_MinAspectRatio;                                                   // 0x01C8 (size: 0x1)
    uint8 bOverride_MaxAspectRatio;                                                   // 0x01C8 (size: 0x1)

    void SetWidthOverride(float InWidthOverride);
    void SetMinDesiredWidth(float InMinDesiredWidth);
    void SetMinDesiredHeight(float InMinDesiredHeight);
    void SetMinAspectRatio(float InMinAspectRatio);
    void SetMaxDesiredWidth(float InMaxDesiredWidth);
    void SetMaxDesiredHeight(float InMaxDesiredHeight);
    void SetMaxAspectRatio(float InMaxAspectRatio);
    void SetHeightOverride(float InHeightOverride);
    void ClearWidthOverride();
    void ClearMinDesiredWidth();
    void ClearMinDesiredHeight();
    void ClearMinAspectRatio();
    void ClearMaxDesiredWidth();
    void ClearMaxDesiredHeight();
    void ClearMaxAspectRatio();
    void ClearHeightOverride();
}; // Size: 0x1D0

class USizeBoxSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0038 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0058 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0059 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x60

class USlateAccessibleWidgetData : public UObject
{
    bool bCanChildrenBeAccessible;                                                    // 0x0028 (size: 0x1)
    ESlateAccessibleBehavior AccessibleBehavior;                                      // 0x0029 (size: 0x1)
    ESlateAccessibleBehavior AccessibleSummaryBehavior;                               // 0x002A (size: 0x1)
    FText AccessibleText;                                                             // 0x0030 (size: 0x18)
    FSlateAccessibleWidgetDataAccessibleTextDelegate AccessibleTextDelegate;          // 0x0048 (size: 0x10)
    void GetText();
    FText AccessibleSummaryText;                                                      // 0x0058 (size: 0x18)
    FSlateAccessibleWidgetDataAccessibleSummaryTextDelegate AccessibleSummaryTextDelegate; // 0x0070 (size: 0x10)
    void GetText();

}; // Size: 0x80

class USlateBlueprintLibrary : public UBlueprintFunctionLibrary
{

    void TransformVectorLocalToAbsolute(const FGeometry& Geometry, FVector2D LocalVector);
    void TransformVectorAbsoluteToLocal(const FGeometry& Geometry, FVector2D AbsoluteVector);
    void TransformScalarLocalToAbsolute(const FGeometry& Geometry, float LocalScalar);
    void TransformScalarAbsoluteToLocal(const FGeometry& Geometry, float AbsoluteScalar);
    void ScreenToWidgetLocal(class UObject* WorldContextObject, const FGeometry& Geometry, FVector2D ScreenPosition, FVector2D& LocalCoordinate, bool bIncludeWindowPosition);
    void ScreenToWidgetAbsolute(class UObject* WorldContextObject, FVector2D ScreenPosition, FVector2D& AbsoluteCoordinate, bool bIncludeWindowPosition);
    void ScreenToViewport(class UObject* WorldContextObject, FVector2D ScreenPosition, FVector2D& ViewportPosition);
    void LocalToViewport(class UObject* WorldContextObject, const FGeometry& Geometry, FVector2D LocalCoordinate, FVector2D& PixelPosition, FVector2D& ViewportPosition);
    void LocalToAbsolute(const FGeometry& Geometry, FVector2D LocalCoordinate);
    void IsUnderLocation(const FGeometry& Geometry, const FVector2D& AbsoluteCoordinate);
    void GetLocalTopLeft(const FGeometry& Geometry);
    void GetLocalSize(const FGeometry& Geometry);
    void GetAbsoluteSize(const FGeometry& Geometry);
    void EqualEqual_SlateBrush(const FSlateBrush& A, const FSlateBrush& B);
    void AbsoluteToViewport(class UObject* WorldContextObject, FVector2D AbsoluteDesktopCoordinate, FVector2D& PixelPosition, FVector2D& ViewportPosition);
    void AbsoluteToLocal(const FGeometry& Geometry, FVector2D AbsoluteCoordinate);
}; // Size: 0x28

class USlateVectorArtData : public UObject
{
    TArray<FSlateMeshVertex> VertexData;                                              // 0x0028 (size: 0x10)
    TArray<uint32> IndexData;                                                         // 0x0038 (size: 0x10)
    class UMaterialInterface* Material;                                               // 0x0048 (size: 0x8)
    FVector2D ExtentMin;                                                              // 0x0050 (size: 0x10)
    FVector2D ExtentMax;                                                              // 0x0060 (size: 0x10)

}; // Size: 0x70

class USlider : public UWidget
{
    float Value;                                                                      // 0x0180 (size: 0x4)
    FSliderValueDelegate ValueDelegate;                                               // 0x0184 (size: 0x10)
    void GetFloat();
    float MinValue;                                                                   // 0x0194 (size: 0x4)
    float MaxValue;                                                                   // 0x0198 (size: 0x4)
    FSliderStyle WidgetStyle;                                                         // 0x01A0 (size: 0x500)
    TEnumAsByte<EOrientation> Orientation;                                            // 0x06A0 (size: 0x1)
    FLinearColor SliderBarColor;                                                      // 0x06A4 (size: 0x10)
    FLinearColor SliderHandleColor;                                                   // 0x06B4 (size: 0x10)
    bool IndentHandle;                                                                // 0x06C4 (size: 0x1)
    bool Locked;                                                                      // 0x06C5 (size: 0x1)
    bool MouseUsesStep;                                                               // 0x06C6 (size: 0x1)
    bool RequiresControllerLock;                                                      // 0x06C7 (size: 0x1)
    float StepSize;                                                                   // 0x06C8 (size: 0x4)
    bool IsFocusable;                                                                 // 0x06CC (size: 0x1)
    FSliderOnMouseCaptureBegin OnMouseCaptureBegin;                                   // 0x06D0 (size: 0x10)
    void OnMouseCaptureBeginEvent();
    FSliderOnMouseCaptureEnd OnMouseCaptureEnd;                                       // 0x06E0 (size: 0x10)
    void OnMouseCaptureEndEvent();
    FSliderOnControllerCaptureBegin OnControllerCaptureBegin;                         // 0x06F0 (size: 0x10)
    void OnControllerCaptureBeginEvent();
    FSliderOnControllerCaptureEnd OnControllerCaptureEnd;                             // 0x0700 (size: 0x10)
    void OnControllerCaptureEndEvent();
    FSliderOnValueChanged OnValueChanged;                                             // 0x0710 (size: 0x10)
    void OnFloatValueChangedEvent(float Value);

    void SetValue(float InValue);
    void SetStepSize(float InValue);
    void SetSliderHandleColor(FLinearColor InValue);
    void SetSliderBarColor(FLinearColor InValue);
    void SetMinValue(float InValue);
    void SetMaxValue(float InValue);
    void SetLocked(bool InValue);
    void SetIndentHandle(bool InValue);
    void GetValue();
    void GetNormalizedValue();
}; // Size: 0x730

class USpacer : public UWidget
{
    FVector2D Size;                                                                   // 0x0180 (size: 0x10)

    void SetSize(FVector2D InSize);
}; // Size: 0x1A0

class USpinBox : public UWidget
{
    float Value;                                                                      // 0x0180 (size: 0x4)
    FSpinBoxValueDelegate ValueDelegate;                                              // 0x0184 (size: 0x10)
    void GetFloat();
    FSpinBoxStyle WidgetStyle;                                                        // 0x01A0 (size: 0x600)
    int32 MinFractionalDigits;                                                        // 0x07A0 (size: 0x4)
    int32 MaxFractionalDigits;                                                        // 0x07A4 (size: 0x4)
    bool bAlwaysUsesDeltaSnap;                                                        // 0x07A8 (size: 0x1)
    bool bEnableSlider;                                                               // 0x07A9 (size: 0x1)
    float Delta;                                                                      // 0x07AC (size: 0x4)
    float SliderExponent;                                                             // 0x07B0 (size: 0x4)
    FSlateFontInfo Font;                                                              // 0x07B8 (size: 0x58)
    TEnumAsByte<ETextJustify::Type> Justification;                                    // 0x0810 (size: 0x1)
    float MinDesiredWidth;                                                            // 0x0814 (size: 0x4)
    TEnumAsByte<EVirtualKeyboardType::Type> KeyboardType;                             // 0x0818 (size: 0x1)
    bool ClearKeyboardFocusOnCommit;                                                  // 0x0819 (size: 0x1)
    bool SelectAllTextOnCommit;                                                       // 0x081A (size: 0x1)
    FSlateColor ForegroundColor;                                                      // 0x081C (size: 0x14)
    FSpinBoxOnValueChanged OnValueChanged;                                            // 0x0830 (size: 0x10)
    void OnSpinBoxValueChangedEvent(float InValue);
    FSpinBoxOnValueCommitted OnValueCommitted;                                        // 0x0840 (size: 0x10)
    void OnSpinBoxValueCommittedEvent(float InValue, TEnumAsByte<ETextCommit::Type> CommitMethod);
    FSpinBoxOnBeginSliderMovement OnBeginSliderMovement;                              // 0x0850 (size: 0x10)
    void OnSpinBoxBeginSliderMovement();
    FSpinBoxOnEndSliderMovement OnEndSliderMovement;                                  // 0x0860 (size: 0x10)
    void OnSpinBoxValueChangedEvent(float InValue);
    uint8 bOverride_MinValue;                                                         // 0x0870 (size: 0x1)
    uint8 bOverride_MaxValue;                                                         // 0x0870 (size: 0x1)
    uint8 bOverride_MinSliderValue;                                                   // 0x0870 (size: 0x1)
    uint8 bOverride_MaxSliderValue;                                                   // 0x0870 (size: 0x1)
    float MinValue;                                                                   // 0x0874 (size: 0x4)
    float MaxValue;                                                                   // 0x0878 (size: 0x4)
    float MinSliderValue;                                                             // 0x087C (size: 0x4)
    float MaxSliderValue;                                                             // 0x0880 (size: 0x4)

    void SetValue(float NewValue);
    void SetMinValue(float NewValue);
    void SetMinSliderValue(float NewValue);
    void SetMinFractionalDigits(int32 NewValue);
    void SetMaxValue(float NewValue);
    void SetMaxSliderValue(float NewValue);
    void SetMaxFractionalDigits(int32 NewValue);
    void SetForegroundColor(FSlateColor InForegroundColor);
    void SetDelta(float NewValue);
    void SetAlwaysUsesDeltaSnap(bool bNewValue);
    void OnSpinBoxValueCommittedEvent__DelegateSignature(float InValue, TEnumAsByte<ETextCommit::Type> CommitMethod);
    void OnSpinBoxValueChangedEvent__DelegateSignature(float InValue);
    void OnSpinBoxBeginSliderMovement__DelegateSignature();
    void GetValue();
    void GetMinValue();
    void GetMinSliderValue();
    void GetMinFractionalDigits();
    void GetMaxValue();
    void GetMaxSliderValue();
    void GetMaxFractionalDigits();
    void GetDelta();
    void GetAlwaysUsesDeltaSnap();
    void ClearMinValue();
    void ClearMinSliderValue();
    void ClearMaxValue();
    void ClearMaxSliderValue();
}; // Size: 0x8A0

class UStackBox : public UPanelWidget
{
    TEnumAsByte<EOrientation> Orientation;                                            // 0x0198 (size: 0x1)

    void ReplaceStackBoxChildAt(int32 Index, class UWidget* Content);
    void AddChildToStackBox(class UWidget* Content);
}; // Size: 0x1B0

class UStackBoxSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0038 (size: 0x10)
    FSlateChildSize Size;                                                             // 0x0048 (size: 0x8)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0050 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0051 (size: 0x1)

}; // Size: 0x60

class UTextBinding : public UPropertyBinding
{

    void GetTextValue();
    void GetStringValue();
}; // Size: 0x78

class UTextBlock : public UTextLayoutWidget
{
    FText Text;                                                                       // 0x01A0 (size: 0x18)
    FTextBlockTextDelegate TextDelegate;                                              // 0x01B8 (size: 0x10)
    void GetText();
    FSlateColor ColorAndOpacity;                                                      // 0x01C8 (size: 0x14)
    FTextBlockColorAndOpacityDelegate ColorAndOpacityDelegate;                        // 0x01DC (size: 0x10)
    void GetSlateColor();
    FSlateFontInfo Font;                                                              // 0x01F0 (size: 0x58)
    FSlateBrush StrikeBrush;                                                          // 0x0250 (size: 0xD0)
    FVector2D ShadowOffset;                                                           // 0x0320 (size: 0x10)
    FLinearColor ShadowColorAndOpacity;                                               // 0x0330 (size: 0x10)
    FTextBlockShadowColorAndOpacityDelegate ShadowColorAndOpacityDelegate;            // 0x0340 (size: 0x10)
    void GetLinearColor();
    float MinDesiredWidth;                                                            // 0x0350 (size: 0x4)
    bool bWrapWithInvalidationPanel;                                                  // 0x0354 (size: 0x1)
    ETextTransformPolicy TextTransformPolicy;                                         // 0x0355 (size: 0x1)
    ETextOverflowPolicy TextOverflowPolicy;                                           // 0x0356 (size: 0x1)
    bool bSimpleTextMode;                                                             // 0x0357 (size: 0x1)

    void SetTextTransformPolicy(ETextTransformPolicy InTransformPolicy);
    void SetTextOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);
    void SetText(FText InText);
    void SetStrikeBrush(FSlateBrush InStrikeBrush);
    void SetShadowOffset(FVector2D InShadowOffset);
    void SetShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity);
    void SetOpacity(float InOpacity);
    void SetMinDesiredWidth(float InMinDesiredWidth);
    void SetFontOutlineMaterial(class UMaterialInterface* InMaterial);
    void SetFontMaterial(class UMaterialInterface* InMaterial);
    void SetFont(FSlateFontInfo InFontInfo);
    void SetColorAndOpacity(FSlateColor InColorAndOpacity);
    void SetAutoWrapText(bool InAutoTextWrap);
    void GetText();
    void GetDynamicOutlineMaterial();
    void GetDynamicFontMaterial();
}; // Size: 0x370

class UTextLayoutWidget : public UWidget
{
    FShapedTextOptions ShapedTextOptions;                                             // 0x0180 (size: 0x3)
    TEnumAsByte<ETextJustify::Type> Justification;                                    // 0x0183 (size: 0x1)
    ETextWrappingPolicy WrappingPolicy;                                               // 0x0184 (size: 0x1)
    uint8 AutoWrapText;                                                               // 0x0185 (size: 0x1)
    float WrapTextAt;                                                                 // 0x0188 (size: 0x4)
    FMargin Margin;                                                                   // 0x018C (size: 0x10)
    float LineHeightPercentage;                                                       // 0x019C (size: 0x4)

    void SetJustification(TEnumAsByte<ETextJustify::Type> InJustification);
}; // Size: 0x1A0

class UThrobber : public UWidget
{
    int32 NumberOfPieces;                                                             // 0x0180 (size: 0x4)
    bool bAnimateHorizontally;                                                        // 0x0184 (size: 0x1)
    bool bAnimateVertically;                                                          // 0x0185 (size: 0x1)
    bool bAnimateOpacity;                                                             // 0x0186 (size: 0x1)
    FSlateBrush Image;                                                                // 0x0190 (size: 0xD0)

    void SetNumberOfPieces(int32 InNumberOfPieces);
    void SetAnimateVertically(bool bInAnimateVertically);
    void SetAnimateOpacity(bool bInAnimateOpacity);
    void SetAnimateHorizontally(bool bInAnimateHorizontally);
}; // Size: 0x270

class UTileView : public UListView
{
    float EntryHeight;                                                                // 0x0C70 (size: 0x4)
    float EntryWidth;                                                                 // 0x0C74 (size: 0x4)
    EListItemAlignment TileAlignment;                                                 // 0x0C78 (size: 0x1)
    bool bWrapHorizontalNavigation;                                                   // 0x0C79 (size: 0x1)
    bool bEntrySizeIncludesEntrySpacing;                                              // 0x0C90 (size: 0x1)

    void SetEntryWidth(float NewWidth);
    void SetEntryHeight(float NewHeight);
    void IsAligned();
    void GetEntryWidth();
    void GetEntryHeight();
}; // Size: 0xCA0

class UTreeView : public UListView
{
    FTreeViewBP_OnGetItemChildren BP_OnGetItemChildren;                               // 0x0C80 (size: 0x10)
    void OnGetItemChildrenDynamic(class UObject* Item, TArray<UObject*>& Children);
    FTreeViewBP_OnItemExpansionChanged BP_OnItemExpansionChanged;                     // 0x0C90 (size: 0x10)
    void OnItemExpansionChangedDynamic(class UObject* Item, bool bIsExpanded);

    void SetItemExpansion(class UObject* Item, bool bExpandItem);
    void ExpandAll();
    void CollapseAll();
}; // Size: 0xCD0

class UUMGSequencePlayer : public UObject
{
    class UWidgetAnimation* Animation;                                                // 0x0220 (size: 0x8)
    FMovieSceneRootEvaluationTemplateInstance RootTemplateInstance;                   // 0x0230 (size: 0x88)

    void SetUserTag(FName InUserTag);
    void GetUserTag();
}; // Size: 0x338

class UUMGSequenceTickManager : public UObject
{
    TMap<TWeakObjectPtr<class UUserWidget>, FSequenceTickManagerWidgetData> WeakUserWidgetData; // 0x0028 (size: 0x50)
    class UMovieSceneEntitySystemLinker* Linker;                                      // 0x0078 (size: 0x8)

}; // Size: 0xC0

class UUniformGridPanel : public UPanelWidget
{
    FMargin SlotPadding;                                                              // 0x0198 (size: 0x10)
    float MinDesiredSlotWidth;                                                        // 0x01A8 (size: 0x4)
    float MinDesiredSlotHeight;                                                       // 0x01AC (size: 0x4)

    void SetSlotPadding(FMargin InSlotPadding);
    void SetMinDesiredSlotWidth(float InMinDesiredSlotWidth);
    void SetMinDesiredSlotHeight(float InMinDesiredSlotHeight);
    void AddChildToUniformGrid(class UWidget* Content, int32 InRow, int32 InColumn);
}; // Size: 0x1C0

class UUniformGridSlot : public UPanelSlot
{
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0038 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0039 (size: 0x1)
    int32 Row;                                                                        // 0x003C (size: 0x4)
    int32 Column;                                                                     // 0x0040 (size: 0x4)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetRow(int32 InRow);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
    void SetColumn(int32 InColumn);
}; // Size: 0x50

class UUserListEntryLibrary : public UBlueprintFunctionLibrary
{

    void IsListItemSelected(TScriptInterface<class IUserListEntry> UserListEntry);
    void IsListItemExpanded(TScriptInterface<class IUserListEntry> UserListEntry);
    void GetOwningListView(TScriptInterface<class IUserListEntry> UserListEntry);
}; // Size: 0x28

class UUserObjectListEntryLibrary : public UBlueprintFunctionLibrary
{

    void GetListItemObject(TScriptInterface<class IUserObjectListEntry> UserObjectListEntry);
}; // Size: 0x28

class UUserWidget : public UWidget
{
    FLinearColor ColorAndOpacity;                                                     // 0x0188 (size: 0x10)
    FUserWidgetColorAndOpacityDelegate ColorAndOpacityDelegate;                       // 0x0198 (size: 0x10)
    void GetLinearColor();
    FSlateColor ForegroundColor;                                                      // 0x01A8 (size: 0x14)
    FUserWidgetForegroundColorDelegate ForegroundColorDelegate;                       // 0x01BC (size: 0x10)
    void GetSlateColor();
    FUserWidgetOnVisibilityChanged OnVisibilityChanged;                               // 0x01D0 (size: 0x10)
    void OnVisibilityChangedEvent(ESlateVisibility InVisibility);
    FMargin Padding;                                                                  // 0x01F8 (size: 0x10)
    int32 Priority;                                                                   // 0x0208 (size: 0x4)
    uint8 bIsFocusable;                                                               // 0x020C (size: 0x1)
    uint8 bStopAction;                                                                // 0x020C (size: 0x1)
    TArray<UUMGSequencePlayer*> ActiveSequencePlayers;                                // 0x0210 (size: 0x10)
    class UUMGSequenceTickManager* AnimationTickManager;                              // 0x0220 (size: 0x8)
    TArray<UUMGSequencePlayer*> StoppedSequencePlayers;                               // 0x0228 (size: 0x10)
    TArray<FNamedSlotBinding> NamedSlotBindings;                                      // 0x0238 (size: 0x10)
    TArray<UUserWidgetExtension*> Extensions;                                         // 0x0248 (size: 0x10)
    class UWidgetTree* WidgetTree;                                                    // 0x0258 (size: 0x8)
    uint8 bHasScriptImplementedTick;                                                  // 0x0260 (size: 0x1)
    uint8 bHasScriptImplementedPaint;                                                 // 0x0260 (size: 0x1)
    EWidgetTickFrequency TickFrequency;                                               // 0x0278 (size: 0x1)
    FWidgetChild DesiredFocusWidget;                                                  // 0x027C (size: 0x10)
    class UInputComponent* InputComponent;                                            // 0x0290 (size: 0x8)
    TArray<FAnimationEventBinding> AnimationCallbacks;                                // 0x0298 (size: 0x10)

    void UnregisterInputComponent();
    void UnbindFromAnimationStarted(class UWidgetAnimation* Animation, FUnbindFromAnimationStartedDelegate Delegate);
    void UnbindFromAnimationFinished(class UWidgetAnimation* Animation, FUnbindFromAnimationFinishedDelegate Delegate);
    void UnbindAllFromAnimationStarted(class UWidgetAnimation* Animation);
    void UnbindAllFromAnimationFinished(class UWidgetAnimation* Animation);
    void Tick(FGeometry MyGeometry, float InDeltaTime);
    void StopListeningForInputAction(FName ActionName, TEnumAsByte<EInputEvent> EventType);
    void StopListeningForAllInputActions();
    void StopAnimationsAndLatentActions();
    void StopAnimation(const class UWidgetAnimation* InAnimation);
    void StopAllAnimations();
    void SetPositionInViewport(FVector2D Position, bool bRemoveDPIScale);
    void SetPlaybackSpeed(const class UWidgetAnimation* InAnimation, float PlaybackSpeed);
    void SetPadding(FMargin InPadding);
    void SetOwningPlayer(class APlayerController* LocalPlayerController);
    void SetNumLoopsToPlay(const class UWidgetAnimation* InAnimation, int32 NumLoopsToPlay);
    void SetInputActionPriority(int32 NewPriority);
    void SetInputActionBlocking(bool bShouldBlock);
    void SetForegroundColor(FSlateColor InForegroundColor);
    void SetDesiredSizeInViewport(FVector2D Size);
    void SetColorAndOpacity(FLinearColor InColorAndOpacity);
    void SetAnimationCurrentTime(const class UWidgetAnimation* InAnimation, float InTime);
    void SetAnchorsInViewport(FAnchors Anchors);
    void SetAlignmentInViewport(FVector2D Alignment);
    void ReverseAnimation(const class UWidgetAnimation* InAnimation);
    void RemoveFromViewport();
    void RemoveExtensions(TSubclassOf<class UUserWidgetExtension> InExtensionType);
    void RemoveExtension(class UUserWidgetExtension* InExtension);
    void RegisterInputComponent();
    void PreConstruct(bool IsDesignTime);
    void PlaySound(class USoundBase* SoundToPlay);
    void PlayAnimationTimeRange(class UWidgetAnimation* InAnimation, float StartAtTime, float EndAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed, bool bRestoreState);
    void PlayAnimationReverse(class UWidgetAnimation* InAnimation, float PlaybackSpeed, bool bRestoreState);
    void PlayAnimationForward(class UWidgetAnimation* InAnimation, float PlaybackSpeed, bool bRestoreState);
    void PlayAnimation(class UWidgetAnimation* InAnimation, float StartAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed, bool bRestoreState);
    void PauseAnimation(const class UWidgetAnimation* InAnimation);
    void OnTouchStarted(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);
    void OnTouchMoved(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);
    void OnTouchGesture(FGeometry MyGeometry, const FPointerEvent& GestureEvent);
    void OnTouchForceChanged(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);
    void OnTouchEnded(FGeometry MyGeometry, const FPointerEvent& InTouchEvent);
    void OnRemovedFromFocusPath(FFocusEvent InFocusEvent);
    void OnPreviewMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    void OnPreviewKeyDown(FGeometry MyGeometry, FKeyEvent InKeyEvent);
    void OnPaint(FPaintContext& Context);
    void OnMouseWheel(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    void OnMouseMove(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    void OnMouseLeave(const FPointerEvent& MouseEvent);
    void OnMouseEnter(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    void OnMouseCaptureLost();
    void OnMouseButtonUp(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    void OnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    void OnMouseButtonDoubleClick(FGeometry InMyGeometry, const FPointerEvent& InMouseEvent);
    void OnMotionDetected(FGeometry MyGeometry, FMotionEvent InMotionEvent);
    void OnKeyUp(FGeometry MyGeometry, FKeyEvent InKeyEvent);
    void OnKeyDown(FGeometry MyGeometry, FKeyEvent InKeyEvent);
    void OnKeyChar(FGeometry MyGeometry, FCharacterEvent InCharacterEvent);
    void OnInitialized();
    void OnFocusReceived(FGeometry MyGeometry, FFocusEvent InFocusEvent);
    void OnFocusLost(FFocusEvent InFocusEvent);
    void OnDrop(FGeometry MyGeometry, FPointerEvent PointerEvent, class UDragDropOperation* Operation);
    void OnDragOver(FGeometry MyGeometry, FPointerEvent PointerEvent, class UDragDropOperation* Operation);
    void OnDragLeave(FPointerEvent PointerEvent, class UDragDropOperation* Operation);
    void OnDragEnter(FGeometry MyGeometry, FPointerEvent PointerEvent, class UDragDropOperation* Operation);
    void OnDragDetected(FGeometry MyGeometry, const FPointerEvent& PointerEvent, class UDragDropOperation*& Operation);
    void OnDragCancelled(const FPointerEvent& PointerEvent, class UDragDropOperation* Operation);
    void OnAnimationStarted(const class UWidgetAnimation* Animation);
    void OnAnimationFinished(const class UWidgetAnimation* Animation);
    void OnAnalogValueChanged(FGeometry MyGeometry, FAnalogInputEvent InAnalogInputEvent);
    void OnAddedToFocusPath(FFocusEvent InFocusEvent);
    void ListenForInputAction(FName ActionName, TEnumAsByte<EInputEvent> EventType, bool bConsume, FListenForInputActionCallback Callback);
    void IsPlayingAnimation();
    void IsListeningForInputAction(FName ActionName);
    void IsInteractable();
    void IsAnyAnimationPlaying();
    void IsAnimationPlayingForward(const class UWidgetAnimation* InAnimation);
    void IsAnimationPlaying(const class UWidgetAnimation* InAnimation);
    void GetOwningPlayerPawn();
    void GetOwningPlayerCameraManager();
    void GetIsVisible();
    void GetExtensions(TSubclassOf<class UUserWidgetExtension> ExtensionType);
    void GetExtension(TSubclassOf<class UUserWidgetExtension> ExtensionType);
    void GetAnimationCurrentTime(const class UWidgetAnimation* InAnimation);
    void GetAnchorsInViewport();
    void GetAlignmentInViewport();
    void FlushAnimations();
    void Destruct();
    void Construct();
    void CancelLatentActions();
    void BindToAnimationStarted(class UWidgetAnimation* Animation, FBindToAnimationStartedDelegate Delegate);
    void BindToAnimationFinished(class UWidgetAnimation* Animation, FBindToAnimationFinishedDelegate Delegate);
    void BindToAnimationEvent(class UWidgetAnimation* Animation, FBindToAnimationEventDelegate Delegate, EWidgetAnimationEvent AnimationEvent, FName UserTag);
    void AddToViewport(int32 ZOrder);
    void AddToPlayerScreen(int32 ZOrder);
    void AddExtension(TSubclassOf<class UUserWidgetExtension> InExtensionType);
}; // Size: 0x2C0

class UUserWidgetBlueprint : public UBlueprint
{
}; // Size: 0xA8

class UUserWidgetExtension : public UObject
{
}; // Size: 0x28

class UVerticalBox : public UPanelWidget
{

    void AddChildToVerticalBox(class UWidget* Content);
}; // Size: 0x1A8

class UVerticalBoxSlot : public UPanelSlot
{
    FSlateChildSize Size;                                                             // 0x0038 (size: 0x8)
    FMargin Padding;                                                                  // 0x0040 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0050 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0051 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetSize(FSlateChildSize InSize);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x60

class UViewport : public UContentWidget
{
    FLinearColor BackgroundColor;                                                     // 0x0198 (size: 0x10)

    void Spawn(TSubclassOf<class AActor> ActorClass);
    void SetViewRotation(FRotator Rotation);
    void SetViewLocation(FVector Location);
    void GetViewRotation();
    void GetViewportWorld();
    void GetViewLocation();
}; // Size: 0x1E8

class UVisibilityBinding : public UPropertyBinding
{

    void GetValue();
}; // Size: 0x70

class UVisual : public UObject
{
}; // Size: 0x28

class UWidget : public UVisual
{
    class UPanelSlot* Slot;                                                           // 0x0030 (size: 0x8)
    FWidgetBIsEnabledDelegate bIsEnabledDelegate;                                     // 0x0038 (size: 0x10)
    void GetBool();
    FText ToolTipText;                                                                // 0x0048 (size: 0x18)
    FWidgetToolTipTextDelegate ToolTipTextDelegate;                                   // 0x0060 (size: 0x10)
    void GetText();
    class UWidget* ToolTipWidget;                                                     // 0x0070 (size: 0x8)
    FWidgetToolTipWidgetDelegate ToolTipWidgetDelegate;                               // 0x0078 (size: 0x10)
    void GetWidget();
    FWidgetVisibilityDelegate VisibilityDelegate;                                     // 0x0088 (size: 0x10)
    void GetSlateVisibility();
    FWidgetTransform RenderTransform;                                                 // 0x0098 (size: 0x38)
    FVector2D RenderTransformPivot;                                                   // 0x00D0 (size: 0x10)
    EFlowDirectionPreference FlowDirectionPreference;                                 // 0x00E0 (size: 0x1)
    uint8 bIsVariable;                                                                // 0x00E1 (size: 0x1)
    uint8 bCreatedByConstructionScript;                                               // 0x00E1 (size: 0x1)
    uint8 bIsEnabled;                                                                 // 0x00E1 (size: 0x1)
    uint8 bOverride_Cursor;                                                           // 0x00E1 (size: 0x1)
    uint8 bIsVolatile;                                                                // 0x00E1 (size: 0x1)
    TEnumAsByte<EMouseCursor::Type> Cursor;                                           // 0x00E2 (size: 0x1)
    EWidgetClipping Clipping;                                                         // 0x00E3 (size: 0x1)
    ESlateVisibility Visibility;                                                      // 0x00E4 (size: 0x1)
    float RenderOpacity;                                                              // 0x00E8 (size: 0x4)
    EWidgetPixelSnapping PixelSnapping;                                               // 0x00EC (size: 0x1)
    class USlateAccessibleWidgetData* AccessibleWidgetData;                           // 0x00F0 (size: 0x8)
    class UWidgetNavigation* Navigation;                                              // 0x00F8 (size: 0x8)
    TArray<UPropertyBinding*> NativeBindings;                                         // 0x0150 (size: 0x10)

    void SetVisibility(ESlateVisibility InVisibility);
    void SetUserFocus(class APlayerController* PlayerController);
    void SetToolTipText(const FText& InToolTipText);
    void SetToolTip(class UWidget* Widget);
    void SetRenderTranslation(FVector2D Translation);
    void SetRenderTransformPivot(FVector2D Pivot);
    void SetRenderTransformAngle(float Angle);
    void SetRenderTransform(FWidgetTransform InTransform);
    void SetRenderShear(FVector2D Shear);
    void SetRenderScale(FVector2D Scale);
    void SetRenderOpacity(float InOpacity);
    void SetNavigationRuleExplicit(EUINavigation Direction, class UWidget* InWidget);
    void SetNavigationRuleCustomBoundary(EUINavigation Direction, FSetNavigationRuleCustomBoundaryInCustomDelegate InCustomDelegate);
    void SetNavigationRuleCustom(EUINavigation Direction, FSetNavigationRuleCustomInCustomDelegate InCustomDelegate);
    void SetNavigationRuleBase(EUINavigation Direction, EUINavigationRule Rule);
    void SetNavigationRule(EUINavigation Direction, EUINavigationRule Rule, FName WidgetToFocus);
    void SetKeyboardFocus();
    void SetIsEnabled(bool bInIsEnabled);
    void SetFocus();
    void SetCursor(TEnumAsByte<EMouseCursor::Type> InCursor);
    void SetClipping(EWidgetClipping InClipping);
    void SetAllNavigationRules(EUINavigationRule Rule, FName WidgetToFocus);
    void ResetCursor();
    void RemoveFromParent();
    void OnReply__DelegateSignature();
    void OnPointerEvent__DelegateSignature(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
    void K2_RemoveFieldValueChangedDelegate(FFieldNotificationId FieldId, FK2_RemoveFieldValueChangedDelegateDelegate Delegate);
    void K2_BroadcastFieldValueChanged(FFieldNotificationId FieldId);
    void K2_AddFieldValueChangedDelegate(FFieldNotificationId FieldId, FK2_AddFieldValueChangedDelegateDelegate Delegate);
    void IsVisible();
    void IsRendered();
    void IsInViewport();
    void IsHovered();
    void InvalidateLayoutAndVolatility();
    void HasUserFocusedDescendants(class APlayerController* PlayerController);
    void HasUserFocus(class APlayerController* PlayerController);
    void HasMouseCaptureByUser(int32 UserIndex, int32 PointerIndex);
    void HasMouseCapture();
    void HasKeyboardFocus();
    void HasFocusedDescendants();
    void HasAnyUserFocus();
    void GetWidget__DelegateSignature();
    void GetVisibility();
    void GetTickSpaceGeometry();
    void GetText__DelegateSignature();
    void GetSlateVisibility__DelegateSignature();
    void GetSlateColor__DelegateSignature();
    void GetSlateBrush__DelegateSignature();
    void GetRenderTransformAngle();
    void GetRenderOpacity();
    void GetParent();
    void GetPaintSpaceGeometry();
    void GetOwningPlayer();
    void GetOwningLocalPlayer();
    void GetMouseCursor__DelegateSignature();
    void GetLinearColor__DelegateSignature();
    void GetIsEnabled();
    void GetInt32__DelegateSignature();
    void GetGameInstance();
    void GetFloat__DelegateSignature();
    void GetDesiredSize();
    void GetClipping();
    void GetCheckBoxState__DelegateSignature();
    void GetCachedGeometry();
    void GetBool__DelegateSignature();
    void GetAccessibleText();
    void GetAccessibleSummaryText();
    void GenerateWidgetForString__DelegateSignature(FString Item);
    void GenerateWidgetForObject__DelegateSignature(class UObject* Item);
    void ForceVolatile(bool bForce);
    void ForceLayoutPrepass();
}; // Size: 0x180

class UWidgetAnimation : public UMovieSceneSequence
{
    class UMovieScene* MovieScene;                                                    // 0x0068 (size: 0x8)
    TArray<FWidgetAnimationBinding> AnimationBindings;                                // 0x0070 (size: 0x10)
    bool bLegacyFinishOnStop;                                                         // 0x0080 (size: 0x1)
    FString DisplayLabel;                                                             // 0x0088 (size: 0x10)

    void UnbindFromAnimationStarted(class UUserWidget* Widget, FUnbindFromAnimationStartedDelegate Delegate);
    void UnbindFromAnimationFinished(class UUserWidget* Widget, FUnbindFromAnimationFinishedDelegate Delegate);
    void UnbindAllFromAnimationStarted(class UUserWidget* Widget);
    void UnbindAllFromAnimationFinished(class UUserWidget* Widget);
    void GetStartTime();
    void GetEndTime();
    void BindToAnimationStarted(class UUserWidget* Widget, FBindToAnimationStartedDelegate Delegate);
    void BindToAnimationFinished(class UUserWidget* Widget, FBindToAnimationFinishedDelegate Delegate);
}; // Size: 0x98

class UWidgetAnimationDelegateBinding : public UDynamicBlueprintBinding
{
    TArray<FBlueprintWidgetAnimationDelegateBinding> WidgetAnimationDelegateBindings; // 0x0028 (size: 0x10)

}; // Size: 0x38

class UWidgetAnimationPlayCallbackProxy : public UObject
{
    FWidgetAnimationPlayCallbackProxyFinished Finished;                               // 0x0028 (size: 0x10)
    void WidgetAnimationResult();

    void CreatePlayAnimationTimeRangeProxyObject(class UUMGSequencePlayer*& Result, class UUserWidget* Widget, class UWidgetAnimation* InAnimation, float StartAtTime, float EndAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed);
    void CreatePlayAnimationProxyObject(class UUMGSequencePlayer*& Result, class UUserWidget* Widget, class UWidgetAnimation* InAnimation, float StartAtTime, int32 NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode::Type> PlayMode, float PlaybackSpeed);
}; // Size: 0x40

class UWidgetBinaryStateRegistration : public UObject
{
}; // Size: 0x28

class UWidgetBinding : public UPropertyBinding
{

    void GetValue();
}; // Size: 0x70

class UWidgetBlueprintGeneratedClass : public UBlueprintGeneratedClass
{
    class UWidgetTree* WidgetTree;                                                    // 0x0368 (size: 0x8)
    TArray<UWidgetBlueprintGeneratedClassExtension*> Extensions;                      // 0x0370 (size: 0x10)
    uint8 bClassRequiresNativeTick;                                                   // 0x0380 (size: 0x1)
    TArray<FDelegateRuntimeBinding> Bindings;                                         // 0x0388 (size: 0x10)
    TArray<UWidgetAnimation*> Animations;                                             // 0x0398 (size: 0x10)
    TArray<FName> NamedSlots;                                                         // 0x03A8 (size: 0x10)
    TArray<FName> AvailableNamedSlots;                                                // 0x03B8 (size: 0x10)
    TArray<FName> InstanceNamedSlots;                                                 // 0x03C8 (size: 0x10)

}; // Size: 0x3D8

class UWidgetBlueprintGeneratedClassExtension : public UObject
{
}; // Size: 0x28

class UWidgetBlueprintLibrary : public UBlueprintFunctionLibrary
{

    void UnlockMouse(FEventReply& Reply);
    void Unhandled();
    void SetWindowTitleBarState(class UWidget* TitleBarContent, EWindowTitleBarMode Mode, bool bTitleBarDragEnabled, bool bWindowButtonsVisible, bool bTitleBarVisible);
    void SetWindowTitleBarOnCloseClickedDelegate(FSetWindowTitleBarOnCloseClickedDelegateDelegate Delegate);
    void SetWindowTitleBarCloseButtonActive(bool bActive);
    void SetUserFocus(FEventReply& Reply, class UWidget* FocusWidget, bool bInAllUsers);
    void SetMousePosition(FEventReply& Reply, FVector2D NewMousePosition);
    void SetInputMode_UIOnlyEx(class APlayerController* PlayerController, class UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode, const bool bFlushInput);
    void SetInputMode_GameOnly(class APlayerController* PlayerController, const bool bFlushInput);
    void SetInputMode_GameAndUIEx(class APlayerController* PlayerController, class UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode, bool bHideCursorDuringCapture, const bool bFlushInput);
    void SetHardwareCursor(class UObject* WorldContextObject, TEnumAsByte<EMouseCursor::Type> CursorShape, FName CursorName, FVector2D HotSpot);
    void SetFocusToGameViewport();
    void SetColorVisionDeficiencyType(EColorVisionDeficiency Type, float Severity, bool CorrectDeficiency, bool ShowCorrectionWithDeficiency);
    void SetBrushResourceToTexture(FSlateBrush& Brush, class UTexture2D* Texture);
    void SetBrushResourceToMaterial(FSlateBrush& Brush, class UMaterialInterface* Material);
    void RestorePreviousWindowTitleBarState();
    void ReleaseMouseCapture(FEventReply& Reply);
    void ReleaseJoystickCapture(FEventReply& Reply, bool bInAllJoysticks);
    void OnGameWindowCloseButtonClickedDelegate__DelegateSignature();
    void NoResourceBrush();
    void MakeBrushFromTexture(class UTexture2D* Texture, int32 Width, int32 Height);
    void MakeBrushFromMaterial(class UMaterialInterface* Material, int32 Width, int32 Height);
    void MakeBrushFromAsset(class USlateBrushAsset* BrushAsset);
    void LockMouse(FEventReply& Reply, class UWidget* CapturingWidget);
    void IsDragDropping();
    void Handled();
    void GetSafeZonePadding(class UObject* WorldContextObject, FVector4& SafePadding, FVector2D& SafePaddingScale, FVector4& SpillOverPadding);
    void GetKeyEventFromAnalogInputEvent(const FAnalogInputEvent& Event);
    void GetInputEventFromPointerEvent(const FPointerEvent& Event);
    void GetInputEventFromNavigationEvent(const FNavigationEvent& Event);
    void GetInputEventFromKeyEvent(const FKeyEvent& Event);
    void GetInputEventFromCharacterEvent(const FCharacterEvent& Event);
    void GetDynamicMaterial(FSlateBrush& Brush);
    void GetDragDroppingContent();
    void GetBrushResourceAsTexture2D(const FSlateBrush& Brush);
    void GetBrushResourceAsMaterial(const FSlateBrush& Brush);
    void GetBrushResource(const FSlateBrush& Brush);
    void GetAllWidgetsWithInterface(class UObject* WorldContextObject, TArray<UUserWidget*>& FoundWidgets, TSubclassOf<class UInterface> Interface, bool TopLevelOnly);
    void GetAllWidgetsOfClass(class UObject* WorldContextObject, TArray<UUserWidget*>& FoundWidgets, TSubclassOf<class UUserWidget> WidgetClass, bool TopLevelOnly);
    void EndDragDrop(FEventReply& Reply);
    void DrawTextFormatted(FPaintContext& Context, const FText& Text, FVector2D Position, class UFont* Font, float FontSize, FName FontTypeFace, FLinearColor Tint);
    void DrawText(FPaintContext& Context, FString InString, FVector2D Position, FLinearColor Tint);
    void DrawSpline(FPaintContext& Context, FVector2D Start, FVector2D StartDir, FVector2D End, FVector2D EndDir, FLinearColor Tint, float Thickness);
    void DrawLines(FPaintContext& Context, const TArray<FVector2D>& Points, FLinearColor Tint, bool bAntiAlias, float Thickness);
    void DrawLine(FPaintContext& Context, FVector2D PositionA, FVector2D PositionB, FLinearColor Tint, bool bAntiAlias, float Thickness);
    void DrawBox(FPaintContext& Context, FVector2D Position, FVector2D Size, class USlateBrushAsset* Brush, FLinearColor Tint);
    void DismissAllMenus();
    void DetectDragIfPressed(const FPointerEvent& PointerEvent, class UWidget* WidgetDetectingDrag, FKey DragKey);
    void DetectDrag(FEventReply& Reply, class UWidget* WidgetDetectingDrag, FKey DragKey);
    void CreateDragDropOperation(TSubclassOf<class UDragDropOperation> OperationClass);
    void Create(class UObject* WorldContextObject, TSubclassOf<class UUserWidget> WidgetType, class APlayerController* OwningPlayer);
    void ClearUserFocus(FEventReply& Reply, bool bInAllUsers);
    void CaptureMouse(FEventReply& Reply, class UWidget* CapturingWidget);
    void CaptureJoystick(FEventReply& Reply, class UWidget* CapturingWidget, bool bInAllJoysticks);
    void CancelDragDrop();
}; // Size: 0x28

class UWidgetCheckedStateRegistration : public UWidgetEnumStateRegistration
{
}; // Size: 0x28

class UWidgetComponent : public UMeshComponent
{
    EWidgetSpace Space;                                                               // 0x05A8 (size: 0x1)
    EWidgetTimingPolicy TimingPolicy;                                                 // 0x05A9 (size: 0x1)
    TSubclassOf<class UUserWidget> WidgetClass;                                       // 0x05B0 (size: 0x8)
    FIntPoint DrawSize;                                                               // 0x05B8 (size: 0x8)
    bool bManuallyRedraw;                                                             // 0x05C0 (size: 0x1)
    bool bRedrawRequested;                                                            // 0x05C1 (size: 0x1)
    float RedrawTime;                                                                 // 0x05C4 (size: 0x4)
    FIntPoint CurrentDrawSize;                                                        // 0x05D0 (size: 0x8)
    bool bDrawAtDesiredSize;                                                          // 0x05D8 (size: 0x1)
    FVector2D Pivot;                                                                  // 0x05E0 (size: 0x10)
    bool bReceiveHardwareInput;                                                       // 0x05F0 (size: 0x1)
    bool bWindowFocusable;                                                            // 0x05F1 (size: 0x1)
    EWindowVisibility WindowVisibility;                                               // 0x05F2 (size: 0x1)
    bool bApplyGammaCorrection;                                                       // 0x05F3 (size: 0x1)
    class ULocalPlayer* OwnerPlayer;                                                  // 0x05F8 (size: 0x8)
    FLinearColor BackgroundColor;                                                     // 0x0600 (size: 0x10)
    FLinearColor TintColorAndOpacity;                                                 // 0x0610 (size: 0x10)
    float OpacityFromTexture;                                                         // 0x0620 (size: 0x4)
    EWidgetBlendMode BlendMode;                                                       // 0x0624 (size: 0x1)
    bool bIsTwoSided;                                                                 // 0x0625 (size: 0x1)
    bool TickWhenOffscreen;                                                           // 0x0626 (size: 0x1)
    class UBodySetup* BodySetup;                                                      // 0x0628 (size: 0x8)
    class UMaterialInterface* TranslucentMaterial;                                    // 0x0630 (size: 0x8)
    class UMaterialInterface* TranslucentMaterial_OneSided;                           // 0x0638 (size: 0x8)
    class UMaterialInterface* OpaqueMaterial;                                         // 0x0640 (size: 0x8)
    class UMaterialInterface* OpaqueMaterial_OneSided;                                // 0x0648 (size: 0x8)
    class UMaterialInterface* MaskedMaterial;                                         // 0x0650 (size: 0x8)
    class UMaterialInterface* MaskedMaterial_OneSided;                                // 0x0658 (size: 0x8)
    class UTextureRenderTarget2D* RenderTarget;                                       // 0x0660 (size: 0x8)
    class UMaterialInstanceDynamic* MaterialInstance;                                 // 0x0668 (size: 0x8)
    bool bAddedToScreen;                                                              // 0x0670 (size: 0x1)
    bool bEditTimeUsable;                                                             // 0x0671 (size: 0x1)
    FName SharedLayerName;                                                            // 0x0674 (size: 0x8)
    int32 LayerZOrder;                                                                // 0x067C (size: 0x4)
    EWidgetGeometryMode GeometryMode;                                                 // 0x0680 (size: 0x1)
    float CylinderArcAngle;                                                           // 0x0684 (size: 0x4)
    ETickMode TickMode;                                                               // 0x0688 (size: 0x1)
    class UUserWidget* Widget;                                                        // 0x06B8 (size: 0x8)

    void SetWindowVisibility(EWindowVisibility InVisibility);
    void SetWindowFocusable(bool bInWindowFocusable);
    void SetWidgetSpace(EWidgetSpace NewSpace);
    void SetWidget(class UUserWidget* Widget);
    void SetTwoSided(const bool bWantTwoSided);
    void SetTintColorAndOpacity(const FLinearColor NewTintColorAndOpacity);
    void SetTickWhenOffscreen(const bool bWantTickWhenOffscreen);
    void SetTickMode(ETickMode InTickMode);
    void SetRedrawTime(float InRedrawTime);
    void SetPivot(const FVector2D& InPivot);
    void SetOwnerPlayer(class ULocalPlayer* LocalPlayer);
    void SetManuallyRedraw(bool bUseManualRedraw);
    void SetGeometryMode(EWidgetGeometryMode InGeometryMode);
    void SetDrawSize(FVector2D Size);
    void SetDrawAtDesiredSize(bool bInDrawAtDesiredSize);
    void SetCylinderArcAngle(const float InCylinderArcAngle);
    void SetBackgroundColor(const FLinearColor NewBackgroundColor);
    void RequestRenderUpdate();
    void RequestRedraw();
    void IsWidgetVisible();
    void GetWindowVisiblility();
    void GetWindowFocusable();
    void GetWidgetSpace();
    void GetWidget();
    void GetUserWidgetObject();
    void GetTwoSided();
    void GetTickWhenOffscreen();
    void GetRenderTarget();
    void GetRedrawTime();
    void GetPivot();
    void GetOwnerPlayer();
    void GetMaterialInstance();
    void GetManuallyRedraw();
    void GetGeometryMode();
    void GetDrawSize();
    void GetDrawAtDesiredSize();
    void GetCylinderArcAngle();
    void GetCurrentDrawSize();
}; // Size: 0x6F0

class UWidgetDisabledStateRegistration : public UWidgetBinaryStateRegistration
{
}; // Size: 0x28

class UWidgetEnumStateRegistration : public UObject
{
}; // Size: 0x28

class UWidgetFieldNotificationExtension : public UUserWidgetExtension
{
}; // Size: 0x40

class UWidgetHoveredStateRegistration : public UWidgetBinaryStateRegistration
{
}; // Size: 0x28

class UWidgetInteractionComponent : public USceneComponent
{
    FWidgetInteractionComponentOnHoveredWidgetChanged OnHoveredWidgetChanged;         // 0x02A0 (size: 0x10)
    void OnHoveredWidgetChanged(class UWidgetComponent* WidgetComponent, class UWidgetComponent* PreviousWidgetComponent);
    int32 VirtualUserIndex;                                                           // 0x02C0 (size: 0x4)
    int32 PointerIndex;                                                               // 0x02C4 (size: 0x4)
    TEnumAsByte<ECollisionChannel> TraceChannel;                                      // 0x02C8 (size: 0x1)
    float InteractionDistance;                                                        // 0x02CC (size: 0x4)
    EWidgetInteractionSource InteractionSource;                                       // 0x02D0 (size: 0x1)
    bool bEnableHitTesting;                                                           // 0x02D1 (size: 0x1)
    bool bShowDebug;                                                                  // 0x02D2 (size: 0x1)
    float DebugSphereLineThickness;                                                   // 0x02D4 (size: 0x4)
    float DebugLineThickness;                                                         // 0x02D8 (size: 0x4)
    FLinearColor DebugColor;                                                          // 0x02DC (size: 0x10)
    FHitResult CustomHitResult;                                                       // 0x0368 (size: 0xE8)
    FVector2D LocalHitLocation;                                                       // 0x0450 (size: 0x10)
    FVector2D LastLocalHitLocation;                                                   // 0x0460 (size: 0x10)
    class UWidgetComponent* HoveredWidgetComponent;                                   // 0x0470 (size: 0x8)
    FHitResult LastHitResult;                                                         // 0x0478 (size: 0xE8)
    bool bIsHoveredWidgetInteractable;                                                // 0x0560 (size: 0x1)
    bool bIsHoveredWidgetFocusable;                                                   // 0x0561 (size: 0x1)
    bool bIsHoveredWidgetHitTestVisible;                                              // 0x0562 (size: 0x1)

    void SetFocus(class UWidget* FocusWidget);
    void SetCustomHitResult(const FHitResult& HitResult);
    void SendKeyChar(FString Characters, bool bRepeat);
    void ScrollWheel(float ScrollDelta);
    void ReleasePointerKey(FKey Key);
    void ReleaseKey(FKey Key);
    void PressPointerKey(FKey Key);
    void PressKey(FKey Key, bool bRepeat);
    void PressAndReleaseKey(FKey Key);
    void IsOverInteractableWidget();
    void IsOverHitTestVisibleWidget();
    void IsOverFocusableWidget();
    void GetLastHitResult();
    void GetHoveredWidgetComponent();
    void Get2DHitLocation();
}; // Size: 0x570

class UWidgetLayoutLibrary : public UBlueprintFunctionLibrary
{

    void SlotAsWrapBoxSlot(class UWidget* Widget);
    void SlotAsWidgetSwitcherSlot(class UWidget* Widget);
    void SlotAsVerticalBoxSlot(class UWidget* Widget);
    void SlotAsUniformGridSlot(class UWidget* Widget);
    void SlotAsSizeBoxSlot(class UWidget* Widget);
    void SlotAsScrollBoxSlot(class UWidget* Widget);
    void SlotAsScaleBoxSlot(class UWidget* Widget);
    void SlotAsSafeBoxSlot(class UWidget* Widget);
    void SlotAsOverlaySlot(class UWidget* Widget);
    void SlotAsHorizontalBoxSlot(class UWidget* Widget);
    void SlotAsGridSlot(class UWidget* Widget);
    void SlotAsCanvasSlot(class UWidget* Widget);
    void SlotAsBorderSlot(class UWidget* Widget);
    void RemoveAllWidgets(class UObject* WorldContextObject);
    void ProjectWorldLocationToWidgetPosition(class APlayerController* PlayerController, FVector WorldLocation, FVector2D& ScreenPosition, bool bPlayerViewportRelative);
    void GetViewportWidgetGeometry(class UObject* WorldContextObject);
    void GetViewportSize(class UObject* WorldContextObject);
    void GetViewportScale(const class UObject* WorldContextObject);
    void GetPlayerScreenWidgetGeometry(class APlayerController* PlayerController);
    void GetMousePositionScaledByDPI(class APlayerController* Player, float& LocationX, float& LocationY);
    void GetMousePositionOnViewport(class UObject* WorldContextObject);
    void GetMousePositionOnPlatform();
}; // Size: 0x28

class UWidgetNavigation : public UObject
{
    FWidgetNavigationData Up;                                                         // 0x0028 (size: 0x24)
    FWidgetNavigationData Down;                                                       // 0x004C (size: 0x24)
    FWidgetNavigationData Left;                                                       // 0x0070 (size: 0x24)
    FWidgetNavigationData Right;                                                      // 0x0094 (size: 0x24)
    FWidgetNavigationData Next;                                                       // 0x00B8 (size: 0x24)
    FWidgetNavigationData Previous;                                                   // 0x00DC (size: 0x24)

}; // Size: 0x100

class UWidgetPressedStateRegistration : public UWidgetBinaryStateRegistration
{
}; // Size: 0x28

class UWidgetSelectedStateRegistration : public UWidgetBinaryStateRegistration
{
}; // Size: 0x28

class UWidgetStateSettings : public UDeveloperSettings
{
}; // Size: 0x6E8

class UWidgetSwitcher : public UPanelWidget
{
    int32 ActiveWidgetIndex;                                                          // 0x0198 (size: 0x4)

    void SetActiveWidgetIndex(int32 Index);
    void SetActiveWidget(class UWidget* Widget);
    void GetWidgetAtIndex(int32 Index);
    void GetNumWidgets();
    void GetActiveWidgetIndex();
    void GetActiveWidget();
}; // Size: 0x1B0

class UWidgetSwitcherSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0040 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0050 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0051 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x58

class UWidgetTree : public UObject
{
    class UWidget* RootWidget;                                                        // 0x0030 (size: 0x8)
    TMap<FName, UWidget*> NamedSlotBindings;                                          // 0x0038 (size: 0x50)

}; // Size: 0x88

class UWindowTitleBarArea : public UContentWidget
{
    bool bWindowButtonsEnabled;                                                       // 0x0198 (size: 0x1)
    bool bDoubleClickTogglesFullscreen;                                               // 0x0199 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x1B8

class UWindowTitleBarAreaSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0038 (size: 0x10)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x0048 (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x0049 (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
}; // Size: 0x60

class UWrapBox : public UPanelWidget
{
    FVector2D InnerSlotPadding;                                                       // 0x0198 (size: 0x10)
    float WrapSize;                                                                   // 0x01A8 (size: 0x4)
    bool bExplicitWrapSize;                                                           // 0x01AC (size: 0x1)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x01AD (size: 0x1)
    TEnumAsByte<EOrientation> Orientation;                                            // 0x01AE (size: 0x1)

    void SetInnerSlotPadding(FVector2D InPadding);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
    void AddChildToWrapBox(class UWidget* Content);
}; // Size: 0x1C0

class UWrapBoxSlot : public UPanelSlot
{
    FMargin Padding;                                                                  // 0x0038 (size: 0x10)
    float FillSpanWhenLessThan;                                                       // 0x0048 (size: 0x4)
    TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;                            // 0x004C (size: 0x1)
    TEnumAsByte<EVerticalAlignment> VerticalAlignment;                                // 0x004D (size: 0x1)
    bool bFillEmptySpace;                                                             // 0x004E (size: 0x1)
    bool bForceNewLine;                                                               // 0x004F (size: 0x1)

    void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
    void SetPadding(FMargin InPadding);
    void SetNewLine(bool InForceNewLine);
    void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
    void SetFillSpanWhenLessThan(float InFillSpanWhenLessThan);
    void SetFillEmptySpace(bool InbFillEmptySpace);
}; // Size: 0x58

#endif
