#pragma once

#include <string>

class File {
   private:
    std::string path;

   public:
    explicit File(const std::string &path);
    std::string read() const;
    void write(const std::string &content) const;

    std::string ext_name() const;
    std::string base_name() const;
};