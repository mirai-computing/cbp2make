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
#include <cstdio>
#include <iostream>
//------------------------------------------------------------------------------
#include "stlstrings.h"
#include "stlconfig.h"
//------------------------------------------------------------------------------

CConfiguration::CConfiguration(void)
{
 Clear();
}

CConfiguration::CConfiguration(const CConfiguration& Configuration)
{
 Assign(Configuration);
}

CConfiguration::~CConfiguration(void)
{
 Clear();
}

void CConfiguration::Assign(const CConfiguration& Configuration)
{
 Clear();
 for (int i = 0, n = Configuration.GetCount(); i < n; i++)
 {
  m_Variables.push_back(CloneVariable(i));
 }
}

void CConfiguration::Merge(CConfiguration& Configuration, const bool OverrideTypes)
{
 for (int i = 0, n = Configuration.GetCount(); i < n; i++)
 {
  CVariable& w = Configuration.Variable(i);
  int j = VarIndex(w.GetName());
  if (j>=0) // variable exists in both symbol tables
  {
   CVariable& v = Variable(j);
   if (w.GetType()==v.GetType() || (!OverrideTypes && (w.GetType()!=v.GetType()))) // both variables are of the same type => update/replace
   {
    switch (v.GetType())
    {
     default: case CVariable::varNone: break;
     case CVariable::varInteger: { v.SetInteger(w.GetInteger()); break; }
     case CVariable::varFloat: { v.SetFloat(w.GetFloat()); break; }
     case CVariable::varBoolean: { v.SetBoolean(w.GetBoolean()); break; }
     case CVariable::varFlag: { v.SetBoolean(w.GetBoolean()); break; }
     case CVariable::varString: { v.SetString(w.GetString()); break; }
     case CVariable::varChar: { v.SetChar(w.GetChar()); break; }
    }
   }
   else // types are different, type override selected
   {
    RemoveVariable(j);
    m_Variables.insert(m_Variables.begin()+j,w.CreateInstance());
   }
   SetDefined(w.GetName()); // mark merged variables as defined
  }
  else m_Variables.push_back(Configuration.Variable(i).CreateInstance());
 }
}

void CConfiguration::Clear(void)
{
 for (size_t i = 0; i < m_Variables.size(); i++) delete m_Variables[i];
 m_Variables.clear();
 m_NullVariable.SetName("NULL");
 m_DefinedPrefix = "~";
}

int CConfiguration::GetCount(void) const
{
 return m_Variables.size();
}

bool CConfiguration::ValidIndex(const int Index) const
{
 return ((Index>=0)&&(Index<GetCount()));
}

bool CConfiguration::VarDefined(const CString& Name) const
{
 int index = VarIndex(DefinedPrefix()+Name);
 return (INVALID_INDEX!=index);
}

void CConfiguration::SetDefined(const CString& Name)
{
 int index = VarIndex(DefinedPrefix()+Name);
 if (INVALID_INDEX==index) InsertBooleanVariable(DefinedPrefix()+Name,true);
}

void CConfiguration::SetUndefined(const CString& Name)
{
 RemoveVariable(DefinedPrefix()+Name);
}

CVariable& CConfiguration::Variable(const int Index)
{
 if (!ValidIndex(Index)) return m_NullVariable;
 CVariable *result = (CVariable *)m_Variables[Index];
 if (NULL==result) return m_NullVariable; else return *result;
}

CVariable& CConfiguration::VarNamed(const CString& Name)
{
 return Variable(VarIndex(Name));
}

int CConfiguration::VarIndex(const CString& Name) const
{
 for (size_t i = 0; i < m_Variables.size(); i++)
 {
  CVariable *variable = m_Variables[i];
  if (variable->GetName()==Name) return i;
 }
 return INVALID_INDEX;
}

int CConfiguration::InsertIntegerVariable(const CString& Name, const int Value)
{
 m_Variables.push_back(new CIntegerVariable(Name,Value));
 return GetCount()-1;
}

int CConfiguration::InsertFloatVariable(const CString& Name, const double Value)
{
 m_Variables.push_back(new CFloatVariable(Name,Value));
 return GetCount()-1;
}

int CConfiguration::InsertBooleanVariable(const CString& Name, const bool Value)
{
 m_Variables.push_back(new CBooleanVariable(Name,Value));
 return GetCount()-1;
}

int CConfiguration::InsertFlagVariable(const CString& Name, const bool Value)
{
 m_Variables.push_back(new CFlagVariable(Name,Value));
 return GetCount()-1;
}

int CConfiguration::InsertStringVariable(const CString& Name, const CString& Value)
{
 m_Variables.push_back(new CStringVariable(Name,Value));
 return GetCount()-1;
}

int CConfiguration::InsertCharVariable(const CString& Name, const char Value)
{
 m_Variables.push_back(new CCharVariable(Name,Value));
 return GetCount()-1;
}

int CConfiguration::InsertVariable(const CVariable& Variable)
{
 m_Variables.push_back(Variable.CreateInstance());
 return GetCount()-1;
}

CVariable* CConfiguration::CloneVariable(const int Index) const
{
 if (ValidIndex(Index))
 {
  return m_Variables.at(Index)->CreateInstance();
 }
 return m_NullVariable.CreateInstance();
}

int CConfiguration::CloneVariable(const CVariable& Variable, const CString& Name)
{
 CVariable *v = Variable.CreateInstance();
 v->SetName(Name);
 m_Variables.push_back(v);
 return GetCount()-1;
}

int CConfiguration::GetInteger(const CString& Name, const int Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index)) return Variable(index).GetInteger();
 else return Value;
}

double CConfiguration::GetFloat(const CString& Name, const double Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index)) return Variable(index).GetFloat();
 else return Value;
}

bool CConfiguration::GetBoolean(const CString& Name, const bool Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index)) return Variable(index).GetBoolean();
 else return Value;
}

bool CConfiguration::GetFlag(const CString& Name, const bool Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index)) return true;
 else return Value;
}

CString CConfiguration::GetString(const CString& Name, const CString& Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index)) return Variable(index).GetString();
 else return Value;
}

char CConfiguration::GetChar(const CString& Name, const char Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index)) return Variable(index).GetChar();
 else return Value;
}

bool CConfiguration::ReadInteger(const CString& Name, int& Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  Value = Variable(index).GetInteger();
  return true;
 }
 return false;
}

bool CConfiguration::ReadFloat(const CString& Name, double& Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  Value = Variable(index).GetFloat();
  return true;
 }
 return false;
}

bool CConfiguration::ReadBoolean(const CString& Name, bool& Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  Value = Variable(index).GetBoolean();
  return true;
 }
 return false;
}

bool CConfiguration::ReadFlag(const CString& Name, bool& Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  Value = Variable(index).GetBoolean();
  return true;
 }
 return false;
}

bool CConfiguration::ReadString(const CString& Name, CString& Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  Value = Variable(index).GetString();
  return true;
 }
 return false;
}

bool CConfiguration::ReadChar(const CString& Name, char& Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  Value = Variable(index).GetChar();
  return true;
 }
 return false;
}

void CConfiguration::RemoveVariable(const int Index)
{
 if (ValidIndex(Index))
 {
  CVariable *variable = m_Variables[Index];
  m_Variables.erase(m_Variables.begin()+Index);
  delete variable;
 }
}

void CConfiguration::RemoveVariable(const CString& Name)
{
 RemoveVariable(VarIndex(Name));
}

void CConfiguration::SetIntegerVariable(const CString& Name, const int Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  CVariable *variable = m_Variables[index];
  variable->SetInteger(Value);
 }
 else
 {
  InsertIntegerVariable(Name,Value);
 }
}

void CConfiguration::SetFloatVariable(const CString& Name, const double Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  CVariable *variable = m_Variables[index];
  variable->SetFloat(Value);
 }
 else
 {
  InsertFloatVariable(Name,Value);
 }
}

void CConfiguration::SetBooleanVariable(const CString& Name, const bool Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  CVariable *variable = m_Variables[index];
  variable->SetBoolean(Value);
 }
 else
 {
  InsertBooleanVariable(Name,Value);
 }
}

void CConfiguration::SetFlagVariable(const CString& Name, const bool Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  if (!Value)
  {
   RemoveVariable(index);
  }
 }
 else
 {
  if (Value)
  {
   InsertFlagVariable(Name,true);
  }
 }
}

void CConfiguration::SetStringVariable(const CString& Name, const CString& Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  CVariable *variable = m_Variables[index];
  variable->SetString(Value);
 }
 else
 {
  InsertStringVariable(Name,Value);
 }
}

void CConfiguration::SetCharVariable(const CString& Name, const char Value)
{
 int index = VarIndex(Name);
 if (ValidIndex(index))
 {
  CVariable *variable = m_Variables[index];
  variable->SetChar(Value);
 }
 else
 {
  InsertCharVariable(Name,Value);
 }
}

void CConfiguration::Print(std::ostream& out)
{
 for (size_t i = 0; i < m_Variables.size(); i++)
 {
  CVariable *variable = m_Variables[i];
  out<<variable->GetTypeName().GetCString()<<" "<<variable->GetName().GetCString()<<"=";
  if (CVariable::varString == variable->GetType())
  {
   out<<"\""<<variable->GetString().GetCString()<<"\";"<<std::endl;
  }
  else if (CVariable::varChar == variable->GetType())
  {
   out<<"'"<<variable->GetString().GetCString()<<"';"<<std::endl;
  }
  else
  {
   out<<variable->GetString().GetCString()<<";"<<std::endl;
 }}
}

bool CConfiguration::LoadFromFile(const CString& FileName)
{
 CStringList configuration, sub_strings;
 CStringListIterator iterator(&configuration);
 bool result = configuration.LoadFromFile(FileName);
 //
 for (int i = 0; i < configuration.GetCount(); i++)
 {
  ParseStr(configuration[i],"=;",sub_strings);
  CVariable variable = VarNamed(sub_strings[0]);
  if (variable.GetType()==CVariable::varChar)
  {
   CStringList sub_strings2;
   ParseStr(sub_strings[1],"''",sub_strings2);
   variable.SetString(sub_strings2[1]);
  }
  else if (variable.GetType()==CVariable::varString)
  {
   CStringList sub_strings2;
   ParseStr(sub_strings[1],"\"\"",sub_strings2);
   variable.SetString(sub_strings2[1]);
  }
  sub_strings.Clear();
 }
 return result;
}

bool CConfiguration::SaveToFile(const CString& FileName)
{
 FILE *stream = fopen(FileName.GetCString(),"wt");
 if (NULL==stream) return false;
 for (size_t i = 0; i < m_Variables.size(); i++)
 {
  CVariable *variable = m_Variables[i];
  CString str = variable->GetName()+"=";
  if (variable->GetType()==CVariable::varString)
  {
   str+="\""+variable->GetString()+"\"";
  }
  else if (variable->GetType()==CVariable::varChar)
  {
   str+="'"+variable->GetString()+"'";
  }
  else
  {
   str+=variable->GetString();
  }
  str.Append(';').AppendEOL();
  fwrite(str.GetCString(),str.GetLength(),1,stream);
 }
 fclose(stream);
 return true;
}

//------------------------------------------------------------------------------

CParameterString::CParameterString(void)
{
 m_argc = 0; m_argv = 0;
}

CParameterString::CParameterString(int argc, char* argv[])
{
 SetParameters(argc,argv);
}

CParameterString::CParameterString(const CParameterString& ParameterString)
{
 Assign(ParameterString);
}

CParameterString::CParameterString(const CString& Parameters)
{
 SetParameters(Parameters);
}

CParameterString::~CParameterString(void)
{
 //
}

void CParameterString::Clear()
{
 m_NullParameter.Clear();
 m_Parameters.Clear();
}

void CParameterString::Assign(const CParameterString& ParameterString)
{
 m_argc = ParameterString.m_argc;
 m_argv = ParameterString.m_argv;
 m_NullParameter = ParameterString.m_NullParameter;
 m_Parameters = ParameterString.m_Parameters;
}

void CParameterString::SetParameters(int argc, char* argv[])
{
 m_argc = argc; m_argv = argv;
 m_Parameters.Clear();
 for (int i = 0; i < argc; i++) m_Parameters.Insert(CString(argv[i]));
}

void CParameterString::SetParameters(const CString& Parameters)
{
 m_Parameters.Clear();
 ParseStrWithQuotes(Parameters,' ',m_Parameters);
}

void CParameterString::SetParameters(const CParameterString& Parameters)
{
 m_Parameters = Parameters.m_Parameters;
}

void CParameterString::AddParameters(const CString& Parameters)
{
 CStringList params;
 ParseStrWithQuotes(Parameters,' ',params);
 m_Parameters.Insert(params);
}

void CParameterString::AddParameters(const CParameterString& Parameters)
{
 m_Parameters.Insert(Parameters.m_Parameters);
}

CString CParameterString::Parameter(const int Index) const
{
 return m_Parameters[Index];
}

//------------------------------------------------------------------------------

CParameterStringConfiguration::CParameterStringConfiguration(void)
{
 m_DefinedPrefix = '~';
 m_CLI_Mode = true;
 m_StrictSyntax = false;
};

CParameterStringConfiguration::CParameterStringConfiguration(const CParameterStringConfiguration& Configuration)
:CConfiguration(Configuration)
{
 //
}


bool CParameterStringConfiguration::VarDefined(const CString& Name)
{
 int index = VarIndex(DefinedPrefix()+Name);
 return (INVALID_INDEX!=index);
}

void CParameterStringConfiguration::SetDefined(const CString& Name)
{
 int index = VarIndex(DefinedPrefix()+Name);
 if (INVALID_INDEX==index) InsertFlagVariable(DefinedPrefix()+Name,true);
}

void CParameterStringConfiguration::SetUndefined(const CString& Name)
{
 RemoveVariable(DefinedPrefix()+Name);
}

bool CParameterStringConfiguration::ProcessParameters(const CParameterString& Parameters)
{
 bool result = true;
 m_Anonymous.Clear();
 // parameter index : 1 = good for application command line
 //                 : 0 = good for other cases (scripting etc.)
 int j = (int)m_CLI_Mode; // skip argv[0] name of executable in CLI mode
 while (j < Parameters.GetCount())
 {
  bool f_recognized = false;
  CString parameter = Parameters.Parameter(j);
  for (size_t i = 0; i < m_Variables.size(); i++)
  {
   CVariable& variable = Variable(i);
   if (variable.GetName()==parameter)
   {
    f_recognized = true;
    if (variable.GetType()==CVariable::varFlag) variable.SetBoolean(true);
    else
    {
     CString value = Parameters.Parameter(++j);
     if (m_StrictSyntax)
     {
      if (ValidIndex(VarIndex(value)))
      {
       std::cerr<<"Missing parameter value: "<<parameter.GetCString()<<" = '"
       <<value.GetCString()<<"' at ["<<j<<"], but '"<<value.GetCString()
       <<"' is a declared parameter itself."<<std::endl;
       j--; // walk back one step to read next parameter properly
       result = false;
      }
     }
     variable.SetString(value);
    }
    m_Variables.push_back(new CFlagVariable(m_DefinedPrefix+variable.GetName(),true));
    break;
   }
  }
  if (!f_recognized)
  {
   if (m_StrictSyntax)
   {
    std::cerr<<"Undeclared parameter or garbage: '"<<parameter.GetCString()
    <<"' at ["<<j<<"]."<<std::endl;
    result = false;
   }
   else
   {
    m_Anonymous.Insert(parameter);
   }
  }
  j++;
 }
 return result;
}

bool CParameterStringConfiguration::ProcessParameters(const CString& Parameters)
{
 CParameterString parameterString(Parameters);
 return ProcessParameters(parameterString);
}

//------------------------------------------------------------------------------
