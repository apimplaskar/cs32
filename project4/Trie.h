//
//  Trie.h
//  project4
//
//  Created by Aditya Pimplaskar on 3/6/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <iostream>
//// TRIE NODE /////////
template<typename ValueType>
class TrieNode{
public:
    TrieNode(){}
    TrieNode(char k, ValueType v){ //overloaded constructor for TrieNode
        key = k;
        values.push_back(v);
    }
    TrieNode(char k){  //overloaded constructor for TrieNode
        key = k;
    }
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    std::vector<ValueType> findRequireFirstMatch(const std::string& key, bool exactMatchOnly) const;
    char key;
    std::vector<ValueType> values;
    std::vector<TrieNode*> m_children; //Vector that holds pointers to children
};

//// TRIE NODE FUNCTIONS /////
template<typename ValueType>
void TrieNode<ValueType>::insert(const std::string& key, const ValueType& value){
    if(key.size()==0){
        values.push_back(value); //add value
        return;
    }  //empty key = we are done
    char cur = key[0];
    for(TrieNode* child : m_children) { //foreach
        if(child->key == cur){ //if we can match char with key
            child->insert(key.substr(1), value);
            return;
        }
    }
    //get here if we have no more nodes that fit the char of the key -- must construct new ones
    TrieNode<ValueType>* newNode = new TrieNode<ValueType>(cur);
    m_children.push_back(newNode); //add this as a child of the current node
    newNode->insert(key.substr(1), value); //recursive call
}

template<typename ValueType>
std::vector<ValueType> TrieNode<ValueType>::findRequireFirstMatch(const std::string& key, bool exactMatchOnly) const{
    std::vector<ValueType> results;
    char cur = key[0];
    //std::cout << "current char: " << cur << std::endl;
    if(key.size() == 0){ //base case, we have reached the end
        //std::cout << "hit find's base case" << std::endl;
        return values; //done!
    }
    for(TrieNode* child: m_children){
        if(child->key == cur){
            std::vector<ValueType> temp = child->find(key.substr(1), exactMatchOnly); //since we have exact matches so far, we can still keep going if need be
            for(ValueType tval : temp){
                results.push_back(tval);
            }
        }
    }
    return results;
}


template<typename ValueType>
/*
 PSEUDOCODE:
 std::vector<ValueType> result;
 
 if (key[0] != any of the keys for m_root's children), return result
 
 Base case:
 if key == "", add that value to the result and return
 
 for each character in the string key
 if a child pointer's key character == key[i] && exactMatchOnly
 find(substring of key leaving off the matched char, false)
 else if a child pointer's key character != key[i] && exactMatchOnly
 find(substring of key leaving off that char, true)
 else
 return result
 */

std::vector<ValueType> TrieNode<ValueType>::find(const std::string& key, bool exactMatchOnly) const{
    std::vector<ValueType> results;
    char cur = key[0];
    if(key.size() == 0){ //base case, we have reached the end
        return values; //done!
    }
    for(TrieNode* child: m_children){
        if(child->key == cur){
            std::vector<ValueType> temp = child->find(key.substr(1), exactMatchOnly); //since we have exact matches so far, we can still keep going if need be
            for(ValueType tval : temp){
                results.push_back(tval);
            }
        }
        else if(!exactMatchOnly){
            std::vector<ValueType> temp = child->find(key.substr(1), true); //since we already have one mismatch, the remaining set have to be exact matches
            for(ValueType tval : temp){
                results.push_back(tval);
            }
        }
    }
    return results;
}

///// TRIE ////////

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    
private:
    TrieNode<ValueType>* m_root = nullptr; //set this when we call constructor
    void freeTrie(TrieNode<ValueType>* cur);
};

///// TRIE FUNCTIONS ///////
template<typename ValueType>
Trie<ValueType>::Trie(){
    m_root = new TrieNode<ValueType>();
}

template<typename ValueType>
Trie<ValueType>::~Trie<ValueType>(){
    freeTrie(m_root);
}

template<typename ValueType>
void Trie<ValueType>::reset(){
    freeTrie(m_root);
    m_root = new TrieNode<ValueType>;
}

template<typename ValueType>
void Trie<ValueType>::freeTrie(TrieNode<ValueType>* cur){
    if(cur == nullptr){ return; } //we're done
    for(int i = 0; i < cur->m_children.size();i++){
        freeTrie(cur->m_children[i]); //recursively calls on children
    }
    delete cur; //like a post-order traversal
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value){
    m_root->insert(key, value); //calls TrieNode's insert.
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const{
    return m_root->findRequireFirstMatch(key, exactMatchOnly); //calls trieNode's find function -- the findRequireFirstMatch function is a specialized version that makes sure that the first characters of the two sequences match
}



//OLD CODE THAT WAS RE-WRITTEN/TWEAKED
/*
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const{
    std::vector<ValueType> result;
    //Algorithm:
    //Use recursion
    //If you are following the path down the trie using the exact match
        //Follow EVERY path down the trie
        //The child path that you follow that is an exact match will recursively call again
        //The child paths that you follow that are NOT exact matches will have to match exactly the rest of the way
    TrieNode* traversal = m_root;
 }
*/

/*
 template<typename ValueType>
 void Trie<ValueType>::insert(const std::string& key, const ValueType& value){
 int key_len = key.size();
 TrieNode* traversal = m_root;
 int i = 0;
 for(;i < key_len; i++){ //loop over every character in key
 char cur = key[i];
 for(int j = 0; j < m_children.size(); j++){
 if(m_children[i].key == cur){ //if that key character exists in one of the children nodes
 if(i == key_len-1){ //if it is the last node
 traversal->values.push_back(value); //add value
 return;
 }
 traversal = m_children[i]; //move to that child node
 }
 else{ break; } //we have run out of nodes to travel to
 }
 //Traversal here is pointing to the last node that we were able to visit
 //downstream of here we want to create new nodes that lead us to the completion of our key
 if(i == key_len-1){
 traversal->values.push_back(value);
 return;
 }
 traversal -> children.push_back(new TrieNode(key[i]));
 traversal = traversal.children[0];
 }
 }
 */

#endif // TRIE_INCLUDED

