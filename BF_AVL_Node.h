#include "BF_Bin.h"
class BF_AVL_Node {
  friend class BF_AVL_Tree;

  public:
    BF_Bin mValue;
    
    BF_AVL_Node* mLeft;
    BF_AVL_Node* mRight;
  
    int mHeight;
    
  public:
     BF_AVL_Node()
      {
      mLeft = nullptr;
      mRight = nullptr;
      mHeight = 0;
      }
    ~BF_AVL_Node() = default;
    
    // BF_AVL_Node(const BF_AVL_Node& other): mValue(other.mValue)
    // {
    //     mLeft = other.mLeft;
    //     mRight = other.mRight;
    //     mHeight = other.mHeight;
    // }
    
    BF_AVL_Node(const BF_Bin& value): mValue(value)
    {
        mLeft = nullptr;
        mRight = nullptr;
        mHeight = 0;
    }
    
    BF_AVL_Node& operator=(const BF_AVL_Node& other) {
        mValue = other.mValue;
        mLeft = other.mLeft;
        mRight = other.mRight;
        mHeight = other.mHeight;
        return *this;
    }
    
    void print() {
        mValue.print();
        std::cout << " " << mHeight << " ";
    }
};
