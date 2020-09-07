#include <fstream>
#include <iostream>
#include <cstdio>

#include "libjsonnet++.h"

static std::string readFile(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in.good()){
        std::cerr << "Could not open: " << filename;
        return "";
    }
    return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cout << "Needs input.jsonnet\n";
    return EXIT_FAILURE;
  }

  jsonnet::Jsonnet jsonnet;
  jsonnet.init();

  std::string output;
  //bool ret = jsonnet.evaluateFile(argv[1], &output);
  //if (!ret) {
  //  std::cerr << jsonnet.lastError() << "\n";
  //  return EXIT_FAILURE;
  //}
  const std::string input = readFile(argv[1]);
  bool ret = jsonnet.evaluateSnippet("dummy", input, &output);
  if (!ret) {
    std::cerr << jsonnet.lastError() << "\n";
    return EXIT_FAILURE;
  }

  std::cout << output;

  return EXIT_SUCCESS;
}
