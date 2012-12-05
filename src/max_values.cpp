#include <iostream>
#include <map>

/*
    given some token TAB count input keep track of max values

    eg input
     a 2
     b 4
     a 4

    eg output
     a 4
     b 4

    does not require input sorted but will hold entire corpus in mem.

    this code has no safeguards and will segfault at it's earliest convenience
*/

using namespace std;

typedef map<string,int> msi;

int main(int argc, char **argv)
{
    msi freqs;
    string token;
    int count;
    while (cin >> token >> count)
        freqs[token] = max(freqs[token], count);
    for(msi::iterator it=freqs.begin(); it!=freqs.end(); ++it)
        cout << it->first << "\t" << it->second << "\n";
    return 0;
}
