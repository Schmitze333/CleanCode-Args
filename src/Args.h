#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

class Args
{
  public:
    Args(std::string schema, std::string args);
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
    bool isLetter(char c);
    std::vector<std::string> SplitString(std::string s);

    std::string unexpectedArgumentMessage();

    std::vector<std::string> schema;
    std::vector<std::string> args;
    bool valid;
    std::set<char> unexpectedArguments;
    std::map<char, bool> booleanArgs;
    int numberOfArguments;
};
