#include "BF_AVL_Node.h"
#include <vector>
#include <utility>      // std::pair

using namespace std;
class BF_AVL_Tree 
{
    public:
        static int height(const BF_AVL_Node* root); 
        static int balance(const BF_AVL_Node* root); 
        static double get_brc(const BF_AVL_Node* root);
        static double get_rc(const BF_AVL_Node* root);
    private:
        BF_AVL_Node *mRoot;
        int bin_cnt;
      
    private:
        BF_AVL_Node* insert(BF_AVL_Node *root, const BF_Bin& value);
        BF_AVL_Node* left_rotate(BF_AVL_Node *root);
        BF_AVL_Node* right_rotate(BF_AVL_Node *root);
        void get_inorder(vector<double>& free_space, BF_AVL_Node* node);
        BF_AVL_Node* remove(BF_AVL_Node* root);
        BF_AVL_Node* minimum(BF_AVL_Node* root);
        pair<int, double> search_best_bin(BF_AVL_Node* root, BF_AVL_Node** root_parent, double item);

    public:
        BF_AVL_Tree();
        ~BF_AVL_Tree();
        pair<int,double> search_best_bin(double item);
        void insert(const BF_Bin& value);
        void update_bin(BF_AVL_Node* root);
        void get_free_space(vector<double>& free_space);
        
        int get_bin_cnt() const; 
        bool is_fit_in_current_bins(double rc) const;

        void clear(BF_AVL_Node *root);
        
        void printBinaryTree() {printBinaryTree(mRoot);}
    private:    
        void printBinaryTree(BF_AVL_Node *root, int space = 4, int height = 10)
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
    root->print();
    // std::cout << root->mValue.get_index() << "\n";
    std::cout << "\n";
    // print left child
    printBinaryTree(root->mLeft, space);
    }
};