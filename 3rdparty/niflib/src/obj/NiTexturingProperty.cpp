/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiTexturingProperty.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
#include "../../include/gen/ShaderTexDesc.h"
#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTexturingProperty::TYPE("NiTexturingProperty", &NiProperty::TYPE );

NiTexturingProperty::NiTexturingProperty() : flags((unsigned short)0), applyMode((ApplyMode)APPLY_MODULATE), textureCount((unsigned int)7), hasBaseTexture(false), hasDarkTexture(false), hasDetailTexture(false), hasGlossTexture(false), hasGlowTexture(false), hasBumpMapTexture(false), bumpMapLumaScale(0.0f), bumpMapLumaOffset(0.0f), hasNormalTexture(false), hasUnknown2Texture(false), unknown2Float(0.0f), hasDecal0Texture(false), hasDecal1Texture(false), hasDecal2Texture(false), hasDecal3Texture(false), numShaderTextures((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTexturingProperty::~NiTexturingProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTexturingProperty::GetType() const {
	return TYPE;
}

NiObject * NiTexturingProperty::Create() {
	return new NiTexturingProperty;
}

void NiTexturingProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiProperty::Read( in, link_stack, info );
	if ( info.version <= 0x0A000102 ) {
		NifStream( flags, in, info );
	};
	if ( info.version >= 0x14010003 ) {
		NifStream( flags, in, info );
	};
	if ( info.version <= 0x14000005 ) {
		NifStream( applyMode, in, info );
	};
	NifStream( textureCount, in, info );
	NifStream( hasBaseTexture, in, info );
	if ( hasBaseTexture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( baseTexture.clampMode, in, info );
			NifStream( baseTexture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( baseTexture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( baseTexture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( baseTexture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( baseTexture.ps2L, in, info );
			NifStream( baseTexture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( baseTexture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( baseTexture.hasTextureTransform, in, info );
			if ( baseTexture.hasTextureTransform ) {
				NifStream( baseTexture.translation, in, info );
				NifStream( baseTexture.tiling, in, info );
				NifStream( baseTexture.wRotation, in, info );
				NifStream( baseTexture.transformType_, in, info );
				NifStream( baseTexture.centerOffset, in, info );
			};
		};
	};
	NifStream( hasDarkTexture, in, info );
	if ( hasDarkTexture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( darkTexture.clampMode, in, info );
			NifStream( darkTexture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( darkTexture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( darkTexture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( darkTexture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( darkTexture.ps2L, in, info );
			NifStream( darkTexture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( darkTexture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( darkTexture.hasTextureTransform, in, info );
			if ( darkTexture.hasTextureTransform ) {
				NifStream( darkTexture.translation, in, info );
				NifStream( darkTexture.tiling, in, info );
				NifStream( darkTexture.wRotation, in, info );
				NifStream( darkTexture.transformType_, in, info );
				NifStream( darkTexture.centerOffset, in, info );
			};
		};
	};
	NifStream( hasDetailTexture, in, info );
	if ( hasDetailTexture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( detailTexture.clampMode, in, info );
			NifStream( detailTexture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( detailTexture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( detailTexture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( detailTexture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( detailTexture.ps2L, in, info );
			NifStream( detailTexture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( detailTexture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( detailTexture.hasTextureTransform, in, info );
			if ( detailTexture.hasTextureTransform ) {
				NifStream( detailTexture.translation, in, info );
				NifStream( detailTexture.tiling, in, info );
				NifStream( detailTexture.wRotation, in, info );
				NifStream( detailTexture.transformType_, in, info );
				NifStream( detailTexture.centerOffset, in, info );
			};
		};
	};
	NifStream( hasGlossTexture, in, info );
	if ( hasGlossTexture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( glossTexture.clampMode, in, info );
			NifStream( glossTexture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( glossTexture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( glossTexture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( glossTexture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( glossTexture.ps2L, in, info );
			NifStream( glossTexture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( glossTexture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( glossTexture.hasTextureTransform, in, info );
			if ( glossTexture.hasTextureTransform ) {
				NifStream( glossTexture.translation, in, info );
				NifStream( glossTexture.tiling, in, info );
				NifStream( glossTexture.wRotation, in, info );
				NifStream( glossTexture.transformType_, in, info );
				NifStream( glossTexture.centerOffset, in, info );
			};
		};
	};
	NifStream( hasGlowTexture, in, info );
	if ( hasGlowTexture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( glowTexture.clampMode, in, info );
			NifStream( glowTexture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( glowTexture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( glowTexture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( glowTexture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( glowTexture.ps2L, in, info );
			NifStream( glowTexture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( glowTexture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( glowTexture.hasTextureTransform, in, info );
			if ( glowTexture.hasTextureTransform ) {
				NifStream( glowTexture.translation, in, info );
				NifStream( glowTexture.tiling, in, info );
				NifStream( glowTexture.wRotation, in, info );
				NifStream( glowTexture.transformType_, in, info );
				NifStream( glowTexture.centerOffset, in, info );
			};
		};
	};
	NifStream( hasBumpMapTexture, in, info );
	if ( hasBumpMapTexture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( bumpMapTexture.clampMode, in, info );
			NifStream( bumpMapTexture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( bumpMapTexture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( bumpMapTexture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( bumpMapTexture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( bumpMapTexture.ps2L, in, info );
			NifStream( bumpMapTexture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( bumpMapTexture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( bumpMapTexture.hasTextureTransform, in, info );
			if ( bumpMapTexture.hasTextureTransform ) {
				NifStream( bumpMapTexture.translation, in, info );
				NifStream( bumpMapTexture.tiling, in, info );
				NifStream( bumpMapTexture.wRotation, in, info );
				NifStream( bumpMapTexture.transformType_, in, info );
				NifStream( bumpMapTexture.centerOffset, in, info );
			};
		};
		NifStream( bumpMapLumaScale, in, info );
		NifStream( bumpMapLumaOffset, in, info );
		NifStream( bumpMapMatrix, in, info );
	};
	if ( info.version >= 0x14020007 ) {
		NifStream( hasNormalTexture, in, info );
		if ( hasNormalTexture ) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
			if ( info.version <= 0x14000005 ) {
				NifStream( normalTexture.clampMode, in, info );
				NifStream( normalTexture.filterMode, in, info );
			};
			if ( info.version >= 0x14010003 ) {
				NifStream( normalTexture.flags, in, info );
			};
			if ( info.version >= 0x14060000 ) {
				NifStream( normalTexture.unknownShort, in, info );
			};
			if ( info.version <= 0x14000005 ) {
				NifStream( normalTexture.uvSet, in, info );
			};
			if ( info.version <= 0x0A040001 ) {
				NifStream( normalTexture.ps2L, in, info );
				NifStream( normalTexture.ps2K, in, info );
			};
			if ( info.version <= 0x0401000C ) {
				NifStream( normalTexture.unknown1, in, info );
			};
			if ( info.version >= 0x0A010000 ) {
				NifStream( normalTexture.hasTextureTransform, in, info );
				if ( normalTexture.hasTextureTransform ) {
					NifStream( normalTexture.translation, in, info );
					NifStream( normalTexture.tiling, in, info );
					NifStream( normalTexture.wRotation, in, info );
					NifStream( normalTexture.transformType_, in, info );
					NifStream( normalTexture.centerOffset, in, info );
				};
			};
		};
		NifStream( hasUnknown2Texture, in, info );
		if ( hasUnknown2Texture ) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
			if ( info.version <= 0x14000005 ) {
				NifStream( unknown2Texture.clampMode, in, info );
				NifStream( unknown2Texture.filterMode, in, info );
			};
			if ( info.version >= 0x14010003 ) {
				NifStream( unknown2Texture.flags, in, info );
			};
			if ( info.version >= 0x14060000 ) {
				NifStream( unknown2Texture.unknownShort, in, info );
			};
			if ( info.version <= 0x14000005 ) {
				NifStream( unknown2Texture.uvSet, in, info );
			};
			if ( info.version <= 0x0A040001 ) {
				NifStream( unknown2Texture.ps2L, in, info );
				NifStream( unknown2Texture.ps2K, in, info );
			};
			if ( info.version <= 0x0401000C ) {
				NifStream( unknown2Texture.unknown1, in, info );
			};
			if ( info.version >= 0x0A010000 ) {
				NifStream( unknown2Texture.hasTextureTransform, in, info );
				if ( unknown2Texture.hasTextureTransform ) {
					NifStream( unknown2Texture.translation, in, info );
					NifStream( unknown2Texture.tiling, in, info );
					NifStream( unknown2Texture.wRotation, in, info );
					NifStream( unknown2Texture.transformType_, in, info );
					NifStream( unknown2Texture.centerOffset, in, info );
				};
			};
		};
	};
	if ( hasUnknown2Texture ) {
		NifStream( unknown2Float, in, info );
	};
	NifStream( hasDecal0Texture, in, info );
	if ( hasDecal0Texture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( decal0Texture.clampMode, in, info );
			NifStream( decal0Texture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( decal0Texture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( decal0Texture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( decal0Texture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( decal0Texture.ps2L, in, info );
			NifStream( decal0Texture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( decal0Texture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( decal0Texture.hasTextureTransform, in, info );
			if ( decal0Texture.hasTextureTransform ) {
				NifStream( decal0Texture.translation, in, info );
				NifStream( decal0Texture.tiling, in, info );
				NifStream( decal0Texture.wRotation, in, info );
				NifStream( decal0Texture.transformType_, in, info );
				NifStream( decal0Texture.centerOffset, in, info );
			};
		};
	};
	if ( info.version <= 0x14010003 ) {
		if ( (textureCount >= 8) ) {
			NifStream( hasDecal1Texture, in, info );
		};
	};
	if ( info.version >= 0x14020007 ) {
		if ( (textureCount >= 10) ) {
			NifStream( hasDecal1Texture, in, info );
		};
	};
	if ( hasDecal1Texture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( decal1Texture.clampMode, in, info );
			NifStream( decal1Texture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( decal1Texture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( decal1Texture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( decal1Texture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( decal1Texture.ps2L, in, info );
			NifStream( decal1Texture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( decal1Texture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( decal1Texture.hasTextureTransform, in, info );
			if ( decal1Texture.hasTextureTransform ) {
				NifStream( decal1Texture.translation, in, info );
				NifStream( decal1Texture.tiling, in, info );
				NifStream( decal1Texture.wRotation, in, info );
				NifStream( decal1Texture.transformType_, in, info );
				NifStream( decal1Texture.centerOffset, in, info );
			};
		};
	};
	if ( info.version <= 0x14010003 ) {
		if ( (textureCount >= 9) ) {
			NifStream( hasDecal2Texture, in, info );
		};
	};
	if ( info.version >= 0x14020007 ) {
		if ( (textureCount >= 11) ) {
			NifStream( hasDecal2Texture, in, info );
		};
	};
	if ( hasDecal2Texture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( decal2Texture.clampMode, in, info );
			NifStream( decal2Texture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( decal2Texture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( decal2Texture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( decal2Texture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( decal2Texture.ps2L, in, info );
			NifStream( decal2Texture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( decal2Texture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( decal2Texture.hasTextureTransform, in, info );
			if ( decal2Texture.hasTextureTransform ) {
				NifStream( decal2Texture.translation, in, info );
				NifStream( decal2Texture.tiling, in, info );
				NifStream( decal2Texture.wRotation, in, info );
				NifStream( decal2Texture.transformType_, in, info );
				NifStream( decal2Texture.centerOffset, in, info );
			};
		};
	};
	if ( info.version <= 0x14010003 ) {
		if ( (textureCount >= 10) ) {
			NifStream( hasDecal3Texture, in, info );
		};
	};
	if ( info.version >= 0x14020007 ) {
		if ( (textureCount >= 12) ) {
			NifStream( hasDecal3Texture, in, info );
		};
	};
	if ( hasDecal3Texture ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		if ( info.version <= 0x14000005 ) {
			NifStream( decal3Texture.clampMode, in, info );
			NifStream( decal3Texture.filterMode, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( decal3Texture.flags, in, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( decal3Texture.unknownShort, in, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( decal3Texture.uvSet, in, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( decal3Texture.ps2L, in, info );
			NifStream( decal3Texture.ps2K, in, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( decal3Texture.unknown1, in, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( decal3Texture.hasTextureTransform, in, info );
			if ( decal3Texture.hasTextureTransform ) {
				NifStream( decal3Texture.translation, in, info );
				NifStream( decal3Texture.tiling, in, info );
				NifStream( decal3Texture.wRotation, in, info );
				NifStream( decal3Texture.transformType_, in, info );
				NifStream( decal3Texture.centerOffset, in, info );
			};
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( numShaderTextures, in, info );
		shaderTextures.resize(numShaderTextures);
		for (unsigned int i2 = 0; i2 < shaderTextures.size(); i2++) {
			NifStream( shaderTextures[i2].isUsed, in, info );
			if ( shaderTextures[i2].isUsed ) {
				NifStream( block_num, in, info );
				link_stack.push_back( block_num );
				if ( info.version <= 0x14000005 ) {
					NifStream( shaderTextures[i2].textureData.clampMode, in, info );
					NifStream( shaderTextures[i2].textureData.filterMode, in, info );
				};
				if ( info.version >= 0x14010003 ) {
					NifStream( shaderTextures[i2].textureData.flags, in, info );
				};
				if ( info.version >= 0x14060000 ) {
					NifStream( shaderTextures[i2].textureData.unknownShort, in, info );
				};
				if ( info.version <= 0x14000005 ) {
					NifStream( shaderTextures[i2].textureData.uvSet, in, info );
				};
				if ( info.version <= 0x0A040001 ) {
					NifStream( shaderTextures[i2].textureData.ps2L, in, info );
					NifStream( shaderTextures[i2].textureData.ps2K, in, info );
				};
				if ( info.version <= 0x0401000C ) {
					NifStream( shaderTextures[i2].textureData.unknown1, in, info );
				};
				if ( info.version >= 0x0A010000 ) {
					NifStream( shaderTextures[i2].textureData.hasTextureTransform, in, info );
					if ( shaderTextures[i2].textureData.hasTextureTransform ) {
						NifStream( shaderTextures[i2].textureData.translation, in, info );
						NifStream( shaderTextures[i2].textureData.tiling, in, info );
						NifStream( shaderTextures[i2].textureData.wRotation, in, info );
						NifStream( shaderTextures[i2].textureData.transformType_, in, info );
						NifStream( shaderTextures[i2].textureData.centerOffset, in, info );
					};
				};
				NifStream( shaderTextures[i2].mapIndex, in, info );
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTexturingProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	numShaderTextures = (unsigned int)(shaderTextures.size());
	if ( info.version <= 0x0A000102 ) {
		NifStream( flags, out, info );
	};
	if ( info.version >= 0x14010003 ) {
		NifStream( flags, out, info );
	};
	if ( info.version <= 0x14000005 ) {
		NifStream( applyMode, out, info );
	};
	NifStream( textureCount, out, info );
	NifStream( hasBaseTexture, out, info );
	if ( hasBaseTexture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*baseTexture.source), out );
		} else {
			if ( baseTexture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(baseTexture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( baseTexture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( baseTexture.clampMode, out, info );
			NifStream( baseTexture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( baseTexture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( baseTexture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( baseTexture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( baseTexture.ps2L, out, info );
			NifStream( baseTexture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( baseTexture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( baseTexture.hasTextureTransform, out, info );
			if ( baseTexture.hasTextureTransform ) {
				NifStream( baseTexture.translation, out, info );
				NifStream( baseTexture.tiling, out, info );
				NifStream( baseTexture.wRotation, out, info );
				NifStream( baseTexture.transformType_, out, info );
				NifStream( baseTexture.centerOffset, out, info );
			};
		};
	};
	NifStream( hasDarkTexture, out, info );
	if ( hasDarkTexture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*darkTexture.source), out );
		} else {
			if ( darkTexture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(darkTexture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( darkTexture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( darkTexture.clampMode, out, info );
			NifStream( darkTexture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( darkTexture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( darkTexture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( darkTexture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( darkTexture.ps2L, out, info );
			NifStream( darkTexture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( darkTexture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( darkTexture.hasTextureTransform, out, info );
			if ( darkTexture.hasTextureTransform ) {
				NifStream( darkTexture.translation, out, info );
				NifStream( darkTexture.tiling, out, info );
				NifStream( darkTexture.wRotation, out, info );
				NifStream( darkTexture.transformType_, out, info );
				NifStream( darkTexture.centerOffset, out, info );
			};
		};
	};
	NifStream( hasDetailTexture, out, info );
	if ( hasDetailTexture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*detailTexture.source), out );
		} else {
			if ( detailTexture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(detailTexture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( detailTexture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( detailTexture.clampMode, out, info );
			NifStream( detailTexture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( detailTexture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( detailTexture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( detailTexture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( detailTexture.ps2L, out, info );
			NifStream( detailTexture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( detailTexture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( detailTexture.hasTextureTransform, out, info );
			if ( detailTexture.hasTextureTransform ) {
				NifStream( detailTexture.translation, out, info );
				NifStream( detailTexture.tiling, out, info );
				NifStream( detailTexture.wRotation, out, info );
				NifStream( detailTexture.transformType_, out, info );
				NifStream( detailTexture.centerOffset, out, info );
			};
		};
	};
	NifStream( hasGlossTexture, out, info );
	if ( hasGlossTexture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*glossTexture.source), out );
		} else {
			if ( glossTexture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(glossTexture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( glossTexture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( glossTexture.clampMode, out, info );
			NifStream( glossTexture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( glossTexture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( glossTexture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( glossTexture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( glossTexture.ps2L, out, info );
			NifStream( glossTexture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( glossTexture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( glossTexture.hasTextureTransform, out, info );
			if ( glossTexture.hasTextureTransform ) {
				NifStream( glossTexture.translation, out, info );
				NifStream( glossTexture.tiling, out, info );
				NifStream( glossTexture.wRotation, out, info );
				NifStream( glossTexture.transformType_, out, info );
				NifStream( glossTexture.centerOffset, out, info );
			};
		};
	};
	NifStream( hasGlowTexture, out, info );
	if ( hasGlowTexture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*glowTexture.source), out );
		} else {
			if ( glowTexture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(glowTexture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( glowTexture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( glowTexture.clampMode, out, info );
			NifStream( glowTexture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( glowTexture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( glowTexture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( glowTexture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( glowTexture.ps2L, out, info );
			NifStream( glowTexture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( glowTexture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( glowTexture.hasTextureTransform, out, info );
			if ( glowTexture.hasTextureTransform ) {
				NifStream( glowTexture.translation, out, info );
				NifStream( glowTexture.tiling, out, info );
				NifStream( glowTexture.wRotation, out, info );
				NifStream( glowTexture.transformType_, out, info );
				NifStream( glowTexture.centerOffset, out, info );
			};
		};
	};
	NifStream( hasBumpMapTexture, out, info );
	if ( hasBumpMapTexture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*bumpMapTexture.source), out );
		} else {
			if ( bumpMapTexture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(bumpMapTexture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( bumpMapTexture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( bumpMapTexture.clampMode, out, info );
			NifStream( bumpMapTexture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( bumpMapTexture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( bumpMapTexture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( bumpMapTexture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( bumpMapTexture.ps2L, out, info );
			NifStream( bumpMapTexture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( bumpMapTexture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( bumpMapTexture.hasTextureTransform, out, info );
			if ( bumpMapTexture.hasTextureTransform ) {
				NifStream( bumpMapTexture.translation, out, info );
				NifStream( bumpMapTexture.tiling, out, info );
				NifStream( bumpMapTexture.wRotation, out, info );
				NifStream( bumpMapTexture.transformType_, out, info );
				NifStream( bumpMapTexture.centerOffset, out, info );
			};
		};
		NifStream( bumpMapLumaScale, out, info );
		NifStream( bumpMapLumaOffset, out, info );
		NifStream( bumpMapMatrix, out, info );
	};
	if ( info.version >= 0x14020007 ) {
		NifStream( hasNormalTexture, out, info );
		if ( hasNormalTexture ) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*normalTexture.source), out );
			} else {
				if ( normalTexture.source != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(normalTexture.source) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( normalTexture.source );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
			if ( info.version <= 0x14000005 ) {
				NifStream( normalTexture.clampMode, out, info );
				NifStream( normalTexture.filterMode, out, info );
			};
			if ( info.version >= 0x14010003 ) {
				NifStream( normalTexture.flags, out, info );
			};
			if ( info.version >= 0x14060000 ) {
				NifStream( normalTexture.unknownShort, out, info );
			};
			if ( info.version <= 0x14000005 ) {
				NifStream( normalTexture.uvSet, out, info );
			};
			if ( info.version <= 0x0A040001 ) {
				NifStream( normalTexture.ps2L, out, info );
				NifStream( normalTexture.ps2K, out, info );
			};
			if ( info.version <= 0x0401000C ) {
				NifStream( normalTexture.unknown1, out, info );
			};
			if ( info.version >= 0x0A010000 ) {
				NifStream( normalTexture.hasTextureTransform, out, info );
				if ( normalTexture.hasTextureTransform ) {
					NifStream( normalTexture.translation, out, info );
					NifStream( normalTexture.tiling, out, info );
					NifStream( normalTexture.wRotation, out, info );
					NifStream( normalTexture.transformType_, out, info );
					NifStream( normalTexture.centerOffset, out, info );
				};
			};
		};
		NifStream( hasUnknown2Texture, out, info );
		if ( hasUnknown2Texture ) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*unknown2Texture.source), out );
			} else {
				if ( unknown2Texture.source != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(unknown2Texture.source) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( unknown2Texture.source );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
			if ( info.version <= 0x14000005 ) {
				NifStream( unknown2Texture.clampMode, out, info );
				NifStream( unknown2Texture.filterMode, out, info );
			};
			if ( info.version >= 0x14010003 ) {
				NifStream( unknown2Texture.flags, out, info );
			};
			if ( info.version >= 0x14060000 ) {
				NifStream( unknown2Texture.unknownShort, out, info );
			};
			if ( info.version <= 0x14000005 ) {
				NifStream( unknown2Texture.uvSet, out, info );
			};
			if ( info.version <= 0x0A040001 ) {
				NifStream( unknown2Texture.ps2L, out, info );
				NifStream( unknown2Texture.ps2K, out, info );
			};
			if ( info.version <= 0x0401000C ) {
				NifStream( unknown2Texture.unknown1, out, info );
			};
			if ( info.version >= 0x0A010000 ) {
				NifStream( unknown2Texture.hasTextureTransform, out, info );
				if ( unknown2Texture.hasTextureTransform ) {
					NifStream( unknown2Texture.translation, out, info );
					NifStream( unknown2Texture.tiling, out, info );
					NifStream( unknown2Texture.wRotation, out, info );
					NifStream( unknown2Texture.transformType_, out, info );
					NifStream( unknown2Texture.centerOffset, out, info );
				};
			};
		};
	};
	if ( hasUnknown2Texture ) {
		NifStream( unknown2Float, out, info );
	};
	NifStream( hasDecal0Texture, out, info );
	if ( hasDecal0Texture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*decal0Texture.source), out );
		} else {
			if ( decal0Texture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(decal0Texture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( decal0Texture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( decal0Texture.clampMode, out, info );
			NifStream( decal0Texture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( decal0Texture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( decal0Texture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( decal0Texture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( decal0Texture.ps2L, out, info );
			NifStream( decal0Texture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( decal0Texture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( decal0Texture.hasTextureTransform, out, info );
			if ( decal0Texture.hasTextureTransform ) {
				NifStream( decal0Texture.translation, out, info );
				NifStream( decal0Texture.tiling, out, info );
				NifStream( decal0Texture.wRotation, out, info );
				NifStream( decal0Texture.transformType_, out, info );
				NifStream( decal0Texture.centerOffset, out, info );
			};
		};
	};
	if ( info.version <= 0x14010003 ) {
		if ( (textureCount >= 8) ) {
			NifStream( hasDecal1Texture, out, info );
		};
	};
	if ( info.version >= 0x14020007 ) {
		if ( (textureCount >= 10) ) {
			NifStream( hasDecal1Texture, out, info );
		};
	};
	if ( hasDecal1Texture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*decal1Texture.source), out );
		} else {
			if ( decal1Texture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(decal1Texture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( decal1Texture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( decal1Texture.clampMode, out, info );
			NifStream( decal1Texture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( decal1Texture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( decal1Texture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( decal1Texture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( decal1Texture.ps2L, out, info );
			NifStream( decal1Texture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( decal1Texture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( decal1Texture.hasTextureTransform, out, info );
			if ( decal1Texture.hasTextureTransform ) {
				NifStream( decal1Texture.translation, out, info );
				NifStream( decal1Texture.tiling, out, info );
				NifStream( decal1Texture.wRotation, out, info );
				NifStream( decal1Texture.transformType_, out, info );
				NifStream( decal1Texture.centerOffset, out, info );
			};
		};
	};
	if ( info.version <= 0x14010003 ) {
		if ( (textureCount >= 9) ) {
			NifStream( hasDecal2Texture, out, info );
		};
	};
	if ( info.version >= 0x14020007 ) {
		if ( (textureCount >= 11) ) {
			NifStream( hasDecal2Texture, out, info );
		};
	};
	if ( hasDecal2Texture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*decal2Texture.source), out );
		} else {
			if ( decal2Texture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(decal2Texture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( decal2Texture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( decal2Texture.clampMode, out, info );
			NifStream( decal2Texture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( decal2Texture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( decal2Texture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( decal2Texture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( decal2Texture.ps2L, out, info );
			NifStream( decal2Texture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( decal2Texture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( decal2Texture.hasTextureTransform, out, info );
			if ( decal2Texture.hasTextureTransform ) {
				NifStream( decal2Texture.translation, out, info );
				NifStream( decal2Texture.tiling, out, info );
				NifStream( decal2Texture.wRotation, out, info );
				NifStream( decal2Texture.transformType_, out, info );
				NifStream( decal2Texture.centerOffset, out, info );
			};
		};
	};
	if ( info.version <= 0x14010003 ) {
		if ( (textureCount >= 10) ) {
			NifStream( hasDecal3Texture, out, info );
		};
	};
	if ( info.version >= 0x14020007 ) {
		if ( (textureCount >= 12) ) {
			NifStream( hasDecal3Texture, out, info );
		};
	};
	if ( hasDecal3Texture ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*decal3Texture.source), out );
		} else {
			if ( decal3Texture.source != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(decal3Texture.source) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( decal3Texture.source );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		if ( info.version <= 0x14000005 ) {
			NifStream( decal3Texture.clampMode, out, info );
			NifStream( decal3Texture.filterMode, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( decal3Texture.flags, out, info );
		};
		if ( info.version >= 0x14060000 ) {
			NifStream( decal3Texture.unknownShort, out, info );
		};
		if ( info.version <= 0x14000005 ) {
			NifStream( decal3Texture.uvSet, out, info );
		};
		if ( info.version <= 0x0A040001 ) {
			NifStream( decal3Texture.ps2L, out, info );
			NifStream( decal3Texture.ps2K, out, info );
		};
		if ( info.version <= 0x0401000C ) {
			NifStream( decal3Texture.unknown1, out, info );
		};
		if ( info.version >= 0x0A010000 ) {
			NifStream( decal3Texture.hasTextureTransform, out, info );
			if ( decal3Texture.hasTextureTransform ) {
				NifStream( decal3Texture.translation, out, info );
				NifStream( decal3Texture.tiling, out, info );
				NifStream( decal3Texture.wRotation, out, info );
				NifStream( decal3Texture.transformType_, out, info );
				NifStream( decal3Texture.centerOffset, out, info );
			};
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( numShaderTextures, out, info );
		for (unsigned int i2 = 0; i2 < shaderTextures.size(); i2++) {
			NifStream( shaderTextures[i2].isUsed, out, info );
			if ( shaderTextures[i2].isUsed ) {
				if ( info.version < VER_3_3_0_13 ) {
					WritePtr32( &(*shaderTextures[i2].textureData.source), out );
				} else {
					if ( shaderTextures[i2].textureData.source != NULL ) {
						map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shaderTextures[i2].textureData.source) );
						if (it != link_map.end()) {
							NifStream( it->second, out, info );
							missing_link_stack.push_back( NULL );
						} else {
							NifStream( 0xFFFFFFFF, out, info );
							missing_link_stack.push_back( shaderTextures[i2].textureData.source );
						}
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( NULL );
					}
				}
				if ( info.version <= 0x14000005 ) {
					NifStream( shaderTextures[i2].textureData.clampMode, out, info );
					NifStream( shaderTextures[i2].textureData.filterMode, out, info );
				};
				if ( info.version >= 0x14010003 ) {
					NifStream( shaderTextures[i2].textureData.flags, out, info );
				};
				if ( info.version >= 0x14060000 ) {
					NifStream( shaderTextures[i2].textureData.unknownShort, out, info );
				};
				if ( info.version <= 0x14000005 ) {
					NifStream( shaderTextures[i2].textureData.uvSet, out, info );
				};
				if ( info.version <= 0x0A040001 ) {
					NifStream( shaderTextures[i2].textureData.ps2L, out, info );
					NifStream( shaderTextures[i2].textureData.ps2K, out, info );
				};
				if ( info.version <= 0x0401000C ) {
					NifStream( shaderTextures[i2].textureData.unknown1, out, info );
				};
				if ( info.version >= 0x0A010000 ) {
					NifStream( shaderTextures[i2].textureData.hasTextureTransform, out, info );
					if ( shaderTextures[i2].textureData.hasTextureTransform ) {
						NifStream( shaderTextures[i2].textureData.translation, out, info );
						NifStream( shaderTextures[i2].textureData.tiling, out, info );
						NifStream( shaderTextures[i2].textureData.wRotation, out, info );
						NifStream( shaderTextures[i2].textureData.transformType_, out, info );
						NifStream( shaderTextures[i2].textureData.centerOffset, out, info );
					};
				};
				NifStream( shaderTextures[i2].mapIndex, out, info );
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTexturingProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiProperty::asString();
	numShaderTextures = (unsigned int)(shaderTextures.size());
	out << "  Flags:  " << flags << endl;
	out << "  Apply Mode:  " << applyMode << endl;
	out << "  Texture Count:  " << textureCount << endl;
	out << "  Has Base Texture:  " << hasBaseTexture << endl;
	if ( hasBaseTexture ) {
		out << "    Source:  " << baseTexture.source << endl;
		out << "    Clamp Mode:  " << baseTexture.clampMode << endl;
		out << "    Filter Mode:  " << baseTexture.filterMode << endl;
		out << "    Flags:  " << baseTexture.flags << endl;
		out << "    Unknown short:  " << baseTexture.unknownShort << endl;
		out << "    UV Set:  " << baseTexture.uvSet << endl;
		out << "    PS2 L:  " << baseTexture.ps2L << endl;
		out << "    PS2 K:  " << baseTexture.ps2K << endl;
		out << "    Unknown1:  " << baseTexture.unknown1 << endl;
		out << "    Has Texture Transform:  " << baseTexture.hasTextureTransform << endl;
		if ( baseTexture.hasTextureTransform ) {
			out << "      Translation:  " << baseTexture.translation << endl;
			out << "      Tiling:  " << baseTexture.tiling << endl;
			out << "      W Rotation:  " << baseTexture.wRotation << endl;
			out << "      Transform Type?:  " << baseTexture.transformType_ << endl;
			out << "      Center Offset:  " << baseTexture.centerOffset << endl;
		};
	};
	out << "  Has Dark Texture:  " << hasDarkTexture << endl;
	if ( hasDarkTexture ) {
		out << "    Source:  " << darkTexture.source << endl;
		out << "    Clamp Mode:  " << darkTexture.clampMode << endl;
		out << "    Filter Mode:  " << darkTexture.filterMode << endl;
		out << "    Flags:  " << darkTexture.flags << endl;
		out << "    Unknown short:  " << darkTexture.unknownShort << endl;
		out << "    UV Set:  " << darkTexture.uvSet << endl;
		out << "    PS2 L:  " << darkTexture.ps2L << endl;
		out << "    PS2 K:  " << darkTexture.ps2K << endl;
		out << "    Unknown1:  " << darkTexture.unknown1 << endl;
		out << "    Has Texture Transform:  " << darkTexture.hasTextureTransform << endl;
		if ( darkTexture.hasTextureTransform ) {
			out << "      Translation:  " << darkTexture.translation << endl;
			out << "      Tiling:  " << darkTexture.tiling << endl;
			out << "      W Rotation:  " << darkTexture.wRotation << endl;
			out << "      Transform Type?:  " << darkTexture.transformType_ << endl;
			out << "      Center Offset:  " << darkTexture.centerOffset << endl;
		};
	};
	out << "  Has Detail Texture:  " << hasDetailTexture << endl;
	if ( hasDetailTexture ) {
		out << "    Source:  " << detailTexture.source << endl;
		out << "    Clamp Mode:  " << detailTexture.clampMode << endl;
		out << "    Filter Mode:  " << detailTexture.filterMode << endl;
		out << "    Flags:  " << detailTexture.flags << endl;
		out << "    Unknown short:  " << detailTexture.unknownShort << endl;
		out << "    UV Set:  " << detailTexture.uvSet << endl;
		out << "    PS2 L:  " << detailTexture.ps2L << endl;
		out << "    PS2 K:  " << detailTexture.ps2K << endl;
		out << "    Unknown1:  " << detailTexture.unknown1 << endl;
		out << "    Has Texture Transform:  " << detailTexture.hasTextureTransform << endl;
		if ( detailTexture.hasTextureTransform ) {
			out << "      Translation:  " << detailTexture.translation << endl;
			out << "      Tiling:  " << detailTexture.tiling << endl;
			out << "      W Rotation:  " << detailTexture.wRotation << endl;
			out << "      Transform Type?:  " << detailTexture.transformType_ << endl;
			out << "      Center Offset:  " << detailTexture.centerOffset << endl;
		};
	};
	out << "  Has Gloss Texture:  " << hasGlossTexture << endl;
	if ( hasGlossTexture ) {
		out << "    Source:  " << glossTexture.source << endl;
		out << "    Clamp Mode:  " << glossTexture.clampMode << endl;
		out << "    Filter Mode:  " << glossTexture.filterMode << endl;
		out << "    Flags:  " << glossTexture.flags << endl;
		out << "    Unknown short:  " << glossTexture.unknownShort << endl;
		out << "    UV Set:  " << glossTexture.uvSet << endl;
		out << "    PS2 L:  " << glossTexture.ps2L << endl;
		out << "    PS2 K:  " << glossTexture.ps2K << endl;
		out << "    Unknown1:  " << glossTexture.unknown1 << endl;
		out << "    Has Texture Transform:  " << glossTexture.hasTextureTransform << endl;
		if ( glossTexture.hasTextureTransform ) {
			out << "      Translation:  " << glossTexture.translation << endl;
			out << "      Tiling:  " << glossTexture.tiling << endl;
			out << "      W Rotation:  " << glossTexture.wRotation << endl;
			out << "      Transform Type?:  " << glossTexture.transformType_ << endl;
			out << "      Center Offset:  " << glossTexture.centerOffset << endl;
		};
	};
	out << "  Has Glow Texture:  " << hasGlowTexture << endl;
	if ( hasGlowTexture ) {
		out << "    Source:  " << glowTexture.source << endl;
		out << "    Clamp Mode:  " << glowTexture.clampMode << endl;
		out << "    Filter Mode:  " << glowTexture.filterMode << endl;
		out << "    Flags:  " << glowTexture.flags << endl;
		out << "    Unknown short:  " << glowTexture.unknownShort << endl;
		out << "    UV Set:  " << glowTexture.uvSet << endl;
		out << "    PS2 L:  " << glowTexture.ps2L << endl;
		out << "    PS2 K:  " << glowTexture.ps2K << endl;
		out << "    Unknown1:  " << glowTexture.unknown1 << endl;
		out << "    Has Texture Transform:  " << glowTexture.hasTextureTransform << endl;
		if ( glowTexture.hasTextureTransform ) {
			out << "      Translation:  " << glowTexture.translation << endl;
			out << "      Tiling:  " << glowTexture.tiling << endl;
			out << "      W Rotation:  " << glowTexture.wRotation << endl;
			out << "      Transform Type?:  " << glowTexture.transformType_ << endl;
			out << "      Center Offset:  " << glowTexture.centerOffset << endl;
		};
	};
	out << "  Has Bump Map Texture:  " << hasBumpMapTexture << endl;
	if ( hasBumpMapTexture ) {
		out << "    Source:  " << bumpMapTexture.source << endl;
		out << "    Clamp Mode:  " << bumpMapTexture.clampMode << endl;
		out << "    Filter Mode:  " << bumpMapTexture.filterMode << endl;
		out << "    Flags:  " << bumpMapTexture.flags << endl;
		out << "    Unknown short:  " << bumpMapTexture.unknownShort << endl;
		out << "    UV Set:  " << bumpMapTexture.uvSet << endl;
		out << "    PS2 L:  " << bumpMapTexture.ps2L << endl;
		out << "    PS2 K:  " << bumpMapTexture.ps2K << endl;
		out << "    Unknown1:  " << bumpMapTexture.unknown1 << endl;
		out << "    Has Texture Transform:  " << bumpMapTexture.hasTextureTransform << endl;
		if ( bumpMapTexture.hasTextureTransform ) {
			out << "      Translation:  " << bumpMapTexture.translation << endl;
			out << "      Tiling:  " << bumpMapTexture.tiling << endl;
			out << "      W Rotation:  " << bumpMapTexture.wRotation << endl;
			out << "      Transform Type?:  " << bumpMapTexture.transformType_ << endl;
			out << "      Center Offset:  " << bumpMapTexture.centerOffset << endl;
		};
		out << "    Bump Map Luma Scale:  " << bumpMapLumaScale << endl;
		out << "    Bump Map Luma Offset:  " << bumpMapLumaOffset << endl;
		out << "    Bump Map Matrix:  " << bumpMapMatrix << endl;
	};
	out << "  Has Normal Texture:  " << hasNormalTexture << endl;
	if ( hasNormalTexture ) {
		out << "    Source:  " << normalTexture.source << endl;
		out << "    Clamp Mode:  " << normalTexture.clampMode << endl;
		out << "    Filter Mode:  " << normalTexture.filterMode << endl;
		out << "    Flags:  " << normalTexture.flags << endl;
		out << "    Unknown short:  " << normalTexture.unknownShort << endl;
		out << "    UV Set:  " << normalTexture.uvSet << endl;
		out << "    PS2 L:  " << normalTexture.ps2L << endl;
		out << "    PS2 K:  " << normalTexture.ps2K << endl;
		out << "    Unknown1:  " << normalTexture.unknown1 << endl;
		out << "    Has Texture Transform:  " << normalTexture.hasTextureTransform << endl;
		if ( normalTexture.hasTextureTransform ) {
			out << "      Translation:  " << normalTexture.translation << endl;
			out << "      Tiling:  " << normalTexture.tiling << endl;
			out << "      W Rotation:  " << normalTexture.wRotation << endl;
			out << "      Transform Type?:  " << normalTexture.transformType_ << endl;
			out << "      Center Offset:  " << normalTexture.centerOffset << endl;
		};
	};
	out << "  Has Unknown2 Texture:  " << hasUnknown2Texture << endl;
	if ( hasUnknown2Texture ) {
		out << "    Source:  " << unknown2Texture.source << endl;
		out << "    Clamp Mode:  " << unknown2Texture.clampMode << endl;
		out << "    Filter Mode:  " << unknown2Texture.filterMode << endl;
		out << "    Flags:  " << unknown2Texture.flags << endl;
		out << "    Unknown short:  " << unknown2Texture.unknownShort << endl;
		out << "    UV Set:  " << unknown2Texture.uvSet << endl;
		out << "    PS2 L:  " << unknown2Texture.ps2L << endl;
		out << "    PS2 K:  " << unknown2Texture.ps2K << endl;
		out << "    Unknown1:  " << unknown2Texture.unknown1 << endl;
		out << "    Has Texture Transform:  " << unknown2Texture.hasTextureTransform << endl;
		if ( unknown2Texture.hasTextureTransform ) {
			out << "      Translation:  " << unknown2Texture.translation << endl;
			out << "      Tiling:  " << unknown2Texture.tiling << endl;
			out << "      W Rotation:  " << unknown2Texture.wRotation << endl;
			out << "      Transform Type?:  " << unknown2Texture.transformType_ << endl;
			out << "      Center Offset:  " << unknown2Texture.centerOffset << endl;
		};
		out << "    Unknown2 Float:  " << unknown2Float << endl;
	};
	out << "  Has Decal 0 Texture:  " << hasDecal0Texture << endl;
	if ( hasDecal0Texture ) {
		out << "    Source:  " << decal0Texture.source << endl;
		out << "    Clamp Mode:  " << decal0Texture.clampMode << endl;
		out << "    Filter Mode:  " << decal0Texture.filterMode << endl;
		out << "    Flags:  " << decal0Texture.flags << endl;
		out << "    Unknown short:  " << decal0Texture.unknownShort << endl;
		out << "    UV Set:  " << decal0Texture.uvSet << endl;
		out << "    PS2 L:  " << decal0Texture.ps2L << endl;
		out << "    PS2 K:  " << decal0Texture.ps2K << endl;
		out << "    Unknown1:  " << decal0Texture.unknown1 << endl;
		out << "    Has Texture Transform:  " << decal0Texture.hasTextureTransform << endl;
		if ( decal0Texture.hasTextureTransform ) {
			out << "      Translation:  " << decal0Texture.translation << endl;
			out << "      Tiling:  " << decal0Texture.tiling << endl;
			out << "      W Rotation:  " << decal0Texture.wRotation << endl;
			out << "      Transform Type?:  " << decal0Texture.transformType_ << endl;
			out << "      Center Offset:  " << decal0Texture.centerOffset << endl;
		};
	};
	if ( (textureCount >= 8) ) {
		out << "    Has Decal 1 Texture:  " << hasDecal1Texture << endl;
	};
	if ( hasDecal1Texture ) {
		out << "    Source:  " << decal1Texture.source << endl;
		out << "    Clamp Mode:  " << decal1Texture.clampMode << endl;
		out << "    Filter Mode:  " << decal1Texture.filterMode << endl;
		out << "    Flags:  " << decal1Texture.flags << endl;
		out << "    Unknown short:  " << decal1Texture.unknownShort << endl;
		out << "    UV Set:  " << decal1Texture.uvSet << endl;
		out << "    PS2 L:  " << decal1Texture.ps2L << endl;
		out << "    PS2 K:  " << decal1Texture.ps2K << endl;
		out << "    Unknown1:  " << decal1Texture.unknown1 << endl;
		out << "    Has Texture Transform:  " << decal1Texture.hasTextureTransform << endl;
		if ( decal1Texture.hasTextureTransform ) {
			out << "      Translation:  " << decal1Texture.translation << endl;
			out << "      Tiling:  " << decal1Texture.tiling << endl;
			out << "      W Rotation:  " << decal1Texture.wRotation << endl;
			out << "      Transform Type?:  " << decal1Texture.transformType_ << endl;
			out << "      Center Offset:  " << decal1Texture.centerOffset << endl;
		};
	};
	if ( (textureCount >= 9) ) {
		out << "    Has Decal 2 Texture:  " << hasDecal2Texture << endl;
	};
	if ( hasDecal2Texture ) {
		out << "    Source:  " << decal2Texture.source << endl;
		out << "    Clamp Mode:  " << decal2Texture.clampMode << endl;
		out << "    Filter Mode:  " << decal2Texture.filterMode << endl;
		out << "    Flags:  " << decal2Texture.flags << endl;
		out << "    Unknown short:  " << decal2Texture.unknownShort << endl;
		out << "    UV Set:  " << decal2Texture.uvSet << endl;
		out << "    PS2 L:  " << decal2Texture.ps2L << endl;
		out << "    PS2 K:  " << decal2Texture.ps2K << endl;
		out << "    Unknown1:  " << decal2Texture.unknown1 << endl;
		out << "    Has Texture Transform:  " << decal2Texture.hasTextureTransform << endl;
		if ( decal2Texture.hasTextureTransform ) {
			out << "      Translation:  " << decal2Texture.translation << endl;
			out << "      Tiling:  " << decal2Texture.tiling << endl;
			out << "      W Rotation:  " << decal2Texture.wRotation << endl;
			out << "      Transform Type?:  " << decal2Texture.transformType_ << endl;
			out << "      Center Offset:  " << decal2Texture.centerOffset << endl;
		};
	};
	if ( (textureCount >= 10) ) {
		out << "    Has Decal 3 Texture:  " << hasDecal3Texture << endl;
	};
	if ( hasDecal3Texture ) {
		out << "    Source:  " << decal3Texture.source << endl;
		out << "    Clamp Mode:  " << decal3Texture.clampMode << endl;
		out << "    Filter Mode:  " << decal3Texture.filterMode << endl;
		out << "    Flags:  " << decal3Texture.flags << endl;
		out << "    Unknown short:  " << decal3Texture.unknownShort << endl;
		out << "    UV Set:  " << decal3Texture.uvSet << endl;
		out << "    PS2 L:  " << decal3Texture.ps2L << endl;
		out << "    PS2 K:  " << decal3Texture.ps2K << endl;
		out << "    Unknown1:  " << decal3Texture.unknown1 << endl;
		out << "    Has Texture Transform:  " << decal3Texture.hasTextureTransform << endl;
		if ( decal3Texture.hasTextureTransform ) {
			out << "      Translation:  " << decal3Texture.translation << endl;
			out << "      Tiling:  " << decal3Texture.tiling << endl;
			out << "      W Rotation:  " << decal3Texture.wRotation << endl;
			out << "      Transform Type?:  " << decal3Texture.transformType_ << endl;
			out << "      Center Offset:  " << decal3Texture.centerOffset << endl;
		};
	};
	out << "  Num Shader Textures:  " << numShaderTextures << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < shaderTextures.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Is Used:  " << shaderTextures[i1].isUsed << endl;
		if ( shaderTextures[i1].isUsed ) {
			out << "      Source:  " << shaderTextures[i1].textureData.source << endl;
			out << "      Clamp Mode:  " << shaderTextures[i1].textureData.clampMode << endl;
			out << "      Filter Mode:  " << shaderTextures[i1].textureData.filterMode << endl;
			out << "      Flags:  " << shaderTextures[i1].textureData.flags << endl;
			out << "      Unknown short:  " << shaderTextures[i1].textureData.unknownShort << endl;
			out << "      UV Set:  " << shaderTextures[i1].textureData.uvSet << endl;
			out << "      PS2 L:  " << shaderTextures[i1].textureData.ps2L << endl;
			out << "      PS2 K:  " << shaderTextures[i1].textureData.ps2K << endl;
			out << "      Unknown1:  " << shaderTextures[i1].textureData.unknown1 << endl;
			out << "      Has Texture Transform:  " << shaderTextures[i1].textureData.hasTextureTransform << endl;
			if ( shaderTextures[i1].textureData.hasTextureTransform ) {
				out << "        Translation:  " << shaderTextures[i1].textureData.translation << endl;
				out << "        Tiling:  " << shaderTextures[i1].textureData.tiling << endl;
				out << "        W Rotation:  " << shaderTextures[i1].textureData.wRotation << endl;
				out << "        Transform Type?:  " << shaderTextures[i1].textureData.transformType_ << endl;
				out << "        Center Offset:  " << shaderTextures[i1].textureData.centerOffset << endl;
			};
			out << "      Map Index:  " << shaderTextures[i1].mapIndex << endl;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTexturingProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( hasBaseTexture ) {
		baseTexture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( hasDarkTexture ) {
		darkTexture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( hasDetailTexture ) {
		detailTexture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( hasGlossTexture ) {
		glossTexture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( hasGlowTexture ) {
		glowTexture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( hasBumpMapTexture ) {
		bumpMapTexture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( info.version >= 0x14020007 ) {
		if ( hasNormalTexture ) {
			normalTexture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
		};
		if ( hasUnknown2Texture ) {
			unknown2Texture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
		};
	};
	if ( hasDecal0Texture ) {
		decal0Texture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( hasDecal1Texture ) {
		decal1Texture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( hasDecal2Texture ) {
		decal2Texture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( hasDecal3Texture ) {
		decal3Texture.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
	};
	if ( info.version >= 0x0A000100 ) {
		for (unsigned int i2 = 0; i2 < shaderTextures.size(); i2++) {
			if ( shaderTextures[i2].isUsed ) {
				shaderTextures[i2].textureData.source = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
			};
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTexturingProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	if ( baseTexture.source != NULL )
		refs.push_back(StaticCast<NiObject>(baseTexture.source));
	if ( darkTexture.source != NULL )
		refs.push_back(StaticCast<NiObject>(darkTexture.source));
	if ( detailTexture.source != NULL )
		refs.push_back(StaticCast<NiObject>(detailTexture.source));
	if ( glossTexture.source != NULL )
		refs.push_back(StaticCast<NiObject>(glossTexture.source));
	if ( glowTexture.source != NULL )
		refs.push_back(StaticCast<NiObject>(glowTexture.source));
	if ( bumpMapTexture.source != NULL )
		refs.push_back(StaticCast<NiObject>(bumpMapTexture.source));
	if ( normalTexture.source != NULL )
		refs.push_back(StaticCast<NiObject>(normalTexture.source));
	if ( unknown2Texture.source != NULL )
		refs.push_back(StaticCast<NiObject>(unknown2Texture.source));
	if ( decal0Texture.source != NULL )
		refs.push_back(StaticCast<NiObject>(decal0Texture.source));
	if ( decal1Texture.source != NULL )
		refs.push_back(StaticCast<NiObject>(decal1Texture.source));
	if ( decal2Texture.source != NULL )
		refs.push_back(StaticCast<NiObject>(decal2Texture.source));
	if ( decal3Texture.source != NULL )
		refs.push_back(StaticCast<NiObject>(decal3Texture.source));
	for (unsigned int i1 = 0; i1 < shaderTextures.size(); i1++) {
		if ( shaderTextures[i1].textureData.source != NULL )
			refs.push_back(StaticCast<NiObject>(shaderTextures[i1].textureData.source));
	};
	return refs;
}

std::list<NiObject *> NiTexturingProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	for (unsigned int i1 = 0; i1 < shaderTextures.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

ApplyMode NiTexturingProperty::GetApplyMode() const {
	return applyMode;
}

void NiTexturingProperty::SetApplyMode( ApplyMode new_val ) {
	applyMode = new_val;
}

int NiTexturingProperty::GetTextureCount() const {
	//TODO:  Create a built in type for this array of textures so it can be a real array again?
	//int count = 0;
	//if ( hasBaseTexture ) { count++; }
	//if ( hasBumpMapTexture ) { count++; }
	//if ( hasDarkTexture ) { count++; }
	//if ( hasDecal0Texture ) { count++; }
	//if ( hasDecal1Texture ) { count++; }
	//if ( hasDetailTexture ) { count++; }
	//if ( hasGlossTexture ) { count++; }
	//if ( hasGlowTexture ) { count++; }
 //  if ( hasNormalTexture ) { count++; }
 //  if ( hasUnknown2Texture ) { count++; }
 //  if ( hasDecal2Texture ) { count++; }
 //  if ( hasDecal3Texture ) { count++; }
	//return count;
   return textureCount;
}

int NiTexturingProperty::GetShaderTextureCount() const {
	return int(shaderTextures.size());
}

TexDesc & NiTexturingProperty::GetTexture( int n ) {
	//TODO:  Create a built in type for this array of textures so it can be a real array again?
	//Copy the values to the right texture
	switch (n) {
		case BASE_MAP:
			return baseTexture;
		case DARK_MAP:
			return darkTexture;
		case DETAIL_MAP:
			return detailTexture;
		case GLOSS_MAP:
			return glossTexture;
		case GLOW_MAP:
			return glowTexture;
		case BUMP_MAP:
			return bumpMapTexture;
      case NORMAL_MAP:
         return normalTexture;
      case UNKNOWN2_MAP:
         return unknown2Texture;
		case DECAL_0_MAP:
			return decal0Texture;
		case DECAL_1_MAP:
			return decal1Texture;
      case DECAL_2_MAP:
         return decal2Texture;
      case DECAL_3_MAP:
         return decal3Texture;
	};

	//If we get here, an invalid texture was requested.
	throw runtime_error("Invalid texture requested.");
}

TexDesc NiTexturingProperty::GetShaderTexture( int n ) const {
	return shaderTextures[n].textureData;
}

float NiTexturingProperty::GetLumaOffset() const {
	return bumpMapLumaOffset;
}

void NiTexturingProperty::SetLumaOffset( float new_val ) {
	bumpMapLumaOffset = new_val;
}

float NiTexturingProperty::GetLumaScale() const {
	return bumpMapLumaScale;
}

void NiTexturingProperty::SetLumaScale( float new_val ) {
	bumpMapLumaScale = new_val;
}

Matrix22 NiTexturingProperty::GetBumpMapMatrix() const {
	return bumpMapMatrix;
}

void NiTexturingProperty::SetBumpMapMatrix( Matrix22 & new_val ) {
	bumpMapMatrix = new_val;
}

void NiTexturingProperty::SetTextureCount( int new_count ) {

	//if ( new_count < int(textureCount) ) {
	//	for ( int i = int(textureCount); i > new_count; --i ) {
	//		ClearTexture(i);
	//	}
	//}
   textureCount = new_count;
}

void NiTexturingProperty::SetShaderTextureCount( int new_count ) {
	//Resize array
	shaderTextures.resize( new_count );
}

void NiTexturingProperty::SetTexture( int n, TexDesc & new_val ) {
	//Make sure index is not out of range
	
	if ( n < 0 || n > int(textureCount) ) {
		throw runtime_error("SetTexture - Index out of range.  Call SetTextureCount to resize.");
	}

	//TODO:  Create a built in type for this array of textures so it can be a real array again?
	//Copy the values to the right texture
	switch (n) {
		case BASE_MAP:
			hasBaseTexture = true;
			baseTexture = new_val;
			break;
		case DARK_MAP:
			hasDarkTexture = true;
			darkTexture = new_val;
			break;
		case DETAIL_MAP:
			hasDetailTexture = true;
			detailTexture = new_val;
			break;
		case GLOSS_MAP:
			hasGlossTexture = true;
			glossTexture = new_val;
			break;
		case GLOW_MAP:
			hasGlowTexture = true;
			glowTexture = new_val;
			break;
		case BUMP_MAP:
			hasBumpMapTexture = true;
			bumpMapTexture = new_val;
			break;
      case NORMAL_MAP:
         hasNormalTexture = true;
         normalTexture = new_val;
         break;
      case UNKNOWN2_MAP:
         hasUnknown2Texture = true;
         unknown2Texture = new_val;
         break;
		case DECAL_0_MAP:
			hasDecal0Texture = true;
			decal0Texture = new_val;
			break;
		case DECAL_1_MAP:
			hasDecal1Texture = true;
			decal1Texture = new_val;
			break;
      case DECAL_2_MAP:
         hasDecal2Texture = true;
         decal2Texture = new_val;
         break;
      case DECAL_3_MAP:
         hasDecal3Texture = true;
         decal3Texture = new_val;
         break;
	};
}

void NiTexturingProperty::SetShaderTexture( int n, TexDesc & new_val ) {
	//Make sure index is not out of range
	if ( n < 0 || n > int(shaderTextures.size()) ) {
		throw runtime_error("SetShaderTexture - Index out of range.  Call SetShaderTextureCount to resize.");
	}

	//Copy the values
	shaderTextures[n].textureData = new_val;
}

bool NiTexturingProperty::HasTexture( int n ) const {
   switch (n) {
      case BASE_MAP:
         return hasBaseTexture;
      case DARK_MAP:
         return hasDarkTexture;
      case DETAIL_MAP:
         return hasDetailTexture;
      case GLOSS_MAP:
         return hasGlossTexture;
      case GLOW_MAP:
         return hasGlowTexture;
      case BUMP_MAP:
         return hasBumpMapTexture;
      case NORMAL_MAP:
         return hasNormalTexture;
      case UNKNOWN2_MAP:
         return hasUnknown2Texture;
      case DECAL_0_MAP:
         return hasDecal0Texture;
      case DECAL_1_MAP:
         return hasDecal1Texture;
      case DECAL_2_MAP:
         return hasDecal2Texture;
      case DECAL_3_MAP:
         return hasDecal3Texture;
      default:
         return false;
         //throw runtime_error("You have specified an invalid texture type.");
   };
}

void NiTexturingProperty::ClearTexture( int n ) {
	switch (n) {
		case BASE_MAP:
			hasBaseTexture = false;
			baseTexture.source = NULL;
			break;
		case DARK_MAP:
			hasDarkTexture = false;
			darkTexture.source = NULL;
			break;
		case DETAIL_MAP:
			hasDetailTexture = false;
			detailTexture.source = NULL;
			break;
		case GLOSS_MAP:
			hasGlossTexture = false;
			glossTexture.source = NULL;
			break;
		case GLOW_MAP:
			hasGlowTexture = false;
			glowTexture.source = NULL;
			break;
		case BUMP_MAP:
			hasBumpMapTexture = false;
			bumpMapTexture.source = NULL;
			break;
      case NORMAL_MAP:
         hasNormalTexture = false;
         normalTexture.source = NULL;
         break;
      case UNKNOWN2_MAP:
         hasUnknown2Texture = false;
         unknown2Texture.source = NULL;
         break;
		case DECAL_0_MAP:
			hasDecal0Texture = false;
			decal0Texture.source = NULL;
			break;
		case DECAL_1_MAP:
			hasDecal1Texture = false;
			decal1Texture.source = NULL;
			break;
      case DECAL_2_MAP:
         hasDecal2Texture = false;
         decal2Texture.source = NULL;
         break;
      case DECAL_3_MAP:
         hasDecal3Texture = false;
         decal3Texture.source = NULL;
         break;
	};
}

//--END CUSTOM CODE--//
