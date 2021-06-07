#pragma once
#include <iostream>
#include<vector>
#include <stack>



namespace ariel
{
  
    template <class Type>
    class BinaryTree
    {
        public:
            class Node
            {
            public:
                Type value;
                Node * father;
                Node * left;
                Node * right;
                Node(Type val):value(val),father(nullptr),left(nullptr),right(nullptr){}
            };
      
      
        Node * head;
        BinaryTree():head(nullptr){}
        ~BinaryTree()
        {   
        }
      
        BinaryTree(BinaryTree&& other)noexcept
        {
            this->head = other.head;
            other.head=nullptr;
        }
      
        BinaryTree(const BinaryTree& other)
        {
            this->head = other.head;
        }
      
        BinaryTree& operator=(BinaryTree&& other) noexcept
        {
            if(head)
            {
                delete head;
            }
            this->head = other.head;
            other.head = nullptr;
            return *this;
        }

        BinaryTree& operator=(BinaryTree const& other)
        {
            if(this ==&other)
            {
                return *this;
            }
            if(head)
            {
                delete head; 
            }
            if(other.head)
            {
            head = &(biuld(this->head,other.head));
            }
            return *this;
        }
        Node& biuld(Node * root,Node * other)
        {
            if(!other)
            {
                return *root;
            }
            root=new Node(other->value);
            root->left = &(biuld(root->left,other->left));
            root->right = &(biuld(root->right,other->right));
            return *root;
        }

        BinaryTree& add_root(const Type x)
        {
            if(this->head)
            {
                head->value = x;
            }
            else
            {
                head = (Node*)new Node(x);
            }
            return *this;
        }
      
        BinaryTree& add_left(const Type x,const Type y)
        {
            Node * temp = search(head,x);
            if(temp==nullptr)
            {
                throw(std::invalid_argument{"no matching node from the left"});           
            }
            if(!temp->left)
            {
                temp->left = (Node *)new Node(y);
            }
            else
            {
                temp->left->value = y;
            }
            return *this;
        }

        BinaryTree& add_right(const Type &x,const Type &y)
        {
            Node * temp = search(head,x);
            if(temp==nullptr)
            {
                throw(std::invalid_argument{"no matching node from the right"});           
            }
            if(!temp->right)
            {
                temp->right = (Node *)new Node(y);
            }
            else
            {
                temp->right->value = y;
            }
            return *this;
        }

    Node* search(Node* node, Type od)
    {
        if(node != nullptr)
        {
            if(node->value==od)
            {
                return node;
            } 
            Node * foundNode = search( node->left,od);
            if(foundNode == nullptr) 
            {
                foundNode = search(node->right,od);
            }
            return foundNode;
        } 
        return nullptr;

    }

    friend std::ostream& operator<< (std::ostream& output, BinaryTree& c)
    {
        c.printInorder(c.head);
        std::cout<<std::endl;
        return output;
    }
    void printInorder(Node* node)
    {
        if (node == NULL)
        {
            return;
        }
        printInorder(node->left);
        std::cout << node->value << " ";
        printInorder(node->right);
    }
      
// --------------------------------- class inorder iterator ----------------------------------  
      
    class inorder_iterator
    {
        public:
        Node * root;
        Node * pointer;
        std::vector<Node *> stack;
        inorder_iterator(Node * ptr=nullptr):root(ptr),pointer(ptr)
        {
            biuld(root); 
            if(stack.size()>1)
            {
                root = stack[0];
            }
        }
        void biuld(Node * it)
        {
            if(!it)
            {
                return;
            }
            biuld(it->left);
            stack.push_back(it);
            biuld(it->right);   
        }
      
        Type& operator*()
        {
            return this->root->value;
        }
        Type* operator->()
        {
            return &(this->root->value);
        }
        inorder_iterator& operator++()
        {
            if(stack.size()>1)
            {
                stack.erase(stack.begin());
                root = stack[0];
            }
            else
            {
            root = nullptr;
            }
            return *this;
        }
        inorder_iterator operator++(int)
        {
            inorder_iterator temp = *this;
            if(stack.size()>1)
            {
                stack.erase(stack.begin());
                root = stack[0];
            }
            else
            {
            root = nullptr;
            } 
            return temp;
        }
        bool operator==(const inorder_iterator &itr)
        {

            return this->root==itr.root;
        }
        bool operator!=(const inorder_iterator &itr)
        {
            return this->root!=itr.root;
        }
    };
      
// --------------------------------- class preorder iterator ----------------------------------  
      
    class preorder_iterator
    {
        public:
        Node * root;
        std::vector<Node *> stack;
        preorder_iterator(Node* ptr=nullptr):root(ptr)
        {
            biuld(root); 
            if(stack.size()>1)
            {
                root = stack[0];
            }
        }
        void biuld(Node * it)
        {
            if(!it)
            {
                return;
            }
            stack.push_back(it);
            biuld(it->left);
            biuld(it->right);
        }
        Type& operator*()
        {
            return this->root->value;
        }
        Type* operator->()
        {
            return &(this->root->value);
        }
        preorder_iterator& operator++()
        {
            if(stack.size()>1)
            {
                stack.erase(stack.begin());
                root = stack[0];
            }
            else
            {
            root = nullptr;
            }
            return *this;
        }
        preorder_iterator operator++(int)
        {
            preorder_iterator temp = *this;
            if(stack.size()>1)
            {
                stack.erase(stack.begin());
                root = stack[0];
            }
            else
            {
            root = nullptr;
            } 
            return temp;
        }
        bool operator==(const preorder_iterator &itr)
        {
            return this->root==itr.root;
        }
        bool operator!=(const preorder_iterator &itr)
        {
            return this->root!=itr.root;
        }
    };
      
// ---------------------------------  class postorder iterator ----------------------------------  
      
    class postorder_iterator 
    {
        public:
        Node * root;
        std::vector<Node *> stack;
        postorder_iterator(Node* ptr=nullptr):root(ptr)
        {
            biuld(root); 
            if(stack.size()>1)
            {
                root = stack[0];
            }
        }
        void biuld(Node * it)
        {
            if(!it)
            {
                return;
            }
            biuld(it->left);
            biuld(it->right);
            stack.push_back(it);
        }
        Type& operator*()
        {
            return this->root->value;
        }
        Type* operator->()
        {
            return &(this->root->value);
        }
        postorder_iterator& operator++()
        {
            if(stack.size()>1)
            {
                stack.erase(stack.begin());
                root = stack[0];
            }
            else
            {
            root = nullptr;
            }
            return *this;
        }
        postorder_iterator operator++(int)
        {
            postorder_iterator temp = *this;
            if(stack.size()>1)
            {
                stack.erase(stack.begin());
                root = stack[0];
            }
            else
            {
            root = nullptr;
            } 
            return temp;
        }
      
        bool operator==(const postorder_iterator &itr)
        {
            return this->root==itr.root;
        }
        bool operator!=(const postorder_iterator &itr)
        {
            return this->root!=itr.root;
        }
    };
      
   // --------------------------------- begain and end preorder/inorder/postorder ----------------------------------  
      
        inorder_iterator begin()
        {
            return inorder_iterator{head};
        }
        preorder_iterator begin_preorder()
        {
            return preorder_iterator{head};
        }
        inorder_iterator begin_inorder()
        {
            return inorder_iterator{head};
        }
        postorder_iterator begin_postorder()
        {
            return postorder_iterator{head};
        }
        inorder_iterator end()
        {
            return inorder_iterator{nullptr};
        }
        inorder_iterator end_inorder()
        {
            return inorder_iterator{nullptr};
        }
        
        preorder_iterator end_preorder()
        {
            return preorder_iterator{nullptr};
        }
        postorder_iterator end_postorder()
        {
            return postorder_iterator{nullptr};
        }
};
}
