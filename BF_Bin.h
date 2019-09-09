#include <iostream>
#include <iomanip>

class BF_Bin // adapted from the slide lecture
{
    private:
        int index;
        double rc;  // remaining capacity
        double brc; // best remaining capacity
    public:
        BF_Bin() = default;
        BF_Bin(const BF_Bin& other)
        {
            index = other.index;
            rc = other.rc;
            brc = other.brc;  
        }
        
        BF_Bin(int index, double rc, double brc)
        {
            this->index = index;
            this->rc = rc;
            this->brc = brc;
        }
        
                
        double get_BRC() const
        {
            return brc;
        }
        
        double get_RC() const
        {
            return rc;
        }
        
        int get_index() const
        {
            return index;   
        }
        
        bool operator<(const BF_Bin& other) const
        {
            return (rc < other.rc || (rc == other.rc && index < other.index));
        }
        
        bool operator>(const BF_Bin &other) const
        {
            return (rc > other.rc || (rc == other.rc && index > other.index));
        }
        
        void set_RC(double new_rc)
        {
            this->rc = new_rc;
        }
        
        void set_BRC(double new_brc)
        {
            this->brc = new_brc;
        }
        void  print() const {
            std::cout << std::fixed <<  rc << " "<<index << " " << brc << " " ;
        }
        
        ~BF_Bin(){}
};
