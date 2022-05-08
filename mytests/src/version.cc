/**								-*- C++ -*-
 ** \file version.cc
 ** \brief Common definitions.
 */

#include <authors.h>
#include <config.h>

/*-------------------.
| Program identity.  |
`-------------------*/

/** Name of this program.

Be sure to have something usable even before main is started,
in case some ctor of a static object need to issue an error
message.  */
const char* program_name = PACKAGE_NAME;

// Version string of this program.
const char* program_version = "tc (" PACKAGE_STRING ")\n"
                              "\n"
                              "\n" PACKAGE_SHORT_AUTHORS;

// Bug report address of this program.
const char* program_bug_address = PACKAGE_BUGREPORT;

/// Describe program and accepted arguments.
const char* program_doc = "Tiger Compiler, Copyright (C) 2004-2021  LRDE.";
const char* program_args_doc = "INPUT-FILE";
