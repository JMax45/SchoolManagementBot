void start_saves(std::string message_chat_id, std::vector<std::string> all_days){
	std::ofstream outfile;
    outfile.open("saves/accounts/chat_id/id.dat", std::ios::app);
    outfile << message_chat_id << "\n";
    outfile.close();
    outfile.open("saves/accounts/user_privileges/privileges.dat", std::ios::app);
    outfile << "user" << "\n";
    outfile.close();

    for (int i = 0; i < all_days.size(); i++){
        std::string filename_user = "saves/days/"+all_days[i]+"/"+message_chat_id+".dat";
        std::ofstream file { filename_user };
    }

    std::string filename_user2 = "saves/configuration/days/"+message_chat_id+".dat";
    std::ofstream file2 { filename_user2 };
    outfile.open(filename_user2);
    outfile << "0";
    outfile.close();
}

void save_registration_date(std::string file_position)
{
	std::ofstream outfile;
   	outfile.open(file_position, std::ios::app);

	std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);

   	outfile << now->tm_mday
   			<< "/" << (now->tm_mon +1) 
   			<< "/" << (now->tm_year + 1900);

   	outfile.close();	
}