#include<iostream>
using namespace std;

struct tree{
	int key,height;
	struct tree *left,*right;
};

class avl_trees
{
	public:
		tree *new_node(int );
		tree *insert(tree *,int);
		int height(tree *);
		tree *ll(tree *);
		tree *rr(tree *);
		void inorder(tree *);
		int get_difference(tree *);
};

int avl_trees::height(tree *root)
{
	if(root==NULL)
		return 0;
	else
		return root->height;
}

tree *avl_trees::new_node(int val)
{
	tree *node=new tree;
	node->key=val;
	node->left=node->right=NULL;
	node->height=1;
	return node;
}

int max(int a,int b)
{
	return (a>b)?a:b;
}

tree *avl_trees::rr(tree *root)
{
	tree *x=root->left;
	tree *y=x->right;
	x->right=root;
	root->left=y;
	root->height=1+max(height(root->left),height(root->right));
	x->height=1+max(height(x->left),height(x->right));
	return x;
}

tree *avl_trees::ll(tree *root)
{
	tree *x=root->right;
	tree *y=x->left;
	x->left=root;
	root->right=y;
	root->height=1+max(height(root->left),height(root->right));
	x->height=1+max(height(x->left),height(x->right));
	return x;
}

int avl_trees::get_difference(tree *root)
{
	if(root==NULL)
		return 0;
	else
		return height(root->left)-height(root->right);
}

tree *avl_trees::insert(tree *root,int key)
{
	int diff;
	if(root==NULL)
		return (new_node(key));
	else if(key>root->key)
		root->right=insert(root->right,key);
	else
		root->left=insert(root->left,key);

	root->height=1+max(height(root->left),height(root->right));
	diff=get_difference(root);
	if(diff>1)
	{
		if(key<root->left->key)
			return rr(root);
		else
		{
			root->left=ll(root->left);
			return rr(root);
		}
	}
	else if(diff<-1)
	{
		if(key>root->right->key)
			return ll(root);
		else
		{
			root->right=rr(root->right);
			return ll(root);
		}
	}
	return root;
}

void avl_trees:: inorder(tree *root)
{
	if(root==NULL)
		return;
	inorder(root->left);
	cout<<root->key<<" ";
	inorder(root->right);
}

int main(void)
{
	tree *root=NULL;
	avl_trees avl;

	root=avl.insert(root,10);
	root=avl.insert(root,20);
	root=avl.insert(root,30);
	root=avl.insert(root,40);
	root=avl.insert(root,50);
	root=avl.insert(root,25);
	cout<<"Inorder traversal is: "<<endl;
	avl.inorder(root);
}
