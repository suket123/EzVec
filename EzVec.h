#ifndef EZVEC_H
#define EZVEC_H

#include <stdlib.h>
#include <iostream>
#include <vector>

#define INIT_VEC_SIZE 2

using namespace std;

template <typename T>
class EzVec
{

private:
	vector<T> myVector;
    /* reason why I chose index types as int rather than unsigned is because
       if all values are inserted using push_front, when the size of the vector
       is full, the value of frontIndex will be -1 */
	int frontIndex;
	int backIndex;

    // Helper Function
    unsigned int nextPowerOf2(unsigned int n)  
    {
        unsigned count = 0;  
        // First n in the below condition  
        // is for the case where n is 0  
        if (n && !(n & (n - 1)))  
            return n;  
          
        while( n != 0)  
        {  
            n >>= 1;  
            count += 1;  
        }
        return 1 << count;  
    }

    bool canSetSize(size_t n)
    {
        if (n > this->myVector.max_size())
        {
            // Not possible to increase the size, hence return without increasing size of the vector
            return false;
        }
        return true;
    }

    void setReplacementVector(vector<T>& replacementVector)
    {
        int size = this->size();
        for (int i = 0; i < size; i++)
        {
            int index = (this->frontIndex + 1 + i) % this->myVector.size();
            replacementVector[i] = this->myVector[index];
        }
        this->backIndex = size;
        this->frontIndex = replacementVector.size() - 1;
    }

    void print_original_vec()
    {
        for(int i = 0; i < myVector.size(); i++)
        {
            cout << myVector[i] << " ";
        }
        cout << endl;
    }

public:
    // Default constructor
	EzVec<T>()
	{
		this->backIndex = 0;
		this->myVector.resize(INIT_VEC_SIZE);
		this->frontIndex = this->myVector.size() - 1;
	}

    // Get by reference, useful for move constructor
    vector<T>& getVectorByRef()
    {
        return this->myVector;
    }

    int getFrontIndex()
    {
        return this->frontIndex;
    }

    int getBackIndex()
    {
        return this->backIndex;
    }

    void setVector(std::vector<T>& tempVector)
    {
        this->myVector = tempVector;
    }

    void setFrontIndex(int tempFrontIndex)
    {
        this->frontIndex = tempFrontIndex;
    }

    void setBackIndex(int tempBackIndex)
    {
        this->backIndex = tempBackIndex;
    }

    // Constructor which creates vector with size n, val is default
	EzVec<T>(size_t n)
	{
        unsigned size = nextPowerOf2(n);
		this->myVector.resize(size);
        this->backIndex = n;
		this->frontIndex = this->myVector.size() - 1;
	}

    // Constructor which allows reading from std::vector
    EzVec<T>(const std::vector<T>& vec)
    {
        int newSize = nextPowerOf2(vec.size());
        this->myVector.resize(newSize);
        for (int i = 0; i < vec.size(); i++)
        {
            this->myVector[i] = vec[i];
        }
        this->backIndex = vec.size();
        this->frontIndex = this->myVector.size() - 1;
    }

    /* A type of a constructor which sets the vector size to n, with the values val
       similar to std::vector::assign */
    void assign (size_t n, T& val)
    {
        unsigned size = nextPowerOf2(n);
        this->myVector.resize(size);
        this->backIndex = n;
        this->frontIndex = this->myVector.size() - 1;
        for (int i = 0; i < n; i++)
        {
            this->myVector[i] = val;
        }
    }

    // Constructor to create vector with given size and value
    EzVec<T>(size_t n, T val)
    {
        assign(n, val);
    }

    // Copy Constructor
    EzVec(const EzVec & obj)
    {
        this->myVector = obj.getVectorByRef();
        this->frontIndex = obj.getFrontIndex();
        this->backIndex = obj.getBackIndex();
    }

    // Move Constructor
    EzVec(EzVec&& obj)
    {
        this->myVector = std::move(obj.getVectorByRef());
        this->frontIndex = obj.getFrontIndex();
        this->backIndex = obj.getBackIndex();
    }

    size_t size()
    {
        size_t unused = this->frontIndex - this->backIndex + 1;
        return this->myVector.size() - unused;
    }

    size_t size() const
    {
        size_t unused = this->frontIndex - this->backIndex + 1;
        return this->myVector.size() - unused;
    }

    T at(int index) const
    {
        if (index >= this->size())
        {
            cout << "Error! Index: " << index << " out of bounds" << endl;
        }

        size_t vecIndex = (this->frontIndex + 1 + index) % this->myVector.size();
        return this->myVector[vecIndex];
    }

    // Index operator functions below
    T operator[](int index) const
    {
        return at(index);
    }

    T at(int index) 
    {
        return static_cast<const EzVec &>(*this).at(index);
    }

    // Index operator functions below
    T operator[](int index)
    {
        return static_cast<const EzVec &>(*this)[index];
    }

    // Copy Assignment
    EzVec& operator=(const EzVec& obj)
    {
        this->myVector = obj.getVectorByRef();
        this->frontIndex = obj.getFrontIndex();
        this->backIndex = obj.getBackIndex();
        return *this;
    }

    // Move Assignment
    EzVec& operator=(EzVec&& obj)
    {
        this->myVector = std::move(obj.getVectorByRef());
        this->frontIndex = obj.getFrontIndex();
        this->backIndex = obj.getBackIndex();
        return *this;
    }

    /* When back() is called on a const object
       - returns const reference to the last value in the vector */
    const T& back() const
    {
        if (this->size() > 0)
        {
            int index = (this->backIndex - 1) % this->myVector.size();
            return this->myVector[index];
        }

        // there are 0 elements in the vector
        return this->myVector[0];
    }

    // Returns reference to the last value in the vector
    T& back()
    {
        return const_cast<T&>(static_cast<const EzVec &>(*this).back());
    }

    /* When front() is called on a const object
       - returns const reference to the first value in the vector */
    const T& front() const
    {
        if (this->size() > 0)
        {
            int index = (this->frontIndex + 1) % this->myVector.size();
            return this->myVector[index];
        }
        
        // there are 0 elements in the vector
        return this->myVector[0];
    }

    T& front()
    {
        return const_cast<T&>(static_cast<const EzVec &>(*this).front());
    }

    size_t capacity() const noexcept
    {
        return this->myVector.size();
    }

    size_t max_size() const noexcept
    {
        return this->myVector.max_size();
    }

    void clear() noexcept
    {
        this->myVector.clear();
        this->myVector.resize(INIT_VEC_SIZE);
        this->backIndex = 0;
        this->frontIndex = this->myVector.size() - 1;
    }

    bool empty() const noexcept
    {
        if ((this->frontIndex + 1) % this->myVector.size() == this->backIndex)
            return true;

        return false;
    }

	void push_back(T newVal)
	{
        if (this->frontIndex != this->backIndex)
        {
            this->myVector[this->backIndex++] = newVal;   
        }
        else
        {
            if (!canSetSize(this->myVector.size() * 2))
                return;

            // increase the size of the vector
            vector<T> replacementVector(this->myVector.size() * 2);
            setReplacementVector(replacementVector);
            replacementVector[this->backIndex++] = newVal;
            this->myVector = replacementVector;
        }
	}

	void push_front(T newVal)
	{
        if (this->frontIndex != this->backIndex)
        {
            this->myVector[this->frontIndex--] = newVal;   
        }
        else
        {
            if (!canSetSize(this->myVector.size() * 2))
                return;

            // increase the size of the vector
            vector<T> replacementVector(this->myVector.size() * 2);
            setReplacementVector(replacementVector);
            replacementVector[this->frontIndex--] = newVal;
            this->myVector = replacementVector;
        }
	}

    void pop_back()
    {
        if (empty())
            return;

        this->backIndex = (this->backIndex - 1) % this->myVector.size();
    }

    void pop_front()
    {
        if (empty())
            return;

        this->frontIndex = (this->frontIndex + 1) % this->myVector.size();
    }

    void reserve(size_t n)
    {
        // cannot reserver for a smaller than current size
        if (n < this->myVector.size())
            return;

        int newSize = nextPowerOf2(n);
        if (!canSetSize(newSize))
            return;

        // increase the size of the vector
        vector<T> replacementVector(newSize);
        setReplacementVector(replacementVector);
        this->myVector = replacementVector;
    }

    void resize(size_t n, T val = T())
    {
        size_t size = this->size();
        if (n == size)
            return;

        if (n < size)
        {
            int toRemove = size - n;
            this->backIndex = (this->backIndex - toRemove) % this->myVector.size();
        }

        if (n > size)
        {
            if (n > this->myVector.size())
            {
                // use replacement vector
                int newSize = nextPowerOf2(n);
                if (!canSetSize(newSize))
                    return;
                vector<T> replacementVector(newSize);
                setReplacementVector(replacementVector);
                this->myVector = replacementVector;
            }

            size_t newCount = n - size;
            size_t newBackIndex = (this->backIndex + newCount) % this->myVector.size();
            while (this->backIndex != newBackIndex)
            {
                this->myVector[this->backIndex] = val;
                this->backIndex = (this->backIndex + 1) % this->myVector.size();
            }
        }
    }

    void swap(EzVec& obj)
    {
        vector<T> tempVector = this->myVector;
        int tempFrontIndex = this->frontIndex;
        int tempBackIndex = this->backIndex;

        this->myVector = std::move(obj.getVectorByRef());
        this->frontIndex = obj.getFrontIndex();
        this->backIndex = obj.getBackIndex();

        obj.setVector(tempVector);
        obj.setFrontIndex(tempFrontIndex);
        obj.setBackIndex(tempBackIndex);
    }

    void shrink_to_fit()
    {
        int size = this->size();
        int newSize = nextPowerOf2(size);
        // cannot increase size in this function
        if (newSize >= this->myVector.size())
            return;

        vector<T> replacementVector(newSize);
        setReplacementVector(replacementVector);
        this->myVector = replacementVector;
    }

};

#endif
