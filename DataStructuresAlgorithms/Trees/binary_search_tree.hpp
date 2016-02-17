#pragma once

/*
namespace Trees
{
    template <typename T>
    struct BSTNode
    {
        T item;

        BSTNode<T>* leftNode;
        BSTNode<T>* rightNode;
    };

    template <typename T>
    class BinarySearchTree
    {
    public:
        BinarySearchTree();
        ~BinarySearchTree();
        
        BinarySearchTree(const BinarySearchTree& other);
        BinarySearchTree(BinarySearchTree&& other) noexcept;

        BinarySearchTree& operator=(const BinarySearchTree& rhs);
        BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept;

        bool operator==(const BinarySearchTree& rhs) const;
        bool operator!=(const BinarySearchTree& rhs) const;

        friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& bst)
        {
            return (os << bst.toString());
        }

        void insert( const T& item );
        void remove(const T& item );

        void clear();

        BSTNode<T>* findNode(const T& item) const;
        BSTNode<T>* findMin(const T& item) const;

        T preorderTraverse();
        T inorderTraverse();
        T postorderTraverse();

        bool isEmpty() const;
    private:
        BSTNode<T>* createNode(const T item);

        void insert(BSTNode<T>* root, const T& item);
        void remove(BSTNode<T>* root, const T& item);
        void destroySubtree(BSTNode<T>* node);

        BSTNode<T>* findNode(BSTNode<T>* root, const T& item) const;

        std::string toString() const;

        BSTNode<T>* root;
        std::size_t nodes;
    };

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree() :
        root(nullptr),
        nodes(0)
    {
    }

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree()
    {
        clear();
    }

    template <typename T>
    void BinarySearchTree<T>::insert( const T& item )
    {
        // Insert the first root
        if (this->root == nullptr)
        {
            this->root = createNode(item);
        }
        else
        {
            insert(this->root, item);
        }

        ++(this->nodes);
    }

    template < typename T >
    void BinarySearchTree< T >::remove(const T& item)
    {
        BSTNode<T>* foundNode = findNode(item);

        if (foundNode != nullptr)
        {
            remove(foundNode, item);

            --(this->nodes);
        }
    }

    template < typename T >
    void BinarySearchTree< T >::clear()
    {
        if (!isEmpty())
        {
            destroySubtree(this->root);
        }
    }

    template <typename T>
    BSTNode<T>* BinarySearchTree< T >::findNode(const T& item) const
    {
        return nullptr;
    }

    template <typename T>
    BSTNode<T>* BinarySearchTree<T>::createNode(const T item)
    {
        BSTNode<T>* node = new BSTNode<T>();

        node->item = item;
        node->leftNode = nullptr;
        node->rightNode = nullptr;

        return node;
    }

    template <typename T>
    void BinarySearchTree<T>::insert(BSTNode<T>* root, const T& item)
    {
        if (root != nullptr)
        {
            // Go left
            if (item < root->item)
            {
                if (root->leftNode == nullptr)
                {
                    root->leftNode = createNode(item);
                }
                else
                {
                    insert(root->leftNode, item);
                }
            }
            // Go right, otherwise ignore (duplicates discarded)
            else if (item > root->item)
            {
                if (root->rightNode == nullptr)
                {
                    root->rightNode = createNode(item);
                }
                else
                {
                    insert(root->rightNode, item);
                }
            }
        }
    }

    template < typename T >
    void BinarySearchTree< T >::remove(BSTNode<T>* root, const T& item)
    {
        if (root != nullptr)
        {
            // Deleting a node with no children: simply remove the node from the tree.
            if (root->leftNode == nullptr && root->rightNode == nullptr)
            {
                delete root;
            }
            // Deleting a node with one child: remove the node and replace it with its child.
            else if (root->leftNode == nullptr && root->rightNode != nullptr)
            {
                // Remove node and replace with right node
                delete root;
                root = root->rightNode;
            }
            else if (root->leftNode != nullptr && root->rightNode == nullptr)
            {
                // Remove node and replace with left node
                delete root;
                root = root->leftNode;
            }
            // Find minimum value in either left or right subtree
            else
            {
                BSTNode<T>* min = findMin(root);

                root->item = min->item;
            }
        }
    }

    template < typename T >
    void BinarySearchTree< T >::destroySubtree(BSTNode<T>* node)
    {
        if (node != nullptr)
        {
            destroySubtree(node->leftNode);
            destroySubtree(node->rightNode);

            delete node;
        }
    }

    template <typename T>
    BSTNode<T>* BinarySearchTree< T >::findNode(BSTNode<T>* root, const T& item) const
    {
        return nullptr;
    }
}
*/