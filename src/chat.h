#ifndef CHAT_H
#define CHAT_H

#include "client.h"
#include <string>
#include <unordered_map>

class ChatClient : public Client {
public:
    ChatClient(connection_hdl hdl, PacketSender& sender);
    void send_event(std::string& event);
    virtual void on_chat_message(connection_hdl sender_hdl, std::string& user_id, std::string& message);
    virtual void store_chat_message(const std::string& message);
    virtual void on_close_chat(connection_hdl hdl);
    virtual void on_open_chat(connection_hdl hdl);
    std::string get_or_generate_username(const std::string& user_id);
    std::string get_chat_history_as_string();
    static std::set<connection_hdl, std::owner_less<connection_hdl>>& get_chat_connections();
    virtual ~ChatClient() { chat_connections.erase(hdl); }

private:
    static std::set<connection_hdl, std::owner_less<connection_hdl>> chat_connections;
    std::unordered_map<std::string, std::string> user_id_to_name;
};

#endif