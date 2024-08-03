#pragma once
#include "AllHeaders.h"
#include "Stack.h"

class transaction {
public:
	long long id;
	string customername, medicine, category, custommanager;
	int totalbill;
	bool Billpaid;
	transaction() {}
	transaction(string customername, string medicine, string category, string custommanager, int totalbill, bool billpaid, bool chk = true)
		: customername(customername), medicine(medicine), category(category), custommanager(custommanager), totalbill(totalbill), Billpaid(billpaid) {
		id = hashing(customername);
		if (chk) {
			saveToFile();
		}
	}


	void display() {
		cout << "------------------------------" << endl;
		cout << "Medicine: " << medicine << endl;
		cout << "Category: " << category << endl;
		cout << "Customer Manager: " << custommanager << endl;
		cout << "Total Bill: " << totalbill << endl;
		cout << "Bill status: " << ((Billpaid) ? "Paid" : "Nil") << endl << endl << endl;
	}
	void saveToFile() {
		ofstream file("transactions.txt", ios::app);
		if (file.is_open()) {
			file << customername << "," << medicine << "," << category << ","
				<< custommanager << "," << totalbill << "," << Billpaid << endl;
			file.close();
		}
		else {
			cout << "Unable to open file for writing." << endl;
		}
	}


};

class Request {
public:
	long long id;
	string customerusername;
	Stack<transaction> history;
	Request() {}
	Request(string customerusername) : customerusername(customerusername) {
		id = hashing(customerusername);
	}
	void insertinhistory(transaction* t) {
		t->customername = customerusername;
		t->id = hashing(customerusername);
		history.push(*t);

	}
	void display() {
		cout << customerusername << endl;
		if (history.empty()) {
			return;
		}
		Stack<transaction> historytemp;
		while (!history.empty())
		{
			transaction temp = history.top();
			temp.display();
			historytemp.push(temp);
			history.pop();
		}
		while (!historytemp.empty())
		{
			transaction temp = historytemp.top();
			history.push(temp);
			historytemp.pop();
		}
	}

	void displaymanager(string str) {

		if (history.empty()) {
			return;
		}
		Stack<transaction> historytemp;
		while (!history.empty())
		{
			transaction temp = history.top();
			if (temp.custommanager == str) {

			temp.display();
			}
			historytemp.push(temp);
			history.pop();
		}
		while (!historytemp.empty())
		{
			transaction temp = historytemp.top();
			history.push(temp);
			historytemp.pop();
		}
	}
	bool operator<(const Request& other) const {
		return id < other.id;
	}

	bool operator>(const Request& other) const {
		return id > other.id;
	}

	bool operator==(const Request& other) const {
		return id == other.id;
	}
};


template <typename T>
class RequestNode {
public:
	T data;
	RequestNode* left;
	RequestNode* right;
	int height;
	RequestNode(const T& value)
		: data(value), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class RequestTree {
public:
	RequestTree() : root(nullptr) {}
	~RequestTree() { destroy(root); }

	void insert(const T& data) {
		root = insert(root, data);
	}

	void remove(const T& data) {
		root = remove(root, data);
	}

	void display() const {
		display(root);
		std::cout << std::endl;
	}

	RequestNode<T>* search(const T& data) const {
		return search(root, data);
	}
	void printdetailsCustomer(string customer) {
		displaycustomer(root, customer);
	}
	void printdetailsCounterManager(string customer) {
		displaycountermanager(root, customer);
	}
	RequestNode<T>* requestholder(string name) {
		return searchHolder(root, name);
	}
private:
	RequestNode<T>* root;

	int height(RequestNode<T>* node) const {
		return node ? node->height : 0;
	}

	int balanceFactor(RequestNode<T>* node) const {
		return node ? height(node->left) - height(node->right) : 0;
	}

	RequestNode<T>* rightRotate(RequestNode<T>* y) {
		RequestNode<T>* x = y->left;
		RequestNode<T>* T2 = x->right;
		x->right = y;
		y->left = T2;
		y->height = std::max(height(y->left), height(y->right)) + 1;
		x->height = std::max(height(x->left), height(x->right)) + 1;
		return x;
	}

	RequestNode<T>* leftRotate(RequestNode<T>* x) {
		RequestNode<T>* y = x->right;
		RequestNode<T>* T2 = y->left;
		y->left = x;
		x->right = T2;
		x->height = std::max(height(x->left), height(x->right)) + 1;
		y->height = std::max(height(y->left), height(y->right)) + 1;
		return y;
	}

	RequestNode<T>* insert(RequestNode<T>* node, const T& data) {
		if (!node) return new RequestNode<T>(data);

		if (data < node->data) {
			node->left = insert(node->left, data);
		}
		else if (data > node->data) {
			node->right = insert(node->right, data);
		}
		else {
			return node;
		}

		node->height = std::max(height(node->left), height(node->right)) + 1;

		int balance = balanceFactor(node);

		if (balance > 1 && data < node->left->data)
			return rightRotate(node);

		if (balance < -1 && data > node->right->data)
			return leftRotate(node);

		if (balance > 1 && data > node->left->data) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		if (balance < -1 && data < node->right->data) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

	RequestNode<T>* minValueNode(RequestNode<T>* node) {
		RequestNode<T>* current = node;
		while (current->left) {
			current = current->left;
		}
		return current;
	}

	RequestNode<T>* remove(RequestNode<T>* root, const T& data) {
		if (!root) return root;

		if (data < root->data) {
			root->left = remove(root->left, data);
		}
		else if (data > root->data) {
			root->right = remove(root->right, data);
		}
		else {
			if (!root->left || !root->right) {
				RequestNode<T>* temp = root->left ? root->left : root->right;
				if (!temp) {
					temp = root;
					root = nullptr;
				}
				else {
					*root = *temp;
				}
				delete temp;
			}
			else {
				RequestNode<T>* temp = minValueNode(root->right);
				root->data = temp->data;
				root->right = remove(root->right, temp->data);
			}
		}

		if (!root) return root;

		root->height = std::max(height(root->left), height(root->right)) + 1;

		int balance = balanceFactor(root);

		if (balance > 1 && balanceFactor(root->left) >= 0)
			return rightRotate(root);

		if (balance > 1 && balanceFactor(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		if (balance < -1 && balanceFactor(root->right) <= 0)
			return leftRotate(root);

		if (balance < -1 && balanceFactor(root->right) > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}

	void display(RequestNode<T>* node) const {
		if (node != nullptr) {
			display(node->left);
			cout << node->data.customerusername << endl;
			node->data.display();
			display(node->right);
		}
	}

	void displaycustomer(RequestNode<T>* node, string customer) const {
		if (node) {
			displaycustomer(node->left, customer);

			if (customer == node->data.customerusername) {

				node->data.display();
			}
			displaycustomer(node->right, customer);
		}
	}
	void displaycountermanager(RequestNode<T>* node, string manager) const {
		if (node) {
			displaycountermanager(node->left, manager);

				node->data.displaymanager(manager);
			
			displaycountermanager(node->right, manager);
		}
	}
	RequestNode<T>* searchHolderHelper(RequestNode<T>* node, const std::string& holder) {
		if (node == nullptr) {
			return nullptr;
		}

		RequestNode<T>* leftResult = searchHolderHelper(node->left, holder);
		if (leftResult != nullptr) {
			return leftResult;
		}

		if (holder == node->data.customerusername && hashing(holder) == node->data.id) {
			return node;
		}

		return searchHolderHelper(node->right, holder);
	}


	RequestNode<T>* searchHolder(RequestNode<T>* node,  std::string& holder) {
		return searchHolderHelper(node, holder);
	}

	RequestNode<T>* search(RequestNode<T>* node, const T& data) const {
		if (!node || node->data == data) {
			return node;
		}
		if (data < node->data) {
			return search(node->left, data);
		}
		return search(node->right, data);
	}

	void destroy(RequestNode<T>* node) {
		if (node) {
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}


};

RequestTree<Request> requestlist;
