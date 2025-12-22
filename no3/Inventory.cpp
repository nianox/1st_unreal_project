#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<compare>

using namespace std;

struct Item
{
    string name;
    int price;

    void PrintInfo() const {
        cout << "[이름: " << name << ", 가격: " << price << "G]" << endl;
    };
    auto operator<=>(const Item& other) const
    {
        if (auto cmp = price <=> other.price; cmp != 0) return cmp;
        return name <=> other.name;
    };
};

template<typename T>
class Inventory
{
private:
    T* pitems;
    int _capacity;
    int size;

public:
    Inventory(const Inventory<T>& other) {
        _capacity = other._capacity;
        size = other.size;
        pitems = new T[_capacity];
        for (int i = 0; i < size; ++i) {
            pitems[i] = other.pitems[i];
        }
        cout << "인벤토리 복사 완료" << endl;
    }

    Inventory(int capacity = 10) : _capacity(capacity)
    {
        size = 0;
        if (capacity < 0)
        {
            _capacity = 1;
        }
        pitems = new T[_capacity];
    }

    ~Inventory()
    {
        delete[] pitems;
        pitems = nullptr;
    }

    void AddItems(const T& item)
    {
        if (size >= _capacity)
        {
            int newCapacity = _capacity * 2;
            T* newPitems = new T[newCapacity];
            for (int i = 0; i < size; i++)
            {
                newPitems[i] = pitems[i];
            }
            delete[] pitems;
            pitems = newPitems;
            _capacity = newCapacity;
        }
        pitems[size++] = item;
    }

    void RemoveLastItems()
    {
        if (size == 0)
        {
            cout << "인벤토리가 비었습니다.\n";
            return;
        }
        size--;
    }

    int Getsize() const
    {
        return size;
    }

    int GetCapacity() const
    {
        return _capacity;
    }

    void PrinAllitems() const
    {
        if (size == 0) {
            cout << "(비어있음)\n";
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                pitems[i].PrintInfo();
            }
        }
    }

    void Resize(int newCapacity)
    {
        T* newPitems = new T[newCapacity];
        for (int i = 0; i < size; i++)
        {
            newPitems[i] = pitems[i]; 
        }
        delete[] pitems;
        pitems = newPitems;
        _capacity = newCapacity;
    }

    void SortItems()
    {
        sort(pitems, pitems + size);
    
    }
};