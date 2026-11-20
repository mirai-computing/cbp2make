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
#include "stlgpm.h"
#include "stlfutils.h"
#include <iostream>
//------------------------------------------------------------------------------

CGenericProcessingMachine::CGenericProcessingMachine(void)
{
 m_FileConfiguration.Clear();
 m_ParameterStringConfiguration.Clear();
 //m_ParameterString.Clear();
 m_InputFileList.Clear();
 m_OutputFileList.Clear();
 m_FileNameLength = GPM_DEFAULT_FILENAME_LENGTH;
 m_FileIndex = 0;
 m_AliasesEnabled = false;
 m_VerboseMode = false;
 m_QuietMode = false;
 m_HelpMode = false;
 m_SaveOutputList = true;
 m_MergedConfiguration = false;
 m_Initialized = false;
}

CGenericProcessingMachine::~CGenericProcessingMachine(void)
{
 //
}

bool CGenericProcessingMachine::Initialize(void)
{
 CreateConfiguration();
 m_Initialized = PSC().ProcessParameters(m_ParameterString);
 if (!m_Initialized) return false; // bad parameters, abort initialization early
 m_Initialized &= Configure(ConfigurationName());
 m_FileNameLength = 12;
 return m_Initialized;
}

bool CGenericProcessingMachine::Initialize(int argc, char * argv[])
{
 PS().SetParameters(argc,argv);
 m_MergedConfiguration = false;
 return Initialize();
}

bool CGenericProcessingMachine::Initialize(const CParameterString& Parameters)
{
 PS().SetParameters(Parameters);
 m_MergedConfiguration = false;
 return Initialize();
}

bool CGenericProcessingMachine::Initialize(
 CParameterString& ParameterString,
 CParameterStringConfiguration& ParameterConfig,
 CConfiguration& FileConfig)
{
 m_ParameterString.Assign(ParameterString);
 m_ParameterStringConfiguration.Assign(ParameterConfig);
 //m_ParameterStringConfiguration.print(std::cout);
 CreateConfiguration();
 //m_ParameterStringConfiguration.print(std::cout);
 PSC().ProcessParameters(m_ParameterString);
 //m_ParameterStringConfiguration.print(std::cout);
 m_FileConfiguration.Merge(FileConfig,false);
 m_MergedConfiguration = true;
 m_Initialized = Configure(ConfigurationName());
 return m_Initialized;
}

void CGenericProcessingMachine::DisplayHelpMessage(void)
{
 std::cout<<
 "Generic parameters: (some parameters may be inapplicable for a particular software)\n\n"
 "\t-in <file>\t: input file/list file name\n"
 "\t-out <file>\t: output file/list fiel name\n"
 "\t-indir <dir>\t: input directory\n"
 "\t-outdir <dir>\t: output directory\n"
 "\t-cfg <file>\t: configuration file\n"
 "\t-list\t\t: run in batch mode\n"
 "\t-cont <number>\t: continue batch from n-th step\n"
 "\t--debug <level>\t: show debug messages up to said verbosity level"
 "\t--quiet\t\t: do not show any messages\n"
 "\t--verbose\t: show all messages\n"
 "\t--help\t\t: show help message\n\n"
 "Meta characters:\n\n\t<> substitution [] optional parameter {} group | variant;\n\n"
 ;
}

void CGenericProcessingMachine::CreateConfiguration(void)
{
 PSC().InsertStringVariable(GPM_VAR_NAME_IN);
 PSC().InsertStringVariable(GPM_VAR_NAME_OUT);
 PSC().InsertFlagVariable(GPM_VAR_NAME_LIST);
 PSC().InsertStringVariable(GPM_VAR_NAME_CFG);
 PSC().InsertStringVariable(GPM_VAR_NAME_INDIR);
 PSC().InsertStringVariable(GPM_VAR_NAME_OUTDIR);
 PSC().InsertFlagVariable(GPM_VAR_NAME_HELP);
 PSC().InsertFlagVariable(GPM_VAR_NAME_VERBOSE);
 PSC().InsertFlagVariable(GPM_VAR_NAME_QUIET);
 PSC().InsertIntegerVariable(GPM_VAR_NAME_DEBUG,0);
 if (m_AliasesEnabled)
 {
  PSC().InsertFlagVariable(GPM_VAR_NAME_HELP_ALIAS);
  PSC().InsertFlagVariable(GPM_VAR_NAME_VERBOSE_ALIAS);
  PSC().InsertFlagVariable(GPM_VAR_NAME_QUIET_ALIAS);
 }
}

CString CGenericProcessingMachine::DefaultConfigurationName(void)
{
 return ChangeFileExt(ExtractFileName(PS().Parameter(0)),".cfg");
}

CString CGenericProcessingMachine::ConfigurationName(void)
{
 if (PSC().VarDefined(GPM_VAR_NAME_CFG))
 {
  return PSC().VarNamed(GPM_VAR_NAME_CFG).GetString();
 }
 else
 {
  return DefaultConfigurationName();
 }
}

bool CGenericProcessingMachine::Configure(const CString& FileName)
{
 bool result = true;
 //
 if (m_AliasesEnabled)
 {
  m_VerboseMode = PSC().VarDefined(GPM_VAR_NAME_VERBOSE_ALIAS);
  m_QuietMode = PSC().VarDefined(GPM_VAR_NAME_QUIET_ALIAS);
  m_HelpMode = PSC().VarDefined(GPM_VAR_NAME_HELP_ALIAS);
 }
 else
 {
  m_VerboseMode = PSC().VarDefined(GPM_VAR_NAME_VERBOSE);
  m_QuietMode = PSC().VarDefined(GPM_VAR_NAME_QUIET);
  m_HelpMode = PSC().VarDefined(GPM_VAR_NAME_HELP);
 }
 m_DebugLevel = PSC().VarNamed(GPM_VAR_NAME_DEBUG).GetInteger();
 //PSC().ProcessParameters(m_ParameterString);
 if (!m_MergedConfiguration)
 {
  if ((FileName.GetLength()>0)&&(FileExists(FileName)))
  {
   m_ConfigurationFileName = FileName;
   result = CFG().LoadFromFile(FileName);
  }
  else
  {
   result = false;
  }
 }
 if (PSC().VarDefined(GPM_VAR_NAME_LIST))
 {
  ILST().Clear();
  ILST().LoadFromFile(PSC().VarNamed(GPM_VAR_NAME_IN).GetString());
  ILST().RemoveEmpty();
 }
 else if (PSC().VarDefined(GPM_VAR_NAME_IN))
 {
  ILST().Clear();
  ILST().Insert(PSC().VarNamed(GPM_VAR_NAME_IN).GetString());
 }
 if (PSC().VarDefined(GPM_VAR_NAME_INDIR))
 {
  m_InputDirectory = CheckLastChar(PSC().VarNamed(GPM_VAR_NAME_INDIR).GetString(),'/');
  PSC().VarNamed(GPM_VAR_NAME_INDIR).SetString(m_InputDirectory);
 }
 if (PSC().VarDefined(GPM_VAR_NAME_OUTDIR))
 {
  m_OutputDirectory = CheckLastChar(PSC().VarNamed(GPM_VAR_NAME_OUTDIR).GetString(),'/');
  PSC().VarNamed(GPM_VAR_NAME_OUTDIR).SetString(m_OutputDirectory);
 }
 m_DoRenameOutputFile = ((!PSC().VarDefined(GPM_VAR_NAME_LIST))&&(PSC().VarDefined(GPM_VAR_NAME_OUT)));
 m_DoCreateOutputList = m_SaveOutputList && ((PSC().VarDefined(GPM_VAR_NAME_LIST))&&(PSC().VarDefined(GPM_VAR_NAME_OUT)));
 return result;
}

bool CGenericProcessingMachine::Reconfigure(void)
{
 return CGenericProcessingMachine::Configure(m_ConfigurationFileName);
}

int CGenericProcessingMachine::SetFileNameLength(const int FileNameLength)
{
 m_FileNameLength = std::max(FileNameLength,1);
 return m_FileNameLength;
}

bool CGenericProcessingMachine::CanContinue(void)
{
 return false;
}

bool CGenericProcessingMachine::LoadState(void)
{
 return false;
}

bool CGenericProcessingMachine::SaveState(void)
{
 return false;
}

CString CGenericProcessingMachine::TargetName(const int FileIndex, const CString& SourceFileName)
{
 return EnumStr("",FileIndex,".out",m_FileNameLength);
}

bool CGenericProcessingMachine::ProcessFile(const CString& SourceFileName, CString& TargetFileName)
{
 // override this function //
 return true;
}

bool CGenericProcessingMachine::PreProcess(void)
{
 // override this function //
 return true;
}

CString CGenericProcessingMachine::GetSourceFilePath(const int Index)
{
 return JoinPaths(m_InputDirectory, ILST().GetString(Index));
}

CString CGenericProcessingMachine::GetTargetFileName(const int Index)
{
 CString target_name = TargetName(Index, ILST().GetString(Index));
 if (m_DoRenameOutputFile)
 {
  target_name = PSC().VarNamed(GPM_VAR_NAME_OUT).GetString();
 }
 if (!m_OutputDirectory.IsEmpty())
 {
  target_name = ExtractFileName(target_name);
 }
 return target_name;
}

CString CGenericProcessingMachine::GetTargetFilePath(const int Index)
{
 return JoinPaths(m_OutputDirectory, GetTargetFileName(Index));
}

bool CGenericProcessingMachine::Run(void)
{
 if (CanContinue())
 {
  if (!LoadState())
  {
   return false;
  }
 }
 if (!PreProcess())
 {
  return false;
 }
 //
 bool result = true;
 int i_first = 0;
 if (CanContinue())
 {
  i_first = PSC().VarNamed(GPM_VAR_NAME_CONT).GetInteger();
 }
 //if ((ILST().GetCount()>1)||(!PSC().VarDefined(GPM_VAR_NAME_OUT)))
 for (int i = i_first; i < ILST().GetCount(); i++)
 {
  m_FileIndex = i;
  if (ILST().GetString(i).GetLength()==0) continue;
  m_SourceFileName = GetSourceFilePath(i);
  m_TargetFileName = GetTargetFilePath(i);
  result = result && ProcessFile(m_SourceFileName,m_TargetFileName);
  if (!m_TargetFileName.IsEmpty())
  {
   OLST().Insert(GetTargetFileName(i));
  }
  if (CanContinue())
  {
   SaveState();
  }
 }
 if (m_DoCreateOutputList)
 {
  OLST().SaveToFile(PSC().VarNamed(GPM_VAR_NAME_OUT).GetString());
 }
 //
 result = result && PostProcess();
 return result;
}

bool CGenericProcessingMachine::PostProcess(void)
{
 // override this function //
 return true;
}

bool CGenericProcessingMachine::Finalize(void)
{
 // override this function //
 return true;
}

/*
CGenericProcessingMachine::CGenericProcessingMachine(void)
{
}

CGenericProcessingMachine::~CGenericProcessingMachine(void)
{
}
*/

//------------------------------------------------------------------------------
