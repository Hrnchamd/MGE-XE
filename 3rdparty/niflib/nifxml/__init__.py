# TODO: split in multiple files

"""
This module generates C++ code for Niflib from the NIF file format specification XML.

@author: Amorilia
@author: Shon

@contact: http://niftools.sourceforge.net

@copyright:
Copyright (c) 2005, NIF File Format Library and Tools.
All rights reserved.

@license:
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

  - Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

  - Neither the name of the NIF File Format Library and Tools
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
POSSIBILITY OF SUCH DAMAGE.

@var native_types: Maps name of basic or compound type to name of type implemented manually in Niflib.
    These are the types tagged by the niflibtype tag in the XML. For example,
    if a (basic or compound) type with C{name="ferrari"} has C{niflibtype="car"}
    then C{native_types["ferrari"]} equals the string C{"car"}.
@type native_types: C{dictionary}

@var basic_types: Maps name of basic type to L{Basic} instance.
@type basic_types: C{dictionary}

@var compound_types:  Maps name of compound type to a L{Compound} instance.
@type compound_types: C{dictionary}

@var block_types: Maps name of the block name to a L{Block} instance.
@type block_types: C{list}

@var basic_names: Sorted keys of L{basic_types}.
@type basic_names: C{list}

@var compound_names: Sorted keys of L{compound_types}.
@type compound_names: C{list}

@var block_names: Sorted keys of L{block_types}.
@type block_names: C{list}

@var ACTION_READ: Constant for use with CFile::stream. Causes it to generate Niflib's Read function.
@type ACTION_READ: C{int}

@var ACTION_WRITE: Constant for use with CFile::stream.  Causes it to generate Niflib's Write function.
@type ACTION_WRITE: C{int}

@var ACTION_OUT: Constant for use with CFile::stream.  Causes it to generate Niflib's asString function.
@type ACTION_OUT: C{int}

@var ACTION_FIXLINKS: Constant for use with CFile::stream.  Causes it to generate Niflib's FixLinks function.
@type ACTION_FIXLINKS: C{int}

@var ACTION_GETREFS: Constant for use with CFile::stream.  Causes it to generate Niflib's GetRefs function.
@type ACTION_GETREFS: C{int}
"""

from xml.dom.minidom import *
from textwrap import wrap

import sys
import os

#
# global data
#

native_types = {}
native_types['TEMPLATE'] = 'T'
basic_types = {}
enum_types = {}
compound_types = {}
block_types = {}
version_types = {}

basic_names = []
compound_names = []
enum_names = []
block_names = []
version_names = []

ACTION_READ = 0
ACTION_WRITE = 1
ACTION_OUT = 2
ACTION_FIXLINKS = 3
ACTION_GETREFS = 4

#
# HTML Template class
#

class Template:
    """
    This class processes template files.  These files have tags enclosed
    in curly brackets like this: {tag}, which are replaced when a template
    is processed.
    """
    def __init__(self):
        #Initialize variable dictionary
        self.vars = {}
        
    def set_var(self, var_name, value):
        self.vars[var_name] = value

    def parse(self, file_name):
        #Open file and read contents to txt variable
        f = file(file_name, 'r')
        txt = f.read()
        f.close()

        #Loop through all variables, replacing them in the template text
        for i in self.vars:
            txt = txt.replace( "{" + i + "}", self.vars[i] )

        #return result
        return txt
        
#
# C++ code formatting functions
#

class CFile(file):
    """
    This class represents a C++ source file.  It is used to open the file for output
    and automatically handles indentation by detecting brackets and colons.
    It also handles writing the generated Niflib C++ code.
    @ivar indent: The current level of indentation.
    @type indent: int
    @ivar backslash_mode: Determines whether a backslash is appended to each line for creation of multi-line defines
    @type backslash_mode: bool
    """
    def __init__(self, filename, mode):
        """
        This constructor requires the name of the file to open and the IO mode to open it in.
        @param filename: The name of the ouput file to open
        @type filename: string
        @param mode: The IO Mode.  Same as fopen?  Usually should be 'r', 'w', or 'a'
        @type mode: char
        """
        file.__init__(self, filename, mode)
        self.indent = 0
        self.backslash_mode = False
    

    def code(self, txt = None):
        r"""
        Formats a line of C++ code; the returned result always ends with a newline.
        If txt starts with "E{rb}", indent is decreased, if it ends with "E{lb}", indent is increased.
        Text ending in "E{:}" de-indents itself.  For example "publicE{:}"
        Result always ends with a newline
        @param txt: None means just a line break.  This will also break the backslash, which is kind of handy.
            "\n" will create a backslashed newline in backslash mode.
        @type txt: string, None
        """
        # txt 
        # this will also break the backslash, which is kind of handy
        # call code("\n") if you want a backslashed newline in backslash mode
        if txt == None:
            self.write("\n")
            return
    
        # block end
        if txt[:1] == "}": self.indent -= 1
        # special, private:, public:, and protected:
        if txt[-1:] == ":": self.indent -= 1
        # endline string
        if self.backslash_mode:
            endl = " \\\n"
        else:
            endl = "\n"
        # indent string
        prefix = "\t" * self.indent
        # strip trailing whitespace, including newlines
        txt = txt.rstrip()
        # indent, and add newline
        result = prefix + txt.replace("\n", endl + prefix) + endl
        # block start
        if txt[-1:] == "{": self.indent += 1
        # special, private:, public:, and protected:
        if txt[-1:] == ":": self.indent += 1
    
        self.write(result)
    
    
    # 
    def comment(self, txt):
        """
        Wraps text in Doxygen-style C++ comments and outputs it to the file.  Handles multilined comments as well.
        Result always ends with a newline
        @param txt: The text to enclose in a Doxygen comment
        @type txt: string
        """
        if self.backslash_mode: return # skip comments when we are in backslash mode
        self.code("/*!\n * " + "\n".join(wrap(txt)).replace("\n", "\n * ") + "\n */")
    
    def declare(self, block):
        """
        Formats the member variables for a specific class as described by the XML and outputs the result to the file.
        @param block: The class or struct to generate member functions for.
        @type block: Block, Compound
        """
        if isinstance(block, Block):
            #self.code('protected:')
            prot_mode = True
        for y in block.members:
            if y.is_declared and not y.is_duplicate:
                if isinstance(block, Block):
                    if y.is_public and prot_mode:
                        self.code('public:')
                        prot_mode = False
                    elif not y.is_public and not prot_mode:
                        self.code('protected:')
                        prot_mode = True
                self.comment(y.description)
                self.code(y.code_declare())
                if y.func:
                  self.comment(y.description)
                  self.code("%s %s() const;"%(y.ctype,y.func))

    def stream(self, block, action, localprefix = "", prefix = "", arg_prefix = "", arg_member = None):
        """
        Generates the function code for various functions in Niflib and outputs it to the file.
        @param block: The class or struct to generate the function for.
        @type block: Block, Compound
        @param action: The type of function to generate, valid values are::
            ACTION_READ - Read function.
            ACTION_WRITE - Write function
            ACTION_OUT - asString function
            ACTION_FIXLINKS - FixLinks function
            ACTION_GETREFS - GetRefs function
        @type action: ACTION_X constant
        @param localprefix: ?
        @type localprefix: string
        @param prefix: ?
        @type prefix: string
        @param arg_prefix: ?
        @type arg_prefix: string
        @param arg_member: ?
        @type arg_member: None, ?
        """
        lastver1 = None
        lastver2 = None
        lastuserver = None
        lastcond = None
        # stream name
        if action == ACTION_READ:
            stream = "in"
        else:
            stream = "out"
        

        # preperation
        if isinstance(block, Block) or block.name in ["Footer", "Header"]:
            if action == ACTION_READ:
                if block.has_links or block.has_crossrefs:
                    self.code("unsigned int block_num;")
            if action == ACTION_OUT:
                self.code("stringstream out;")
                self.code("unsigned int array_output_count = 0;")
            if action == ACTION_GETREFS:
                self.code("list<Ref<NiObject> > refs;")

        # stream the ancestor
        if isinstance(block, Block):
            if block.inherit:
                if action == ACTION_READ:
                    self.code("%s::Read( %s, link_stack, version, user_version );"%(block.inherit.cname, stream))
                elif action == ACTION_WRITE:
                    self.code("%s::Write( %s, link_map, version, user_version );"%(block.inherit.cname, stream))
                elif action == ACTION_OUT:
                    self.code("%s << %s::asString();"%(stream, block.inherit.cname))
                elif action == ACTION_FIXLINKS:
                    self.code("%s::FixLinks( objects, link_stack, version, user_version );"%block.inherit.cname)
                elif action == ACTION_GETREFS:
                    self.code("refs = %s::GetRefs();"%block.inherit.cname)

        # declare and calculate local variables (TODO: GET RID OF THIS; PREFERABLY NO LOCAL VARIABLES AT ALL)
        if action in [ACTION_READ, ACTION_WRITE, ACTION_OUT]:
            block.members.reverse() # calculated data depends on data further down the structure
            for y in block.members:
                # read + write + out: declare
                if not y.is_declared and not y.is_duplicate:
                  # declare it
                  self.code(y.code_declare(localprefix))
                  # write + out: calculate
                  if action in [ACTION_WRITE, ACTION_OUT]:
                      if y.cond_ref:
                          assert(y.is_declared) # bug check
                      elif y.arr1_ref:
                          assert(not y.is_declared) # bug check
                          self.code('%s%s = (%s)(%s%s.size());'%(localprefix, y.cname, y.ctype, prefix, y.carr1_ref[0]))
                      elif y.arr2_ref:
                          assert(not y.is_declared) # bug check
                          if not y.arr1.lhs:
                              self.code('%s%s = (%s)(%s%s.size());'%(localprefix, y.cname, y.ctype, prefix, y.carr2_ref[0]))
                          else:
                              # index of dynamically sized array
                              self.code('%s%s.resize(%s%s.size());'%(localprefix, y.cname, prefix, y.carr2_ref[0]))
                              self.code('for (unsigned int i%i = 0; i%i < %s%s.size(); i%i++)'%(self.indent, self.indent, localprefix, y.cname, self.indent))
                              self.code('\t%s%s[i%i] = (%s)(%s%s[i%i].size());'%(localprefix, y.cname, self.indent, y.ctype, prefix, y.carr2_ref[0], self.indent))
                      elif y.func:
                          assert(not y.is_declared) # bug check
                          self.code('%s%s = %s%s();'%(localprefix, y.cname, prefix, y.func))
                      else:
                          assert(y.is_declared) # bug check
                          
                elif y.is_declared and not y.is_duplicate and not y.is_manual_update and action in [ACTION_WRITE, ACTION_OUT]:
                  if y.func:
                      self.code('%s%s = %s%s();'%(prefix, y.cname, prefix, y.func))
                  elif y.arr1_ref:
                    if not y.arr1 or not y.arr1.lhs: # Simple Scalar
                      cref = block.find_member(y.arr1_ref[0], True) 
                      # if not cref.is_duplicate and not cref.next_dup and (not cref.cond.lhs or cref.cond.lhs == y.name):
                        # self.code('assert(%s%s == (%s)(%s%s.size()));'%(prefix, y.cname, y.ctype, prefix, cref.cname))
                      self.code('%s%s = (%s)(%s%s.size());'%(prefix, y.cname, y.ctype, prefix, cref.cname))
                  elif y.arr2_ref: # 1-dimensional dynamic array
                    cref = block.find_member(y.arr2_ref[0], True) 
                    if not y.arr1 or not y.arr1.lhs: # Second dimension
                      # if not cref.is_duplicate and not cref.next_dup (not cref.cond.lhs or cref.cond.lhs == y.name):
                       # self.code('assert(%s%s == (%s)((%s%s.size() > 0) ? %s%s[0].size() : 0));'%(prefix, y.cname, y.ctype, prefix, cref.cname, prefix, cref.cname))
                      self.code('%s%s = (%s)((%s%s.size() > 0) ? %s%s[0].size() : 0);'%(prefix, y.cname, y.ctype, prefix, cref.cname, prefix, cref.cname))
                    else:
                        # index of dynamically sized array
                        self.code('for (unsigned int i%i = 0; i%i < %s%s.size(); i%i++)'%(self.indent, self.indent, prefix, cref.cname, self.indent))
                        self.code('\t%s%s[i%i] = (%s)(%s%s[i%i].size());'%(prefix, y.cname, self.indent, y.ctype, prefix, cref.cname, self.indent))
                  # else: #has duplicates needs to be selective based on version
                    # self.code('assert(!"%s");'%(y.name))
            block.members.reverse() # undo reverse


        # now comes the difficult part: processing all members recursively
        for y in block.members:
            # get block
            if y.type in basic_types:
                subblock = basic_types[y.type]
            elif y.type in compound_types:
                subblock = compound_types[y.type]
            else:
                subblock = enum_types[y.type]
            # check for links
            if action in [ACTION_FIXLINKS, ACTION_GETREFS]:
                if not subblock.has_links and not subblock.has_crossrefs:
                    continue # contains no links, so skip this member!
            if action == ACTION_OUT:
                if y.is_duplicate:
                    continue # don't write variables twice
            # resolve array & cond references
            y_arr1_lmember = None
            y_arr2_lmember = None
            y_cond_lmember = None
            y_arg = None
            y_arr1_prefix = ""
            y_arr2_prefix = ""
            y_cond_prefix = ""
            y_arg_prefix = ""
            if y.arr1.lhs or y.arr2.lhs or y.cond.lhs or y.arg:
                for z in block.members:
                    if not y_arr1_lmember and y.arr1.lhs == z.name:
                        y_arr1_lmember = z
                    if not y_arr2_lmember and y.arr2.lhs == z.name:
                        y_arr2_lmember = z
                    if not y_cond_lmember and y.cond.lhs == z.name:
                        y_cond_lmember = z
                    if not y_arg and y.arg == z.name:
                        y_arg = z
                if y_arr1_lmember:
                    if y_arr1_lmember.is_declared:
                        y_arr1_prefix = prefix
                    else:
                        y_arr1_prefix = localprefix
                if y_arr2_lmember:
                    if y_arr2_lmember.is_declared:
                        y_arr2_prefix = prefix
                    else:
                        y_arr2_prefix = localprefix
                if y_cond_lmember:
                    if y_cond_lmember.is_declared:
                        y_cond_prefix = prefix
                    else:
                        y_cond_prefix = localprefix
                if y_arg:
                    if y_arg.is_declared:
                        y_arg_prefix = prefix
                    else:
                        y_arg_prefix = localprefix
            # resolve this prefix
            if y.is_declared:
                y_prefix = prefix
            else:
                y_prefix = localprefix
            # resolve arguments
            if y.arr1 and y.arr1.lhs == 'ARG':
                y.arr1.lhs = arg_member.name
                y.arr1.clhs = arg_member.cname
                y_arr1_prefix = arg_prefix
            if y.arr2 and y.arr2.lhs == 'ARG':
                y.arr2.lhs = arg_member.name
                y.arr2.clhs = arg_member.cname
                y_arr2_prefix = arg_prefix
            if y.cond and y.cond.lhs == 'ARG':
                y.cond.lhs = arg_member.name
                y.cond.clhs = arg_member.cname
                y_cond_prefix = arg_prefix
            # conditioning
            y_cond = y.cond.code(y_cond_prefix)
            if action in [ACTION_READ, ACTION_WRITE, ACTION_FIXLINKS]:
                if lastver1 != y.ver1 or lastver2 != y.ver2 or lastuserver != y.userver:
                    # we must switch to a new version block    
                    # close old version block
                    if lastver1 or lastver2 or lastuserver: self.code("};")
                    # close old condition block as well    
                    if lastcond:
                        self.code("};")
                        lastcond = None
                    # start new version block
                    if not y.userver:
                        if y.ver1 and not y.ver2:
                            self.code("if ( version >= 0x%08X ) {"%y.ver1)
                        elif not y.ver1 and y.ver2:
                            self.code("if ( version <= 0x%08X ) {"%y.ver2)
                        elif y.ver1 and y.ver2:
                            self.code("if ( ( version >= 0x%08X ) && ( version <= 0x%08X ) ) {"%(y.ver1, y.ver2))
                    else:
                        if y.ver1 and not y.ver2:
                            self.code("if ( ( version >= 0x%08X ) && ( user_version == %s ) ) {"%(y.ver1, y.userver))
                        elif not y.ver1 and y.ver2:
                            self.code("if ( ( version <= 0x%08X ) && ( user_version == %s ) ) {"%(y.ver2, userver))
                        elif y.ver1 and y.ver2:
                            self.code("if ( ( version >= 0x%08X ) && ( version <= 0x%08X ) && ( user_version == %s ) ) {"%(y.ver1, y.ver2, y.userver))
                    # start new condition block
                    if lastcond != y_cond and y_cond:
                        self.code("if ( %s ) {"%y_cond)
                else:
                    # we remain in the same version block    
                    # check condition block
                    if lastcond != y_cond:
                        if lastcond:
                            self.code("};")
                        if y_cond:
                            self.code("if ( %s ) {"%y_cond)
            elif action == ACTION_OUT:
                # check condition block
                if lastcond != y_cond:
                    if lastcond:
                        self.code("};")
                    if y_cond:
                        self.code("if ( %s ) {"%y_cond)
    
            # loop over arrays
            # and resolve variable name
            if not y.arr1.lhs:
                z = "%s%s"%(y_prefix, y.cname)
            else:
                if action == ACTION_OUT:
                    self.code("array_output_count = 0;")
                if y.arr1.lhs.isdigit() == False:
                    if action == ACTION_READ:
                      # default to local variable, check if variable is in current scope if not then try to use
                      #   definition from resized child
                      memcode = "%s%s.resize(%s);"%(y_prefix, y.cname, y.arr1.code(y_arr1_prefix))
                      mem = block.find_member(y.arr1.lhs, True) # find member in self or parents
                      if mem and not mem.is_declared and not mem.is_duplicate and mem.arr1_ref:
                          localmem = block.find_member(y.arr1.lhs, False) # find only in self for locals
                          if not localmem:
                            ref1 = block.find_first_ref(mem.name)
                            if ref1 and ref1.name != y.name:
                              memcode = "%s%s.resize(%s%s.size());"%(y_prefix, y.cname, prefix, member_name(ref1.name))
                      self.code(memcode)
                      
                    self.code(\
                        "for (unsigned int i%i = 0; i%i < %s%s.size(); i%i++) {"%(self.indent, self.indent, y_prefix, y.cname, self.indent))
                else:
                    self.code(\
                        "for (unsigned int i%i = 0; i%i < %s; i%i++) {"\
                        %(self.indent, self.indent, y.arr1.code(y_arr1_prefix), self.indent))
                if action == ACTION_OUT:
                        self.code('if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {')
                        self.code('%s << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;'%stream)
                        self.code('break;')
                        self.code('};')
                        
                if not y.arr2.lhs:
                    z = "%s%s[i%i]"%(y_prefix, y.cname, self.indent-1)
                else:
                    if not y.arr2_dynamic:
                        if y.arr2.lhs.isdigit() == False:
                            if action == ACTION_READ:
                                self.code("%s%s[i%i].resize(%s);"%(y_prefix, y.cname, self.indent-1, y.arr2.code(y_arr2_prefix)))
                            self.code(\
                                "for (unsigned int i%i = 0; i%i < %s%s[i%i].size(); i%i++) {"\
                                %(self.indent, self.indent, y_prefix, y.cname, self.indent-1, self.indent))
                        else:
                            self.code(\
                                "for (unsigned int i%i = 0; i%i < %s; i%i++) {"\
                                %(self.indent, self.indent, y.arr2.code(y_arr2_prefix), self.indent))
                    else:
                        if action == ACTION_READ:
                            self.code("%s%s[i%i].resize(%s[i%i]);"%(y_prefix, y.cname, self.indent-1, y.arr2.code(y_arr2_prefix), self.indent-1))
                        self.code(\
                            "for (unsigned int i%i = 0; i%i < %s[i%i]; i%i++) {"\
                            %(self.indent, self.indent, y.arr2.code(y_arr2_prefix), self.indent-1, self.indent))
                    z = "%s%s[i%i][i%i]"%(y_prefix, y.cname, self.indent-2, self.indent-1)
    
            if native_types.has_key(y.type):
                # these actions distinguish between refs and non-refs
                if action in [ACTION_READ, ACTION_WRITE, ACTION_FIXLINKS, ACTION_GETREFS]:
                    if (not subblock.is_link) and (not subblock.is_crossref):
                        # not a ref
                        if action in [ACTION_READ, ACTION_WRITE]:
                            if not y.arg:
                                self.code("NifStream( %s, %s, version );"%(z, stream))
                            else:
                                self.code("NifStream( %s, %s, version, %s%s );"%(z, stream, y_prefix, y.carg))
                    else:
                        # a ref
                        if action == ACTION_READ:
                            self.code("NifStream( block_num, %s, version );"%stream)
                            if y.is_declared:
                                self.code("link_stack.push_back( block_num );")
                        elif action == ACTION_WRITE:
                            self.code("if ( %s != NULL )"%z)
                            self.code("\tNifStream( link_map.find( StaticCast<NiObject>(%s) )->second, %s, version );"%(z, stream))
                            self.code("else")
                            self.code("\tNifStream( 0xffffffff, %s, version );"%stream)
                        elif action == ACTION_FIXLINKS:
                            if y.is_declared:
                                
                                self.code("%s = FixLink<%s>( objects, link_stack, version );"%(z,y.ctemplate))
                                
                        elif action == ACTION_GETREFS and subblock.is_link:
                            if y.is_declared and not y.is_duplicate:
                                self.code('if ( %s != NULL )\n\trefs.push_back(StaticCast<NiObject>(%s));'%(z,z))
                # the following actions don't distinguish between refs and non-refs
                elif action == ACTION_OUT:
                    if not y.arr1.lhs:
                        self.code('%s << "%*s%s:  " << %s << endl;'%(stream, 2*self.indent, "", y.name, z))
                    else:
                        self.code('if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {')
                        self.code('break;')
                        self.code('};')
                        self.code('%s << "%*s%s[" << i%i << "]:  " << %s << endl;'%(stream, 2*self.indent, "", y.name, self.indent-1, z))
                        self.code('array_output_count++;')
            else:
                subblock = compound_types[y.type]
                if not y.arr1.lhs:
                    self.stream(subblock, action, "%s%s_"%(localprefix, y.cname), "%s."%z, y_arg_prefix,  y_arg)
                elif not y.arr2.lhs:
                    self.stream(subblock, action, "%s%s_"%(localprefix, y.cname), "%s."%z, y_arg_prefix, y_arg)
                else:
                    self.stream(subblock, action, "%s%s_"%(localprefix, y.cname), "%s."%z, y_arg_prefix, y_arg)

            # close array loops
            if y.arr1.lhs:
                self.code("};")
                if y.arr2.lhs:
                    self.code("};")

            lastver1 = y.ver1
            lastver2 = y.ver2
            lastuserver = y.userver
            lastcond = y_cond

        if action in [ACTION_READ, ACTION_WRITE, ACTION_FIXLINKS]:
            if lastver1 or lastver2 or lastuserver:
                self.code("};")
        if action in [ACTION_READ, ACTION_WRITE, ACTION_FIXLINKS, ACTION_OUT]:
            if lastcond:
                self.code("};")

        # the end
        if isinstance(block, Block) or block.name in ["Header", "Footer"]:
            if action == ACTION_OUT:
                self.code("return out.str();")
            if action == ACTION_GETREFS:
                self.code("return refs;")

    # declaration
    # print "$t Get$n() const; \nvoid Set$n($t value);\n\n";
    def getset_declare(self, block, prefix = ""): # prefix is used to tag local variables only
      for y in block.members:
        if not y.func:
          if y.cname.find("Unk") == -1:
            self.code( y.getter_declare("", ";") )
            self.code( y.setter_declare("", ";") )
            self.code()


def class_name(n):
    """
    Formats a valid C++ class name from the name format used in the XML.
    @param n: The class name to format in C++ style.
    @type n: string
    @return The resulting valid C++ class name
    @rtype: string
    """
    if n == None: return None
    try:
        return native_types[n]
    except KeyError:
        return n.replace(' ', '_')

    if n == None: return None
    try:
        return native_types[n]
    except KeyError:
        pass
    if n == 'TEMPLATE': return 'T'
    n2 = ''
    for i, c in enumerate(n):
        if ('A' <= c) and (c <= 'Z'):
            if i > 0: n2 += '_'
            n2 += c.lower()
        elif (('a' <= c) and (c <= 'z')) or (('0' <= c) and (c <= '9')):
            n2 += c
        else:
            n2 += '_'
    return n2

def define_name(n):
    """
    Formats an all-uppercase version of the name for use in C++ defines.
    @param n: The class name to format in define style.
    @type n: string
    @return The resulting valid C++ define name
    @rtype: string
    """
    n2 = ''
    for i, c in enumerate(n):
        if ('A' <= c) and (c <= 'Z'):
            if i > 0:
                n2 += '_'
                n2 += c
            else:
                n2 += c
        elif (('a' <= c) and (c <= 'z')) or (('0' <= c) and (c <= '9')):
            n2 += c.upper()
        else:
            n2 += '_'
    return n2

def member_name(n):
    """
    Formats a version of the name for use as a C++ member variable.
    @param n: The attribute name to format in variable style.
    @type n: string
    @return The resulting valid C++ variable name
    @rtype: string
    """
    if n == None: return None
    if n == 'ARG': return 'ARG'
    n2 = ''
    lower = True
    for i, c in enumerate(n):
        if c == ' ':
            lower = False
        elif (('A' <= c) and (c <= 'Z')) or (('a' <= c) and (c <= 'z')) or (('0' <= c) and (c <= '9')):
            if lower:
                n2 += c.lower()
            else:
                n2 += c.upper()
                lower = True
        else:
            n2 += '_'
            lower = True
    return n2

def version2number(s):
    """
    Translates a legible NIF version number to the packed-byte numeric representation. For example, "10.0.1.0" is translated to 0x0A000100.
    @param s: The version string to translate into numeric form.
    @type s: string
    @return The resulting numeric version of the given version string.
    @rtype: int
    """
    if not s: return None
    l = s.split('.')
    if len(l) > 4:
        assert(False)
        return int(s)
    else:
        version = 0
        for i in range( 0, len(l) ):
            version += int(l[i]) << ((3-i) * 8)
            #return (int(l[0]) << 24) + (int(l[1]) << 16) + (int(l[2]) << 8) + int(l[3])
        return version

def userversion2number(s):
    """
    Translates a legible NIF user version number to the packed-byte numeric representation.
    Currently just converts the string to an int as this may be a raw number.
    Probably to be used just in case this understanding changes.
    @param s: The version string to translate into numeric form.
    @type s: string
    @return The resulting numeric version of the given version string.
    @rtype: int
    """
    if not s: return None
    return int(s)

class Expr:
    """
    Represents a mathmatical expression?
    @ivar lhs: The left hand side of the expression?
    @type lhs: string
    @ivar clhs: The C++ formatted version of the left hand side of the expression?
    @type clhs: string
    @ivar op: The operator used in the expression.  ==, &&, !=, etc.
    @type op: string
    @ivar rhs: The right hand side of the expression?
    @type rhs: string
    """
    def __init__(self, n):
        """
        This constructor takes the expression in the form of a string and tokenizes it into left-hand side, operator, right hand side, and something called clhs.
        @param n: The expression to tokenize.
        @type n: string
        """
        if n == None:
            self.lhs = None
            self.clhs = None
            self.op = None
            self.rhs = None
            return
        
        if n.find('&&') != -1:
            self.lhs = Expr(n[n.find('(')+1:n.find(')')])
            self.clhs = None
            self.op = '&&'
            self.rhs = Expr(n[n.rfind('(')+1:n.rfind(')')])
            return
            
        x = None
        for op in [ '>=', '<=', '<', '>', '==', '!=', '&' ]:
            if n.find(op) != -1:
                x = n.split(op)
                break
        if not x:
            self.lhs = n.strip()
            self.clhs = member_name(self.lhs)
            self.op = None
            self.rhs = None
        elif len(x) == 2:
            self.lhs = x[0].strip()
            self.clhs = member_name(self.lhs)
            self.op = op
            self.rhs = x[1].strip()
        else:
            # bad syntax
            print x
            raise str('"%s" is an invalid expression'%n)

    def code(self, prefix):
        """
        This function formats the expression as a string?  
        right hand side, and something called clhs.
        @param prefix: An optional prefix used in some situations?
        @type prefix: string
        @return The expression formatted into a string?
        @rtype: string
        """
        if not self.op:
            if not self.lhs: return None
            if self.lhs[0] >= '0' and self.lhs[0] <= '9':
                return self.lhs
            else:
                return prefix + self.clhs
        else:
            if self.op != '&&':
                if self.lhs[0] >= '0' and self.lhs[0] <= '9':
                    return '(%s %s %s)'%(self.lhs, self.op, self.rhs)
                else:
                    return '(%s%s %s %s)'%(prefix, self.clhs, self.op, self.rhs)
            else:
                return '((%s) && (%s))'%(self.lhs.code(prefix), self.rhs.code(prefix))
                
class Option:
    """
    This class represents an option in an option list.
    @ivar value: The C++ value of option variable.  Comes from the "value" attribute of the <option> tag.
    @type value: string
    @ivar name: The name of this member variable.  Comes from the "name" attribute of the <option> tag.
    @type name: string
    @ivar description: The description of this option.  Comes from the text between <option> and </option>.
    @type description: string
    """
    def __init__(self, element):
        """
        This constructor converts an XML <option> element into an Option object.
        """
        assert element.tagName == 'option'
        parent = element.parentNode
        #sisters = parent.getElementsByTagName('option')
        
        # member attributes
        self.value     = element.getAttribute('value')
        self.name      = element.getAttribute('name')
        if element.firstChild:
            assert element.firstChild.nodeType == Node.TEXT_NODE
            self.description = element.firstChild.nodeValue.strip()
        else:
            self.description = self.name

class Member:
    """
    This class represents a member variable?
    @ivar name:  The name of this member variable.  Comes from the "name" attribute of the <add> tag.
    @type name: string
    @ivar type: The type of this member variable.  Comes from the "type" attribute of the <add> tag.
    @type type: string
    @ivar arg: The argument of this member variable.  Comes from the "arg" attribute of the <add> tag.
    @type arg: string
    @ivar template: The template type of this member variable.  Comes from the "template" attribute of the <add> tag.
    @type template: string
    @ivar arr1: The first array size of this member variable.  Comes from the "arr1" attribute of the <add> tag.
    @type arr1: Eval
    @ivar arr2: The first array size of this member variable.  Comes from the "arr2" attribute of the <add> tag.
    @type arr2: Eval
    @ivar cond: The condition of this member variable.  Comes from the "cond" attribute of the <add> tag.
    @type cond: Eval
    @ivar func: The function of this member variable.  Comes from the "func" attribute of the <add> tag.
    @type func: string
    @ivar default: The default value of this member variable.  Comes from the "default" attribute of the <add> tag.
        Formatted to be ready to use in a C++ constructor initializer list.
    @type default: string
    @ivar ver1: The first version this member exists.  Comes from the "ver1" attribute of the <add> tag.
    @type ver1: string
    @ivar ver2: The last version this member exists.  Comes from the "ver2" attribute of the <add> tag.
    @type ver2: string
    @ivar userver: The user version where this member exists.  Comes from the "userver" attribute of the <add> tag.
    @type userver: string
    @ivar is_public: Whether this member will be declared public.  Comes from the "public" attribute of the <add> tag.
    @type is_public: string
    @ivar description: The description of this member variable.  Comes from the text between <add> and </add>.
    @type description: string
    @ivar uses_argument: Specifies whether this attribute uses an argument.
    @type uses_argument: bool
    @ivar type_is_native: Specifies whether the type is implemented natively
    @type type_is_native: bool
    @ivar is_duplicate: Specifies whether this is a duplicate of a previously declared member
    @type is_duplicate: bool
    @ivar arr2_dynamic: Specifies whether arr2 refers to an array (?)
    @type arr2_dynamic: bool
    @ivar arr1_ref: Names of the attributes it is a (unmasked) size of (?)
    @type arr1_ref: string array?
    @ivar arr2_ref: Names of the attributes it is a (unmasked) size of (?)
    @type arr2_ref: string array?
    @ivar cond_ref: Names of the attributes it is a condition of (?)
    @type cond_ref: string array?
    @ivar is_declared: True if it is declared in the class, if false, then field is calculated somehow
    @type is_declared: bool
    @ivar cname: Unlike default, name isn't formatted for C++ so use this instead?
    @type cname: string
    @ivar ctype: Unlike default, type isn't formatted for C++ so use this instead?
    @type ctype: string
    @ivar carg: Unlike default, arg isn't formatted for C++ so use this instead?
    @type carg: string
    @ivar ctemplate: Unlike default, template isn't formatted for C++ so use this instead?
    @type ctemplate: string
    @ivar carr1_ref: Unlike default, arr1_ref isn't formatted for C++ so use this instead?
    @type carr1_ref: string
    @ivar carr2_ref: Unlike default, arr2_ref isn't formatted for C++ so use this instead?
    @type carr2_ref: string
    @ivar ccond_ref: Unlike default, cond_ref isn't formatted for C++ so use this instead?
    @type ccond_ref: string
    @ivar next_dup: Next duplicate member
    @type next_dup: Member
    @ivar is_manual_update: True if the member value is manually updated by the code
    @type is_manual_update: bool
    """
    def __init__(self, element):
        """
        This constructor converts an XML <add> element into a Member object.
        Some sort of processing is applied to the various variables that are copied from the XML tag...
        Seems to be trying to set reasonable defaults for certain types, and put things into C++ format generally. 
        @param prefix: An optional prefix used in some situations?
        @type prefix: string
        @return The expression formatted into a string?
        @rtype: string?
        """
        assert element.tagName == 'add'
        parent = element.parentNode
        sisters = parent.getElementsByTagName('add')
        
        # member attributes
        self.name      = element.getAttribute('name')
        self.type      = element.getAttribute('type')
        self.arg       = element.getAttribute('arg')
        self.template  = element.getAttribute('template')
        self.arr1      = Expr(element.getAttribute('arr1'))
        self.arr2      = Expr(element.getAttribute('arr2'))
        self.cond      = Expr(element.getAttribute('cond'))
        self.func      = element.getAttribute('function')
        self.default   = element.getAttribute('default')
        self.orig_ver1 = element.getAttribute('ver1')
        self.orig_ver2 = element.getAttribute('ver2')
        self.ver1      = version2number(element.getAttribute('ver1'))
        self.ver2      = version2number(element.getAttribute('ver2'))
        self.userver   = userversion2number(element.getAttribute('userver'))
        self.is_public = (element.getAttribute('public') == "1")  
        self.next_dup  = None
        self.is_manual_update = False

        #Get description from text between start and end tags
        if element.firstChild:
            assert element.firstChild.nodeType == Node.TEXT_NODE
            self.description = element.firstChild.nodeValue.strip()
        else:
            self.description = "Unknown."
        
        # Format default value so that it can be used in a C++ initializer list
        if not self.default and (not self.arr1.lhs and not self.arr2.lhs):
            if self.type in ["unsigned int", "unsigned short", "byte", "int", "short", "char"]:
                self.default = "0"
            elif self.type == "bool":
                self.default = "false"
            elif self.type in ["Ref", "Ptr"]:
                self.default = "NULL"
            elif self.type in "float":
                self.default = "0.0"
            elif self.type == "HeaderString":
                pass
            elif self.type == "StringOffset":
                self.default = "-1";
            elif self.type in basic_names:
                self.default = "0"
        if self.default:
            if self.type == "string":
                self.default = "\"" + self.default + "\""
            elif self.type == "float":
                self.default += "f"
            elif self.type in ["Ref", "Ptr", "bool", "Vector3"]:
                pass
            elif self.default[0] == '(' and self.default[-1] == ')':
                self.default = self.default[1:-1]
            else:
                self.default = "(%s)%s"%(class_name(self.type), self.default)
        
        # calculate other stuff
        self.uses_argument = (self.cond.lhs == '(ARG)' or self.arr1.lhs == '(ARG)' or self.arr2.lhs == '(ARG)')
        self.type_is_native = native_types.has_key(self.name) # true if the type is implemented natively

        # calculate stuff from reference to previous members
        # true if this is a duplicate of a previously declared member
        self.is_duplicate = False
        self.arr2_dynamic = False  # true if arr2 refers to an array
        sis = element.previousSibling
        while sis:
            if sis.nodeType == Node.ELEMENT_NODE:
                sis_name = sis.getAttribute('name')
                if sis_name == self.name:
                    self.is_duplicate = True
                sis_arr1 = Expr(sis.getAttribute('arr1'))
                sis_arr2 = Expr(sis.getAttribute('arr2'))
                if sis_name == self.arr2.lhs and sis_arr1.lhs:
                    self.arr2_dynamic = True
            sis = sis.previousSibling

        # calculate stuff from reference to next members
        self.arr1_ref = [] # names of the attributes it is a (unmasked) size of
        self.arr2_ref = [] # names of the attributes it is a (unmasked) size of
        self.cond_ref = [] # names of the attributes it is a condition of
        sis = element.nextSibling
        while sis != None:
            if sis.nodeType == Node.ELEMENT_NODE:
                sis_name = sis.getAttribute('name')
                sis_arr1 = Expr(sis.getAttribute('arr1'))
                sis_arr2 = Expr(sis.getAttribute('arr2'))
                sis_cond = Expr(sis.getAttribute('cond'))
                if sis_arr1.lhs == self.name and (not sis_arr1.rhs or sis_arr1.rhs.isdigit()):
                    self.arr1_ref.append(sis_name)
                if sis_arr2.lhs == self.name and (not sis_arr2.rhs or sis_arr2.rhs.isdigit()):
                    self.arr2_ref.append(sis_name)
                if sis_cond.lhs == self.name:
                    self.cond_ref.append(sis_name)
            sis = sis.nextSibling
        # true if it is declared in the class, if false, this field is calculated somehow
        # so don't declare variables that can be calculated; ("Num Vertices" is a dirty hack, it's used in derived classes as array size so we must declare it)
        # if (self.arr1_ref or self.arr2_ref or self.func) and not self.cond_ref : # and self.name != "Num Vertices":
          # self.is_declared = False
        # else:
        self.is_declared = True

        # C++ names
        self.cname     = member_name(self.name)
        self.ctype     = class_name(self.type)
        self.carg      = member_name(self.arg)
        self.ctemplate = class_name(self.template)
        self.carr1_ref = [member_name(n) for n in self.arr1_ref]
        self.carr2_ref = [member_name(n) for n in self.arr2_ref]
        self.ccond_ref = [member_name(n) for n in self.cond_ref]

    # construction
    # don't construct anything that hasn't been declared
    # don't construct if it has no default
    def code_construct(self):
        if self.is_declared and self.default and not self.is_duplicate:
            return "%s(%s)"%(self.cname, self.default)

    # declaration
    def code_declare(self, prefix = ""): # prefix is used to tag local variables only
        result = self.ctype
        suffix1 = ""
        suffix2 = ""
        keyword = ""
        if self.is_declared and not self.is_duplicate: # is dimension for one or more arrays
          if self.arr1_ref:
            if not self.arr1 or not self.arr1.lhs: # Simple Scalar
              keyword = "mutable "
          elif self.arr2_ref: # 1-dimensional dynamic array
              keyword = "mutable "
                  
        if self.ctemplate:
            if result != "*":
                result += "<%s >"%self.ctemplate
            else:
                result = "%s *"%self.ctemplate
        if self.arr1.lhs:
            if self.arr1.lhs.isdigit():
                if self.arr2.lhs and self.arr2.lhs.isdigit():
                      result = "array< %s, array<%s,%s > >"%(self.arr1.lhs, self.arr2.lhs, result)
                else:
                      result = "array<%s,%s >"%(self.arr1.lhs, result) 
            else:
                if self.arr2.lhs and self.arr2.lhs.isdigit():
                    result = "vector< array<%s,%s > >"%(self.arr2.lhs, result)
                else:
                    if self.arr2.lhs:
                        result = "vector< vector<%s > >"%result
                    else:
                        result = "vector<%s >"%result
        result = keyword + result + " " + prefix + self.cname + suffix1 + suffix2 + ";"
        return result

    def getter_declare(self, scope = "", suffix = ""):
      ltype = self.ctype
      if self.ctemplate:
          if ltype != "*":
              ltype += "<%s >"%self.ctemplate
          else:
              ltype = "%s *"%self.ctemplate
      if self.arr1.lhs:
          if self.arr1.lhs.isdigit():
              ltype = "array<%s,%s > "%(self.arr1.lhs, ltype)
              # ltype = ltype
          else:
              if self.arr2.lhs and self.arr2.lhs.isdigit():
                  ltype = "vector< array<%s,%s > >"%(self.arr2.lhs, ltype)
              else:
                  ltype = "vector<%s >"%ltype
          if self.arr2.lhs:
              if self.arr2.lhs.isdigit():
                  if self.arr1.lhs.isdigit():
                    ltype = "array<%s,%s >"%(self.arr2.lhs,ltype)
                    # ltype = ltype
              else:
                  ltype = "vector<%s >"%ltype
      result = ltype + " " + scope + "Get" + self.cname[0:1].upper() + self.cname[1:] + "() const" + suffix
      return result

    def setter_declare(self, scope = "", suffix = ""):
      ltype = self.ctype
      if self.ctemplate:
          if ltype != "*":
              ltype += "<%s >"%self.ctemplate
          else:
              ltype = "%s *"%self.ctemplate
      if self.arr1.lhs:
          if self.arr1.lhs.isdigit():
            # ltype = "const %s&"%ltype
            if self.arr2.lhs and self.arr2.lhs.isdigit():
                  ltype = "const array< %s, array<%s,%s > >&"%(self.arr1.lhs,self.arr2.lhs, ltype)
            else:
                  ltype = "const array<%s,%s >& "%(self.arr1.lhs,ltype)              
            
          else:
              if self.arr2.lhs and self.arr2.lhs.isdigit():
                  ltype = "const vector< array<%s,%s > >&"%(self.arr2.lhs, ltype)
              else:
                  ltype = "const vector<%s >&"%ltype
      else:
          if not self.type in basic_names:
            ltype = "const %s &"%ltype
             
      result = "void " + scope + "Set" + self.cname[0:1].upper() + self.cname[1:] + "( " + ltype + " value )" + suffix
      return result

class Version:
    def __init__(self, element):
        self.num = element.getAttribute('num')
        self.description = element.firstChild.nodeValue.strip()
        
class Basic:
    def __init__(self, element):
        global native_types

        self.name = element.getAttribute('name')
        assert(self.name) # debug
        self.cname = class_name(self.name)
        self.niflibtype = element.getAttribute('niflibtype')
        assert element.firstChild.nodeType == Node.TEXT_NODE
        self.description = element.firstChild.nodeValue.strip()

        self.count = element.getAttribute('count')

        self.is_link = False
        self.is_crossref = False
        self.has_links = False
        self.has_crossrefs = False

        if self.niflibtype:
            native_types[self.name] = self.niflibtype
            if self.niflibtype == "Ref":
                self.is_link = True
                self.has_links = True
            if self.niflibtype == "*":
                self.is_crossref = True
                self.has_crossrefs = True

        self.template = (element.getAttribute('istemplate') == "1")
        self.options = []

class Enum(Basic):
  def __init__(self, element):
      Basic.__init__(self, element)
      
      self.storage = element.getAttribute('storage')
      #find the Niflib type of the storage
      self.storage = basic_types[self.storage].niflibtype
      self.description = element.firstChild.nodeValue.strip()
             
      self.niflibtype = self.cname
      native_types[self.name] = self.niflibtype
      
      # Locate all special enumeration options
      for option in element.getElementsByTagName('option'):
          x = Option(option)
          self.options.append(x)

class Compound(Basic):
    # create a compound type from the XML <compound /> attributes
    def __init__(self, element):
        Basic.__init__(self, element)

        #the relative path to files in the gen folder
        self.gen_file_prefix = ""
        #the relative path to files in the obj folder
        self.obj_file_prefix = "../obj/"
        #the relative path to files in the root folder
        self.root_file_prefix = "../"

        self.members = []     # list of all members (list of Member)
        self.argument = False # does it use an argument?

        # store all attribute data & calculate stuff
        for member in element.getElementsByTagName('add'):
            x = Member(member)
            self.members.append(x)
            
            # detect templates
            #if x.type == 'TEMPLATE':
            #    self.template = True
            #if x.template == 'TEMPLATE':
            #    self.template = True

            # detect argument
            if x.uses_argument:
                self.argument = True
            else:
                self.argument = False

            # detect links & crossrefs
            y = None
            try:
                y = basic_types[x.type]
            except KeyError:
                try:
                    y = compound_types[x.type]
                except KeyError:
                    pass
            if y:
                if y.has_links:
                    self.has_links = True
                if y.has_crossrefs:
                    self.has_crossrefs = True
                    
        # create duplicate chains for items that need it (only valid in current object scope)
        #  prefer to use iterators to avoid O(n^2) but I dont know how to reset iterators
        for x in self.members:
          atx = False
          for y in self.members:
            if atx:
              if x.name == y.name: # duplicate
                x.next_dup = y
                break
            elif x == y:
              atx = True

    def code_construct(self):
        # constructor
        result = ''
        first = True
        for y in self.members:
            y_code_construct = y.code_construct()
            if y_code_construct:
                if not first:
                    result += ', ' + y_code_construct
                else:
                    result += ' : ' + y_code_construct
                    first = False
        return result

    def code_include_h(self):
        if self.niflibtype: return ""

        result = ""

        # include all required structures
        used_structs = []
        for y in self.members:
            file_name = None
            if y.type != self.name:
                if y.type in compound_names:
                    if not compound_types[y.type].niflibtype:
                        file_name = "%s%s.h"%(self.gen_file_prefix, y.ctype)
                elif y.type in basic_names:
                    if basic_types[y.type].niflibtype == "Ref":
                        file_name = "%sRef.h"%(self.root_file_prefix)
            if file_name and file_name not in used_structs:
                used_structs.append( file_name )
        if used_structs:
            result += "\n// Include structures\n"
        for file_name in used_structs:
            result += '#include "%s"\n'%file_name
        return result
        
    def code_fwd_decl(self):
        if self.niflibtype: return ""
        
        result = ""

        # forward declaration of blocks
        used_blocks = []
        for y in self.members:
            if y.template in block_names and y.template != self.name:
                if not y.ctemplate in used_blocks:
                    used_blocks.append( y.ctemplate )
        if used_blocks:
            result += '\n// Forward define of referenced blocks\n'
        for fwd_class in used_blocks:
            result += 'class %s;\n'%fwd_class
        
        return result

    def code_include_cpp(self, usedirs=False, gen_dir=None, obj_dir=None):
        if self.niflibtype: return ""
        
        if not usedirs:
          gen_dir = self.gen_file_prefix
          obj_dir = self.obj_file_prefix

        result = ""

        if self.name in compound_names:
            result += '#include "%s%s.h"\n'%(gen_dir, self.cname)
        elif self.name in block_names:
            result += '#include "%s%s.h"\n'%(obj_dir, self.cname)
        else: assert(False) # bug

        # include referenced blocks
        used_blocks = []
        for y in self.members:
            if y.template in block_names and y.template != self.name:
                file_name = "%s%s.h"%(obj_dir, y.ctemplate)
                if file_name not in used_blocks:
                    used_blocks.append( file_name )
            if y.type in compound_names:
                subblock = compound_types[y.type]
                result += subblock.code_include_cpp(True, gen_dir, obj_dir)
        for file_name in used_blocks:
            result += '#include "%s"\n'%file_name

        return result

    # find member by name
    def find_member(self, name, inherit=False):
      for y in self.members:
        if y.name == name:
          return y
      return None
      
    # find first reference of name in class
    def find_first_ref(self, name):
      for y in self.members:
        if y.arr1 and y.arr1.lhs == name:
          return y
        elif y.arr2 and y.arr2.lhs == name:
          return y
      return None
      

class Block(Compound):
    def __init__(self, element):
        Compound.__init__(self, element)
        #the relative path to files in the gen folder
        self.gen_file_prefix = "../gen/"
        #the relative path to files in the obj folder
        self.obj_file_prefix = ""
        
        self.is_ancestor = (element.getAttribute('abstract') == "1")
        inherit = element.getAttribute('inherit')
        if inherit:
            self.inherit = block_types[inherit]
        else:
            self.inherit = None
        self.has_interface = (element.getElementsByTagName('interface') != [])

    def code_include_h(self):
        result = ""
        if self.inherit:
            result += '#include "%s.h"\n'%self.inherit.cname
        result += Compound.code_include_h(self)
        return result
    
    # find member by name
    def find_member(self, name, inherit=False):
      ret = Compound.find_member(self, name)
      if not ret and inherit and self.inherit:
        ret = self.inherit.find_member(name, inherit)
      return ret

    # find first reference of name in class
    def find_first_ref(self, name):
      ret = None
      if self.inherit:
        ret = self.inherit.find_first_ref(name)
      if not ret:
        ret = Compound.find_first_ref(self, name)
      return ret
      
#
# import elements into our code generating classes
#

doc = parse("nifxml/nif.xml")

for element in doc.getElementsByTagName('version'):
    x = Version(element)
    version_types[x.num] = x
    version_names.append(x.num)

for element in doc.getElementsByTagName('basic'):
    x = Basic(element)
    assert not basic_types.has_key(x.name)
    basic_types[x.name] = x
    basic_names.append(x.name)

for element in doc.getElementsByTagName('enum'):
    x = Enum(element)
    assert not enum_types.has_key(x.name)
    enum_types[x.name] = x
    enum_names.append(x.name)
    
for element in doc.getElementsByTagName("compound"):
    x = Compound(element)
    assert not compound_types.has_key(x.name)
    compound_types[x.name] = x
    compound_names.append(x.name)

for element in doc.getElementsByTagName("niobject"):
    x = Block(element)
    assert not block_types.has_key(x.name)
    block_types[x.name] = x
    block_names.append(x.name)
