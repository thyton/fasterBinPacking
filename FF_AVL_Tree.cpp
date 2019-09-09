#include "FF_AVL_Tree.h"
using namespace std;
FF_AVL_Tree::FF_AVL_Tree()
{
  mRoot = nullptr;
  bin_cnt = 0;
}

FF_AVL_Tree::~FF_AVL_Tree()
{
  clear(mRoot);
}

int FF_AVL_Tree::balance(const FF_AVL_Node *root)
{
  return (root == nullptr ? 0 : height(root->mLeft) - height(root->mRight));
}
  
int FF_AVL_Tree::height(const FF_AVL_Node *root)
{
    return (root == nullptr ? -1 : root->mHeight);
}

double FF_AVL_Tree::get_brc(const FF_AVL_Node* root)
{
    return (root == nullptr? 0.0 : root->mValue.get_BRC());
}

double FF_AVL_Tree::get_rc(const FF_AVL_Node* root)
{
    return (root == nullptr? 0.0 : root->mValue.get_RC());
}

void FF_AVL_Tree::insert(const FF_Bin& value)
{
  mRoot = insert(mRoot, value);
  ++bin_cnt;
  mRoot->mHeight = std::max(height(mRoot->mRight), height(mRoot->mRight)) + 1;
}

FF_AVL_Node* FF_AVL_Tree::right_rotate(FF_AVL_Node *root) 
{
    FF_AVL_Node *pivot{root->mLeft};
    FF_AVL_Node *r_child{pivot->mRight};
    pivot->mRight = root;
    root->mLeft = r_child;
    
    // update brc of bin at old root
    update_bin(root);
    // update brc of bin at new root
    update_bin(pivot);
    
    root->mHeight = std::max(height(root->mLeft), height(root->mRight)) + 1;
    pivot->mHeight = std::max(height(pivot->mLeft), height(pivot->mRight)) + 1;
    return pivot;
}

FF_AVL_Node* FF_AVL_Tree::left_rotate(FF_AVL_Node *root) 
{
    FF_AVL_Node *pivot{root->mRight};
    FF_AVL_Node *orphan{pivot->mLeft};
    pivot->mLeft = root;
    root->mRight = orphan;
    
    // update brc of bin at old root
    update_bin(root);
    // update brc of bin at new root
    update_bin(pivot);

    root->mHeight = std::max(height(root->mLeft), height(root->mRight)) + 1;
    pivot->mHeight = std::max(height(pivot->mLeft), height(pivot->mRight)) + 1;
    return pivot;
}

FF_AVL_Node* FF_AVL_Tree::insert(FF_AVL_Node *root, const FF_Bin& value)
{
  if (!root)  
    return(new FF_AVL_Node(value));  
   
  root->mRight = insert(root->mRight, value);
  root->mHeight = 1 + std::max(height(root->mLeft), height(root->mRight));  
  
  if (balance(root) > 1) // left subtree is higher than right subtree
  {
      if (balance(root->mLeft) == 1) {
        return right_rotate(root);
      } else if (balance(root->mLeft) == -1) {
        root->mLeft = left_rotate(root->mLeft);
        return right_rotate(root);
      }
  } 
  else if (balance(root) < -1) 
  {
      if (balance(root->mRight) == -1) 
      {
        return left_rotate(root);
      } else if (balance(root->mRight) == 1) {
        root->mRight = right_rotate(root->mRight);
        return left_rotate(root);
      }
  }
  update_bin(root);
  return root;
}

void FF_AVL_Tree::update_bin(FF_AVL_Node* root)
{
  if(get_brc(root->mLeft) < get_brc(root->mRight))
  {
     root->mValue.set_BRC( std::max( get_brc(root->mRight), get_rc(root) ) ); 
  } else
  {
     root->mValue.set_BRC( std::max( get_brc(root->mLeft), get_rc(root) ) );
  }
}

int FF_AVL_Tree::insert_item(FF_AVL_Node* root, double weight)
{
  int index;
  if(get_brc(root->mLeft) >= weight)
  {
    index = insert_item(root->mLeft,weight);
    update_bin(root);
    return index;
  } else if(get_rc(root) >= weight)
  {
    root->mValue.set_RC(get_rc(root) - weight);
    update_bin(root);
    return root->mValue.get_index();
  } else
  {
    index = insert_item(root->mRight,weight);
    update_bin(root);
    return index;
  }
}

int FF_AVL_Tree::insert_item(double weight)
{
  return insert_item(mRoot, weight);
}

bool FF_AVL_Tree::is_fit_in_current_bins(double rc) const
{
    return get_brc(mRoot) >= rc;
}

void FF_AVL_Tree::clear(FF_AVL_Node *root)
{
    if (!root)
      return;
    if (root->mLeft)
      clear(root->mLeft);
    if (root->mRight)
      clear(root->mRight);
    delete root;
    root = nullptr;
}

void FF_AVL_Tree::get_inorder(vector<double>& free_space, FF_AVL_Node* root)
{
    if(root == nullptr)
        return;
    get_inorder(free_space, root->mLeft);
    free_space.push_back(get_rc(root));
    get_inorder(free_space, root->mRight);
}

void FF_AVL_Tree::get_free_space(vector<double>& free_space) 
{ 
    free_space = {};
    get_inorder(free_space, mRoot);
} 

int FF_AVL_Tree::get_bin_cnt() const
{
  return bin_cnt; 
}
