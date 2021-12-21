#include <iostream>
#include <fstream>
#include "windows.h"
using namespace std;

class PerformanceCalculator {
	LARGE_INTEGER startCounter;
	LARGE_INTEGER stopCounter;
	LARGE_INTEGER frequency;
public:
	PerformanceCalculator() {
		startCounter.QuadPart = stopCounter.QuadPart = 0;
		QueryPerformanceFrequency(&frequency);
	}
	void start() {
		QueryPerformanceCounter(&startCounter);
	}
	void stop() {
		QueryPerformanceCounter(&stopCounter);
	}
	double elapsedMillis() const {
		return (stopCounter.QuadPart - startCounter.QuadPart)*1000. / frequency.QuadPart;
	}
};

class BSTree;

class TreeNode{
private:
	int key;
	TreeNode* left;
	TreeNode* right;
public:
	TreeNode(int k) : key(k), left(nullptr), right(nullptr){}
	friend class BSTree;
	~TreeNode(){
		left = nullptr;
		right = nullptr;
	}
	TreeNode* getRight();
	TreeNode* getLeft();
	void setLeft(TreeNode*);
	void setRight(TreeNode*);
	friend class MyStack;
	int getKey();
};

class BSTree{
private:
	TreeNode* root;
	int numOfNodes;
	void copyTree(const BSTree&);
public:
	BSTree() : numOfNodes(0), root(nullptr){}
	BSTree(const BSTree&);
	BSTree& operator= (const BSTree&);
	BSTree& operator+= (const int&);
	TreeNode* getRoot();
	int sizeOfTree();
	void insertNode(int, bool);
	bool findNode(int);
	friend ostream& operator<<(ostream&, const BSTree&);
	friend void printTree(TreeNode*);
	friend BSTree* unionOf2trees(int);
	void destroyTree();
	void deleteNode(int, bool);
	void delSpecRangeT(int, int);
	~BSTree();
};

class List{
private:
	struct Elem{
		int num;
		Elem* next;
		Elem(int n, Elem* p = nullptr) : num(n), next(p){}
	};
	Elem* first, *last;
	int numOfElem;
	void copyList(const List&);
public:
	List() : numOfElem(0), first(nullptr), last(nullptr){}
	~List();
	int size();
	void delSpecRange(int, int);
	List& operator=(const List&);
	List& operator+=(const int&);
	friend List* createList(int*);
	bool findElem(int);
	void deleteElem(int, bool);
	void destroy();
	friend List* unionOf2lst(int);
	Elem* getFirst();
	friend ostream& operator<<(ostream&, const List&);
	void insertElem(int, bool);
	friend void test();
	friend void ftest(int);
};

class MyStack{
private:
	struct Elem{
		TreeNode* num;
		Elem* next;
		Elem(TreeNode* n, Elem* p = nullptr){
			num = n;
			next = p;
		}
	};
	Elem* first;
public:
	MyStack() : first(nullptr){}
	void pushElem(TreeNode*);
	TreeNode* popElem();
	bool stackEmpty();
	~MyStack();
};

#include <string>
void f();
void fd(std::ifstream&);

int main(){

	//test();

	cout << "Do you want to use a file or with a standard input? [f(file)/i(input)] "<<endl;
	char dec;
	cin >> dec;
	if (dec != 'f' && dec != 'F' && dec != 'i' && dec != 'I')
		exit(9);
	int s = 0;
	if (dec == 'f' || dec == 'F'){
		s = 5;
		ifstream dat;
		string inFile;
		cout << "Enter the filename." << endl;
		cin >> inFile; 
		dat.open(inFile);
		if (!dat.is_open()) {
			cout << "The file doesn't exist." << endl;
			exit(4);
		}
		fd(dat);
		dat.close();
	}

	if(!s) f();

	return 0;
} 

//#define _FTREE_
#ifdef _FTREE_
void f(){

	int num = 0;
	BSTree* structure = nullptr;

	while (1){

		cout << "1. Create empty set\n"
			"2. Destroy the set\n"
			"3. Find an element (determine affiliation)\n"
			"4. Insert an element\n"
			"5. Delete an element from the set\n"
			"6. Delete the elements of the set in the specified range\n"
			"7. Number of elements in the set\n"
			"8. Print a set\n"
			"9. Union of 2 sets\n"
			"10. Exit\n"
			"What is your choice?\n";

		int choice;
		cin >> choice;

		switch (choice){
		case 1: 
			if (structure != nullptr)
				cout << "The set already exists." << endl;
			else
				structure = new BSTree();
			break;
		case 2: 
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else
				structure->destroyTree(), structure = nullptr;
			break;
		case 3: 
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else{
				cout << "What number do you want to find?" << endl;
				cin >> num;
				if (structure->findNode(num))
					cout << "The number " << num << " exists in the set." << endl;
				else
					cout << "The number " << num << " doesn't exist in the set." << endl;
			}
			break;
		case 4:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else{
				cout << "What number do you want to insert?" << endl;
				cin >> num;
				structure->insertNode(num, true);
			}
			break;
		case 5:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else{
				cout << "What number do you want to delete?" << endl;
				cin >> num;
				structure->deleteNode(num, true);
			}
			break;
		case 6:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else{
				cout << "Which are the left and right boundaries, respectively?" << endl;
				int lB, rB;
				cin >> lB >> rB;
				if (rB < lB)
					cout << "You didn't enter the range correctly." << endl;
				else
					structure->delSpecRangeT(lB, rB);
			}
			break;
		case 7:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else
				cout << structure->sizeOfTree() << endl;
			break;
		case 8:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else
				cout << (*structure);
			break;
		case 9:
			if (structure != nullptr){
				cout << "Some set already exists, do you want to destroy it?[y(YES), n(NO)]" << endl;
				char ans; cin >> ans;
				if ((ans == 'n') || (ans == 'N')) break;
				else structure->destroyTree(), structure = nullptr;
			}
			structure = unionOf2trees(0);
			break;
		case 10: exit(10);
		}
	}

}

//dat

void fd(std::ifstream& dat){

	int num = 0;
	int choice;
	BSTree* structure = nullptr;

	while (!dat.eof()){

		dat >> choice;

		switch (choice){
		case 1: 
			if (structure != nullptr)
				cout << "The set already exists." << endl;
			else
				structure = new BSTree();
			break;
		case 2: 
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else
				structure->destroyTree(), structure = nullptr;
			break;
		case 3: 
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else{
				dat >> num;
				if (structure->findNode(num))
					cout << "The number " << num << " exists in the set." << endl;
				else
					cout << "The number " << num << " doesn't exist in the set." << endl;
			}
			break;
		case 4:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else{
				dat >> num;
				structure->insertNode(num, true);
			}
			break;
		case 5:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else{
				dat >> num;
				structure->deleteNode(num, true);
			}
			break;
		case 6:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else{
				int lB, rB;
				dat >> lB >> rB;
				if (rB < lB)
					cout << "You didn't enter the range correctly." << endl;
				else
					structure->delSpecRangeT(lB, rB);
			}
			break;
		case 7:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else
				cout << structure->sizeOfTree() << endl;
			break;
		case 8:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getRoot() == nullptr)
				cout << "The set is empty." << endl;
			else
				cout << (*structure);
			break;
		case 9:
			if (structure != nullptr)
				structure->destroyTree(), structure = nullptr;
			structure = unionOf2trees(0);
			break;
		case 10: exit(10);
		}
	}

}

#endif _FTREE_


void sortArr(int* sArr, int n){

	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j<n; j++){
			if (sArr[i]>sArr[j]) {
				int h = sArr[i];
				sArr[i] = sArr[j];
				sArr[j] = h;
			}
		}
	}
}

#ifndef _FTREE_
void f(){

	int num;
	List* structure = nullptr;

	while (1){
		cout << "1. Create empty set\n"
			"2. Destroy the set\n"
			"3. Find an element (determine affiliation)\n"
			"4. Insert an element\n"
			"5. Delete an element from the set\n"
			"6. Delete the elements of the set in the specified range\n"
			"7. Number of elements in the set\n"
			"8. Print a set\n"
			"9. Union of 2 sets\n"
			"10. Exit\n"
			"What is your choice?\n";

		int choice;
		cin >> choice;

		switch (choice){
		case 1: 
			if (structure != nullptr)
				cout << "The set already exists." << endl;
			else
				structure = new List();
			break;
		case 2: 
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else
				structure->destroy(), structure = nullptr;
			break;
		case 3: 
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getFirst() == nullptr)
				cout << "The set is empty." << endl;
			else{
				cout << "What number do you want to find?" << endl;
				cin >> num;
				if (structure->findElem(num))
					cout << "The number " << num << " exists in the set." << endl;
				else
					cout << "The number " << num << " doesn't exist in the set." << endl;
			}
			break;
		case 4:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else{
				cout << "What number do you want to insert?" << endl;
				cin >> num;
				structure->insertElem(num, true);
			}
			break;
		case 5:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getFirst() == nullptr)
				cout << "The set is empty." << endl;
			else{
				cout << "What number do you want to delete?" << endl;
				cin >> num;
				structure->deleteElem(num, true);
			}
			break;
		case 6:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getFirst() == nullptr)
				cout << "The set is empty." << endl;
			else{
				cout << "Which are the left and right boundaries, respectively?" << endl;
				int lB, rB;
				cin >> lB >> rB;
				if (rB < lB)
					cout << "You didn't enter the range correctly." << endl;
				else
				structure->delSpecRange(lB, rB);
			}
			break;
		case 7:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getFirst() == nullptr)
				cout << "The set is empty." << endl;
			else
				cout << structure->size() << endl;
			break;
		case 8:
			if (structure == nullptr)
				cout << "The set doesn't exist." << endl;
			else if (structure->getFirst() == nullptr)
				cout << "The set is empty." << endl;
			else
				cout << (*structure);
			break;
		case 9:
			if (structure != nullptr){
				cout << "Some set already exists, do you want to destroy it?[y(YES), n(NO)]" << endl;
				char ans; cin >> ans;
				if ((ans == 'n') || (ans == 'N')) break;
				else structure->destroy(), structure = nullptr;
			}
			structure = unionOf2lst(0);
			break;
		case 10: exit(8); break;
		default: cout << "Try again." << endl;
		}
	}

}

//dat

void fd(std::ifstream& dat){

	int num;
	List* structure = nullptr;
	int choice;
	dat >> choice;

	switch (choice){
	case 1:
		if (structure != nullptr)
			cout << "The set already exists." << endl;
		else
			structure = new List();
		break;
	case 2:
		if (structure == nullptr)
			cout << "The set doesn't exist." << endl;
		else
			structure->destroy(), structure = nullptr;
		break;
	case 3:
		if (structure == nullptr)
			cout << "The set doesn't exist." << endl;
		else if (structure->getFirst() == nullptr)
			cout << "The set is empty." << endl;
		else{
			dat >> num;
			if (structure->findElem(num))
				cout << "The number " << num << " exists in the set." << endl;
			else
				cout << "The number " << num << " doesn't exist in the set." << endl;
		}
		break;
	case 4:
		if (structure == nullptr)
			cout << "The set doesn't exist." << endl;
		else{
			dat >> num;
			structure->insertElem(num, true);
		}
		break;
	case 5:
		if (structure == nullptr)
			cout << "The set doesn't exist." << endl;
		else if (structure->getFirst() == nullptr)
			cout << "The set is empty." << endl;
		else{
			dat >> num;
			structure->deleteElem(num, true);
		}
		break;
	case 6:
		if (structure == nullptr)
			cout << "The set doesn't exist." << endl;
		else if (structure->getFirst() == nullptr)
			cout << "The set is empty." << endl;
		else{
			int lB, rB;
			dat >> lB >> rB;
			if (rB < lB)
				cout << "You didn't enter the range correctly." << endl;
			else
				structure->delSpecRange(lB, rB);
		}
		break;
	case 7:
		if (structure == nullptr)
			cout << "The set doesn't exist." << endl;
		else if (structure->getFirst() == nullptr)
			cout << "The set is empty." << endl;
		else
			cout << structure->size() << endl;
		break;
	case 8:
		if (structure == nullptr)
			cout << "The set doesn't exist." << endl;
		else if (structure->getFirst() == nullptr)
			cout << "The set is empty." << endl;
		else
			cout << (*structure);
		break;
	case 9:
		if (structure != nullptr) 
			cout << "The set doesn't exist." << endl;
		else structure->destroy(), structure = nullptr;
		structure = unionOf2lst(0);
		break;
	case 10: exit(8);
	}
}


#endif _FTREE_


//tree

void unsortArr(int* sArr, int n, int first){

	for (int i = 0; i < n / 2; i += 2){
		int h = sArr[i];
		sArr[i] = sArr[n - 1 - i];
		sArr[n - 1 - i] = h;

		if (!(i % 3)){
			h = sArr[i + 1];
			sArr[i + 1] = sArr[n - 2 - i];
			sArr[n - 2 - i] = h;

			h = sArr[i - 1];
			sArr[i - 1] = sArr[n - i];
			sArr[n - i] = h;
		}
	}
	
	int i;
	for (i = 0; i < n; i++)
	if (sArr[i] == first) break;
	sArr[i] = sArr[0];
	sArr[0] = first;
	
}

int* arrUnion(int* arr1, int &n1, int* arr2, int n2){

	int k = 0, i = 0, j = 0;
	int* newArr = new int[n1 + n2];

	while (i < n1 && j < n2) {
		if (arr1[i] < arr2[j]){
			newArr[k] = arr1[i];
			i++, k++;
		}
		else if (arr1[i] > arr2[j]){
			newArr[k] = arr2[j];
			j++, k++;
		}
		else if (arr1[i] == arr2[j]){
			newArr[k] = arr1[i];
			i++, j++, k++;
		}
	}
	while (i < n1){
		newArr[k] = arr1[i];
		i++, k++;
	}
	while (j < n2){
		newArr[k] = arr2[j];
		j++, k++;
	}

	int* newArr2 = nullptr;
	if (k < (n1 + n2)){
		newArr2 = new int[k];
		for (int iter = 0; iter < k; iter++)
			newArr2[iter] = newArr[iter];
		delete newArr;
		newArr = nullptr;
	}

	n1 = k;

	if (newArr2 != nullptr)
		return newArr2;
	else return newArr;
}

BSTree* unionOf2trees(int nTest){

	int* arr1 = nullptr;
	int* arr2 = nullptr;
	int newNum, n = 0, n2 = 0;

	if (nTest){
		int s = -4;
		arr1 = new int[nTest];
		for (int i = 0; i < nTest; i++)
			arr1[i] = rand() % 100 + s;
		s = 9;
		arr2 = new int[nTest];
		for (int i = 0; i < nTest; i++)
			arr2[i] = rand() % 100 + s;
	}
	else{
		cout << "How many elements will have the first set?" << endl;
		cin >> n;
		if (n <= 0) cout << "Incorrect number." << endl, exit(1);
		arr1 = new int[n];
		cout << "Enter the first set." << endl;
		for (int iter = 0; iter < n; iter++){
			cin >> newNum;
			arr1[iter] = newNum;
		}

		cout << "How many elements will have the second set?" << endl;
		cin >> n2;
		if (n2 <= 0) cout << "Incorrect number." << endl, exit(1);
		arr2 = new int[n2];
		cout << "Enter the second set." << endl;
		for (int iter = 0; iter < n2; iter++){
			cin >> newNum;
			arr2[iter] = newNum;
		}
	}
	sortArr(arr1, n);
	sortArr(arr2, n2);

	int* newArr = arrUnion(arr1, n, arr2, n2);
	unsortArr(newArr, n, newArr[n / 2]);
	delete arr1;
	delete arr2;

	BSTree* unionBst = new BSTree();
	n2 = 0;
	while (n2 < n)
		unionBst->insertNode(newArr[n2++], false);

	delete newArr;

	return unionBst;
}

void BSTree::delSpecRangeT(int lBound, int rBound){

	MyStack* nodeStack = new MyStack;
	nodeStack->pushElem(root);

	while (!nodeStack->stackEmpty()){
		TreeNode* hNode = nodeStack->popElem();
		if (hNode->getKey() < lBound){
			if (hNode->right)
				nodeStack->pushElem(hNode->right);
		}
		else if (hNode->getKey() > rBound){
			if (hNode->left)
				nodeStack->pushElem(hNode->left);
		}
		else if ((hNode->getKey() >= lBound) || (hNode->getKey() <= rBound)){
			if (hNode->left)
				nodeStack->pushElem(hNode->left);
			if (hNode->right)
				nodeStack->pushElem(hNode->right);
			deleteNode(hNode->key, false);
		}
	}

	delete nodeStack;
}

void BSTree::deleteNode(int num, bool mess){

	TreeNode* node1 = root;
	TreeNode* node2 = nullptr;
	TreeNode* rNode = nullptr, *f = nullptr, *s = nullptr;

	while (node1 && (num != node1->key)){
		node2 = node1;
		if (num < node1->key)
			node1 = node1->left;
		else
			node1 = node1->right;
	}

	if (!node1){
		if (mess)
			cout << "The number does not belong to the set." << endl;
		return;
	}
	if (!node1->left)
		rNode = node1->right;
	else if (!node1->right)
		rNode = node1->left;
	else{
		f = node1;
		rNode = node1->right;
		s = rNode->left;
		while (s){
			f = rNode;
			rNode = s;
			s = rNode->left;
		}
		if (f != node1){
			f->left = rNode->right;
			rNode->right = node1->right;
		}
		rNode->left = node1->left;
	}

	if (!node2)
		root = rNode;
	else if (node1 == node2->left)
		node2->left = rNode;
	else
		node2->right = rNode;

	--numOfNodes;
	delete node1;
	node1 = f = s = node2 = nullptr;
}

void BSTree::insertNode(int num, bool mess){

	TreeNode* node = root;
	TreeNode* hNode = nullptr;
	while (node){
		hNode = node;
		if (num == node->key){
			if (mess)
				cout << "The number " << num << " already exists in the set." << endl;
			return;
		}
		else if (num < node->key)
			node = node->left;
		else
			node = node->right;
	}
	if (!hNode)
		root = new TreeNode(num);
	else if (num < hNode->key)
		hNode->left = new TreeNode(num);
	else
		hNode->right = new TreeNode(num);

	++numOfNodes;
}

bool BSTree::findNode(int num){
	TreeNode* hNode = root;
	while (hNode && (hNode->key != num)) {
		if (num < hNode->key)
			hNode = hNode->left;
		else
			hNode = hNode->right;
	}
	if (hNode && (hNode->key == num))
		return true;
	else return false;
}

BSTree& BSTree::operator += (const int& n){
	insertNode(n, true);
	return *this;
}

void BSTree::destroyTree(){

	if (root == nullptr) return;
	MyStack* nodeStack = new MyStack();
	nodeStack->pushElem(root);
	while (nodeStack->stackEmpty() == false) {
		TreeNode *node = nodeStack->popElem();
		if (node->getRight())
			nodeStack->pushElem(node->getRight());
		if (node->getLeft())
			nodeStack->pushElem(node->getLeft());
		delete node;
	}

	root = nullptr;
	delete nodeStack;
}

int BSTree::sizeOfTree(){
	return numOfNodes;
}

TreeNode* BSTree::getRoot(){
	return root;
}

void printTree(TreeNode* treeRoot){

	TreeNode* curr = treeRoot;
	MyStack* nodeStack = new MyStack;

	while (1){

		while (curr){
			nodeStack->pushElem(curr);
			curr = curr->getLeft();
		}

		if (!nodeStack->stackEmpty()) {
			curr = nodeStack->popElem();
			cout << curr->getKey() << " ";
			curr = curr->getRight();
		}
		else
			break;
	}
	delete nodeStack;
}

ostream& operator<<(ostream& out, const BSTree& tree){
	printTree(tree.root);
	return out << endl;
}

BSTree::~BSTree(){
	destroyTree();
}

void TreeNode::setLeft(TreeNode* l){
	left = l;
}

void TreeNode::setRight(TreeNode* r){
	right = r;
}

TreeNode* TreeNode::getRight(){
	return right;
}

TreeNode* TreeNode::getLeft(){
	return left;
}

int TreeNode::getKey(){
	return key;
}



//list

List::~List(){
	destroy();
}

void List::destroy(){

	while (this && first) {
		Elem* old = first; first = first->next;
		delete old;
	}
	if (this) last = nullptr;
}

void List::copyList(const List& lst) {

	first = last = nullptr;
	for (Elem* curr = lst.first; curr; curr = curr->next){
		if (!first)
			last = first = new Elem(curr->num);
		else
			last = last->next = new Elem(curr->num);
	}
}

void List::delSpecRange(int lBound, int rBound){

	if ((first->num > rBound) || (last->num < lBound))
		cout << "The range " << lBound << "-" << rBound << " does not belong to the set." << endl;
	else{
		Elem* curr = first;
		Elem* prev = nullptr;
		while (lBound > curr->num)
			curr = curr->next;
		while (curr && (curr->num <= rBound)){
			int hNum = curr->num;
			curr = curr->next;
			deleteElem(hNum, false);
		}
	}
}

List* createList(int* arr){
	sortArr(arr, sizeof(arr) / sizeof(int));
	List* newLst = new List();
	newLst->first = newLst->last = new List::Elem(arr[0]);
	for (int it = 1; it < sizeof(arr) / sizeof(int); it++)
		newLst->last = newLst->last->next = new List::Elem(arr[it]);
	return newLst;
}

void List::deleteElem(int n, bool mess){

	if (first == nullptr)
		cout << "The set is empty." << endl;
	else{
		Elem* curr = this->first;
		Elem* prev = nullptr;
		while (curr && (curr->num < n)){
			prev = curr;
			curr = curr->next;
		}
		if (curr && (curr->num == n)){
			if (prev){
				prev->next = curr->next;
				if (curr == last)
					last = prev;
			}
			else{
				first = curr->next;
				if (!first)
					last = nullptr;
			}
			delete curr;
			--numOfElem;
		}
		else{
			if (mess)
				cout << "The number " << n << " doesn't exist in the set." << endl;
		}
	}
}

List& List::operator = (const List& lst){

	if (this != &lst){
		destroy();
		copyList(lst);
	}
	return *this;
}

bool List::findElem(int n){

	if (first == nullptr){
		cout << "The set is empty." << endl;
		return false;
	}
	else{
		Elem* curr = this->first;
		while (curr && (curr->num < n))
			curr = curr->next;
		if (curr && (curr->num == n))
			return true;
		else return false;
	}
}

void List::insertElem(int newNum, bool mess){

	bool exist = false;
	if (!first) last = first = new Elem(newNum);
	else {
		Elem* curr = first;
		Elem* prev = nullptr;
		while (curr && (curr->num < newNum)){
			prev = curr;
			curr = curr->next;
		}
		if (!curr)
			last = last->next = new Elem(newNum);
		else if (curr && (curr->num == newNum)){
			if (mess)
				cout << "The element " << newNum << " already exists in the set." << endl;
			exist = true;
		}
		else if (curr && (curr->num != newNum)){
			Elem* newElem = new Elem(newNum);
			if (curr == first){
				newElem->next = first;
				first = newElem;
			}
			else{
				newElem->next = prev->next;
				prev->next = newElem;
			}
			newElem = prev = nullptr;
		}
		curr = nullptr;
	}
	if (!exist) ++numOfElem;
}

int List::size(){
	return numOfElem;
}

List& List::operator += (const int& n) {
	insertElem(n, true);
	return *this;
}

ostream& operator << (ostream& out, const List& lst) {

	for (List::Elem* current = lst.first; current; current = current->next)
		out << current->num << " ";
	out << endl;
	return out;
}

List::Elem* List::getFirst(){
	return first;
}

List* unionOf2lst(int nTest)
{
	int* arr1 = nullptr;
	int* arr2 = nullptr;
	int newNum, n = 0, n2 = 0;

	if (nTest){
		int s = -4;
		arr1 = new int[nTest];
		for (int i = 0; i < nTest; i++)
			arr1[i] = rand() % 100 + s;
		s = 9;
		arr2 = new int[nTest];
		for (int i = 0; i < nTest; i++)
			arr2[i] = rand() % 100 + s;
	}
	else{
		cout << "How many elements will have the first set?" << endl;
		cin >> n;
		if (n <= 0) cout << "Incorrect number." << endl, exit(1);
		arr1 = new int[n];
		cout << "Enter the first set." << endl;
		for (int iter = 0; iter < n; iter++){
			cin >> newNum;
			arr1[iter] = newNum;
		}

		cout << "How many elements will have the second set?" << endl;
		cin >> n2;
		if (n2 <= 0) cout << "Incorrect number." << endl, exit(1);
		arr2 = new int[n2];
		cout << "Enter the second set." << endl;
		for (int iter = 0; iter < n2; iter++){
			cin >> newNum;
			arr2[iter] = newNum;
		}
	}
	sortArr(arr1, n);
	sortArr(arr2, n2);

	int* newArr = arrUnion(arr1, n, arr2, n2);
	delete arr1;
	delete arr2;

	List* unionLst = new List();
	n2 = 1;
	unionLst->first = unionLst->last = new List::Elem(newArr[0]);
	while (n2 < sizeof(newArr) / (sizeof(int)))
		unionLst->last = unionLst->last->next = new List::Elem(newArr[n2++]);

	delete newArr;

	return unionLst;
}



//test

void ftest(int n){
	PerformanceCalculator pc;
	double avgTime = 0;
	int* numbers = new int[n];
	for (int i = 0; i < n; i++)
		numbers[i] = rand() % n + 1;

	cout << "Function: Creating a set" << endl;
	for (int j = 0; j < 3; j++){
		pc.start();
		BSTree* testTree = new BSTree();
		for (int i = 0; i < n; i++)
			testTree->insertNode(numbers[i], false);
		pc.stop();
		avgTime += pc.elapsedMillis();
		delete testTree;
	}
	cout << "The average execution time for the bst-set is " << avgTime / 3.0 << " miliseconds." << endl;

	avgTime = 0;
	for (int j = 0; j < 3; j++){
		pc.start();
		List* testList = createList(numbers);
		for (int i = 0; i < n; i++)
			testList->insertElem(numbers[i], false);
		pc.stop();
		avgTime += pc.elapsedMillis();
		delete testList;
	}
	cout << "The average execution time for the list-set is " << avgTime / 3.0 << " miliseconds." << endl;

	//new BSTree and List objects for other function testing performances
	BSTree* testTree = new BSTree();
	for (int i = 0; i < n; i++)
		testTree->insertNode(numbers[i], false);
	List* testList = createList(numbers);

	avgTime = 0;

	//insert element in the set
	cout << "Function: Inserting an element in the set" << endl;
	for (int j = 0; j < 3; j++){
		pc.start();
		testTree->insertNode((rand() % 100 + 1), false);
		pc.stop();
		avgTime += pc.elapsedMillis();
	}
	cout << "The average execution time for the bst-set is " << avgTime / 3.0 << " miliseconds." << endl;

	avgTime = 0;
	for (int j = 0; j < 3; j++){
		pc.start();
		testList->insertElem((rand() % 100 + 1), false);
		pc.stop();
		avgTime += pc.elapsedMillis();
	}
	cout << "The average execution time for the list-set is " << avgTime / 3.0 << " miliseconds." << endl;

	//delete element from the set
	avgTime = 0;
	cout << "Function: Deleting an element in the set" << endl;
	for (int j = 0; j < 3; j++){
		pc.start();
		testTree->deleteNode((rand() % 100 + 1), false);
		pc.stop();
		avgTime += pc.elapsedMillis();
	}
	cout << "The average execution time for the bst-set is " << avgTime / 3.0 << " miliseconds." << endl;

	avgTime = 0;
	for (int j = 0; j < 3; j++){
		pc.start();
		testList->deleteElem((rand() % 100 + 1), false);
		pc.stop();
		avgTime += pc.elapsedMillis();
	}
	cout << "The average execution time for the list-set is " << avgTime / 3.0 << " miliseconds." << endl;

	//find element in the set
	avgTime = 0;
	cout << "Function: Finding an element in the set" << endl;
	for (int j = 0; j < 3; j++){
		pc.start();
		testTree->findNode((rand() % 100 + 1));
		pc.stop();
		avgTime += pc.elapsedMillis();
	}
	cout << "The average execution time for the bst-set is " << avgTime / 3.0 << " miliseconds." << endl;

	avgTime = 0;
	for (int j = 0; j < 3; j++){
		pc.start();
		testList->findElem((rand() % 100 + 1));
		pc.stop();
		avgTime += pc.elapsedMillis();
	}
	cout << "The average execution time for the list-set is " << avgTime / 3.0 << " miliseconds." << endl;

	delete testTree;
	delete testList;
	
	//union
	cout << "Function: Union" << endl;
	avgTime = 0;
	for (int j = 0; j < 3; j++){
	pc.start();
	unionOf2trees(n);
	pc.stop();
	avgTime += pc.elapsedMillis();
	}
	cout << "The average execution time for the bst-set is " << avgTime / 3.0 << " miliseconds." << endl;
	
	avgTime = 0;
	for (int j = 0; j < 3; j++){
		pc.start();
		unionOf2lst(n);
		pc.stop();
		avgTime += pc.elapsedMillis();
	}
	cout << "The average execution time for the list-set is " << avgTime / 3.0 << " miliseconds." << endl;

	delete numbers;
}

void test(){
	
	cout << "200 elements set performances" << endl;
	ftest(200);
	cout << endl;

	cout << "500 elements set performances" << endl;
	ftest(500);
	cout << endl;

	cout << "1000 elements set performances" << endl;
	ftest(1000);
	cout << endl;

	cout << "10000 elements set performances" << endl;
	ftest(10000);
	cout << endl;
	
	cout << "100000 elements set performances" << endl;
	ftest(100000);
	cout << endl;

	cout << "1000000 elements set performances" << endl;
	ftest(1000000);
	cout << endl;
}

//myStack

MyStack::~MyStack(){
	while (first){
		Elem* old = first;
		first = first->next;
		delete old->num;
	}
}

bool MyStack::stackEmpty(){
	if (!first) return true;
	else return false;
}

TreeNode* MyStack::popElem(){
	if (stackEmpty()) return nullptr;
	Elem* newEl = first;
	first = first->next;
	TreeNode* newNode = newEl->num;
	newEl->num = nullptr;
	newEl->next = nullptr;
	return newNode;
}

void MyStack::pushElem(TreeNode* num){
	TreeNode* newNd = num;
	Elem* newEl = new Elem(num);
	if (!first) first = newEl;
	else {
		newEl->next = first;
		first = newEl;
	}
	newEl = nullptr;
}