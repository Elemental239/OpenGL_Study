#ifndef __Utility_File_H__
#define __Utility_File_H__

#include "IFile.h"
#include <fstream>

//El239: sample how to load file using std::streams
/*#include <fstream>
#include <sstream>
#include <iostream>
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

	// ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try 
    {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // Convert stream into GLchar array
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    } catch(std::ifstream::failure e)
    {
        LOGE("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
    }
*/


class CFile : public IFile
{
public:
	CFile(CStringWide path, EFileMode mode);
	~CFile();

	virtual void Open() override;
	virtual void Close() override;
	virtual void Flush() override;
	virtual void Write(CStringWide data) override;
	virtual CStringWide ReadString() override;

	virtual bool IsExist() override;

private:
	static const int MODE_INPUT = std::fstream::in;
	static const int MODE_OUTPUT = std::fstream::out;
	static const int MODE_BINARY = std::fstream::binary;
	static const int MODE_APPEND = std::fstream::app;
	static const int MODE_TRUNCATE = std::fstream::trunc;

	std::fstream m_stream;
};

#endif //__Utility_File_H__
