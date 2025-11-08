/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    struct BST<K, V>::Node*& ctmd = find(root, key);
    if (ctmd == nullptr) {
        return V();
    }
    return ctmd->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == nullptr) {
        return subtree;
    }
    if (subtree->key == key) {
        return subtree;
    } else if (subtree->key > key) {
        return find(subtree->left, key);
    } else {
        return find(subtree->right, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    if (find(root, key) != nullptr) {
        return;
    }
    // your code here
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr) {
        subtree = new Node(key, value);
        return;
    }
    if (subtree->key > key) {
        insert(subtree->left, key, value);
    } else {
        insert(subtree->right, key, value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    K tmpk = first->key;
    V tmpv = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = tmpk;
    second->value = tmpv;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    if (find(root, key) == nullptr) {
        return;
    }
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    if (subtree->key == key) {
        if (subtree->left == nullptr && subtree->right == nullptr) {
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != nullptr && subtree->right == nullptr) {
            Node* tmp = subtree;
            subtree = subtree->left;
            delete tmp;
        } else if (subtree->left == nullptr && subtree->right != nullptr) {
            Node* tmp = subtree;
            subtree = subtree->right;
            delete tmp;
        } else {
            Node* cnmb = subtree->left;
            while (cnmb->right != nullptr) {
                cnmb = cnmb->right;
            }
            swap(subtree, cnmb);
            remove(subtree->left, key);
        }
    } else {
        if (subtree->key > key) {
            remove(subtree->left, key);
        } else {
            remove(subtree->right, key);
        }
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> cnm;
    // your code here
    for (std::pair<K, V> nmsl : inList) {
        cnm.insert(nmsl.first, nmsl.second);
    }
    return cnm;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> cnm(inList.size(), 0);
    std::sort(inList.begin(), inList.end());
    do {
        BST<K, V> nmsl = listBuild(inList);
        cnm[nmsl.height()]++;
    } while (std::next_permutation(inList.begin(), inList.end()));
    return cnm;
}