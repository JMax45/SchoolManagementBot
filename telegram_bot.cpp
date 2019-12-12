#include <stdio.h>
//#include <tgbot/tgbot.h>
#include "tgbot-cpp-master/include/tgbot/tgbot.h" 
#include <string>
#include <vector>
#include <ctime>
#include "includes/external_functions.h"
#include <algorithm>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>

int main() {
    TgBot::Bot bot(get_token());
    bool configuration_calendar = false;
    int32_t message_delete_id;
    std::vector<std::string> all_days = get_all_days_vector();
    std::vector<std::string> all_days_italian = get_all_days_italian_vector();
    std::vector<std::string> all_days_short = get_all_days_short();

    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row0 = get_inline_one();
    keyboard->inlineKeyboard.push_back(row0);

    bot.getEvents().onCommand("start", [&bot,&all_days](TgBot::Message::Ptr message) {
        std::vector<std::string> all_users;
        std::ifstream file("saves/accounts/chat_id/id.dat");
        std::string str; 
        
        while (std::getline(file, str)) 
        {
            all_users.push_back(str);
        }
        file.close();

        std::string message_chat_id = std::to_string(message->chat->id);

        if (std::find(all_users.begin(), all_users.end(), message_chat_id) != all_users.end())
        {
            bot.getApi().sendMessage(message->chat->id, "Your account is already registered in the system");
        }

        else
        {
            start_saves(message_chat_id, all_days); // Salva i dati dell'utente 
            save_registration_date("saves/accounts/registration_date/registration_date.dat");
            printf("New user registered in the system.\n");
            bot.getApi().sendMessage(message->chat->id, "Welcome to the School Management Bot.");
            bot.getApi().sendMessage(message->chat->id, "This bot offers you a wide range of tools to manage your school life.");
            bot.getApi().sendMessage(message->chat->id, "To start configuring the calendar, type /settings.");
        }

    });
    
    bot.getEvents().onCommand("settings", [&bot,&configuration_calendar,&all_days,&all_days_italian](TgBot::Message::Ptr message) {
        std::string number_to_string = std::to_string(message->chat->id);
        std::vector<std::string> configuration_step;

        std::string filename_vector = "saves/configuration/days/"+number_to_string+".dat";
        std::ifstream file(filename_vector);

        std::string str; 

        while (std::getline(file, str)) {
            configuration_step.push_back(str);
        }
        file.close();

        int config_step_to_int = std::stoi( configuration_step[0] );

        std::string message_to_display = "Digita le materie per "+all_days_italian[config_step_to_int];
        bot.getApi().sendMessage(message->chat->id, message_to_display);
        bot.getApi().sendMessage(message->chat->id, "Quando hai finito digita /end e passerai al prossimo giorno.");
        
        configuration_calendar = true;
    });

    bot.getEvents().onCommand("today", [&bot,&all_days_short,&all_days](TgBot::Message::Ptr message) {
        std::string day_of_the_week = get_date();
        std::string id_to_string = std::to_string(message->chat->id); 
        int user_position = get_user_position(id_to_string);

        if (day_of_the_week == "Sun"){
            bot.getApi().sendMessage(message->chat->id, "L'orario per la domenica non è disponibile.");
        }
        else{
            std::string message_to_send = get_day_schedule(user_position, day_of_the_week, all_days_short, id_to_string, all_days, 0);

            bot.getApi().sendMessage(message->chat->id, message_to_send);   
        }              
    });

    bot.getEvents().onCommand("tomorrow", [&bot,&all_days_short,&all_days](TgBot::Message::Ptr message) {
        std::string day_of_the_week = get_date();
        std::string id_to_string = std::to_string(message->chat->id); 
        int user_position = get_user_position(id_to_string);

        if (day_of_the_week == "Sun"){
            bot.getApi().sendMessage(message->chat->id, "L'orario per la domenica non è disponibile.");
        }
        else{
            std::string message_to_send = get_day_schedule(user_position, day_of_the_week, all_days_short, id_to_string, all_days, 1);

            bot.getApi().sendMessage(message->chat->id, message_to_send);   
        }    
    });

    bot.getEvents().onCallbackQuery([&bot, &keyboard, &all_days_short, &all_days, &message_delete_id](TgBot::CallbackQuery::Ptr query) {
        std::string id_to_string = std::to_string(query->message->chat->id); 
        int user_position = get_user_position(id_to_string);
        std::string message_from_user = "null";
        if (StringTools::startsWith(query->data, "lunedi")) {      
            message_from_user = "Mon";
        }
        if (StringTools::startsWith(query->data, "martedi")) {      
            message_from_user = "Tue";
        }
        if (StringTools::startsWith(query->data, "mercoledi")) {        
            message_from_user = "Wed";
        }
        if (StringTools::startsWith(query->data, "giovedi")) {      
            message_from_user = "Thu";
        }
        if (StringTools::startsWith(query->data, "venerdi")) {      
            message_from_user = "Fri";
        } 
        if (StringTools::startsWith(query->data, "sabato")) {    
            message_from_user = "Sat";
        }
        std::string message_to_send = get_day_schedule(user_position, message_from_user, all_days_short, id_to_string, all_days, 0);
        if (get_day_schedule_additional(query->message->chat->id)==0){
            bot.getApi().sendMessage(query->message->chat->id, message_to_send, false, 0); 
        }
        else{
            bot.getApi().sendMessage(query->message->chat->id, message_to_send, false, 0);  
            bot.getApi().deleteMessage(query->message->chat->id, get_day_schedule_additional(query->message->chat->id));   
            get_day_schedule_delete(query->message->chat->id);
        }                      
    });
 
    bot.getEvents().onCommand("getd", [&bot, &all_days_short, &all_days, &keyboard, &message_delete_id](TgBot::Message::Ptr message) {
        std::string id_to_string = std::to_string(message->chat->id); 
        int user_position = get_user_position(id_to_string);        
        std::string message_from_user = message->text.c_str();
        std::string string_to_remove = "/getd ";
        message_from_user = clean_message(message_from_user, string_to_remove);

        if (message_from_user == "/getd"){
            message_from_user = "/getd";
        }
        if (message_from_user == "domenica"){
            bot.getApi().sendMessage(message->chat->id, "L'orario per la domenica non è disponibile.");
        }
        else if (message_from_user == "/getd"){
            bot.getApi().sendMessage(message->chat->id, "Scegli il giorno: ", false, 0, keyboard);
            message_delete_id = message->messageId+1;
            save_day_schedule_additional(message->chat->id, message_delete_id);
        }
        else{
            std::string message_to_send = get_day_schedule(user_position, message_from_user, all_days_short, id_to_string, all_days, 0);
            bot.getApi().sendMessage(message->chat->id, message_to_send, false, 0);
        }
    });
    // Admin commands
    bot.getEvents().onCommand("see_users_number", [&bot](TgBot::Message::Ptr message) {
        std::string id_to_string = std::to_string(message->chat->id); 
        int user_position = get_user_position(id_to_string);

        if (check_user_status(user_position) == "root" || check_user_status(user_position) == "admin"){
            std::string message_to_display = "Users registered in the system: " + see_users_number() + ".";
            bot.getApi().sendMessage(message->chat->id, message_to_display);
        }
        else{
            bot.getApi().sendMessage(message->chat->id, "Comando non riconosciuto");
        }   
    });
    bot.getEvents().onCommand("delacc", [&bot](TgBot::Message::Ptr message) {
        std::string id_to_string = std::to_string(message->chat->id); 
        int user_position = get_user_position(id_to_string);        
        if (check_user_status(user_position) == "root" || check_user_status(user_position) == "admin"){
            std::string message_from_user = message->text.c_str();
            std::string string_to_remove = "/delacc ";
            message_from_user = clean_message(message_from_user, string_to_remove);

            delete_account(message_from_user);
            bot.getApi().sendMessage(message->chat->id, "Account Deleted.");
        }
        else{
            bot.getApi().sendMessage(message->chat->id, "Comando non riconosciuto.");
        }    
    });

    bot.getEvents().onAnyMessage([&bot,&configuration_calendar,&all_days,&all_days_italian](TgBot::Message::Ptr message) {
        std::cout << get_time() << " ";
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        if (configuration_calendar == false){
            //bot.getApi().sendMessage(message->chat->id, "Il tuo messaggio: " + message->text);
        }
        if (StringTools::startsWith(message->text, "/end")){
            if (configuration_calendar == true){
                std::string number_to_string = std::to_string(message->chat->id);
                std::vector<std::string> configuration_step;

                std::string filename_vector = "saves/configuration/days/"+number_to_string+".dat";
                std::ifstream file(filename_vector);

                std::string str; 

                while (std::getline(file, str)) {
                    configuration_step.push_back(str);
                }
                file.close();

                int config_step_to_int = std::stoi( configuration_step[0] );

                std::ofstream outfile;

                outfile.open(filename_vector);
                int new_value = config_step_to_int + 1;
                outfile << new_value;
                outfile.close();
            }    
        } 
        if (StringTools::startsWith(message->text, "/end-config")){
            if (configuration_calendar == true){
                configuration_calendar = false;
                bot.getApi().sendMessage(message->chat->id, "Configurazione completata.");
            }    
        }          
        if (configuration_calendar == true){
            if (message->text=="/end"){
                std::string number_to_string = std::to_string(message->chat->id);
                std::vector<std::string> configuration_step;

                std::string filename_vector = "saves/configuration/days/"+number_to_string+".dat";
                std::ifstream file(filename_vector);

                std::string str; 

                while (std::getline(file, str)) {
                    configuration_step.push_back(str);
                }
                file.close();

                int config_step_to_int = std::stoi( configuration_step[0] );

                if (config_step_to_int>5){
                    std::string number_to_string = std::to_string(message->chat->id);
                    std::vector<std::string> configuration_step;

                    std::string filename_vector = "saves/configuration/days/"+number_to_string+".dat";
                    std::ifstream file(filename_vector);

                    std::ofstream outfile;
                    outfile.open(filename_vector);
                    outfile << 0;
                    outfile.close();

                    bot.getApi().sendMessage(message->chat->id, "Configurazione Completata.");
                    configuration_calendar = false;
                }
                else{
                    std::string message_to_display = "Digita le materie per "+all_days_italian[config_step_to_int];
                    bot.getApi().sendMessage(message->chat->id, message_to_display);
                    bot.getApi().sendMessage(message->chat->id, "Quando hai finito digita /end e passerai al prossimo giorno.");
                }
            }
            else{
                std::ofstream outfile;

                std::string number_to_string = std::to_string(message->chat->id);

                std::vector<std::string> configuration_step;

                std::string filename_vector = "saves/configuration/days/"+number_to_string+".dat";
                std::ifstream file(filename_vector);

                std::string str; 

                while (std::getline(file, str)) {
                    configuration_step.push_back(str);
                }
                file.close();

                int config_step_to_int = std::stoi( configuration_step[0] );

                std::string filename_to_save = "saves/days/"+all_days[config_step_to_int]+"/"+number_to_string+".dat";
                outfile.open(filename_to_save, std::ios::app);
                outfile << message->text << "\n";
                bot.getApi().sendMessage(message->chat->id, "Materia aggiunta con successo.");
            }

        }  
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << get_time() << " ";
            printf("Long poll started\n");
            longPoll.start();
            //bot.getApi().deleteWebhook();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}