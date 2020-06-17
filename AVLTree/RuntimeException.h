#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H


#include <exception>

using namespace std;

class RuntimeException : public exception
{
public:
	RuntimeException(const char* err) : exception(err) {}
};

class NonexistentElement : public RuntimeException
{
public:
	NonexistentElement(const char* err) : RuntimeException(err) {}
};

#endif