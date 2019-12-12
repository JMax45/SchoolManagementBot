std::string get_token(){
	std::ifstream file("bot/token.dat");
	std::string bot_token;
	file >> bot_token;
	file.close();

	return bot_token;
}