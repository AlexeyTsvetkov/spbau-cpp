#include <cstring>

#include "file.hpp"

file::file():file_(NULL), mode_(open_mode::Read) {}

file::file(std::string const &fname, open_mode mode): file_(fopen(fname.c_str(), (mode == Read)?"r":"w")),
                                                      mode_(mode) {}

file::~file() {
  close();
}

void file::open(std::string const &fname, open_mode mode) {
  close();
  if(mode_ == Read)
    file_ = fopen(fname.c_str(), "r");
  else 
    file_ = fopen(fname.c_str(), "w");

}

void file::close() {
  fclose(file_);
  file_ = NULL;
}

file::open_mode file::mode() const {
  return mode_;
}

bool file::opened() const {
  return file_ != NULL;
}

bool file::eof() const {
  const int ok = 0;
  return opened() && feof(file_) != ok;
}

bool file::error() const {
  const int ok = 0;
  return opened() && ferror(file_) != ok;
}

size_t file::write(const char* buf, size_t size) {
  if(!can_write())
    return 0;

  return fwrite((const void*)buf, sizeof(char), size, file_);
}


size_t file::write(std::string const &str) {
  return write(str.c_str(), str.size());
}

size_t file::write(char value) {
  return write_(value, "%c"); 
}

size_t file::write(long value) {
  return write_(value, "%li"); 
}

size_t file::write(unsigned long value) {
  return write_(value, "%lu");
}

size_t file::write(double value) {
  return write_(value, "%f");
}

size_t file::read(char *buf, size_t size) {
  if(!can_read())
      return 0;

  return fread((void*)buf, sizeof(char), size, file_);
}

size_t file::read(std::string &word) {
  word = "";
  const size_t buf_size = 1024;
  char tmp[buf_size];
  
  if(can_read()) {
    int ret = fscanf(file_, "%s", tmp);
    if(ret >= 0)
      word = std::string(tmp);
  }
  

  return word.size(); 
}

size_t file::read(char &c) {
  return read_(c, "%c%n"); 
}

size_t file::read(long &value) {
  return read_(value, "%li%n"); 
}

size_t file::read(unsigned long &value) {
  return read_(value, "%lu%n"); 
}

size_t file::read(double &value) {
  return read_(value, "%lf%n"); 
}

size_t file::readline(std::string &line) {
  line = "";
  const size_t buf_size = 1024;
  char buf[buf_size];

  if(can_read()) {
    if(fgets(buf, buf_size, file_));
      line.append(buf, strlen(buf));
  }

  return line.size();
}

bool file::can_write() const {
  return opened() && mode_ == Write;
}

bool file::can_read() const {
  return opened() && mode_ == Read && !eof();
}