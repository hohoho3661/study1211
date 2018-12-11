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

	GameError& operator=(const GameError& e) // 상속된 클래스에 대한 연산자 재정의 ( 대입 연산자 )
	{
		std::exception::operator=(e); // 상속된 곳에 대입연산자가 있는지 확인
		errorCode = e.errorCode;
		message = e.message;
		
		return *this;
	}
	
	virtual ~GameError(){} // 다형성때문에 자식클래스의 소멸자에는 virtual을 써줘서  ,,, AAA* a = new BBB 일때 소멸자 호출이 잘되게 해준다

	virtual const char* what() const { return getMessage(); }
	const char* getMessage() const { return message.c_str(); }
	int			getErrorCode() const { return errorCode; }
};