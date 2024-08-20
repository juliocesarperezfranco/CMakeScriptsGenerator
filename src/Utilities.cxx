#include "Utilities.h"

const bool IsValid(const ScriptInfo& scriptInfo)
{
  if(scriptInfo.name.empty() || scriptInfo.configurations.empty())
  {
    return false;
  }
  return true;
}

const bool IsValid(const ConfigurationInfo& configurationInfo)
{
  if (configurationInfo.generator.empty() || configurationInfo.sourceDir.empty() || configurationInfo.binaryDir.empty() || configurationInfo.enabled == false)
  {
    return false;
  }
  return true;
}

const bool IsValid(const EnvironmentInfo& environmentInfo)
{
  return false;
}

const bool IsValid(const VariableInfo& variableInfo)
{
  return false;
}

void Print(const std::string& message, const bool newLine)
{
  std::cout << message;
  if (newLine)
  {
    std::cout << "\n";
  }
}

void PrintVariable(const std::string& variableName, const std::string& value)
{
  std::cout << variableName + "\t= " + value << "\n";
}
