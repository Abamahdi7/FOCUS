#include "Community.h"

#include <iostream>

using namespace std;

static const char* DISCORD_LINK = "https://discord.gg/QD5uPGqP";

Community::Community() {
}

Community::~Community() {
}

void Community::showDiscord() const {
    cout << "\n========== COMMUNITY ==========\n";
    cout << "Join our Discord Community:\n";
    cout << DISCORD_LINK << "\n";
    cout << "Terminal version: copy the link and open it in your browser.\n";
    cout << "================================\n";
}
