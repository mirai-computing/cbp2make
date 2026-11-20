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
#include "stlvariables.h"
//------------------------------------------------------------------------------

CString CVariable::TypeName(const CVariable::VariableType VarType)
{
 switch (VarType)
 {
  default: case CVariable::varNone: return "none";
  case CVariable::varInteger: return "integer";
  case CVariable::varFloat: return "float";
  case CVariable::varBoolean: return "boolean";
  case CVariable::varFlag: return "flag";
  case CVariable::varString: return "string";
  case CVariable::varChar: return "char";
 }
 return "";
}

CVariable::VariableType CVariable::GetType(const CString& TypeName)
{
 for (int i=CVariable::varNone; i<=CVariable::varChar; i++)
 {
  if (CVariable::TypeName((CVariable::VariableType)i)==TypeName)
  {
   return (CVariable::VariableType)i;
  }
 }
 return CVariable::varNone;
}

CVariable::VariableType CVariable::GetType(void) const
{
 return CVariable::varNone;
}

CString CVariable::GetTypeName(void) const
{
 return "none";
}

CString& CVariable::GetName(void)
{
 return m_Name;
}

void CVariable::SetName(const CString& Name)
{
 m_Name = Name;
}

double CVariable::GetFloat(void) const
{
 return 0.0;
}

void CVariable::SetFloat(const double Value)
{
 // do nothing //
}

int CVariable::GetInteger(void) const
{
 return 0;
}

void CVariable::SetInteger(const int Value)
{
 // do nothing //
}

bool CVariable::GetBoolean(void) const
{
 return 0;
}

void CVariable::SetBoolean(const bool Value)
{
 // do nothing //
}

CString CVariable::GetString(void) const
{
 return CString();
}

void CVariable::SetString(const CString& Value)
{
 // do nothing //
}

char CVariable::GetChar(void) const
{
 return char(0);
}

void CVariable::SetChar(const char Value)
{
 // do nothing //
}

void CVariable::Print(std::ostream& out)
{
 out<<m_Name.GetCString()<<"="<<GetString().GetCString();
}

CVariable *CVariable::CreateInstance() const
{
 CVariable *variable = new CVariable(m_Name);
 return variable;
}

CVariable::CVariable(void)
{
 m_Name = "CVariable";
}

CVariable::CVariable(const CString& Name)
{
 m_Name = Name;
}

CVariable::~CVariable(void)
{
 // do nothing //
}

//------------------------------------------------------------------------------

CVariable::VariableType CIntegerVariable::GetType(void) const
{
 return CVariable::varInteger;
}

CString CIntegerVariable::GetTypeName(void) const
{
 return "int";
}

double CIntegerVariable::GetFloat(void) const
{
 return IntToFloat(m_Value);
}

void CIntegerVariable::SetFloat(const double Value)
{
 m_Value = FloatToInt(Value);
}

int CIntegerVariable::GetInteger(void) const
{
 return m_Value;
}

void CIntegerVariable::SetInteger(const int Value)
{
 m_Value = Value;
}

bool CIntegerVariable::GetBoolean(void) const
{
 return IntToBool(m_Value);
}

void CIntegerVariable::SetBoolean(const bool Value)
{
 m_Value = BoolToInt(Value);
}

CString CIntegerVariable::GetString(void) const
{
 return IntToStr(m_Value);
}

void CIntegerVariable::SetString(const CString& Value)
{
 m_Value = StringToInteger(Value);
}

char CIntegerVariable::GetChar(void) const
{
 return IntToChar(m_Value);
}

void CIntegerVariable::SetChar(const char Value)
{
 m_Value = CharToInt(Value);
}

CVariable *CIntegerVariable::CreateInstance() const
{
 CIntegerVariable *variable = new CIntegerVariable(m_Name);
 variable->SetInteger(m_Value);
 return variable;
}

int CIntegerVariable::operator=(const CIntegerVariable& Variable)
{
 return Variable.GetInteger();
}

CIntegerVariable& CIntegerVariable::operator =(const double Value)
{
 SetFloat(Value);
 return *this;
}

CIntegerVariable& CIntegerVariable::operator =(const int Value)
{
 SetInteger(Value);
 return *this;
}

CIntegerVariable& CIntegerVariable::operator =(const bool Value)
{
 SetBoolean(Value);
 return *this;
}

CIntegerVariable& CIntegerVariable::operator =(const CString& Value)
{
 SetString(Value);
 return *this;
}

CIntegerVariable& CIntegerVariable::operator =(const char Value)
{
 SetChar(Value);
 return *this;
}

CIntegerVariable::CIntegerVariable(const CString& Name,const int Value)
:CVariable(Name)
{
 m_Value=Value;
}

//------------------------------------------------------------------------------

CVariable::VariableType CFloatVariable::GetType(void) const
{
 return CVariable::varFloat;
}

CString CFloatVariable::GetTypeName(void) const
{
 return "float";
}

double CFloatVariable::GetFloat(void) const
{
 return m_Value;
}

void CFloatVariable::SetFloat(const double Value)
{
 m_Value=Value;
}

int CFloatVariable::GetInteger(void) const
{
 return FloatToInt(m_Value);
}

void CFloatVariable::SetInteger(const int Value)
{
 m_Value = IntToFloat(Value);
}

bool CFloatVariable::GetBoolean(void) const
{
 return FloatToBool(m_Value);
}

void CFloatVariable::SetBoolean(const bool Value)
{
 m_Value = BoolToFloat(Value);
}

CString CFloatVariable::GetString(void) const
{
 return FloatToStr(m_Value);
}

void CFloatVariable::SetString(const CString& Value)
{
 m_Value=StringToFloat(Value);
}

char CFloatVariable::GetChar(void) const
{
 return FloatToChar(m_Value);
}

void CFloatVariable::SetChar(const char Value)
{
 m_Value = CharToFloat(Value);
}

CVariable *CFloatVariable::CreateInstance() const
{
 CFloatVariable *variable = new CFloatVariable(m_Name);
 variable->SetFloat(m_Value);
 return variable;
}

double CFloatVariable::operator=(const CFloatVariable& Variable)
{
 return Variable.GetFloat();
}

CFloatVariable& CFloatVariable::operator =(const double Value)
{
 SetFloat(Value);
 return *this;
}

CFloatVariable& CFloatVariable::operator =(const int Value)
{
 SetInteger(Value);
 return *this;
}

CFloatVariable& CFloatVariable::operator =(const bool Value)
{
 SetBoolean(Value);
 return *this;
}

CFloatVariable& CFloatVariable::operator =(const CString& Value)
{
 SetString(Value);
 return *this;
}

CFloatVariable& CFloatVariable::operator =(const char Value)
{
 SetChar(Value);
 return *this;
}

CFloatVariable::CFloatVariable(const CString& Name,const double Value)
:CVariable(Name)
{
 m_Value = Value;
}

//------------------------------------------------------------------------------

CVariable::VariableType CBooleanVariable::GetType(void) const
{
 return CVariable::varBoolean;
}

CString CBooleanVariable::GetTypeName(void) const
{
 return "bool";
}

double CBooleanVariable::GetFloat(void) const
{
 return BoolToFloat(m_Value);
}

void CBooleanVariable::SetFloat(const double Value)
{
 m_Value = FloatToBool(Value);
}

int CBooleanVariable::GetInteger(void) const
{
 return BoolToInt(m_Value);
}

void CBooleanVariable::SetInteger(const int Value)
{
 m_Value = IntToBool(Value);
}

bool CBooleanVariable::GetBoolean(void) const
{
 return m_Value;
}

void CBooleanVariable::SetBoolean(const bool Value)
{
 m_Value = Value;
}

CString CBooleanVariable::GetString(void) const
{
 return BoolToStr(m_Value);
}

void CBooleanVariable::SetString(const CString& Value)
{
 m_Value = StringToBoolean(Value);
}

char CBooleanVariable::GetChar(void) const
{
 return BoolToChar(m_Value);
}

void CBooleanVariable::SetChar(const char Value)
{
 m_Value = CharToBool(Value);
}

CVariable *CBooleanVariable::CreateInstance() const
{
 CBooleanVariable *variable = new CBooleanVariable(m_Name);
 variable->SetBoolean(m_Value);
 return variable;
}

bool CBooleanVariable::operator=(const CBooleanVariable& Variable)
{
 return Variable.GetBoolean();
}

CBooleanVariable& CBooleanVariable::operator =(const double Value)
{
 SetFloat(Value);
 return *this;
}

CBooleanVariable& CBooleanVariable::operator =(const int Value)
{
 SetInteger(Value);
 return *this;
}

CBooleanVariable& CBooleanVariable::operator =(const bool Value)
{
 SetBoolean(Value);
 return *this;
}

CBooleanVariable& CBooleanVariable::operator =(const CString& Value)
{
 SetString(Value);
 return *this;
}

CBooleanVariable& CBooleanVariable::operator =(const char Value)
{
 SetChar(Value);
 return *this;
}

CBooleanVariable::CBooleanVariable(const CString& Name,const bool Value)
:CVariable(Name)
{
 m_Value = Value;
}

//------------------------------------------------------------------------------

CVariable::VariableType CFlagVariable::GetType(void) const
{
 return CVariable::varFlag;
}

CString CFlagVariable::GetTypeName(void) const
{
 return "flag";
}

CVariable *CFlagVariable::CreateInstance() const
{
 CFlagVariable *variable = new CFlagVariable(m_Name);
 variable->SetBoolean(m_Value);
 return variable;
}

//------------------------------------------------------------------------------

CVariable::VariableType CStringVariable::GetType(void) const
{
 return CVariable::varString;
}

CString CStringVariable::GetTypeName(void) const
{
 return "string";
}

double CStringVariable::GetFloat(void) const
{
 return StringToFloat(m_Value);
}

void CStringVariable::SetFloat(const double Value)
{
 m_Value = FloatToStr(Value);
}

int CStringVariable::GetInteger(void) const
{
 return StringToInteger(m_Value);
}

void CStringVariable::SetInteger(const int Value)
{
 m_Value = IntegerToString(Value);
}

bool CStringVariable::GetBoolean(void) const
{
 return StringToBoolean(m_Value);
}

void CStringVariable::SetBoolean(const bool Value)
{
 m_Value = BooleanToString(Value);
}

CString CStringVariable::GetString(void) const
{
 return m_Value;
}

void CStringVariable::SetString(const CString& Value)
{
 m_Value = Value;
}

char CStringVariable::GetChar(void) const
{
 return StringToChar(m_Value);
}

void CStringVariable::SetChar(const char Value)
{
 m_Value = CharToString(Value);
}

CVariable *CStringVariable::CreateInstance() const
{
 CStringVariable *variable = new CStringVariable(m_Name);
 variable->SetString(m_Value);
 return variable;
}

CString CStringVariable::operator=(const CStringVariable& Variable)
{
 return Variable.GetString();
}

CStringVariable& CStringVariable::operator =(const double Value)
{
 SetFloat(Value);
 return *this;
}

CStringVariable& CStringVariable::operator =(const int Value)
{
 SetInteger(Value);
 return *this;
}

CStringVariable& CStringVariable::operator =(const bool Value)
{
 SetBoolean(Value);
 return *this;
}

CStringVariable& CStringVariable::operator =(const CString& Value)
{
 SetString(Value);
 return *this;
}

CStringVariable& CStringVariable::operator =(const char Value)
{
 SetChar(Value);
 return *this;
}

CStringVariable::CStringVariable(const CString& Name,const CString Value)
:CVariable(Name)
{
 m_Value = Value;
}

//------------------------------------------------------------------------------

CVariable::VariableType CCharVariable::GetType(void) const
{
 return CVariable::varChar;
}

CString CCharVariable::GetTypeName(void) const
{
 return "char";
}

double CCharVariable::GetFloat(void) const
{
 return CharToFloat(m_Value);
}

void CCharVariable::SetFloat(const double Value)
{
 m_Value = FloatToChar(Value);
}

int CCharVariable::GetInteger(void) const
{
 return CharToInt(m_Value);
}

void CCharVariable::SetInteger(const int Value)
{
 m_Value = IntToChar(Value);
}

bool CCharVariable::GetBoolean(void) const
{
 return CharToBool(m_Value);
}

void CCharVariable::SetBoolean(const bool Value)
{
 m_Value = BoolToChar(Value);
}

CString CCharVariable::GetString(void) const
{
 return CharToStr(m_Value);
}

void CCharVariable::SetString(const CString& Value)
{
 m_Value = StringToChar(Value);
}

char CCharVariable::GetChar(void) const
{
 return m_Value;
}

void CCharVariable::SetChar(const char Value)
{
 m_Value=Value;
}

CVariable *CCharVariable::CreateInstance() const
{
 CCharVariable *variable = new CCharVariable(m_Name);
 variable->SetChar(m_Value);
 return variable;
}

char CCharVariable::operator=(const CCharVariable& Variable)
{
 return Variable.GetChar();
}

CCharVariable& CCharVariable::operator =(const double Value)
{
 SetFloat(Value);
 return *this;
}

CCharVariable& CCharVariable::operator =(const int Value)
{
 SetInteger(Value);
 return *this;
}

CCharVariable& CCharVariable::operator =(const bool Value)
{
 SetBoolean(Value);
 return *this;
}

CCharVariable& CCharVariable::operator =(const CString& Value)
{
 SetString(Value);
 return *this;
}

CCharVariable& CCharVariable::operator =(const char Value)
{
 SetChar(Value);
 return *this;
}

CCharVariable::CCharVariable(const CString& Name,const char Value)
:CVariable(Name)
{
 m_Value = Value;
}

//------------------------------------------------------------------------------
