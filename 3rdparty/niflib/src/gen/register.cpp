/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/ObjectRegistry.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/Ni3dsAlphaAnimator.h"
#include "../../include/obj/Ni3dsAnimationNode.h"
#include "../../include/obj/Ni3dsColorAnimator.h"
#include "../../include/obj/Ni3dsMorphShape.h"
#include "../../include/obj/Ni3dsParticleSystem.h"
#include "../../include/obj/Ni3dsPathController.h"
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
#include "../../include/obj/bhkBallAndSocketConstraint.h"
#include "../../include/obj/bhkBallSocketConstraintChain.h"
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
#include "../../include/obj/bhkMeshShape.h"
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
#include "../../include/obj/NiTransparentProperty.h"
#include "../../include/obj/NiPSysModifier.h"
#include "../../include/obj/NiPSysEmitter.h"
#include "../../include/obj/NiPSysVolumeEmitter.h"
#include "../../include/obj/NiTimeController.h"
#include "../../include/obj/NiInterpController.h"
#include "../../include/obj/NiMultiTargetTransformController.h"
#include "../../include/obj/NiGeomMorpherController.h"
#include "../../include/obj/NiMorphController.h"
#include "../../include/obj/NiMorpherController.h"
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
#include "../../include/obj/AbstractAdditionalGeometryData.h"
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
#include "../../include/obj/BSRotAccumTransfInterpolator.h"
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
#include "../../include/obj/ATextureRenderData.h"
#include "../../include/obj/NiPersistentSrcTextureRendererData.h"
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
#include "../../include/obj/BSPSysInheritVelocityModifier.h"
#include "../../include/obj/BSPSysHavokUpdateModifier.h"
#include "../../include/obj/BSPSysRecycleBoundModifier.h"
#include "../../include/obj/BSPSysSubTexModifier.h"
#include "../../include/obj/NiPSysPlanarCollider.h"
#include "../../include/obj/NiPSysSphericalCollider.h"
#include "../../include/obj/NiPSysPositionModifier.h"
#include "../../include/obj/NiPSysResetOnLoopCtlr.h"
#include "../../include/obj/NiPSysRotationModifier.h"
#include "../../include/obj/NiPSysSpawnModifier.h"
#include "../../include/obj/NiPSysSphereEmitter.h"
#include "../../include/obj/NiPSysUpdateCtlr.h"
#include "../../include/obj/NiPSysFieldModifier.h"
#include "../../include/obj/NiPSysVortexFieldModifier.h"
#include "../../include/obj/NiPSysGravityFieldModifier.h"
#include "../../include/obj/NiPSysDragFieldModifier.h"
#include "../../include/obj/NiPSysTurbulenceFieldModifier.h"
#include "../../include/obj/BSPSysLODModifier.h"
#include "../../include/obj/BSPSysScaleModifier.h"
#include "../../include/obj/NiPSysFieldMagnitudeCtlr.h"
#include "../../include/obj/NiPSysFieldAttenuationCtlr.h"
#include "../../include/obj/NiPSysFieldMaxDistanceCtlr.h"
#include "../../include/obj/NiPSysAirFieldAirFrictionCtlr.h"
#include "../../include/obj/NiPSysAirFieldInheritVelocityCtlr.h"
#include "../../include/obj/NiPSysAirFieldSpreadCtlr.h"
#include "../../include/obj/NiPSysInitialRotSpeedCtlr.h"
#include "../../include/obj/NiPSysInitialRotSpeedVarCtlr.h"
#include "../../include/obj/NiPSysInitialRotAngleCtlr.h"
#include "../../include/obj/NiPSysInitialRotAngleVarCtlr.h"
#include "../../include/obj/NiPSysEmitterPlanarAngleCtlr.h"
#include "../../include/obj/NiPSysEmitterPlanarAngleVarCtlr.h"
#include "../../include/obj/NiPSysAirFieldModifier.h"
#include "../../include/obj/NiPSysTrailEmitter.h"
#include "../../include/obj/NiLightIntensityController.h"
#include "../../include/obj/NiPSysRadialFieldModifier.h"
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
#include "../../include/obj/NiEnvMappedTriShape.h"
#include "../../include/obj/NiEnvMappedTriShapeData.h"
#include "../../include/obj/NiBezierTriangle4.h"
#include "../../include/obj/NiBezierMesh.h"
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
#include "../../include/obj/NiSortAdjustNode.h"
#include "../../include/obj/NiSourceCubeMap.h"
#include "../../include/obj/NiPhysXProp.h"
#include "../../include/obj/NiPhysXPropDesc.h"
#include "../../include/obj/NiPhysXActorDesc.h"
#include "../../include/obj/NiPhysXBodyDesc.h"
#include "../../include/obj/NiPhysXD6JointDesc.h"
#include "../../include/obj/NiPhysXShapeDesc.h"
#include "../../include/obj/NiPhysXMeshDesc.h"
#include "../../include/obj/NiPhysXMaterialDesc.h"
#include "../../include/obj/NiPhysXKinematicSrc.h"
#include "../../include/obj/NiPhysXTransformDest.h"
#include "../../include/obj/NiArkAnimationExtraData.h"
#include "../../include/obj/NiArkImporterExtraData.h"
#include "../../include/obj/NiArkTextureExtraData.h"
#include "../../include/obj/NiArkViewportInfoExtraData.h"
#include "../../include/obj/NiArkShaderExtraData.h"
#include "../../include/obj/NiLines.h"
#include "../../include/obj/NiLinesData.h"
#include "../../include/obj/NiScreenElementsData.h"
#include "../../include/obj/NiScreenElements.h"
#include "../../include/obj/NiRoomGroup.h"
#include "../../include/obj/NiRoom.h"
#include "../../include/obj/NiPortal.h"
#include "../../include/obj/BSFadeNode.h"
#include "../../include/obj/BSShaderProperty.h"
#include "../../include/obj/BSShaderLightingProperty.h"
#include "../../include/obj/BSShaderNoLightingProperty.h"
#include "../../include/obj/BSShaderPPLightingProperty.h"
#include "../../include/obj/BSEffectShaderPropertyFloatController.h"
#include "../../include/obj/BSEffectShaderPropertyColorController.h"
#include "../../include/obj/BSLightingShaderPropertyFloatController.h"
#include "../../include/obj/BSLightingShaderPropertyColorController.h"
#include "../../include/obj/BSNiAlphaPropertyTestRefController.h"
#include "../../include/obj/BSProceduralLightningController.h"
#include "../../include/obj/BSShaderTextureSet.h"
#include "../../include/obj/WaterShaderProperty.h"
#include "../../include/obj/SkyShaderProperty.h"
#include "../../include/obj/TileShaderProperty.h"
#include "../../include/obj/DistantLODShaderProperty.h"
#include "../../include/obj/BSDistantTreeShaderProperty.h"
#include "../../include/obj/TallGrassShaderProperty.h"
#include "../../include/obj/VolumetricFogShaderProperty.h"
#include "../../include/obj/HairShaderProperty.h"
#include "../../include/obj/Lighting30ShaderProperty.h"
#include "../../include/obj/BSLightingShaderProperty.h"
#include "../../include/obj/BSEffectShaderProperty.h"
#include "../../include/obj/BSWaterShaderProperty.h"
#include "../../include/obj/BSSkyShaderProperty.h"
#include "../../include/obj/BSDismemberSkinInstance.h"
#include "../../include/obj/BSDecalPlacementVectorExtraData.h"
#include "../../include/obj/BSPSysSimpleColorModifier.h"
#include "../../include/obj/BSValueNode.h"
#include "../../include/obj/BSStripParticleSystem.h"
#include "../../include/obj/BSStripPSysData.h"
#include "../../include/obj/BSPSysStripUpdateModifier.h"
#include "../../include/obj/BSMaterialEmittanceMultController.h"
#include "../../include/obj/BSMasterParticleSystem.h"
#include "../../include/obj/BSPSysMultiTargetEmitterCtlr.h"
#include "../../include/obj/BSRefractionStrengthController.h"
#include "../../include/obj/BSOrderedNode.h"
#include "../../include/obj/BSBlastNode.h"
#include "../../include/obj/BSDamageStage.h"
#include "../../include/obj/BSRefractionFirePeriodController.h"
#include "../../include/obj/bhkConvexListShape.h"
#include "../../include/obj/BSTreadTransfInterpolator.h"
#include "../../include/obj/BSAnimNotes.h"
#include "../../include/obj/bhkLiquidAction.h"
#include "../../include/obj/BSMultiBoundNode.h"
#include "../../include/obj/BSMultiBound.h"
#include "../../include/obj/BSMultiBoundData.h"
#include "../../include/obj/BSMultiBoundOBB.h"
#include "../../include/obj/BSMultiBoundSphere.h"
#include "../../include/obj/BSSegmentedTriShape.h"
#include "../../include/obj/BSMultiBoundAABB.h"
#include "../../include/obj/NiAdditionalGeometryData.h"
#include "../../include/obj/BSPackedAdditionalGeometryData.h"
#include "../../include/obj/BSWArray.h"
#include "../../include/obj/bhkAabbPhantom.h"
#include "../../include/obj/BSFrustumFOVController.h"
#include "../../include/obj/BSDebrisNode.h"
#include "../../include/obj/bhkBreakableConstraint.h"
#include "../../include/obj/bhkOrientHingedBodyAction.h"
#include "../../include/obj/NiDataStream.h"
#include "../../include/obj/NiRenderObject.h"
#include "../../include/obj/NiMeshModifier.h"
#include "../../include/obj/NiMesh.h"
#include "../../include/obj/NiMorphWeightsController.h"
#include "../../include/obj/NiMorphMeshModifier.h"
#include "../../include/obj/NiSkinningMeshModifier.h"
#include "../../include/obj/NiInstancingMeshModifier.h"
#include "../../include/obj/NiSkinningLODController.h"
#include "../../include/obj/NiPSParticleSystem.h"
#include "../../include/obj/NiPSMeshParticleSystem.h"
#include "../../include/obj/NiPSEmitParticlesCtlr.h"
#include "../../include/obj/NiPSForceActiveCtlr.h"
#include "../../include/obj/NiPSSimulator.h"
#include "../../include/obj/NiPSSimulatorStep.h"
#include "../../include/obj/NiPSSimulatorGeneralStep.h"
#include "../../include/obj/NiPSSimulatorForcesStep.h"
#include "../../include/obj/NiPSSimulatorCollidersStep.h"
#include "../../include/obj/NiPSSimulatorMeshAlignStep.h"
#include "../../include/obj/NiPSSimulatorFinalStep.h"
#include "../../include/obj/NiPSFacingQuadGenerator.h"
#include "../../include/obj/NiShadowGenerator.h"
#include "../../include/obj/NiPSBoundUpdater.h"
#include "../../include/obj/NiPSDragForce.h"
#include "../../include/obj/NiPSGravityForce.h"
#include "../../include/obj/NiPSBoxEmitter.h"
#include "../../include/obj/NiPSMeshEmitter.h"
#include "../../include/obj/NiPSGravityStrengthCtlr.h"
#include "../../include/obj/NiPSPlanarCollider.h"
#include "../../include/obj/NiPSEmitterSpeedCtlr.h"
#include "../../include/obj/NiPSEmitterRadiusCtlr.h"
#include "../../include/obj/NiPSResetOnLoopCtlr.h"
#include "../../include/obj/NiPSSphereEmitter.h"
#include "../../include/obj/NiPSCylinderEmitter.h"
#include "../../include/obj/NiPSEmitterDeclinationCtlr.h"
#include "../../include/obj/NiPSEmitterDeclinationVarCtlr.h"
#include "../../include/obj/NiPSEmitterPlanarAngleCtlr.h"
#include "../../include/obj/NiPSEmitterPlanarAngleVarCtlr.h"
#include "../../include/obj/NiPSEmitterRotAngleCtlr.h"
#include "../../include/obj/NiPSEmitterRotAngleVarCtlr.h"
#include "../../include/obj/NiPSEmitterRotSpeedCtlr.h"
#include "../../include/obj/NiPSEmitterRotSpeedVarCtlr.h"
#include "../../include/obj/NiPSEmitterLifeSpanCtlr.h"
#include "../../include/obj/NiPSBombForce.h"
#include "../../include/obj/NiPSSphericalCollider.h"
#include "../../include/obj/NiPSSpawner.h"
#include "../../include/obj/NiSequenceData.h"
#include "../../include/obj/NiTransformEvaluator.h"
#include "../../include/obj/NiBSplineCompTransformEvaluator.h"
#include "../../include/obj/NiMeshHWInstance.h"
#include "../../include/obj/NiFurSpringController.h"
#include "../../include/obj/CStreamableAssetData.h"
#include "../../include/obj/bhkCompressedMeshShape.h"
#include "../../include/obj/bhkCompressedMeshShapeData.h"
#include "../../include/obj/BSInvMarker.h"
#include "../../include/obj/BSBoneLODExtraData.h"
#include "../../include/obj/BSBehaviorGraphExtraData.h"
#include "../../include/obj/BSLagBoneController.h"
#include "../../include/obj/BSLODTriShape.h"
#include "../../include/obj/BSFurnitureMarkerNode.h"
#include "../../include/obj/BSLeafAnimNode.h"
#include "../../include/obj/BSTreeNode.h"

namespace Niflib {
	void RegisterObjects() {

		ObjectRegistry::RegisterObject( "NiObject", NiObject::Create );
		ObjectRegistry::RegisterObject( "Ni3dsAlphaAnimator", Ni3dsAlphaAnimator::Create );
		ObjectRegistry::RegisterObject( "Ni3dsAnimationNode", Ni3dsAnimationNode::Create );
		ObjectRegistry::RegisterObject( "Ni3dsColorAnimator", Ni3dsColorAnimator::Create );
		ObjectRegistry::RegisterObject( "Ni3dsMorphShape", Ni3dsMorphShape::Create );
		ObjectRegistry::RegisterObject( "Ni3dsParticleSystem", Ni3dsParticleSystem::Create );
		ObjectRegistry::RegisterObject( "Ni3dsPathController", Ni3dsPathController::Create );
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
		ObjectRegistry::RegisterObject( "bhkBallAndSocketConstraint", bhkBallAndSocketConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkBallSocketConstraintChain", bhkBallSocketConstraintChain::Create );
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
		ObjectRegistry::RegisterObject( "bhkMeshShape", bhkMeshShape::Create );
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
		ObjectRegistry::RegisterObject( "NiTransparentProperty", NiTransparentProperty::Create );
		ObjectRegistry::RegisterObject( "NiPSysModifier", NiPSysModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitter", NiPSysEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSysVolumeEmitter", NiPSysVolumeEmitter::Create );
		ObjectRegistry::RegisterObject( "NiTimeController", NiTimeController::Create );
		ObjectRegistry::RegisterObject( "NiInterpController", NiInterpController::Create );
		ObjectRegistry::RegisterObject( "NiMultiTargetTransformController", NiMultiTargetTransformController::Create );
		ObjectRegistry::RegisterObject( "NiGeomMorpherController", NiGeomMorpherController::Create );
		ObjectRegistry::RegisterObject( "NiMorphController", NiMorphController::Create );
		ObjectRegistry::RegisterObject( "NiMorpherController", NiMorpherController::Create );
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
		ObjectRegistry::RegisterObject( "AbstractAdditionalGeometryData", AbstractAdditionalGeometryData::Create );
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
		ObjectRegistry::RegisterObject( "BSRotAccumTransfInterpolator", BSRotAccumTransfInterpolator::Create );
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
		ObjectRegistry::RegisterObject( "ATextureRenderData", ATextureRenderData::Create );
		ObjectRegistry::RegisterObject( "NiPersistentSrcTextureRendererData", NiPersistentSrcTextureRendererData::Create );
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
		ObjectRegistry::RegisterObject( "BSPSysInheritVelocityModifier", BSPSysInheritVelocityModifier::Create );
		ObjectRegistry::RegisterObject( "BSPSysHavokUpdateModifier", BSPSysHavokUpdateModifier::Create );
		ObjectRegistry::RegisterObject( "BSPSysRecycleBoundModifier", BSPSysRecycleBoundModifier::Create );
		ObjectRegistry::RegisterObject( "BSPSysSubTexModifier", BSPSysSubTexModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysPlanarCollider", NiPSysPlanarCollider::Create );
		ObjectRegistry::RegisterObject( "NiPSysSphericalCollider", NiPSysSphericalCollider::Create );
		ObjectRegistry::RegisterObject( "NiPSysPositionModifier", NiPSysPositionModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysResetOnLoopCtlr", NiPSysResetOnLoopCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysRotationModifier", NiPSysRotationModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysSpawnModifier", NiPSysSpawnModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysSphereEmitter", NiPSysSphereEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSysUpdateCtlr", NiPSysUpdateCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysFieldModifier", NiPSysFieldModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysVortexFieldModifier", NiPSysVortexFieldModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysGravityFieldModifier", NiPSysGravityFieldModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysDragFieldModifier", NiPSysDragFieldModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysTurbulenceFieldModifier", NiPSysTurbulenceFieldModifier::Create );
		ObjectRegistry::RegisterObject( "BSPSysLODModifier", BSPSysLODModifier::Create );
		ObjectRegistry::RegisterObject( "BSPSysScaleModifier", BSPSysScaleModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysFieldMagnitudeCtlr", NiPSysFieldMagnitudeCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysFieldAttenuationCtlr", NiPSysFieldAttenuationCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysFieldMaxDistanceCtlr", NiPSysFieldMaxDistanceCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysAirFieldAirFrictionCtlr", NiPSysAirFieldAirFrictionCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysAirFieldInheritVelocityCtlr", NiPSysAirFieldInheritVelocityCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysAirFieldSpreadCtlr", NiPSysAirFieldSpreadCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysInitialRotSpeedCtlr", NiPSysInitialRotSpeedCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysInitialRotSpeedVarCtlr", NiPSysInitialRotSpeedVarCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysInitialRotAngleCtlr", NiPSysInitialRotAngleCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysInitialRotAngleVarCtlr", NiPSysInitialRotAngleVarCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterPlanarAngleCtlr", NiPSysEmitterPlanarAngleCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysEmitterPlanarAngleVarCtlr", NiPSysEmitterPlanarAngleVarCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSysAirFieldModifier", NiPSysAirFieldModifier::Create );
		ObjectRegistry::RegisterObject( "NiPSysTrailEmitter", NiPSysTrailEmitter::Create );
		ObjectRegistry::RegisterObject( "NiLightIntensityController", NiLightIntensityController::Create );
		ObjectRegistry::RegisterObject( "NiPSysRadialFieldModifier", NiPSysRadialFieldModifier::Create );
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
		ObjectRegistry::RegisterObject( "NiEnvMappedTriShape", NiEnvMappedTriShape::Create );
		ObjectRegistry::RegisterObject( "NiEnvMappedTriShapeData", NiEnvMappedTriShapeData::Create );
		ObjectRegistry::RegisterObject( "NiBezierTriangle4", NiBezierTriangle4::Create );
		ObjectRegistry::RegisterObject( "NiBezierMesh", NiBezierMesh::Create );
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
		ObjectRegistry::RegisterObject( "NiSortAdjustNode", NiSortAdjustNode::Create );
		ObjectRegistry::RegisterObject( "NiSourceCubeMap", NiSourceCubeMap::Create );
		ObjectRegistry::RegisterObject( "NiPhysXProp", NiPhysXProp::Create );
		ObjectRegistry::RegisterObject( "NiPhysXPropDesc", NiPhysXPropDesc::Create );
		ObjectRegistry::RegisterObject( "NiPhysXActorDesc", NiPhysXActorDesc::Create );
		ObjectRegistry::RegisterObject( "NiPhysXBodyDesc", NiPhysXBodyDesc::Create );
		ObjectRegistry::RegisterObject( "NiPhysXD6JointDesc", NiPhysXD6JointDesc::Create );
		ObjectRegistry::RegisterObject( "NiPhysXShapeDesc", NiPhysXShapeDesc::Create );
		ObjectRegistry::RegisterObject( "NiPhysXMeshDesc", NiPhysXMeshDesc::Create );
		ObjectRegistry::RegisterObject( "NiPhysXMaterialDesc", NiPhysXMaterialDesc::Create );
		ObjectRegistry::RegisterObject( "NiPhysXKinematicSrc", NiPhysXKinematicSrc::Create );
		ObjectRegistry::RegisterObject( "NiPhysXTransformDest", NiPhysXTransformDest::Create );
		ObjectRegistry::RegisterObject( "NiArkAnimationExtraData", NiArkAnimationExtraData::Create );
		ObjectRegistry::RegisterObject( "NiArkImporterExtraData", NiArkImporterExtraData::Create );
		ObjectRegistry::RegisterObject( "NiArkTextureExtraData", NiArkTextureExtraData::Create );
		ObjectRegistry::RegisterObject( "NiArkViewportInfoExtraData", NiArkViewportInfoExtraData::Create );
		ObjectRegistry::RegisterObject( "NiArkShaderExtraData", NiArkShaderExtraData::Create );
		ObjectRegistry::RegisterObject( "NiLines", NiLines::Create );
		ObjectRegistry::RegisterObject( "NiLinesData", NiLinesData::Create );
		ObjectRegistry::RegisterObject( "NiScreenElementsData", NiScreenElementsData::Create );
		ObjectRegistry::RegisterObject( "NiScreenElements", NiScreenElements::Create );
		ObjectRegistry::RegisterObject( "NiRoomGroup", NiRoomGroup::Create );
		ObjectRegistry::RegisterObject( "NiRoom", NiRoom::Create );
		ObjectRegistry::RegisterObject( "NiPortal", NiPortal::Create );
		ObjectRegistry::RegisterObject( "BSFadeNode", BSFadeNode::Create );
		ObjectRegistry::RegisterObject( "BSShaderProperty", BSShaderProperty::Create );
		ObjectRegistry::RegisterObject( "BSShaderLightingProperty", BSShaderLightingProperty::Create );
		ObjectRegistry::RegisterObject( "BSShaderNoLightingProperty", BSShaderNoLightingProperty::Create );
		ObjectRegistry::RegisterObject( "BSShaderPPLightingProperty", BSShaderPPLightingProperty::Create );
		ObjectRegistry::RegisterObject( "BSEffectShaderPropertyFloatController", BSEffectShaderPropertyFloatController::Create );
		ObjectRegistry::RegisterObject( "BSEffectShaderPropertyColorController", BSEffectShaderPropertyColorController::Create );
		ObjectRegistry::RegisterObject( "BSLightingShaderPropertyFloatController", BSLightingShaderPropertyFloatController::Create );
		ObjectRegistry::RegisterObject( "BSLightingShaderPropertyColorController", BSLightingShaderPropertyColorController::Create );
		ObjectRegistry::RegisterObject( "BSNiAlphaPropertyTestRefController", BSNiAlphaPropertyTestRefController::Create );
		ObjectRegistry::RegisterObject( "BSProceduralLightningController", BSProceduralLightningController::Create );
		ObjectRegistry::RegisterObject( "BSShaderTextureSet", BSShaderTextureSet::Create );
		ObjectRegistry::RegisterObject( "WaterShaderProperty", WaterShaderProperty::Create );
		ObjectRegistry::RegisterObject( "SkyShaderProperty", SkyShaderProperty::Create );
		ObjectRegistry::RegisterObject( "TileShaderProperty", TileShaderProperty::Create );
		ObjectRegistry::RegisterObject( "DistantLODShaderProperty", DistantLODShaderProperty::Create );
		ObjectRegistry::RegisterObject( "BSDistantTreeShaderProperty", BSDistantTreeShaderProperty::Create );
		ObjectRegistry::RegisterObject( "TallGrassShaderProperty", TallGrassShaderProperty::Create );
		ObjectRegistry::RegisterObject( "VolumetricFogShaderProperty", VolumetricFogShaderProperty::Create );
		ObjectRegistry::RegisterObject( "HairShaderProperty", HairShaderProperty::Create );
		ObjectRegistry::RegisterObject( "Lighting30ShaderProperty", Lighting30ShaderProperty::Create );
		ObjectRegistry::RegisterObject( "BSLightingShaderProperty", BSLightingShaderProperty::Create );
		ObjectRegistry::RegisterObject( "BSEffectShaderProperty", BSEffectShaderProperty::Create );
		ObjectRegistry::RegisterObject( "BSWaterShaderProperty", BSWaterShaderProperty::Create );
		ObjectRegistry::RegisterObject( "BSSkyShaderProperty", BSSkyShaderProperty::Create );
		ObjectRegistry::RegisterObject( "BSDismemberSkinInstance", BSDismemberSkinInstance::Create );
		ObjectRegistry::RegisterObject( "BSDecalPlacementVectorExtraData", BSDecalPlacementVectorExtraData::Create );
		ObjectRegistry::RegisterObject( "BSPSysSimpleColorModifier", BSPSysSimpleColorModifier::Create );
		ObjectRegistry::RegisterObject( "BSValueNode", BSValueNode::Create );
		ObjectRegistry::RegisterObject( "BSStripParticleSystem", BSStripParticleSystem::Create );
		ObjectRegistry::RegisterObject( "BSStripPSysData", BSStripPSysData::Create );
		ObjectRegistry::RegisterObject( "BSPSysStripUpdateModifier", BSPSysStripUpdateModifier::Create );
		ObjectRegistry::RegisterObject( "BSMaterialEmittanceMultController", BSMaterialEmittanceMultController::Create );
		ObjectRegistry::RegisterObject( "BSMasterParticleSystem", BSMasterParticleSystem::Create );
		ObjectRegistry::RegisterObject( "BSPSysMultiTargetEmitterCtlr", BSPSysMultiTargetEmitterCtlr::Create );
		ObjectRegistry::RegisterObject( "BSRefractionStrengthController", BSRefractionStrengthController::Create );
		ObjectRegistry::RegisterObject( "BSOrderedNode", BSOrderedNode::Create );
		ObjectRegistry::RegisterObject( "BSBlastNode", BSBlastNode::Create );
		ObjectRegistry::RegisterObject( "BSDamageStage", BSDamageStage::Create );
		ObjectRegistry::RegisterObject( "BSRefractionFirePeriodController", BSRefractionFirePeriodController::Create );
		ObjectRegistry::RegisterObject( "bhkConvexListShape", bhkConvexListShape::Create );
		ObjectRegistry::RegisterObject( "BSTreadTransfInterpolator", BSTreadTransfInterpolator::Create );
		ObjectRegistry::RegisterObject( "BSAnimNotes", BSAnimNotes::Create );
		ObjectRegistry::RegisterObject( "bhkLiquidAction", bhkLiquidAction::Create );
		ObjectRegistry::RegisterObject( "BSMultiBoundNode", BSMultiBoundNode::Create );
		ObjectRegistry::RegisterObject( "BSMultiBound", BSMultiBound::Create );
		ObjectRegistry::RegisterObject( "BSMultiBoundData", BSMultiBoundData::Create );
		ObjectRegistry::RegisterObject( "BSMultiBoundOBB", BSMultiBoundOBB::Create );
		ObjectRegistry::RegisterObject( "BSMultiBoundSphere", BSMultiBoundSphere::Create );
		ObjectRegistry::RegisterObject( "BSSegmentedTriShape", BSSegmentedTriShape::Create );
		ObjectRegistry::RegisterObject( "BSMultiBoundAABB", BSMultiBoundAABB::Create );
		ObjectRegistry::RegisterObject( "NiAdditionalGeometryData", NiAdditionalGeometryData::Create );
		ObjectRegistry::RegisterObject( "BSPackedAdditionalGeometryData", BSPackedAdditionalGeometryData::Create );
		ObjectRegistry::RegisterObject( "BSWArray", BSWArray::Create );
		ObjectRegistry::RegisterObject( "bhkAabbPhantom", bhkAabbPhantom::Create );
		ObjectRegistry::RegisterObject( "BSFrustumFOVController", BSFrustumFOVController::Create );
		ObjectRegistry::RegisterObject( "BSDebrisNode", BSDebrisNode::Create );
		ObjectRegistry::RegisterObject( "bhkBreakableConstraint", bhkBreakableConstraint::Create );
		ObjectRegistry::RegisterObject( "bhkOrientHingedBodyAction", bhkOrientHingedBodyAction::Create );
		ObjectRegistry::RegisterObject( "NiDataStream", NiDataStream::Create );
		ObjectRegistry::RegisterObject( "NiRenderObject", NiRenderObject::Create );
		ObjectRegistry::RegisterObject( "NiMeshModifier", NiMeshModifier::Create );
		ObjectRegistry::RegisterObject( "NiMesh", NiMesh::Create );
		ObjectRegistry::RegisterObject( "NiMorphWeightsController", NiMorphWeightsController::Create );
		ObjectRegistry::RegisterObject( "NiMorphMeshModifier", NiMorphMeshModifier::Create );
		ObjectRegistry::RegisterObject( "NiSkinningMeshModifier", NiSkinningMeshModifier::Create );
		ObjectRegistry::RegisterObject( "NiInstancingMeshModifier", NiInstancingMeshModifier::Create );
		ObjectRegistry::RegisterObject( "NiSkinningLODController", NiSkinningLODController::Create );
		ObjectRegistry::RegisterObject( "NiPSParticleSystem", NiPSParticleSystem::Create );
		ObjectRegistry::RegisterObject( "NiPSMeshParticleSystem", NiPSMeshParticleSystem::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitParticlesCtlr", NiPSEmitParticlesCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSForceActiveCtlr", NiPSForceActiveCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSSimulator", NiPSSimulator::Create );
		ObjectRegistry::RegisterObject( "NiPSSimulatorStep", NiPSSimulatorStep::Create );
		ObjectRegistry::RegisterObject( "NiPSSimulatorGeneralStep", NiPSSimulatorGeneralStep::Create );
		ObjectRegistry::RegisterObject( "NiPSSimulatorForcesStep", NiPSSimulatorForcesStep::Create );
		ObjectRegistry::RegisterObject( "NiPSSimulatorCollidersStep", NiPSSimulatorCollidersStep::Create );
		ObjectRegistry::RegisterObject( "NiPSSimulatorMeshAlignStep", NiPSSimulatorMeshAlignStep::Create );
		ObjectRegistry::RegisterObject( "NiPSSimulatorFinalStep", NiPSSimulatorFinalStep::Create );
		ObjectRegistry::RegisterObject( "NiPSFacingQuadGenerator", NiPSFacingQuadGenerator::Create );
		ObjectRegistry::RegisterObject( "NiShadowGenerator", NiShadowGenerator::Create );
		ObjectRegistry::RegisterObject( "NiPSBoundUpdater", NiPSBoundUpdater::Create );
		ObjectRegistry::RegisterObject( "NiPSDragForce", NiPSDragForce::Create );
		ObjectRegistry::RegisterObject( "NiPSGravityForce", NiPSGravityForce::Create );
		ObjectRegistry::RegisterObject( "NiPSBoxEmitter", NiPSBoxEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSMeshEmitter", NiPSMeshEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSGravityStrengthCtlr", NiPSGravityStrengthCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSPlanarCollider", NiPSPlanarCollider::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterSpeedCtlr", NiPSEmitterSpeedCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterRadiusCtlr", NiPSEmitterRadiusCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSResetOnLoopCtlr", NiPSResetOnLoopCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSSphereEmitter", NiPSSphereEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSCylinderEmitter", NiPSCylinderEmitter::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterDeclinationCtlr", NiPSEmitterDeclinationCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterDeclinationVarCtlr", NiPSEmitterDeclinationVarCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterPlanarAngleCtlr", NiPSEmitterPlanarAngleCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterPlanarAngleVarCtlr", NiPSEmitterPlanarAngleVarCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterRotAngleCtlr", NiPSEmitterRotAngleCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterRotAngleVarCtlr", NiPSEmitterRotAngleVarCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterRotSpeedCtlr", NiPSEmitterRotSpeedCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterRotSpeedVarCtlr", NiPSEmitterRotSpeedVarCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSEmitterLifeSpanCtlr", NiPSEmitterLifeSpanCtlr::Create );
		ObjectRegistry::RegisterObject( "NiPSBombForce", NiPSBombForce::Create );
		ObjectRegistry::RegisterObject( "NiPSSphericalCollider", NiPSSphericalCollider::Create );
		ObjectRegistry::RegisterObject( "NiPSSpawner", NiPSSpawner::Create );
		ObjectRegistry::RegisterObject( "NiSequenceData", NiSequenceData::Create );
		ObjectRegistry::RegisterObject( "NiTransformEvaluator", NiTransformEvaluator::Create );
		ObjectRegistry::RegisterObject( "NiBSplineCompTransformEvaluator", NiBSplineCompTransformEvaluator::Create );
		ObjectRegistry::RegisterObject( "NiMeshHWInstance", NiMeshHWInstance::Create );
		ObjectRegistry::RegisterObject( "NiFurSpringController", NiFurSpringController::Create );
		ObjectRegistry::RegisterObject( "CStreamableAssetData", CStreamableAssetData::Create );
		ObjectRegistry::RegisterObject( "bhkCompressedMeshShape", bhkCompressedMeshShape::Create );
		ObjectRegistry::RegisterObject( "bhkCompressedMeshShapeData", bhkCompressedMeshShapeData::Create );
		ObjectRegistry::RegisterObject( "BSInvMarker", BSInvMarker::Create );
		ObjectRegistry::RegisterObject( "BSBoneLODExtraData", BSBoneLODExtraData::Create );
		ObjectRegistry::RegisterObject( "BSBehaviorGraphExtraData", BSBehaviorGraphExtraData::Create );
		ObjectRegistry::RegisterObject( "BSLagBoneController", BSLagBoneController::Create );
		ObjectRegistry::RegisterObject( "BSLODTriShape", BSLODTriShape::Create );
		ObjectRegistry::RegisterObject( "BSFurnitureMarkerNode", BSFurnitureMarkerNode::Create );
		ObjectRegistry::RegisterObject( "BSLeafAnimNode", BSLeafAnimNode::Create );
		ObjectRegistry::RegisterObject( "BSTreeNode", BSTreeNode::Create );

	}
}
