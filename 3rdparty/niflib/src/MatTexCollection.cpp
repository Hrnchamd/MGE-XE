/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/MatTexCollection.h"
#include "../include/obj/NiGeometry.h"
#include "../include/obj/NiAVObject.h"
#include "../include/obj/NiNode.h"
#include "../include/obj/NiMaterialProperty.h"
#include "../include/obj/NiTexturingProperty.h"
#include "../include/obj/NiTextureProperty.h"
#include "../include/obj/NiMultiTextureProperty.h"
#include "../include/obj/NiSpecularProperty.h"
#include "../include/obj/NiAlphaProperty.h"
#include "../include/obj/NiSourceTexture.h"
#include "../include/obj/NiImage.h"
#include "../include/obj/NiStencilProperty.h"

namespace Niflib {

MatTexCollection::MatTexCollection( NiAVObject * scene_root ) {
	if ( scene_root != NULL ) {
		GatherMaterials( scene_root );
	}
}

MatTexCollection::~MatTexCollection() {}

void MatTexCollection::GatherMaterials( NiAVObject * scene_root ) {	
	if ( scene_root == NULL ) {
		throw runtime_error( "MatTexCollection::GatherMaterials was called on a NULL scene root." );
	}

	//Check and see if this object is a geometry object
	if ( scene_root->IsDerivedType( NiGeometry::TYPE ) ) {

		//Check and see if this geometry's unique combination of material and texture properties has already been found
		if ( GetMaterialIndex( scene_root ) == NO_MATERIAL ) {
			//Material was not already found.  Look for material/texture related properties.
			NiPropertyRef mat = scene_root->GetPropertyByType( NiMaterialProperty::TYPE );
			NiPropertyRef texing = scene_root->GetPropertyByType( NiTexturingProperty::TYPE );
			NiPropertyRef tex = scene_root->GetPropertyByType( NiTextureProperty::TYPE );
			NiPropertyRef multi = scene_root->GetPropertyByType( NiMultiTextureProperty::TYPE );
			NiPropertyRef spec = scene_root->GetPropertyByType( NiSpecularProperty::TYPE );
			NiPropertyRef alpha = scene_root->GetPropertyByType( NiAlphaProperty::TYPE );
			NiPropertyRef stencil = scene_root->GetPropertyByType( NiStencilProperty::TYPE);

			//Make sure at least one isn't NULL
			if ( mat != NULL || texing != NULL || tex != NULL || multi != NULL || stencil != NULL) {
				//One isn't NULL, so create a new Material

				NiMaterialPropertyRef matC = DynamicCast<NiMaterialProperty>(mat);
				NiTexturingPropertyRef texingC = DynamicCast<NiTexturingProperty>(texing);
				NiTexturePropertyRef texC = DynamicCast<NiTextureProperty>(tex);
				NiMultiTexturePropertyRef multiC = DynamicCast<NiMultiTextureProperty>(multi);
				NiSpecularPropertyRef specC = DynamicCast<NiSpecularProperty>(spec);
				NiAlphaPropertyRef alphaC = DynamicCast<NiAlphaProperty>(alpha);
				NiStencilPropertyRef stencilC = DynamicCast<NiStencilProperty>(stencil);

				//First, check if the material's textures have been found yet

				if ( texingC != NULL ) {
					for ( int i = 0; i < 8; ++i ) {
						if ( texingC->HasTexture(i) ) {
							TexDesc td = texingC->GetTexture(i);
							if ( td.source != NULL ) {
								unsigned int index = GetTextureIndex( td.source );
								if ( index == NO_TEXTURE ) {
									//Texture has not yet been found.  Create a new one.
									textures.push_back( TextureWrapper( td.source ) );
								}
							}
						}
					}
				} else if ( texC != NULL ) {
					NiImageRef image = texC->GetImage();
					if ( image != NULL ) {
						unsigned int index = GetTextureIndex( image );
						if ( index == NO_TEXTURE ) {
							//Texture has not yet been found.  Create a new one.
							textures.push_back( TextureWrapper( image ) );
						}
					}
				}

				//TODO: Implement this for NiMultiTextureProperty as well


				materials.push_back( MaterialWrapper( matC, texingC, texC, multiC, specC, alphaC, stencilC, this ) );
			}
		}
		//Done with this branch, so return.
		return;
	}

	//If this object is a NiNode, then call this function on its children
	NiNodeRef node = DynamicCast<NiNode>(scene_root);
	if ( node != NULL ) {
		vector<NiAVObjectRef> children = node->GetChildren();

		for ( size_t i = 0; i < children.size(); ++i ) {
			GatherMaterials( children[i] );
		}
	}

}

void MatTexCollection::Clear() {
	materials.clear();
	textures.clear();
}

unsigned int MatTexCollection::GetNumMaterials() {
	return materials.size();
}

unsigned int MatTexCollection::GetNumTextures() {
	return textures.size();
}

MaterialWrapper MatTexCollection::GetMaterial( unsigned int index ) {
	if ( index >= materials.size() ) {
		throw runtime_error("The index passed to MatTexCollection::GetMaterial was out of range.");
	}

	return materials[index];
}

TextureWrapper MatTexCollection::GetTexture( unsigned int index ) {
	if ( index >= textures.size() ) {
		throw runtime_error("The index passed to MatTexCollection::GetTexture was out of range.");
	}

	return textures[index];
}
	
unsigned int MatTexCollection::GetMaterialIndex( NiAVObject * obj ) {
	//Search for a material that matches the properties that the NiAVObject has.
	vector< Ref<NiProperty> > properties = obj->GetProperties();

	return GetMaterialIndex( properties );
}

unsigned int MatTexCollection::GetMaterialIndex( NiMaterialProperty * mat, NiTexturingProperty * texing, NiTextureProperty * tex, NiMultiTextureProperty * multi, NiSpecularProperty * spec, NiAlphaProperty * alpha, NiStencilProperty * stencil ) {
	for( size_t i = 0; i < materials.size(); ++i ) {
		if ( materials[i].mat_prop == mat &&
			 materials[i].texing_prop == texing &&
			 materials[i].tex_prop == tex &&
			 materials[i].multi_prop == multi &&
			 materials[i].spec_prop == spec &&
			 materials[i].alpha_prop == alpha &&
			 materials[i].stencil_prop == stencil) {
				 //Match found, return its index
				 return i;
		}
	}

	//No match was found, return NO_MATERIAL
	return NO_MATERIAL;
}

unsigned int MatTexCollection::GetTextureIndex( NiSourceTexture * src_tex ) {
	for( size_t i = 0; i < textures.size(); ++i ) {
		if ( textures[i].src_tex == src_tex  ) {
				 //Match found, return its index
				 return i;
		}
	}

	//No match was found, return NO_MATERIAL
	return NO_TEXTURE;
}

unsigned int MatTexCollection::GetTextureIndex( NiImage * image ) {
	for( size_t i = 0; i < textures.size(); ++i ) {
		if ( textures[i].image == image  ) {
				 //Match found, return its index
				 return i;
		}
	}

	//No match was found, return NO_MATERIAL
	return NO_TEXTURE;
}

unsigned int MatTexCollection::GetMaterialIndex( const vector< Ref<NiProperty> > & properties ) {
	//Get Material and Texturing properties, if any
	NiMaterialPropertyRef mat = NULL;
	NiTexturingPropertyRef texing = NULL;
	NiTexturePropertyRef tex = NULL;
	NiMultiTexturePropertyRef multi = NULL;
	NiSpecularPropertyRef spec = NULL;
	NiAlphaPropertyRef alpha = NULL;
	NiStencilPropertyRef stencil = NULL;

	for ( unsigned i = 0; i < properties.size(); ++i ) {
		if ( properties[i] == NULL ) {
			continue;
		}
		if ( properties[i]->IsDerivedType( NiMaterialProperty::TYPE ) ) {
			mat = DynamicCast<NiMaterialProperty>( properties[i] );
		} else if ( properties[i]->IsDerivedType( NiTexturingProperty::TYPE ) ) {
			texing = DynamicCast<NiTexturingProperty>( properties[i] );
		} else if ( properties[i]->IsDerivedType( NiTextureProperty::TYPE ) ) {
			tex = DynamicCast<NiTextureProperty>( properties[i] );
		} else if ( properties[i]->IsDerivedType( NiMultiTextureProperty::TYPE ) ) {
			multi = DynamicCast<NiMultiTextureProperty>( properties[i] );
		} else if ( properties[i]->IsDerivedType( NiSpecularProperty::TYPE ) ) {
			spec = DynamicCast<NiSpecularProperty>( properties[i] );
		} else if ( properties[i]->IsDerivedType( NiAlphaProperty::TYPE ) ) {
			alpha = DynamicCast<NiAlphaProperty>( properties[i] );
		} else if ( properties[i]->IsDerivedType( NiStencilProperty::TYPE )) {
			stencil = DynamicCast<NiStencilProperty>( properties[i] );
		}
	}

	//Do the search
	return GetMaterialIndex( mat, texing, tex, multi, spec, alpha, stencil );
}

unsigned int MatTexCollection::CreateTexture( unsigned int version ) {
	if ( version < VER_3_3_0_13 ) {
		//Old image object style
		NiImageRef image = new NiImage;

		//Create texture wrapper and add it to the array
		textures.push_back( TextureWrapper( image ) );
	} else {
		//New iamge object style
		NiSourceTextureRef src_tex = new NiSourceTexture;

		//Create texture wrapper and add it to the array
		textures.push_back( TextureWrapper( src_tex ) );
	}

	//Return the index of the newly created texture
	return textures.size() - 1;
}

unsigned int MatTexCollection::CreateMaterial( bool color, bool texture, bool multi_tex, bool specular, bool translucency, unsigned int version ) {
	//Make sure at least one option is set to true
	if ( color == false && texture == false && multi_tex == false && specular == false && translucency == false ) {
		throw runtime_error( "At least one of the types of texture/material info needs to be stored in a new material.  All the argumetns to MatTexCollection::CreateMaterial cannot be false." );
	}
	
	NiMaterialPropertyRef mat = NULL;
	NiTexturingPropertyRef texing = NULL;
	NiTexturePropertyRef tex = NULL;
	NiMultiTexturePropertyRef multi = NULL;
	NiSpecularPropertyRef spec = NULL;
	NiAlphaPropertyRef alpha = NULL;
	NiStencilPropertyRef stencil = NULL;

	if ( color == true ) {
		mat = new NiMaterialProperty;
	}
	if ( specular == true ) {
		spec = new NiSpecularProperty;
	}
	if ( translucency == true ) {
		alpha = new NiAlphaProperty;
	}

	if ( version < VER_3_3_0_13 ) {
		//Old texturing property style
		if ( texture == true ) {
			tex = new NiTextureProperty;
		}
		if ( multi_tex == true ) {
			multi = new NiMultiTextureProperty;
		}
	} else {
		//New texturing property style
		if ( texture == true ) {
			texing = new NiTexturingProperty;
		}
	}

	//Create Material and add it to the array
	materials.push_back( MaterialWrapper( mat, texing, tex, multi, spec, alpha, stencil, this ) );

	//Return the index of the newly created material
	return materials.size() - 1;
}

//MaterialWrapper//////////////////////////////////////////////////////////////

MaterialWrapper::MaterialWrapper( NiMaterialProperty * mat, NiTexturingProperty * texing, NiTextureProperty * tex, NiMultiTextureProperty * multi, NiSpecularProperty * spec, NiAlphaProperty * alpha, NiStencilProperty * stencil, MatTexCollection * creator ) {
	mat_prop = mat;
	texing_prop = texing;
	tex_prop = tex;
	multi_prop = multi;
	spec_prop = spec;
	alpha_prop = alpha;
	stencil_prop = stencil;
	_creator = creator;
}

MaterialWrapper::~MaterialWrapper() {}

void MaterialWrapper::ApplyToObject( NiAVObject * target ) {
	//Add any non-NULL properties to the target object
	if ( mat_prop != NULL ) {
		target->AddProperty( mat_prop );
	}
	if ( texing_prop != NULL ) {
		target->AddProperty( texing_prop );
	}
	if ( tex_prop != NULL ) {
		target->AddProperty( tex_prop );
	}
	if ( multi_prop != NULL ) {
		target->AddProperty( multi_prop );
	}
	if ( spec_prop != NULL ) {
		target->AddProperty( spec_prop );
	}
	if ( alpha_prop != NULL ) {
		target->AddProperty( alpha_prop );
	}
	if ( stencil_prop != NULL) {
		target->AddProperty( stencil_prop );
	}
}

vector< Ref<NiProperty> > MaterialWrapper::GetProperties() {
	vector<NiPropertyRef> properties;
	NiPropertyRef prop;

	if ( mat_prop != NULL ) {
		prop = StaticCast<NiProperty>(mat_prop);
		properties.push_back(prop);
	}
	if ( texing_prop != NULL ) {
		prop = StaticCast<NiProperty>(texing_prop);
		properties.push_back(prop);
	}
	if ( tex_prop != NULL ) {
		prop = StaticCast<NiProperty>(tex_prop);
		properties.push_back(prop);
	}
	if ( multi_prop != NULL ) {
		prop = StaticCast<NiProperty>(multi_prop);
		properties.push_back(prop);
	}
	if ( spec_prop != NULL ) {
		prop = StaticCast<NiProperty>(spec_prop);
		properties.push_back(prop);
	}
	if ( alpha_prop != NULL ) {
		prop = StaticCast<NiProperty>(alpha_prop);
		properties.push_back(prop);
	}
	if( stencil_prop != NULL ) {
		prop = StaticCast<NiProperty>(stencil_prop);
		properties.push_back(prop);
	}

	return properties;
}


//--Color Function--//

Ref<NiMaterialProperty> MaterialWrapper::GetColorInfo() {
	return mat_prop;
}

Ref<NiSpecularProperty> MaterialWrapper::GetSpecularInfo() {
	return spec_prop;
}

Ref<NiAlphaProperty> MaterialWrapper::GetTranslucencyInfo() {
	return alpha_prop;
}

//--Texture Functions--//

bool MaterialWrapper::HasTexture( TexType slot ) {
	if ( texing_prop != NULL ) {
		return texing_prop->HasTexture( int(slot) );
	}
	if ( tex_prop != NULL && slot == BASE_MAP ) {
		if ( tex_prop->GetImage() != NULL ) {
			return true;
		}
	}
	//TODO:  Figure out which slots are what in NiMultiTextureProperty so this can be implemented for that too

	//Texture not found
	return false;;
}

unsigned int MaterialWrapper::GetTextureIndex( TexType slot ) {
	if ( texing_prop != NULL ) {
		if ( texing_prop->HasTexture( int(slot) ) == false ) {
			return NO_TEXTURE;
		}

		TexDesc td = texing_prop->GetTexture( int(slot) );

		if ( td.source == NULL ) {
			return NO_TEXTURE;
		}

		return _creator->GetTextureIndex( td.source );
	}
	if ( tex_prop != NULL && slot == BASE_MAP ) {
		NiImageRef img = tex_prop->GetImage();
		if ( img == NULL ) {
			return NO_TEXTURE;
		}

		return _creator->GetTextureIndex(img);

	}
	//TODO:  Figure out which slots are what in NiMultiTextureProperty so this can be implemented for that too

	//Texture not found
	return NO_TEXTURE;
}

void MaterialWrapper::SetTextureIndex( TexType slot, unsigned int tex_index ) {
	//Get the texture from the creator.  This will cause an exception if it fails.
	TextureWrapper tw = _creator->GetTexture(tex_index);
	
	if ( texing_prop != NULL ) {
		TexDesc td;

		td.source = tw.src_tex;

		texing_prop->SetTexture( int(slot), td );
	}
	if ( tex_prop != NULL && slot == BASE_MAP ) {
		tex_prop->SetImage( tw.image );
	}
	//TODO:  Figure out which slots are what in NiMultiTextureProperty so this can be implemented for that too
}

unsigned int MaterialWrapper::GetTexUVSetIndex( TexType slot ) {
	if ( texing_prop != NULL ) {
		if ( texing_prop->HasTexture( int(slot) ) == false ) {
			throw runtime_error("The texture at the specified index does not exist.");
		}

		TexDesc td = texing_prop->GetTexture( int(slot) );
		return td.uvSet;
	}

	//Just return default value for now.  Not sure where this data may or may not be stored in the old style texture properties.
	return 0;
}

void MaterialWrapper::SetTexUVSetIndex( TexType slot, unsigned int uv_set ) {
	if ( texing_prop != NULL ) {
		if ( texing_prop->HasTexture( int(slot) ) == false ) {
			throw runtime_error("The texture at the specified index does not exist.");
		}

		TexDesc td = texing_prop->GetTexture( int(slot) );
		td.uvSet = uv_set;
		texing_prop->SetTexture( int(slot), td );
	}

	//Just silently fail for now.  Not sure where this data may or may not be stored in the old style texture properties.
}

TexClampMode MaterialWrapper::GetTexClampMode( TexType slot ) {
	if ( texing_prop != NULL ) {
		if ( texing_prop->HasTexture( int(slot) ) == false ) {
			throw runtime_error("The texture at the specified index does not exist.");
		}

		TexDesc td = texing_prop->GetTexture( int(slot) );
		return td.clampMode;
	}

	//Just return default value for now.  Not sure where this data may or may not be stored in the old style texture properties.
	return WRAP_S_WRAP_T;
}

void MaterialWrapper::SetTexClampMode( TexType slot, TexClampMode mode ) {
	if ( texing_prop != NULL ) {
		if ( texing_prop->HasTexture( int(slot) ) == false ) {
			throw runtime_error("The texture at the specified index does not exist.");
		}

		TexDesc td = texing_prop->GetTexture( int(slot) );
		td.clampMode = mode;
		texing_prop->SetTexture( int(slot), td );
	}

	//Just silently fail for now.  Not sure where this data may or may not be stored in the old style texture properties.
}

TexFilterMode MaterialWrapper::GetTexFilterMode( TexType slot ) {
	if ( texing_prop != NULL ) {
		if ( texing_prop->HasTexture( int(slot) ) == false ) {
			throw runtime_error("The texture at the specified index does not exist.");
		}

		TexDesc td = texing_prop->GetTexture( int(slot) );
		return td.filterMode;
	}

	//Just return default value for now.  Not sure where this data may or may not be stored in the old style texture properties.
	return FILTER_BILERP;
}

void MaterialWrapper::SetTexFilterMode( TexType slot, TexFilterMode mode ) {
	if ( texing_prop != NULL ) {
		if ( texing_prop->HasTexture( int(slot) ) == false ) {
			throw runtime_error("The texture at the specified index does not exist.");
		}

		TexDesc td = texing_prop->GetTexture( int(slot) );
		td.filterMode = mode;
		texing_prop->SetTexture( int(slot), td );
	}

	//Just silently fail for now.  Not sure where this data may or may not be stored in the old style texture properties.
}

///Texture Wrapper/////////////////////////////////////////////////////////////

TextureWrapper::TextureWrapper( NiSourceTexture * src ) {
	src_tex = src;
}

TextureWrapper::TextureWrapper( NiImage * img ) {
	image = img;
}

TextureWrapper::~TextureWrapper() {}

bool TextureWrapper::IsTextureExternal() {
	if ( src_tex != NULL ) {
		return src_tex->IsTextureExternal();
	} else if ( image != NULL ) {
		return image->IsTextureExternal();
	} else {
		//Texture not found
		throw runtime_error("TextureWrapper holds no data.  This should not be able to happen.");
	}
}

string TextureWrapper::GetTextureFileName() {
	if ( src_tex != NULL ) {
		return src_tex->GetTextureFileName();
	} else if ( image != NULL ) {
		return image->GetTextureFileName();
	} else {
		//Texture not found
		throw runtime_error("TextureWrapper holds no data.  This should not be able to happen.");
	}
}

void TextureWrapper::SetExternalTexture( const string & file_name ) {
	if ( src_tex != NULL ) {
		src_tex->SetExternalTexture( file_name );
		return;
	} else if ( image != NULL ) {
		image->SetExternalTexture( file_name );

	} else {
		//Texture not found
		throw runtime_error("TextureWrapper holds no data.  This should not be able to happen.");
	}
}

PixelLayout TextureWrapper::GetPixelLayout() {
	if ( src_tex != NULL ) {
		return src_tex->GetPixelLayout();
	}

	//Just return default value for now.  Not sure where this data may or may not be stored in the old style image object.
	return PIX_LAY_DEFAULT;
}

void TextureWrapper::SetPixelLayout( PixelLayout layout ) {
	if ( src_tex != NULL ) {
		src_tex->SetPixelLayout(layout);
	}

	//Just silently fail for now.  Not sure where this data may or may not be stored in the old style image object.
}

MipMapFormat TextureWrapper::GetMipMapFormat() {
	if ( src_tex != NULL ) {
		return src_tex->GetMipMapFormat();
	}

	//Just return default value for now.  Not sure where this data may or may not be stored in the old style image object.
	return MIP_FMT_DEFAULT;
}

void TextureWrapper::SetMipMapFormat( MipMapFormat format ) {
	if ( src_tex != NULL ) {
		src_tex->SetMipMapFormat(format);
	}

	//Just silently fail for now.  Not sure where this data may or may not be stored in the old style image objects.
}

AlphaFormat TextureWrapper::GetAlphaFormat() {
	if ( src_tex != NULL ) {
		return src_tex->GetAlphaFormat();
	}

	//Just return default value for now.  Not sure where this data may or may not be stored in the old style image object.
	return ALPHA_DEFAULT;
}

void TextureWrapper::SetAlphaFormat( AlphaFormat format ) {
	if ( src_tex != NULL ) {
		src_tex->SetAlphaFormat(format);
	}

	//Just silently fail for now.  Not sure where this data may or may not be stored in the old style image objects.
}

string TextureWrapper::GetObjectName() {
	if ( src_tex != NULL ) {
		return src_tex->GetName();
	}

	//NiImage objects don't seem to have a name since they derive from NiObject.  Return an empty string.
	return string();
}

void TextureWrapper::SetObjectName( const string & name ) {
	if ( src_tex != NULL ) {
		src_tex->SetName( name );
	}

	//NiImage objects don't seem to have a name since they derive from NiObject.  Do nothing.
}

} //End namespace Niflib