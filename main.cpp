#include <bits/stdc++.h>
using namespace std;


string str;
char _not = '~', _and = 'A', _or = 'O', _con = 'C';
map<int, int> parentheses_match;


bool is_atom(int ind) {
    return ((str[ind] >= 'a') && (str[ind] <= 'z'));
}


bool is_atom(char chr) {
    return ((chr >= 'a') && (chr <= 'z'));
}


bool is_and_or_con(int ind) {
    return str[ind] == _and || str[ind] == _or || str[ind] == _con;
}


bool is_and_or_con(char chr) {
    return chr == _and || chr == _or || chr == _con;
}


string input() {

    string tmp, res;

    getline(cin, tmp);

    for (int i = 0; i < tmp.size(); i++) {
        char chr = tmp[i];
        if (chr != ' ') {
            res.push_back(chr);
            if (!is_atom(chr) && !is_and_or_con(chr) && chr != '(' && chr != ')' && chr != _not) {
                cout << "Not a valid formula.\nInvalid characters.\n" << chr;
                exit(0);
            }
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

    if (r - l < 0 || l >= str.size() || r > str.size()) {
        return true;
    }

    if (r - l == 1) {
        return is_atom(l);
    }

    if (str[l] == '(') {
        int close = parentheses_match[l];
        return is_valid(l + 1, close) && is_valid(close + 1, r);
    }

    if (str[l] == _not) {
        return is_valid(l + 1, r) && (r - l) > 1;
    }

    if (is_atom(l)) {
        return is_and_or_con(l + 1) && is_valid(l + 2, r) && (r - l) > 2;
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
