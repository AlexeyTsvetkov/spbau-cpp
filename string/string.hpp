#ifndef STRING_HPP
#define STRING_HPP

#include <cstddef>

#include <iostream>

class string
{
public:
	string();
	string(char const * const cstr);
	string(string const &str);
	~string();

	string& operator=(string const &str);

	string& append(string const &str);

	void swap(string &str);

	char at(size_t it) const;
	char& at(size_t it);
	char const * c_str() const;
	size_t size() const;

private:
	size_t s_size;
	char* data;
};

std::ostream& operator<<(std::ostream& os, string const &str);

#endif