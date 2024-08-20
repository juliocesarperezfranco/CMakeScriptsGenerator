#include "ScriptParser.h"

#include <wx/log.h>

ScriptParser::ScriptParser(const std::string& inputFile)
{
  wxLogDebug(std::string("ScriptParser::ScriptParser(" + inputFile + ")").c_str());
}

ScriptParser::~ScriptParser()
{
  wxLogDebug("ScriptParser::~ScriptParser()");
}

void ScriptParser::Parse()
{
  wxLogDebug("ScriptParser::Parse()");
}
