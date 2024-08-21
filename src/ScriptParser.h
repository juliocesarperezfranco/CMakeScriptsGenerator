#ifndef SCRIPTPARSER_H
#define SCRIPTPARSER_H

#pragma once

#include <ScriptInfo.h>

#include <wx/xml/xml.h>

class ScriptParser
{
  public:
    ScriptParser(const std::string& inputFile);
    virtual ~ScriptParser();

    void ParseScript();
    void ParseConfigurationNode(wxXmlNode* configurationNode);
    void GenerateReport(const std::string& outputFile = "");
    void GenerateScript(const std::string& outputFile = "");

  private:
    std::string m_inputFile;
    ScriptInfo m_script;
};

#endif // SCRIPTPARSER_H