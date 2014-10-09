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


    template<class T, class Hash>
    void Disjoint_set<T,Hash>::add(T object)
    {
        Tree_node<T> * new_node = new Tree_node<T>(object);
        tree_nodes.push_back(new_node);
        object_map[object] = new_node;
    }

    template<class T>
    void Tree_node<T>::compress()
    {
        Tree_node<T> * current_node = this;

        while(current_node != current_node->get_parent())
        {
            current_node = current_node->get_parent();
        }

        this->set_parent(current_node);
    }

    template<class T, class Hash>
    Tree_node<T> * Disjoint_set<T, Hash>::find_set(T object)
    {
        Tree_node<T> * set;

        typename Tree_map::const_iterator found = object_map.find(object);
        if(found == object_map.end())
            throw CannotFindObject();
        else
        {
            set = found->second;

            /* before we return the found set, we shall do the path compression
                heuristic */
            set->compress();

            return set;
        }
    }

    template<class T, class Hash>
    void Disjoint_set<T, Hash>::union_sets(Tree_node<T> * set1, Tree_node<T> * set2)
    {

        /* first check they are disjoint */
        if(!is_disjoint(set1, set2))
            throw SetsNotDisjoint();

        Tree_node<T> * set1_head = set1->get_parent();
        Tree_node<T> * set2_head = set2->get_parent();

        if(set1_head->get_rank() > set2_head->get_rank())
        {

            set2_head->set_parent(set1_head);
        }
        else
        {
            set1_head->set_parent(set2_head);
            if(set1_head->get_rank() == set2_head->get_rank())
                set2_head->set_rank(set2_head->get_rank() + 1);
        }


    }

    template<class T, class Hash>
    bool Disjoint_set<T, Hash>::is_disjoint(Tree_node<T> * set1, Tree_node<T> * set2)
    {
        set1->compress();
        set2->compress();
        
        if(set1->get_parent() == set2->get_parent())
            return false;
        else
                    
            return true;
        
    }

    template<class T, class Hash>
    void Disjoint_set<T, Hash>::link(T object1, T object2)
    {
        this->union_sets(this->find_set(object1), this->find_set(object2));
    }

    template<class T, class Hash>
    Disjoint_set<T, Hash>::~Disjoint_set()
    {
        for(auto node : tree_nodes)
            delete node;
    }
}
