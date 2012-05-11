#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

bool has_at_least_one_alpha_numeric(string &token) {
    for(string::iterator it=token.begin(); it!=token.end(); ++it)
        if (isalnum(*it))
            return true;
    return false;
}

int main(int argc, char **argv) {
    string line;
    string token;
    set<string> unique_tokens;
    while (getline(cin, line)) {
        // tokenise line
        istringstream iss(line, istringstream::in);
        // read and write md5 & dts
        iss >> token;
        cout << token;
        iss >> token;
        cout << " " << token;
        // rest of line through a set
        unique_tokens.clear();
        while (iss >> token) {
            // ignore short strings
            if (token.length() < 3)
                continue;
            // must have at least one alpha
            if (!has_at_least_one_alpha_numeric(token))
                continue;
            // downcase
            boost::algorithm::to_lower(token);
            // add to set
            unique_tokens.insert(token);
        }
        for (set<string>::iterator it=unique_tokens.begin(); it!=unique_tokens.end(); ++it)
            cout << " " << *it;
        cout << "\n";
    }
    return 0;
}
