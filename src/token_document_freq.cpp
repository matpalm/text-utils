#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <cstdlib>

using namespace std;

typedef set<string> ss;
typedef map<string,int> msi;

int main(int argc, char **argv)
{

    msi freqs;

    string line;
    while (getline(cin, line))
    {
        // unique the tokens
        istringstream iss(line, istringstream::in);
        ss unique_tokens;
        string token;
        while (iss >> token)
            unique_tokens.insert(token);
        // add unique tokens to freq table
        for (ss::iterator it=unique_tokens.begin(); it!=unique_tokens.end(); ++it)
            ++freqs[*it];
    }

    // dump
    for(msi::iterator it=freqs.begin(); it!=freqs.end(); ++it)
        cout << it->first << "\t" << it->second << "\n";
}
