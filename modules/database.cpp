void create_user(std::string user_id, std::vector<std::string> all_days){
	std::ofstream outfile;

	// User ID
	outfile.open("saves/accounts/chat_id/id.dat", std::ios::app);
	outfile << user_id << "\n";
	outfile.close();

	// User Privileges
	outfile.open("saves/accounts/user_privileges/privileges.dat", std::ios::app);
	outfile << "user" << "\n";
	outfile.close();

	// Create the days of the week
    for (int i = 0; i < all_days.size(); i++){
        std::string filename_one = "saves/days/"+all_days[i]+"/"+user_id+".dat";
        std::ofstream file { filename_one };
    }

    // Create Configuration File
    std::string filename_two = "saves/configuration/days/"+user_id+".dat";
    std::ofstream file_two { filename_two };
    outfile.open(filename_two);
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
   			<< "/" << (now->tm_year + 1900) << "\n";

   	outfile.close();	
}