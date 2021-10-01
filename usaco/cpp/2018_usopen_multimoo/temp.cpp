class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int r=0, l=0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ')') {
                if (l == 0)
                    r++;
                else
                    l--;
            }
            else if (s[i] == '(')
                l++;
        }
        std::cout << "l=" << l << ", r=" << r << std::endl;
        vector<string> ret;
        dfs(s, 0, l, r, ret);
        return ret;
    }
private:
    void dfs(string& s, int index, int l, int r, vector<string>& ret)
    {
        if (l == 0 && r == 0) {
            std::cout << "log0 s=" << s << std::endl;
            ret.push_back(s);
            return;
        }
        
        for (int i = index; i < s.size(); i++) {
            if (i != index && s[i] == s[i-1]) {
                std::cout << "log1 skip, i=" << i << ", index=" << index << ", s=" << s << std::endl;
                continue;
            string newS;
            if (s[i] == ')' && r != 0) {
                newS = s.erase(index, 1);
                std::cout << "log2 l=" << l << ", r=" << r << ", index=" << index << ", s=" << s << ", newS=" << newS << std::endl;
                dfs(newS, index, l, r-1, ret);
            }
            else if (s[i] == '(' && l != 0) {
                newS = s.erase(index, 1);
                std::cout << "log3 l=" << l << ", r=" << r << ", index=" << index << ", s=" << s << ", newS=" << newS << std::endl;
                dfs(newS, index, l-1, r, ret);
            }
        }
    }
};