#include <unordered_map>
#include <vector>
#include <stdexcept>

#include <functional>


#define REALLOC_SIZE_FACTOR 2


namespace josh
{
    template<class T>
    class Tree_node
    {
        T object;
        unsigned long rank;
        Tree_node<T> * parent;

        template<class, class>friend class Disjoint_set;

    public:
        Tree_node() : Tree_node(T()) {}
        Tree_node(T & obj) : object(obj), rank(0), parent(this) {}

        T get_object() { return object; }
        unsigned long get_rank() { return rank; }
        Tree_node<T> * get_parent() { return parent; }

        void set_rank(unsigned long rank) { this->rank = rank; }
        void set_parent(Tree_node<T> * parent) { this->parent = parent; }
        void compress();

    };


    template<class T, class Hash = std::hash<T> >
    class Disjoint_set
    {
        std::vector<Tree_node<T> *> tree_nodes;
        typedef std::unordered_map<T, Tree_node<T> *, Hash> Tree_map;
        Tree_map object_map;

        typedef Tree_node<T> node;

    public:
        Disjoint_set() {}
        void add(T object); 
        node * find_set(T object);
        void union_sets(node * set1, node * set2);
        bool is_disjoint(node * set1, node * set2);
        void link(T object1, T object2);
        

        ~Disjoint_set();


    };

    class CannotFindObject : public std::runtime_error
    {
        public:
            CannotFindObject()
                : std::runtime_error("Cannot find object in disjoint set") {};
    };


    class SetsNotDisjoint : public std::runtime_error
    {
        public:
            SetsNotDisjoint()
                : std::runtime_error("Cannot union sets that are not disjoint") {};
    };


}

#include "disjoint_set.cpp"
