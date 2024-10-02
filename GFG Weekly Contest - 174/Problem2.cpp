#include<bits/stdc++.h>
using namespace std;
int longestSubarray(int n, vector<int> &v, int k) {
        // code here
        if(n==1){
            return v[0]%k==0;
        }
        map<int,int>m;
        m[0]=-1;
        long long curr=0;
        int i=0,j=1,sub=0;
        curr=v[i];
        if(m.find(curr%k) != m.end()){
            sub=1;
        }else{
            m[curr%k]=0;
        }
        while(j<n){
           if(v[j]>=v[j-1]){
               curr+=v[j];
               int find=curr%k;
               if(m.find(find) != m.end()){
                   sub=max(sub,j-m[find]);
               }
              else m[find]=j;
           }else{
               curr=v[j];
            //   cout<<curr<<" ";
               m.clear();
               m[0]=j-1;
               if(m.find(curr%k) != m.end()){
                   sub=max(sub,j-m[curr%k]);
               }
              else m[curr%k]=j;
           }
        //   cout<<sub<<endl;
           j++;    
        }
        return sub;
}
void solve(){
    int n,k;cin>>n>>k;
    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<longestSubarray(n,arr,k)<<endl;
}
int main(){
    solve();
    return 0;
}