/*
    cbp2make : Makefile generation tool for the Code::Blocks IDE
    Copyright (C) 2010-2026 Mirai Computing (mirai.computing@gmail.com)

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
#ifndef STL_CONFIG_H
#define STL_CONFIG_H
//------------------------------------------------------------------------------
#include "stlvariables.h"
//------------------------------------------------------------------------------

class CConfiguration
{
 protected:
  CVariable m_NullVariable;
  std::vector<CVariable *> m_Variables;
  CString m_DefinedPrefix;
 protected:
  bool ValidIndex(const int Index) const;
 public:
  virtual void Initialize(void) {};
  void Assign(const CConfiguration& Configuration);
  void Merge(CConfiguration& Configuration, const bool OverrideTypes = false);
  virtual void Clear(void);
  int GetCount(void) const;
  CString& DefinedPrefix(void) { return m_DefinedPrefix; }
  CString DefinedPrefix(void) const { return m_DefinedPrefix; }
  bool VarDefined(const CString& Name) const;
  void SetDefined(const CString& Name);
  void SetUndefined(const CString& Name);
  CVariable& Variable(const int Index);
  CVariable& VarNamed(const CString& Name);
  int VarIndex(const CString& Name) const;
  int InsertIntegerVariable(const CString& Name, const int Value=0);
  int InsertFloatVariable(const CString& Name, const double Value=0.0);
  int InsertBooleanVariable(const CString& Name, const bool Value=false);
  int InsertFlagVariable(const CString& Name, const bool Value=false);
  int InsertStringVariable(const CString& Name, const CString& Value="");
  int InsertCharVariable(const CString& Name, const char Value=char(0));
  int InsertVariable(const CVariable& Variable);
  CVariable* CloneVariable(const int Index) const;
  int CloneVariable(const CVariable& Variable, const CString& Name);
  int GetInteger(const CString& Name, const int Value = 0);
  double GetFloat(const CString& Name, const double Value = 0.0);
  bool GetBoolean(const CString& Name, const bool Value = false);
  bool GetFlag(const CString& Name, const bool Value = false);
  CString GetString(const CString& Name, const CString& Value = "");
  char GetChar(const CString& Name, const char Value = char(0));
  bool ReadInteger(const CString& Name, int& Value);
  bool ReadFloat(const CString& Name, double& Value);
  bool ReadBoolean(const CString& Name, bool& Value);
  bool ReadFlag(const CString& Name, bool& Value);
  bool ReadString(const CString& Name, CString& Value);
  bool ReadChar(const CString& Name, char& Value);
  void SetIntegerVariable(const CString& Name, const int Value);
  void SetFloatVariable(const CString& Name, const double Value);
  void SetBooleanVariable(const CString& Name, const bool Value);
  void SetFlagVariable(const CString& Name, const bool Value);
  void SetStringVariable(const CString& Name, const CString& Value);
  void SetCharVariable(const CString& Name, const char Value);
  void RemoveVariable(const int Index);
  void RemoveVariable(const CString& Name);
  void Print(std::ostream& out);
  void ProcessParameters(int argc, char* argv[]);
  bool LoadFromFile(const CString& FileName);
  bool SaveToFile(const CString& FileName);
 public:
  CConfiguration(void);
  CConfiguration(const CConfiguration& Configuration);
  virtual ~CConfiguration(void);
};

class CParameterString
{
 protected:
  int m_argc;
  char **m_argv;
  CString m_NullParameter;
  CStringList m_Parameters;
 public:
  void Clear();
  void Assign(const CParameterString& ParameterString);
  int argc(void) const { return m_argc; }
  char **argv(void) { return m_argv; }
  void SetParameters(int argc, char* argv[]);
  void SetParameters(const CString& Parameters);
  void SetParameters(const CParameterString& Parameters);
  void AddParameters(const CString& Parameters);
  void AddParameters(const CParameterString& Parameters);
  int GetCount(void) const { return m_Parameters.GetCount(); }
  CString Parameter(const int Index) const;
  virtual void Print(std::ostream& out) {};
 public:
  CParameterString(int argc, char* argv[]);
  CParameterString(const CParameterString& ParameterString);
  CParameterString(const CString& Parameters);
  CParameterString(void);
  virtual ~CParameterString(void);
};

class CParameterStringConfiguration: public CConfiguration
{
 protected:
  CString m_DefinedPrefix;
  CStringList m_Anonymous;
  bool m_CLI_Mode;
  bool m_StrictSyntax;
 public:
  CStringList Anonymous(void) const { return m_Anonymous; }
  CString& DefinedPrefix(void) { return m_DefinedPrefix; }
  bool& CLI_Mode(void) { return m_CLI_Mode; }
  bool& StrictSyntax(void) { return m_StrictSyntax; }
  bool VarDefined(const CString& Name);
  void SetDefined(const CString& Name);
  void SetUndefined(const CString& Name);
  bool ProcessParameters(const CParameterString& Parameters);
  bool ProcessParameters(const CString& Parameters);
 public:
  CParameterStringConfiguration(void);
  CParameterStringConfiguration(const CParameterStringConfiguration& Configuration);
  virtual ~CParameterStringConfiguration(void) {};
};

#endif
//------------------------------------------------------------------------------
