#include <iostream>
#include <iomanip>

class FF_Bin // adapted from the slide lecture
{
    private:
        int index;
        double rc;  // remaining capacity
        double brc; // best remaining capacity
    public:
        FF_Bin() = default;
        FF_Bin(const FF_Bin& other)
        {
            index = other.index;
            rc = other.rc;
            brc = other.brc;  
        }
        
        FF_Bin(int index, double rc, double brc)
        {
            this->index = index;
            this->rc = rc;
            this->brc = brc;
        }
        
        double get_RC() const
        {
            return rc;
        }
        
        double get_BRC() const
        {
            return brc;
        }
        
        int get_index() const
        {
            return index;   
        }
        
        bool operator<(const FF_Bin& other) const
        {
            return (index < other.index) ;
        }
        
        bool operator>(const FF_Bin &other) const
        {
            return (index > other.index) ;
        }
        
        void set_RC(double new_rc)
        {
            this->rc = new_rc;
        }
        
        void set_BRC(double new_brc)
        {
            this->brc = new_brc;
        }
        
        void  print() {
            std::cout << std::fixed << index << " " << rc << " " << brc;
        }
        
        ~FF_Bin(){}
};
