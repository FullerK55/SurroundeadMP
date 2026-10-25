#ifndef UE4SS_SDK_StructUtilsEngine_HPP
#define UE4SS_SDK_StructUtilsEngine_HPP

#include "StructUtilsEngine_enums.hpp"

class UStructUtilsFunctionLibrary : public UBlueprintFunctionLibrary
{

    void SetInstancedStructValue(FInstancedStruct& InstancedStruct, const int32& Value);
    void Reset(FInstancedStruct& InstancedStruct, const class UScriptStruct* StructType);
    void NotEqual_InstancedStruct(const FInstancedStruct& A, const FInstancedStruct& B);
    void MakeInstancedStruct(const int32& Value);
    void IsValid_InstancedStruct(const FInstancedStruct& InstancedStruct);
    void IsInstancedStructValid(const FInstancedStruct& InstancedStruct);
    void GetInstancedStructValue(EStructUtilsResult& ExecResult, const FInstancedStruct& InstancedStruct, int32& Value);
    void EqualEqual_InstancedStruct(const FInstancedStruct& A, const FInstancedStruct& B);
}; // Size: 0x28

#endif
