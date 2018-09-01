#pragma once
#ifndef MENU_H
#define MENU_H
#include "includes.h"
class ConsoleMenu {
public:
	ConsoleMenu(const std::string& message,
		const std::string& invalidChoiceMessage,
		const std::string& prompt,
		const std::unordered_map<std::string, std::function<void()>>& commandsByChoice,
		std::istream &in = std::cin,
		std::ostream &out = std::cout);
	void operator()() const;
private:
	std::string invalidChoiceMessage_;
	// the prompt_ string contains the message, all choices and prompt
	std::string prompt_;
	std::unordered_map<std::string, std::function<void()>> commandsByChoice_;
	std::istream &in;
	std::ostream &out;
};
#endif // MENU_H