#include "main.h"

int MAXSIZE;

/*------------ CODE BEGIN: Define a node in Huffman Tree ------------*/
struct HuffNode_T {
	char letter;
	int freq;
	struct HuffNode_T *left;
	struct HuffNode_T *right;
};

struct HuffNode_T* newHuffNode(char letter, int freq, struct HuffNode_T *left, struct HuffNode_T *right) {
	struct HuffNode_T* new_node = (struct HuffNode_T*) malloc(sizeof(struct HuffNode_T));
	new_node->letter = letter;
	new_node->freq = freq;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}
/*------------- CODE END: Define a node in Huffman Tree -------------*/
void LAPSE(string name) {
	/* Count frequency of letters */
	struct HuffNode_T* list_node = newHuffNode(name[0], 1, NULL, NULL);
	struct HuffNode_T* tail_of_list = list_node;
	for (int i = 1; i < name.length(); i++) {
		struct HuffNode_T* tmp = list_node;
		while (tmp != NULL) {
			if (name[i] == tmp->letter) {
				tmp->freq++;
				break;
			}
			tmp = tmp->right;
		}
		if (tmp == NULL) {
			tail_of_list->right = newHuffNode(name[i], 1, NULL, NULL);
			tail_of_list = tail_of_list->right;
		}
	}
	// Unit Test
	struct HuffNode_T* tmp = list_node;
	while (tmp != NULL) {
		cout << tmp->letter << " - " << tmp->freq << endl;
		tmp = tmp->right;
	}
	/* Apply Caeser cipher */
	for (int i = 0; i < name.length(); i++) {
		struct HuffNode_T* tmp = list_node;
		while (tmp != NULL) {
			if (tmp->letter == name[i]) break;
			tmp = tmp->right;
		}
		if (name[i] >= 'a' && name[i] <= 'z') name[i] = (name[i] - 'a' + tmp->freq) % 26 + 'a';
		else name[i] = (name[i] - 'A' + tmp->freq) % 26 + 'A';
	}
	/* Clear raw list */
	while (list_node != NULL) {
		struct HuffNode_T* prev = list_node;
		list_node = list_node->right;
		delete prev;
	}
	tail_of_list = NULL;
	cout << "New name: " << name << endl;
}

void KOKUSEN() {
	cout << "KOKUSEN" << endl;
}

void KEITEIKEN(int num) {
	cout << "KEITEIKEN " << num << endl;
}

void HAND() {
	cout << "HAND " << endl;
}

void LIMITLESS(int num) {
	cout << "LIMITLESS " << num << endl;
}

void CLEAVE(int num) {
	cout << "CLEAVE " << num << endl;
}

void simulate(string filename) {
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while (ss >> str) {
		if (str == "MAXSIZE") {
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
		} else if (str == "LAPSE") {
			ss >> name;
			LAPSE(name);
		} else if (str == "KOKUSEN") {
			KOKUSEN();
		} else if (str == "KEITEIKEN") {
			ss >> num;
			KEITEIKEN(stoi(num));
		} else if (str == "HAND") {
			HAND();
		} else if (str == "LIMITLESS") {
			ss >> num;
			LIMITLESS(stoi(num));
		} else {
			ss >> num;
			CLEAVE(stoi(num));
		}
	}
	return;
}