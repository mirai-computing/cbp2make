/*
    cbp2make : Makefile generation tool for the Code::Blocks IDE
    Copyright (C) 2010-2016 Mirai Computing (mirai.computing@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//------------------------------------------------------------------------------
#ifndef CBBUILTINVAR_H
#define CBBUILTINVAR_H
//------------------------------------------------------------------------------
#include "stlstrings.h"
#include "stlconfig.h"
#include "stringhash.h"
//------------------------------------------------------------------------------

// Constants for known built-in variables

// While a built-in variable could be defined by several macros,
// its hash code identifies the variable as whole

// Workspace

static const CString TPL_WORKSPACE_FILENAME =
 "WORKSPACE_FILENAME,WORKSPACE_FILE_NAME,WORKSPACEFILE,WORKSPACEFILENAME";
static const hash_t TPL_WORKSPACE_FILENAME_ID =
 sdbm_hash((unsigned char *)TPL_WORKSPACE_FILENAME.GetCString(),TPL_WORKSPACE_FILENAME.GetLength());

static const CString TPL_WORKSPACE_NAME = "WORKSPACENAME,WORKSPACE_NAME";
static const hash_t TPL_WORKSPACE_NAME_ID =
 sdbm_hash((unsigned char *)TPL_WORKSPACE_NAME.GetCString(),TPL_WORKSPACE_NAME.GetLength());

static const CString TPL_WORKSPACE_DIR =
 "WORKSPACE_DIR,WORKSPACE_DIRECTORY,WORKSPACEDIR,WORKSPACEDIRECTORY";
static const hash_t TPL_WORKSPACE_DIR_ID =
 sdbm_hash((unsigned char *)TPL_WORKSPACE_DIR.GetCString(),TPL_WORKSPACE_DIR.GetLength());

// Files and directories

static const CString TPL_PROJECT_FILENAME = "PROJECT_FILENAME,PROJECT_FILE,PROJECTFILE";
static const hash_t TPL_PROJECT_FILENAME_ID =
 sdbm_hash((unsigned char *)TPL_PROJECT_FILENAME.GetCString(),TPL_PROJECT_FILENAME.GetLength());

static const CString TPL_PROJECT_NAME = "PROJECT_NAME";
static const hash_t TPL_PROJECT_NAME_ID =
 sdbm_hash((unsigned char *)TPL_PROJECT_NAME.GetCString(),TPL_PROJECT_NAME.GetLength());

static const CString TPL_PROJECT_DIR =
 "PROJECT_DIR,PROJECTDIR,PROJECT_DIRECTORY";
static const hash_t TPL_PROJECT_DIR_ID =
 sdbm_hash((unsigned char *)TPL_PROJECT_DIR.GetCString(),TPL_PROJECT_DIR.GetLength());

static const CString TPL_ACTIVE_EDITOR_FILENAME = "ACTIVE_EDITOR_FILENAME";
static const hash_t TPL_ACTIVE_EDITOR_FILENAME_ID =
 sdbm_hash((unsigned char *)TPL_ACTIVE_EDITOR_FILENAME.GetCString(),TPL_ACTIVE_EDITOR_FILENAME.GetLength());

static const CString TPL_ACTIVE_EDITOR_LINE = "ACTIVE_EDITOR_LINE";
static const hash_t TPL_ACTIVE_EDITOR_LINE_ID =
 sdbm_hash((unsigned char *)TPL_ACTIVE_EDITOR_LINE.GetCString(),TPL_ACTIVE_EDITOR_LINE.GetLength());

static const CString TPL_ACTIVE_EDITOR_COLUMN = "ACTIVE_EDITOR_COLUMN";
static const hash_t TPL_ACTIVE_EDITOR_COLUMN_ID =
 sdbm_hash((unsigned char *)TPL_ACTIVE_EDITOR_COLUMN.GetCString(),TPL_ACTIVE_EDITOR_COLUMN.GetLength());

static const CString TPL_ACTIVE_EDITOR_DIRNAME = "ACTIVE_EDITOR_DIRNAME";
static const hash_t TPL_ACTIVE_EDITOR_DIRNAME_ID =
 sdbm_hash((unsigned char *)TPL_ACTIVE_EDITOR_DIRNAME.GetCString(),TPL_ACTIVE_EDITOR_DIRNAME.GetLength());

static const CString TPL_ACTIVE_EDITOR_STEM = "ACTIVE_EDITOR_STEM";
static const hash_t TPL_ACTIVE_EDITOR_STEM_ID =
 sdbm_hash((unsigned char *)TPL_ACTIVE_EDITOR_STEM.GetCString(),TPL_ACTIVE_EDITOR_STEM.GetLength());

static const CString TPL_ACTIVE_EDITOR_EXT = "ACTIVE_EDITOR_EXT";
static const hash_t TPL_ACTIVE_EDITOR_EXT_ID =
 sdbm_hash((unsigned char *)TPL_ACTIVE_EDITOR_EXT.GetCString(),TPL_ACTIVE_EDITOR_EXT.GetLength());

static const CString TPL_ALL_PROJECT_FILES = "ALL_PROJECT_FILES";
static const hash_t TPL_ALL_PROJECT_FILES_ID =
 sdbm_hash((unsigned char *)TPL_ALL_PROJECT_FILES.GetCString(),TPL_ALL_PROJECT_FILES.GetLength());

static const CString TPL_MAKEFILE = "MAKEFILE";
static const hash_t TPL_MAKEFILE_ID =
 sdbm_hash((unsigned char *)TPL_MAKEFILE.GetCString(),TPL_MAKEFILE.GetLength());

static const CString TPL_APP_PATH =
 "CODEBLOCKS,APP_PATH,APPPATH,APP-PATH";
static const hash_t TPL_APP_PATH_ID =
 sdbm_hash((unsigned char *)TPL_APP_PATH.GetCString(),TPL_APP_PATH.GetLength());

static const CString TPL_DATA_PATH =
 "DATAPATH,DATA_PATH,DATA-PATH";
static const hash_t TPL_DATA_PATH_ID =
 sdbm_hash((unsigned char *)TPL_DATA_PATH.GetCString(),TPL_DATA_PATH.GetLength());

static const CString TPL_PLUGINS = "PLUGINS";
static const hash_t TPL_PLUGINS_ID =
 sdbm_hash((unsigned char *)TPL_PLUGINS.GetCString(),TPL_PLUGINS.GetLength());

static const CString TPL_TARGET_COMPILER_DIR = "TARGET_COMPILER_DIR";
static const hash_t TPL_TARGET_COMPILER_DIR_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_COMPILER_DIR.GetCString(),TPL_TARGET_COMPILER_DIR.GetLength());

// Build targets

static const CString TPL_FOOBAR_OUTPUT_FILE = "FOOBAR_OUTPUT_FILE";
static const hash_t TPL_FOOBAR_OUTPUT_FILE_ID =
 sdbm_hash((unsigned char *)TPL_FOOBAR_OUTPUT_FILE.GetCString(),TPL_FOOBAR_OUTPUT_FILE.GetLength());

static const CString TPL_FOOBAR_OUTPUT_DIR = "FOOBAR_OUTPUT_DIR";
static const hash_t TPL_FOOBAR_OUTPUT_DIR_ID =
 sdbm_hash((unsigned char *)TPL_FOOBAR_OUTPUT_DIR.GetCString(),TPL_FOOBAR_OUTPUT_DIR.GetLength());

static const CString TPL_FOOBAR_OUTPUT_BASENAME = "FOOBAR_OUTPUT_BASENAME";
static const hash_t TPL_FOOBAR_OUTPUT_BASENAME_ID =
 sdbm_hash((unsigned char *)TPL_FOOBAR_OUTPUT_BASENAME.GetCString(),TPL_FOOBAR_OUTPUT_BASENAME.GetLength());

static const CString TPL_TARGET_OUTPUT_DIR = "TARGET_OUTPUT_DIR";
static const hash_t TPL_TARGET_OUTPUT_DIR_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_OUTPUT_DIR.GetCString(),TPL_TARGET_OUTPUT_DIR.GetLength());

static const CString TPL_TARGET_OBJECT_DIR = "TARGET_OBJECT_DIR";
static const hash_t TPL_TARGET_OBJECT_DIR_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_OBJECT_DIR.GetCString(),TPL_TARGET_OBJECT_DIR.GetLength());

static const CString TPL_TARGET_NAME = "TARGET_NAME";
static const hash_t TPL_TARGET_NAME_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_NAME.GetCString(),TPL_TARGET_NAME.GetLength());

static const CString TPL_TARGET_OUTPUT_FILE = "TARGET_OUTPUT_FILE";
static const hash_t TPL_TARGET_OUTPUT_FILE_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_OUTPUT_FILE.GetCString(),TPL_TARGET_OUTPUT_FILE.GetLength());

static const CString TPL_TARGET_OUTPUT_BASENAME = "TARGET_OUTPUT_BASENAME";
static const hash_t TPL_TARGET_OUTPUT_BASENAME_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_OUTPUT_BASENAME.GetCString(),TPL_TARGET_OUTPUT_BASENAME.GetLength());

static const CString TPL_TARGET_CC = "TARGET_CC";
static const hash_t TPL_TARGET_CC_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_CC.GetCString(),TPL_TARGET_CC.GetLength());

static const CString TPL_TARGET_CPP = "TARGET_CPP";
static const hash_t TPL_TARGET_CPP_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_CPP.GetCString(),TPL_TARGET_CPP.GetLength());

static const CString TPL_TARGET_LD = "TARGET_LD";
static const hash_t TPL_TARGET_LD_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_LD.GetCString(),TPL_TARGET_LD.GetLength());

static const CString TPL_TARGET_LIB = "TARGET_LIB";
static const hash_t TPL_TARGET_LIB_ID =
 sdbm_hash((unsigned char *)TPL_TARGET_LIB.GetCString(),TPL_TARGET_LIB.GetLength());

// Language and encoding

static const CString TPL_LANGUAGE = "LANGUAGE";
static const hash_t TPL_LANGUAGE_ID =
 sdbm_hash((unsigned char *)TPL_LANGUAGE.GetCString(),TPL_LANGUAGE.GetLength());

static const CString TPL_ENCODING = "ENCODING";
static const hash_t TPL_ENCODING_ID =
 sdbm_hash((unsigned char *)TPL_ENCODING.GetCString(),TPL_ENCODING.GetLength());

// Time and date

static const CString TPL_TDAY = "TDAY";
static const hash_t TPL_TDAY_ID =
 sdbm_hash((unsigned char *)TPL_TDAY.GetCString(),TPL_TDAY.GetLength());

static const CString TPL_TODAY = "TODAY";
static const hash_t TPL_TODAY_ID =
 sdbm_hash((unsigned char *)TPL_TODAY.GetCString(),TPL_TODAY.GetLength());

static const CString TPL_NOW = "NOW";
static const hash_t TPL_NOW_ID =
 sdbm_hash((unsigned char *)TPL_NOW.GetCString(),TPL_NOW.GetLength());

static const CString TPL_NOW_L = "NOW_L";
static const hash_t TPL_NOW_L_ID =
 sdbm_hash((unsigned char *)TPL_NOW_L.GetCString(),TPL_NOW_L.GetLength());

static const CString TPL_WEEKDAY = "WEEKDAY";
static const hash_t TPL_WEEKDAY_ID =
 sdbm_hash((unsigned char *)TPL_WEEKDAY.GetCString(),TPL_WEEKDAY.GetLength());

static const CString TPL_TDAY_UTC = "TDAY_UTC";
static const hash_t TPL_TDAY_UTC_ID =
 sdbm_hash((unsigned char *)TPL_TDAY_UTC.GetCString(),TPL_TDAY_UTC.GetLength());

static const CString TPL_TODAY_UTC = "TODAY_UTC";
static const hash_t TPL_TODAY_UTC_ID =
 sdbm_hash((unsigned char *)TPL_TODAY_UTC.GetCString(),TPL_TODAY_UTC.GetLength());

static const CString TPL_NOW_UTC = "NOW_UTC";
static const hash_t TPL_NOW_UTC_ID =
 sdbm_hash((unsigned char *)TPL_NOW_UTC.GetCString(),TPL_NOW_UTC.GetLength());

static const CString TPL_NOW_L_UTC = "NOW_L_UTC";
static const hash_t TPL_NOW_L_UTC_ID =
 sdbm_hash((unsigned char *)TPL_NOW_L_UTC.GetCString(),TPL_NOW_L_UTC.GetLength());

static const CString TPL_WEEKDAY_UTC = "WEEKDAY_UTC";
static const hash_t TPL_WEEKDAY_UTC_ID =
 sdbm_hash((unsigned char *)TPL_WEEKDAY_UTC.GetCString(),TPL_WEEKDAY_UTC.GetLength());

static const CString TPL_DAYCOUNT = "DAYCOUNT";
static const hash_t TPL_DAYCOUNT_ID =
 sdbm_hash((unsigned char *)TPL_DAYCOUNT.GetCString(),TPL_DAYCOUNT.GetLength());

// Random values

static const CString TPL_COIN = "COIN";
static const hash_t TPL_COIN_ID =
 sdbm_hash((unsigned char *)TPL_COIN.GetCString(),TPL_COIN.GetLength());

static const CString TPL_RANDOM = "RANDOM";
static const hash_t TPL_RANDOM_ID =
 sdbm_hash((unsigned char *)TPL_RANDOM.GetCString(),TPL_RANDOM.GetLength());

/*
static const CString TPL_ =
 "";
static const hash_t TPL_ =
 sdbm_hash((unsigned char *)TPL_.GetCString(),TPL_.GetLength());
*/

/*

Code::Blocks workspace

$(WORKSPACE_FILENAME), $(WORKSPACE_FILE_NAME), $(WORKSPACEFILE), $(WORKSPACEFILENAME)
The filename of the current workspace project (.workspace).

$(WORKSPACENAME), $(WORKSPACE_NAME)
The name of the workspace that is displayed in the tab Projects of the Management panel.

$(WORKSPACE_DIR), $(WORKSPACE_DIRECTORY), $(WORKSPACEDIR), $(WORKSPACEDIRECTORY)
The location of the workspace directory.

 Files and directories

$(PROJECT_FILENAME), $(PROJECT_FILE), $(PROJECTFILE)
The filename of the currently compiling project.

$(PROJECT_NAME)
The name of the currently compiling project.

$(PROJECT_DIR), $(PROJECTDIR), $(PROJECT_DIRECTORY)
The common top-level directory of the currently compiling project.

$(ACTIVE_EDITOR_FILENAME)
The filename of the file opened in the currently active editor.

$(ACTIVE_EDITOR_LINE)
Return the current line in the active editor.

$(ACTIVE_EDITOR_COLUMN)
Return the column of the current line in the active editor.

$(ACTIVE_EDITOR_DIRNAME)
Currently active file's containing directory (relative to the common top level path)

$(ACTIVE_EDITOR_STEM)
Currently active file's base name (without extension).

$(ACTIVE_EDITOR_EXT)
Currently active file's extension.

$(ALL_PROJECT_FILES)
A string containing the names of all files in the current project.

$(MAKEFILE)
The filename of the makefile.

$(CODEBLOCKS), $(APP_PATH), $(APPPATH), $(APP-PATH)
The path to the currently running instance of Code::Blocks

$(DATAPATH), $(DATA_PATH), $(DATA-PATH)
The 'shared' directory of the currently running instance of Code::Blocks

$(PLUGINS)
The 'plugins' directory of the currently running instance of Code::Blocks

$(TARGET_COMPILER_DIR)
The compiler installation directory so-called master path.

 Build targets

$(FOOBAR_OUTPUT_FILE)
A specific target's output file.

$(FOOBAR_OUTPUT_DIR)
A specific target's output directory.

$(FOOBAR_OUTPUT_BASENAME)
A specific target's output file's base name (no path, no extension).

$(TARGET_OUTPUT_DIR)
The current target's output directory.

$(TARGET_OBJECT_DIR)
The current target's object directory.

$(TARGET_NAME)
The current target's name.

$(TARGET_OUTPUT_FILE)
The current target's output file.

$(TARGET_OUTPUT_BASENAME)
The current target's output file's base name (no path, no extension).

$(TARGET_CC), $(TARGET_CPP), $(TARGET_LD), $(TARGET_LIB)
The current target's build tool executable (compiler, linker, etc).
 Language and encoding

$(LANGUAGE)
The system language in human readable form.

$(ENCODING)
The character encoding in human readable form.
 Time and date

$(TDAY)
Current date in the form YYYYMMDD (for example 20051228)

$(TODAY)
Current date in the form YYYY-MM-DD (for example 2005-12-28)

$(NOW)
Timestamp in the form YYYY-MM-DD-hh.mm (for example 2005-12-28-07.15)

$(NOW_L)
Timestamp in the form YYYY-MM-DD-hh.mm.ss (for example 2005-12-28-07.15.45)

$(WEEKDAY)
Human-readable day of the week (for example "Wednesday")

$(TDAY_UTC), $(TODAY_UTC), $(NOW_UTC), $(NOW_L_UTC), $(WEEKDAY_UTC)
These are identical to the preceding types, but are expressed relative to UTC.

$(DAYCOUNT)
The number of the days passed since an arbitrarily chosen day zero (January 1, 2009). Useful as last component of a version/build number.
 Random values

$(COIN)
This variable tosses a virtual coin (once per invokation) and returns 0 or 1.

$(RANDOM)
A 16bit positive random number (0-65535)

*/
//class TiXmlElement;

class CBuiltinVariable
{
 private:
  hash_t m_ID;
  CStringList m_Macros;
  CString m_Value;
 public:
  hash_t ID(void) const { return m_ID; }
  CString& Value(void) { return m_Value; }
  CString Convert(const CString& Value, const CStringList& Prefixes, const CStringList& Suffixes);
  void Clear(void);
  void Show(void);
 public:
  explicit CBuiltinVariable(const hash_t ID, const CString& Macros, const CString& Value = "");
  ~CBuiltinVariable(void);
};

/*

Code::Blocks treats the following functionally identical character sequences
inside pre-build, post-build, or build steps as variables:

$VARIABLE
$(VARIABLE)
${VARIABLE}
%VARIABLE%

Variable names must consist of alphanumeric characters and are not case-sensitive.
Variables starting with a single hash sign (#) are interpreted as global compiler
variables. The names listed below are interpreted as builtin types.

Variables which are neither global user variables nor builtin types are replaced
with a value provided in the project file, or with an environment variable if the
latter should fail.

Per-target definitions have precedence over per-project definitions.

*/

class CBuiltinVariableConfig
{
 private:
  CStringList m_Prefixes;
  CStringList m_Suffixes;
  std::vector<CBuiltinVariable*> m_BuiltinVariables;
 protected:
  void InitializeVariables();
 public:
  CString GetValue(const hash_t ID);
  void SetValue(const hash_t ID, const CString& Value);
  CString Convert(const CString& Value);
  void Clear(void);
  void Show(void);
 public:
  CBuiltinVariableConfig(void);
  ~CBuiltinVariableConfig(void);
};

#endif
//------------------------------------------------------------------------------
