// SiDA2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
/* C++ program to construct tree using inorder and
   postorder traversals */

#define COUNT 10
using namespace std;

/* A binary tree node has data, pointer to left
   child and a pointer to right child */
struct Node {
    char data;
    Node* left, * right;
};

// Utility function to create a new node 
Node* newNode(int data);

/* Prototypes for utility functions */
int search(char arr[], int strt, int end, int value);

/* Recursive function to construct binary of size n
   from  Inorder traversal in[] and Postorder traversal
   post[].  Initial values of inStrt and inEnd should
   be 0 and n -1.  The function doesn't do any error
   checking for cases where inorder and postorder
   do not form a tree */
Node* buildUtil(char in[], char post[], int inStrt,
    int inEnd, int* pIndex)
{
    // Base case 
    if (inStrt > inEnd)
        return NULL;

    /* Pick current node from Postorder traversal using
       postIndex and decrement postIndex */
    Node* node = newNode(post[*pIndex]);
    (*pIndex)--;

    /* If this node has no children then return */
    if (inStrt == inEnd)
        return node;

    /* Else find the index of this node in Inorder
       traversal */
    int iIndex = search(in, inStrt, inEnd, node->data);

    /* Using index in Inorder traversal, construct left and
       right subtress */
    node->right = buildUtil(in, post, iIndex + 1, inEnd, pIndex);
    node->left = buildUtil(in, post, inStrt, iIndex - 1, pIndex);

    return node;
}

// This function mainly initializes index of root 
// and calls buildUtil() 
Node* buildTree(char in[], char post[], int n)
{
    int pIndex = n - 1;
    return buildUtil(in, post, 0, n - 1, &pIndex);
}

/* Function to find index of value in arr[start...end]
   The function assumes that value is postsent in in[] */
int search(char arr[], int strt, int end, int value)
{
    int i;
    for (i = strt; i <= end; i++) {
        if (arr[i] == value)
            break;
    }
    return i;
}

/* Helper function that allocates a new node */
Node* newNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return (node);
}

/* This funtcion is here just to test  */
void postOrder(Node* node)
{
    if (node == NULL)
        return;
    
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << ' ';
}
void preOrder(Node* node)
{
    if (node == NULL)
        return;
    cout << node->data << ' ';
    preOrder(node->left);
    preOrder(node->right);
    
}
void inOrder(Node* node)
{
    if (node == NULL)
        return;
    inOrder(node->left);
    cout << node->data << ' ';
    inOrder(node->right);

}
void print2DUtil(Node* root, int space) {
    // Base case  
    if (root == NULL)
        return;

    // Increase distance between levels  
    space += COUNT;

    // Process right child first  
    print2DUtil(root->right, space);

    // Print current node after space  
    // count  
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    // Process left child  
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()  
void print2D(Node* root)
{
    // Pass initial space count as 0  
    print2DUtil(root, 0);
}

// Driver code 
int main()
{
    char in[] = { 'B', 'X', 'Z', 'Y', 'A', 'V','F','M','Q','N' };
    char post[] = { 'B', 'Z', 'A', 'Y', 'X', 'M','N','Q','F','V' };
    int n = sizeof(in) / sizeof(in[0]);

    Node* root = buildTree(in, post, n);

    //cout << "Preorder of the constructed tree : \n";
    //preOrder(root);
    print2D(root);
    cout << " \n";
    cout << " \n";
    cout << " \n";
    cout << " \n";
    cout << " \n";
    cout << "pre:\n";
    preOrder(root);
    cout << "\nin: \n";
    inOrder(root);
    cout << "\npost: \n";
    postOrder(root);
    return 0;
}