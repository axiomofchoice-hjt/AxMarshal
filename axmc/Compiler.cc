#include "Compiler.h"

#include "BackEnd/BackEnd.h"
#include "BackEnd/HdrGen.h"
#include "BackEnd/SrcGen.h"
#include "File/File.h"
#include "FrontEnd/FrontEnd.h"

namespace Compiler {
void Compile(const std::string &input, std::string output) {
    File input_file = File(input);
    if (input_file.ext_name() != "txt") {
        throw "path must ended with `.txt`";
    }

    std::string input_str = input_file.read();
    auto tokens = FrontEnd::Lexer(input_str);
    auto blocks = FrontEnd::Parser(tokens.result);
    BackEnd::BackEnd back_end(input_file.base_name(), blocks);

    if (output.empty()) {
        throw "output_dir is empty";
    }
    if (output.back() != '/' && output.back() != '\\') {
        output.push_back('/');
    }

    auto data = back_end.json();
    File(output + input_file.base_name() + ".h")
        .write(BackEnd::HdrGen::gen(data));
    File(output + input_file.base_name() + ".cc")
        .write(BackEnd::SrcGen::gen(data));
}
}  // namespace Compiler