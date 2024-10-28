#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// GET COD
void get_cod(websocketpp::connection_hdl hdl, client* c) {
    std::cout << "\nStatus for CoD!" << std::endl;

    websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);
    std:: string msg = "{\"jsonrpc\":\"2.0\",\"id\":220,\"method\":\"private/get_cancel_on_disconnect\",\"params\":{\"scope\":\"account\"}}";
    c->send(con, msg, websocketpp::frame::opcode::text);
}
// PLACE ORDER BY INSTRUMENT NAME
void plcae_order_by_instrument_name(std::string amount,std::string price,std::string instrument_name,websocketpp::connection_hdl hdl, client* c) {
    std::cout << "\nOrder placed for " << instrument_name << std::endl;
    std::cout << "Amount: " << amount << std::endl;

    websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);
    
    std::string payload = "{\"jsonrpc\":\"2.0\",\"id\":1001,\"method\":\"private/buy\",\"params\":{\"instrument_name\":\"" + instrument_name + "\",\"amount\":" + amount + ",\"type\":\"limit\",\"price\":" + price + ",\"label\":\"market001\"}}";
    c->send(con, payload, websocketpp::frame::opcode::text);
}
// CANCEL ORDER BY LABEL
void cancel_order_by_label(std::string label,websocketpp::connection_hdl hdl, client* c) {
    std::cout << "\nOrder cancelled for label: " << label << std::endl;

    websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);
    
    std::string payload = "{\"id\":47,\"method\":\"private/cancel_by_label\",\"params\":{\"label\":\"" + label + "\"}}";
    c->send(con, payload, websocketpp::frame::opcode::text);
}
// EDIT ORDER BY ORDER ID
void edit_order_by_id(std::string amount,std::string price,std::string order_id,websocketpp::connection_hdl hdl, client* c) {
    std::cout << "\nOrder edited for order ID: " << order_id << std::endl;
    std::cout << "New amount: " << amount << std::endl;
    std::cout << "New price: " << price << std::endl;

    websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);
    
    std::string payload = "{\"jsonrpc\":\"2.0\",\"id\":3725,\"method\":\"private/edit\",\"params\":{\"order_id\":\"" + order_id + "\",\"amount\":" + amount + ",\"price\":" + price + "}}";
    c->send(con, payload, websocketpp::frame::opcode::text);
}
// GET OPEN ORDERS BY ASSET KIND
void get_open_orders_by_asset_kind(std::string asset_kind,websocketpp::connection_hdl hdl, client* c) {
    std::cout << "\nOrders for asset kind: " << asset_kind << std::endl;
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);

    std::string payload = "{\"jsonrpc\":\"2.0\",\"id\":1953,\"method\":\"private/get_open_orders\",\"params\":{\"kind\":\"" + asset_kind + "\"}}";
    c->send(con, payload, websocketpp::frame::opcode::text);
}
// GET ORDER BOOK BY INSTRUMENT NAME
void get_order_book_by_instrument_name(std::string instrument_name,std::string depth,websocketpp::connection_hdl hdl, client* c) {
    std::cout << "\nOrders for asset: " << instrument_name << std::endl;
    std::cout << "The number of entries to return for bids and asks: " << depth << std::endl;
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);

    std::string payload = "{\"jsonrpc\":\"2.0\",\"id\":8772,\"method\":\"public/get_order_book\",\"params\":{\"instrument_name\":\"" + instrument_name + "\",\"depth\":" + depth + "}}";
    c->send(con, payload, websocketpp::frame::opcode::text);
}
// VIEW CURRENT POSITIONS
void get_positions(std::string currency,std::string kind,websocketpp::connection_hdl hdl, client* c) {
    std::cout << "\nOrders for currency: " << currency << std::endl;
    std::cout << "Currency kind: " << kind << std::endl;
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);

    std::string payload = "{\"jsonrpc\":\"2.0\",\"id\":2236,\"method\":\"private/get_positions\",\"params\":{\"currency\":\"" + currency + "\",\"kind\":\""+ kind + "\"}}";
    c->send(con, payload, websocketpp::frame::opcode::text);
}

void on_open(websocketpp::connection_hdl hdl, client* c) {
    std::cout << "WebSocket connection opened!" << std::endl;

    websocketpp::lib::error_code ec;
    
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);
    if (ec) {
        std::cout << "Failed to get connection pointer: " << ec.message() << std::endl;
        return;
    }
    
    // AUTH
    std:: string payload = "{\"jsonrpc\":\"2.0\",\"id\":9929,\"method\":\"public/auth\",\"params\":{\"grant_type\":\"client_credentials\",\"client_id\":\"CLIENT_ID\",\"client_secret\":\"CLIENT_SECRET\"}}";
    c->send(con, payload, websocketpp::frame::opcode::text);
    
    // MAIN MENU
    bool exitMenu = true;
    while(exitMenu) {
        std::cout << "\nChoose option from below: ";
        std::cout << "\n1. Place order";
        std::cout << "\n2. Cancel order";
        std::cout << "\n3. Modify order";
        std::cout << "\n4. Get orderbook by instrument name";
        std::cout << "\n5. View positions" << std::endl;
        int option = 0;
        std::cin >> option;
        std::cin.clear();
        std::fflush(stdin);
        switch (option) {
        case 0: {
            exitMenu = false; break;
        }
        case 1: {
            std::string instrument_name = "ETH-PERPETUAL";
            std::string amount = "40";
            std::string price = "400";
            plcae_order_by_instrument_name(amount,price,instrument_name,hdl,c);
            exitMenu = false;
            break;
        }
        case 2: {
            std::string label = "market001";
            cancel_order_by_label(label,hdl,c);
            exitMenu = false;
            break;
        }
        case 3: {
            std::string order_id = "ETH-14380402213";
            std::string amount = "20";
            std::string price = "200";
            edit_order_by_id(amount,price,order_id,hdl,c);
            exitMenu = false;
            break;
        }
        case 4: {
            std::string instrument_name = "BTC-PERPETUAL";
            std::string depth = "5";
            get_order_book_by_instrument_name(instrument_name,depth,hdl,c);
            exitMenu = false;
            break;
        }
        case 5: {
            std::string currency = "BTC";
            std::string kind = "future";
            get_positions(currency,kind,hdl,c);
            exitMenu = false;
            break;
        }
        default: {
            std::cout << "\nOption does not exist, choose again!" << std::endl;
            break;
        }
        }
    }
}

void on_message(websocketpp::connection_hdl, client::message_ptr msg) {
    std::cout << "Received message: " << msg->get_payload() << std::endl;

}
void on_fail(websocketpp::connection_hdl hdl) {
    std::cout << "WebSocket connection failed!" << std::endl;
}
void on_close(websocketpp::connection_hdl hdl) {
    std::cout << "WebSocket connection closed!" << std::endl;
}

context_ptr on_tls_init(const char * hostname, websocketpp::connection_hdl) {
    context_ptr ctx = websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);

    try {
        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                        boost::asio::ssl::context::no_sslv2 |
                        boost::asio::ssl::context::no_sslv3 |
                        boost::asio::ssl::context::single_dh_use);
        ctx->set_verify_mode(boost::asio::ssl::verify_none);
    } catch (std::exception& e) {
        std::cout << "TLS Initialization Error: " << e.what() << std::endl;
    }
    return ctx;
}

int main(int argc, char* argv[]) {
    client c;
    
    std::string hostname = "test.deribit.com/ws/api/v2";
    std::string uri = "wss://test.deribit.com/ws/api/v2";

    try {
        // Configure WebSocket++ client
        c.set_access_channels(websocketpp::log::alevel::all);
        c.clear_access_channels(websocketpp::log::alevel::frame_payload);
        c.set_error_channels(websocketpp::log::elevel::all);
            
        c.init_asio();

        // Set message, TLS initialization, open, fail, and close handlers
        c.set_message_handler(&on_message);
            
        c.set_tls_init_handler(bind(&on_tls_init, hostname.c_str(), ::_1));
        c.set_open_handler(bind(&on_open, ::_1, &c));
        c.set_fail_handler(bind(&on_fail, ::_1));
        c.set_close_handler(bind(&on_close, ::_1));
        
        // Enable detailed error logging
        c.set_error_channels(websocketpp::log::elevel::all);          
            
        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(uri, ec);
        if (ec) {
            std::cout << "Could not create connection because: " << ec.message() << std::endl;
            return 0;
        }
        // Create a connection to the specified url
        c.connect(con);
            
        c.run();
    } catch (websocketpp::exception const & e) {
        std::cout << "WebSocket Exception: " << e.what() << std::endl;
    }
}
