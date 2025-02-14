#include <string>
#include "Node.hpp"

class Node {
    private:
        std::string title;
        std::string authorLast;
        std::string authorFirst;
        std::string publisher;
        std::string publicationDate;
        std::string genre;
        std::string synopsis;
        int isbn;
        Node* left;
        Node* right;
    
    Node::Node(std::string title, std::string authorLast, std::string authorFirst, std::string publisher,
        std::string publicationDate, std::string genre, std::string synopsis, int isbn) {
            this->title = title;
            this->authorLast = authorLast;
            this-> authorFirst = authorFirst;
            this->publisher = publisher;
            this->publicationDate = publicationDate;
            this->genre = genre;
            this->synopsis = synopsis;
            this->isbn = isbn;
        }

    Node::Node(std::string title, std::string authorLast, std::string authorFirst, std::string publisher,
        std::string publicationDate, std::string genre, std::string synopsis, int isbn, Node* left, Node* right) {
        this->title = title;
        this->authorLast = authorLast;
        this-> authorFirst = authorFirst;
        this->publisher = publisher;
        this->publicationDate = publicationDate;
        this->genre = genre;
        this->synopsis = synopsis;
        this->isbn = isbn;
        this->left = left;
        this->right = right;
        }

    public:
        std::string Node::getTitle() {
            return title;
        }

        std::string Node::getAuthorLast() {
            return authorLast;
        }

        std::string Node::getAuthorFirst() {
            return authorFirst;
        }   

        std::string Node::getPublisher() {
            return publisher;
        }

        std::string Node::getPublicationDate() {
            return publicationDate;
        }

        std::string Node::getGenre() {
            return genre;
        }

        std::string Node::getSynposis() {
            return synopsis;
        }

        int Node::getISBN() {
            return isbn;
        }

        std::string Node::toString() {
            return "Title: " + title + "\nAuthor Last Name: " + authorLast + "\nAuthor First Name: "
            + authorFirst + "\nPublisher: " + publisher + "\nPublication Date: " + publicationDate +
            "\nGenre: " + genre + "\nSynposis: " + synopsis + "\nISBN: " + std::to_string(isbn);
        }
};
