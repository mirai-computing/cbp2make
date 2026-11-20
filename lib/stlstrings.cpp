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
#include <cstdlib>
#include <cmath>
#include <iostream>
//------------------------------------------------------------------------------
#include "stlstrings.h"
#include "stlconvert.h"
//------------------------------------------------------------------------------

const CString ALPHABET_NULL_CHAR      = char(0x00);
const CString ALPHABET_TAB_CHAR       = char(0x09);
const CString ALPHABET_CR_CHAR        = char(0x0d);
const CString ALPHABET_LF_CHAR        = char(0x0a);
const CString ALPHABET_BIN_NUMBER     = "01";
const CString ALPHABET_OCT_NUMBER     = "01234567";
const CString ALPHABET_NUMBER         = "0123456789";
const CString ALPHABET_INTEGER_NUMBER = "+-0123456789";
const CString ALPHABET_FLOAT_NUMBER   = "+-.,0123456789eE";
const CString ALPHABET_DOUBLE_NUMBER  = "+-.,0123456789dD";
const CString ALPHABET_REAL_NUMBER    = "+-.,0123456789eEdD";
const CString ALPHABET_HEX_NUMBER     = "0123456789abcdefABCDEF";
const CString ALPHABET_CTL_CHARS      = "\'\"\?\\\a\b\f\n\r\t\v\0";
const CString ALPHABET_ESC_SEQUENCE   = "\'\"?\\abfnrtv0";
const CString ALPHABET_SHELL_CHARS    = " !@#$%^&*(){}[];\'\"\\|<>?";
const CString ALPHABET_LCASE_CHARS    = "abcdefghijklmnopqrstuvwxyz";
const CString ALPHABET_UCASE_CHARS    = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


std::string& CString::GetString(void)
{
 return m_String;
}

std::string CString::GetString(void) const
{
 return m_String;
}

char *CString::GetCString(void) const
{
 return (char *)m_String.c_str();
}

int CString::GetLength(void) const
{
 return m_String.size();
}

bool CString::IsEmpty(void) const
{
 return (GetLength()==0);
}

CString& CString::SetLength(void)
{
 m_String.resize(strlen(GetCString()));
 return *this;
}

CString& CString::SetLength(const int Length)
{
 m_String.resize(Length);
 return *this;
}

CString& CString::Reserve(const int Length)
{
 size_t new_size = std::max(Length,0);
 if (new_size>m_String.capacity())
 {
  m_String.reserve(new_size);
 }
 return *this;
}

CString& CString::Truncate(void)
{
 m_String.shrink_to_fit();
 return *this;
}

CString& CString::Truncate(const int Size)
{
 m_String.resize(Size);
 return *this;
}

CString& CString::Clear(void)
{
 m_String.clear();
 return *this;
}

char CString::GetChar(const int Index) const
{
 if ((Index>=0)&&(Index<GetLength())) return m_String[Index]; else return 0;
}

char CString::GetFirstChar(void) const
{
 return m_String[0];
}

char CString::GetLastChar(void) const
{
 if (m_String.size()) return m_String[GetLength()-1]; else return 0;
}

void CString::SetChar(const int Index, const char Value)
{
 if ((Index>=0)&&(Index<GetLength())) m_String[Index] = Value;
}

CString& CString::Assign(const char AChar)
{
 m_String.resize(1);
 m_String[0]=AChar;
 return *this;
}

CString& CString::Assign(const char *AString)
{
 m_String = AString;
 return *this;
}

CString& CString::Assign(const std::string& AString)
{
 m_String = AString;
 return *this;
}

CString& CString::Assign(const CString& AString)
{
 m_String = AString.GetString();
 return *this;
}

CString& CString::Assign(const int32_t AInteger)
{
 std::to_string(AInteger);
 char buffer[CString::BUFFER_SIZE];
 sprintf(buffer,"%ld",(long int)AInteger);
 *this = buffer;
 return *this;
}

CString& CString::Assign(const int64_t AInteger)
{
 char buffer[CString::BUFFER_SIZE];
 sprintf(buffer,"%lld",(long long int)AInteger);
 *this = buffer;
 return *this;
}

CString& CString::Assign(const uint32_t AInteger)
{
 char buffer[CString::BUFFER_SIZE];
 sprintf(buffer,"%lu",(unsigned long int)AInteger);
 *this = buffer;
 return *this;
}

CString& CString::Assign(const uint64_t AInteger)
{
 char buffer[CString::BUFFER_SIZE];
 sprintf(buffer,"%llu",(unsigned long long int)AInteger);
 *this = buffer;
 return *this;
}

CString& CString::Assign(const float AFloat, const int Precision)
{
 char buffer[CString::BUFFER_SIZE];
 if (Precision>=0)
 {
  CString format = "%."+IntegerToString(Precision)+"e";
  sprintf(buffer,format.GetCString(),AFloat);
 }
 else
 {
  sprintf(buffer,"%e",AFloat);
 }
 *this = buffer;
 return *this;
}

CString& CString::Assign(const double AFloat, const int Precision)
{
 char buffer[CString::BUFFER_SIZE];
 if (Precision>=0)
 {
  CString format = "%."+IntegerToString(Precision)+"le";
  sprintf(buffer,format.GetCString(),AFloat);
 }
 else
 {
  sprintf(buffer,"%le",AFloat);
 }
 *this = buffer;
 return *this;
}

CString& CString::Prepend(const CString& AString)
{
 m_String.insert(0,AString.m_String);
 return *this;
}

CString& CString::Append(const char AChar)
{
 SetLength(GetLength()+1);
 m_String[GetLength()-1]=AChar;
 return *this;
}

CString& CString::Append(const char *AString)
{
 m_String.append(AString);
 return *this;
}

CString& CString::Append(const CString& AString)
{
 m_String.append(AString.GetString());
 return *this;
}

CString& CString::AppendCR(void)
{
 return Append(char(0xd));
}

CString& CString::AppendLF(void)
{
 return Append(char(0xa));
}

CString& CString::AppendCRLF(void)
{
 char *_CRLF = "\r\n";
 return Append(_CRLF);
}

CString& CString::AppendEOL(void)
{
 switch (m_eol_type)
 {
  case eol_cr: { AppendCR(); break; }
  case eol_lf: { AppendLF(); break; }
  case eol_crlf: { AppendCRLF(); break; }
 }
 return *this;
}

CString  CString::GetEOL(void)
{
 CString result;
 result.AppendEOL();
 return result;
}

CString& CString::SetEOL(const eol_t EOL)
{
 m_eol_type = EOL;
 return *this;
}

char& CString::operator [](const int Index)
{
 return m_String[Index];
}

char CString::operator [](const int Index) const
{
 return m_String[Index];
}

CString& CString::operator =(const char AChar)
{
 return Assign(AChar);
}

CString& CString::operator =(const char *AString)
{
 return Assign(AString);
}

CString& CString::operator =(const std::string& AString)
{
 return Assign(AString);
}

CString& CString::operator =(const CString& AString)
{
 return Assign(AString);
}

CString& CString::operator =(const int AInteger)
{
 char buffer[MAX_SHORTSTRING_LENGTH];
 sprintf(buffer,"%d",AInteger);
 *this = buffer;
 return *this;
}

CString& CString::operator =(const int64_t AInteger)
{
 char buffer[MAX_SHORTSTRING_LENGTH];
 sprintf(buffer,"%lld",AInteger);
 *this = buffer;
 return *this;
}

CString& CString::operator =(const float AFloat)
{
 char buffer[MAX_SHORTSTRING_LENGTH];
 sprintf(buffer,"%e",AFloat);
 *this = buffer;
 return *this;
}

CString& CString::operator =(const double AFloat)
{
 char buffer[MAX_SHORTSTRING_LENGTH];
 sprintf(buffer,"%le",AFloat);
 *this = buffer;
 return *this;
}

CString& CString::operator +=(const char AChar)
{
 return Append(AChar);
}

CString& CString::operator +=(const char *AString)
{
 return Append(AString);
}

CString& CString::operator +=(const CString& AString)
{
 return Append(AString);
}

CString& CString::operator +=(const int AInteger)
{
 char buffer[MAX_SHORTSTRING_LENGTH];
 sprintf(buffer,"%d",AInteger);
 Append(buffer);
 return *this;
}

CString& CString::operator +=(const int64_t AInteger)
{
 char buffer[MAX_SHORTSTRING_LENGTH];
 sprintf(buffer,"%lld",AInteger);
 Append(buffer);
 return *this;
}

CString& CString::operator +=(const float AFloat)
{
 char buffer[MAX_SHORTSTRING_LENGTH];
 sprintf(buffer,"%e",AFloat);
 Append(buffer);
 return *this;
}

CString& CString::operator +=(const double AFloat)
{
 char buffer[MAX_SHORTSTRING_LENGTH];
 sprintf(buffer,"%le",AFloat);
 Append(buffer);
 return *this;
}

bool CString::operator ==(const char *AString) const
{
 return (0==strcmp(GetCString(),AString));
}

bool CString::operator ==(const std::string& AString) const
{
 return (0==strcmp(GetCString(),AString.c_str()));
}

bool CString::operator ==(const CString& AString) const
{
 return (0==strcmp(GetCString(),AString.GetCString()));
}

int CString::GetInteger(void) const
{
 return atoi(GetCString());
}

int64_t CString::GetInt64(void) const
{
 if (sizeof(long int)==sizeof(int64_t)) return atol(GetCString());
 return atoll(GetCString());
}

uint64_t CString::GetUInt64(void) const
{
 if (sizeof(long int)==sizeof(uint64_t)) return (uint64_t)atol(GetCString());
 return (uint64_t)atoll(GetCString());
}

double CString::GetFloat(void) const
{
 return atof(GetCString());
}

void CString::Fill(const char AChar)
{
 for (int i = 0, n = GetLength(); i < n; i++)
 {
  m_String[i] = AChar;
 }
}

void CString::Print(std::ostream& out)
{
 out<<m_String;
}

CString::CString(void)
{
 m_eol_type = eol_lf;
}

CString::CString(const char AChar)
{
 Assign(AChar);
 m_eol_type = eol_lf;
}

CString::CString(const char *AString)
{
 Assign(AString);
 m_eol_type = eol_lf;
}

CString::CString(const std::string& AString)
{
 Assign(AString);
 m_eol_type = eol_lf;
}

CString::CString(const CString& AString)
{
 Assign(AString);
 m_eol_type = eol_lf;
}

CString::~CString(void)
{
 //Clear();
}

//------------------------------------------------------------------------------

CStringList::CStringList(void)
{
 //Clear();
}

CStringList::CStringList(const CStringList& AStringList)
{
 Clear();
 Insert(AStringList);
}

CStringList::~CStringList(void)
{
 Clear();
}

bool CStringList::ValidIndex(const int Index) const
{
 return ((Index>=0)&&(Index<GetCount()));
}

bool CStringList::IsEmpty(void) const
{
 if (0==GetCount()) return true;
 if (0==GetLength()) return true;
 return false;
}

int CStringList::GetCount(void) const
{
 return m_Strings.size();
}

int CStringList::GetLength(void) const
{
 int result = 0;
 for (int i = GetCount()-1; i > 0; i--) result += m_Strings[i]->GetLength();
 return result;
}

CString& CStringList::GetString(const int Index)
{
 if (ValidIndex(Index))
 {
  return *m_Strings[Index];
 }
 else
 {
  return m_NullString;
 }
}

CString CStringList::GetString(const int Index) const
{
 if (ValidIndex(Index))
 {
  return *m_Strings[Index];
 }
 else
 {
  return m_NullString;
 }
}

CString CStringList::Join(const CString& Delimiter) const
{
 CString result;
 if (GetCount() > 0)
 {
  result.Append(*m_Strings[0]);
  for (int i = 1, n = GetCount(); i < n; i++)
  {
   result.Append(Delimiter).Append(*m_Strings[i]);
  }
 }
 return result;
}

int CStringList::FindString(const CString& AString) const
{
 for (int i = 0, n = GetCount(); i < n; i++)
 {
  if (GetString(i)==AString) return i;
 }
 return INVALID_INDEX;
}

int CStringList::Insert(const CString *AString)
{
 m_Strings.push_back((CString *)AString);
 return GetCount()-1;
}

int CStringList::Insert(const CString& AString)
{
 m_Strings.push_back(new CString(AString));
 return GetCount()-1;
}

CStringList& CStringList::Insert(const CStringList& AStringList)
{
 for (int i = 0; i < AStringList.GetCount(); i++)
 {
  Insert(AStringList[i]);
 }
 return *this;
}

CStringList& CStringList::InsertAt(const int Index, const CStringList& AStringList)
{
 for (int i = 0; i < AStringList.GetCount(); i++)
 {
  InsertAt(Index+i,AStringList[i]);
 }
 return *this;
}

CStringList& CStringList::InsertAt(const int Index, const CString *AString)
{
 if (ValidIndex(Index))
 {
  m_Strings.insert(m_Strings.begin()+Index,(CString *)AString);
 }
 return *this;
}

CStringList& CStringList::InsertAt(const int Index, const CString& AString)
{
 if (ValidIndex(Index))
 {
  m_Strings.insert(m_Strings.begin()+Index,new CString(AString));
 }
 return *this;
}

CStringList& CStringList::RemoveAt(const int Index)
{
 if (ValidIndex(Index))
 {
  CString *string = m_Strings[Index];
  m_Strings.erase(m_Strings.begin()+Index);
  delete string;
 }
 return *this;
}

CStringList& CStringList::Reserve(const int Count)
{
 while (GetCount()<Count) Insert("");
 return *this;
}

CStringList& CStringList::RemoveEmpty(void)
{
 for (int i = m_Strings.size()-1; i >= 0; i--)
 {
  if (GetString(i).IsEmpty())
  {
   RemoveAt(i);
 }}
 return *this;
}

CStringList& CStringList::RemoveDuplicates(void)
{
 for (size_t j = 0; j < m_Strings.size(); j++)
 {
  for (size_t i = m_Strings.size()-1; i > j; i--)
  {
   if (GetString(j)==GetString(i))
   {
    RemoveAt(i);
 }}}
 return *this;
}

CStringList& CStringList::Clear(void)
{
 for (int i = m_Strings.size()-1; i >= 0; i--)
 {
  RemoveAt(i);
 }
 return *this;
}

CStringList& CStringList::PrependAllStrings(const CString& AString)
{
 for (size_t j = 0; j < m_Strings.size(); j++)
 {
  CString *sj = (CString *)m_Strings.at(j);
  sj->Prepend(AString);
 }
 return *this;
}

CStringList& CStringList::AppendAllStrings(const CString& AString)
{
 for (size_t j = 0; j < m_Strings.size(); j++)
 {
  CString *sj = (CString *)m_Strings.at(j);
  sj->Append(AString);
 }
 return *this;
}

bool CStringList::AppendFromFile(const CString& FileName)
{
 FILE* stream = fopen(FileName.GetCString(),"rb");
 CString buffer; char c,c2; int buf_pos;
 if (NULL!=stream)
 {
  buffer.SetLength(CString::BUFFER_SIZE);
  buf_pos = 0; c = 0;
  while (!feof(stream))
  {
   c2 = c;
   fread(&c,1,1,stream);
   switch (c)
   {
    case 0x00: case 0x0d:
    {
     buffer.SetLength(buf_pos);
     Insert(buffer);
     buf_pos = 0;
     break;
    }
    case 0x0a:
    {
     if (0x0d!=c2)
     {
      buffer.SetLength(buf_pos);
      Insert(buffer);
      buf_pos = 0;
     }
     break;
    }
    default:
    {
     if (buffer.GetLength()<CString::BUFFER_SIZE) buffer.SetLength(CString::BUFFER_SIZE);
     if (buf_pos>=buffer.GetLength()) buffer.SetLength(buffer.GetLength()*2);
     buffer[buf_pos++] = c;
     break;
  }}}
  if (buf_pos>0)
  {
   buffer.SetLength(buf_pos-1);
   Insert(buffer);
  }
  fclose(stream);
  return true;
 }
 return false;
}

bool CStringList::LoadFromFile(const CString& FileName)
{
 Clear();
 return AppendFromFile(FileName);
}

bool CStringList::AppendToFile(const CString& FileName, const bool WriteEOL)
{
 FILE* stream = fopen(FileName.GetCString(),"a+");
 if (NULL!=stream)
 {
  CString buf; buf.AppendEOL();
  for (int i = 0; i < GetCount(); i++)
  {
   CString& tmp = GetString(i);
   fwrite(tmp.GetCString(),tmp.GetLength(),1,stream);
   if (WriteEOL) fwrite(buf.GetCString(),buf.GetLength(),1,stream);
  }
  fclose(stream);
  return true;
 }
 return false;
}

bool CStringList::WriteToFile(FILE* stream, const bool WriteEOL)
{
 if (NULL!=stream)
 {
  CString buf; buf.AppendEOL();
  for (int i = 0; i < GetCount(); i++)
  {
   CString& tmp = GetString(i);
   fwrite(tmp.GetCString(),tmp.GetLength(),1,stream);
   if (WriteEOL) fwrite(buf.GetCString(),buf.GetLength(),1,stream);
  }
  return true;
 }
 return false;
}

bool CStringList::SaveToFile(const CString& FileName, const bool WriteEOL)
{
 FILE* stream = fopen(FileName.GetCString(),"wb");
 if (NULL!=stream)
 {
  WriteToFile(stream,WriteEOL);
  fclose(stream);
  return true;
 }
 return false;
}

void CStringList::Print(std::ostream& out)
{
 for (int i = 0; i < GetCount(); i++)
 {
  out<<GetString(i).GetCString()<<std::endl;
 }
}

CStringList& CStringList::operator =(const CString& AString)
{
 Clear();
 Insert(AString);
 return *this;
}

CStringList& CStringList::operator =(const CStringList& AStringList)
{
 Clear();
 Insert(AStringList);
 return *this;
}

CString& CStringList::operator [](const int Index)
{
 return GetString(Index);
}

CString CStringList::operator [](const int Index) const
{
 return GetString(Index);
}

CStringList& CStringList::operator <<(const CString& AString)
{
 Insert(AString);
 return *this;
}

//---------------------------------------------------------------------------

CCharset::CCharset(void)
{
 UpdateCharset();
}

CCharset::CCharset(const CCharset& Charset)
{
 SetAlphabet(Charset.GetAlphabet());
}

CCharset::CCharset(const CString& Alphabet)
{
 SetAlphabet(Alphabet);
}

CCharset::~CCharset(void)
{
}

void CCharset::UpdateCharset(void)
{
 for (int i = 0; i < CHARSET_SIZE; i++) m_Charset[i] = false;
 for (int i = 0; i < m_Alphabet.GetLength(); i++) m_Charset[(unsigned char)m_Alphabet[i]] = true;
}

void CCharset::UpdateAlphabet(void)
{
 m_Alphabet.SetLength(CHARSET_SIZE); int charset_size = 0;
 for (int i = 0; i < CHARSET_SIZE; i++)
 {
  if (m_Charset[i])
  {
   m_Alphabet[charset_size++] = char(i);
  }
 }
 m_Alphabet.SetLength(charset_size);
}

bool CCharset::Isset(const char AChar) const
{
 return m_Charset[*(unsigned char *)&AChar];
}

char CCharset::GetChar(const char AChar) const
{
 if (m_Charset[*(unsigned char *)&AChar]) return AChar; else return char(0);
}

void CCharset::SetChar(const char AChar)
{
 m_Charset[*(unsigned char *)&AChar] = true;
 UpdateAlphabet();
}

void CCharset::UnsetChar(const char AChar)
{
 m_Charset[*(unsigned char *)&AChar] = false;
 UpdateAlphabet();
}

CString CCharset::GetAlphabet(void) const
{
 return m_Alphabet;
}

void CCharset::SetAlphabet(const CString& Alphabet)
{
 m_Alphabet = Alphabet;
 UpdateCharset();
 /*UpdateAlphabet();*/
}

void CCharset::Print(std::ostream& out)
{
 out<<m_Alphabet.GetCString();
}

//------------------------------------------------------------------------------

bool CCharIterator::Match(const CString& Pattern, const bool Move)
{
 bool result = true;
 for (int i = 0; i < Pattern.GetLength(); i++)
 {
  if (This()!=Pattern[i]) return false;
  Next();
 }
 return result;
}

//------------------------------------------------------------------------------

CStringIterator::CStringIterator(void)
{
 m_String = NULL;
 m_Position = 0;
}

CStringIterator::CStringIterator(const CString *AString)
{
 m_String = (CString *)AString;
 m_Position = 0;
}

CStringIterator::CStringIterator(const CStringIterator& AStringIterator)
{
}

int CStringIterator::FirstPosition(void)
{
 return 0;
}

int CStringIterator::ThisPosition(void)
{
 return m_Position;
}

int CStringIterator::LastPosition(void)
{
 return m_String->GetLength()-1;
}

char& CStringIterator::First(void)
{
 m_Position = FirstPosition();
 return This();
}

char& CStringIterator::Prev(void)
{
 if (m_Position > 0) m_Position--;
 return This();
}

char& CStringIterator::This(void)
{
 return (*m_String)[m_Position];
}

char& CStringIterator::Next(void)
{
 if (m_Position < (int)m_String->GetLength()) m_Position++;
 return This();
}

char& CStringIterator::Last(void)
{
 m_Position = LastPosition();
 return This();
}

void CStringIterator::Reset(void)
{
 First();
}

bool CStringIterator::Match(const CString& Pattern, const bool Move)
{
 int position = m_Position;
 bool result = CCharIterator::Match(Pattern,false);
 if (!(result && Move)) m_Position = position;
 return result;
}

void CStringIterator::Assign(const CStringIterator& Iterator)
{
 m_String = Iterator.m_String;
 m_Position = Iterator.m_Position;
}

void CStringIterator::Assign(const CCharIterator* Iterator)
{
 if (Iterator->GetType()==CCharIterator::ir_string_iterator)
 {
  Assign(*(CStringIterator*)Iterator);
 }
}

CCharIterator* CStringIterator::CreateInstance(void)
{
 return new CStringIterator(*this);
}

void CStringIterator::InitInstance(CStringIterator& Iterator)
{
 Iterator.Assign(*this);
}

//------------------------------------------------------------------------------

CStringListIterator::CStringListIterator(void)
{
 m_StringList = NULL;
 m_Line = 0;
 m_Position = 0;
}

CStringListIterator::CStringListIterator(const CStringList *AStringList)
{
 m_StringList = (CStringList *)AStringList;
}

CStringListIterator::CStringListIterator(const CStringListIterator& AStringListIterator)
{
 Assign(AStringListIterator);
}

int CStringListIterator::FirstPosition(void)
{
 return 0;
}

int CStringListIterator::ThisPosition(void)
{
 return m_Position;
}

int CStringListIterator::LastPosition(void)
{
 if (NULL==m_StringList) return m_NullChar;
 return m_StringList->GetLength() + m_StringList->GetCount(); // length of all strings + null chars
}

char& CStringListIterator::First(void)
{
 if (NULL==m_StringList) return m_NullChar;
 m_Line = 0;
 m_LinePos = 0;
 m_Position = FirstPosition();
 return This();
}

char& CStringListIterator::Prev(void)
{
 if (NULL==m_StringList) return m_NullChar;
 if (m_LinePos > 0)
 {
  m_LinePos--; m_Position--; return This();
 }
 else
 {
  if (m_Line > 0)
  {
   m_Line--; m_Position--;
   m_LinePos = std::max(0,m_StringList->GetString(m_Line).GetLength()-1);
 }}
 return This();
}

char& CStringListIterator::This(void)
{
 if (NULL==m_StringList) return m_NullChar;
 return m_StringList->GetString(m_Line)[m_Position];
}

char& CStringListIterator::Next(void)
{
 if (NULL==m_StringList) return m_NullChar;
 if (m_LinePos < m_StringList->GetString(m_Line).GetLength())
 {
  m_LinePos++; m_Position++; return This();
 }
 else
 {
 if (m_Line < (m_StringList->GetCount()-1))
  {
   m_Line++; m_LinePos = 0; m_Position++;
 }}
 return This();
}

char& CStringListIterator::Last(void)
{
 if (NULL==m_StringList) return m_NullChar;
 m_Line = m_StringList->GetCount()-1;
 m_LinePos = m_StringList->GetString(m_Line).GetLength();
 m_Position = LastPosition();
 return This();
}

void CStringListIterator::Reset(void)
{
 First();
}

bool CStringListIterator::Match(const CString& Pattern, const bool Move)
{
 int line = m_Line;
 int position = m_Position;
 bool result = CCharIterator::Match(Pattern,false);
 if (!(result && Move))
 {
  m_Line = line;
  m_Position = position;
 }
 return result;
}

void CStringListIterator::Assign(const CStringListIterator& Iterator)
{
 m_StringList = Iterator.m_StringList;
 m_Line = Iterator.m_Line;
 m_LinePos = Iterator.m_LinePos;
 m_Position = Iterator.m_Position;
}

void CStringListIterator::Assign(const CCharIterator* Iterator)
{
 if (Iterator->GetType()==CCharIterator::it_stringlist_iterator)
 {
  Assign(*(CStringListIterator*)Iterator);
 }
}

void CStringListIterator::InitInstance(CStringListIterator& Iterator)
{
 Iterator.Assign(*this);
}

//------------------------------------------------------------------------------

CCharHistogram::CCharHistogram(void)
{
 Reset();
}

CCharHistogram::CCharHistogram(const CCharHistogram& AHistogram)
{
 Reset();
}

CCharHistogram::~CCharHistogram(void)
{
 // do nothing //
}

void CCharHistogram::Analyze(void)
{
 m_Flags = 0;
 CCharset numeric_charset(ALPHABET_NUMBER);
 CCharset realnum_charset(ALPHABET_REAL_NUMBER);
 CCharset integer_charset(ALPHABET_INTEGER_NUMBER);
 CCharset textnum_charset(ALPHABET_REAL_NUMBER+ALPHABET_TAB_CHAR+" "+ALPHABET_CR_CHAR+ALPHABET_LF_CHAR);
 unsigned int total_chars = 0, ascii_chars = 0, textnum_chars = 0,
              realnum_chars = 0, integer_chars = 0, numeric_chars = 0;
 for (int i = 0; i < CHARSET_SIZE; i++)
 {
  unsigned int _CharCount = m_Histogram[i];
  total_chars += _CharCount;
  if (i<0x80) ascii_chars += _CharCount;
  if (textnum_charset.Isset(char(i)))
  {
   textnum_chars += _CharCount;
   if (realnum_charset.Isset(char(i)))
   {
    realnum_chars += _CharCount;
    if (integer_charset.Isset(char(i)))
    {
     integer_chars += _CharCount;
     if (numeric_charset.Isset(char(i))) numeric_chars += _CharCount;
 }}}}
 // if there are characters with codes >= 0x80 then content is not an ascii text
 if (total_chars>ascii_chars) m_Flags |= FLAG_CUSTOM_BINARY;
 else
 {
  // if there are letters other than exponent specifiers
  if (total_chars>textnum_chars) m_Flags |= FLAG_ASCII_TEXT;
  else
  {
   // if there is at least one digit character
   if (numeric_chars>0)
   {
    if (realnum_chars>integer_chars) m_Flags |= FLAG_PURE_NUMERIC;
    else m_Flags |= FLAG_PURE_INTEGER;
   }
   else m_Flags |= FLAG_ASCII_TEXT;
  }
 }
}

void CCharHistogram::Reset(void)
{
 m_Flags = 0; for (int i = 0; i < CHARSET_SIZE; i++) m_Histogram[i] = 0;
}

void CCharHistogram::Insert(const char AChar)
{
 if (m_Histogram[(unsigned char)AChar]<MAX_CHAR_FREQUENCY) m_Histogram[(unsigned char)AChar]++;
 m_Flags = 0;
}

void CCharHistogram::Insert(const CString& AString)
{
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  char c = AString[i];
  if (m_Histogram[(unsigned char)c]<MAX_CHAR_FREQUENCY) m_Histogram[(unsigned char)c]++;
 }
 m_Flags = 0;
}

void CCharHistogram::Insert(const CStringList& AStringList)
{
 for (int j = 0, nj = AStringList.GetCount(); j < nj; j++)
 {
  CString s = AStringList.GetString(j);
  for (int i = 0, ni = s.GetLength(); i < ni; i++)
  {
   char c = s[i];
   if (m_Histogram[(unsigned char)c]<MAX_CHAR_FREQUENCY) m_Histogram[(unsigned char)c]++;
 }}
 m_Flags = 0;
}

void CCharHistogram::Remove(const char AChar)
{
 if (m_Histogram[(unsigned char)AChar]>0) m_Histogram[(unsigned char)AChar]--;
 m_Flags = 0;
}

void CCharHistogram::Remove(const CString& AString)
{
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  char c = AString[i];
  if (m_Histogram[(unsigned char)c]>0) m_Histogram[(unsigned char)c]--;
 }
 m_Flags = 0;
}

void CCharHistogram::Remove(const CStringList& AStringList)
{
 for (int j = 0, nj = AStringList.GetCount(); j < nj; j++)
 {
  CString s = AStringList.GetString(j);
  for (int i = 0, ni = s.GetLength(); i < ni; i++)
  {
   char c = s[i];
   if (m_Histogram[(unsigned char)c]>0) m_Histogram[(unsigned char)c]--;
 }}
 m_Flags = 0;
}

bool CCharHistogram::IsPureNumeric(void)
{
 if (0==m_Flags) Analyze();
 return ((m_Flags&FLAG_PURE_NUMERIC)!=0);
}

bool CCharHistogram::IsPureInteger(void)
{
 if (0==m_Flags) Analyze();
 return ((m_Flags&FLAG_PURE_INTEGER)!=0);
}

bool CCharHistogram::IsAsciiText(void)
{
 if (0==m_Flags) Analyze();
 return ((m_Flags&FLAG_ASCII_TEXT)!=0);
}

bool CCharHistogram::IsCustomBinary(void)
{
 if (0==m_Flags) Analyze();
 return ((m_Flags&FLAG_CUSTOM_BINARY)!=0);
}

unsigned int CCharHistogram::GetAt(const char AChar) const
{
 return m_Histogram[(unsigned char)AChar];
}

void CCharHistogram::SetAt(const char AChar, const unsigned int Frequency)
{
 m_Histogram[(unsigned char)AChar] = Frequency;
}

CString CCharHistogram::GetAlphabet(void) const
{
 CString result;
 for (int i = 0, n = CHARSET_SIZE; i < n; i++)
 {
  if (m_Histogram[i]>0) result.Append(char(i));
 }
 return result;
}

void CCharHistogram::Print(std::ostream& out)
{
 for (int i = 0, n = CHARSET_SIZE; i < n; i++)
 {
  out<<"char 0x"<<hex(i,2*sizeof(char)).GetCString();
  if (i>0x20) out<<char(i)<<" "; else out<<"  ";
  out<<" freq "<<m_Histogram[i]<<std::endl<<std::flush;
 }
}

//------------------------------------------------------------------------------

static bool F_HEX_LUT = false;
static uint8_t HEX_LUT[0x100];

void InitHexLUT()
{
 if (!F_HEX_LUT)
 {
  for (int i=0; i<0x100; i++) HEX_LUT[i] = 0;
  for (int i=0; i<0x10; i++) HEX_LUT[(uint8_t)HEX_CHARS_LCASE[i]] = i;
  for (int i=0; i<0x10; i++) HEX_LUT[(uint8_t)HEX_CHARS_UCASE[i]] = i;
  F_HEX_LUT = true;
 }
}

void HexToBuf(const CString& AString, uint8_t* Buffer, const int Size, const bool BigEndian)
{
 if (BigEndian)
 {
  for (int i=0,j=0; i<Size; i++)
  {
   uint8_t h = HEX_LUT[(uint8_t)AString.GetChar(j++)];
   uint8_t l = HEX_LUT[(uint8_t)AString.GetChar(j++)];
   Buffer[i] = ((h<<4)|l);
  }
 }
 else
 {
  for (int i=0,j=Size*2-1; i<Size; i++)
  {
   uint8_t l = HEX_LUT[(uint8_t)AString.GetChar(j--)];
   uint8_t h = HEX_LUT[(uint8_t)AString.GetChar(j--)];
   Buffer[i] = ((h<<4)|l);
  }
 }
}

int HexStrToInt(const CString& AString, const int Size, const bool BigEndian)
{
 InitHexLUT();
 int result = 0;
 uint8_t* buf = (uint8_t*)&result;
 int n = std::min((size_t)Size,sizeof(result));
 HexToBuf(AString,buf,n,BigEndian);
 return result;
}

float HexStrToFloat(const CString& AString, const int Size, const bool BigEndian)
{
 InitHexLUT();
 float result = 0;
 uint8_t* buf = (uint8_t*)&result;
 int n = std::min((size_t)Size,sizeof(result));
 HexToBuf(AString,buf,n,BigEndian);
 return result;
}

double HexStrToDouble(const CString& AString, const int Size, const bool BigEndian)
{
 InitHexLUT();
 double result = 0;
 uint8_t* buf = (uint8_t*)&result;
 int n = std::min((size_t)Size,sizeof(result));
 HexToBuf(AString,buf,n,BigEndian);
 return result;
}

CString CharArrayToString(const char* CharArray, const int Size)
{
 CString result; result.SetLength(Size);
 for (int i=0; i<Size; i++) result[i] = CharArray[i];
 result.SetLength(); // trim 0's
 return result;
}

void StringToCharArray(const CString& AString, char* CharArray, const int Size)
{
 int n = std::min(AString.GetLength(),std::max(Size,0));
 for (int i=0; i<n; i++) CharArray[i] = AString[i];
 for (int i=n; i<Size; i++) CharArray[i] = 0;
}

CString SignatureChars(const uint32_t Signature)
{
 CString result; uint32_t s = Signature;
 for (size_t i = 0; i < sizeof(s); i++)
 {
  result+=char(s&0xff);
  if (result[i]<' ') result[i] = ' ';
  s>>=8;
 }
 return result;
}

CString StringOfChars(const char AChar, const int Count)
{
 CString result;
 if (Count>0) result.SetLength(Count).Fill(AChar);
 return result;
}

CString FillStr(const CString& Prefix, const char AChar,
                const CString& Suffix, const int Length)
{
 CString filler = StringOfChars(AChar,Length-Prefix.GetLength()-Suffix.GetLength());
 CString result = Prefix+filler+Suffix;
 return result;
}

int EnumDigits(const int Number)
{
 //return 1+ceil(log10(abs(Number)));
 int result = 1, threshold = 10;
 while (threshold<=Number)
 {
  threshold *= 10;
  result++;
 }
 return result;
}

CString EnumCounterStr(const int Counter, const int Length)
{
 CString result, lead_zero, counter = IntegerToString(Counter);
 int length = counter.GetLength();
 if (Length>length)
 {
  lead_zero.SetLength(Length-length); lead_zero.Fill('0');
 }
 result = lead_zero + counter;
 return result;
}

CString EnumStr(const CString& Prefix, const int Counter, const CString& Suffix, const unsigned int Length)
{
 CString result, lead_zero, counter = IntegerToString(Counter);
 unsigned int length = Prefix.GetLength()+counter.GetLength()+Suffix.GetLength();
 if (Length>length) { lead_zero.SetLength(Length-length); lead_zero.Fill('0'); }
 result = Prefix + lead_zero + counter + Suffix;
 return result;
}

CString SubStr(const CString& AString, const int FirstPos, const int LastPos)
{
 CString result;
 if (FirstPos > LastPos) return result;
 int first_pos = std::max(std::min(FirstPos,AString.GetLength()-1),0);
 int last_pos = std::max(std::min(LastPos,AString.GetLength()-1),0);
 if (last_pos<first_pos) return result;
 result.SetLength(last_pos-first_pos+1);
 for (int i = first_pos, j = 0; i <= last_pos; i++, j++) { result[j] = AString.GetChar(i); }
 return result;
}

CString ShiftStr(const CString& AString, const int Shift)
{
 CString result;
 if (AString.GetLength()==0) return result;
 if (Shift>0) return SubStr(AString,Shift,AString.GetLength()-1);
 if (Shift<0) if (AString.GetLength()>(-Shift)) return SubStr(AString,-Shift,AString.GetLength()-Shift);
 return result;
}

CString LeftStr(const CString& AString, const int Position)
{
 return SubStr(AString,0,std::min(AString.GetLength(),Position));
}

CString RightStr(const CString& AString, const int Position)
{
 CString result;
 if (AString.GetLength() > 0)
 {
  result = SubStr(AString,Position,std::max(0,AString.GetLength()-1));
 }
 return result;
}

void SplitStr(const CString& AString, const int Position, CString& LString, CString& RString)
{
 LString = LeftStr(AString,Position);
 RString = RightStr(AString,Position);
}

void SplitStr(const CString& AString, const char AChar, CString& LString, CString& RString)
{
 int pos = FirstCharPos(AString,AChar);
 LString = LeftStr(AString,pos-1);
 RString = RightStr(AString,pos+1);
}

void SplitStr(const CString& AString, const int Length, CStringList& SubStrings)
{
 if (Length>0)
 {
  if (AString.GetLength()>Length)
  {
   for (int i=0; i<AString.GetLength(); i+=Length)
   {
    SubStrings.Insert(SubStr(AString,i,i+Length-1));
   }
  }
  else
  {
   SubStrings.Insert(AString);
  }
 }
}

bool StrSplitNumberUnit(const CString& AString, CString& NumberStr, CString& UnitStr)
{
 NumberStr.Clear(); UnitStr.Clear();
 if (AString.IsEmpty()) return false;
 CCharset NUM_CHARS(ALPHABET_FLOAT_NUMBER);
 int pos = 0;
 for (int i=0; i<AString.GetLength(); i++)
 {
  if (' '==AString[i]) continue;
  if (!NUM_CHARS.Isset(AString[i])) { pos = i; break; }
 }
 if (pos)
 {
  CString s1,s2; SplitStr(AString,pos,s1,s2);
  NumberStr = TrimStr2(s1);
  UnitStr = TrimStr2(s2);
 }
 else
 {
  NumberStr = TrimStr2(AString);
 }
 return true;
}

CString JoinStr(const CString& AString, const CString& BString, const char Separator)
{
 CString result = AString;
 if (!AString.IsEmpty() && !BString.IsEmpty())
 {
  if (BString.GetFirstChar()!=Separator)
  {
   result = CheckLastChar(result,Separator);
  }
 }
 result.Append(BString);
 //std::cout<<"join('"<<AString.GetCString()<<"','"<<BString.GetCString()<<"','"<<Separator<<"')='"<<result.GetCString()<<"'"<<std::endl;
 return result;
}

CString FilterStr(const CString& AString, const CCharset& ValidChars, const CCharset& InvalidChars, const bool ValidateUndefined)
{
 CString result(AString);
 int length = 0;
 for (int i = 0; i < AString.GetLength(); i++)
 {
  if (InvalidChars.Isset(result[i])) continue;
  if (ValidChars.Isset(result[i]) || ValidateUndefined) result[length++] = result[i];
 }
 result.SetLength(length);
 return result;
}

CString FilterStr(const CString& AString, const CString& ValidChars, const CString& InvalidChars, const bool ValidateUndefined)
{
 CCharset vc(ValidChars); CCharset ic(InvalidChars);
 return FilterStr(AString,vc,ic,ValidateUndefined);
}

int CountChars(const CString& AString, const char AChar)
{
 int result = 0;
 for (int i = 0; i < AString.GetLength(); i++) if (AChar==AString.GetChar(i)) result++;
 return result;
}

int NextCharPos(const CString& AString, const char AChar, const int Position)
{
 for (int i = Position; i < AString.GetLength(); i++) if (AChar==AString.GetChar(i)) return i;
 return INVALID_INDEX;
}

int PrevCharPos(const CString& AString, const char AChar, const int Position)
{
 for (int i = Position; i > 0; i--)
 {
  if (AChar==AString.GetChar(i)) return i;
 }
 return INVALID_INDEX;
}

int FirstCharPos(const CString& AString, const char AChar)
{
 return NextCharPos(AString,AChar,0);
}

int LastCharPos(const CString& AString, const char AChar)
{
 if (AString.GetLength() > 0)
 {
  return PrevCharPos(AString,AChar,AString.GetLength()-1);
 }
 else return INVALID_INDEX;
}

CString TrimStr(const CString& AString, const char AChar)
{
 int first_pos = 0, last_pos = AString.GetLength()-1;
 for (int i = first_pos; i <= last_pos; i++)
 { if (AChar==AString.GetChar(i)) first_pos++; else break; }
 for (int i = last_pos; i > first_pos; i--)
 { if (AChar==AString.GetChar(i)) last_pos--; else break; }
 return SubStr(AString,first_pos,last_pos);
}

bool IsTabOrSpace(const char AChar)
{
 return (' '==AChar) || ('\t'==AChar);
}

CString TrimStr2(const CString& AString)
{
 int first_pos = 0, last_pos = AString.GetLength()-1;
 for (int i = first_pos; i <= last_pos; i++)
 { if (IsTabOrSpace(AString.GetChar(i))) first_pos++; else break; }
 for (int i = last_pos; i > first_pos; i--)
 { if (IsTabOrSpace(AString.GetChar(i))) last_pos--; else break; }
 return SubStr(AString,first_pos,last_pos);
}

CString LeadStr(const CString& AString, const int RLength)
{
 CString result;
 result.SetLength(std::max(0,RLength-AString.GetLength()));
 result.Fill(' ');
 result.Append(AString);
 return result;
}

CString PadStr(const CString& AString, const int Length, const CString::align_t Align)
{
 if (Length<=AString.GetLength()) return AString;
 CString result; result.Reserve(Length);
 int padding = Length - AString.GetLength();
 int lpad = padding, rpad = 0;
 switch (Align)
 {
  default: case CString::al_none: case CString::al_right: break;
  case CString::al_left: { rpad = padding; lpad = 0; break; }
  case CString::al_center: { rpad = padding/2; lpad = padding-rpad; break; }
  case CString::al_dot:
  {
   int pos =  std::max(FirstCharPos(AString,'.'),FirstCharPos(AString,','));
   if (pos>0) { lpad = padding-pos; rpad = padding-lpad; }
   break;
  }
 }
 if (lpad) result.Append(StringOfChars(' ',lpad));
 result.Append(AString);
 if (rpad) result.Append(StringOfChars(' ',rpad));
 return result;
}

void ParseStr(const CString& AString, const CString& Delimiters, CStringList& SubStrings)
{
 if (Delimiters.GetLength()==0) { SubStrings.Insert(AString); return; }
 if (AString.GetLength()==0) { return; }
 int str_pos = 0, delim_pos = 0;
 CString sub_str;
 while (str_pos<AString.GetLength())
 {
  if (AString.GetChar(str_pos)==Delimiters.GetChar(delim_pos))
  {
   SubStrings.Insert(sub_str);
   sub_str.SetLength(0);
   if (++delim_pos>=Delimiters.GetLength())
   {
    sub_str = SubStr(AString,++str_pos,AString.GetLength()-1);
    break;
  }}
  else sub_str.Append(AString.GetChar(str_pos));
  str_pos++;
 }
 SubStrings.Insert(sub_str);
}

void ParseStr(const CString& AString, const char Delimiter, CStringList& SubStrings)
{
 CString delimiters;
 delimiters.SetLength(CountChars(AString,Delimiter));
 delimiters.Fill(Delimiter);
 ParseStr(AString,delimiters,SubStrings);
}

void ParseStrWithQuotes(const CString& AString, const CString& Delimiters, CStringList& SubStrings)
{
 if (Delimiters.GetLength()==0) { SubStrings.Insert(AString); return; }
 if (AString.GetLength()==0) { return; }
 int str_pos = 0, delim_pos = 0;
 CString sub_str; bool f_quoted = false; char quote_char;
 while (str_pos<AString.GetLength())
 {
  //if (AString.GetChar(str_pos)=='"') f_quoted = !f_quoted;
  if (f_quoted)
  {
   if (AString.GetChar(str_pos)==quote_char) f_quoted = false;
  }
  else
  {
   const char c = AString.GetChar(str_pos);
   if (c=='"' || c=='\'')
   {
    f_quoted = true; quote_char = c;
   }
  }
  if (AString.GetChar(str_pos)==Delimiters.GetChar(delim_pos) && !f_quoted)
  {
   SubStrings.Insert(sub_str);
   sub_str.SetLength(0);
   if (++delim_pos>=Delimiters.GetLength())
   {
    sub_str = SubStr(AString,++str_pos,AString.GetLength()-1);
    break;
  }}
  else sub_str.Append(AString.GetChar(str_pos));
  str_pos++;
 }
 SubStrings.Insert(sub_str);
}

void ParseStrWithQuotes(const CString& AString, const char Delimiter, CStringList& SubStrings)
{
 CString delimiters;
 delimiters.SetLength(CountChars(AString,Delimiter));
 delimiters.Fill(Delimiter);
 ParseStrWithQuotes(AString,delimiters,SubStrings);
}

CString CollectStr(const CStringList& SubStrings, const CString& Delimiters)
{
 CString result;
 int delim_pos = 0; int sub_strIdx = 0;
 bool delim_set, sub_str_set;
 do
 {
  sub_str_set = (sub_strIdx<SubStrings.GetCount());
  delim_set = (delim_pos<Delimiters.GetLength());
  if (sub_str_set) result.Append(SubStrings.GetString(sub_strIdx++));
  if (delim_set) result.Append(Delimiters.GetChar(delim_pos++));
 }
 while (delim_set||sub_str_set);
 return result;
}

CString StripDupChars(const CString& AString, const char AChar)
{
 CString result(AString);
 int length = 0;
 for (int i = 0; i < AString.GetLength(); i++)
 {
  if ((AChar!=AString.GetChar(i))||(AChar!=AString.GetChar(i+1))) result[length++] = result[i];
 }
 result.SetLength(length);
 return result;
}

CString StripDupChars(const CString& AString)
{
 CString result(AString);
 int length = 0;
 for (int i = 0; i < AString.GetLength(); i++)
 {
  if (AString.GetChar(i)!=AString.GetChar(i+1)) result[length++] = result[i];
 }
 result.SetLength(length);
 return result;
}

CString CheckFirstChar(const CString& AString, const char AChar)
{
 CString result;
 if (AChar!=AString.GetFirstChar()) result = CString(AChar) + AString; else result = AString;
 return result;
}

CString CheckLastChar(const CString& AString, const char AChar)
{
 CString result;
 if (AChar!=AString.GetLastChar()) result = AString + AChar; else result = AString;
 return result;
}

int FindStr(const CString& AString, const CString& BString, const int Position)
{
 int result = INVALID_INDEX;
 for (int i = Position, n = ((int)AString.GetLength() - (int)BString.GetLength()); i <= n; i++)
 {
  bool flag = true;
  for (int j = 0, k = i, m = BString.GetLength(); j < m; j++, k++)
  {
   if (AString[k]!=BString[j]) { flag = false; break; }
  }
  if (flag) { result = i; break; }
 }
 return result;
}

CString FindReplaceChar(const CString& AString,
 const char SearchChar, const char ReplaceChar)
{
 CString result = AString;
 for (int i = 0, n = result.GetLength(); i < n; i++)
 {
  if (SearchChar==result[i]) result[i] = ReplaceChar;
 }
 return result;
}

CString FindReplaceStr(const CString& AString,
 const CString& SearchString, const CString& ReplaceString)
{
 CString result = AString;
 do
 {
  int pos = FindStr(result,SearchString);
  if (INVALID_INDEX == pos) break;
  result = LeftStr(result,pos-1)+ReplaceString+RightStr(result,pos+SearchString.GetLength());
 }
 while (true);
 return result;
}

CString FindReplaceStr2(const CString& AString,
 const CString& SearchString, const CString& ReplaceString)
{
 CString result = AString;
 int last_pos = 0;
 do
 {
  int pos = FindStr(result,SearchString,last_pos);
  if (INVALID_INDEX==pos) break;
  // if current position is same as last one, this means that ReplaceString contains SearchString causing infinite loop
  // to avoid this we fast forward past ReplaceString and try again
  if (pos==last_pos) pos = FindStr(result,SearchString,last_pos+ReplaceString.GetLength());
  if (INVALID_INDEX==pos) break;
  last_pos = pos;
  result = LeftStr(result,pos-1) + ReplaceString + RightStr(result,pos + SearchString.GetLength());
 }
 while (true);
 return result;
}

int ParseMemSizeStr(const CString& AString, int& UnitSize, char& UnitChar)
{
 CCharset invalid_chars;
 CCharset valid_number_chars(ALPHABET_NUMBER);
 CCharset valid_suffix_chars("bkmgBKMG");
 CString number_str = FilterStr(AString,valid_number_chars,invalid_chars,false);
 CString suffix_str = FilterStr(AString,valid_suffix_chars,invalid_chars,false);
 valid_suffix_chars.SetAlphabet(suffix_str[0]);
 int result = StringToInteger(number_str);
 UnitSize = 1; UnitChar = 'b';
 if (valid_suffix_chars.Isset('k')||valid_suffix_chars.Isset('K')) { UnitSize = 0x00000400; UnitChar = 'k'; };
 if (valid_suffix_chars.Isset('m')||valid_suffix_chars.Isset('M')) { UnitSize = 0x00010000; UnitChar = 'm'; };
 if (valid_suffix_chars.Isset('g')||valid_suffix_chars.Isset('G')) { UnitSize = 0x40000000; UnitChar = 'g'; };
 return result;
}

int ParseMemSizeStr(const CString& AString)
{
 int unit_size; char unit_char;
 int result = ParseMemSizeStr(AString,unit_size,unit_char);
 result *= unit_size;
 return result;
}

uint64_t ParseMemSizeStr64(const CString& AString, uint64_t& UnitSize, char& UnitChar)
{
 const uint64_t kb = 0x00000000400LL;
 const uint64_t mb = 0x00000100000LL;
 const uint64_t gb = 0x00040000000LL;
 const uint64_t tb = 0x10000000000LL;
 CCharset invalid_chars;
 CCharset valid_number_chars(ALPHABET_NUMBER);
 CCharset valid_suffix_chars("bkmgtBKMGT");
 CString number_str = FilterStr(AString,valid_number_chars,invalid_chars,false);
 CString suffix_str = FilterStr(AString,valid_suffix_chars,invalid_chars,false);
 valid_suffix_chars.SetAlphabet(suffix_str[0]);
 int result = StringToInteger(number_str);
 UnitSize = 1; UnitChar = 'b';
 if (valid_suffix_chars.Isset('k')||valid_suffix_chars.Isset('K')) { UnitSize = kb; UnitChar = 'K'; };
 if (valid_suffix_chars.Isset('m')||valid_suffix_chars.Isset('M')) { UnitSize = mb; UnitChar = 'M'; };
 if (valid_suffix_chars.Isset('g')||valid_suffix_chars.Isset('G')) { UnitSize = gb; UnitChar = 'G'; };
 if (valid_suffix_chars.Isset('t')||valid_suffix_chars.Isset('T')) { UnitSize = tb; UnitChar = 'T'; };
 return result;
}

uint64_t ParseMemSizeStr64(const CString& AString)
{
 uint64_t unit_size; char unit_char;
 uint64_t result = ParseMemSizeStr64(AString,unit_size,unit_char);
 result *= unit_size;
 return result;
}

int GuessStr(const CString& AString, const CStringList& Variants, CString& Guessed, const bool TryFuzzy)
{
 CString source = AString;
 Guessed = "";
 // try to match variants exactly
 for (int i = 0, n = Variants.GetCount(); i < n; i++)
 {
  if (Variants[i]==source)
  {
   Guessed = Variants[i];
   return i;
  }
 }
 if (!TryFuzzy) return INVALID_INDEX;
 // if none succeed, try to match fuzzy
 int result = -1; unsigned int max_match = 0;
 CCharHistogram freq_a,freq_v;
 freq_a.Insert(source);
 for (int i = 0, n = Variants.GetCount(); i < n; i++)
 {
  freq_v.Reset(); freq_v.Insert(Variants[i]);
  unsigned int match = 0;
  for (int j = 0; j < CHARSET_SIZE; j++) { match += freq_a.GetAt(j)*freq_v.GetAt(j); }
  if ((match>0)&&(match==max_match)) return INVALID_INDEX;
  if (match>max_match) { result = i; max_match = match; }
 }
 if (result>=0) Guessed = Variants[result];
 // if none succeed, return -1
 return result;
}

int GuessStr(const CString& AString, const CString& Variants, CString& Guessed, const char Delimiter, const bool TryFuzzy)
{
 CStringList varlist;
 ParseStr(Variants,Delimiter,varlist);
 return GuessStr(AString,varlist,Guessed,TryFuzzy);
}

CString VariantStr(const int Index, const CString& Variants, const char Delimiter)
{
 CStringList variants;
 ParseStr(Variants,Delimiter,variants);
 CString result = variants.GetString(Index);
 return result;
}

CString MemSizeStr(const uint64_t Value, uint64_t& UnitSize, CString& UnitSuffix, const CString Spacer)
{
 const uint64_t kb = 0x00000000400LL;
 const uint64_t mb = 0x00000100000LL;
 const uint64_t gb = 0x00040000000LL;
 const uint64_t tb = 0x10000000000LL;
 const CString format = "%lg";
 if (Value < kb)
 {
  UnitSize = 1; UnitSuffix = "b";
  return Int64ToString(Value);
 }
 else if (Value < mb)
 {
  UnitSize = kb; UnitSuffix = "Kb";
  return FloatToString((double)Value/(double)kb,format);
 }
 else if (Value < gb)
 {
  UnitSize = mb; UnitSuffix = "Mb";
  return FloatToString((double)Value/(double)mb,format);
 }
 else if (Value < tb)
 {
  UnitSize = gb; UnitSuffix = "Gb";
  return FloatToString((double)Value/(double)gb,format);
 }
 else
 {
  UnitSize = tb; UnitSuffix = "Tb";
  return FloatToString((double)Value/(double)tb,format);
 }
 return "";
}

CString MemSizeStr(const uint64_t Value, const CString Spacer)
{
 uint64_t unit_size; CString unit_suffix;
 return MemSizeStr(Value,unit_size,unit_suffix).Append(Spacer).Append(unit_suffix);
}

CString SI_UnitStr(const double Value, double& UnitSize, CString& UnitPrefix, CString& UnitSymbol)
{
 int m = (int)floor(log10(Value)); CString format = "%lg";
 if (m<0)
 {
  if (m<=-24) { UnitSize = 1e-24; UnitPrefix = "yocto"; UnitSymbol = "y"; return FloatToString(Value/UnitSize,format); }
  else if (m<=-21) { UnitSize = 1e-21; UnitPrefix = "zepto"; UnitSymbol = "z"; return FloatToString(Value/UnitSize,format); }
  else if (m<=-18) { UnitSize = 1e-18; UnitPrefix = "atto"; UnitSymbol = "a"; return FloatToString(Value/UnitSize,format); }
  else if (m<=-15) { UnitSize = 1e-15; UnitPrefix = "femto"; UnitSymbol = format; return FloatToString(Value/UnitSize,format); }
  else if (m<=-9) { UnitSize = 1e-9; UnitPrefix = "pico"; UnitSymbol = "p"; return FloatToString(Value/UnitSize,format); }
  else if (m<=-6) { UnitSize = 1e-6; UnitPrefix = "nano"; UnitSymbol = "n"; return FloatToString(Value/UnitSize,format);  }
  else if (m<=-3) { UnitSize = 1e-3; UnitPrefix = "micro"; UnitSymbol = "mu"; return FloatToString(Value/UnitSize,format);  }
  else if (m<=-2) { UnitSize = 1e-2; UnitPrefix = "milli"; UnitSymbol = "m"; return FloatToString(Value/UnitSize,format); }
  else if (m<=-1) { UnitSize = 1e-1; UnitPrefix = "deci"; UnitSymbol = "d"; return FloatToString(Value/UnitSize,format); }
 }
 if (m>0)
 {
  if (m>=24) { UnitSize = 1e24; UnitPrefix = "yotta"; UnitSymbol = "Y"; return FloatToString(Value/UnitSize,format); }
  else if (m>=21) { UnitSize = 1e21; UnitPrefix = "zetta"; UnitSymbol = "Z"; return FloatToString(Value/UnitSize,format); }
  else if (m>=18) { UnitSize = 1e18; UnitPrefix = "exa"; UnitSymbol = "E"; return FloatToString(Value/UnitSize,format); }
  else if (m>=15) { UnitSize = 1e15; UnitPrefix = "peta"; UnitSymbol = "P"; return FloatToString(Value/UnitSize,format); }
  else if (m>=12) { UnitSize = 1e12; UnitPrefix = "tera"; UnitSymbol = "T"; return FloatToString(Value/UnitSize,format); }
  else if (m>=9) { UnitSize = 1e9; UnitPrefix = "giga"; UnitSymbol = "G"; return FloatToString(Value/UnitSize,format); }
  else if (m>=6) { UnitSize = 1e6; UnitPrefix = "mega"; UnitSymbol = "M"; return FloatToString(Value/UnitSize,format); }
  else if (m>=3) { UnitSize = 1e3; UnitPrefix = "kilo"; UnitSymbol = "k"; return FloatToString(Value/UnitSize,format); }
  else if (m>=2) { UnitSize = 1e2; UnitPrefix = "hecto"; UnitSymbol = "h"; return FloatToString(Value/UnitSize,format); }
  else if (m>=1) { UnitSize = 1e1; UnitPrefix = "deca"; UnitSymbol = "da"; return FloatToString(Value/UnitSize,format); }
 }
 UnitSize = 1; UnitPrefix = ""; UnitSymbol = ""; return FloatToString(Value,format);
}

CString SI_UnitStr(const double Value)
{
 double unit_size; CString unit_prefix; CString unit_symbol;
 return SI_UnitStr(Value,unit_size,unit_prefix,unit_symbol).Append(" ").Append(unit_symbol);
}

bool IsQuoted(const CString& AString)
{
 int len = AString.GetLength();
 char fc = AString.GetFirstChar();
 char lc = AString.GetLastChar();
 bool result = ((len>=2)&&(((fc=='\"')&&(lc=='\"'))||((fc=='\'')&&(lc=='\''))));
 return result;
}

CString QuoteStr(const CString& AString)
{
 if (!IsQuoted(AString)) return "\""+AString+"\"";
 else return AString;
}

CString UnquoteStr(const CString& AString)
{
 if (IsQuoted(AString)) return SubStr(AString,1,AString.GetLength()-2);
 else return AString;
}

CString ShieldSpaces(const CString& AString)
{
 CString result; bool shield = false;
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  if (shield)
  {
   shield = false;
   result.Append(AString[i]);
  }
  else
  {
   if ('\\'==AString[i]) shield = true;
   else if (' '==AString[i])
   {
    result.Append('\\');
   }
   result.Append(AString[i]);
  }
 }
 return result;
}

CString UnshieldSpaces(const CString& AString)
{
 CString result; bool shield = false;
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  if (shield)
  {
   shield = false;
   if (' '!=AString[i]) result.Append('\\');
   result.Append(AString[i]);
  }
  else
  {
   if ('\\'==AString[i]) shield = true;
   else result.Append(AString[i]);
  }
 }
 if (shield) result.Append('\\');
 return result;
}

CString ShieldChars(const CString& AString, const CString& Chars)
{
 if (Chars.IsEmpty()) return AString;
 CCharset esc_chars(Chars);
 CString result; bool shield = false;
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  if (shield)
  {
   shield = false;
   if (!esc_chars.Isset(AString[i]))
   {
    result.Append('\\');
   }
   result.Append(AString[i]);
  }
  else
  {
   if ('\\'==AString[i]) shield = true;
   else if (esc_chars.Isset(AString[i]))
   {
    result.Append('\\');
   }
   result.Append(AString[i]);
  }
 }
 return result;
}

CString UnshieldChars(const CString& AString, const CString& Chars)
{
 if (Chars.IsEmpty()) return AString;
 CCharset esc_chars(Chars);
 CString result; bool shield = false;
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  if (shield)
  {
   shield = false;
   if (!esc_chars.Isset(AString[i])) result.Append('\\');
   result.Append(AString[i]);
  }
  else
  {
   if ('\\'==AString[i]) shield = true;
   else result.Append(AString[i]);
  }
 }
 if (shield) result.Append('\\');
 return result;
}

CString ReplaceQuotedChars(const CString& AString, const char QuoteChar, const char FindChar, const char ReplaceChar)
{
 CString result = AString;
 bool replace = false;
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  char c = result[i];
  if (QuoteChar==c)
  {
   replace = !replace;
   continue;
  }
  if ((FindChar==c) && replace)
  {
   result[i] = ReplaceChar;
  }
 }
 return result;
}

CString ReverseStr(const CString& AString)
{
 CString result(AString);
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  result[i] = AString[n-i-1];
 }
 return result;
}

bool StrBeginsWith(const CString& AString, const CString& StartChars, bool IgnoreSpaces)
{
 if (IgnoreSpaces)
 {
  CString s = TrimStr2(AString);
  return (LeftStr(s,StartChars.GetLength()-1)==StartChars);
 }
 return (LeftStr(AString,StartChars.GetLength()-1)==StartChars);
}

bool StrContainsAny(const CString& AString, const CString& Chars)
{
 if (AString.IsEmpty()) return false;
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  for (int j = 0, m = Chars.GetLength(); j < m; j++)
  {
   if (AString[i]==Chars[j]) return true;
  }
 }
 return false;
}

bool StrContainsAll(const CString& AString, const CString& Chars)
{
 if (AString.IsEmpty()) return false;
 bool f_char[Chars.GetLength()]; int n_char = 0;
 for (int j = 0, m = Chars.GetLength(); j < m; j++) f_char[j] = false;
 //
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  for (int j = 0, m = Chars.GetLength(); j < m; j++)
  {
   if (AString[i]==Chars[j])
   {
    if (!f_char[j]) { f_char[j] = true; n_char++; break; }
   }
  }
  //
  if (Chars.GetLength()==n_char) return true;
 }
 return false;
}

bool StrContainsOnly(const CString& AString, const CString& Chars)
{
 if (AString.IsEmpty()) return false;
 for (int i = 0, n = AString.GetLength(); i < n; i++)
 {
  bool f_char = true;
  for (int j = 0, m = Chars.GetLength(); j < m; j++)
  {
   if (AString[i]==Chars[j]) { f_char = false; break; }
  }
  if (f_char) return false;
 }
 return true;
}

int StrGetNumBase(const CString& AString, CString *UnprefixedString)
{
 CString s = TrimStr(AString,' ');
 int base = 0;
 // tell base from prefix
 if (StrBeginsWith(s,"0x",false)||StrBeginsWith(s,"0X",false))
 {
  s = RightStr(s,2); base = 16;
 }
 else if (StrBeginsWith(s,"0b",false)||StrBeginsWith(s,"0B",false))
 {
  s = RightStr(s,2); base = 2;
 }
 else if (StrBeginsWith(s,"b",false)||StrBeginsWith(s,"B",false))
 {
  s = RightStr(AString,1); base = 2;
 }
 else if (StrBeginsWith(s,"0o",false)||StrBeginsWith(s,"0O",false))
 {
  s = RightStr(AString,2); base = 8;
 }
 else if (StrBeginsWith(s,"o",false)||StrBeginsWith(s,"o",false))
 {
  s = RightStr(AString,1); base = 8;
 }
 /*
 else if (StrBeginsWith(s,"o",false)||StrBeginsWith(s,"O",false))
 {
  s = RightStr(AString,1); base = 8;
 }
 else if (StrBeginsWith(s,"0",false))
 {
  s = AString; base = 8;
 }
 */
 /*
 else
 {
  s = AString; base = 10;
 }
 */
 //std::cout<<"auto base = "<<base<<std::endl;
 // tell base from content
 if (0==base)
 {
  if (StrContainsOnly(s,ALPHABET_INTEGER_NUMBER)) base = 10;
  else if (StrContainsOnly(s,ALPHABET_BIN_NUMBER)) base = 2;
  else if (StrContainsOnly(s,ALPHABET_OCT_NUMBER)) base = 8;
  else if (StrContainsOnly(s,ALPHABET_HEX_NUMBER)) base = 16;
 }
 // validate base
 /*
 switch (base)
 {
  default: break;
  case 2: { if (!StrContainsOnly(s,ALPHABET_BIN_NUMBER)) base = 0; break; }
  case 8: { if (!StrContainsOnly(s,ALPHABET_OCT_NUMBER)) base = 0; break; }
  case 10: { if (!StrContainsOnly(s,ALPHABET_INTEGER_NUMBER)) base = 0; break; }
  case 16: { if (!StrContainsOnly(s,ALPHABET_HEX_NUMBER)) base = 0; break; }
 }
 */
 //
 if (0!=UnprefixedString) UnprefixedString->Assign(s);
 return base;
}

//------------------------------------------------------------------------------
