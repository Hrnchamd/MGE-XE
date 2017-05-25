/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following
     disclaimer in the documentation and/or other materials provided
     with the distribution.

   * Neither the name of the NIF File Format Library and Tools
     project nor the names of its contributors may be used to endorse
     or promote products derived from this software without specific
     prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE. */

#ifndef _NIFLIB_H_
#define _NIFLIB_H_

//--Includes--//
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <list>
#include <map>
#include "dll_export.h"
#include "nif_math.h"
#include "nif_versions.h"
#include "Ref.h"
#include "nif_basic_types.h"

using namespace std;
namespace Niflib {

//Classes used
class NiObject;
class NiNode;
class NiAVObject;
class NiControllerSequence;

#ifndef NULL
#define NULL 0  /*!< Definition used to detect null pointers. */ 
#endif

//--Constants--//

/*! Keyframe trees are game dependent, so here we define a few games. */
enum NifGame {
	KF_MW = 0, /*!< keyframe files: NiSequenceStreamHelper header, .kf extension */
	KF_DAOC = 1, /*!< keyframe files: NiNode header, .kfa extension */
	KF_CIV4 = 2 /*!< keyframe files: NiControllerSequence header, .kf extension */
};

/*! Export options. */
enum ExportOptions { 
	EXPORT_NIF = 0, /*!< NIF */
	EXPORT_NIF_KF = 1, /*!< NIF + single KF + KFM */
	EXPORT_NIF_KF_MULTI = 2, /*!< NIF + multiple KF + KFM */
	EXPORT_KF = 3, /*!< single KF */
	EXPORT_KF_MULTI = 4 /*!< multiple KF */
};

//--Main Functions--//

/*!
 * Reads the header of the given file by file name and returns the NIF version
 * if it is a valid NIF file. Call this function prior to calling ReadNifList
 * or ReadNifTree, if you want to make sure that its NIF version is supported
 * before trying to read it.
 * \param file_name The name of the file to load, or the complete path if it is not in the working directory.
 * \return The NIF version of the file, in hexadecimal format. If the file is not a NIF file, it returns VER_INVALID.
 * 
 * <b>Example:</b> 
 * \code
 * unsigned ver = GetNifVersion("test_in.nif");
 * if ( IsSupportedVersion(ver) == false ) {
 *    cout << "Unsupported.\n" << endl;
 * } else if ( ver == VER_INVALID ) {
 *    cout << "Not a NIF file.\n" << endl;
 * }
 * \endcode
 */
NIFLIB_API unsigned int GetNifVersion( string const & file_name );

/*!
 * Reads the given file by file name and returns a vector of object references
 * \param file_name The name of the file to load, or the complete path if it is not in the working directory.
 * \param info Optionally, a NifInfo structure pointer can be passed in, and it will be filled with information from the header of the NIF file.
 * \return All the NIF objects read from the Nif file. 
 * \sa ReadNifTree, WriteNifTree
 */
NIFLIB_API vector< Ref<NiObject> > ReadNifList( string const & file_name, NifInfo * info = NULL );

/*!
 * Reads the given input stream and returns a vector of object references
 * \param in The input stream to read NIF data from.
 * \param info Optionally, a NifInfo structure pointer can be passed in, and it will be filled with information from the header of the NIF file.
 * \return All the NIF objects read from the stream.
 */
NIFLIB_API vector< Ref<NiObject> > ReadNifList( istream & in, NifInfo * info = NULL );

/*!
 * Reads the given file by file name and returns a reference to the root object.
 * \param file_name The name of the file to load, or the complete path if it is not in the working directory.
 * \param info Optionally, a NifInfo structure pointer can be passed in, and it will be filled with information from the header of the NIF file.
 * \return The root of tree of NIF objects contained in the NIF file.
 * \sa ReadNifList, WriteNifTree
 */
NIFLIB_API Ref<NiObject> ReadNifTree( string const & file_name, NifInfo * info = NULL );

/*!
 * Reads the given input stream and returns a reference to the root object.
 * \param[in] in The input stream to read NIF data from.
 * \param[out] info Optionally, a NifInfo structure pointer can be passed in, and it will be filled with information from the header of the NIF file.
 * \return The root of the tree of NIF Objects contained in the NIF file.
 */
NIFLIB_API Ref<NiObject> ReadNifTree( istream & in, NifInfo * info = NULL );

/*!
 * Creates a new NIF file of the given file name by crawling through the data tree starting with the root object given.
 * \param[in] file_name The desired file name for the new NIF file.  The path is relative to the working directory unless a full path is specified.
 * \param[in] root The root object to start from when writing out the NIF file.  All decedents of this block will be written to the file in tree-descending order.
 * \param[in] info A NifInfo structure that contains information such as the version of the NIF file to create.
 * \sa ReadNifList, WriteNifTree
 */
NIFLIB_API void WriteNifTree( string const & file_name, NiObject * root, const NifInfo & info = NifInfo() );

/*!
 * Writes a nif tree to an ostream starting at the given root object.
 * \param[in] in The output stream to write the NIF data to.
 * \param[in] root The root object to start from when writing out the NIF data.  All decedents of this object will be written to the stream in tree-descending order.
 * \param[in] info A NifInfo structure that contains information such as the version of the NIF file to create.
 */
NIFLIB_API void WriteNifTree( ostream & in, NiObject * root, const NifInfo & info = NifInfo() );

/*!
 * Writes a bunch of files given a base file name, and a pointer to the root object of the Nif file tree.
 * \param[in] file_name The desired file name for the base NIF file. This name serves as the basis for the names of any Kf files and Kfm files as well.  The path is relative to the working directory unless a full path is specified.
 * \param[in] root_object The root object to start from when writing out the NIF file.
 * \param[in] info A NifInfo structure that contains information such as the version of the NIF file to create.
 * \param[in] export_files What files to write: NIF, NIF + KF + KFM, NIF + KF's + KFM, KF only, KF's only
 * \param[in] kf_type The KF type (Morrowind style, DAoC style, CivIV style, ...)
 */
NIFLIB_API void WriteFileGroup( string const & file_name, NiObject * root_object, const NifInfo & info = NifInfo(), ExportOptions export_files = EXPORT_NIF, NifGame kf_type = KF_MW);

/*!
 * Creates a clone of an entire tree of objects.
 * \param[in] root The root object to start from when cloning the NIF data.  All referenced objects will be included in the new tree.
 * \param[in] version The version of the NIF format to use when writing a file.  Default is version 4.0.0.2.
 * \param[in] user_version The user version of the NIF format to use when writing a file.  Default is user version 0.
 * \return The root of the new cloned tree.
 */
NIFLIB_API Ref<NiObject> CloneNifTree( NiObject * root, unsigned version = 0xFFFFFFFF, unsigned user_version = 0 );


//TODO:  Figure out how to fix this to work with the new system
/*!
 * Merges two Nif trees into one.  For standard Nif files, any NIF Objects with the same name are merged.  For Kf files, objects are attatched to those that match the name specified in the KF root object.  The data stored in a NIF file varies from version to version.  Usually you are safe with the default option (the highest availiable version) but you may need to use an earlier version if you need to clone an obsolete piece of information.
 * \param[in,out] target The root object of the first Nif tree to merge.
 * \param[in] right The root object of the second Nif tree to merge.
 * \param[in] version The version of the nif format to use during the clone operation on the right-hand tree.  The default is the highest version availiable.
 * \param[in] user_version The user version to use during the clone operation.
 */
//NIFLIB_API void MergeNifTrees( NiNodeRef target, NiAVObjectRef right, unsigned int version = 0xFFFFFFFF );
NIFLIB_API void MergeNifTrees( NiNode * target, NiControllerSequence * right, unsigned version = 0xFFFFFFFF, unsigned user_version = 0  );

/*! 
 * Traverses a tree of NIF objects, attempting to move each skeleton root
 * to the natural bind position where no meshes are distorted by skin
 * influences.  This is not always successful and only affects nodes that
 * are skin influences.
 * \param[in] root The root NiNode of the tree.
 */
NIFLIB_API void SendNifTreeToBindPos( NiNode * root );

/*!
 * Returns the common ancestor of several NiAVObjects, or NULL if there is no common
 * ancestor.  None of the objects given can be the common ansestor, the search starts
 * with their parents.
 * \param[in] objects The list of NiAVObjects to try to find the commen ancestor of.
 * \return The common anscestor if one is found, otherwise a NULL reference.
 */
NIFLIB_API Ref<NiNode> FindCommonAncestor( const vector< Ref<NiAVObject> > & objects );

/*!
 * Returns a list of all the ancestors of a given NiAVObject
 * \param[in] leaf The NiAVObject to list the ancestors of.
 * \return A list containing all the ancestors of the given NiAVObject
 */
NIFLIB_API list< Ref<NiNode> > ListAncestors( NiAVObject * leaf );

/*!
 * Returns whether the requested version is explicitly supported.  This does
 * not mean that the file will not open, rather it means that we have not
 * encountered files with this version in our tests yet.
 * \param[in] version The version of the NIF format to test for the support level of.
 * \return Whether the requested version is supported.
 */
NIFLIB_API bool IsSupportedVersion( unsigned int version );

/*!
 * Parses a version string and returns the equivalent version as a byte-packed integer.
 * \param[in] version The version number of the NIF format to parse in string format.
 * \return The version in integer format or VER_INVALID if the version string is not in the correct format.
 */
NIFLIB_API unsigned ParseVersionString( string version );

/*!
 * Takes a NIF version in byte-packed integer format and returns a formatted human-
 * readable string.  For example, 0x04000002 returns the string "4.0.0.2"
 * \param[in] version The NIF version in integer form.
 * \return The equivalent string representation of the version number.
 */
NIFLIB_API string FormatVersionString( unsigned version );

//--USER GUIDE DOCUMENTATION--//

/*! \mainpage Niflib Documentation
\section user_guide User Guide
- \ref intro_page
- \ref starting_out
*/

///////////////////////////////////////////////////////////////////////////////

/*! \page intro_page Introduction

\section compile Compiling the Library

While it is possible to use the pre-compiled DLL file if you are using Microsoft Visual Studio 2005 as your compiler, you may also want to compile it yourself.  You may also want to use Niflib on a platform other than Windows, in which case compiling yourself is the only option.

If you need help to do this, there is information about it on our main website here:  <a href="http://www.niftools.org/wiki/index.php/Niflib/Compile">Compiling Niflib</a>.

\section include_lib Including the Library

Visual Studio 2005 is the preferred compiler for Niflib as this is the platform that all development is done on.  The instructions in this guide assume that you are using this compiler.  If you do not have a copy, you can <a href="http://msdn.microsoft.com/vstudio/express/downloads/default.aspx">download Microsoft Visual C++ 2005 Express</a> for free from Microsoft.  Niflib should work on other compilers, and is tested on GCC from time to time, but you will have to figure out how to use those compilers on your own.

You need to make some changes to the project settings of your project before you can build a program that uses Niflib.  These settings are available when right-clicking the project in the Solution Explorer and clicking “Properties.”  You want to use Niflib in Release or Debug mode, or as a static or dynamic library.

Debug mode means that Visual C++ will put a bunch of extra data in your program to enable you to use the Visual Debugger and see the real code when you set break points or experience a crash.  This adds bloat to your program and slows it down, however, so you should always compile in Release mode when you plan on creating the final version for distribution.

Dynamic linking means that your program will include a Niflib DLL file which the user can replace with a new version so long as the file hasn't changed too much.  It also means that various applications can share one copy of the Niflib code.  On the other hand, it also means that you will need to tell your users how to obtain and install the <a href="http://www.microsoft.com/downloads/details.aspx?familyid=32BC1BEE-A3F9-4C13-9C99-220B62A191EE&displaylang=en">Microsoft Visual C++ 2005 Redistributable Package</a> from Microsoft.  Static linking means that all of the Niflib code that your application uses will be included directly in the EXE file.  This also includes the code from the standard C++ library which would otherwise be part of the MSVS 2005 Runtime DLL.  This means your EXE will be bigger, but also means that your user won't have to install any DLL files.

These are the project settings that you should change to use each combination of Debug/Release and DLL/Static.  This assumes that you've already created a default empty project with Debug and Release configurations, and are altering those with these additional settings.  It also assumes that you're using the provided Niflib project file to build Niflib, and have added Niflib's lib and include folders to the proper paths in the Tools > Options screen under Projects and Solutions > VC++ Directories.

\subsection dll_release DLL Release:

Configuration Properties > C/C++ > Code Generation = Multi-threaded DLL (/MD)

Configuration Properties > Linker > Additional Dependencies = niflib_dll.lib

\subsection dll_debug DLL Debug:

Configuration Properties > C/C++ > Code Generation = Multi-threaded Debug DLL (/MDd)

Configuration Properties > Linker > Additional Dependencies = niflib_dll_debug.lib

\subsection static_release Static Release:

Configuration Properties > C/C++ > Code Generation = Multi-threaded (/MT)

Configuration Properties > Linker > Additional Dependencies = niflib_static.lib

Configuration Properties > Preprocessor > Preprocessor Definitions:  (Add this to the end of what is already there, separated by semicolons) NIFLIB_STATIC_LINK 

\subsection static_debug Static Debug:

Configuration Properties > C/C++ > Code Generation = Multi-threaded Debug (/MTd)

Configuration Properties > Linker > Additional Dependencies = niflib_static_debug.lib

Configuration Properties > Preprocessor > Preprocessor Definitions:  (Add this to the end of what is already there, separated by semicolons) NIFLIB_STATIC_LINK 

With that out of the way, you can start writing your source code and include the main Niflib header file:

\code
#include "niflib.h"
\endcode

In addition to the main header file, there are also separate headers for each object type in a NIF file.  To include the NiNode object, for example, include the obj/NiNode.h file like so:

\code
#include "obj/NiNode.h"
\endcode

You will have one such line in your source code for each NIF object that your program needs access to.

Niflib also wraps all its functions in the "Niflib" namespace.  So, depending on your needs, you can either gain access to all Niflib symbols with a using directive that follows the include statements like this:

\code
using namespace Niflib;
\endcode

Or you can gain access to some symbols but not others with specific using directives like this:

\code
using Niflib::NiNodeRef;
using Niflib::NiObjectRef;
using Niflib::ReadNifTree;
\endcode

Finally, you can simply prepend all of your Niflib symbols with "Niflib::" like this:

\code
Niflib::NiObjectRef niObj = Niflib::ReadNifTree( "test.nif" );
\endcode

\section exept Exceptions

Niflib uses C++ exceptions rather than error return codes. These are a lot more convenient in that you don't have to wrap every single function in an if-test, but not everyone understands what they are, so I thought I'd provide enough of an intro to get you along.

Very basically, if you want to check if Niflib function calls are failing and why, then wrap them in a try block like this:

\code
try {
    //Niflib Function Call
    vector<NiObject> objects = ReadNifList( current_file );
}
catch( exception & e ) {
    cout << "Error: " << e.what() << endl;
    return 0;
}
catch( ... ) {
    cout << "Unknown Exception." << endl;
    return 0;
}
\endcode

The really nice thing about exceptions is that you can place all of your Niflib calls within one try block, and if any one of them fails, execution will jump to the catch block and tell you what went wrong. The first catch block will react to any exception thrown explicitly by Niflib, and an error message can be extracted and printed. Other exceptions, such as from bugs in the library or errors it never occurred to us to test for, will go to the second block which is a catch-all statement that will end your program for any other reason.

There are ways to recover from exceptions, but this should be enough to allow you to at least exit gracefully if a function signals an error.

\section stl_temp STL & Templates

Niflib makes extensive use of the standard template library(STL), and also includes some templates of its own. You should be familiar with the template syntax for defining variables (ex: template<type>) You should also be familiar with at least the following STL built-in types: string, vector, and list.

//<center>\ref starting_out "Next Section >>>"</center>

*/

///////////////////////////////////////////////////////////////////////////////

/*! \page starting_out Starting Out with Niflib

\section file_basics NIF File Basics

NIF files are the result of the NetImmmerse/Gamebryo engine saving the current state of a scene graph.  A scene graph is a tree of 3D transforms that has meshes and rendering instructions attached.  Each object is a class which, when the file is saved, writes its contents to disk.  So the NIF file is a listing of all the NIF classes, or objects, that are required to recreate a particular scene.

The objects in a NIF file all inherit from the NiObject class and reference each other in various ways.  These relationships are reconstructed when the file is loaded from disk and can then be broken or redirected by you.  The most important structure is formed by the scene graph objects.  These objects inherit from the NiAVObject class and form the spatial structure of the scene represented by the NIF file.  Each has a 3D transform that is relative to its parent.

Attached to the NiAVObject classes are various other sorts of objects that either contain the raw data used to render the scene, such as the vertices in NiTriBasedGeomData and the animation key frames in NiKeyFrameData, or modify the way the scene is drawn in some other way such as objects inheriting from NiProperty and NiExtraData.

Each object type has member functions which allow you to get and set data, adjust linkage to other objects, and some also include functions to perform useful calculations on the data.

You do not access the classes directly, however.  Niflib uses reference counting to determine when objects are destroyed, so you always access a class through a Ref smart pointer.  This is a template which takes the class as its template argument, such as Ref<NiNode>.  For each type of Ref a typedef has been provided in the form of [class name]Ref, so Ref<NiNode> has the typedef NiNodeRef, and this name can be used instead of the more unusual template syntax.  When the last Ref smart pointer that points to a particular object is reassigned or goes out of scope, that object will take care of cleaning itself up automatically.

Objects use Ref smart pointers internally as well, so you don't have to worry about objects that are referenced by other objects destroying themselves unexpectedly.  Also, any function that takes a pointer to a NIF object, such as “NiObject*” will also take appropriate Ref versions of compatible objects.  Compatible objects are those that can be converted to the correct type via a static cast.  That is, a derived type can be substituted for a type that it inherits from.

\section rw_files Reading and Writing NIF Files

To check whether a file is really a NIF file, call the CheckNifVersion() function. You can then call the IsSupportedVersion() function to determine whether the data in the file may not be well understood.  There are two ways to read in a NIF file – as a list of objects in the order they appear in the file and as a single Ref pointing to the root of the scene graph tree from which all other objects can be found by following the links between objects.  Most of the time you will probably want to use the tree method, as this is the only one eligible for writing.  The list method is provided for uses such as Niflyze that need to retrieve all objects, regardless of whether we fully understand the links that keep them from destroying themselves.  Unsupported objects may not be included in the tree representation if no other objects reference them.  So most of the time, you're going to want to call the ReadNifTree() function.

That's all there is to reading in a NIF file.  If all goes well with the reading process (no exception was thrown), you will have at least one NIF object in memory – the root object of the tree.  You can pass this same object to the WriteNifTree() function to create a new NIF file from the representation in memory.

WARNING:  Some features of the NIF format are still unsupported by Niflib, therefore in some cases the exported NIF may either be different from the original, or completely unusable.  DO NOT OVERWRITE THE ORIGINAL NIF FILE.

\section work_blk Working with NIF Objects

New class objects don't have to just come from loaded NIF files.  To create an object yourself, you can do so by using the C++ new keyword like so:

\code
RefNiNode node = new NiNode;
\endcode

It is recommended to always use smart pointers, rather than plain pointers, to ensure that your object is not destroyed before you realize it.  So do NOT do this:

\code
NiNode * node = new NiNode;
\endcode

All NIF objects inherit from NiObject so a good place to start would be understanding the methods of that class.

You can access the member functions of any class through a Ref smart pointer of the right type by using the -> operator, like so:

\code
niNode->GetChildren;
\endcode

If you have a Ref of one type, such as a generic NiObjectRef, and want to do something with the object that requires it to be the more specialized NiNode type, you use the DynamicCast() template function.  To cast from a NiObjectRef to a NiNodeRef, you would do the following:

\code
NiObjectRef root = ReadNifTree( “test.nif” );
NiNodeRef node = DynamicCast<NiNode>( root );
if ( node != NULL ) {
   ...
\endcode

Note the template syntax of the DynamicCast() function.  Notice also that you must always check the value returned by DynamicCast().  If the cast is not successful, i.e. the object is not a derived type of the one you're trying to cast it to, the function will return NULL.

Casting down the inheritance tree is usually automatic, but you can also explicitly call the StaticCast() function.

One useful function of all NIF objects is the NiObject::asString() function.  You can use it to get an English summary of the contents of that object.  You can also call the NiObject::GetIDString() function to get a short readout that includes the memory address, type, and name, if any, of the object.

You will probably also want to know the type of a object at some point.  Each NIF object has a static member variable called TYPE which uniquely identifies that type of object.  For example, the type constant for NiNode is NiNode::TYPE while the type constant for NiAVObject is NiAVObject::TYPE.  These constants should be used instead of the object name string since comparisons between the unique type ID number are much faster than string comparisons, and because these comparisons are aware of inheritance.  The type objects also have a function which you can use to get the type name at any time, the Type::GetTypeName() function.

For example, you may have a program that does something to NiGeometry objects.  There are many types of NiGeometry objects in a NIF file, but perhaps for what you're doing you only need to know whether the object is derived from the NiGeometry type.  You can do this without attempting a dynamic cast by using the NiObject:: IsDerivedType () function.  For example:

\code
NiObjectRef niObj = new NiTriShapeData;
if ( niObj->IsDerivedType( NiGeometry::TYPE ) ) {
	NiGeometryRef niGeom = DynamicCast<NiGeometry>(niObj);
	//You can proceed with the assumption that the dynamic cast was successful
\endcode

<center>\ref intro_page "<< Previous Section"</center>

*/

}
#endif
