#include "ScriptInfo.h"
#include "ConfigurationInfo.h"
#include "VariableInfo.h"

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/cmdline.h>
#include <wx/filename.h>
#include <wx/vector.h>
#include <wx/xml/xml.h>

#include "ScriptParser.h"

class CommandApp: public wxAppConsole
{
public:
  virtual void OnInitCmdLine(wxCmdLineParser& parser)override;
  virtual bool OnCmdLineParsed(wxCmdLineParser& parser)override;
  virtual int OnRun()override;

private:
  std::string m_inputFile;
  std::string m_outputFile;
  ScriptInfo  m_buildInfo;
};

IMPLEMENT_APP_CONSOLE(CommandApp)

void CommandApp::OnInitCmdLine(wxCmdLineParser& parser)
{
  wxAppConsole::OnInitCmdLine(parser);
  parser.AddParam("file_name");

  parser.AddUsageText("\nCommand:");
  parser.AddUsageText("\nFileName.xml");
}

bool CommandApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
  auto inputFile = parser.GetParam();

  this->m_inputFile = "";

  if (wxFileExists(inputFile) == true)
  {
    this->m_inputFile = inputFile;
  }

  return wxAppConsole::OnCmdLineParsed(parser);
}

int CommandApp::OnRun()
{
  ScriptParser sp(this->m_inputFile);
  sp.ParseScript();
  sp.GenerateReport();
  sp.GenerateScript("./cmake_script.bat");
  return 0;
}
