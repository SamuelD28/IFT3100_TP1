	class PaletteCommand : public Command
	{
	public:
		static Command *build(ConsoleCommand command)
		{
			return new PaletteCommand();
		}

	public:
		bool exec(Context *context)
		{
			return true;
		}

	public:
		bool revert(Context *context)
		{
			return true;
		}
	};