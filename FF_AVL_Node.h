#include "FF_Bin.h"
class FF_AVL_Node {
  friend class FF_AVL_Tree;

  public:
    FF_Bin mValue;
    
    FF_AVL_Node* mLeft;
    FF_AVL_Node* mRight;
  
    int mHeight;
    
  public:
    FF_AVL_Node()
    {
      mLeft = nullptr;
      mRight = nullptr;
      mHeight = 0;
    }
    ~FF_AVL_Node() = default;
    
    FF_AVL_Node(const FF_Bin& value): mValue(value)
    {
        mLeft = nullptr;
        mRight = nullptr;
        mHeight = 0;
    }
    FF_AVL_Node* insert(FF_AVL_Node* Node);
    
    void print() {
        mValue.print();
        std::cout << mHeight << "\n";
        std::cout << mLeft << " " << mRight << "\n";
    }
};
