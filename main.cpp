#include <bits/stdc++.h>
using namespace std;


string str;
map<int, int> parentheses_match;


string input() {

    string tmp, res;

    getline(cin, tmp);

    for (auto chr: tmp)
        if (chr != ' ')
            res.push_back(chr);

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
