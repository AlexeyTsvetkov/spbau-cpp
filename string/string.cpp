#include <cstring>
#include <cstddef>

#include <algorithm>
#include <iostream>

#include "string.hpp"

string::string(): s_size(0), data(NULL) {}

string::string(char const * const cstr): s_size(strlen(cstr)), data(strcpy(new char[this->s_size + 1], cstr))  {}

string::string(string const &str): s_size(str.size()), data(strcpy(new char[this->s_size + 1], str.data)) {}

string::~string() {
	delete [] this->data;
}

string& string::operator=(string const &str) {
	string(str).swap(*this);
	return *this;
}

string& string::append(string const &str) {
	char* new_data = new char[this->s_size + str.s_size + 1];
	new_data = strcpy(new_data, this->data);
	delete [] this->data;
	this->data = strcat(new_data, str.data);
	this->s_size = this->s_size + str.s_size + 1;

	return *this;
}

void string::swap(string &str) {
	std::swap(this->data, str.data);
	std::swap(this->s_size, str.s_size);
}

char string::at(size_t it) const {
	return this->data[it];
}

char& string::at(size_t it) {
	return this->data[it];
}

char const * string::c_str() const {
	return (s_size > 0)?this->data:"";
}

size_t string::size() const {
	return this->s_size;
}

std::ostream& operator<<(std::ostream& os, string const &str) {
	os << str.c_str();
	return os;
}