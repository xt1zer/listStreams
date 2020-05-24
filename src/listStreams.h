#pragma once
#include <string>
using std::string;

struct Node {
private:
    string surname;
    unsigned int number;
    Node *nextSurname;
    Node *nextNumber;

public:
    Node() {}

    Node(string l, unsigned int r) : surname(l), number(r),
    nextSurname(nullptr), nextNumber(nullptr) { }

    string getSurname() const {
        return surname;
    }

    unsigned int getNumber() const {
        return number;
    }

    Node *getNextBySurname() const {
        return nextSurname;
    }

    Node *getNextByNumber() const {
        return nextNumber;
    }

    void setSurname(const string& name) {
        surname = name;
    }

    void setNumber(const unsigned int& num) {
        number = num;
    }

    void setNextBySurname(Node *node) {
        nextSurname = node;
    }

    void setNextByNumber(Node *node) {
        nextNumber = node;
    }
};

class ListStreams {
public:
    typedef Node *Iterator;
private:
    Node *head = new Node;
    Node *tail = new Node;

    void pop(Iterator popAfterByName, Iterator popAfterByNum) {
        Iterator toDelete = popAfterByName->getNextBySurname();
        popAfterByName->setNextBySurname(popAfterByName->getNextBySurname()->getNextBySurname());
	if(popAfterByName == head)
	    head->setSurname(popAfterByName->getNextBySurname()->getSurname());
	if(popAfterByName->getNextBySurname() == tail)
	    tail->setSurname(popAfterByName->getSurname());
	
        popAfterByNum->setNextByNumber(popAfterByNum->getNextByNumber()->getNextByNumber());
	if(popAfterByNum == head)
	    popAfterByNum->setNumber(popAfterByNum->getNextByNumber()->getNumber());
	if(popAfterByNum->getNextByNumber() == tail)
	    tail->setNumber(popAfterByNum->getNumber());
	
        delete toDelete;
    }

    // newNode is pushed after pushAfter

    void pushByName(Node *newNode, Iterator pushAfter) {
        if (pushAfter == head)
            pushAfter->setSurname(newNode->getSurname());
        if (pushAfter->getNextBySurname() == tail)
            tail->setSurname(newNode->getSurname());

        newNode->setNextBySurname(pushAfter->getNextBySurname());
        pushAfter->setNextBySurname(newNode);
    }

    void pushByNumber(Node *newNode, Iterator pushAfter) {
        // same for number value
        if (pushAfter == head)
            pushAfter->setNumber(newNode->getNumber());
        if (pushAfter->getNextByNumber() == tail)
            tail->setNumber(newNode->getNumber());

        newNode->setNextByNumber(pushAfter->getNextByNumber());
        pushAfter->setNextByNumber(newNode);
    }

public:
    ListStreams(){
	head->setNextBySurname(tail);
	head->setNextByNumber(tail);
    }
    	Iterator getHead() { return head; }

    bool isEmpty() const {
        return head->getNextBySurname() == tail;
    }

    short int pop(const string &name) {
        if (isEmpty()) return -1;

        // find node to pop
        Iterator popAfterByName = head, next = popAfterByName->getNextBySurname();
        while (next != tail) {
            if (name.compare(next->getSurname()) == 0)
                break;
            popAfterByName = next;
	    next = next->getNextBySurname();
        }
        if (next == tail) return 1; // node not found

        // find node in number stream
        Iterator popAfterByNumber = head;
	next = popAfterByNumber->getNextByNumber();
        while (next != tail) {
            if (next == popAfterByName->getNextBySurname())
                break;
            popAfterByNumber = next;
	    next = next->getNextByNumber();
        }

        pop(popAfterByName, popAfterByNumber);

        return 0;
    }

    short int pop(const unsigned int &num) {
        if (isEmpty()) return -1;

        // find node to pop
        Iterator popAfterByNum = head, next = popAfterByNum->getNextByNumber();
        while (next != tail) {
            if (next->getNumber() == num)
                break;
            popAfterByNum = next;
	    next = next->getNextByNumber();
        }
        if (next == tail) return 1; // node not found

        // find node in surname stream
        Iterator popAfterByName = head;
	next = popAfterByName->getNextBySurname();
        while (next != tail) {
            if (next == popAfterByNum->getNextByNumber())
                break;
            popAfterByName = next;
	    next = next->getNextBySurname();
        }

        pop(popAfterByName, popAfterByNum);

        return 0;
    }

    string getSurname(const unsigned int &num) const {
        if (isEmpty())
            return "*empty*";

        Iterator current = head->getNextByNumber();
        while (current != tail) {
            if (current->getNumber() == num)
                break;
            current = current->getNextByNumber();
        }
        if (current == tail)
            return "not found";
        return current->getSurname();
    }

    unsigned int getNumber(const string &name) const {
        if (isEmpty())
            return UINT32_MAX - 1;

        Iterator current = head->getNextBySurname();
        while (current != tail) {
            // string::compare returns non-zero if strings are not equal
            if (name.compare(current->getSurname()) == 0)
                break;
            current = current->getNextBySurname();
        }
        if (current == tail)
            return UINT32_MAX;
        return current->getNumber();
    }

    void push(const string &name, const unsigned int &num) {
        Node *newNode = new Node(name, num);
        if (isEmpty()) {
            head = new Node(*newNode);
	    tail = new Node(*newNode);
            head->setNextBySurname(newNode);
            head->setNextByNumber(newNode);
            newNode->setNextBySurname(tail);
            newNode->setNextByNumber(tail);
        } else {
            // first connect by surname
            Iterator current = head, next = current->getNextBySurname();
            while (next != tail) {
                // if name < current node's name
                if (name.compare(next->getSurname()) <= 0)
                    break;
                current = next;
                next = next->getNextBySurname();
            }
            // if several nodes have same surname then skip the lower numbers
            // string::compare returns 0 if strings are equal
            while (name.compare(next->getSurname()) == 0) {
		    current = next;
		    next = next->getNextBySurname();
            }
            pushByName(newNode, current);

            // then connect by number
            current = head;
            next = current->getNextByNumber();
            while (next != tail) {
                if (next->getNumber() >= num)
                    break;
                current = next;
                next = next->getNextByNumber();
            }
            // assume that every number in list is unique
            pushByNumber(newNode, current);
        }
    }

    void clear() {
        while (!isEmpty()) {
            pop(head->getNextBySurname()->getSurname());
        }
    }
};
