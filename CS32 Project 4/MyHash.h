// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

#include <string>
#include <iostream>
using namespace std;

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5)
    {
        m_buckets = 100;
        m_hash = new LinkedList[m_buckets];
        
        if (maxLoadFactor <= 0)
            m_maxLoad = 0.5;
        else if (maxLoadFactor > 2)
            m_maxLoad = 2;
        else
            m_maxLoad = maxLoadFactor;
    }
    
    ~MyHash()
    {
        delete [] m_hash;
    }
    
    void reset()
    {
        //delete [] m_hash;
        LinkedList* m_hash2 = new LinkedList[100];
        m_hash = m_hash2;
        m_buckets = 100;
        m_nums = 0;
    }
    
    unsigned int getBucketNumber(const KeyType& key) const
    {
        unsigned int hash(const KeyType& k); // prototype
        unsigned int h = hash(key);
        return h;
    }
    
    
    void associate(const KeyType& key, const ValueType& value)
    {
        int buckNum = getBucketNumber(key)%m_buckets;
        if (!m_hash[buckNum].findItem(key))
        {
            m_hash[buckNum].addToRear(key, value);
            m_nums++;
        }
        else
        {
            m_hash[buckNum].deleteItem(key);
            m_hash[buckNum].addToRear(key, value);
        }
        
        if (getLoadFactor() > m_maxLoad)
        {
            LinkedList* temp = new LinkedList[m_buckets*2];
            for (int i = 0; i < m_buckets; i++)
            {
                for (int j = 0; j < m_hash[i].getCount(); j++)
                {
                    KeyType key1;
                    ValueType val1;
                    m_hash[i].traverseTo(j, key1, val1);
                    
                    int buckNum2 = getBucketNumber(key1)%(m_buckets*2);
                    temp[buckNum2].addToRear(key1, val1);
                }
            }
            m_hash = temp;
        }
    }
    
    int getNumItems() const
    {
        return m_nums;
    }
    double getLoadFactor() const
    {
        double load = (double)m_nums/m_buckets;
        return load;
    }
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const
    {
        int buckNum = getBucketNumber(key)%m_buckets;
        ValueType* val;
        if (m_hash[buckNum].getVal(key, *val))
            return val;
        else
            return nullptr;
    }
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
    
private:
    class LinkedList
    {
    public:
        LinkedList()
        {
            head = nullptr;
            count = 0;
        }
        
        void addToRear(KeyType k, ValueType v)
        {
            if (head == nullptr)
            {
                Node* p = new Node;
                p->key = k;
                p->val = v;
                p->next = head;
                head = p;
            }
            else
            {
                Node* p = head;
                while (p->next != nullptr)
                    p = p->next;
                Node* n = new Node;
                n->key = k;
                n->val = v;
                p->next = n;
                n->next = nullptr;
            }
            count++;
        }
        
        void deleteItem(KeyType k)
        {
            if (head == nullptr)
                return;
            if (head->key == k)
            {
                Node* kill = head;
                head = kill->next;
                delete kill;
                count--;
                return;
            }
            Node* p = head;
            while (head != nullptr)
            {
                if (p->next != nullptr && p->next->key == k)
                    break;
                p = p->next;
            }
            if (p != nullptr)
            {
                Node* kill = p->next;
                p->next = kill->next;
                delete kill;
                count--;
            }
        }
        
        bool findItem(KeyType k) const
        {
            Node* p = head;
            while (p != nullptr)
            {
                if (p->key == k)
                    return true;
                p = p->next;
            }
            return false;
        }
        
        bool getVal(KeyType k, ValueType &v) const
        {
            Node* p = head;
            while (p != nullptr)
            {
                if (p->key == k)
                {
                    v = p->val;
                    return true;
                }
                p = p->next;
            }
            return false;
        }
        
        bool traverseTo(int n, KeyType &k, ValueType &v)
        {
            int x = 0;
            Node* p = head;
            while (p != nullptr)
            {
                if (x == n)
                {
                    k = p->key;
                    v = p->val;
                    return true;
                }
                p = p->next;
                x++;
            }
            return false;
        }
        
        int getCount()
        {
            return count;
        }
        
        ~LinkedList()
        {
            Node *p = head;
            while (p != nullptr)
            {
                Node *n = p->next;
                delete p;
                p = n;
            }
        }
        
    private:
        struct Node
        {
            KeyType key;
            ValueType val;
            Node* next;
        };
        Node* head;
        int count;
    };
    LinkedList* m_hash;
    int m_nums;
    int m_buckets;
    double m_maxLoad;
};

