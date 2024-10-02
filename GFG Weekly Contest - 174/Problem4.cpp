#include<bits/stdc++.h>
using namespace std;

struct Node {
    int maxLen, prefixLen, suffixLen; // longest non-decreasing subarray, prefix and suffix lengths
    int start, end; // range of values at the ends of the segment

    Node() : maxLen(0), prefixLen(0), suffixLen(0), start(-1), end(-1) {}
    Node(int value) : maxLen(1), prefixLen(1), suffixLen(1), start(value), end(value) {}
};

class SegmentTree {
    vector<Node> tree;
    vector<int> arr;
    int n;

    Node merge(Node left, Node right) {
        Node res;
        res.start = left.start;
        res.end = right.end;

        // Merge the two segments
        res.maxLen = max(left.maxLen, right.maxLen);
        if (left.end <= right.start) { // If the segments can be merged
            res.maxLen = max(res.maxLen, left.suffixLen + right.prefixLen);
        }
        res.prefixLen = left.prefixLen;
        if (left.prefixLen == (left.end - left.start + 1) && left.end <= right.start) {
            res.prefixLen += right.prefixLen;
        }

        res.suffixLen = right.suffixLen;
        if (right.suffixLen == (right.end - right.start + 1) && left.end <= right.start) {
            res.suffixLen += left.suffixLen;
        }

        return res;
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = Node(arr[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);
        tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return Node();
        if (ql <= l && qr >= r) return tree[idx];

        int mid = (l + r) / 2;
        Node left = query(2 * idx, l, mid, ql, qr);
        Node right = query(2 * idx + 1, mid + 1, r, ql, qr);
        return merge(left, right);
    }

    void update(int idx, int l, int r, int pos, int value) {
        if (l == r) {
            // Update the value at position pos
            arr[l] = value;
            tree[idx] = Node(value);
            return;
        }

        int mid = (l + r) / 2;
        if (pos <= mid) {
            update(2 * idx, l, mid, pos, value); // Update the left child
        } else {
            update(2 * idx + 1, mid + 1, r, pos, value); // Update the right child
        }
        // Rebuild the current node after the update
        tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
    }

public:
    SegmentTree(const vector<int>& inputArr) {
        arr = inputArr;
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    int query(int l, int r) {
        Node res = query(1, 0, n - 1, l, r);
        return res.maxLen;
    }

    void update(int pos, int value) {
        update(1, 0, n - 1, pos, value);
    }
};
void solve(){
    int n,q;cin>>n>>q;
    vector<int>arr(n);
    for(int i=0;i<n;i++)cin>>arr[i];
    SegmentTree st(arr);
    while(q--){
        int type,qs,qe;cin>>type>>qs>>qe;
        if(type==0){
            cout<<st.query(qs,qe)<<endl;
        }else{
            st.update(qs,qe);
        }
    }

}
int main(){
    solve();
    return 0;
}