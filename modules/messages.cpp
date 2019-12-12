std::string clean_message(std::string message_to_clean, std::string string_to_remove){
	std::string::size_type i = message_to_clean.find(string_to_remove);

    if (i != std::string::npos){
    	message_to_clean.erase(i, string_to_remove.length());
    }  
    return message_to_clean;
}

std::vector<TgBot::InlineKeyboardButton::Ptr> get_inline_one(){
	std::vector<TgBot::InlineKeyboardButton::Ptr> row0;
	TgBot::InlineKeyboardButton::Ptr checkButton(new TgBot::InlineKeyboardButton);
    checkButton->text = "Lunedi";
    checkButton->callbackData = "lunedi";
    TgBot::InlineKeyboardButton::Ptr checkButton2(new TgBot::InlineKeyboardButton);
    checkButton2->text = "Martedi";
    checkButton2->callbackData = "martedi";
    TgBot::InlineKeyboardButton::Ptr checkButton3(new TgBot::InlineKeyboardButton);
    checkButton3->text = "Mercoledi";
    checkButton3->callbackData = "mercoledi";
    TgBot::InlineKeyboardButton::Ptr checkButton4(new TgBot::InlineKeyboardButton);
    checkButton4->text = "Giovedi";
    checkButton4->callbackData = "giovedi";
    TgBot::InlineKeyboardButton::Ptr checkButton5(new TgBot::InlineKeyboardButton);
    checkButton5->text = "Venerdi";
    checkButton5->callbackData = "venerdi";
    TgBot::InlineKeyboardButton::Ptr checkButton6(new TgBot::InlineKeyboardButton);
    checkButton6->text = "Sabato";
    checkButton6->callbackData = "sabato";  

    row0.push_back(checkButton);
    row0.push_back(checkButton2);
    row0.push_back(checkButton3);
    row0.push_back(checkButton4);
    row0.push_back(checkButton5);
    row0.push_back(checkButton6);

    return row0;
}