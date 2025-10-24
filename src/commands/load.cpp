	class LoadCommand : public Command
	{
	public:
		std::string path{};

		const std::string resourcesDirectoryPath = "resources";

	public:
		static Command *build(ConsoleCommand command)
		{
			auto loadCommand = new LoadCommand();
			// assertions
			if (command.arguments.size() != 1)
			{
				return nullptr;
			}

			loadCommand->path = command.arguments.at(0);
			return loadCommand;
		}

	public:
		bool exec(Context *context) override
		{
			if (!std::filesystem::exists(path))
			{
				std::cout << "[LOAD COMMAND] file is not open \n";
				return false;
			}

			std::string filename = "";
			const size_t lastSlashIndex = path.find_last_of("\\");
			if (lastSlashIndex != SIZE_MAX)
			{
				filename = path.substr(lastSlashIndex + 1);
			}
			else
			{
				filename = path;
			}

			std::cout << "[LOAD COMMAND] file name: " << filename << "\n";

			if (!std::filesystem::exists(resourcesDirectoryPath))
			{
				if (!std::filesystem::create_directory(resourcesDirectoryPath))
				{
					std::cout << "[LOAD COMMAND] could not create resource directory \n";
					return false;
				}
				std::cout << "[LOAD COMMAND] created directory:" << resourcesDirectoryPath << "\n";
			}

			const std::string destinationPath = resourcesDirectoryPath + "\\" + filename;
			if (std::filesystem::exists(destinationPath))
			{
				std::cout << "[LOAD COMMAND] file already exist at: " << destinationPath << "\n";
				return false;
			}

			if (std::filesystem::copy_file(path, destinationPath))
			{
				std::cout << "[LOAD COMMAND] copied file from:" << path << " to:" << destinationPath << "\n";
			}

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distrib(1, INT32_MAX);
			int randomNumber = distrib(gen);

			Resource resource{
					randomNumber,
					"image",
					destinationPath,
			};

			context->resources.push_back(resource);

			return true;
		}

	public:
		bool revert(Context *context) override
		{
			return true;
		}
	};