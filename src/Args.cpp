#include "Args.h"

Args::Args(std::string schema, std::string[] args)
{
  this->schema = schema;
  this->args = args;
  valid = parse();
}

bool Args::isValid()
{
  return valid;
}

bool Args::parse()
{
  if (schema.length() == 0 && args.length() == 0)
    return true;

  parseSchema();
  parseArguments();
  return unexpectedArguments.size() == 0;
}

bool Args::parseSchema()
{
  for (std::string element : schema.split(',')) {
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
  char c = element.charAt(0);
  if (Character.isLetter(c)) {
    booleanArgs.put(c, false);
  }
}

bool Args::parseArguments()
{
  for (std::string arg : args) {
    parseArgument(arg);
  }
}

void Args::parseArgument(std::string arg)
{
  if (arg.startsWith("-"))
    parseElements(arg);
}

void Args::parseElements(std::string arg)
{
  for (int i = 1; i < arg.length(); ++i)
    parseElement(arg.charAt(i));
}

void Args::parseElement(char argChar)
{
  if (isBoolean(argChar)) {
    numberOfArguments++;
    setBooleanArg(argChar, true);
  }
  else {
    unexpectedArguments.add(argChar);
  }
}

void Args::setBooleanArg(char argChar, bool value)
{
  booleanArgs.put(argChar, value);
}

bool Args::isBoolean(char argChar)
{
  return booleanArgs.containsKey(argChar);
}

int Args::cardinality()
{
  return numberOfArguments;
}

std::string Args::usage()
{
  if (schema.length() > 0)
    return "-[" + schema + "]";
  else
    return "";
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
  std::stringbuffer message = new std::stringbuffer("Argument(s) -");
  for (char c : unexpectedArguments) {
    message.append(c);
  }
  message.append(" unexpected.");
  return message.toString();
}

bool Args::getBoolean(char arg)
{
  return booleanArgs.get(arg);
}
