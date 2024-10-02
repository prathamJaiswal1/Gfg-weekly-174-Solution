#include<bits/stdc++.h>
using namespace std;
unordered_set<string>st;
//     void pal(string str){
//       int n=str.length();
//       for(int i=0;i<n;i++){
//           int l=i,r=i;
//           while(l>=0 and r<n and str[l]==str[r]) {
//               st.insert(str.substr(l,r-l+1));
//               l--;
//               r++;
//           }
//           l=i;
//           r=i+1;
//           while(l>=0 and r<n and str[l]==str[r]) {
//               st.insert(str.substr(l,r-l+1));
//               l--;
//               r++;
//           }
//       }
//   }
    void lps(string s) {
         int n = s.size();
         vector<vector<bool>> dp(n, vector<bool>(n, false));
         for (int len = 1; len <= n; len++) {
             for (int i = 0, j = len - 1; j < n; i++, j++) {
                 if (len == 1) {
                     dp[i][j] = true;
                 } else if (len == 2) {
                     dp[i][j] = (s[i] == s[j]); 
                 } else {
                     dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1]; 
                 }

                 if (dp[i][j]) {
                    st.insert(s.substr(i,len));
                 }
             }
         }
    }
    int longestCommonPalindrome(string& s, string& t) {
        // code here
        lps(s);
        int ans=0;
        int n=t.size();
        for(auto &str:st){
            if(str.size()>ans && t.find(str)!=-1){
                int len=str.size();
                ans=max(ans,len);
            }
        }
        return ans;
    }
void solve(){
    string s,t;cin>>s>>t;
    cout<<longestCommonPalindrome(s,t)<<endl;
}
int main(){
    solve();
    return 0;
}