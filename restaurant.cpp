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

int countFreqOfLetter(string name, struct HuffNode_T*** char_arr_addr) {
	struct HuffNode_T** char_arr = *char_arr_addr;
	char_arr = (struct HuffNode_T**) malloc(sizeof(struct HuffNode_T*) * name.length());
	for (int i = 0; i < name.length(); i++) char_arr[i] = NULL;
	int char_arr_size = 0;
	for (int i = 0; i < name.length(); i++) {
		int j = 0;
		while (char_arr[j] != NULL) {
			if (name[i] == char_arr[j]->letter) break;
			j++;
		}
		if (j == char_arr_size) {
			char_arr[char_arr_size] = newHuffNode(name[i], 1, NULL, NULL);
			char_arr_size++;
		} else {
			char_arr[j]->freq++;
		}
	}
	char_arr = (struct HuffNode_T**) realloc(char_arr, sizeof(struct HuffNode_T*) * char_arr_size);
	*char_arr_addr = char_arr;
	return char_arr_size;
}

string applyCaesarCipher(string name) {
	/* Count frequency of letters */
	struct HuffNode_T** char_arr = NULL;
	int char_arr_size = countFreqOfLetter(name, &char_arr);
	/* Apply Caeser cipher */
	for (int i = 0; i < name.length(); i++) {
		int j = 0;
		for (j = 0; j < char_arr_size; j++) {
			if (char_arr[j]->letter == name[i]) break;
		}
		if (name[i] >= 'a' && name[i] <= 'z') name[i] = (name[i] - 'a' + char_arr[j]->freq) % 26 + 'a';
		else name[i] = (name[i] - 'A' + char_arr[j]->freq) % 26 + 'A';
	}
	/* Clear raw list */
	for (int i = 0; i < char_arr_size; i++) {
		delete char_arr[i];
	}
	delete char_arr;
	return name;
}

bool isUpperCase(char letter) {
	return (letter >= 'A' && letter <= 'Z');
}

bool isLowerCase(char letter) {
	return (letter >= 'a' && letter <= 'z');
}

bool isASmallerThanB(char letter_A, char letter_B) {
	return ((isLowerCase(letter_A) && isUpperCase(letter_B)) || 
			(isLowerCase(letter_A) && isLowerCase(letter_B) && letter_A < letter_B) ||
			(isUpperCase(letter_A) && isUpperCase(letter_B) && letter_A < letter_B));
}

void reheapUp(struct HuffNode_T*** min_heap_addr, int pos) {
	struct HuffNode_T** min_heap = *min_heap_addr;
	if (pos > 0) {
		int parent = (pos - 1) / 2;
		if (min_heap[parent]->freq > min_heap[pos]->freq ||
			(min_heap[parent]->freq == min_heap[pos]->freq && isASmallerThanB(min_heap[pos]->letter, min_heap[parent]->letter))) {
			struct HuffNode_T* tmp_data = min_heap[parent];
			min_heap[parent] = min_heap[pos];
			min_heap[pos] = tmp_data;
			reheapUp(&min_heap, parent);
		}
	}
	*min_heap_addr = min_heap;
}

void reheapDown(struct HuffNode_T*** min_heap_addr, int pos, int last_pos) {
	struct HuffNode_T** min_heap = *min_heap_addr;
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	if (left <= last_pos) {
		int smaller = left;
		if (right <= last_pos && (min_heap[right]->freq < min_heap[left]->freq || 
			(min_heap[right]->freq == min_heap[left]->freq && isASmallerThanB(min_heap[right]->letter, min_heap[left]->letter)))) {
			smaller = right;
		}
		if (min_heap[smaller]->freq < min_heap[pos]->freq ||
			(min_heap[smaller]->freq == min_heap[pos]->freq && isASmallerThanB(min_heap[smaller]->letter, min_heap[pos]->letter))) {
			struct HuffNode_T* tmp_data = min_heap[smaller];
			min_heap[smaller] = min_heap[pos];
			min_heap[pos] = tmp_data;
			reheapDown(&min_heap, smaller, last_pos);
		}
	}
	*min_heap_addr = min_heap;
}

void buildHeap(struct HuffNode_T*** char_arr_addr, int size) {
	struct HuffNode_T** char_arr = *char_arr_addr;
	int last_pos = size - 1;
	int pos = (last_pos - 1) / 2;
	for (int i = pos; i >= 0; i--) {
		reheapDown(&char_arr, i, last_pos);
	}
	*char_arr_addr = char_arr;
}

struct HuffNode_T* popHeap(struct HuffNode_T*** min_heap_addr, int* size) {
	if (*size == 0) return NULL;
	struct HuffNode_T** min_heap = *min_heap_addr;
	struct HuffNode_T* ret = min_heap[0];
	(*size)--;
	min_heap[0] = min_heap[*size];
	reheapDown(&min_heap, 0, (*size) - 1);
	*min_heap_addr = min_heap;
	return ret;
}

void pushHeap(struct HuffNode_T* merged_node, struct HuffNode_T*** min_heap_addr, int* size) {
	struct HuffNode_T** min_heap = *min_heap_addr;
	min_heap[*size] = merged_node;
	reheapUp(&min_heap, *size);
	(*size)++;
	*min_heap_addr = min_heap;
}

/*------------- CODE END: Define a node in Huffman Tree -------------*/
void LAPSE(string name) {
	name = applyCaesarCipher(name);
	cout << "New name: " << name << endl;
	struct HuffNode_T** heap_for_huffman = NULL;	// Remind for cleaning up heap after finishing LAPSE
	int heap_size = countFreqOfLetter(name, &heap_for_huffman);
	buildHeap(&heap_for_huffman, heap_size);
	for (int i = 0; i < heap_size; i++) {
		cout << heap_for_huffman[i]->letter << " - " << heap_for_huffman[i]->freq << endl;
	}
	struct HuffNode_T* first_node = popHeap(&heap_for_huffman, &heap_size);
	cout << "After pop" << endl;
	for (int i = 0; i < heap_size; i++) {
		cout << heap_for_huffman[i]->letter << " - " << heap_for_huffman[i]->freq << endl;
	}
	pushHeap(first_node, &heap_for_huffman, &heap_size);
	cout << "After push" << endl;
	for (int i = 0; i < heap_size; i++) {
		cout << heap_for_huffman[i]->letter << " - " << heap_for_huffman[i]->freq << endl;
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