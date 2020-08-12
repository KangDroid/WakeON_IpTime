#include <iostream>
#include <fstream>
#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <cpprest/http_client.h>
#include "json.h"

using namespace std;
using namespace web::http;
using namespace web::http::client;

/**
 * Enable/Disable terminal output
 * Reference: https://stackoverflow.com/questions/1413445/reading-a-password-from-stdcin
 * @param enable
 */
void set_echo_terminal(bool enable) {
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode );

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}

int main(int argc, char** argv) {
    string path = "/Users/kangdroid/wol_conf.json";
    string url;
    string mac_addr;
    // Parse it.
    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            if (!strcmp(argv[i], "--credential_info")) {
                if (i < argc-1) {
                    i++;
                    path = string(argv[i]);
                } else {
                    cout << "\"--credential_info\" specified, but no path was found." << endl;
                }
            }
        }
    }

    // Parse setting file
    ifstream input_file(path);
    Json::Reader json_reader;
    Json::Value main_json;
    if (!json_reader.parse(input_file, main_json)) {
        cout << "Somehow, parse failed" << endl;
        return -1;
    }

    // For now, this program only supports single computer.
    Json::Value cur_working = main_json[0];
    url = "http://" + cur_working["ip_address"].asString() + "/cgi-bin/wol_apply.cgi?act=wakeup&mac=" + cur_working["mac_address"].asString();

    // Get str and pw
    string id = cur_working["username"].asString();
    set_echo_terminal(false);
    string pw;
    cin >> pw;
    set_echo_terminal(true);

    // Request part
    http_client_config config;
    credentials cred(id,pw);
    config.set_credentials(cred);

    http_client client(url, config);
    http_request request_tpr (methods::GET);
    // request_tpr.headers().add("Accept", "application/vnd.github.v3+json");
    try {
        client.request(request_tpr).then([] (http_response hr) {
        }).wait();
    } catch (const exception& expn) {
    }
    return 0;
}