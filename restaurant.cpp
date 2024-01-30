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

void reheapDown(struct HuffNode_T** min_heap_addr, int pos, int last_pos) {
	struct HuffNode_T* min_heap = *min_heap_addr;
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	if (left <= last_pos) {
		int smaller = left;
		if (right <= last_pos && (min_heap[right].freq < min_heap[left].freq || 
			(min_heap[right].freq == min_heap[left].freq && isASmallerThanB(min_heap[right].letter, min_heap[left].letter)))) {
			smaller = right;
		}
		if (min_heap[smaller].freq < min_heap[pos].freq ||
			(min_heap[smaller].freq == min_heap[pos].freq && isASmallerThanB(min_heap[smaller].letter, min_heap[pos].letter))) {
			int tmp_freq = min_heap[smaller].freq;
			char tmp_letter = min_heap[smaller].letter;
			min_heap[smaller].freq = min_heap[pos].freq;
			min_heap[smaller].letter = min_heap[pos].letter;
			min_heap[pos].freq = tmp_freq;
			min_heap[pos].letter = tmp_letter;
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

struct HuffNode_T popHeap(struct HuffNode_T** char_arr_addr, int* size) {
	struct HuffNode_T* char_arr = *char_arr_addr;
	struct HuffNode_T ret = char_arr[0];
	(*size)--;
	char_arr[0] = char_arr[*size];
	reheapDown(&char_arr, 0, *size);
	*char_arr_addr = char_arr;
	return ret;
}

/*------------- CODE END: Define a node in Huffman Tree -------------*/
void LAPSE(string name) {
	name = applyCaesarCipher(name);
	cout << "New name: " << name << endl;
	struct HuffNode_T* heap_for_huffman = NULL;
	int heap_size = countFreqOfLetter(name, &heap_for_huffman);
	buildHeap(&heap_for_huffman, heap_size);
	for (int i = 0; i < heap_size; i++) {
		cout << heap_for_huffman[i].letter << " - " << heap_for_huffman[i].freq << endl;
	}
	while (heap_size > 0) {
		struct HuffNode_T first_node = popHeap(&heap_for_huffman, &heap_size);
		cout << "Heap size: " << heap_size << "\tRemoved node: " << first_node.letter << " - " << first_node.freq << endl;
	}
	// /* Count frequency of letters */
	// list_node = newHuffNode(name[0], 1, NULL, NULL);
	// tail_of_list = list_node;
	// for (int i = 0; i < name.length(); i++) {
	// 	struct HuffNode_T* tmp = list_node;
	// 	while (tmp != NULL) {
	// 		if (name[i] == tmp->letter) break;
	// 		tmp = tmp->right;
	// 	}
	// 	if (tmp == NULL || i == 0) {
	// 		int count = 0;
	// 		for (int j = i; j < name.length(); j++) {
	// 			if (name[i] == name[j]) count++;
	// 		}
	// 		if (i == 0) list_node->freq = count;
	// 		else {
	// 			tmp = list_node;
	// 			while (tmp != NULL) {
	// 				if (count < tmp->freq) break;
	// 				if (count == tmp->freq) {
	// 					if ((name[i] >= 'a' && name[i] <= 'z') && (tmp->letter >= 'A' && tmp->letter <= 'Z')) break;
	// 					if ((name[i] >= 'a' && name[i] <= 'z') && (tmp->letter >= 'a' && tmp->letter <= 'z') && name[i] < tmp->letter) break;
	// 					if ((name[i] >= 'A' && name[i] <= 'Z') && (tmp->letter >= 'A' && tmp->letter <= 'Z') && name[i] < tmp->letter) break;
	// 				}
	// 				tmp = tmp->right;
	// 			}
	// 			if (tmp != NULL) {
	// 				struct HuffNode_T* prev = tmp->left;
	// 				if (prev == NULL) {
	// 					prev = newHuffNode(name[i], count, NULL, list_node);
	// 					tmp->left = prev;
	// 					list_node = prev;
	// 				} else {
	// 					prev->right = newHuffNode(name[i], count, prev, tmp);
	// 					tmp->left = prev->right;
	// 				}
	// 			} else {
	// 				tail_of_list->right = newHuffNode(name[i], count, tail_of_list, NULL);
	// 				tail_of_list = tail_of_list->right;
	// 			}
	// 		}
	// 	}
	// }
	// // Unit Test
	// tmp = list_node;
	// while (tmp != NULL) {
	// 	cout << tmp->letter << " - " << tmp->freq << endl;
	// 	tmp = tmp->right;
	// }
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