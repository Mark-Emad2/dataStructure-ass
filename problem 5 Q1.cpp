#include <iostream>
#include <stack>
using namespace std;

class calc {
private:
    string infixtopostfix(const string& infix ) {
        string postfix = "";
        int prev = '\0';                // like NULL
        stack<char> st;
        char ch;
        for ( int i=0 ; i <infix.length();i++) {
            ch = infix[i];

            if (ch == ' ') {
                continue;
            }
            else if (isdigit(ch)) {
                while (i < infix.length() && isdigit(infix[i])) {
                    postfix+=infix[i];
                    i++;
                }
                i--;
                postfix+= ' ';
            }
            else if (ch == '(') {
                st.push(ch);
            }
            else if (ch == ')') {
                while (!st.empty() && st.top() != '(') {
                    postfix = postfix + st.top() + ' ';
                    st.pop();
                }
                if (!st.empty()) st.pop();
            }
            else {
                if ((ch == '-' && prev == '\0') || (ch == '-' && prev == '(')) {
                    postfix= postfix +'0' + ' ';
                }
                while (!st.empty() &&  st.top() != '(') {
                    postfix=  postfix  +st.top() + ' ';
                    st.pop();
                }
                st.push(ch);
            }
            prev = ch;
        }
        while (!st.empty()) {
            postfix= postfix + st.top()+ ' ';
            st.pop();
        }
        return postfix;
    }

public:

int evalExpression (const string& exp) {
    stack<int> st;
    string postfix = infixtopostfix(exp);
    char ch;
    for (int i = 0 ; i < postfix.length() ; i++) {
        ch = postfix[i];
        if (ch == ' ') {
            continue;
        }
        else if (isdigit(ch)) {
            string numString="";
            while (i<postfix.length() && isdigit(postfix[i])) {
                numString+=postfix[i];
                i++;
            }
            int N = stoi(numString) ;       // stoi >> string to int
            st.push(N);
            i--;
        }
        else {
            int num2 = st.top();
            st.pop();
            int num1 = st.top();
            st.pop();

            if (ch == '+') st.push(num1 + num2);
            else if (ch == '-') st.push(num1 - num2);
        }
    }

    return st.top();
}
};








int main() {

    calc cal;
    string exp = " (1 + 2 - 5 - (15+2) )";
    cout << cal.evalExpression(exp)<<"\n";


    string hhh = "-1+2+(-1)";
    cout << cal.evalExpression(hhh)<<"\n";



    return 0;
}