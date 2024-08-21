#ifndef VARIABLEINFO_H
#define VARIABLEINFO_H

#pragma once

#include <string>

struct VariableInfo
{
  bool enabled = "true";
  std::string name = "";
  std::string type = "";
  std::string value = "";
  std::string description = "";
};

#endif // VARIABLEINFO_H