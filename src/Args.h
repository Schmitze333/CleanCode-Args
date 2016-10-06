#pragma once

#include <string>

class Args
{
  public:
    Args(std:string schema, std::string[] args);
    bool getBoolean(char arg);
    bool isValid();
    int cardinality();
    std::string usage();
    std::string errorMessage();

  private:
    bool parse();

    bool parseSchema();
    void parseSchemaElement(std::string element);
    void parseBooleanSchemaElement(std::string element);

    bool parseArguments();
    void parseArgument(std::string arg);

    void parseElements(std::string arg);
    void parseElement(char argChar);

    void setBooleanArg(char argChar, bool value);
    bool isBoolean(char argChar);

    std::string unexpectedArgumentMessage();
};
