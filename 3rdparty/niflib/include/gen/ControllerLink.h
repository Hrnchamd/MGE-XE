/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _CONTROLLERLINK_H_
#define _CONTROLLERLINK_H_

#include "../NIF_IO.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiTimeController;
class NiInterpolator;
class NiObject;
class NiStringPalette;

/*!
 * In a .kf file, this links to a controllable object, via its name (or for version
 * 10.2.0.0 and up, a link and offset to a NiStringPalette that contains the name),
 * and a sequence of interpolators that apply to this controllable object, via
 * links.
 */
struct ControllerLink {
	/*! Default Constructor */
	NIFLIB_API ControllerLink();
	/*! Default Destructor */
	NIFLIB_API ~ControllerLink();
	/*! Copy Constructor */
	NIFLIB_API ControllerLink( const ControllerLink & src );
	/*! Copy Operator */
	NIFLIB_API ControllerLink & operator=( const ControllerLink & src );
	/*! Name of a controllable object in another NIF file. */
	IndexString targetName;
	/*! Link to a controller. */
	Ref<NiTimeController > controller;
	/*! Link to an interpolator. */
	Ref<NiInterpolator > interpolator;
	/*! Unknown. */
	Ref<NiObject > unknownLink2;
	/*! Unknown. */
	unsigned short unknownShort0;
	/*!
	 * Idle animations tend to have low values for this, and NIF objects that have high
	 * values tend to correspond with the important parts of the animation.
	 */
	byte priority;
	/*!
	 * Refers to the NiStringPalette which contains the name of the controlled NIF
	 * object.
	 */
	Ref<NiStringPalette > stringPalette;
	/*! The name of the animated node. */
	IndexString nodeName;
	/*!
	 * Offset in the string palette where the name of the controlled node (NiNode,
	 * NiTriShape, ...) starts.
	 */
	unsigned int nodeNameOffset;
	/*!
	 * Name of the property (NiMaterialProperty, ...), if this controller controls a
	 * property.
	 */
	IndexString propertyType;
	/*!
	 * Offset in the string palette where the property (NiMaterialProperty, ...)
	 * starts, if this controller controls a property. Otherwise, -1.
	 */
	unsigned int propertyTypeOffset;
	/*!
	 * Probably the object type name of the controller in the NIF file that is child of
	 * the controlled object.
	 */
	IndexString controllerType;
	/*!
	 * Apparently the offset in the string palette of some type of controller related
	 * to Interpolator (for example, a 'NiTransformInterpolator' will have here a
	 * 'NiTransformController', etc.). Sometimes the type of controller that links to
	 * the interpolator. Probably it refers to the controller in the NIF file that is
	 * child of the controlled object, via its type name.
	 */
	unsigned int controllerTypeOffset;
	/*!
	 * Some variable string (such as 'SELF_ILLUM', '0-0-TT_TRANSLATE_U', 'tongue_out',
	 * etc.).
	 */
	IndexString variable1;
	/*!
	 * Offset in the string palette where some variable string starts (such as
	 * 'SELF_ILLUM', '0-0-TT_TRANSLATE_U', 'tongue_out', etc.). Usually, -1.
	 */
	unsigned int variable1Offset;
	/*! Another variable string, apparently used for particle system controllers. */
	IndexString variable2;
	/*!
	 * Offset in the string palette where some variable string starts (so far only
	 * 'EmitterActive' and 'BirthRate' have been observed in official files, used for
	 * particle system controllers). Usually, -1.
	 */
	unsigned int variable2Offset;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
