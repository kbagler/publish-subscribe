#ifndef INPUT_H
#define INPUT_H

#include <memory>
#include <functional>
#include <string>

class Input
{
public:
	using Ptr = std::shared_ptr<Input>;
	using CommandHandler = std::function<int(const std::string&)>;

	Input() { }
	Input(const Input&) = delete;
	Input(Input&&) = delete;
	Input& operator=(const Input&) = delete;
	Input& operator=(Input&&) = delete;
	virtual ~Input() { }

	void register_command_input(CommandHandler handler)
	{
		command_handler = handler;
	}

protected:
	CommandHandler command_handler = nullptr;

};

#endif /* INPUT_H */

