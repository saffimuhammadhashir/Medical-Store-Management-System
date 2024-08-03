#pragma once
#include "medicine.h"







template <typename T>
class AVLNode {
public:
	long long key;
	T data;
	AVLNode* left;
	AVLNode* right;
	int height;

	AVLNode(long long key, T data)
		: key(key), data(data), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
private:
	AVLNode<T>* root;


	int height(AVLNode<T>* node) {
		return node ? node->height : 0;
	}

	int getBalance(AVLNode<T>* node) {
		return node ? height(node->left) - height(node->right) : 0;
	}

	AVLNode<T>* rightRotate(AVLNode<T>* y) {
		AVLNode<T>* x = y->left;
		AVLNode<T>* T2 = x->right;



		x->right = y;
		y->left = T2;


		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;


		return x;
	}

	AVLNode<T>* leftRotate(AVLNode<T>* x) {
		AVLNode<T>* y = x->right;
		AVLNode<T>* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		return y;
	}

	AVLNode<T>* insertNode(AVLNode<T>* node, long long key, T data) {

		if (!node)
			return new AVLNode<T>(key, data);

		if (key < node->key)
			node->left = insertNode(node->left, key, data);
		else if (key > node->key)
			node->right = insertNode(node->right, key, data);
		else
			return node;

		node->height = 1 + max(height(node->left), height(node->right));

		int balance = getBalance(node);



		if (balance > 1 && key < node->left->key)
			return rightRotate(node);

		if (balance < -1 && key > node->right->key)
			return leftRotate(node);


		if (balance > 1 && key > node->left->key) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}


		if (balance < -1 && key < node->right->key) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}


		return node;
	}

	void inorder(AVLNode<T>* root) {
		if (root != nullptr) {
			inorder(root->left);
			root->data.display();
			inorder(root->right);
		}
	}
	void inorderdisplay(AVLNode<T>* root) {
		if (root != nullptr) {
			inorderdisplay(root->left);
			cout << root->data.name << endl;;
			inorderdisplay(root->right);
		}
	}

	AVLNode<T>* helpersearch(long long id, AVLNode<T>* curr) {
		if (curr == nullptr) {
			return nullptr;
		}
		if (curr->key == id) {
			return curr;
		}
		if (curr->key > id) {
			return helpersearch(id, curr->left);
		}
		if (curr->key < id) {
			return helpersearch(id, curr->right);
		}
	}

	void inordermatch(AVLNode<T>* curr, string str) {
		if (curr == nullptr) {
			return;
		}
		inordermatch(curr->left, str);
		if (str == curr->data.name) {
			curr->data.display();
		}
		inordermatch(curr->right, str);
	}

	Medicine* inordermatch_search(AVLNode<T>* curr, string str) {
		if (curr == nullptr) {
			return nullptr;
		}
		Medicine* cur = nullptr;
		cur = inordermatch_search(curr->left, str);
		if (cur == nullptr) {
			cur = curr->data.searchmedicine(str);
			if (cur == nullptr) {
				cur = inordermatch_search(curr->right, str);

			}
		}
		return cur;
	}


	void inordercategrytraversal(AVLNode<T>* curr) {
		if (curr == nullptr) {
			return ;
		}

		inordercategrytraversal(curr->left);

		curr->data.medicines.savemeds();

		inordercategrytraversal(curr->right);


	}
	void savemedstraversal(AVLNode<T>* curr) {
		if (curr == nullptr) {
			return ;
		}

		savemedstraversal(curr->left);

		curr->data.truncToMedicineFile();
		
		savemedstraversal(curr->right);
	}


public:
	AVLTree() : root(nullptr) {}
	void savemeds() {
		savemedstraversal(root);
	}

	void displaytitles() {
		cout << "All Categories:" << endl;
		inorderdisplay(root);
		cout << endl;
	}
	void insert(T data) {
		long long key = hashing(data.name);
		root = insertNode(root, key, data);
	}
	AVLNode<T>* search(long long id) {
		if (root == nullptr) {
			return root;
		}
		else {
			AVLNode<T>* curr = helpersearch(id, root);

			return curr;
		}
	}

	void traversecat() {
		inordercategrytraversal(root);
	}


	void printmatch(string str) {
		inordermatch(root, str);
		cout << endl;
	}
	AVLNode<T>* returnmatch(string str) {
		return inordermatchreturn(root, str);
		cout << endl;
	}
	Medicine* printtitle(string str) {
		return inordermatch_search(root, str);
	}

	void display() {
		inorder(root);
		cout << endl;
	}
};



