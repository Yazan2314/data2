//
// Created by yazan on 09/01/2025.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "AvlTree.h"








template <class Data>

class HashTable{
public:
    int m_arrSize;
    int m_objectsNum;
    AVLTree<int,Data>** m_arrOfobjects;


    HashTable(): m_arrSize(1), m_objectsNum(0)
    {
        m_arrOfobjects = new AVLTree<int,Data>*[1];
        m_arrOfobjects[0] = new AVLTree<int,Data>();
    }


    ~HashTable()
    {
        for(int i=0; i < m_arrSize; i++) {
            m_arrOfobjects[i]->deleteTree(m_arrOfobjects[i]->m_root);
            delete m_arrOfobjects[i];
        }
        delete[] m_arrOfobjects;
    }


    int hashFunction(int num){
        return num % m_arrSize;
    }


    void copyData(int id, Data data, AVLTree<int,Data>* tmp)
    {
        tmp->addKeyAndData(id,data);
    }


    void expand(){
        m_arrSize *=2 ;
        AVLTree<int,Data>** newArr= new AVLTree<int,Data>*[m_arrSize];
        for (int i = 0; i < m_arrSize; i++) {
            newArr[i] = new AVLTree<int,Data>();
        }

        for(int i = 0; i < (m_arrSize / 2); i++){
            AVLTree<int,Data>* tmpT = m_arrOfobjects[i];
            TreeNode<int,Data>* tmpNode = tmpT->minValueNode;
            while(tmpNode){
                int index= hashFunction(tmpNode->key);
                AVLTree<int,Data>* destT = newArr[index];
                copyData(tmpNode->key, tmpNode->data, destT);
                tmpNode = tmpT->findNext(tmpNode);
            }
        }

        for (int i = 0; i < m_arrSize / 2; i++) {
            m_arrOfobjects[i]->deleteTree(m_arrOfobjects[i]->m_root);
            delete m_arrOfobjects[i];
        }
        delete[] m_arrOfobjects;
        m_arrOfobjects=newArr;
    }
    template<class opertion>
    void expand2(opertion op){
        m_arrSize *=2 ;
        AVLTree<int,Data>** newArr= new AVLTree<int,Data>*[m_arrSize];
        for (int i = 0; i < m_arrSize; i++) {
            newArr[i] = new AVLTree<int,Data>();
        }

        for(int i = 0; i < (m_arrSize / 2); i++){
            AVLTree<int,Data>* tmpT = m_arrOfobjects[i];
            TreeNode<int,Data>* tmpNode = tmpT->minValueNode;
            while(tmpNode){
                int index= hashFunction((tmpNode->data.get()->*op)());
                AVLTree<int,Data>* destT = newArr[index];
                copyData(tmpNode->key, tmpNode->data, destT);
                tmpNode = tmpT->findNext(tmpNode);
            }
        }

        for (int i = 0; i < m_arrSize / 2; i++) {
            m_arrOfobjects[i]->deleteTree(m_arrOfobjects[i]->m_root);
            delete m_arrOfobjects[i];
        }
        delete[] m_arrOfobjects;
        m_arrOfobjects=newArr;
    }


    void addObj(int id, Data data1){
        m_objectsNum++;
        if(m_objectsNum >= (m_arrSize / 2)){
            expand();
        }
        int index = hashFunction(id);
        AVLTree<int,Data>* tmp = m_arrOfobjects[index];
        tmp->addKeyAndData(id,data1);
    }

    template<class opertion>

    void addobj2(int record ,int id ,Data data2 , opertion op) {
        m_objectsNum++;
        if(m_objectsNum >= (m_arrSize / 2)){
            expand2(op);
        }
        int index = hashFunction(record);
        AVLTree<int,Data>* tmp = m_arrOfobjects[index];
        tmp->addKeyAndData(id,data2);
    }


    Data& getObj(int id){
        int index = hashFunction(id);
        AVLTree<int,Data>* tmp = m_arrOfobjects[index];

        return tmp->searchNode(id)->data;
    }


    bool Contained(int id)
    {
        int index = hashFunction(id);
        AVLTree<int,Data>* tmp = m_arrOfobjects[index];
        if(!tmp)
            return false;
        return tmp->isKeyContained(id);
    }


    Data operator[](int id)
    {
        if(! m_arrOfobjects[hashFunction(id)] || ! m_arrOfobjects[hashFunction(id)]->searchNode(id))
            return nullptr;
        return m_arrOfobjects[hashFunction(id)]->searchNode(id)->data;

    }



    //////////////////////////// yazan add ////////////////////////////
    void deleteObj(int id,int teamid) {
        int index = hashFunction(id);
        AVLTree<int,Data>* tmp = m_arrOfobjects[index];
        tmp->deleteNode(teamid);
        m_objectsNum--;
    }



    AVLTree<int,Data>* get_avl_tree(int id) {
        int index = hashFunction(id);
        AVLTree<int,Data>* tmp = m_arrOfobjects[index];
        return tmp;
    }
};
#endif //HASHTABLE_H
