#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <stdlib.h>

using namespace std;

typedef set<string> s_s;
typedef map<string, unsigned int> m_s_ui;

// should we keep all entities? regardless of freq?
const bool KEEP_ALL_ENTITIES = true;

int main(int argc, char **argv)
{
    // arg handling
    if (argc!=4) {
        cerr << "usage: " << argv[0] << " <file> <lowerbound> <upperbound>" << endl;
        return 2;
    }
    const string input_file = string(argv[1]);
    const float lower_bound_percentage = atof(argv[2]);
    if (lower_bound_percentage < 0.0 || lower_bound_percentage > 1.0) {
        cerr << "usage: " << argv[0] << " <file> <lowerbound (0.0 -> 1.0)> <upperbound>" << endl;
        return 2;
    }
    const float upper_bound_percentage = atof(argv[3]);
    if (upper_bound_percentage < 0.0 || upper_bound_percentage > 1.0) {
        cerr << "usage: " << argv[0] << " <file> <lowerbound> <upperbound (0.0 -> 1.0)>" << endl;
        return 2;
    }

    // read file
    ifstream file(input_file.c_str());
    if (!file.is_open()) {
        cerr << "couldn't open file [" << input_file << "], sad panda" << endl;
        return -1;
    }

    // make one pass over the file counting the number of documents
    // each token appears in
    string line;
    m_s_ui token_document_freq;
    unsigned int num_docs = 0;
    while (getline(file, line)) {
        // tokenise document
        istringstream iss(line, istringstream::in);
        s_s tokens;
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             inserter(tokens, tokens.begin()));
        // count tokens
        for (s_s::iterator it=tokens.begin(); it!=tokens.end(); ++it)
            ++token_document_freq[*it];
        // track number docs
        ++num_docs;
    }
    file.close();

    // decide what the limits will be, a token's freq
    // will have to be within this range to be kept
    const unsigned int lower_bound = num_docs * lower_bound_percentage;
    const unsigned int upper_bound = num_docs * upper_bound_percentage;
    cerr << "num_docs=" << num_docs
         << " upper_bound=" << upper_bound
         << " lower_bound=" << lower_bound << endl;

    // decide what tokens to keep
    s_s tokens_to_keep;

    // keep other values in range and all entities
    unsigned int num_tokens_to_keep = 0;
    unsigned int num_tokens_to_discard = 0;
    unsigned int num_entities_kept = 0;
    const string entity_marker = "entity/";
    for(m_s_ui::iterator it=token_document_freq.begin(); it!=token_document_freq.end(); ++it) {
        if (KEEP_ALL_ENTITIES && equal(entity_marker.begin(), entity_marker.end(), it->first.begin())) {
            tokens_to_keep.insert(it->first);
            ++num_entities_kept;
        }
        else if (it->second >= lower_bound && it->second <= upper_bound) {
            tokens_to_keep.insert(it->first);
            ++num_tokens_to_keep;
        }
        else {
            ++num_tokens_to_discard;
        }
    }
    cerr << "num_tokens_to_keep=" << num_tokens_to_keep
         << " num_tokens_to_discard=" << num_tokens_to_discard
         << " num_entities_kept=" << num_entities_kept << endl;

    // make another pass over file, only emitting tokens that we decided to keep
    file.open(input_file.c_str());
    if (!file.is_open()) {
        cerr << "couldn't open file [" << input_file << "] second time?!, extremely sad panda" << endl;
        return -1;
    }

    while (getline(file, line)) {
        // tokenise document in same way
        string token;
        istringstream iss(line, istringstream::in);
        // only emit tokens in keep list
        while(iss >> token) {
            if (tokens_to_keep.find(token) != tokens_to_keep.end()) {
                cout << token << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
