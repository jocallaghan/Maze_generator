
#include <iostream>

namespace josh
{
    template<class T, class Hash>
    void Disjoint_set<T,Hash>::add(T object)
    {
        Tree_node<T> * new_node = new Tree_node<T>(object);
        tree_nodes.push_back(new_node);
        /*object_map.insert({object, new_node});*/
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

        /*std::cerr << set1->object << " joined with " << set2->object << "\n";*/

    }

    template<class T, class Hash>
    bool Disjoint_set<T, Hash>::is_disjoint(Tree_node<T> * set1, Tree_node<T> * set2)
    {
        set1->compress();
        set2->compress();

        /*std::cerr << "TESTING DISJOINT:: " <<
            set1->object << "'s parent: " << set1->get_parent()->object <<
                ", " << set2->object << "'s parent: " << set2->get_parent()->object << "\n";
*/
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