#include "TreeNode.h"
#include "allheaders.h"
using namespace std;
TreeNode::TreeNode() : val(0), left(nullptr), right(nullptr) {};
TreeNode::TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
TreeNode::TreeNode(int x, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {};

//https://leetcode.com/problems/binary-tree-cameras/
// 0 => it's leaf, 1 => parent of leaf with camera, 2 => covered without a camera
int resCameraCover = 0;
int dfsCameraCover(TreeNode* root) {
	if (!root) return 2; //if it's covered we return 2
	int l = dfsCameraCover(root->left), r = dfsCameraCover(root->right);
	if (l == 0 or r == 0) { //if it needs camera
		resCameraCover++;   // increase camera count
		return 1;
	}
	return l == 1 or r == 1 ? 2 : 0;  //return 2 it it's covered otherwise 0(i.e. needs camera)
}
int minCameraCover(TreeNode* root) {
	return (dfsCameraCover(root) == 0 ? 1 : 0) + resCameraCover;
}


//merge K binary trees
class BSTIterator {
    std::stack<TreeNode*> s;
    void pushLeft(TreeNode* n) {
        while (n != nullptr) s.push(std::exchange(n, n->left));
    }
public:
    BSTIterator(TreeNode* root) { 
        pushLeft(root); 
    }
    bool hasNext() const { 
        return !s.empty(); 
    }
    int next() {
        auto n = s.top(); s.pop();
        pushLeft(n->right);
        return n->val;
    }
};
class PeekingIterator : public BSTIterator {
    bool peeked = false;
    int last_val = 0;
public:
    PeekingIterator(TreeNode* root) : BSTIterator(root) { }
    int peek() {
        if (peeked) return last_val;
        peeked = true;
        return last_val = BSTIterator::next();
    }
    int next() {
        if (peeked) {
            peeked = false;
            return last_val;
        }
        return BSTIterator::next();
    }
    bool hasNext() const {
        return peeked || BSTIterator::hasNext();
    }
};
std::vector<int> mergeKTrees(std::vector<TreeNode*> trees) {
    std::vector<int> res;
    std::priority_queue <std::pair<int, PeekingIterator*>,
        std::vector<std::pair<int, PeekingIterator*>>, std::greater<std::pair<int, PeekingIterator*>> > q;
    for (auto t : trees) {
        auto it = new PeekingIterator(t);
        if (it->hasNext()) q.push({ it->peek(), it });
    }
    while (!q.empty()) {
        auto p = q.top(); q.pop();
        res.push_back(p.second->next());
        if (p.second->hasNext())
            q.push({ p.second->peek(), p.second });
    }
    return res;
}


//merge 2 binary trees
void pushLeft(stack<TreeNode*>& s, TreeNode* n) {
    while (n != nullptr)
        s.push(exchange(n, n->left));
}
vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
    vector<int>res;
    stack<TreeNode*> s1, s2;
    pushLeft(s1, root1);
    pushLeft(s2, root2);
    while (!s1.empty() or !s2.empty()) {
        stack<TreeNode*>& s = s1.empty() ? s2 : s2.empty() ? s1 : s1.top()->val < s2.top()->val ? s1 : s2;
        auto n = s.top(); s.pop();
        res.push_back(n->val);
        pushLeft(s, n->right);
    }
    return res;
}
