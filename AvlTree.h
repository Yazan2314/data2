//
// Created by yazan on 09/01/2025.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

using namespace std;

enum struct RotatingType {
    LL = 0,
    LR = 1,
    RL = 2,
    RR = 3,
    NOCHANGENEEDED = 4,
};


template <class Key,class Data>
class TreeNode{
public:
    Key key;
    Data data;
    TreeNode* m_parent;
    TreeNode* m_right;
    TreeNode* m_left;
    int NodeHeight;

    TreeNode(Key key,Data data, TreeNode* parent= nullptr): key(key), data(data),
                                                            m_parent(parent), m_right(nullptr), m_left(nullptr), NodeHeight(0){}

    ~TreeNode() = default;
    TreeNode(const TreeNode& other) = default;
};

template <class Key,class Data>
class AVLTree {

public:
    TreeNode<Key,Data>* m_root;
    TreeNode<Key,Data>* maxValueNode;
    TreeNode<Key,Data>* minValueNode;
    int m_size;

    AVLTree(): m_root(nullptr), maxValueNode(nullptr), minValueNode(nullptr), m_size(0){};
    AVLTree(const AVLTree<Key,Data>& other) = default;
    ~AVLTree() = default;




    void deleteTreeAux(TreeNode<Key,Data>* root)
    {
        if(!root)
        {
            return;
        }
        else
        {
            deleteTreeAux(root->m_left);
            deleteTreeAux(root->m_right);
            delete root;
        }
    }

    void deleteTree(TreeNode<Key,Data>* root)
    {
        deleteTreeAux(root);
        m_size = 0;
        m_root = nullptr;
        maxValueNode = nullptr;
        minValueNode = nullptr;
    }

    void modifyMaxValueNode()
    {
        TreeNode<Key,Data>* tmp = m_root;
        if(! m_root)
        {
            maxValueNode = nullptr;
            return;
        }
        else
        {
            while (tmp->m_right)
                tmp = tmp->m_right;
        }
        maxValueNode = tmp;
    }

    void modifyMinValueNode(){
        TreeNode<Key,Data>* tmp = m_root;
        if(!m_root)
        {
            minValueNode = nullptr;
            return;
        }
        else
        {
            while (tmp->m_left)
                tmp = tmp->m_left;
        }
        minValueNode = tmp;
    }

    TreeNode<Key,Data>* searchNodeAux(TreeNode<Key,Data>* root, Key key){
        if(!root)
            return nullptr;
        else if(key == root->key)
            return root;
        else if(key > root->key)
            return searchNodeAux(root->m_right, key);
        return searchNodeAux(root->m_left, key);

    }

    TreeNode<Key,Data>* searchNode(Key key){
        return searchNodeAux(m_root, key);
    }

    bool isLeaf(TreeNode<Key,Data>* tNode){
        if (tNode->m_right == nullptr && tNode->m_left == nullptr){
            return true;
        }
        return (false);
    }

    void modifyNodeHeight(TreeNode<Key,Data>* tNode){
        if(!tNode){
            return;
        }
        if(isLeaf(tNode)){
            tNode->NodeHeight = 0;
        }
        else if(!tNode->m_right || !tNode->m_left)
        {
            if (!tNode->m_right)
            {
                tNode->NodeHeight = tNode->m_left->NodeHeight + 1;
            } else
            {
                tNode->NodeHeight = tNode->m_right->NodeHeight + 1;
            }
        }
        else if(tNode->m_right->NodeHeight >= tNode->m_left->NodeHeight)
            tNode->NodeHeight = tNode->m_right->NodeHeight + 1;
        else
            tNode->NodeHeight = tNode->m_left->NodeHeight + 1;
    }

    void modifyTreeHeight(TreeNode<Key,Data>* root){
        if(!root)
            return;
        modifyTreeHeight(root->m_right);
        modifyTreeHeight(root->m_left);
        modifyNodeHeight(root);
    }

    int balanceFactor(TreeNode<Key,Data>* root){
        int leftSonHeight;
        int rightSonHeight;
        int BF;

        if(!root->m_left)
            leftSonHeight = -1;
        else
            leftSonHeight = root->m_left->NodeHeight;

        if(!root->m_right)
            rightSonHeight = -1;
        else
            rightSonHeight = root->m_right->NodeHeight;

        BF = leftSonHeight - rightSonHeight;
        return BF;
    }

    RotatingType checkRotation(TreeNode<Key,Data>* root){
        int BF = balanceFactor(root);
        int leftBalance = 0;
        int rightBalance = 0;
        if(root->m_left)
            leftBalance = balanceFactor(root->m_left);
        if(root->m_right)
            rightBalance = balanceFactor(root->m_right);
        if(BF == 2){
            if(leftBalance >= 0)
                return RotatingType::LL;
            if(leftBalance == -1)
                return RotatingType::LR;
        }
        else if(BF == -2){
            if(rightBalance <= 0)
                return RotatingType::RR;
            if(rightBalance == 1)
                return RotatingType::RL;
        }
        return RotatingType::NOCHANGENEEDED;
    }

    ///////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    TreeNode<Key,Data>* LL(TreeNode<Key,Data>* root)
    {
        if(! root)
            return nullptr;
        TreeNode<Key,Data>* leftSonNode=root->m_left;
        TreeNode<Key,Data>* leftSonRight=leftSonNode->m_right;
        TreeNode<Key,Data>* Parent = root->m_parent;
        if(leftSonRight)
            leftSonRight->m_parent=root;
        root->m_left= leftSonRight;
        leftSonNode->m_parent = Parent;
        leftSonNode->m_right = root;
        if(Parent)
        {
            if(Parent->m_left == root)
                Parent->m_left = leftSonNode;
            else
                Parent->m_right = leftSonNode;
        }
        root->m_parent= leftSonNode;
        modifyNodeHeight(root);
        modifyNodeHeight(leftSonNode);

        return leftSonNode;
    }

    TreeNode<Key,Data>* LR(TreeNode<Key,Data>* root)
    {
        TreeNode<Key,Data>* leftSonNode=root->m_left;
        TreeNode<Key,Data>* leftSonRight=leftSonNode->m_right;
        TreeNode<Key,Data>* leftSonRightLeft=leftSonRight->m_left;
        TreeNode<Key,Data>* leftSonRightRight=leftSonRight->m_right;
        leftSonRight->m_parent=root->m_parent;
        root->m_left=leftSonRightRight;
        if(leftSonRightRight != nullptr)
            leftSonRightRight->m_parent=root;
        leftSonRight->m_right=root;
        root->m_parent=leftSonRight;
        leftSonRight->m_left=leftSonNode;
        leftSonNode->m_parent=leftSonRight;
        leftSonNode->m_right=leftSonRightLeft;
        if(leftSonRightLeft != nullptr)
            leftSonRightLeft->m_parent=leftSonNode;
        modifyNodeHeight(root);
        modifyNodeHeight(leftSonNode);
        modifyNodeHeight(leftSonRight);
        return leftSonRight;
    }

    TreeNode<Key,Data>* RR(TreeNode<Key,Data>* root)
    {
        if(! root)
            return nullptr;
        TreeNode<Key,Data>* rightSonNode=root->m_right;
        TreeNode<Key,Data>* rightSonLeft=rightSonNode->m_left;
        TreeNode<Key,Data>* Parent = root->m_parent;
        if(rightSonLeft)
            rightSonLeft->m_parent=root;
        root->m_right= rightSonLeft;
        rightSonNode->m_parent = Parent;
        rightSonNode->m_left = root;
        if(Parent)
        {
            if(Parent->m_left == root)
                Parent->m_left = rightSonNode;
            else
                Parent->m_right = rightSonNode;
        }
        root->m_parent= rightSonNode;
        modifyNodeHeight(root);
        modifyNodeHeight(rightSonNode);

        return rightSonNode;
    }



    TreeNode<Key,Data>* RL(TreeNode<Key,Data>* root){
        TreeNode<Key,Data>* rightSonNode=root->m_right;
        TreeNode<Key,Data>* rightSonLeft=rightSonNode->m_left;
        TreeNode<Key,Data>* rightSonLeftLeft=rightSonLeft->m_left;
        TreeNode<Key,Data>* rightSonLeftRight=rightSonLeft->m_right;
        rightSonLeft->m_parent=root->m_parent;
        root->m_right=rightSonLeftLeft;
        if(rightSonLeftLeft != nullptr)
            rightSonLeftLeft->m_parent=root;
        rightSonLeft->m_left=root;
        root->m_parent=rightSonLeft;
        rightSonLeft->m_right=rightSonNode;
        rightSonNode->m_parent=rightSonLeft;
        rightSonNode->m_left=rightSonLeftRight;
        if(rightSonLeftRight != nullptr)
            rightSonLeftRight->m_parent=rightSonNode;
        modifyNodeHeight(root);
        modifyNodeHeight(rightSonNode);
        modifyNodeHeight(rightSonLeft);
        return rightSonLeft;
    }
    ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////

    TreeNode<Key,Data>* balanceTree(TreeNode<Key,Data>* root){
        RotatingType rotation = checkRotation(root);
        if(rotation == RotatingType::LL)
            return LL(root);
        else if(rotation == RotatingType::RR)
            return RR(root);
        else if(rotation == RotatingType::RL)
            return RL(root);
        else if(rotation == RotatingType::LR)
            return LR(root);
        return root;
    }

    bool isKeyContainedAux(TreeNode<Key,Data>* root, Key key){
        if(!root)
            return false;
        if(key == root->key)
            return true;
        if(key > root->key)
            return isKeyContainedAux(root->m_right, key);
        else
            return isKeyContainedAux(root->m_left, key);
    }

    bool isKeyContained(Key key){
        return isKeyContainedAux(m_root, key);
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////
    TreeNode<Key,Data>* findNext(TreeNode<Key,Data>* root){
        if (!root) {
            return nullptr;
        }
        if (!root->m_right) {
            TreeNode<Key,Data>* index = root->m_parent;
            TreeNode<Key,Data>* tmp = root;
            while (index && index->m_right == tmp) {
                tmp = index;
                index = index->m_parent;
            }
            return index;
        }
        TreeNode<Key,Data>* tmp = root->m_right;
        while (tmp->m_left) {
            tmp = tmp->m_left;
        }
        return tmp;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TreeNode<Key,Data>* deleteNodeAux(TreeNode<Key,Data>* root, Key key){
        if(!root)
            return nullptr;
        if (key > root->key)
        {
            root->m_right = deleteNodeAux(root->m_right, key);
        }
        else if (key < root->key)
        {
            root->m_left = deleteNodeAux(root->m_left, key);
        }
        else if (key == root->key)
        {
            if (isLeaf(root))
            {
                TreeNode<Key,Data>* tmp = root;
                root = root->m_parent;
                if(!root)
                {
                    delete tmp;
                    return nullptr;
                }
                if(root->m_right == tmp)
                    root->m_right = nullptr;
                else
                    root->m_left = nullptr;
                delete tmp;
                return nullptr;
            }
            else if (root->m_left != nullptr && root->m_right == nullptr)
            {
                TreeNode<Key,Data>* tmp = root->m_left;
                tmp->m_parent = root->m_parent;
                delete root;
                return tmp;
            }
            else if (root->m_left == nullptr && root->m_right != nullptr)
            {
                TreeNode<Key,Data>* tmp = root->m_right;
                tmp->m_parent = root->m_parent;
                delete root;
                return tmp;
            }
            else
            {
                TreeNode<Key,Data>* next = findNext(root);
                if(next == nullptr)
                    return nullptr;
                root->key = next->key;
                root->data = next->data;
                root->m_right = deleteNodeAux(root->m_right, next->key);
            }
        }
        modifyNodeHeight(root);
        return balanceTree(root);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void deleteNode(Key key) {
        m_root = deleteNodeAux(m_root, key);
        m_size--;
        modifyNodeHeight(m_root);
        modifyMaxValueNode();
        modifyMinValueNode();
    }

    TreeNode<Key,Data>* addNodeToTreeAux(TreeNode<Key,Data>* root, TreeNode<Key,Data>* tNode){
        if(!tNode){
            return nullptr;
        }
        if(!root){
            tNode->m_parent = root;
            return tNode;
        }
        if(root->key < tNode->key){
            root->m_right = addNodeToTreeAux(root->m_right, tNode);
            root->m_right->m_parent = root;
        }
        else if(root->key > tNode->key){
            root->m_left = addNodeToTreeAux(root->m_left, tNode);
            root->m_left->m_parent = root;
        }
        modifyNodeHeight(root);
        return balanceTree(root);
    }

    TreeNode<Key,Data>* addNodeToTree(TreeNode<Key,Data>* tTree){
        TreeNode<Key,Data>* newNode= addNodeToTreeAux(m_root, tTree);
        modifyMaxValueNode();
        modifyMinValueNode();
        m_size++;
        return newNode;
    }

    bool addKeyAndData(Key key, Data &data) {
        if (isKeyContained(key)) {
            return false;
        }
        TreeNode<Key,Data>* Node = new TreeNode<Key,Data>(key, data);
        m_root = addNodeToTree(Node);
        m_root->m_parent = nullptr;
        modifyMaxValueNode();
        modifyMinValueNode();
        modifyNodeHeight(m_root);
        return true;
    }


};






#endif //AVLTREE_H
