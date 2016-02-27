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
#include <iostream>
//------------------------------------------------------------------------------
#include "tinyxml.h"
#include "stlfutils.h"
#include "cbbuiltinvar.h"
#include "cbhelper.h"
//------------------------------------------------------------------------------

CBuiltinVariable::CBuiltinVariable(const hash_t ID, const CString& Macros, const CString& Value)
{
 Clear();
 m_ID = ID;
 ParseStr(Macros,',',m_Macros);
 m_Value = Value;
}

CBuiltinVariable::~CBuiltinVariable(void)
{
 Clear();
}

void CBuiltinVariable::Clear(void)
{
 m_ID = 0;
 m_Macros.Clear();
 m_Value.Clear();
}

void CBuiltinVariable::Show(void)
{
}

CString CBuiltinVariable::Convert(const CString& Value, const CStringList& Prefixes, const CStringList& Suffixes)
{
 CString result = Value;
 for (size_t i = 0, n = m_Macros.GetCount(); i < n; i++)
 {
  for (size_t j = 0, m = Prefixes.GetCount(); j < m; j++)
  {
   CString s = Prefixes.GetString(j)+m_Macros[i]+Suffixes.GetString(j);
   result = FindReplaceStr(result,s,m_Value);
  }
 }
 return result;
}

//------------------------------------------------------------------------------

CBuiltinVariableConfig::CBuiltinVariableConfig(void)
{
 Clear();
 InitializeVariables();
}

CBuiltinVariableConfig::~CBuiltinVariableConfig(void)
{
 Clear();
}

void CBuiltinVariableConfig::Clear(void)
{
 for (size_t i = 0; i < m_BuiltinVariables.size(); i++) delete m_BuiltinVariables[i];
 m_Prefixes.Clear();
 m_Suffixes.Clear();
}

void CBuiltinVariableConfig::Show(void)
{
 //
}

void CBuiltinVariableConfig::InitializeVariables()
{
 m_Prefixes.Insert("%");  m_Suffixes.Insert("%");
 m_Prefixes.Insert("$("); m_Suffixes.Insert(")");
 m_Prefixes.Insert("${"); m_Suffixes.Insert("}");
 m_Prefixes.Insert("$");  m_Suffixes.Insert("");
 // Workspace
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_WORKSPACE_FILENAME_ID,TPL_WORKSPACE_FILENAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_WORKSPACE_NAME_ID,TPL_WORKSPACE_NAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_WORKSPACE_DIR_ID,TPL_WORKSPACE_DIR));
 // Files and directories
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_PROJECT_FILENAME_ID,TPL_PROJECT_FILENAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_PROJECT_NAME_ID,TPL_PROJECT_NAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_PROJECT_DIR_ID,TPL_PROJECT_DIR));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_ACTIVE_EDITOR_FILENAME_ID,TPL_ACTIVE_EDITOR_FILENAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_ACTIVE_EDITOR_LINE_ID,TPL_ACTIVE_EDITOR_LINE));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_ACTIVE_EDITOR_COLUMN_ID,TPL_ACTIVE_EDITOR_COLUMN));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_ACTIVE_EDITOR_DIRNAME_ID,TPL_ACTIVE_EDITOR_DIRNAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_ACTIVE_EDITOR_STEM_ID,TPL_ACTIVE_EDITOR_STEM));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_ACTIVE_EDITOR_EXT_ID,TPL_ACTIVE_EDITOR_EXT));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_ALL_PROJECT_FILES_ID,TPL_ALL_PROJECT_FILES));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_MAKEFILE_ID,TPL_MAKEFILE));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_APP_PATH_ID,TPL_APP_PATH));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_DATA_PATH_ID,TPL_DATA_PATH));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_PLUGINS_ID,TPL_PLUGINS));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_COMPILER_DIR_ID,TPL_TARGET_COMPILER_DIR));
 // Build targets
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_FOOBAR_OUTPUT_FILE_ID,TPL_FOOBAR_OUTPUT_FILE));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_FOOBAR_OUTPUT_DIR_ID,TPL_FOOBAR_OUTPUT_DIR));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_FOOBAR_OUTPUT_BASENAME_ID,TPL_FOOBAR_OUTPUT_BASENAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_OUTPUT_DIR_ID,TPL_TARGET_OUTPUT_DIR));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_OBJECT_DIR_ID,TPL_TARGET_OBJECT_DIR));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_NAME_ID,TPL_TARGET_NAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_OUTPUT_FILE_ID,TPL_TARGET_OUTPUT_FILE));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_OUTPUT_BASENAME_ID,TPL_TARGET_OUTPUT_BASENAME));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_CC_ID,TPL_TARGET_CC));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_CPP_ID,TPL_TARGET_CPP));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_LD_ID,TPL_TARGET_LD));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TARGET_LIB_ID,TPL_TARGET_LIB));
 // Language and encoding
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_LANGUAGE_ID,TPL_LANGUAGE));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_ENCODING_ID,TPL_ENCODING));
 // Time and date
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TDAY_ID,TPL_TDAY));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TODAY_ID,TPL_TODAY));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_NOW_ID,TPL_NOW));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_NOW_L_ID,TPL_NOW_L));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_WEEKDAY_ID,TPL_WEEKDAY));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TDAY_UTC_ID,TPL_TDAY_UTC));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_TODAY_UTC_ID,TPL_TODAY_UTC));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_NOW_UTC_ID,TPL_NOW_UTC));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_NOW_L_UTC_ID,TPL_NOW_L_UTC));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_WEEKDAY_UTC_ID,TPL_WEEKDAY_UTC));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_DAYCOUNT_ID,TPL_DAYCOUNT));
 // Random values
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_COIN_ID,TPL_COIN));
 m_BuiltinVariables.push_back(new CBuiltinVariable(TPL_RANDOM_ID,TPL_RANDOM));
 //
 //m_BuiltinVariables.push_back(new CBuiltinVariable(,));
 //
}

CString CBuiltinVariableConfig::GetValue(const hash_t ID)
{
 for (size_t i = 0; i < m_BuiltinVariables.size(); i++)
 {
  CBuiltinVariable* v = m_BuiltinVariables.at(i);
  if (v->ID() == ID)
  {
   return v->Value();
  }
 }
 return "";
}

void CBuiltinVariableConfig::SetValue(const hash_t ID, const CString& Value)
{
 for (size_t i = 0; i < m_BuiltinVariables.size(); i++)
 {
  CBuiltinVariable* v = m_BuiltinVariables.at(i);
  if (v->ID() == ID)
  {
   v->Value() = Value;
  }
 }
}

CString CBuiltinVariableConfig::Convert(const CString& Value)
{
 CString result = Value;
 for (size_t i = 0; i < m_BuiltinVariables.size(); i++)
 {
  CBuiltinVariable* v = m_BuiltinVariables.at(i);
  result = v->Convert(result, m_Prefixes, m_Suffixes);
 }
 return result;
}

//------------------------------------------------------------------------------
