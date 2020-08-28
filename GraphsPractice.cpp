#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <list>

using std::string;
using std::unordered_set;

struct node {
    int id;
    unordered_set<int> nodes;

    node(int id, const std::list<int>& nodes) {
        this->id = id;
        this->nodes.insert(std::begin(nodes), std::end(nodes));
    }

    friend std::ostream& operator<< (std::ostream& os, const node& n) {
        os << n.id << ": ";
        for (int el : n.nodes) {
            os << el << " ";
        }
        return os;
    }

    size_t operator()(const node& pointToHash) const noexcept {
        size_t hash = 10 * pointToHash.id;
        return hash;
    };
};


namespace std {
    template<> struct hash<node>
    {
        std::size_t operator()(const node& p) const noexcept
        {
            return p(p);
        }
    };
}


unordered_set<int> getNodes(const node &arr) {
    unordered_set<int>*passed = new unordered_set<int>();

    for (const int& n : arr.nodes) {
        passed->insert(n);
    }
    return *passed;
}

int main()
{
    int graph[10][10] = { 0, 1, 0, 0, 0, 0, 1, 0, 1, 0,
                        1, 0, 0, 0, 1, 0, 1, 0, 0, 1,
                        0, 1, 0, 0, 0, 0, 1, 0, 0, 1,
                        0, 0, 0, 0, 1, 1, 0, 0, 1, 0,
                        0, 1, 0, 1, 0, 1, 0, 0, 0, 1,
                        0, 0, 0, 1, 1, 0, 1, 0, 1, 0,
                        1, 1, 1, 0, 0, 0, 0, 1, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
                        1, 0, 0, 1, 0, 0, 0, 1, 0, 0,
                        0, 0, 0, 0, 1, 0, 0, 1, 0, 0 };
    std::vector<node> nodes;
    std::list<int> arr;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (graph[i][j] == 1) {
                arr.push_back(j);
            }
        }
        node* node1 = new node(i, arr);
        nodes.push_back(*node1);
        arr.clear();
    }


    std::vector<node>::iterator it = std::find_if(nodes.begin(), nodes.end(), [](const node& val) {
        if (val.id == 3)
            return true;
        return false;
        });

    unordered_set<int> inQueue = getNodes(*it);
    unordered_set<int> *nextQueue = new unordered_set<int>;
    unordered_set<int> *passed = new unordered_set<int>;
    while (!inQueue.empty())
    {
        int i = *inQueue.find(*inQueue.begin());
            if (!passed->count(i))
            {
                passed->insert(i);

                for (int k : nodes.at(i).nodes)
                {
                    inQueue.insert(k);
                }
            }
            unordered_set<int>::iterator it1 = inQueue.find(i);
            inQueue.erase(it1);
            //int a = 12;
    }

    for (int i : *passed)
    {
        std::cout << i << std::endl;
    }
    system("pause");
}
