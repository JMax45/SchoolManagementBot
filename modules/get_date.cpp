std::string get_date(){
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string the_day(dt);
    std::string day_of_the_week = the_day.substr(0, the_day.find(" "));	
    return day_of_the_week;
}

std::string get_time(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	std::string conv_hour = std::to_string(ltm->tm_hour);
	std::string conv_min = std::to_string(ltm->tm_min);
	std::string conv_sec = std::to_string(ltm->tm_sec);

	std::string return_time = "["+conv_hour+":"+conv_min+":"+conv_sec+"]";
	
	return return_time;
}