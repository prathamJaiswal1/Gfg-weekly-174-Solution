#include<bits/stdc++.h>
using namespace std;

const int mod=1e9+7;
 int distributeBalls(int n) {
     int ans=1;
     for(int i=1;i<=n;i++){
        ans=(ans*2)%mod;
     }
     return ans-2;
}
void solve(){
    int n;cin>>n;
    cout<<distributeBalls(n)<<endl;
}
int main(){
    solve();
    return 0;
}