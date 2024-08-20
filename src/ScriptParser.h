#ifndef SCRIPTPARSER_H
#define SCRIPTPARSER_H

#pragma once

#include <ScriptInfo.h>

class ScriptParser
{
  public:
    ScriptParser(const std::string& inputFile);
    virtual ~ScriptParser();

    void Parse();
    void GenerateReport(const std::string& outputFile = "");

  private:
    std::string m_inputFile;
    ScriptInfo m_script;
};

#endif // SCRIPTPARSER_H