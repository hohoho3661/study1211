#pragma once

#include <string>
#include <exception>

namespace GE_NS
{
	const int FATAL_ERROR	= -1;
	const int WARNING		= 1;

}

class GameError : public std::exception
{
private:
	int			errorCode;
	std::string	message;

public:
	GameError() : errorCode(GE_NS::FATAL_ERROR), message("Undefined Error int Game."){}
	GameError(const GameError& e) : std::exception(e), errorCode(e.errorCode), message(e.message){}
	GameError(int code, const std::string& s) : errorCode(code), message(s){}

	GameError& operator=(const GameError& e) // ��ӵ� Ŭ������ ���� ������ ������ ( ���� ������ )
	{
		std::exception::operator=(e); // ��ӵ� ���� ���Կ����ڰ� �ִ��� Ȯ��
		errorCode = e.errorCode;
		message = e.message;
		
		return *this;
	}
	
	virtual ~GameError(){} // ������������ �ڽ�Ŭ������ �Ҹ��ڿ��� virtual�� ���༭  ,,, AAA* a = new BBB �϶� �Ҹ��� ȣ���� �ߵǰ� ���ش�

	virtual const char* what() const { return getMessage(); }
	const char* getMessage() const { return message.c_str(); }
	int			getErrorCode() const { return errorCode; }
};