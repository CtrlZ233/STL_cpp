#include<list>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
using namespace std;
#include<string>
#include<memory.h>
#include<unordered_map>
#include<queue>
#include<stack>
#include<math.h>


//  Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct q_elem {
	TreeNode* root;
	int depth;
	long long int position;
	q_elem(TreeNode* n, int d, int p) : root(n), depth(d), position(p) {} 
};

long long int max (long long int a, long long b){
	return a > b ? a : b;
}

int widthOfBinaryTree(TreeNode* root) {
	int ans = 0;
	int cur_depth = 0;
	long long int left = 0;
	queue<q_elem> Q;
	Q.push(q_elem(root, 0, 0));
	while(!Q.empty()){
		q_elem q = Q.front(); Q.pop();
		if(q.depth != cur_depth){
			cur_depth = q.depth;
			left = q.position;
		}
		ans = max(q.position-left, ans);
		if(q.root->left) Q.push(q_elem(q.root->left, q.depth+1, q.position*2+1));
		if(q.root->right) Q.push(q_elem(q.root->right, q.depth+1, q.position*2+2));
	}
	return ans + 1;

}

// int main(){
// 	TreeNode* a = new TreeNode(1);
// 	TreeNode* b = new TreeNode(3);
// 	TreeNode* c = new TreeNode(2);
// 	TreeNode* d = new TreeNode(5);
// 	a->left = b;
// 	a->right = c;
// 	b->left = d;
// 	int ans = widthOfBinaryTree(a);
// 	system("pause");
// }
int main(){
	int i = 0;
	int j = 1;
	int a = i > j ? i++ : j++;
	cout << i << endl;
	cout << j << endl;
	
	system("pause");
}

