std::string get_day_schedule(int user_id_position, std::string day_of_the_week, std::vector<std::string> all_days_short, std::string number_to_string,
							 std::vector<std::string> all_days, int additional)
{
	std::vector<std::string>::iterator itr = std::find(all_days_short.begin(), all_days_short.end(), day_of_the_week);
    int day_position = std::distance(all_days_short.begin(), itr); 

    std::vector<std::string> all_calendar;
    std::string filename_user = "saves/days/"+all_days[day_position+additional]+"/"+number_to_string+".dat";
    std::ifstream file(filename_user);

    std::string file_name = "saves/accounts/temp/"+number_to_string+".dat";
    std::ofstream file_temp { file_name };
    std::ofstream outfile;
    outfile.open(file_name);

    std::vector<std::string> all_id;
    std::ifstream file3(filename_user);
    std::string str2; 
    while (std::getline(file3, str2)) {
    	all_id.push_back(str2);
    }
    file3.close();

    std::string size_to_string = std::to_string(all_id.size());

    for (int i = 0; i < all_id.size(); i++){
    	outfile << "[" << i + 1 << "] " << all_id[i] << "\n";
    }
    outfile.close();

    std::ifstream file4(file_name);
    //const char *text
    std::string str((std::istreambuf_iterator<char>(file4)),
                     std::istreambuf_iterator<char>());
    file.close();
            
    std::string str_to_check = str; 
    str_to_check.erase(remove(str_to_check.begin(), str_to_check.end(), ' '), str_to_check.end());

    if(str_to_check.empty()){
    	return "L'orario per questo giorno è vuoto.";
    }
    else{
    	return str;
    }    
}

bool check_if_exists(const std::string& filename) {
	std::ifstream ifile(filename.c_str());
  	return (bool)ifile;
}

std::string save_day_schedule_additional(int user_id, int32_t message_delete_id){
	std::string filename = "saves/accounts/temp/getd_inline/"+std::to_string(user_id)+".dat";

	if (check_if_exists(filename)==0){
		std::ofstream file_temp { filename };
		file_temp.close();
		std::ofstream outfile;
		outfile.open(filename);
		outfile << message_delete_id;
		outfile.close();
	}
}

void get_day_schedule_delete(int user_id){
	std::string filename = "saves/accounts/temp/getd_inline/"+std::to_string(user_id)+".dat";

	std::string str2 = filename;
	const char *cstr = str2.c_str();

	if( remove( cstr ) != 0 )
		std::cout << get_time() << " Error deleting file" << "\n";
    else
    	std::cout << get_time() << " File successfully deleted" << "\n"; 
}

int32_t get_day_schedule_additional(int user_id){
	std::string filename = "saves/accounts/temp/getd_inline/"+std::to_string(user_id)+".dat";

	bool check_if_delete;

	if (check_if_exists(filename)==0){
		check_if_delete = false;
	}
	else{
		check_if_delete = true;
	}

	if (check_if_delete == false){
		return 0;
	}
	else{
		std::ifstream file4(filename);
    	std::string str((std::istreambuf_iterator<char>(file4)),
                     	std::istreambuf_iterator<char>());
    	file4.close();

		std::string text = str;
		int number;
		std::istringstream iss (text);
		iss >> number;
    	return number;
    }	             	
}