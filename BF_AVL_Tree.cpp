#include "BF_AVL_Tree.h"
using namespace std;
BF_AVL_Tree::BF_AVL_Tree()
{
  mRoot = nullptr;
  bin_cnt = 0;
}

BF_AVL_Tree::~BF_AVL_Tree()
{
  clear(mRoot);
}

int BF_AVL_Tree::balance(const BF_AVL_Node *root)
{
  return (root == nullptr ? 0 : height(root->mLeft) - height(root->mRight));
}
  
int BF_AVL_Tree::height(const BF_AVL_Node *root)
{
    return (root == nullptr ? -1 : root->mHeight);
}

double BF_AVL_Tree::get_brc(const BF_AVL_Node* root)
{
    return (root == nullptr? 0.0 : root->mValue.get_BRC());
}

double BF_AVL_Tree::get_rc(const BF_AVL_Node* root)
{
    return (root == nullptr? 0.0 : root->mValue.get_RC());
}

pair<int,double> BF_AVL_Tree::search_best_bin(BF_AVL_Node* root, BF_AVL_Node** root_parent, double item)
{
    if(root->mLeft != nullptr && get_brc(root->mLeft) >= item)
    { 
      pair<int, double> index_rc = search_best_bin(root->mLeft, &root->mLeft ,item);
      update_bin(root->mLeft);
      return index_rc;
    } else if( get_rc(root) >= item )
    {
      pair<int, double> index_rc = make_pair<int,double>(root->mValue.get_index(), root->mValue.get_RC());
      *root_parent = remove(root);
      update_bin(*root_parent);
      --bin_cnt;
      return index_rc;
    } else 
    {
      pair<int, double> index_rc = search_best_bin(root->mRight, &root->mRight, item);
      update_bin(root->mRight);
      return index_rc;
    }
}

pair<int,double> BF_AVL_Tree::search_best_bin(double item)
{
     return search_best_bin(mRoot, &mRoot, item);
}

BF_AVL_Node* BF_AVL_Tree::remove(BF_AVL_Node* root)
{
    if (root->mLeft == nullptr && root->mRight == nullptr) {
        delete root;
        root = nullptr;
        return root;
      } else if (root->mLeft == nullptr) {
        BF_AVL_Node *p = root;
        root = root->mRight;
        delete p;
        p = nullptr;
        update_bin(root);
        return root;
      } else if (root->mRight == nullptr) {
        BF_AVL_Node *p = root;
        root = root->mLeft;
        delete p;
        p = nullptr;
        update_bin(root);
        return root;
      } else {
        BF_AVL_Node *min_p{minimum(root->mRight)};
        *root = *min_p;
        root->mRight = remove(min_p);
        update_bin(root->mRight);
        update_bin(root);
        return root;
    }
}

void BF_AVL_Tree::insert(const BF_Bin& value)
{
  mRoot = insert(mRoot, value);
  update_bin(mRoot);
  ++bin_cnt;
}

BF_AVL_Node* BF_AVL_Tree::insert(BF_AVL_Node *root, const BF_Bin& value)
{
  if (root == nullptr) 
  {
    return (new BF_AVL_Node(value));
  }else if (value < root->mValue) {
    root->mLeft = insert(root->mLeft, value);
    update_bin(root->mLeft);
  }else if (value > root->mValue) {
    root->mRight = insert(root->mRight, value);
    update_bin(root->mRight);
  }
  
  // update root height after the insertion
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

BF_AVL_Node* BF_AVL_Tree::right_rotate(BF_AVL_Node *root) 
{
    BF_AVL_Node *pivot{root->mLeft};
    BF_AVL_Node *r_child{pivot->mRight};
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

BF_AVL_Node* BF_AVL_Tree::left_rotate(BF_AVL_Node *root) 
{
    BF_AVL_Node *pivot{root->mRight};
    BF_AVL_Node *orphan{pivot->mLeft};
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

BF_AVL_Node* BF_AVL_Tree::minimum(BF_AVL_Node* root)
{
    if (root->mLeft == nullptr) {
      return root;
    } else 
      return minimum(root->mLeft);
}


void BF_AVL_Tree::update_bin(BF_AVL_Node* root)
{
  if(root != nullptr) 
      root->mValue.set_BRC( std::max( get_brc(root->mRight), get_rc(root))); 
}

bool BF_AVL_Tree::is_fit_in_current_bins(double rc) const
{
    return get_brc(mRoot) >= rc;
}

void BF_AVL_Tree::clear(BF_AVL_Node *root)
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

void BF_AVL_Tree::get_inorder(vector<double>& free_space, BF_AVL_Node* root)
{
    if(root == nullptr)
        return;
    get_inorder(free_space, root->mLeft);
    free_space[root->mValue.get_index()] = get_rc(root);
    get_inorder(free_space, root->mRight);
}

void BF_AVL_Tree::get_free_space(vector<double>& free_space) 
{ 
    get_inorder(free_space, mRoot);
} 

int BF_AVL_Tree::get_bin_cnt() const
{
  return bin_cnt; 
}
