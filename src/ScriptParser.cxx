#include "ScriptParser.h"

#include <wx/log.h>
#include <wx/file.h>
#include <fstream>

#include "Utilities.h"

ScriptParser::ScriptParser(const std::string& inputFile):
  m_inputFile(inputFile)
{
  wxLogDebug(std::string("ScriptParser::ScriptParser(" + inputFile + ")").c_str());
}

ScriptParser::~ScriptParser()
{
  wxLogDebug("ScriptParser::~ScriptParser()");
}

void ScriptParser::ParseScript()
{
  wxLogDebug("ScriptParser::Parse()");
  if (wxFileExists(this->m_inputFile) == false)
  {
    std::string m = "Error: Archivo " + this->m_inputFile + " no exnontrado.";
    wxLogDebug(m.c_str());
    return;
  }

  auto doc = new wxXmlDocument(this->m_inputFile);
  auto rootNode = doc->GetRoot();

  if (rootNode->GetName().Upper() == "CMAKE_SCRIPT_GENERATOR")
  {
    this->m_script.name = rootNode->GetAttribute("name", "");
    this->m_script.version = rootNode->GetAttribute("version", "0.0.0");
    this->m_script.description = rootNode->GetAttribute("description", "");

    auto rootNodeChildNodes = rootNode->GetChildren();
    while (rootNodeChildNodes)
    {
      if (rootNodeChildNodes->GetName().Upper() == "CONFIGURATIONS")
      {
        auto parseConfigurationNode = rootNodeChildNodes->GetChildren();
        if (parseConfigurationNode->GetName().Upper() == "CONFIGURATION")
        {
          ParseConfigurationNode(parseConfigurationNode);
        }
        parseConfigurationNode = parseConfigurationNode->GetNext();
      }
      rootNodeChildNodes = rootNodeChildNodes->GetNext();
    }
  }

  delete doc;

}

void ScriptParser::ParseConfigurationNode(wxXmlNode* configurationNode)
{
  wxLogDebug(std::string("ScriptParser::ParseConfigurationNode(" + configurationNode->GetName() + ")").c_str());
  ConfigurationInfo configInfo;
  configInfo.name = configurationNode->GetAttribute("name", "");
  configInfo.sourceDir = configurationNode->GetAttribute("source_dir", "");
  configInfo.binaryDir = configurationNode->GetAttribute("binary_dir", "");
  configInfo.generator = configurationNode->GetAttribute("generator", "");
  configInfo.architecture = configurationNode->GetAttribute("architecture", "");
  configInfo.enabled = (configurationNode->GetAttribute("enabled", "true").Upper() == "TRUE") ? true : false; ;
  configInfo.name = configurationNode->GetAttribute("name", "");

  auto configurationsNodes = configurationNode->GetChildren();
  if(configurationsNodes != nullptr)
  {
    if (configurationsNodes->GetName().Upper() == "VARIABLES")
    {
      auto configurationsChildNode = configurationsNodes->GetChildren();
      while (configurationsChildNode)
      {
        if (configurationsChildNode->GetName().Upper() == "VARIABLE")
        {
          auto variableNode = configurationsChildNode;
          VariableInfo varInfo;
          varInfo.name  = variableNode->GetAttribute("name", "");
          varInfo.type  = variableNode->GetAttribute("type", "STRING");
          varInfo.value = variableNode->GetAttribute("value", "");
          varInfo.description = variableNode->GetAttribute("description", "");
          auto enabled = variableNode->GetAttribute("enabled", "TRUE").Upper();
          if (enabled == "TRUE" || enabled.empty())
          {
            varInfo.enabled = true;
          }
          else
          {
            varInfo.enabled = false;
          }
          if (IsValid(varInfo))
          {
            configInfo.variables.push_back(varInfo);
          }
        }
        configurationsChildNode = configurationsChildNode->GetNext();
      }
    }
  }

  if (IsValid(configInfo) == true)
  {
    this->m_script.configurations.push_back(configInfo);
  }
}



void ScriptParser::GenerateReport(const std::string& outputFile)
{
  if (IsValid(this->m_script) == false)
  {
    wxLogDebug("Proyecto vacio");
    std::cout << "Proyecto vacio.\n";
    return;
  }
  std::string result = "";
  result += "================================================================================\n";
  result += " PROYECTO\t\t" + this->m_script.name + "\n";
  result += " VERSION\t\t" + this->m_script.version + "\n";
  result += " DESCRIPCION\t\t" + this->m_script.description + "\n";
  result += "================================================================================\n";
  result += " CONFIGURACIONES\t" + std::to_string(this->m_script.configurations.size()) + "\n";
  result += "================================================================================\n";
  for (const auto it : this->m_script.configurations)
  {
    result += "  CONFIGURACION\t\t" + it.name + "\n";
    result += "================================================================================\n";
    result += "   NOMBRE\t\t" + it.name + "\n";
    result += "   VERSION\t\t" + it.version + "\n";
    result += "   DESCRIPCION\t\t" + it.description + "\n";
    result += "   FUENTE\t\t" + it.sourceDir + "\n";
    result += "   BINARIO\t\t" + it.binaryDir + "\n";
    result += "   GENERADOR\t\t" + it.generator + "\n";
    result += "   ARQUITECTURA\t\t" + it.architecture + "\n";
    if (it.enabled) { result += "   HABILITADO\t\tSI\n"; }
    else { result += "   HABILITADO\t\tNO\n"; }
    result += "================================================================================\n";
    if (it.variables.empty() == false)
    {
      result += "   VARIABLES\t\t" + std::to_string(it.variables.size()) + "\n";
      result += "================================================================================\n";
      result += "   NOMBRE:TIPO=\"VALOR\"\tACTIVO=TRUE|FALSE\n";
      result += "================================================================================\n";

      unsigned int value = 0;
      unsigned int maxValue = it.variables.size() - 1;
      for (const auto& iv : it.variables)
      {
        result += "    " + iv.name + ":" + iv.type + "=\"" + iv.value + "\" ACTIVO=" + ((iv.enabled) ? "SI" : "NO") + "\t" + iv.description + "\n";
        if (value < maxValue)
        {
          value++;
          result += "    ----------------------------------------------------------------------------\n";
        }
      }
      result += "================================================================================\n";
    }
  }
  if(wxFileExists(outputFile))
  {

  }
  else
  {
    std::cout << result;
  }
}

void ScriptParser::GenerateScript(const std::string& outputFile)
{
  std::ofstream f(outputFile);
#ifdef _WIN32
  for (const auto& it : this->m_script.configurations)
  {
    f << "REM SCRIPT " << it.name;
    f << "cmake.exe ";
    f << "-S \"" << it.sourceDir << "\" ";
    f << "-B \"" << it.binaryDir << "\" ";
    f << "-G \"" << it.generator << "\"";
    f << "-A \"" << it.architecture << "\"";

    for (const auto& iv : it.variables)
    {
      f << "-D" << iv.name << ":" << iv.type << "=\"" << iv.value << "\" ";
    }

    f << "\n";
  }
#endif // _WIN32

  f.close();
}