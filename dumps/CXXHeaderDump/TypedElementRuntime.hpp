#ifndef UE4SS_SDK_TypedElementRuntime_HPP
#define UE4SS_SDK_TypedElementRuntime_HPP

#include "TypedElementRuntime_enums.hpp"

struct FTypedElementIsSelectedOptions
{
    bool bAllowIndirect;                                                              // 0x0000 (size: 0x1)

}; // Size: 0x1

struct FTypedElementSelectionNormalizationOptions
{
    bool bExpandGroups;                                                               // 0x0000 (size: 0x1)
    bool bFollowAttachment;                                                           // 0x0001 (size: 0x1)

}; // Size: 0x2

struct FTypedElementSelectionOptions
{
    bool bAllowHidden;                                                                // 0x0000 (size: 0x1)
    bool bAllowGroups;                                                                // 0x0001 (size: 0x1)
    bool bAllowLegacyNotifications;                                                   // 0x0002 (size: 0x1)
    bool bWarnIfLocked;                                                               // 0x0003 (size: 0x1)
    ETypedElementChildInclusionMethod ChildElementInclusionMethod;                    // 0x0004 (size: 0x1)

}; // Size: 0x5

struct FTypedElementSelectionSetState
{
    TWeakObjectPtr<class UTypedElementSelectionSet> CreatedFromSelectionSet;          // 0x0000 (size: 0x8)

}; // Size: 0x18

class ITypedElementAssetDataInterface : public IInterface
{

    void GetAssetData(const FScriptTypedElementHandle& InElementHandle);
    void GetAllReferencedAssetDatas(const FScriptTypedElementHandle& InElementHandle);
}; // Size: 0x28

class ITypedElementHierarchyInterface : public IInterface
{

    void GetParentElement(const FScriptTypedElementHandle& InElementHandle, const bool bAllowCreate);
    void GetChildElements(const FScriptTypedElementHandle& InElementHandle, TArray<FScriptTypedElementHandle>& OutElementHandles, const bool bAllowCreate);
}; // Size: 0x28

class ITypedElementObjectInterface : public IInterface
{

    void GetObjectClass(const FScriptTypedElementHandle& InElementHandle);
    void GetObject(const FScriptTypedElementHandle& InElementHandle);
}; // Size: 0x28

class ITypedElementPrimitiveCustomDataInterface : public IInterface
{

    void SetCustomDataValue(const FScriptTypedElementHandle& InElementHandle, int32 CustomDataIndex, float CustomDataValue, bool bMarkRenderStateDirty);
    void SetCustomData(const FScriptTypedElementHandle& InElementHandle, const TArray<float>& CustomDataFloats, bool bMarkRenderStateDirty);
}; // Size: 0x28

class ITypedElementSelectionInterface : public IInterface
{

    void SelectElement(const FScriptTypedElementHandle& InElementHandle, FScriptTypedElementListProxy InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);
    void IsElementSelected(const FScriptTypedElementHandle& InElementHandle, const FScriptTypedElementListProxy InSelectionSet, const FTypedElementIsSelectedOptions& InSelectionOptions);
    void GetSelectionElement(const FScriptTypedElementHandle& InElementHandle, const FScriptTypedElementListProxy InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod);
    void DeselectElement(const FScriptTypedElementHandle& InElementHandle, FScriptTypedElementListProxy InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);
    void CanSelectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions& InSelectionOptions);
    void CanDeselectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions& InSelectionOptions);
    void AllowSelectionModifiers(const FScriptTypedElementHandle& InElementHandle, const FScriptTypedElementListProxy InSelectionSet);
}; // Size: 0x28

class UTypedElementSelectionSet : public UObject
{
    FTypedElementSelectionSetOnPreSelectionChange OnPreSelectionChange;               // 0x0828 (size: 0x10)
    void OnPreChangeDynamic(const class UTypedElementSelectionSet* SelectionSet);
    FTypedElementSelectionSetOnSelectionChange OnSelectionChange;                     // 0x0838 (size: 0x10)
    void OnChangeDynamic(const class UTypedElementSelectionSet* SelectionSet);

    void SetSelection(const TArray<FScriptTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);
    void SelectElements(const TArray<FScriptTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);
    void SelectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions);
    void RestoreSelectionState(const FTypedElementSelectionSetState& InSelectionState);
    void OnPreChangeDynamic__DelegateSignature(const class UTypedElementSelectionSet* SelectionSet);
    void OnChangeDynamic__DelegateSignature(const class UTypedElementSelectionSet* SelectionSet);
    void K2_GetSelectedElementHandles(const TSubclassOf<class UInterface> InBaseInterfaceType);
    void IsElementSelected(const FScriptTypedElementHandle& InElementHandle, const FTypedElementIsSelectedOptions InSelectionOptions);
    void HasSelectedObjects(const UClass* InRequiredClass);
    void HasSelectedElements(const TSubclassOf<class UInterface> InBaseInterfaceType);
    void GetTopSelectedObject(const UClass* InRequiredClass);
    void GetSelectionElement(const FScriptTypedElementHandle& InElementHandle, const ETypedElementSelectionMethod InSelectionMethod);
    void GetSelectedObjects(const UClass* InRequiredClass);
    void GetNumSelectedElements();
    void GetCurrentSelectionState();
    void GetBottomSelectedObject(const UClass* InRequiredClass);
    void DeselectElements(const TArray<FScriptTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);
    void DeselectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions);
    void CountSelectedObjects(const UClass* InRequiredClass);
    void CountSelectedElements(const TSubclassOf<class UInterface> InBaseInterfaceType);
    void ClearSelection(const FTypedElementSelectionOptions InSelectionOptions);
    void CanSelectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions);
    void CanDeselectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions);
    void AllowSelectionModifiers(const FScriptTypedElementHandle& InElementHandle);
}; // Size: 0x898

class UTypedElementSelectionSetLibrary : public UObject
{

    void SetSelectionFromList(class UTypedElementSelectionSet* SelectionSet, const FScriptTypedElementListProxy ElementList, const FTypedElementSelectionOptions SelectionOptions);
    void SelectElementsFromList(class UTypedElementSelectionSet* SelectionSet, const FScriptTypedElementListProxy ElementList, const FTypedElementSelectionOptions SelectionOptions);
    void GetNormalizedSelection(class UTypedElementSelectionSet* SelectionSet, const FTypedElementSelectionNormalizationOptions NormalizationOptions);
    void GetNormalizedElementList(class UTypedElementSelectionSet* SelectionSet, const FScriptTypedElementListProxy ElementList, const FTypedElementSelectionNormalizationOptions NormalizationOptions);
    void DeselectElementsFromList(class UTypedElementSelectionSet* SelectionSet, const FScriptTypedElementListProxy ElementList, const FTypedElementSelectionOptions SelectionOptions);
}; // Size: 0x28

#endif
