/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/ObjectRegistry.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiParticleModifier.h"
#include "../../include/obj/NiPSysCollider.h"
#include "../../include/obj/bhkRefObject.h"
#include "../../include/obj/bhkSerializable.h"
#include "../../include/obj/bhkWorldObject.h"
#include "../../include/obj/bhkPhantom.h"
#include "../../include/obj/bhkShapePhantom.h"
#include "../../include/obj/bhkSimpleShapePhantom.h"
#include "../../include/obj/bhkEntity.h"
#include "../../include/obj/bhkRigidBody.h"
#include "../../include/obj/bhkRigidBodyT.h"
#include "../../include/obj/bhkConstraint.h"
#include "../../include/obj/bhkLimitedHingeConstraint.h"
#include "../../include/obj/bhkMalleableConstraint.h"
#include "../../include/obj/bhkStiffSpringConstraint.h"
#include "../../include/obj/bhkRagdollConstraint.h"
#include "../../include/obj/bhkPrismaticConstraint.h"
#include "../../include/obj/bhkHingeConstraint.h"
#include "../../include/obj/bhkShape.h"
#include "../../include/obj/bhkTransformShape.h"
#include "../../include/obj/bhkSphereRepShape.h"
#include "../../include/obj/bhkConvexShape.h"
#include "../../include/obj/bhkSphereShape.h"
#include "../../include/obj/bhkCapsuleShape.h"
#include "../../include/obj/bhkBoxShape.h"
#include "../../include/obj/bhkConvexVerticesShape.h"
#include "../../include/obj/bhkConvexTransformShape.h"
#include "../../include/obj/bhkMultiSphereShape.h"
#include "../../include/obj/bhkBvTreeShape.h"
#include "../../include/obj/bhkMoppBvTreeShape.h"
#include "../../include/obj/bhkShapeCollection.h"
#include "../../include/obj/bhkListShape.h"
#include "../../include/obj/bhkPackedNiTriStripsShape.h"
#include "../../include/obj/bhkNiTriStripsShape.h"
#include "../../include/obj/NiExtraData.h"
#include "../../include/obj/NiInterpolator.h"
#include "../../include/obj/NiKeyBasedInterpolator.h"
#include "../../include/obj/NiFloatInterpolator.h"
#include "../../include/obj/NiTransformInterpolator.h"
#include "../../include/obj/NiPoint3Interpolator.h"
#include "../../include/obj/NiPathInterpolator.h"
#include "../../include/obj/NiBoolInterpolator.h"
#include "../../include/obj/NiBoolTimelineInterpolator.h"
#include "../../include/obj/NiBlendInterpolator.h"
#include "../../include/obj/NiBSplineInterpolator.h"
#include "../../include/obj/NiObjectNET.h"
#include "../../include/obj/NiCollisionObject.h"
#include "../../include/obj/NiCollisionData.h"
#include "../../include/obj/bhkNiCollisionObject.h"
#include "../../include/obj/bhkCollisionObject.h"
#include "../../include/obj/bhkBlendCollisionObject.h"
#include "../../include/obj/bhkPCollisionObject.h"
#include "../../include/obj/bhkSPCollisionObject.h"
#include "../../include/obj/NiAVObject.h"
#include "../../include/obj/NiDynamicEffect.h"
#include "../../include/obj/NiLight.h"
#include "../../include/obj/NiProperty.h"
#include "../../include/obj/NiPSysModifier.h"
#include "../../include/obj/NiPSysEmitter.h"
#include "../../include/obj/NiPSysVolumeEmitter.h"
#include "../../include/obj/NiTimeController.h"
#include "../../include/obj/NiInterpController.h"
#include "../../include/obj/NiMultiTargetTransformController.h"
#include "../../include/obj/NiGeomMorpherController.h"
#include "../../include/obj/NiSingleInterpController.h"
#include "../../include/obj/NiKeyframeController.h"
#include "../../include/obj/NiTransformController.h"
#include "../../include/obj/NiPSysModifierCtlr.h"
#include "../../include/obj/NiPSysEmitterCtlr.h"
#include "../../include/obj/NiPSysModifierBoolCtlr.h"
#include "../../include/obj/NiPSysModifierActiveCtlr.h"
#include "../../include/obj/NiPSysModifierFloatCtlr.h"
#include "../../include/obj/NiPSysEmitterDeclinationCtlr.h"
#include "../../include/obj/NiPSysEmitterDeclinationVarCtlr.h"
#include "../../include/obj/NiPSysEmitterInitialRadiusCtlr.h"
#include "../../include/obj/NiPSysEmitterLifeSpanCtlr.h"
#include "../../include/obj/NiPSysEmitterSpeedCtlr.h"
#include "../../include/obj/NiPSysGravityStrengthCtlr.h"
#include "../../include/obj/NiFloatInterpController.h"
#include "../../include/obj/NiFlipController.h"
#include "../../include/obj/NiAlphaController.h"
#include "../../include/obj/NiTextureTransformController.h"
#include "../../include/obj/NiLightDimmerController.h"
#include "../../include/obj/NiBoolInterpController.h"
#include "../../include/obj/NiVisController.h"
#include "../../include/obj/NiPoint3InterpController.h"
#include "../../include/obj/NiMaterialColorController.h"
#include "../../include/obj/NiLightColorController.h"
#include "../../include/obj/NiExtraDataController.h"
#include "../../include/obj/NiFloatExtraDataController.h"
#include "../../include/obj/NiBoneLODController.h"
#include "../../include/obj/NiBSBoneLODController.h"
#include "../../include/obj/NiGeometry.h"
#include "../../include/obj/NiTriBasedGeom.h"
#include "../../include/obj/NiGeometryData.h"
#include "../../include/obj/NiTriBasedGeomData.h"
#include "../../include/obj/bhkBlendController.h"
#include "../../include/obj/BSBound.h"
#include "../../include/obj/BSFurnitureMarker.h"
#include "../../include/obj/BSParentVelocityModifier.h"
#include "../../include/obj/BSPSysArrayEmitter.h"
#include "../../include/obj/BSWindModifier.h"
#include "../../include/obj/hkPackedNiTriStripsData.h"
#include "../../include/obj/NiAlphaProperty.h"
#include "../../include/obj/NiAmbientLight.h"
#include "../../include/obj/NiParticlesData.h"
#include "../../include/obj/NiRotatingParticlesData.h"
#include "../../include/obj/NiAutoNormalParticlesData.h"
#include "../../include/obj/NiPSysData.h"
#include "../../include/obj/NiMeshPSysData.h"
#include "../../include/obj/NiBinaryExtraData.h"
#include "../../include/obj/NiBinaryVoxelExtraData.h"
#include "../../include/obj/NiBinaryVoxelData.h"
#include "../../include/obj/NiBlendBoolInterpolator.h"
#include "../../include/obj/NiBlendFloatInterpolator.h"
#include "../../include/obj/NiBlendPoint3Interpolator.h"
#include "../../include/obj/NiBlendTransformInterpolator.h"
#include "../../include/obj/NiBoolData.h"
#include "../../include/obj/NiBooleanExtraData.h"
#include "../../include/obj/NiBSplineBasisData.h"
#include "../../include/obj/NiBSplineFloatInterpolator.h"
#include "../../include/obj/NiBSplineCompFloatInterpolator.h"
#include "../../include/obj/NiBSplinePoint3Interpolator.h"
#include "../../include/obj/NiBSplineCompPoint3Interpolator.h"
#include "../../include/obj/NiBSplineTransformInterpolator.h"
#include "../../include/obj/NiBSplineCompTransformInterpolator.h"
#include "../../include/obj/NiBSplineData.h"
#include "../../include/obj/NiCamera.h"
#include "../../include/obj/NiColorData.h"
#include "../../include/obj/NiColorExtraData.h"
#include "../../include/obj/NiControllerManager.h"
#include "../../include/obj/NiSequence.h"
#include "../../include/obj/NiControllerSequence.h"
#include "../../include/obj/NiAVObjectPalette.h"
#include "../../include/obj/NiDefaultAVObjectPalette.h"
#include "../../include/obj/NiDirectionalLight.h"
#include "../../include/obj/NiDitherProperty.h"
#include "../../include/obj/NiRollController.h"
#include "../../include/obj/NiFloatData.h"
#include "../../include/obj/NiFloatExtraData.h"
#include "../../include/obj/NiFloatsExtraData.h"
#include "../../include/obj/NiFogProperty.h"
#include "../../include/obj/NiGravity.h"
#include "../../include/obj/NiIntegerExtraData.h"
#include "../../include/obj/BSXFlags.h"
#include "../../include/obj/NiIntegersExtraData.h"
#include "../../include/obj/BSKeyframeController.h"
#include "../../include/obj/NiKeyframeData.h"
#include "../../include/obj/NiLookAtController.h"
#include "../../include/obj/NiLookAtInterpolator.h"
#include "../../include/obj/NiMaterialProperty.h"
#include "../../include/obj/NiMorphData.h"
#include "../../include/obj/NiNode.h"
#include "../../include/obj/NiBone.h"
#include "../../include/obj/AvoidNode.h"
#include "../../include/obj/FxWidget.h"
#include "../../include/obj/FxButton.h"
#include "../../include/obj/FxRadioButton.h"
#include "../../include/obj/NiBillboardNode.h"
#include "../../include/obj/NiBSAnimationNode.h"
#include "../../include/obj/NiBSParticleNode.h"
#include "../../include/obj/NiSwitchNode.h"
#include "../../include/obj/NiLODNode.h"
#include "../../include/obj/NiPalette.h"
#include "../../include/obj/NiParticleBomb.h"
#include "../../include/obj/NiParticleColorModifier.h"
#include "../../include/obj/NiParticleGrowFade.h"
#include "../../include/obj/NiParticleMeshModifier.h"
#include "../../include/obj/NiParticleRotation.h"
#include "../../include/obj/NiParticles.h"
#include "../../include/obj/NiAutoNormalParticles.h"
#include "../../include/obj/NiParticleMeshes.h"
#include "../../include/obj/NiParticleMeshesData.h"
#include "../../include/obj/NiParticleSystem.h"
#include "../../include/obj/NiMeshParticleSystem.h"
#include "../../include/obj/NiParticleSystemController.h"
#include "../../include/obj/NiBSPArrayController.h"
#include "../../include/obj/NiPathController.h"
#include "../../include/obj/NiPixelData.h"
#include "../../include/obj/NiPlanarCollider.h"
#include "../../include/obj/NiPointLight.h"
#include "../../include/obj/NiPosData.h"
#include "../../include/obj/NiPSysAgeDeathModifier.h"
#include "../../include/obj/NiPSysBombModifier.h"
#include "../../include/obj/NiPSysBoundUpdateModifier.h"
#include "../../include/obj/NiPSysBoxEmitter.h"
#include "../../include/obj/NiPSysColliderManager.h"
#include "../../include/obj/NiPSysColorModifier.h"
#include "../../include/obj/NiPSysCylinderEmitter.h"
#include "../../include/obj/NiPSysDragModifier.h"
#include "../../include/obj/NiPSysEmitterCtlrData.h"
#include "../../include/obj/NiPSysGravityModifier.h"
#include "../../include/obj/NiPSysGrowFadeModifier.h"
#include "../../include/obj/NiPSysMeshEmitter.h"
#include "../../include/obj/NiPSysMeshUpdateModifier.h"
#include "../../include/obj/NiPSysPlanarCollider.h"
#include "../../include/obj/NiPSysSphericalCollider.h"
#include "../../include/obj/NiPSysPositionModifier.h"
#include "../../include/obj/NiPSysResetOnLoopCtlr.h"
#include "../../include/obj/NiPSysRotationModifier.h"
#include "../../include/obj/NiPSysSpawnModifier.h"
#include "../../include/obj/NiPSysSphereEmitter.h"
#include "../../include/obj/NiPSysUpdateCtlr.h"
#include "../../include/obj/NiLODData.h"
#include "../../include/obj/NiRangeLODData.h"
#include "../../include/obj/NiScreenLODData.h"
#include "../../include/obj/NiRotatingParticles.h"
#include "../../include/obj/NiSequenceStreamHelper.h"
#include "../../include/obj/NiShadeProperty.h"
#include "../../include/obj/NiSkinData.h"
#include "../../include/obj/NiSkinInstance.h"
#include "../../include/obj/NiTriShapeSkinController.h"
#include "../../include/obj/NiClodSkinInstance.h"
#include "../../include/obj/NiSkinPartition.h"
#include "../../include/obj/NiTexture.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/obj/NiSpecularProperty.h"
#include "../../include/obj/NiSphericalCollider.h"
#include "../../include/obj/NiSpotLight.h"
#include "../../include/obj/NiStencilProperty.h"
#include "../../include/obj/NiStringExtraData.h"
#include "../../include/obj/NiStringPalette.h"
#include "../../include/obj/NiStringsExtraData.h"
#include "../../include/obj/NiTextKeyExtraData.h"
#include "../../include/obj/NiTextureEffect.h"
#include "../../include/obj/NiTextureModeProperty.h"
#include "../../include/obj/NiImage.h"
#include "../../include/obj/NiTextureProperty.h"
#include "../../include/obj/NiMultiTextureProperty.h"
#include "../../include/obj/NiTexturingProperty.h"
#include "../../include/obj/NiTransformData.h"
#include "../../include/obj/NiTriShape.h"
#include "../../include/obj/NiTriShapeData.h"
#include "../../include/obj/NiTriStrips.h"
#include "../../include/obj/NiTriStripsData.h"
#include "../../include/obj/NiClod.h"
#include "../../include/obj/NiClodData.h"
#include "../../include/obj/NiUVController.h"
#include "../../include/obj/NiUVData.h"
#include "../../include/obj/NiVectorExtraData.h"
#include "../../include/obj/NiVertexColorProperty.h"
#include "../../include/obj/NiVertWeightsExtraData.h"
#include "../../include/obj/NiVisData.h"
#include "../../include/obj/NiWireframeProperty.h"
#include "../../include/obj/NiZBufferProperty.h"
#include "../../include/obj/RootCollisionNode.h"
#include "../../include/obj/NiRawImageData.h"

namespace Niflib {
	void RegisterObjects() {

		ObjectRegistry::RegisterObject( "NiObject", NiObject::Create );
		ObjectRegistry::RegisterObject( "NiParticleModifier", NiParticleModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysCollider", NiPSysCollider::Create );
		ObjectRegistry::RegisterObject( "bhkRefObject", bhkRefObject::Create );
		ObjectRegistry::RegisterObject( "bhkSerializable", bhkSerializable::Create );
		ObjectRegistry::RegisterObject( "bhkWorldObject", bhkWorldObject::Create );
		ObjectRegistry::RegisterObject( "bhkPhantom", bhkPhantom::Create );
		ObjectRegistry::RegisterObject( "bhkShapePhantom", bhkShapePhantom::Create );
		ObjectRegistry::RegisterObject( "bhkSimpleShapePhantom", bhkSimpleShapePhantom::Create );
		ObjectRegistry::RegisterObject( "bhkEntity", bhkEntity::Create );
		ObjectRegistry::RegisterObject( "bhkRigidBody", bhkRigidBody::Create );
		ObjectRegistry::RegisterObject( "bhkRigidBodyT", bhkRigidBodyT::Create );
		ObjectRegistry::RegisterObject( "bhkConstraint", bhkConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkLimitedHingeConstraint", bhkLimitedHingeConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkMalleableConstraint", bhkMalleableConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkStiffSpringConstraint", bhkStiffSpringConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkRagdollConstraint", bhkRagdollConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkPrismaticConstraint", bhkPrismaticConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkHingeConstraint", bhkHingeConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkShape", bhkShape::Create );
		ObjectRegistry::RegisterObject( "bhkTransformShape", bhkTransformShape::Create );
		ObjectRegistry::RegisterObject( "bhkSphereRepShape", bhkSphereRepShape::Create );
		ObjectRegistry::RegisterObject( "bhkConvexShape", bhkConvexShape::Create );
		ObjectRegistry::RegisterObject( "bhkSphereShape", bhkSphereShape::Create );
		ObjectRegistry::RegisterObject( "bhkCapsuleShape", bhkCapsuleShape::Create );
		ObjectRegistry::RegisterObject( "bhkBoxShape", bhkBoxShape::Create );
		ObjectRegistry::RegisterObject( "bhkConvexVerticesShape", bhkConvexVerticesShape::Create );
		ObjectRegistry::RegisterObject( "bhkConvexTransformShape", bhkConvexTransformShape::Create );
		ObjectRegistry::RegisterObject( "bhkMultiSphereShape", bhkMultiSphereShape::Create );
		ObjectRegistry::RegisterObject( "bhkBvTreeShape", bhkBvTreeShape::Create );
		ObjectRegistry::RegisterObject( "bhkMoppBvTreeShape", bhkMoppBvTreeShape::Create );
		ObjectRegistry::RegisterObject( "bhkShapeCollection", bhkShapeCollection::Create );
		ObjectRegistry::RegisterObject( "bhkListShape", bhkListShape::Create );
		ObjectRegistry::RegisterObject( "bhkPackedNiTriStripsShape", bhkPackedNiTriStripsShape::Create );
		ObjectRegistry::RegisterObject( "bhkNiTriStripsShape", bhkNiTriStripsShape::Create );
		ObjectRegistry::RegisterObject( "NiExtraData", NiExtraData::Create );
		ObjectRegistry::RegisterObject( "NiInterpolator", NiInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiKeyBasedInterpolator", NiKeyBasedInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiFloatInterpolator", NiFloatInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiTransformInterpolator", NiTransformInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiPoint3Interpolator", NiPoint3Interpolator::Create );
		ObjectRegistry::RegisterObject( "NiPathInterpolator", NiPathInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBoolInterpolator", NiBoolInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBoolTimelineInterpolator", NiBoolTimelineInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBlendInterpolator", NiBlendInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBSplineInterpolator", NiBSplineInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiObjectNET", NiObjectNET::Create );
		ObjectRegistry::RegisterObject( "NiCollisionObject", NiCollisionObject::Create );
		ObjectRegistry::RegisterObject( "NiCollisionData", NiCollisionData::Create );
		ObjectRegistry::RegisterObject( "bhkNiCollisionObject", bhkNiCollisionObject::Create );
		ObjectRegistry::RegisterObject( "bhkCollisionObject", bhkCollisionObject::Create );
		ObjectRegistry::RegisterObject( "bhkBlendCollisionObject", bhkBlendCollisionObject::Create );
		ObjectRegistry::RegisterObject( "bhkPCollisionObject", bhkPCollisionObject::Create );
		ObjectRegistry::RegisterObject( "bhkSPCollisionObject", bhkSPCollisionObject::Create );
		ObjectRegistry::RegisterObject( "NiAVObject", NiAVObject::Create );
		ObjectRegistry::RegisterObject( "NiDynamicEffect", NiDynamicEffect::Create );
		ObjectRegistry::RegisterObject( "NiLight", NiLight::Create );
		ObjectRegistry::RegisterObject( "NiProperty", NiProperty::Create );
		ObjectRegistry::RegisterObject( "NiPSysModifier", NiPSysModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitter", NiPSysEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSysVolumeEmitter", NiPSysVolumeEmitter::Create );
		ObjectRegistry::RegisterObject( "NiTimeController", NiTimeController::Create );
		ObjectRegistry::RegisterObject( "NiInterpController", NiInterpController::Create );
		ObjectRegistry::RegisterObject( "NiMultiTargetTransformController", NiMultiTargetTransformController::Create );
		ObjectRegistry::RegisterObject( "NiGeomMorpherController", NiGeomMorpherController::Create );
		ObjectRegistry::RegisterObject( "NiSingleInterpController", NiSingleInterpController::Create );
		ObjectRegistry::RegisterObject( "NiKeyframeController", NiKeyframeController::Create );
		ObjectRegistry::RegisterObject( "NiTransformController", NiTransformController::Create );
		ObjectRegistry::RegisterObject( "NiPSysModifierCtlr", NiPSysModifierCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterCtlr", NiPSysEmitterCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysModifierBoolCtlr", NiPSysModifierBoolCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysModifierActiveCtlr", NiPSysModifierActiveCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysModifierFloatCtlr", NiPSysModifierFloatCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterDeclinationCtlr", NiPSysEmitterDeclinationCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterDeclinationVarCtlr", NiPSysEmitterDeclinationVarCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterInitialRadiusCtlr", NiPSysEmitterInitialRadiusCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterLifeSpanCtlr", NiPSysEmitterLifeSpanCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterSpeedCtlr", NiPSysEmitterSpeedCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysGravityStrengthCtlr", NiPSysGravityStrengthCtlr::Create );
		ObjectRegistry::RegisterObject( "NiFloatInterpController", NiFloatInterpController::Create );
		ObjectRegistry::RegisterObject( "NiFlipController", NiFlipController::Create );
		ObjectRegistry::RegisterObject( "NiAlphaController", NiAlphaController::Create );
		ObjectRegistry::RegisterObject( "NiTextureTransformController", NiTextureTransformController::Create );
		ObjectRegistry::RegisterObject( "NiLightDimmerController", NiLightDimmerController::Create );
		ObjectRegistry::RegisterObject( "NiBoolInterpController", NiBoolInterpController::Create );
		ObjectRegistry::RegisterObject( "NiVisController", NiVisController::Create );
		ObjectRegistry::RegisterObject( "NiPoint3InterpController", NiPoint3InterpController::Create );
		ObjectRegistry::RegisterObject( "NiMaterialColorController", NiMaterialColorController::Create );
		ObjectRegistry::RegisterObject( "NiLightColorController", NiLightColorController::Create );
		ObjectRegistry::RegisterObject( "NiExtraDataController", NiExtraDataController::Create );
		ObjectRegistry::RegisterObject( "NiFloatExtraDataController", NiFloatExtraDataController::Create );
		ObjectRegistry::RegisterObject( "NiBoneLODController", NiBoneLODController::Create );
		ObjectRegistry::RegisterObject( "NiBSBoneLODController", NiBSBoneLODController::Create );
		ObjectRegistry::RegisterObject( "NiGeometry", NiGeometry::Create );
		ObjectRegistry::RegisterObject( "NiTriBasedGeom", NiTriBasedGeom::Create );
		ObjectRegistry::RegisterObject( "NiGeometryData", NiGeometryData::Create );
		ObjectRegistry::RegisterObject( "NiTriBasedGeomData", NiTriBasedGeomData::Create );
		ObjectRegistry::RegisterObject( "bhkBlendController", bhkBlendController::Create );
		ObjectRegistry::RegisterObject( "BSBound", BSBound::Create );
		ObjectRegistry::RegisterObject( "BSFurnitureMarker", BSFurnitureMarker::Create );
		ObjectRegistry::RegisterObject( "BSParentVelocityModifier", BSParentVelocityModifier::Create );
		ObjectRegistry::RegisterObject( "BSPSysArrayEmitter", BSPSysArrayEmitter::Create );
		ObjectRegistry::RegisterObject( "BSWindModifier", BSWindModifier::Create );
		ObjectRegistry::RegisterObject( "hkPackedNiTriStripsData", hkPackedNiTriStripsData::Create );
		ObjectRegistry::RegisterObject( "NiAlphaProperty", NiAlphaProperty::Create );
		ObjectRegistry::RegisterObject( "NiAmbientLight", NiAmbientLight::Create );
		ObjectRegistry::RegisterObject( "NiParticlesData", NiParticlesData::Create );
		ObjectRegistry::RegisterObject( "NiRotatingParticlesData", NiRotatingParticlesData::Create );
		ObjectRegistry::RegisterObject( "NiAutoNormalParticlesData", NiAutoNormalParticlesData::Create );
		ObjectRegistry::RegisterObject( "NiPSysData", NiPSysData::Create );
		ObjectRegistry::RegisterObject( "NiMeshPSysData", NiMeshPSysData::Create );
		ObjectRegistry::RegisterObject( "NiBinaryExtraData", NiBinaryExtraData::Create );
		ObjectRegistry::RegisterObject( "NiBinaryVoxelExtraData", NiBinaryVoxelExtraData::Create );
		ObjectRegistry::RegisterObject( "NiBinaryVoxelData", NiBinaryVoxelData::Create );
		ObjectRegistry::RegisterObject( "NiBlendBoolInterpolator", NiBlendBoolInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBlendFloatInterpolator", NiBlendFloatInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBlendPoint3Interpolator", NiBlendPoint3Interpolator::Create );
		ObjectRegistry::RegisterObject( "NiBlendTransformInterpolator", NiBlendTransformInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBoolData", NiBoolData::Create );
		ObjectRegistry::RegisterObject( "NiBooleanExtraData", NiBooleanExtraData::Create );
		ObjectRegistry::RegisterObject( "NiBSplineBasisData", NiBSplineBasisData::Create );
		ObjectRegistry::RegisterObject( "NiBSplineFloatInterpolator", NiBSplineFloatInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBSplineCompFloatInterpolator", NiBSplineCompFloatInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBSplinePoint3Interpolator", NiBSplinePoint3Interpolator::Create );
		ObjectRegistry::RegisterObject( "NiBSplineCompPoint3Interpolator", NiBSplineCompPoint3Interpolator::Create );
		ObjectRegistry::RegisterObject( "NiBSplineTransformInterpolator", NiBSplineTransformInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBSplineCompTransformInterpolator", NiBSplineCompTransformInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiBSplineData", NiBSplineData::Create );
		ObjectRegistry::RegisterObject( "NiCamera", NiCamera::Create );
		ObjectRegistry::RegisterObject( "NiColorData", NiColorData::Create );
		ObjectRegistry::RegisterObject( "NiColorExtraData", NiColorExtraData::Create );
		ObjectRegistry::RegisterObject( "NiControllerManager", NiControllerManager::Create );
		ObjectRegistry::RegisterObject( "NiSequence", NiSequence::Create );
		ObjectRegistry::RegisterObject( "NiControllerSequence", NiControllerSequence::Create );
		ObjectRegistry::RegisterObject( "NiAVObjectPalette", NiAVObjectPalette::Create );
		ObjectRegistry::RegisterObject( "NiDefaultAVObjectPalette", NiDefaultAVObjectPalette::Create );
		ObjectRegistry::RegisterObject( "NiDirectionalLight", NiDirectionalLight::Create );
		ObjectRegistry::RegisterObject( "NiDitherProperty", NiDitherProperty::Create );
		ObjectRegistry::RegisterObject( "NiRollController", NiRollController::Create );
		ObjectRegistry::RegisterObject( "NiFloatData", NiFloatData::Create );
		ObjectRegistry::RegisterObject( "NiFloatExtraData", NiFloatExtraData::Create );
		ObjectRegistry::RegisterObject( "NiFloatsExtraData", NiFloatsExtraData::Create );
		ObjectRegistry::RegisterObject( "NiFogProperty", NiFogProperty::Create );
		ObjectRegistry::RegisterObject( "NiGravity", NiGravity::Create );
		ObjectRegistry::RegisterObject( "NiIntegerExtraData", NiIntegerExtraData::Create );
		ObjectRegistry::RegisterObject( "BSXFlags", BSXFlags::Create );
		ObjectRegistry::RegisterObject( "NiIntegersExtraData", NiIntegersExtraData::Create );
		ObjectRegistry::RegisterObject( "BSKeyframeController", BSKeyframeController::Create );
		ObjectRegistry::RegisterObject( "NiKeyframeData", NiKeyframeData::Create );
		ObjectRegistry::RegisterObject( "NiLookAtController", NiLookAtController::Create );
		ObjectRegistry::RegisterObject( "NiLookAtInterpolator", NiLookAtInterpolator::Create );
		ObjectRegistry::RegisterObject( "NiMaterialProperty", NiMaterialProperty::Create );
		ObjectRegistry::RegisterObject( "NiMorphData", NiMorphData::Create );
		ObjectRegistry::RegisterObject( "NiNode", NiNode::Create );
		ObjectRegistry::RegisterObject( "NiBone", NiBone::Create );
		ObjectRegistry::RegisterObject( "AvoidNode", AvoidNode::Create );
		ObjectRegistry::RegisterObject( "FxWidget", FxWidget::Create );
		ObjectRegistry::RegisterObject( "FxButton", FxButton::Create );
		ObjectRegistry::RegisterObject( "FxRadioButton", FxRadioButton::Create );
		ObjectRegistry::RegisterObject( "NiBillboardNode", NiBillboardNode::Create );
		ObjectRegistry::RegisterObject( "NiBSAnimationNode", NiBSAnimationNode::Create );
		ObjectRegistry::RegisterObject( "NiBSParticleNode", NiBSParticleNode::Create );
		ObjectRegistry::RegisterObject( "NiSwitchNode", NiSwitchNode::Create );
		ObjectRegistry::RegisterObject( "NiLODNode", NiLODNode::Create );
		ObjectRegistry::RegisterObject( "NiPalette", NiPalette::Create );
		ObjectRegistry::RegisterObject( "NiParticleBomb", NiParticleBomb::Create );
		ObjectRegistry::RegisterObject( "NiParticleColorModifier", NiParticleColorModifier::Create );
		ObjectRegistry::RegisterObject( "NiParticleGrowFade", NiParticleGrowFade::Create );
		ObjectRegistry::RegisterObject( "NiParticleMeshModifier", NiParticleMeshModifier::Create );
		ObjectRegistry::RegisterObject( "NiParticleRotation", NiParticleRotation::Create );
		ObjectRegistry::RegisterObject( "NiParticles", NiParticles::Create );
		ObjectRegistry::RegisterObject( "NiAutoNormalParticles", NiAutoNormalParticles::Create );
		ObjectRegistry::RegisterObject( "NiParticleMeshes", NiParticleMeshes::Create );
		ObjectRegistry::RegisterObject( "NiParticleMeshesData", NiParticleMeshesData::Create );
		ObjectRegistry::RegisterObject( "NiParticleSystem", NiParticleSystem::Create );
		ObjectRegistry::RegisterObject( "NiMeshParticleSystem", NiMeshParticleSystem::Create );
		ObjectRegistry::RegisterObject( "NiParticleSystemController", NiParticleSystemController::Create );
		ObjectRegistry::RegisterObject( "NiBSPArrayController", NiBSPArrayController::Create );
		ObjectRegistry::RegisterObject( "NiPathController", NiPathController::Create );
		ObjectRegistry::RegisterObject( "NiPixelData", NiPixelData::Create );
		ObjectRegistry::RegisterObject( "NiPlanarCollider", NiPlanarCollider::Create );
		ObjectRegistry::RegisterObject( "NiPointLight", NiPointLight::Create );
		ObjectRegistry::RegisterObject( "NiPosData", NiPosData::Create );
		ObjectRegistry::RegisterObject( "NiPSysAgeDeathModifier", NiPSysAgeDeathModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysBombModifier", NiPSysBombModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysBoundUpdateModifier", NiPSysBoundUpdateModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysBoxEmitter", NiPSysBoxEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSysColliderManager", NiPSysColliderManager::Create );
		ObjectRegistry::RegisterObject( "NiPSysColorModifier", NiPSysColorModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysCylinderEmitter", NiPSysCylinderEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSysDragModifier", NiPSysDragModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterCtlrData", NiPSysEmitterCtlrData::Create );
		ObjectRegistry::RegisterObject( "NiPSysGravityModifier", NiPSysGravityModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysGrowFadeModifier", NiPSysGrowFadeModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysMeshEmitter", NiPSysMeshEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSysMeshUpdateModifier", NiPSysMeshUpdateModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysPlanarCollider", NiPSysPlanarCollider::Create );
		ObjectRegistry::RegisterObject( "NiPSysSphericalCollider", NiPSysSphericalCollider::Create );
		ObjectRegistry::RegisterObject( "NiPSysPositionModifier", NiPSysPositionModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysResetOnLoopCtlr", NiPSysResetOnLoopCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysRotationModifier", NiPSysRotationModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysSpawnModifier", NiPSysSpawnModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysSphereEmitter", NiPSysSphereEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSysUpdateCtlr", NiPSysUpdateCtlr::Create );
		ObjectRegistry::RegisterObject( "NiLODData", NiLODData::Create );
		ObjectRegistry::RegisterObject( "NiRangeLODData", NiRangeLODData::Create );
		ObjectRegistry::RegisterObject( "NiScreenLODData", NiScreenLODData::Create );
		ObjectRegistry::RegisterObject( "NiRotatingParticles", NiRotatingParticles::Create );
		ObjectRegistry::RegisterObject( "NiSequenceStreamHelper", NiSequenceStreamHelper::Create );
		ObjectRegistry::RegisterObject( "NiShadeProperty", NiShadeProperty::Create );
		ObjectRegistry::RegisterObject( "NiSkinData", NiSkinData::Create );
		ObjectRegistry::RegisterObject( "NiSkinInstance", NiSkinInstance::Create );
		ObjectRegistry::RegisterObject( "NiTriShapeSkinController", NiTriShapeSkinController::Create );
		ObjectRegistry::RegisterObject( "NiClodSkinInstance", NiClodSkinInstance::Create );
		ObjectRegistry::RegisterObject( "NiSkinPartition", NiSkinPartition::Create );
		ObjectRegistry::RegisterObject( "NiTexture", NiTexture::Create );
		ObjectRegistry::RegisterObject( "NiSourceTexture", NiSourceTexture::Create );
		ObjectRegistry::RegisterObject( "NiSpecularProperty", NiSpecularProperty::Create );
		ObjectRegistry::RegisterObject( "NiSphericalCollider", NiSphericalCollider::Create );
		ObjectRegistry::RegisterObject( "NiSpotLight", NiSpotLight::Create );
		ObjectRegistry::RegisterObject( "NiStencilProperty", NiStencilProperty::Create );
		ObjectRegistry::RegisterObject( "NiStringExtraData", NiStringExtraData::Create );
		ObjectRegistry::RegisterObject( "NiStringPalette", NiStringPalette::Create );
		ObjectRegistry::RegisterObject( "NiStringsExtraData", NiStringsExtraData::Create );
		ObjectRegistry::RegisterObject( "NiTextKeyExtraData", NiTextKeyExtraData::Create );
		ObjectRegistry::RegisterObject( "NiTextureEffect", NiTextureEffect::Create );
		ObjectRegistry::RegisterObject( "NiTextureModeProperty", NiTextureModeProperty::Create );
		ObjectRegistry::RegisterObject( "NiImage", NiImage::Create );
		ObjectRegistry::RegisterObject( "NiTextureProperty", NiTextureProperty::Create );
		ObjectRegistry::RegisterObject( "NiMultiTextureProperty", NiMultiTextureProperty::Create );
		ObjectRegistry::RegisterObject( "NiTexturingProperty", NiTexturingProperty::Create );
		ObjectRegistry::RegisterObject( "NiTransformData", NiTransformData::Create );
		ObjectRegistry::RegisterObject( "NiTriShape", NiTriShape::Create );
		ObjectRegistry::RegisterObject( "NiTriShapeData", NiTriShapeData::Create );
		ObjectRegistry::RegisterObject( "NiTriStrips", NiTriStrips::Create );
		ObjectRegistry::RegisterObject( "NiTriStripsData", NiTriStripsData::Create );
		ObjectRegistry::RegisterObject( "NiClod", NiClod::Create );
		ObjectRegistry::RegisterObject( "NiClodData", NiClodData::Create );
		ObjectRegistry::RegisterObject( "NiUVController", NiUVController::Create );
		ObjectRegistry::RegisterObject( "NiUVData", NiUVData::Create );
		ObjectRegistry::RegisterObject( "NiVectorExtraData", NiVectorExtraData::Create );
		ObjectRegistry::RegisterObject( "NiVertexColorProperty", NiVertexColorProperty::Create );
		ObjectRegistry::RegisterObject( "NiVertWeightsExtraData", NiVertWeightsExtraData::Create );
		ObjectRegistry::RegisterObject( "NiVisData", NiVisData::Create );
		ObjectRegistry::RegisterObject( "NiWireframeProperty", NiWireframeProperty::Create );
		ObjectRegistry::RegisterObject( "NiZBufferProperty", NiZBufferProperty::Create );
		ObjectRegistry::RegisterObject( "RootCollisionNode", RootCollisionNode::Create );
		ObjectRegistry::RegisterObject( "NiRawImageData", NiRawImageData::Create );

	}
}
