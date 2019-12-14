std::string check_user_status(int user_id_position){
	std::ifstream file2("saves/accounts/user_privileges/privileges.dat");
    std::string str2; 
    std::vector<std::string> all_id_privileges;
    while (std::getline(file2, str2)) {
    	all_id_privileges.push_back(str2);
    }
    file2.close();

    return all_id_privileges[user_id_position];
}

std::string see_users_number(){
	std::vector<std::string> all_id;
    std::ifstream file("saves/accounts/chat_id/id.dat");
    std::string str; 
    while (std::getline(file, str)) {
    	all_id.push_back(str);
    }
    file.close();

    std::string size_to_string = std::to_string(all_id.size());
    
    return size_to_string;
}

int get_user_position(std::string user_id){
	std::vector<std::string> all_id;
    std::ifstream file("saves/accounts/chat_id/id.dat");
    std::string str; 
    while (std::getline(file, str)) {
    	all_id.push_back(str);
    }
    file.close();
        
    std::vector<std::string>::iterator itr = std::find(all_id.begin(), all_id.end(), user_id);
    int id_position = std::distance(all_id.begin(), itr);

    return id_position;
}

std::string delete_account(std::string user_id){
	std::vector<std::string> all_id;
	std::ifstream file("saves/accounts/chat_id/id.dat");
	std::string str;
	while (std::getline(file, str)) {
		all_id.push_back(str);
	}
	file.close();

	std::vector<std::string> all_user_privileges;
	std::ifstream file2("saves/accounts/user_privileges/privileges.dat");
	std::string str2;
	while (std::getline(file2, str2)) {
		all_user_privileges.push_back(str2);
	}
	file2.close();

	std::vector<std::string> all_user_regdate;
	std::ifstream file3("saves/accounts/user_privileges/privileges.dat");
	std::string str3;
	while (std::getline(file3, str3)) {
		all_user_regdate.push_back(str3);
	}
	file3.close();

	std::vector<std::string>::iterator itr = std::find(all_id.begin(), all_id.end(), user_id);
	int id_position = std::distance(all_id.begin(), itr);

	all_id.erase(all_id.begin() + id_position);
	all_user_privileges.erase(all_user_privileges.begin() + id_position);
	all_user_regdate.erase(all_user_regdate.begin() + id_position);

	std::ofstream outfile;
	outfile.open("saves/accounts/chat_id/id.dat");
	for(int i = 0; i < all_id.size(); i++){
    	outfile << all_id[i] << "\n";
	}
	outfile.close();

	outfile.open("saves/accounts/user_privileges/privileges.dat");
	for(int i = 0; i < all_id.size(); i++){
		outfile << all_user_privileges[i] << "\n";
	}
	outfile.close();

	outfile.open("saves/accounts/registration_date/registration_date.dat");
	for(int i = 0; i < all_id.size(); i++){
		outfile << all_user_regdate[i] << "\n";
	}
	outfile.close();
}

void wipedata(){
	// Accounts
	// chat_id
	std::ofstream outfile;
	outfile.open("saves/accounts/chat_id/id.dat");
	outfile << "[id.dat]\n";
	outfile.close();

	// registration_date
	outfile.open("saves/accounts/registration_date/registration_date.dat");
	outfile << "[registration_date.dat]\n";
	outfile.close();

	// registration_date
	outfile.open("saves/accounts/user_privileges/privileges.dat");
	outfile << "[privileges.dat]\n";
	outfile.close();

	// registration_date
	outfile.open("bot/token.dat");
	outfile << "Your_Token";
	outfile.close();		

	system("exec rm -r saves/configuration/days/*");
	system("exec rm -r saves/days/friday/*");
	system("exec rm -r saves/days/monday/*");
	system("exec rm -r saves/days/saturday/*");
	system("exec rm -r saves/days/thursday/*");
	system("exec rm -r saves/days/tuesday/*");
	system("exec rm -r saves/days/wednesday/*");

}