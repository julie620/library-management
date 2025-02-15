#include <iostream>
#include <string>
#include <stack>
#include <vector>

#include "Manager.hpp"

        Node* root;

        Manager::Manager() {
            root = nullptr;
        } 

        bool Manager::add(std::string title, std::string authorLast, std::string authorFirst,
            std::string publisher, std::string publicationDate, std::string genre, 
            std::string synopsis, int isbn) {
            Node temp(title, authorLast, authorFirst, publisher, publicationDate, genre,
                synopsis, isbn);
            if (root == NULL) {
                root = &temp;
                return true;
            } else {
                Node* current = root;
                Node* parent = root;
                while (current != NULL) {
                    if (isbn < current->getISBN()){
                        parent = current;
                        *current = current->getLeft();
                    } else if(isbn > current->getISBN()){
                        parent = current;
                        *current = current->getRight();
                    } else {
                        return false;
                    }
                }
                if (isbn < parent->getISBN()) {
                    parent->left = &temp;
                } else {
                    parent->right = &temp;
                }
                return true;
            }
        }

        bool Manager::remove(int isbn) {
            Node* current = root;
            Node* parent = root;
            while(isbn != current->getISBN()){
                if (isbn < current->getISBN()){
                    parent = current;
                    current = current->left;
                } else if (isbn > current->getISBN()) {
                    parent = current;
                    current = current->right;
                } else {
                    return false;
                }
            }
            if (current == root) {
                if (current->left == nullptr) {
                    root = current->right;
                } else if (current->right == nullptr) {
                    root = current->left;
                } else {
                    removeRootTwo(isbn);
                }
            } else if (current->left == nullptr && current->right == nullptr) {
                removeLeaf(current, parent, isbn);
            } else if (current->left == nullptr) {
                removeChildR(current, parent, isbn);
            } else if (current->right == nullptr) {
                removeChildL(current, parent, isbn);
            } else {
                removeTwoChild(current, parent, isbn);
            }
            return true;
        }

        void Manager::removeRootTwo(int isbn) {
            Node* replacement = root->right;
            while (replacement->left != nullptr) {
                replacement = replacement->left;
            }
            root = new Node(replacement->getTitle(), replacement->getAuthorLast(), 
                replacement->getAuthorFirst(), replacement->getPublisher(), 
                replacement->getPublicationDate(), replacement->getGenre(), 
                replacement->getSynposis(), replacement->getISBN());
        }

        void Manager::removeLeaf(Node* current, Node* parent, int isbn) {
            if (parent->left->getISBN() == isbn) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }

        void Manager::removeChildR(Node* current, Node* parent, int isbn){
            if (isbn < parent->getISBN()) {
                parent->left = current->right;
            } else {
                parent->right = current->right;
            }
        }

        void Manager::removeChildL(Node* current, Node* parent, int isbn) {
            if (isbn < parent->getISBN()) {
                parent->left = current->left;
            } else {
                parent->right = current->left;
            }
        }
        
        void Manager::removeTwoChild(Node* current, Node* parent, int isbn) {
            Node* replacement = current->right;
            while (replacement->left != nullptr) {
                replacement = replacement->left;
            }
            if (isbn < parent->getISBN()) {
                parent->left = replacement;
            } else {
                parent->right = replacement;
            }
        }

        bool Manager::validMod(int isbn) {
            Node* current = root;
            while (isbn != current->getISBN()) {
                if (isbn < current->getISBN()) {
                    current = current->left;
                } else if (isbn > current->getISBN()) {
                    current = current->right;
                } else {
                    return false;
                }
            }
            return true;
        }

        Node* Manager::modNode(int isbn) {
            Node* current = root;
            while (isbn != current->getISBN()) {
                if (isbn < current->getISBN()) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return current;
        }

        bool Manager::modify(std::string title, std::string authorLast, std::string authorFirst, 
            std::string publisher, std::string publicationDate, std::string genre, 
            std::string synopsis, int isbn) {
                if (validMod(isbn) != true) {
                    std::cout << "false" << std::endl;
                    return false;
                }
                Node* current = root;
                while (isbn != current->getISBN()) {
                    if (isbn < current->getISBN()) {
                        current = current->left;
                    } else if (isbn > current->getISBN()) {
                        current = current->right;
                    }
                }
                remove(isbn);
                add(title, authorLast, authorFirst, publisher, publicationDate, genre, synopsis, 
                    isbn);
                return true;
        }

        Node* Manager::traversal() {
            Node* current = root;
            return current;
        }

        void Manager::inorder() {
            std::vector<std::string> list;
            std::stack<Node*> s;
            Node* current = root;
            while (current != nullptr || s.empty() == false) {
                while (current != nullptr) {
                    s.push(current);

                    *current = *current->left;
                }
                current = s.top();
                s.pop();
                list.push_back(current->toString());
                current = current->right;
            }
            for (int i = 0; i < list.size(); i ++) {
                std::cout << list[i] << " ";
            }
        }

        void Manager::preorder() {
            if (root == nullptr) {
                return;
            }
            std::stack<Node*> s;
            s.push(root);
            while (s.empty() == false) {
                Node* temp = s.top();
                std::cout << temp->toString() << std::endl;
                s.pop();
                if (temp->right) {
                    s.push(temp->right);
                }
                if (temp->left) {
                    s.push(temp->left);
                }
            }
        }

        void Manager::postorder() {
            std::vector<std::string> list;
            std::stack<Node*> s;
            s.push(root);
            Node* previous = nullptr;
            while(!s.empty()) {
                Node* current = s.top();
                if (previous == nullptr || previous->left == current || 
                    previous->right == current) {
                    if (current->left) {
                        s.push(current->left);
                    } else if (current->right) {
                        s.push(current->right);
                    } else {
                        s.pop();
                        list.push_back(current->toString());
                    }
                } else if (current->left == previous) {
                    if (current->right) {
                        s.push(current->right);
                    } else {
                        s.pop();
                        list.push_back(current->toString());
                    }
                } else if (current->right == previous) {
                    s.pop();
                    list.push_back(current->toString());
                }
                previous = current;
            }
            for (int i = 0; i < list.size(); i ++) {
                std::cout << list[i] << " ";
            }
        }

        std::string Manager::title(int isbn) {
            return modNode(isbn)->getTitle();
        }

        std::string Manager::authorLast(int isbn) {
            return modNode(isbn)->getAuthorLast();
        }

        std::string Manager::authorFirst(int isbn) {
            return modNode(isbn)->getAuthorFirst();
        }

        std::string Manager::publisher(int isbn) {
            return modNode(isbn)->getPublisher();
        }

        std::string Manager::publicationDate(int isbn) {
            return modNode(isbn)->getPublicationDate();
        }

        std::string Manager::genre(int isbn) {
            return modNode(isbn)->getGenre();
        }

        std::string Manager::synopsis(int isbn) {
            return modNode(isbn)->getSynposis();
        }