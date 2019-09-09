#include "FF_AVL_Node.h"
#include <vector>
using namespace std;

class FF_AVL_Tree 
{
    public:
        static int height(const FF_AVL_Node* root); 
        static int balance(const FF_AVL_Node* root); 
        static double get_brc(const FF_AVL_Node* root);
        static double get_rc(const FF_AVL_Node* root);
    private:
        FF_AVL_Node *mRoot;
        int bin_cnt;
      
    private:
        FF_AVL_Node* insert(FF_AVL_Node *root, const FF_Bin& value);
        int insert_item(FF_AVL_Node *root, double weight);
        FF_AVL_Node* left_rotate(FF_AVL_Node *root);
        FF_AVL_Node* right_rotate(FF_AVL_Node *root);
        void get_inorder(vector<double>& free_space, FF_AVL_Node* node);

    public:
        FF_AVL_Tree();
        ~FF_AVL_Tree();
        void insert(const FF_Bin& value);
        void update_bin(FF_AVL_Node* root);
        void get_free_space(vector<double>& free_space);
        
        int get_bin_cnt() const; 
        int insert_item(double weight);
        bool is_fit_in_current_bins(double rc) const;

        void clear(FF_AVL_Node *root);
        
        void printBinaryTree() {printBinaryTree(mRoot);}
    private:    
        void printBinaryTree(FF_AVL_Node *root, int space = 4, int height = 10)
{
    // Base case
    if (root == nullptr)
        return;

    // increase distance between levels
    space += height;

    // print right child first
    printBinaryTree(root->mRight, space);
    std::cout << "\n";

    // print current node after padding with spaces
    for (int i = height; i < space; i++)
         std::cout << ' ';
    root->mValue.print();
    std::cout << " " << root->mHeight;
    // std::cout << root->mValue.get_index() << "\n";
    std::cout << "\n";
    // print left child
    printBinaryTree(root->mLeft, space);
    }
};