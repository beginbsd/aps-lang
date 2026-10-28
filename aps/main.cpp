#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

vector<string> keywords =
{
    "ADD", "SUB", "MUL", "DIV", "MOD", "EQ", "print", "input", "goto", "while"
};

// ================= 高精度运算库 =================
namespace BigInt
{
    bool combig(string a, string b)
    {
        if (a[0] == '-')
        {
            return false;
        }
        if (b[0] == '-')
        {
            return true;
        }
        if (a.size() != b.size())
        {
            return a.size() > b.size();
        }
        return a > b;
    }

    bool comlittle(string a, string b)
    {
        if (a[0] == '-')
        {
            return true;
        }
        if (b[0] == '-')
        {
            return false;
        }
        if (a.size() != b.size())
        {
            return a.size() < b.size();
        }
        return a < b;
    }

    bool comequal(string a, string b)
    {
        return a == b;
    }

    string add(string a, string b)
    {
        vector<int> va, vb, vc;
        int lenA = (int)a.size();
        int lenB = (int)b.size();

        if (lenA > lenB)
        {
            b = string(lenA - lenB, '0') + b;
        }
        else if (lenB > lenA)
        {
            a = string(lenB - lenA, '0') + a;
        }

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        for (int i = 0; i < (int)a.size(); i++)
        {
            va.push_back(a[i] - '0');
        }
        for (int i = 0; i < (int)b.size(); i++)
        {
            vb.push_back(b[i] - '0');
        }

        int t = 0;
        for (int i = 0; i < (int)a.size(); i++)
        {
            int sum = va[i] + vb[i] + t;
            vc.push_back(sum % 10);
            t = sum / 10;
        }

        if (t >= 1)
        {
            vc.push_back(1);
        }

        reverse(vc.begin(), vc.end());
        string s;

        for (int i = 0; i < (int)vc.size(); i++)
        {
            s += to_string(vc[i]);
        }

        size_t pos = s.find_first_not_of('0');
        if (pos == string::npos)
        {
            return "0";
        }
        return s.substr(pos);
    }

    string sub(string a, string b)
    {
        vector<int> va, vb, vc;
        int lenA = (int)a.size();
        int lenB = (int)b.size();

        if (lenA > lenB)
        {
            b = string(lenA - lenB, '0') + b;
        }
        else if (lenB > lenA)
        {
            a = string(lenB - lenA, '0') + a;
        }

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        for (int i = 0; i < (int)a.size(); i++)
        {
            va.push_back(a[i] - '0');
        }
        for (int i = 0; i < (int)b.size(); i++)
        {
            vb.push_back(b[i] - '0');
        }

        int borrow = 0;
        for (int i = 0; i < (int)a.size(); i++)
        {
            int diff = va[i] - vb[i] - borrow;
            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            vc.push_back(diff);
        }

        while (vc.size() > 1 && vc.back() == 0)
        {
            vc.pop_back();
        }

        reverse(vc.begin(), vc.end());
        string s;
        for (int i = 0; i < (int)vc.size(); i++)
        {
            s += to_string(vc[i]);
        }
        return s;
    }

    string mul(string a, string b)
    {
        vector<int> va, vb;
        vector<string> vc, c;

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        for (int i = 0; i < (int)a.size(); i++)
        {
            va.push_back(a[i] - '0');
        }
        for (int i = 0; i < (int)b.size(); i++)
        {
            vb.push_back(b[i] - '0');
        }

        for (int i = 0; i < (int)va.size(); i++)
        {
            int tt = 0;
            for (int j = 0; j < (int)vb.size(); j++)
            {
                vc.push_back(to_string((va[i] * vb[j] + tt) % 10));
                tt = (va[i] * vb[j] + tt) / 10;
            }
            if (tt > 0)
            {
                vc.push_back(to_string(tt));
            }
            string m;
            for (int j = 0; j < (int)vc.size(); j++)
            {
                m += vc[j];
            }
            reverse(m.begin(), m.end());
            m += string(i, '0');
            c.push_back(m);
            vc.clear();
        }

        string s = "0";
        for (int i = 0; i < (int)c.size(); i++)
        {
            s = add(s, c[i]);
        }

        size_t pos = s.find_first_not_of('0');
        if (pos == string::npos)
        {
            return "0";
        }
        return s.substr(pos);
    }

    string div(string a, string b)
    {
        if (b == "0")
        {
            return "0";
        }
        if (comlittle(a, b))
        {
            return "0";
        }

        string rem = "0";
        string res = "";

        for (int pos = 0; pos < (int)a.size(); pos++)
        {
            string q = "0";
            rem = mul(rem, "10");
            rem = add(rem, to_string(a[pos] - '0'));

            while (comlittle(rem, b) == false)
            {
                rem = sub(rem, b);
                q = add(q, "1");
            }
            res += q;
        }

        size_t p = res.find_first_not_of('0');
        if (p == string::npos)
        {
            return "0";
        }
        return res.substr(p);
    }
}
using namespace BigInt;
// ================================================

vector<string> vs;
map<string, string> mp;
map<string, int> position_goto;
map<int, int> position_while;
stack<int> st_while;

string get_val_str(string s)
{
    if (s[0] == '$')
    {
        if (mp.find(s) == mp.end())
        {
            throw runtime_error("Var Undefined: " + s);
        }
        return mp[s];
    }
    return s;
}

void MAIN(int k)
{
    while (k < (int)vs.size())
    {
        stack<string> st;
        stringstream ss(vs[k]);
        string token;

        while (ss >> token)
        {
            st.push(token);
        }

        if (st.empty())
        {
            k++;
            continue;
        }

        string cmd = st.top();
        bool jumped = false;

        try
        {
            if (cmd == "ADD")
            {
                st.pop();
                string a = get_val_str(st.top());
                st.pop();
                string b = get_val_str(st.top());
                st.pop();
                string n = st.top();
                st.pop();
                mp[n] = add(a, b);
            }
            else if (cmd == "SUB")
            {
                st.pop();
                string a = get_val_str(st.top());
                st.pop();
                string b = get_val_str(st.top());
                st.pop();
                string n = st.top();
                st.pop();
                if (combig(b, a))
                {
                    mp[n] = sub(b, a);
                }
                else
                {
                    mp[n] = "-" + sub(a, b);
                }
            }
            else if (cmd == "MUL")
            {
                st.pop();
                string a = get_val_str(st.top());
                st.pop();
                string b = get_val_str(st.top());
                st.pop();
                string n = st.top();
                st.pop();
                mp[n] = mul(a, b);
            }
            else if (cmd == "DIV")
            {
                st.pop();
                string a = get_val_str(st.top());
                st.pop();
                string b = get_val_str(st.top());
                st.pop();
                string n = st.top();
                st.pop();
                if (a == "0")
                {
                    throw runtime_error("Div by 0");
                }
                mp[n] = div(b, a);
            }
            else if (cmd == "MOD")
            {
                st.pop();
                string a = get_val_str(st.top());
                st.pop();
                string b = get_val_str(st.top());
                st.pop();
                string n = st.top();
                st.pop();
                string q = div(b, a);
                string prod = mul(q, a);
                mp[n] = sub(b, prod);
            }
            else if (cmd == "EQ")
            {
                st.pop();
                string a = get_val_str(st.top());
                st.pop();
                string b = get_val_str(st.top());
                st.pop();
                string n = st.top();
                st.pop();
                if (a == b)
                {
                    mp[n] = "1";
                }
                else
                {
                    mp[n] = "0";
                }
            }
            else if (cmd == "print")
            {
                st.pop();
                if (st.empty())
                {
                    throw runtime_error("Empty print");
                }
                string target = st.top();
                st.pop();
                if (target[0] == '$')
                {
                    cout << get_val_str(target) << endl;
                }
                else if (target[0] == '@')
                {
                    cout << target.substr(1) << endl;
                }
                else
                {
                    cout << target << endl;
                }
            }
            else if (cmd == "input")
            {
                st.pop();
                if (st.empty())
                {
                    throw runtime_error("Empty input");
                }
                string n = st.top();
                st.pop();
                string val;
                cin >> val;
                mp[n] = val;
            }
            else if (cmd == "goto")
            {
                st.pop();
                if (st.empty())
                {
                    throw runtime_error("Empty goto");
                }
                string n = st.top();
                st.pop();
                auto it = position_goto.find(n);
                if (it != position_goto.end())
                {
                    k = it->second;
                    jumped = true;
                }
                else
                {
                    throw runtime_error("No label " + n);
                }
            }
            else if (cmd == "while")
            {
                st.pop();
                string right = st.top();
                st.pop();
                string op = st.top();
                st.pop();
                string left = st.top();
                st.pop();

                string l = get_val_str(left);
                string r = get_val_str(right);
                bool cond = false;

                if (op == "==")
                {
                    cond = comequal(l, r);
                }
                else if (op == ">=")
                {
                    cond = (comequal(l, r) || combig(l, r));
                }
                else if (op == "<=")
                {
                    cond = (comequal(l, r) || comlittle(l, r));
                }
                else if (op == ">")
                {
                    cond = combig(l, r);
                }
                else if (op == "<")
                {
                    cond = comlittle(l, r);
                }
                else
                {
                    throw runtime_error("Bad op");
                }

                if (!cond)
                {
                    k = position_while[k] + 1;
                    jumped = true;
                }
            }
            else if (cmd == "!}")
            {
                k = position_while[k];
                jumped = true;
            }
            else
            {
                if (st.size() == 2)
                {
                    string val = st.top();
                    st.pop();
                    string var = st.top();
                    st.pop();
                    if (var[0] == '$')
                    {
                        mp[var] = val;
                    }
                }
            }
        }
        catch (exception& e)
        {
            cout << "ERROR: " << e.what() << endl;
            return;
        }

        if (!jumped)
        {
            k++;
        }
    }
}

int main()
{
    string s;

    while (getline(cin, s))
    {
        if (s.empty())
        {
            continue;
        }
        vs.push_back(s);
    }

    for (int i = 0; i < (int)vs.size(); i++)
    {
        vector<string> v;
        stringstream ss(vs[i]);
        string token;

        while (ss >> token)
        {
            v.push_back(token);
        }

        if (v.size() == 1)
        {
            string label = v[0];
            if (label.back() == ':')
            {
                label.pop_back();
            }
            position_goto[label] = i;
        }
    }

    for (int i = 0; i < (int)vs.size(); i++)
    {
        if (vs[i].length() >= 5 && vs[i].substr(vs[i].length() - 5) == "while")
        {
            st_while.push(i);
        }

        if (vs[i] == "!}")
        {
            int top = st_while.top();
            st_while.pop();
            position_while[top] = i;
            position_while[i] = top;
        }
    }

    MAIN(0);

    return 0;
}