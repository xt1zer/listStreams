#pragma once
#include <string>
using std::string;

struct Node {
private:
	string surname;
	unsigned int number;
	Node *nextSurname;
	Node *prevSurname;
	Node *nextNumber;
	Node *prevNumber;

public:
	Node(string l, unsigned int r) : surname(l), number(r),
		nextSurname(nullptr), nextNumber(nullptr),
		prevSurname(nullptr), prevNumber(nullptr) {}

	string getSurname() { return surname; }
	unsigned int getNumber() { return number; }
	Node *getNextBySurname() { return nextSurname; }
	Node *getPrevBySurname() { return prevSurname; }
	Node *getNextByNumber() { return nextNumber; }
	Node *getPrevByNumber() { return prevNumber; }

	void setNextBySurname(Node *node) { nextSurname = node; }
	void setPrevBySurname(Node *node) { prevSurname = node; }
	void setNextByNumber(Node *node) { nextNumber = node; }
	void setPrevByNumber(Node *node) { prevNumber = node; }
};

class ListStreams {
public:
	typedef Node *Iterator;
private:
	Node *headName = nullptr;    // lowest surname string value
	Node *tailName = nullptr;    // highest surname string value
	Node *headNum = nullptr;     // lowest number value
	Node *tailNum = nullptr;     // highest number value

	void pop(Node *node) {
		// list has one node
		if (node == headName && node == tailName) {
			delete node;
			headName = tailName = headNum = tailNum = nullptr;
			return;
		}
		// node is either head or tail
		else {
			if (node == headName) {
				headName = node->getNextBySurname();
				headName->setPrevBySurname(nullptr);
			}
			if (node == headNum) {
				headNum = node->getNextByNumber();
				headNum->setPrevByNumber(nullptr);
			}
			if (node == tailName) {
				tailName = node->getPrevBySurname();
				tailName->setNextBySurname(nullptr);
			}
			if (node == tailNum) {
				tailNum = node->getPrevByNumber();
				tailNum->setNextByNumber(nullptr);
			}
			delete node;
			return;
		}
		// node is in-between
		node->getPrevBySurname()->setNextBySurname(node->getNextBySurname());
		node->getNextBySurname()->setPrevBySurname(node->getPrevBySurname());
		node->getPrevByNumber()->setNextByNumber(node->getNextByNumber());
		node->getNextByNumber()->setPrevByNumber(node->getPrevByNumber());
		delete node;
	}

	// newNode is pushed before pushBefore
	void pushByName(Node *newNode, Iterator pushBefore) {
		// if newNode has largest surname value then push to tail
		if (!pushBefore) {
			tailName->setNextBySurname(newNode);
			newNode->setPrevBySurname(tailName);
			tailName = newNode;
		}
		else {
			newNode->setPrevBySurname(pushBefore->getPrevBySurname());
			newNode->setNextBySurname(pushBefore);
			if (pushBefore != headName)
				pushBefore->getPrevBySurname()->setNextBySurname(newNode);
			pushBefore->setPrevBySurname(newNode);
			if (pushBefore == headName)
				headName = newNode;
		}
	}

	void pushByNumber(Node *newNode, Iterator pushBefore) {
		// same for number value
		if (!pushBefore) {
			tailNum->setNextByNumber(newNode);
			newNode->setPrevByNumber(tailNum);
			tailNum = newNode;
		}
		else {
			newNode->setPrevByNumber(pushBefore->getPrevByNumber());
			newNode->setNextByNumber(pushBefore);
			if (pushBefore != headNum)
				pushBefore->getPrevByNumber()->setNextByNumber(newNode);
			pushBefore->setPrevByNumber(newNode);
			if (pushBefore == headNum)
				headNum = newNode;
		}
	}

public:
	Iterator getHeadName() { return headName; }
	Iterator getHeadNum() { return headNum; }

	bool isEmpty() const { return !headName || !tailName || !headNum || !tailNum; }

	short int pop(const string &name) {
		if (isEmpty()) return -1;

		Iterator current = headName;
		while (current) {
			if (name.compare(current->getSurname()) == 0)
				break;
			current = current->getNextBySurname();
		}
		if (!current) return 1;		// node not found
		pop(current);

		return 0;
	}

	short int pop(const unsigned int &num) {
		if (isEmpty()) return -1;

		Iterator current = headNum;
		while (current) {
			if (current->getNumber() == num)
				break;
			current = current->getNextByNumber();
		}
		if (!current) return 1;		// node not found
		pop(current);

		return 0;
	}

	string getSurname(const unsigned int &num) const {
		if (isEmpty())
			return "*empty*";
		Iterator current = headNum;
		while (current) {
			if (current->getNumber() == num)
				break;
			current = current->getNextByNumber();
		}
		if (!current)
			return "not found";
		return current->getSurname();
	}

	unsigned int getNumber(const string &name) const {
		if (isEmpty())
			return UINT_MAX - 1;
		Iterator current = headName;
		while (current) {
			// string::compare returns non-zero if strings are not equal
			if (name.compare(current->getSurname()) == 0)
				break;
			current = current->getNextBySurname();
		}
		if (!current)
			return UINT_MAX;
		return current->getNumber();
	}

	void push(const string &name, const unsigned int &num) {
		Node *newNode = new Node(name, num);
		if (isEmpty())
			headName = tailName = headNum = tailNum = newNode;
		else {
			// first connect by surname
			Iterator current = headName;
			while (current) {
				// if name <= current name
				if (name.compare(current->getSurname()) != 1)
					break;
				current = current->getNextBySurname();
			}
			// if several nodes have same surname then skip the lower numbers
			// string::compare returns 0 if strings are equal
			while (name.compare(current->getSurname()) == 0 && current->getNumber() < num
				&& !current->getNextBySurname())
				current = current->getNextBySurname();
			pushByName(newNode, current);

			// then connect by number
			current = headNum;
			while (current) {
				if (current->getNumber() >= num)
					break;
				current = current->getNextByNumber();
			}
			// assume that every number in list is unique
			pushByNumber(newNode, current);
		}
	}

	void clear() {
		while (!isEmpty()) {
			pop(headName);
		}
	}
};
