#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <iterator>

using namespace std;

typedef set<string> ss;
typedef map<string,int> msi;

/*
    slurp stdin and
    emit
     token TAB n
     ...
    to denote token occured on n distinct lines
*/

int main(int argc, char **argv)
{
    msi freqs;
    string line;
    while (getline(cin, line))
    {
        // unique the tokens
        istringstream iss(line, istringstream::in);
        ss unique_tokens;
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             inserter(unique_tokens, unique_tokens.begin()));
        // add unique tokens to freq table
        for (ss::iterator it=unique_tokens.begin(); it!=unique_tokens.end(); ++it)
            ++freqs[*it];
    }
    // dump
    for(msi::iterator it=freqs.begin(); it!=freqs.end(); ++it)
        cout << it->first << "\t" << it->second << "\n";
}
