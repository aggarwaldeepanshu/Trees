#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *lchild;
    struct node *rchild;
};
struct node *root;


struct node *insert(struct node *root,int n);
struct node *del3(struct node *root,struct node *par,struct node *ptr);
struct node *del2(struct node *root,struct node *par,struct node *ptr);
struct node *del1(struct node *root,struct node *par,struct node *ptr);
struct node *delete(struct node *root,int key);
void inorder(struct node *root);
struct node *max(struct node *ptr);
struct node *min(struct node *ptr);
struct node *search(struct node *ptr,int key);
struct node *insert(struct node *root,int key);

int main(void)
{
    int n,val,v=0;
    struct node *var;
    printf("Press 1 to Insert element in the Tree\nPress 2 to Search element in the Tree\nPress 3 to find element with Minimum Value in the Tree\nPress 4 to find element with Maximum value in the Tree\nPress 5 to Delete element from the Tree\nPress 6 to Print the values of the Tree\n");
    printf("Enter the choice\nEnter -1 to exit\n");
    scanf("%d",&v);
    while(v!=-1)
    {
     switch (v) {
        case 1:
            printf("Enter the value to be inserted in the tree\n");
            scanf("%d",&n);
            root=insert(root,n);
            break;
        case 2:
             printf("Enter the element to be searched\n");
            scanf("%d",&val);
            var=search(root,val);
            if(var==NULL)
                printf("Element is not present\n");
            else
                printf("Element is present\n");
            break;
        case 3:
            var=min(root);
            printf("Node with Minimum Value is %d\n",var->data);
            break;
        case 4:
            var=max(root);
            printf("Node with Maximum Value is %d\n",var->data);
            break;
        case 5:
            printf("Enter the value to be deleted\n");
            scanf("%d",&val);
             root=delete(root,val);
            break;
        case 6:
            printf("The required Tree is\n");
            inorder(root);
             printf("\n");
        default:
            break;
    }
        printf("Enter the choice\n");
        scanf("%d",&v);
    }
}

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
struct node *search(struct node *ptr,int key)
{
    while(ptr!=NULL)
    {
        if(ptr->data==key)
            return ptr;
        else if(ptr->data>key)
            ptr=ptr->lchild;
        else
            ptr=ptr->rchild;
    }
    return NULL;
}
struct node *min(struct node *ptr)
{
    if(ptr!=NULL)
        while(ptr->lchild!=NULL)
            ptr=ptr->lchild;
    return ptr;
}
struct node *max(struct node *ptr)
{
    if(ptr!=NULL)
        while(ptr->rchild!=NULL)
            ptr=ptr->rchild;
    return ptr;
}
void inorder(struct node *root)
{
    if(root==NULL)
        return;
    
    inorder(root->lchild);
    printf("%d\t",root->data);
    inorder(root->rchild);
    
}
struct node *delete(struct node *root,int key)
{
    struct node *ptr,*par;
    ptr=root;
    par=NULL;
    while (ptr!=NULL) {
        par=ptr;
        if(ptr->data==key)
            break;
        else if(ptr->data<key)
            ptr=ptr->rchild;
        else
            ptr=ptr->lchild;
    }
    if(ptr==NULL)
        printf("Invalid Input\n");
    else if(ptr->lchild!=NULL && ptr->rchild!=NULL)
        root=del1(root,par,ptr);
    else if(ptr->lchild!=NULL)
        root=del2(root,par,ptr);
    else if(ptr->rchild!=NULL)
        root=del2(root,par,ptr);
    else
        root=del3(root,par,ptr);
    return root;
}
struct node *del1(struct node *root,struct node *par,struct node *ptr)
{
    struct node *ptr1,*ptr2;
    ptr1=ptr;
    ptr2=ptr->rchild;
    while(ptr2->lchild!=NULL)
    {
        ptr1=ptr2;
        ptr2=ptr2->lchild;
    }
    ptr->data=ptr2->data;
    if(ptr2->lchild==NULL && ptr2->rchild==NULL)
        root=del3(root,ptr1,ptr2);
    else
        root=del2(root,ptr1,ptr2);
    return root;
}
struct node *del2(struct node *root,struct node *par,struct node *ptr)
{
    struct node *ptr1;
    if(ptr->lchild!=NULL)
        ptr1=ptr->lchild;
    else
        ptr1=ptr->rchild;
    if(par==NULL)
        root=ptr1;
    else if(ptr==par->lchild)
        par->lchild=ptr1;
    else
        par->rchild=ptr1;
    free(ptr);
    return root;
}

struct node *del3(struct node *root,struct node *par,struct node *ptr)
{
    if(par==NULL)
        root=NULL;
    else if(ptr==par->lchild)
        par->lchild=NULL;
    else
        par->rchild=NULL;
    free(ptr);
    return root;
}