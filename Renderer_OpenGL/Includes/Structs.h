#pragma once

template<typename T> struct GLuniform
{
public:
	void Bind(GLuint shader);
public:
	T value = T();
	std::string strName;
};