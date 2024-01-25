#include <bits/stdc++.h>
using namespace std;

typedef pair<int, char> pic;


string str;

char _not = '~', _and = 'A', _or = 'O', _imp = 'C';

string 
    lat_not = "neg",
    lat_or = "vee",
    lat_and = "wedge",
    lat_imp = "rightarrow";

map<int, int> parentheses_match;


bool is_atom(char chr) {
    return ((chr >= 'a') && (chr <= 'z'));
}


bool is_atom(int ind) {
    return is_atom(str[ind]);
}


bool is_and_or_imp(char chr) {
    return chr == _and || chr == _or || chr == _imp;
}


bool is_and_or_imp(int ind) {
    return is_and_or_imp(str[ind]);
}


pic find_symbol(string str, int ind) {
    bool 
        can_be_not = false,
        can_be_or = false,
        can_be_and = false, 
        can_be_imp = false;


    if (str[ind + 1] == 'n') {
        can_be_not = true;
    }   
    else if (str[ind + 1] == 'v') {
        can_be_or = true;
    }     
    else if (str[ind + 1] == 'w') {
        can_be_and = true;
    }
    else if (str[ind + 1] == 'r') {
        can_be_imp = true;
    }

    if (!(can_be_not || can_be_or || can_be_and || can_be_imp)) {
        cout << "Not a valid formula.\nInvalid latex symbol.\n";
        exit(0);
    }

    string other;
    char replace_char;
    int replace_ind;

    if (can_be_not) {
        other = lat_not;
        replace_char = _not;
        replace_ind = 3;
    }
    else if (can_be_or) {
        other = lat_or;
        replace_char = _or;
        replace_ind = 3;
    }
    else if (can_be_and) {
        other = lat_and;
        replace_char = _and;
        replace_ind = 5;
    }
    else if (can_be_imp) {
        other = lat_imp;
        replace_char = _imp;
        replace_ind = 10;
    }
    
    if (str.size() < ind + 1 + other.size()) {
        cout << "Not a valid formula.\nInvalid latex symbol.\n";
        exit(0);
    }

    for (int i = ind + 1, j = 0; j < other.size(); i++, j++) {
        if (other[j] != str[i]) {
        cout << "Not a valid formula.\nInvalid latex symbol.\n";
        exit(0);
        }
    }

    return {replace_ind, replace_char};

}


string input() {

    string tmp, res;
    res = "";

    getline(cin, tmp);

    for (int i = 0; i < tmp.size(); i++) {
        char chr = tmp[i];
        
        if (chr == ' ')
            continue;

        res += chr;
    }

    tmp = res;
    res = "";

    for (int i = 0; i < tmp.size(); i++) {
        char chr = tmp[i];
        
        if (chr == '\\') {
            pic symbol = find_symbol(tmp, i);
            res += symbol.second;
            i += symbol.first;
        }
        
        else if (chr == '(' || chr == ')' || is_atom(chr)) {
            res += chr;
        }

        else {
            cout << "Not a valid formula.\nInvalid characters.\n";
            exit(0);
        }
    }

    return res;
}


// find the pairs of parentheses and return false if the parentheses are not valid
bool  fill_parentheses_match() {

    vector<int> stack;

    for (int i = 0; i < str.size(); i++) {

        char chr = str[i];

        if (chr == '(') {
            stack.push_back(i);
        }

        else if (chr == ')') {
            if (stack.empty())
                return false;
            int open = stack.back();
            stack.pop_back();
            parentheses_match[open] = i;
        }

    }

    return stack.empty();

}


bool is_valid(int l, int r) {

    if (r - l == 0) {
        return false;
    }

    if (r - l == 1) {
        return is_atom(l);
    }

    if (str[l] == '(') {
        int close = parentheses_match[l];
        if (close + 1 == r) {
            return is_valid(l + 1, close);
        }
        return is_and_or_imp(close + 1) && is_valid(close + 2, r);
    }

    if (str[l] == _not) {
        return is_valid(l + 1, r);
    }

    if (is_atom(l)) {
        return is_and_or_imp(l + 1) && is_valid(l + 2, r);
    }

    return false;

}


int main() {

    str = input();

    if (!fill_parentheses_match()) {
        cout << "Not a valid formula.\nInvalid parentheses format.\n";
        return 0;
    }

    cout << (is_valid(0, str.size())? "Valid": "Invalid") << "\n";

    return 0;
}
