#include "Args.h"

#include <sstream>

Args::Args(std::string schema, std::string args)
{
  this->schema = SplitString(schema);
  this->args = SplitString(args);
  valid = parse();
}

std::vector<std::string> Args::SplitString(std::string s)
{
  std::vector<std::string> stringList;
  return stringList;
}

bool Args::isValid()
{
  return valid;
}

bool Args::parse()
{
  if (schema.size() == 0 && args.size() == 0)
    return true;

  parseSchema();
  parseArguments();
  return unexpectedArguments.size() == 0;
}

bool Args::parseSchema()
{
  for (std::string element : schema)
  {
    parseSchemaElement(element);
  }
  return true;
}

void Args::parseSchemaElement(std::string element)
{
  if (element.length() == 1) {
    parseBooleanSchemaElement(element);
  }
}

void Args::parseBooleanSchemaElement(std::string element)
{
  char c = element.at(0);
  if (isLetter(c)) {
    booleanArgs[c] = false;
    // booleanArgs.put(c, false);
  }
}

bool Args::isLetter(char c)
{
  return true;
}

bool Args::parseArguments()
{
  for (std::string arg : args) {
    parseArgument(arg);
  }
  return true;
}

void Args::parseArgument(std::string arg)
{
  if (arg[0] == ('-'))
    parseElements(arg);
}

void Args::parseElements(std::string arg)
{
  for (size_t i = 1; i < arg.size(); ++i)
    parseElement(arg.at(i));
}

void Args::parseElement(char argChar)
{
  if (isBoolean(argChar)) {
    numberOfArguments++;
    setBooleanArg(argChar, true);
  }
  else {
    unexpectedArguments.insert(argChar);
  }
}

void Args::setBooleanArg(char argChar, bool value)
{
  booleanArgs[argChar] = value;
}

bool Args::isBoolean(char argChar)
{
  return (booleanArgs.find(argChar) == booleanArgs.end());
}

int Args::cardinality()
{
  return numberOfArguments;
}

std::string Args::usage()
{
  std::string out = "";
  if (schema.size() > 0) {
    out += "-[";
    for (std::string s : schema) {
      out += s;
    }
    out += "]";
  }
  return out;
}

std::string Args::errorMessage()
{
  if (unexpectedArguments.size() > 0)
    return unexpectedArgumentMessage();
  else
    return "";
}

std::string Args::unexpectedArgumentMessage()
{
  std::ostringstream message;
  message << "Argument(s) -";
  for (char c : unexpectedArguments) {
    message << c;
  }
  message << " unexpected.";
  return message.str();
}

bool Args::getBoolean(char arg)
{
  return booleanArgs[arg];
}
