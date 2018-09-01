#include "menu.h"



ConsoleMenu::ConsoleMenu(const std::string& message,
	const std::string& invalidChoiceMessage,
	const std::string& prompt,
	const std::unordered_map<std::string, std::function<void()>>& commandsByChoice,
	std::istream &in, std::ostream& out) :

	invalidChoiceMessage_{ invalidChoiceMessage },
	commandsByChoice_{ commandsByChoice },
	in{ in },
	out{ out }
{
	std::stringstream ss;
	std::system("color B");
	ss << message;
	for (const auto &commandByChoice : commandsByChoice_) {
		ss << '[' << commandByChoice.first << ']' << '\n';
	}
	ss << prompt;
	prompt_ = ss.str();
}

void ConsoleMenu::operator()() const {
	std::string userChoice;
	const auto bad{ commandsByChoice_.cend() };
	auto result{ bad };
	out << '\n';
	while ((out << prompt_) && (!(std::getline(in, userChoice)) ||
		((result = commandsByChoice_.find(userChoice)) == bad))) {
		out << '\n' << invalidChoiceMessage_;

		std::system("cls");
	}
	result->second();
}