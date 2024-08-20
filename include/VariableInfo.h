#ifndef VARIABLEINFO_H
#define VARIABLEINFO_H

#pragma once

#include <string>

struct VariableInfo
{
  std::string name = "";
  std::string type = "";
  std::string value = "";
  std::string description = "";
  std::string enabled = "true";
};

#endif // VARIABLEINFO_H