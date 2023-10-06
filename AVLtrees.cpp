// AVL tree
#include<iostream>
using namespace std;

class Node
{
    public:
    int key;
    Node *left;
    Node *right;
    int height;
    friend class AVL;
};

class AVL
{
    public:

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}
Node *minValueNode(Node *node)
{
    Node*current =node;
    while(current->left!=NULL)  //find leftmost leaf
        current=current->left;
    return current;
}

Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;


    x->right = y;   //rotation
    y->left = T2;


    y->height = max(height(y->left), height(y->right)) + 1;                //heights

    x->height = max(height(x->left), height(x->right)) + 1;

    return x;    //new root
}


Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;     //rotation
    x->right = T2;

    x->height = max(height(x->left),  height(x->right)) + 1;  //new heights

    y->height = max(height(y->left),   height(y->right)) + 1;

    return y;   //new root
}
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
    node->height = 1 + max(height(node->left),
                        height(node->right));
    int balance = getBalance(node);
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* deleteNode(Node* root,int key)
{
    if(root==NULL)
        return root;
    if(key<root->key)
        root->left=deleteNode(root->left,key);
    else if (key>root->key)
        root->right=deleteNode(root->right,key);
    else
    {
        if((root->left==NULL)||(root->right==NULL))   //one child or no child
        {
            Node *temp=root->left?root->left:root->right;

            if(temp==NULL)   //no child
            {
                temp=root;
                root=NULL;
            }
            else
                *root =*temp;

            delete temp;

        }

        else
        {
            Node* temp= minValueNode(root->right);
            root->key=temp->key;
            root->right=deleteNode(root->right,temp->key);
        }

    }
    if(root==NULL)
        return root;

    root->height=1+max(height(root->left),height(root->right)); //update height
}

void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}



void inorderdisplay(Node *root)
{
	if(root)
	{
		inorderdisplay(root->left);
		cout<<root->key<<" ";
		inorderdisplay(root->right);
	}

}

void postorderdisplay(Node *root)
{
	if(root)
	{
		postorderdisplay(root->left);
		postorderdisplay(root->right);
		cout<<root->key<<" ";
	}
}





};
int main()
{
    Node *root = NULL;

     AVL a;
     char ch='y';
      int o;



    while(ch=='y'||ch=='Y')
    {
         int x;
    cout<<"------------ ENTER THE CHOICE ------------------------ "<<endl;
    cout<<" 1. INSERT  \n 2. PRE-ORDER DISPLAY \n3.INORDER DISPLAY \n 4.POSTORDER DISPLAY \n 5.DELETE ELEMENT \n "<<endl;
    cin>>o;
    if(o==1)
    {
         int n;

        cout<<" ENTER THE NUMBER OF ELEMENT "<<endl;
        cin>>n;

        for(int i = 0; i<n; i++){
                    cout<<"ENTER ELEMENT : ";
                    cin>>x;
                     root = a.insert(root, x);

    }
    }

    else if(o==2)
    {
        cout<<" PRE-ORDER DISPLAY "<<endl;
         a.preOrder(root);

    }
     else if(o==3)
    {
        cout<<" IN-ORDER DISPLAY "<<endl;
         a.inorderdisplay(root);

    }
     else if(o==4)
    {
        cout<<" POST-ORDER DISPLAY "<<endl;
         a.postorderdisplay(root);

    }
    else
    {

        cout<<" ENTER THE ELEMENT YOU WANT TO DELETE "<<endl;
        cin>>x;
         root=a.deleteNode(root,x);
    }

    cout<<" ENTER Y/y TO CONTINUE THE PROGRAM "<<endl;
    cin>>ch;

    }
}

