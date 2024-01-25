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

/*------------- CODE END: Define a node in Huffman Tree -------------*/
void LAPSE(string name) {
	name = applyCaesarCipher(name);
	cout << "New name: " << name << endl;
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