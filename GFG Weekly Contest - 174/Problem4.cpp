struct Node {
    int maxlen, prelen, suflen, start, end, len;
    Node() {
        maxlen = prelen = suflen = len = 0;
        start = -1, end = -1;
    }
    Node(int val) {
        maxlen = prelen = suflen = len = 1;
        start = val, end = val;
    }
};

class segmentTree {
    vector<Node> seg;
    int n;
    
    Node merge(Node &left, Node &right) {
        Node par;
        par.maxlen = max(left.maxlen, right.maxlen);
        par.start = left.start;
        par.end = right.end;
        par.len = left.len + right.len;
        
        if (left.end <= right.start) {
            par.maxlen = max(par.maxlen, left.suflen + right.prelen);
        }

        par.prelen = left.prelen;
        if (left.prelen == left.len && left.end <= right.start) {
            par.prelen = left.len + right.prelen;
        }

        par.suflen = right.suflen;
        if (right.suflen == right.len && left.end <= right.start) {
            par.suflen = left.suflen + right.len;
        }

        return par;
    }

    void build(int node, int low, int high, vector<int> &arr) {
        if (low == high) {
            seg[node] = Node(arr[low]);
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * node + 1, low, mid, arr);
        build(2 * node + 2, mid + 1, high, arr);
        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    void update(int node, int low, int high, int pos, int val) {
        if (low == high) {
            seg[node] = Node(val);
            return;
        }
        int mid = (low + high) >> 1;
        if (pos <= mid) {
            update(2 * node + 1, low, mid, pos, val);
        } else {
            update(2 * node + 2, mid + 1, high, pos, val);
        }
        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    Node query(int node, int low, int high, int qs, int qe) {
        if (qe < low || qs > high) {
            return Node();
        }
        if (qs <= low && high <= qe) {
            return seg[node];
        }
        int mid = (low + high) >> 1;
        Node left = query(2 * node + 1, low, mid, qs, qe);
        Node right = query(2 * node + 2, mid + 1, high, qs, qe);
        return merge(left, right);
    }

public:
    segmentTree(vector<int> &arr) {
        n = arr.size();
        seg.resize(4 * n);
        build(0, 0, n - 1, arr);
    }

    void update(int pos, int val) {
        update(0, 0, n - 1, pos, val);
    }

    Node query(int qs, int qe) {
        return query(0, 0, n - 1, qs, qe);
    }
};

class Solution {
public:
    vector<int> longestSubarray(int n, vector<int> &arr, int m, vector<vector<int>> &q) {
        segmentTree st(arr);
        vector<int> ans;
        for (int i = 0; i < m; i++) {
            int a = q[i][0], b = q[i][1], c = q[i][2];
            if (a == 0) {
                ans.push_back(st.query(b, c).maxlen);
            } else {
                st.update(b, c); 
            }
        }
        return ans;
    }
};
