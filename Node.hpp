#include <string>

#ifndef NODE_H
#define NODE_H

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

    public:
        Node(std::string title, std::string authorLast, std::string authorFirst, std::string publisher,
            std::string publicationDate, std::string genre, std::string synopsis, int isbn);

        Node(std::string title, std::string authorLast, std::string authorFirst, std::string publisher,
            std::string publicationDate, std::string genre, std::string synopsis, int isbn, 
            Node* left, Node* right);

        std::string getTitle();
        std::string getAuthorLast();
        std::string getAuthorFirst();
        std::string getPublisher();
        std::string getPublicationDate();
        std::string getGenre();
        std::string getSynposis();
        std::string getISBN();
        std::string toString();
};

#endif