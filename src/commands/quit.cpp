	class QuitCommand : public Command
	{
	public:
		static Command *build(ConsoleCommand command)
		{
			return new QuitCommand();
		};

	public:
		bool exec(Context *context)
		{
			std::cout << "quit command" << "\n";
			return true;
		}

	public:
		bool revert(Context *context)
		{
			return true;
		}
	};