#include <iostream>
#include <string>

#include "Manager.hpp"

class Manager {
    private:
        Node* root;

    public:
        Manager::Manager() {
            root = nullptr;
        } 

        bool Manager::add(std::string title, std::string authorLast, std::string authorFirst,
            std::string publisher, std::string publicationDate, std::string genre, 
            std::string synopsis, int isbn) {
            if (root == NULL) {
                root = new Node(title, authorLast, authorFirst, publisher, publicationDate, genre,
                    synopsis, isbn);
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
                    parent->left = new Node(title, authorLast, authorFirst, publisher, publicationDate, 
                        genre, synopsis, isbn);
                } else {
                    parent->right = new Node(title, authorLast, authorFirst, publisher, publicationDate, 
                        genre, synopsis, isbn);
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

        void Manager::inorder(Node* current) {
            if (current != nullptr) {
                inorder(current->left);
                std::cout << current->toString() << std::endl;
                inorder(current->right);
            }
        }

        void Manager::preorder(Node* current) {
            if (current != nullptr) {
                std::cout << current->toString() << std::endl;
                preorder(current->left);
                preorder(current->right);
            }
        }

        void Manager::postorder(Node* current) {
            if (current != nullptr) {
                postorder(current->left);
                postorder(current->right);
                std::cout << current->toString() << std::endl;
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
};