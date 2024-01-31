#include "main.h"

int MAXSIZE;

/*------------ CODE BEGIN: Define a node in Huffman Tree ------------*/
struct HuffNode_T {
	unsigned char letter;
	int freq;
	struct HuffNode_T *left;
	struct HuffNode_T *right;
};

struct HuffNode_T* newHuffNode(unsigned char letter, int freq, struct HuffNode_T *left, struct HuffNode_T *right) {
	struct HuffNode_T* new_node = (struct HuffNode_T*) malloc(sizeof(struct HuffNode_T));
	new_node->letter = letter;
	new_node->freq = freq;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}

int countFreqOfLetter(string name, struct HuffNode_T** char_arr_addr) {
	struct HuffNode_T* char_arr = *char_arr_addr;
	char_arr = (struct HuffNode_T*) malloc(sizeof(struct HuffNode_T) * name.length());
	int char_arr_size = 0;
	for (int i = 0; i < name.length(); i++) {
		int j = 0;
		for (j = 0; j < char_arr_size; j++) {
			if (name[i] == char_arr[j].letter) break;
		}
		if (j == char_arr_size) {
			char_arr[char_arr_size].letter = name[i];
			char_arr[char_arr_size].freq = 1;
			char_arr[char_arr_size].left = NULL;
			char_arr[char_arr_size].right = NULL;
			char_arr_size++;
		} else {
			char_arr[j].freq++;
		}
	}
	char_arr = (struct HuffNode_T*) realloc(char_arr, sizeof(struct HuffNode_T) * char_arr_size);
	*char_arr_addr = char_arr;
	return char_arr_size;
}

string applyCaesarCipher(string name) {
	/* Count frequency of letters */
	struct HuffNode_T* char_arr = NULL;
	int char_arr_size = countFreqOfLetter(name, &char_arr);
	/* Apply Caeser cipher */
	for (int i = 0; i < name.length(); i++) {
		int j = 0;
		for (j = 0; j < char_arr_size; j++) {
			if (char_arr[j].letter == name[i]) break;
		}
		if (name[i] >= 'a' && name[i] <= 'z') name[i] = (name[i] - 'a' + char_arr[j].freq) % 26 + 'a';
		else name[i] = (name[i] - 'A' + char_arr[j].freq) % 26 + 'A';
	}
	/* Clear raw list */
	delete char_arr;
	return name;
}

bool isUpperCase(unsigned char letter) {
	return (letter >= 'A' && letter <= 'Z');
}

bool isLowerCase(unsigned char letter) {
	return (letter >= 'a' && letter <= 'z');
}

bool isASmallerThanB(struct HuffNode_T node_A, struct HuffNode_T node_B) {
	if (node_A.freq < node_B.freq) return true;
	if (node_A.freq == node_B.freq) {
		if ((isUpperCase(node_A.letter) || isLowerCase(node_A.letter)) && 
			(isUpperCase(node_B.letter) || isLowerCase(node_B.letter))) {
			// Both A and B are letter nodes
			return ((isLowerCase(node_A.letter) && isUpperCase(node_B.letter)) || 
					(isLowerCase(node_A.letter) && isLowerCase(node_B.letter) && node_A.letter < node_B.letter) ||
					(isUpperCase(node_A.letter) && isUpperCase(node_B.letter) && node_A.letter < node_B.letter));
		} else if (isUpperCase(node_A.letter) || isLowerCase(node_A.letter)) {
			// A is letter node, B is merged node
			return true;
		} else if (isUpperCase(node_B.letter) || isLowerCase(node_B.letter)) {
			// A is merged node, B is letter node
			return false;
		} else {
			// Both A and B are merged nodes
			if (node_A.letter < node_B.letter) return true;
		}
	}
	return false;
}

void reheapUp(struct HuffNode_T** min_heap_addr, int pos) {
	struct HuffNode_T* min_heap = *min_heap_addr;
	if (pos > 0) {
		int parent = (pos - 1) / 2;
		if (isASmallerThanB(min_heap[pos], min_heap[parent])) {
			struct HuffNode_T tmp_data = min_heap[parent];
			min_heap[parent] = min_heap[pos];
			min_heap[pos] = tmp_data;
			reheapUp(&min_heap, parent);
		}
	}
	*min_heap_addr = min_heap;
}

void reheapDown(struct HuffNode_T** min_heap_addr, int pos, int last_pos) {
	struct HuffNode_T* min_heap = *min_heap_addr;
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	if (left <= last_pos) {
		int smaller = left;
		if (right <= last_pos && isASmallerThanB(min_heap[right], min_heap[left])) {
			smaller = right;
		}
		if (isASmallerThanB(min_heap[smaller], min_heap[pos])) {
			struct HuffNode_T tmp_data = min_heap[smaller];
			min_heap[smaller] = min_heap[pos];
			min_heap[pos] = tmp_data;
			reheapDown(&min_heap, smaller, last_pos);
		}
	}
	*min_heap_addr = min_heap;
}

void buildHeap(struct HuffNode_T** char_arr_addr, int size) {
	struct HuffNode_T* char_arr = *char_arr_addr;
	int last_pos = size - 1;
	int pos = (last_pos - 1) / 2;
	for (int i = pos; i >= 0; i--) {
		reheapDown(&char_arr, i, last_pos);
	}
	*char_arr_addr = char_arr;
}

struct HuffNode_T* popHeap(struct HuffNode_T** min_heap_addr, int* size) {
	if (*size == 0) return NULL;
	struct HuffNode_T* min_heap = *min_heap_addr;
	struct HuffNode_T* ret = (struct HuffNode_T*) malloc(sizeof(struct HuffNode_T));
	memcpy(ret, &min_heap[0], sizeof(struct HuffNode_T));
	(*size)--;
	min_heap[0] = min_heap[*size];
	reheapDown(&min_heap, 0, (*size) - 1);
	*min_heap_addr = min_heap;
	return ret;
}

void pushHeap(struct HuffNode_T merged_node, struct HuffNode_T** min_heap_addr, int* size) {
	struct HuffNode_T* min_heap = *min_heap_addr;
	min_heap[*size] = merged_node;
	reheapUp(&min_heap, *size);
	(*size)++;
	*min_heap_addr = min_heap;
}

unsigned char nextOrderNumber(unsigned char cur_order_num) {
	cur_order_num++;
	if (cur_order_num == 'a') return 'z' + 1;
	if (cur_order_num == 'A') return 'Z' + 1;
	return cur_order_num;
}

void buildHuff(struct HuffNode_T** tree_heap_addr, int heap_size) {
	struct HuffNode_T* tree_heap = *tree_heap_addr;
	struct HuffNode_T *tmp1, *tmp2, tmp3;
	unsigned char order_num = 0;
	while (heap_size > 1) {
		tmp1 = popHeap(&tree_heap, &heap_size);
		tmp2 = popHeap(&tree_heap, &heap_size);
		tmp3.letter = order_num;
		tmp3.freq = tmp1->freq + tmp2->freq;
		tmp3.left = tmp1;
		tmp3.right = tmp2;
		pushHeap(tmp3, &tree_heap, &heap_size);
		order_num = nextOrderNumber(order_num);
	}
	*tree_heap_addr = tree_heap;
}

void removeTree(struct HuffNode_T* root) {
	if (root->left != NULL) {
		removeTree(root->left);
	}
	if (root->right != NULL) {
		removeTree(root->right);
	}
	delete root;
}

/*------------- CODE END: Define a node in Huffman Tree -------------*/
void LAPSE(string name) {
	name = applyCaesarCipher(name);
	cout << "New name: " << name << endl;
	struct HuffNode_T* heap_for_huffman = NULL;	// Remind for cleaning up heap after finishing LAPSE
	int heap_size = countFreqOfLetter(name, &heap_for_huffman);
	buildHeap(&heap_for_huffman, heap_size);
	for (int i = 0; i < heap_size; i++) {
		cout << heap_for_huffman[i].letter << " - " << heap_for_huffman[i].freq << endl;
	}
	buildHuff(&heap_for_huffman, heap_size);
	struct HuffNode_T tmp[17];
	for (int i = 0; i < 17; i++) {
		tmp[i] = heap_for_huffman[i];
	}
	removeTree(&heap_for_huffman[0]);
	for (int i = 0; i < 17; i++) {
		tmp[i] = heap_for_huffman[i];
	}
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