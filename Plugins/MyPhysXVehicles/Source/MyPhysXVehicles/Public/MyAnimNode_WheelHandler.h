// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BoneContainer.h"
#include "BonePose.h"
#include "MyVehicleAnimInstance.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "MyAnimNode_WheelHandler.generated.h"

/**
 *	Simple controller that replaces or adds to the translation/rotation of a single bone.
 */
struct UE_DEPRECATED(4.26, "PhysX is deprecated. Use the FAnimNode_WheelController from the ChaosVehiclePhysics Plugin.") FMyAnimNode_WheelHandler;
USTRUCT()
struct  FMyAnimNode_WheelHandler : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()

	FMyAnimNode_WheelHandler();

	// FAnimNode_Base interface
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	// End of FAnimNode_Base interface

	// FAnimNode_SkeletalControlBase interface
	virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	// End of FAnimNode_SkeletalControlBase interface

private:
	// FAnimNode_SkeletalControlBase interface
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;
	// End of FAnimNode_SkeletalControlBase interface

	struct FMyWheelLookupData
	{
		int32 WheelIndex;
		FBoneReference BoneReference;
	};

	TArray<FMyWheelLookupData> Wheels;
PRAGMA_DISABLE_DEPRECATION_WARNINGS
		const FMyVehicleAnimInstanceProxy* AnimInstanceProxy;	//TODO: we only cache this to use in eval where it's safe. Should change API to pass proxy into eval
PRAGMA_ENABLE_DEPRECATION_WARNINGS 
};
