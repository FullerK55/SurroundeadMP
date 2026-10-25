#ifndef UE4SS_SDK_AnimNotify_MeleeHitDetect_Power_HPP
#define UE4SS_SDK_AnimNotify_MeleeHitDetect_Power_HPP

class UAnimNotify_MeleeHitDetect_Power_C : public UAnimNotifyState
{

    void Received_NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
    void Received_NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
}; // Size: 0x30

#endif
