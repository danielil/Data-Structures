#pragma once

namespace Trees
{
    template <typename T>
    struct Node
    {
        T item;

        Node<T>* leftNode;
        Node<T>* rightNode;
    };

    template <typename T>
    class BinarySearchTree
    {
    public:
        BinarySearchTree();
        ~BinarySearchTree();

        void insert(Node<T>* root, T item);
        void remove(Node<T>* root, const T& item);
        bool contains(const T& item) const;

        T preorderTraverse();
        T inorderTraverse();
        T postorderTraverse();
    private:
        void empty();

        Node<T>* root;
        size_t nodes;
    };

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree() :
        root(nullptr),
        nodes(0U)
    {
    }

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree()
    {
        empty();
    }

    template <typename T>
    void BinarySearchTree<T>::insert(Node<T>* root, T item)
    {
        Node<T>* parentNode = nullptr;
        Node<T>* currentNode = root;

        while (currentNode)
        {
            parentNode = currentNode;

            if (item < currentNode->item)
            {
                currentNode = currentNode->leftNode;
            }
            else if (item > currentNode->item)
            {
                currentNode = currentNode->rightNode;
            }
            else
            {
                // This BST implementation ignores duplicate values.
                return;
            }
        }

        Node<T>* node = new Node<T>();

        node->item = item;
        node->leftNode = nullptr;
        node->rightNode = nullptr;

        if (parentNode)
        {
            // By this point, the BST should not have
            if (item < parentNode->item)
            {
                parentNode->leftNode = node;
            }
            else
            {
                parentNode->rightNode = node;
            }
        }
        else
        {
            root = node;
        }
    }

    template < typename T >
    void BinarySearchTree< T >::remove(Node<T>* root, const T& item)
    {
        Node<T>* parentNode = nullptr;
        Node<T>* currentNode = root;

        while (currentNode)
        {
            if (item < currentNode->item)
            {
                parentNode = currentNode;
                currentNode = currentNode->leftNode;
            }
            else if (item > currentNode->item)
            {
                parentNode = currentNode;
                currentNode = currentNode->rightNode;
            }
            else
            {
                if (parentNode)
                {
                }
                else
                {
                    if (currentNode->rightNode)
                    {
                        currentNode->rightNode;
                    }
                }

                break;
            }
        }
    }
}
