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
#ifndef STL_GPM_H
#define STL_GPM_H
//------------------------------------------------------------------------------
#include "stlconfig.h"
//------------------------------------------------------------------------------

class CGenericProcessingMachine
{
 protected:
  CString m_ConfigurationFileName;
  CConfiguration m_FileConfiguration;
  CParameterStringConfiguration m_ParameterStringConfiguration;
  CParameterString m_ParameterString;
  CStringList m_InputFileList;
  CStringList m_OutputFileList;
  CString m_InputDirectory;
  CString m_OutputDirectory;
  int m_FileIndex;
  bool m_AliasesEnabled;
  int m_FileNameLength;
  bool m_VerboseMode;
  bool m_QuietMode;
  bool m_HelpMode;
  int m_DebugLevel;
  bool m_SaveOutputList;
  bool m_MergedConfiguration;
  bool m_Initialized;
  bool m_DoRenameOutputFile;
  bool m_DoCreateOutputList;
  CString m_SourceFileName;
  CString m_TargetFileName;
  bool m_ProcessingStatus;
 protected:
  virtual bool Initialize(void);
  virtual CString GetSourceFilePath(const int Index);
  virtual CString GetTargetFileName(const int Index);
  virtual CString GetTargetFilePath(const int Index);
 public:
  virtual bool Initialize(int argc, char * argv[]);
  virtual bool Initialize(const CParameterString& Parameters);
  virtual bool Initialize(CParameterString& ParameterString,
                          CParameterStringConfiguration& ParameterConfig,
                          CConfiguration& FileConfig);
  virtual void DisplayHelpMessage(void);
  virtual void CreateConfiguration(void);
  CString DefaultConfigurationName(void);
  virtual CString ConfigurationName(void);
  virtual bool Configure(const CString& FileName);
  virtual bool Reconfigure(void);
  int GetFileNameLength(void) const { return m_FileNameLength; }
  int SetFileNameLength(const int FileNameLength);
  int FileIndex(void) const { return m_FileIndex; }
  virtual bool CanContinue(void);
  virtual bool LoadState(void);
  virtual bool SaveState(void);
  virtual CString TargetName(const int FileIndex, const CString& SourceFileName);
  virtual bool ProcessFile(const CString& SourceFileName, CString& TargetFileName);
  virtual bool PreProcess(void);
  virtual bool Run(void);
  virtual bool PostProcess(void);
  virtual bool Finalize(void);
  virtual void Print(std::ostream& out) { };
 public:
  bool& AliasesEnabled(void) { return m_AliasesEnabled; }
  bool& BeVerbose(void) { return m_VerboseMode; }
  bool& BeQuiet(void) { return m_QuietMode; }
  bool& DoShowHelp(void) { return m_HelpMode; }
  bool DebugMode(void) const { return 0!=m_DebugLevel; }
  int& DebugLevel(void) { return m_DebugLevel; }
  CConfiguration& CFG(void) { return m_FileConfiguration; }
  CParameterStringConfiguration& PSC(void) { return m_ParameterStringConfiguration; }
  CParameterString& PS(void) { return m_ParameterString; }
  CStringList& ILST(void) { return m_InputFileList; };
  CStringList& OLST(void) { return m_OutputFileList; };
 public:
  CGenericProcessingMachine(void);
  virtual ~CGenericProcessingMachine(void);
};

#ifndef GPM_DEFAULT_FILENAME_LENGTH
#define GPM_DEFAULT_FILENAME_LENGTH 12
#endif

static const char* GPM_VAR_NAME_IN   = "-in";
static const char* GPM_VAR_NAME_OUT  = "-out";
static const char* GPM_VAR_NAME_LIST = "-list";
static const char* GPM_VAR_NAME_CONT = "-cont";
static const char* GPM_VAR_NAME_CFG  = "-cfg";
static const char* GPM_VAR_NAME_INDIR   = "-indir";
static const char* GPM_VAR_NAME_OUTDIR  = "-outdir";
static const char* GPM_VAR_NAME_HELP   = "--help";
static const char* GPM_VAR_NAME_VERBOSE = "--verbose";
static const char* GPM_VAR_NAME_QUIET = "--quiet";
static const char* GPM_VAR_NAME_DEBUG = "--debug";
static const char* GPM_VAR_NAME_HELP_ALIAS   = "-h";
static const char* GPM_VAR_NAME_VERBOSE_ALIAS = "-v";
static const char* GPM_VAR_NAME_QUIET_ALIAS = "-q";

#endif
//------------------------------------------------------------------------------
