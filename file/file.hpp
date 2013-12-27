#ifndef FILE_HPP
#define FILE_HPP
#include <iostream>

#include <cstdio>
#include <cstddef>

#include <string>

class file {
public:
  enum open_mode { Read, Write };
  file();
  explicit file(std::string const &fname, open_mode mode = Read);
  ~file();
  void open(std::string const &fname, open_mode mode = Read);
  void close();
  open_mode mode() const;
  bool opened() const;
  bool eof() const;
  bool error() const;
  size_t write(const char* buf, size_t size);
  size_t write(std::string const &str);
  size_t write(char value);
  size_t write(long value);
  size_t write(unsigned long value);
  size_t write(double value);
  size_t read(char *buf, size_t size);
  size_t read(std::string &word);
  size_t read(char &c);
  size_t read(long &value);
  size_t read(unsigned long &value);
  size_t read(double &value);
  size_t readline(std::string &line);
private:
  FILE* file_;
  open_mode mode_;

  file(const file& other);
  file& operator=(const file& other);

  template<typename T>
  size_t write(T value);

  template<typename T>
  size_t read(T& value);

  bool can_write() const;
  bool can_read() const;

  template<typename T>
  size_t write_(T value, const char * format) {
    if(!can_write())
      return 0;

    int ret = fprintf(file_, format, value);
    if(ret < 0)
      return 0;

    return ret; 
  }

  template<typename T>
  size_t read_(T& value, const char* format) {
    if(!can_read())
      return 0;

    int ret;
    if(fscanf(file_, format, &value, &ret) == 1) {
      return (size_t)ret;
    }

    return 0;
  }
};
#endif 