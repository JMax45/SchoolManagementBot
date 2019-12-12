# School Management Bot
[![Code Climate](https://codeclimate.com/github/JMax45/SchoolManagementBot/badges/gpa.svg)](https://codeclimate.com/github/JMax45/SchoolManagementBot/coverage)
[![Issue Count](https://codeclimate.com/github/JMax45/SchoolManagementBot/badges/issue_count.svg)](https://codeclimate.com/github/JMax45/SchoolManagementBot)

![SMB](readme_media/logo.png)

**SMB** is a C++ telegram bot for organizing your school life.



## Requirements

[tgbot-cpp](https://github.com/reo7sp/tgbot-cpp) is required for the compilation.
```bash
git clone https://github.com/reo7sp/tgbot-cpp
cd tgbot-cpp
cmake .
make -j4
sudo make install
```

## Installation

Use GIT to clone the repository into your local machine.

```bash
git clone https://github.com/JMax45/SchoolManagementBot
```

## Usage

Change the bot token in line 15.
```bash
TgBot::Bot bot("YOUR_TOKEN");
```

## Compilation

```bash
g++ telegram_bot.cpp -o telegram_bot --std=c++11 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
