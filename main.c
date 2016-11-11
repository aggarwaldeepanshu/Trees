#include<stdio.h>
#include<stdlib.h>
#define max 100

struct node{
    int data;
    struct node *lchild;
    struct node *rchild;
};
struct node *root;
struct node *arr[max];
int front=-1,rear=-1;


struct node *insert(struct node *root,int n);
void preorder(struct node *root);
void inorder(struct node *root);
void postorder(struct node *root);
void insert_queue(struct node *ptr);
struct node *deque();
int queue_empty();
void level_order(struct node *root);
int height(struct node *root);

int main(void)
{
    int i,n,key;
    printf("Enter the size of the tree\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&key);
       root=insert(root,key);
    }
    printf("Preorder Traversal\n");
    preorder(root);
    printf("\nInorder Traversal\n");
    inorder(root);
    printf("\nPostorder Traversal\n");
    postorder(root);
    printf("\nLevel Order Traversal\n");
    level_order(root);
    printf("\n");
    printf("Height of Binary Tree is %d\n",height(root));
}
//function to insert node in binary tree
struct node *insert(struct node *root,int key)
{
    struct node *ptr,*ptr1,*temp;
    ptr=root;
    ptr1=NULL;
    temp=(struct node*)malloc(sizeof(struct node));
    while(ptr!=NULL)
    {
        ptr1=ptr;
        if(ptr->data>key)
            ptr=ptr->lchild;
        else if(ptr->data<key)
            ptr=ptr->rchild;
        else
        {
            printf("Value already exist\n");
            return root;
        }
    }
    temp->data=key;
    temp->lchild=NULL;
    temp->rchild=NULL;
    if(ptr1==NULL)
        root=temp;
    else if(ptr1->data>key)
        ptr1->lchild=temp;
    else
        ptr1->rchild=temp;
    return root;
}
//preorder traversal in binary tree
void preorder(struct node *root)
{
    if(root==NULL)
        return;
    
    printf("%d\t",root->data);
    preorder(root->lchild);
    preorder(root->rchild);
    
}
//inorder traversal in binary tree
void inorder(struct node *root)
{
    if(root==NULL)
        return;
    
    inorder(root->lchild);
    printf("%d\t",root->data);
    inorder(root->rchild);
    
}
//postorder traversal in binary tree
void postorder(struct node *root)
{
    if(root==NULL)
        return;
    
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d\t",root->data);
    
}
//level order traversal in binary tree
void level_order(struct node *root)
{
    struct node *ptr;
    ptr=root;
    if(ptr==NULL)
    {
        printf("Empty Tree\n");
        return;
    }
    insert_queue(ptr);
    while(!queue_empty())
    {
        ptr=deque();
        printf("%d\t",ptr->data);
        if(ptr->lchild!=NULL)
            insert_queue(ptr->lchild);
        if(ptr->rchild!=NULL)
            insert_queue(ptr->rchild);
    }
}
//function to insert address of node in queue
void insert_queue(struct node *ptr)
{
    if(rear==max-1)
    {
        printf("Overflow\n");
        return;
    }
    if(front==-1)
        front=0;
    arr[++rear]=ptr;
}
//function to pop address of node in queue
struct node *deque()
{
    struct node *ptr1;
    if(queue_empty())
    
        printf("Underflow\n");
    else
        ptr1=arr[front];
    front+=1;
    return ptr1;
}
//to check if queue is empty or not
int queue_empty()
{
    if(front==-1||front==rear+1)
        return 1;
    else
        return 0;
}
//to calculate height of binary tree
int height(struct node *root)
{
    int left,right;
    if(root==NULL)
        return 0;
    left=height(root->lchild);
    right=height(root->rchild);
    if(left>=right)
        return 1+left;
    else
        return 1+right;
}