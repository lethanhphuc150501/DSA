#include "main.h"

/*--------------------- DECLEARATION BEGIN: Global structures ---------------------*/
int MAXSIZE;
struct HuffNode_T* g_lastest_customer = NULL;
struct area_G* g_Gojo_restaurant = NULL;
struct min_heap_S* g_Sukuna_restaurant = NULL;
/*--------------------- DECLEARATION END: Global structures ---------------------*/

/*------------ CODE BEGIN: Support functions for Building Huffman tree ------------*/
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
int heightOfTree(const struct HuffNode_T* root) {
	if (root == NULL) return 0;
	int left = heightOfTree(root->left);
	int right = heightOfTree(root->right);
	return left > right ? (left + 1) : (right + 1);
}
struct HuffNode_T* rotateRight(struct HuffNode_T* root) {
	struct HuffNode_T* tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	return tmp;	// new root
}
struct HuffNode_T* rotateLeft(struct HuffNode_T* root) {
	struct HuffNode_T* tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	return tmp;	// new root
}
struct HuffNode_T* leftBalance(struct HuffNode_T* root) {
	struct HuffNode_T* leftTree = root->left;
	// Case 1: Right of left
	if (heightOfTree(leftTree->right) > heightOfTree(leftTree->left)) {
		root->left = rotateLeft(leftTree);
		root = rotateRight(root);
	} else	// Case 2: Left of left
		root = rotateRight(root);
	return root;
}
struct HuffNode_T* rightBalance(struct HuffNode_T* root) {
	struct HuffNode_T* rightTree = root->right;
	// Case 3: Left of right
	if (heightOfTree(rightTree->left) > heightOfTree(rightTree->right)) {
		root->right = rotateRight(rightTree);
		root = rotateLeft(root);
	} else	// Case 4: Right of right
		root = rotateLeft(root);
	return root;
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
void pushHeap(struct HuffNode_T* merged_node, struct HuffNode_T** min_heap_addr, int* size) {
	struct HuffNode_T* min_heap = *min_heap_addr;
	min_heap[*size].freq = merged_node->freq;
	min_heap[*size].letter = merged_node->letter;
	min_heap[*size].left = merged_node->left;
	min_heap[*size].right = merged_node->right;
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
struct HuffNode_T* balanceTree(struct HuffNode_T* root, bool* change_flag) {
	if (root == NULL) return root;
	int balance_factor = heightOfTree(root->left) - heightOfTree(root->right);
	if (balance_factor >= 2) {
		root = leftBalance(root);
		*change_flag = true;
		return root;
	} else if (balance_factor <= -2) {
		root = rightBalance(root);
		*change_flag = true;
		return root;
	}
	root->left = balanceTree(root->left, change_flag);
	if (*change_flag) return root;
	root->right = balanceTree(root->right, change_flag);
	return root;
}
void buildHuff(struct HuffNode_T** tree_heap_addr, int heap_size) {
	struct HuffNode_T* tree_heap = *tree_heap_addr;
	struct HuffNode_T *tmp1, *tmp2, *tmp3;
	unsigned char order_num = 0;
	while (heap_size > 1) {
		tmp1 = popHeap(&tree_heap, &heap_size);
		tmp2 = popHeap(&tree_heap, &heap_size);
		tmp3 = newHuffNode(order_num, tmp1->freq + tmp2->freq, tmp1, tmp2);
		bool is_tree_change = false;
		for (int i = 0; i < 3; i++) {
			tmp3 = balanceTree(tmp3, &is_tree_change);
			if (!is_tree_change) break;
			else is_tree_change = false;
		}
		order_num = nextOrderNumber(order_num);
		tmp3->letter = order_num;
		pushHeap(tmp3, &tree_heap, &heap_size);
		order_num = nextOrderNumber(order_num);
		delete tmp3;
	}
	*tree_heap_addr = tree_heap;
}
void removeTree(struct HuffNode_T* root) {
	if (root == NULL) return;
	removeTree(root->left);
	removeTree(root->right);
	delete root;
}
struct encodeChar_T {
	char letter;
	union {
		int raw_data;
		char* data;
	} encode;
	struct encodeChar_T* next;
};
struct encodeChar_T* encodeCharacter(struct HuffNode_T* root, int tmp) {
	if (root == NULL) return NULL;
	struct encodeChar_T* ret = NULL;
	if (isUpperCase(root->letter) || isLowerCase(root->letter)) {
		ret = (struct encodeChar_T*) malloc(sizeof(struct encodeChar_T));
		ret->letter = root->letter;
		ret->encode.raw_data = tmp;
		ret->next = NULL;
	} else {
		struct encodeChar_T* left = encodeCharacter(root->left, tmp * 2);
		struct encodeChar_T* right = encodeCharacter(root->right, tmp * 2 + 1);
		if (left != NULL) {
			ret = left;
			while (left->next != NULL) left = left->next;
			left->next = right;
		} else if (right != NULL) {
			ret = right;
		}
	}
	return ret;
}
char* convertRawData(int raw) {
	char bin_ret[32];
	int i = 0;
	while (raw > 0) {
	    bin_ret[i] = (raw % 2) ? '1' : '0';
	    raw /= 2;
	    i++;
	}
	if (i == 0) return NULL;
	char* ret = (char*) malloc(sizeof(char) * i);
	for (int j = 0; j < i - 1; j++) {
		ret[j] = bin_ret[i - j - 2];
	}
	ret[i - 1] = 0;
	return ret;
}
int convertStringBinary(char str_bin[], int str_len) {
	int mul = 1;
	int ret = 0;
	for (int i = 0; i < str_len; i++) {
		if (str_bin[i] == '1') ret += mul;
		mul = mul * 2;
	}
	return ret;
}
/*------------- CODE END: Support functions for Building Huffman tree -------------*/

/*------------------------- CODE BEGIN: Gojo's Restaurant -------------------------*/
struct customer_seat_G {
	int result;
	struct customer_seat_G* left;
	struct customer_seat_G* right;
};
struct fifo_node {
	int result;
	struct fifo_node* next;
};
struct area_G {
	int ID;
	int size;
	struct customer_seat_G* root;
	struct {
		struct fifo_node* head;
		struct fifo_node* tail;
	} fifo_order;
};
struct area_G* initGojoRestaurant() {
	struct area_G* ret = (struct area_G*) malloc(sizeof(struct area_G) * MAXSIZE);
	for (int i = 0; i < MAXSIZE; i++) {
		ret[i].ID = i + 1;
		ret[i].size = 0;
		ret[i].root = NULL;
		ret[i].fifo_order.head = NULL;
		ret[i].fifo_order.tail = NULL;
	}
	return ret;
}
struct customer_seat_G* addBST(struct customer_seat_G* root, int result) {
	if (root == NULL) {
		struct customer_seat_G* root = (struct customer_seat_G*) malloc(sizeof(struct customer_seat_G));
		root->left = NULL;
		root->right = NULL;
		root->result = result;
		return root;
	} else {
		if (result >= root->result) root->right = addBST(root->right, result);
		else root->left = addBST(root->left, result);
	}
	return root;
}
struct area_G* addCustomertoGojo(struct area_G* restaurant, int result) {
	int ID = result % MAXSIZE + 1;
	struct fifo_node* tmp = (struct fifo_node*) malloc(sizeof(struct fifo_node));
	tmp->next = NULL;
	tmp->result = result;
	if (restaurant[ID - 1].fifo_order.head == NULL) {
		restaurant[ID - 1].fifo_order.head = tmp;
		restaurant[ID - 1].fifo_order.tail = tmp;
	} else {
		restaurant[ID - 1].fifo_order.tail->next = tmp;
		restaurant[ID - 1].fifo_order.tail = tmp;
	}
	restaurant[ID - 1].root = addBST(restaurant[ID - 1].root, result);
	restaurant[ID - 1].size += 1;
	return restaurant;
}
void removeTree_G(struct customer_seat_G* root) {
	if (root == NULL) return;
	removeTree_G(root->left);
	removeTree_G(root->right);
	delete root;
}
struct customer_seat_G* removeNode_G(struct customer_seat_G* root, int value) {
	if (root == NULL) return NULL;
	if (value > root->result) root->right = removeNode_G(root->right, value);
	else if (value < root->result) root->left = removeNode_G(root->left, value);
	else {
		if (root->left == NULL) {
			struct customer_seat_G* dlt_it = root;
			root = root->right;
			delete dlt_it;
		} else if (root->right == NULL) {
			struct customer_seat_G* dlt_it = root;
			root = root->left;
			delete dlt_it;
		} else {
			struct customer_seat_G* dlt_it = root->right;
			while (dlt_it->left != NULL) {
				dlt_it = dlt_it->left;
			}
			root->result = dlt_it->result;
			root->right = removeNode_G(root->right, dlt_it->result);
		}
	}
	return root;
}
void removeAllCustomer(struct area_G* restaurant) {
	removeTree_G(restaurant->root);
	restaurant->root = NULL;
	restaurant->size = 0;
	struct fifo_node* tmp = restaurant->fifo_order.head;
	while (tmp != NULL) {
		restaurant->fifo_order.head = tmp->next;
		delete tmp;
		tmp = restaurant->fifo_order.head;
	}
	restaurant->fifo_order.head = NULL;
	restaurant->fifo_order.tail = NULL;
}
/*-------------------------- CODE END: Gojo's Restaurant --------------------------*/

/*------------------------ CODE BEGIN: Sukuna's restaurant ------------------------*/
struct lifo_node {
	int result;
	struct lifo_node* next;
	struct lifo_node* prev;
};
struct area_S {
	struct {
		struct lifo_node* head;
		struct lifo_node* tail;
	} lifo_order;
	int size;
	int label;
	unsigned int last_modified; 
};
struct min_heap_S {
	int size;
	struct area_S* heap_root;
};
struct min_heap_S* initSukunaRestaurant() {
	struct min_heap_S* ret = (struct min_heap_S*) malloc(sizeof(struct min_heap_S));
	ret->size = 0;
	ret->heap_root = (struct area_S*) malloc(sizeof(struct area_S) * MAXSIZE);
	for (int i = 0; i < MAXSIZE; i++) {
		ret->heap_root[i].size = 0;
		ret->heap_root[i].label = i + 1;
		ret->heap_root[i].last_modified = 0;
		ret->heap_root[i].lifo_order.head = NULL;
		ret->heap_root[i].lifo_order.tail = NULL;
	}
	return ret;
}
int updateAreaInfo(bool add_ops, struct area_S* area) {
	static unsigned int modified = 0;
	modified++;
	if (add_ops) area->size++;
	else area->size--;
	area->last_modified = modified;
	return area->size;
}
struct area_S* reheapUp_S(struct area_S* heap_root, int pos) {
	if (pos > 0) {
		int parent = (pos - 1) / 2;
		if (heap_root[pos].size < heap_root[parent].size ||
			(heap_root[pos].size == heap_root[parent].size && heap_root[pos].last_modified < heap_root[parent].last_modified)) {
			struct area_S tmp_data = heap_root[parent];
			heap_root[parent] = heap_root[pos];
			heap_root[pos] = tmp_data;
			heap_root = reheapUp_S(heap_root, parent);
		}
	}
	return heap_root;
}
struct area_S* reheapDown_S(struct area_S* heap_root, int pos, int last_pos) {
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	if (left <= last_pos) {
		int smaller = left;
		if (right <= last_pos && (heap_root[right].size < heap_root[left].size ||
			(heap_root[right].size == heap_root[left].size && heap_root[right].last_modified < heap_root[left].last_modified))) {
			smaller = right;
		}
		if (heap_root[smaller].size < heap_root[pos].size ||
			(heap_root[smaller].size == heap_root[pos].size && heap_root[smaller].last_modified < heap_root[pos].last_modified)) {
			struct area_S tmp_data = heap_root[smaller];
			heap_root[smaller] = heap_root[pos];
			heap_root[pos] = tmp_data;
			heap_root = reheapDown_S(heap_root, smaller, last_pos);
		}
	}
	return heap_root;
}
struct min_heap_S* addCustomertoSukuna(struct min_heap_S* restaurant, int result) {
	int ID = result % MAXSIZE + 1;
	int area_idx = 0;
	for (area_idx = 0; area_idx < MAXSIZE; area_idx++) {
		if (ID == restaurant->heap_root[area_idx].label) break;
	}
	struct lifo_node* new_customer = (struct lifo_node*) malloc(sizeof(struct lifo_node));
	new_customer->result = result;
	if (restaurant->heap_root[area_idx].size == 0) {
		new_customer->next = NULL;
		new_customer->prev = NULL;
		restaurant->heap_root[area_idx].lifo_order.head = new_customer;
		restaurant->heap_root[area_idx].lifo_order.tail = new_customer;
		updateAreaInfo(true, restaurant->heap_root + area_idx);
		struct area_S tmp = restaurant->heap_root[area_idx];
		restaurant->heap_root[area_idx] = restaurant->heap_root[restaurant->size];
		restaurant->heap_root[restaurant->size] = tmp;
		restaurant->heap_root = reheapUp_S(restaurant->heap_root, restaurant->size);
		restaurant->size++;
	} else {
		new_customer->next = restaurant->heap_root[area_idx].lifo_order.head;
		new_customer->prev = NULL;
		restaurant->heap_root[area_idx].lifo_order.head->prev = new_customer;
		restaurant->heap_root[area_idx].lifo_order.head = new_customer;
		updateAreaInfo(true, restaurant->heap_root + area_idx);
		restaurant->heap_root = reheapDown_S(restaurant->heap_root, area_idx, restaurant->size - 1);
	}
	return restaurant;
}
/*------------------------ CODE END: Sukuna's restaurant ------------------------*/
int LAPSE(string name) {
	if (name.length() < 3) return -1;
	name = applyCaesarCipher(name);
	struct HuffNode_T* heap_for_huffman = NULL;	// Remind for cleaning up heap after finishing LAPSE
	int heap_size = countFreqOfLetter(name, &heap_for_huffman);
	buildHeap(&heap_for_huffman, heap_size);
	int result = 0;
	buildHuff(&heap_for_huffman, heap_size);
	struct encodeChar_T* huff_result = encodeCharacter(heap_for_huffman, 1);
	struct encodeChar_T* tmp = huff_result;
	while (tmp != NULL) {
		tmp->encode.data = convertRawData(tmp->encode.raw_data);
		tmp = tmp->next;
	}
	char encode_name_reverse[10];
	int encode_slot = 10;
	for (int i = name.length() - 1; i >= 0; i--) {
		tmp = huff_result;
		while (tmp != NULL && tmp->letter != name[i]) tmp = tmp->next;
		for (int j = strlen(tmp->encode.data) - 1; j >= 0 && encode_slot > 0; j--) {
			encode_slot--;
			encode_name_reverse[encode_slot] = tmp->encode.data[j];
		}
		if (encode_slot <= 0) break;
	}
	result = convertStringBinary(encode_name_reverse, strlen(encode_name_reverse));
	if (result % 2 == 1) {
		if (g_Gojo_restaurant == NULL) {
			cout << "Error: Gojo restaurant has not been initialized" << endl;
			return -1;
		}
		g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, result);
	} else {
		if (g_Sukuna_restaurant == NULL) {
			cout << "Error: Sukuna restaurant has not been initialized" << endl;
			return -1;
		}
		g_Sukuna_restaurant = addCustomertoSukuna(g_Sukuna_restaurant, result);
	}
	struct HuffNode_T* rm_tree = g_lastest_customer;
	g_lastest_customer = heap_for_huffman;
	// Clean previous Huffman tree
	if (rm_tree != NULL) removeTree(rm_tree);
	// Clean encode result
	tmp = huff_result;
	while (tmp != NULL) {
		huff_result = tmp->next;
		delete tmp->encode.data;
		delete tmp;
		tmp = huff_result;
	}
	return result;
}
int sizeOfBST(const struct customer_seat_G* root) {
	if (root == NULL) return 0;
	int left = sizeOfBST(root->left);
	int right = sizeOfBST(root->right);
	return 1 + left + right;
}
int dfs(const struct customer_seat_G* root, int** pascal_triangle) {
	int num_of_children = sizeOfBST(root);
	if (num_of_children < 3) return 1;
	int left_ways = dfs(root->left, pascal_triangle) % MAXSIZE;
	int right_ways = dfs(root->right, pascal_triangle) % MAXSIZE;
	return ((left_ways * right_ways) % MAXSIZE) * pascal_triangle[num_of_children - 1][sizeOfBST(root->left)] % MAXSIZE;
}
int numOfWays(const struct customer_seat_G* root) {
	int num_of_children = sizeOfBST(root);
	if (num_of_children <= 1) return num_of_children % MAXSIZE;
	int** table = (int**) malloc(sizeof(int*) * num_of_children);
	for (int i = 0; i < num_of_children; i++) {
		table[i] = (int*) malloc(sizeof(int) * (i + 1));
	}
	for (int i = 0; i < num_of_children; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || j == i) table[i][j] = 1;
			else table[i][j] = (table[i - 1][j - 1] % MAXSIZE + table[i - 1][j] % MAXSIZE) % MAXSIZE;
		}
	}
	int ret = dfs(root, table) % MAXSIZE;
	for (int i = 0; i < num_of_children; i++) delete table[i];
	delete table;
	return ret;
}
void KOKUSEN() {
	for (int i = 0; i < MAXSIZE; i++) {
		int Y = numOfWays(g_Gojo_restaurant[i].root);
		if (Y >= g_Gojo_restaurant[i].size) removeAllCustomer(g_Gojo_restaurant + i);
		else {
			for (int j = 0; j < Y; j++) {
				g_Gojo_restaurant[i].root = removeNode_G(g_Gojo_restaurant[i].root, g_Gojo_restaurant[i].fifo_order.head->result);
				g_Gojo_restaurant[i].size--;
				fifo_node* dlt_it = g_Gojo_restaurant[i].fifo_order.head;
				g_Gojo_restaurant[i].fifo_order.head = dlt_it->next;
				delete dlt_it;
			}
		}
	}
}

void KEITEIKEN(int num) {
	if (g_Sukuna_restaurant->size == 0) return;
	struct area_S* heap_copy = (struct area_S*) malloc(sizeof(struct area_S) * g_Sukuna_restaurant->size);
	int size_copy = g_Sukuna_restaurant->size;
	memcpy(heap_copy, g_Sukuna_restaurant->heap_root, sizeof(struct area_S) * g_Sukuna_restaurant->size);
	for (int i = 0; i < num; i++) {
		int k = 0;
		for (k = 0; k < g_Sukuna_restaurant->size; k++) {
			if (g_Sukuna_restaurant->heap_root[k].label == heap_copy[0].label) break;
		}
		int num_of_rm_it = num;
		if (num_of_rm_it >= g_Sukuna_restaurant->heap_root[k].size) num_of_rm_it = g_Sukuna_restaurant->heap_root[k].size;
		for (int j = 0; j < num_of_rm_it; j++) {
			struct lifo_node* dlt_it = g_Sukuna_restaurant->heap_root[k].lifo_order.tail;
			g_Sukuna_restaurant->heap_root[k].lifo_order.tail = dlt_it->prev;
			if (g_Sukuna_restaurant->heap_root[k].lifo_order.tail != NULL)
				g_Sukuna_restaurant->heap_root[k].lifo_order.tail->next = NULL;
			else
				g_Sukuna_restaurant->heap_root[k].lifo_order.head = NULL;
			cout << dlt_it->result << "-" << g_Sukuna_restaurant->heap_root[k].label << endl;
			delete dlt_it;
			updateAreaInfo(false, g_Sukuna_restaurant->heap_root + k);
		}
		if (g_Sukuna_restaurant->heap_root[k].size == 0) {
			g_Sukuna_restaurant->size -= 1;
			struct area_S tmp = g_Sukuna_restaurant->heap_root[k];
			g_Sukuna_restaurant->heap_root[k] = g_Sukuna_restaurant->heap_root[g_Sukuna_restaurant->size];
			g_Sukuna_restaurant->heap_root[g_Sukuna_restaurant->size] = tmp;
			g_Sukuna_restaurant->heap_root = reheapDown_S(g_Sukuna_restaurant->heap_root, k, g_Sukuna_restaurant->size - 1);
		}
		size_copy--;
		if (size_copy == 0) break;
		struct area_S tmp = heap_copy[0];
		heap_copy[0] = heap_copy[size_copy];
		heap_copy[size_copy] = tmp;
		heap_copy = reheapDown_S(heap_copy, 0, size_copy - 1);
	}
	delete heap_copy;
}
void printTreeInOrder(struct HuffNode_T* root) {
	if (root == NULL) return;
	printTreeInOrder(root->left);
	if (isUpperCase(root->letter) || isLowerCase(root->letter)) cout << root->letter << endl;
	else cout << root->freq << endl;
	printTreeInOrder(root->right);
}
void HAND() {
	printTreeInOrder(g_lastest_customer);
}
void printBST(struct customer_seat_G* root) {
	if (root == NULL) return;
	printBST(root->left);
	cout << root->result << endl;
	printBST(root->right);
}
void LIMITLESS(int num) {
	if (num <= 0 || num > MAXSIZE) return;
	if (g_Gojo_restaurant[num - 1].size == 0) return;
	printBST(g_Gojo_restaurant[num - 1].root);
}
void printSukuna(int num, int idx) {
	if (idx >= g_Sukuna_restaurant->size) return;
	struct lifo_node* tmp = g_Sukuna_restaurant->heap_root[idx].lifo_order.head;
	for (int i = 0; i < num && tmp != NULL; i++) {
		cout << g_Sukuna_restaurant->heap_root[idx].label << "-" << tmp->result << endl;
		tmp = tmp->next;
	}
	printSukuna(num, 2 * idx + 1);
	printSukuna(num, 2 * idx + 2);
}
void CLEAVE(int num) {
	printSukuna(num, 0);
}

void simulate(string filename) {
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while (ss >> str) {
		if (str == "MAXSIZE") {
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
			g_Gojo_restaurant = initGojoRestaurant();
			g_Sukuna_restaurant = initSukunaRestaurant();
			g_lastest_customer = NULL;
		} else if (str == "LAPSE") {
			ss >> name;
			cout << "LAPSE " << LAPSE(name) << endl;
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
	// Clean all global structures
	removeTree(g_lastest_customer);
	for (int i = 0; i < MAXSIZE; i++) removeAllCustomer(g_Gojo_restaurant + i);
	delete g_Gojo_restaurant;
	for (int i = 0; i < MAXSIZE; i++) {
		lifo_node* tmp = g_Sukuna_restaurant->heap_root[i].lifo_order.head;
		while (tmp != NULL) {
			g_Sukuna_restaurant->heap_root[i].lifo_order.head = tmp->next;
			delete tmp;
			tmp = g_Sukuna_restaurant->heap_root[i].lifo_order.head;
		}
	}
	delete g_Sukuna_restaurant->heap_root;
	delete g_Sukuna_restaurant;
	return;
}