#include <utility>
#include <list>

struct EmptyHeap: public std::exception {};

template<class T>
class BinomialHeap {
    private:
        /* inner class: binomial tree */
        struct BinomialTree {
            int _size;
            T element;
            std::list<BinomialTree*> children;

            BinomialTree(T _ele): _size(1), element(_ele) {
                children.clear();
            }

            /* return the size of BinomialTree
             * #note that nullptr->size() == 0
             * (nullptr is a null pointer (like NULL in C))
             */
            int size() {
                return (this!=nullptr)?this->_size:0;
            }
        };
        /* some definition for convinience */ 
        typedef BinomialTree BT;
        typedef BinomialHeap<T> BH;
        typedef std::pair<BT*, BT*> CarrySum;
        typedef std::pair<T, BH> MaxRemainder;

        CarrySum half_adder(BT *a, BT *b) {
            CarrySum Result;
            if (a != nullptr && b != nullptr)
            {
                Result.second = nullptr;
                if (a->element > b->element)
                {
                    a->children.push_back(b);
                    Result.first = a;
                }
                else
                {
                    b->children.push_back(a);
                    Result.first = b;
                }
                Result.first->_size *= 2;
            }
            else
            {
                Result.first = nullptr;
                Result.second = (a != nullptr)? a:b;
            }
            return Result;
        }
        /* Merge three binomial trees which have the same sizes
         *
         * INPUT:   a: operand a, b: operand b, c: carry in
         *          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
         *          second: sum (nullptr or a pointer of BinomialTree with size 2^n)
         *
         * (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
         */
        CarrySum merge_tree(BT *a, BT *b, BT *c) {
            CarrySum Result;
            CarrySum tmp = half_adder(a, b);

            if (tmp.first != nullptr)
            {
                Result.first = tmp.first;
                Result.second = c;
            }
            else
            {
                Result = half_adder(tmp.second, c);
            }
            return Result;
        };

        /* Pop the maximum element of a binomial tree and make other elements a binomial heap.
         *
         * INPUT:   a: a pointer of BinomialTree
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: the maximum element
         *          second: a binomial heap consists of other elements
         */
        MaxRemainder pop_max(BT *a) {
            MaxRemainder Result;
            Result.first = a->element;

            BH Remain;
            Remain.size = a->_size - 1;

            int index = 0;
            for (typename std::list<BinomialTree*>::iterator it = a->children.begin();
                 it != a->children.end();
                 ++it) 
                Remain.trees[index++] = *it;

            Result.second = Remain;

            return Result;
        }

        BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

    public:
        int size;
        BinomialHeap(): size(0) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
        }
        BinomialHeap(T element): size(1) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
            trees[0] = new BT(element);
        }

        /* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
         *
         * INPUT:   b: a pointer of BinomialHeap
         */
        void merge(BH &b) {
            BT* Carry = nullptr;
            this->size += b.size;
            for (int i = 0; i < 32; i++)
            {
                CarrySum Out = merge_tree(this->trees[i], b.trees[i], Carry);

                Carry = Out.first;
                this->trees[i] = Out.second;

                b.trees[i] = nullptr;

            }
            b.size = 0;
            return;
        }

        void insert(const T &element) {
            BH tmp = BH(element);
            merge(tmp);
        }

        const T& top() {
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;
                return trees[max_tree]->element;
        }

        T pop() {
            if(size==0) throw EmptyHeap();
            else {
                //find the tree contains maximum element
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;

                MaxRemainder m_r = pop_max(trees[max_tree]);
                T &max_element = m_r.first;
                BH &remainder = m_r.second;

                size -= trees[max_tree]->_size;
                delete trees[max_tree];
                trees[max_tree] = nullptr;

                merge(remainder);
                return max_element;
            }
        }
};
