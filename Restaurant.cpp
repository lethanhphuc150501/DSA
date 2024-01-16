#include "main.h"

int abs(int num) {
	if (num > 0) return num;
	else return -num;
}

int first_incremental_value(int n) {
	int k = 1;
	while (k < n/3) {
		k = 3 * k + 1;
	}
	return k;
}
class imp_res : public Restaurant
{
	private:
		int serve_size; 		// Number of customer served
		customer* cir_head;		// Position X

		int total_size;			// Number of all customer in the restaurant
		customer* seq_head;		// Head of sequence list
		customer* seq_tail;		// Tail of sequence list
		
		int wait_size;			// Number of customer waiting
		customer* top_queue;	// Head for waiting queue
		customer* bot_queue;	// Tail for waiting queue

		void addSeqList(string name, int energy) {
			if (this->total_size == 0) {
				customer *cp_cus = new customer (name, energy, nullptr, nullptr); mem_leak++;
				this->seq_head = cp_cus;
				this->seq_tail = cp_cus;
			} else {
				customer *cp_cus = new customer (name, energy, this->seq_tail, nullptr); mem_leak++;
				this->seq_tail->next = cp_cus;
				this->seq_tail = cp_cus;
			}
			this->total_size += 1;
		}

		void rmSeqList(string name) {
			if (this->total_size <= 0) return;
			this->total_size -= 1;
			if (this->total_size == 0) {
				customer* tmp = this->seq_head;
				delete tmp; mem_leak--;
				this->seq_head = NULL;
				this->seq_tail = NULL;
				return;
			}
			if (name == this->seq_head->name) {
				customer* tmp = this->seq_head;
				this->seq_head = tmp->next;
				this->seq_head->prev = NULL;
				delete tmp; mem_leak--;
				return;
			}
			if (name == this->seq_tail->name) {
				customer* tmp = this->seq_tail;
				this->seq_tail = tmp->prev;
				this->seq_tail->next = NULL;
				delete tmp; mem_leak--;
				return;
			}
			customer* tmp = this->seq_head;
			while (tmp->name != name) {
				tmp = tmp->next;
			}
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp; mem_leak--;
		}

		void enqueue(string name, int energy) {
			if (this->wait_size == 0) {
				customer *cus = new customer (name, energy, nullptr, nullptr); mem_leak++;
				this->top_queue = cus;
				this->bot_queue = cus;
			} else {
				customer *cus = new customer (name, energy, this->bot_queue, nullptr); mem_leak++;
				this->bot_queue->next = cus;
				this->bot_queue = cus;
			}
			this->wait_size += 1;
		}

		void dequeue() {
			if (this->wait_size <= 1) {
				customer *tmp = this->top_queue;
				this->wait_size = 0;
				delete tmp; mem_leak--;
				this->top_queue = NULL;
				this->bot_queue = NULL;
			} else {
				customer *tmp = this->top_queue;
				this->wait_size -= 1;
				this->top_queue = tmp->next;
				this->top_queue->prev = NULL;
				delete tmp; mem_leak--;
			}
		}

		void rmQueue(string name) {
			if (this->wait_size <= 0) return;
			if (name == this->top_queue->name) {
				this->dequeue();
				return;
			}
			if (name == this->bot_queue->name) {
				customer* tmp = this->bot_queue;
				this->bot_queue = tmp->prev;
				this->bot_queue->next = NULL;
				delete tmp; mem_leak--;
				this->wait_size -= 1;
				return;
			}
			customer* tmp = this->top_queue;
			while (tmp->name != name) {
				tmp = tmp->next;
				if (tmp == NULL) return;
			}
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp; mem_leak--;
			this->wait_size -= 1;
		}

		void firstCustomer(string name, int energy) {
			customer *cus = new customer(name, energy, NULL, NULL); mem_leak++;
			cus->next = cus;
			cus->prev = cus;
			this->serve_size = 1;
			this->cir_head = cus;
		}

		void serveCustomer(bool clockwise, string name, int energy, string name_ref) {
			customer *tmp = this->cir_head;
			while (tmp->name != name_ref) {		// unsafe, add variable to count number of loops later
				tmp = tmp->next;
			}
			if (clockwise == true) {
				customer *cus = new customer(name, energy, tmp, tmp->next); mem_leak++;
				tmp->next->prev = cus;
				tmp->next = cus;
				this->cir_head = cus;
			} else {
				customer *cus = new customer(name, energy, tmp->prev, tmp); mem_leak++;
				tmp->prev->next = cus;
				tmp->prev = cus;
				this->cir_head = cus;
			}
			this->serve_size += 1;
		}

		int byeCustomer(string name) {
			if (this->serve_size <= 1 && this->cir_head->name == name) {
				customer *tmp = this->cir_head;
				this->cir_head = NULL;
				this->serve_size = 0;
				delete tmp; mem_leak--;
				return 0;
			}
			customer *rm_it = this->cir_head;
			int loop = 1;
			while (rm_it->name != name) {
				loop++;
				if (loop > this->serve_size) return -1;
				rm_it = rm_it->next;
			}
			this->cir_head = (rm_it->energy > 0) ? rm_it->next : rm_it->prev;
			customer *tmp = rm_it->next;
			rm_it->prev->next = tmp;
			tmp->prev = rm_it->prev;
			delete rm_it; mem_leak--;
			this->serve_size -= 1;
			return 0;
		}

		int SortSegment(int k, int segment, customer *nxt_cus) {
			int swap_time = 0;
			customer *neo = this->top_queue;
			for (int i = 0; i < segment && neo != nxt_cus; i++) neo = neo->next;
			if (neo == nxt_cus) return 0;
			while (neo != nxt_cus) {
				int neo_energy = neo->energy;
				string neo_name = neo->name;
				customer *tmp = neo;
				customer *walker = tmp;
				for (int i = 0; i < k && walker != NULL; i++) walker = walker->prev;
				while (walker != NULL && abs(neo_energy) >= abs(walker->energy)) {	// Insertion Sort
					if (abs(neo_energy) == abs(walker->energy)) {
						customer *check_equal = this->seq_head;
						while (check_equal->name != neo_name && check_equal->name != walker->name) {
							check_equal = check_equal->next;
						}
						if (check_equal->name == walker->name) break;						
					}
					tmp->energy = walker->energy;
					tmp->name = walker->name;
					tmp = walker;
					swap_time++;
					for (int i = 0; i < k && walker != NULL; i++) walker = walker->prev;
				}
				tmp->energy = neo_energy;
				tmp->name = neo_name;
				for (int i = 0; i < k && neo != nxt_cus; i++) neo = neo->next;
			}
			return swap_time;	
		}
		
		int ShellSort(customer *brk_cus) {
			int k = first_incremental_value(this->wait_size);
			int swap_ovt = 0;
			while (k >= 1) {
				int segment = 0;
				while (segment < k) {
					swap_ovt += this->SortSegment(k, segment, brk_cus->next);
					segment++;
				}
				k = k/3;
			}
			return swap_ovt;
		}
		
	public:	
		imp_res() {
			this->serve_size = 0;
			this->cir_head = NULL;
			this->total_size = 0;
			this->seq_head = NULL;
			this->seq_tail = NULL;
			this->wait_size = 0;
			this->top_queue = NULL;
		};
		
		void RED(string name, int energy) {
			if (energy == 0) return;
			if (this->serve_size >= MAXSIZE && this->wait_size >= MAXSIZE) return;	// full slot

			bool wait_to_serve = false;
			if (this->serve_size < MAXSIZE && this->wait_size > 0) {
				wait_to_serve = true;
			} else {
				customer *check_duplicate = this->seq_head;
				while (check_duplicate != NULL) {
					if (check_duplicate->name == name) return;	// Check duplicate customer name
					check_duplicate = check_duplicate->next;
				}
			}
			
			if (this->serve_size >= MAXSIZE) {
				this->enqueue(name, energy);
				this->addSeqList(name, energy);
				return;
			}
			
			if (this->serve_size == 0) {
				this->firstCustomer(name, energy);
			} else if (this->serve_size < MAXSIZE/2) {
				if (energy >= this->cir_head->energy)
					this->serveCustomer(true, name, energy, this->cir_head->name);
				else
					this->serveCustomer(false, name, energy, this->cir_head->name);
			} else {
				customer *ref = this->cir_head;
				customer *tmp = ref;
				int res = energy - tmp->energy;
				for (int i = 0; i < this->serve_size; i++) {
					if (abs(res) < abs(energy - tmp->energy)) {
						res = energy - tmp->energy;
						ref = tmp;
					}
					tmp = tmp->next;
				}
				if (res < 0) this->serveCustomer(false, name, energy, ref->name);
				else this->serveCustomer(true, name, energy, ref->name);
			}
			if (!wait_to_serve) {
				this->addSeqList(name, energy);
			}		
		}
		void BLUE(int num) {
			if (num >= this->serve_size) {
				while (this->serve_size > 0) {
					string rm_name = this->cir_head->name;
					this->byeCustomer(rm_name);
					this->rmSeqList(rm_name);
				}
			} else {
				customer *tmp = this->seq_head;
				string rm_name = tmp->name;
				int ret = -1;
				for (int i = 0; i < num; i++) {
					do {
						rm_name = tmp->name;
						ret = this->byeCustomer(rm_name);
						tmp = tmp->next;
					} while (ret != 0 && tmp != NULL);
					this->rmSeqList(rm_name);
				}
			}
			while (this->serve_size < MAXSIZE && this->wait_size > 0) {
				this->RED(this->top_queue->name, this->top_queue->energy);
				this->dequeue();
			}
		}
		void PURPLE() {
			if (this->wait_size <= 0) return;
			customer *highest = this->top_queue;
			customer *tmp = this->top_queue;
			while (tmp != NULL) {
				if (abs(highest->energy) < abs(tmp->energy)) highest = tmp;
				tmp = tmp->next;
			}
			int swap_total = this->ShellSort(highest);
			BLUE(swap_total % MAXSIZE);
		}
		void REVERSAL() {
			if (this->serve_size == 0) return;
			customer *positive_prev = this->cir_head;
			customer *positive_next = this->cir_head->next;
			customer *negative_prev = this->cir_head;
			customer *negative_next = this->cir_head->next;
			
			/*------Reverse positive values------*/
			int loop_prev = 1;
			while (positive_prev->energy < 0) {
				positive_prev = positive_prev->prev;
				loop_prev++;
				if (loop_prev > this->serve_size) break;
			}
			int loop_next = 1;
			while (positive_next->energy < 0) {
				positive_next = positive_next->next;
				loop_next++;
				if (loop_next > this->serve_size) break;
			}
			if (loop_next <= this->serve_size && loop_prev <= this->serve_size) {
				while (positive_prev != positive_next) {
					int swap_energy = positive_prev->energy;
					string swap_name = positive_prev->name;
					if (swap_name == this->cir_head->name) {
						this->cir_head = positive_next;
					}
					positive_prev->energy = positive_next->energy;
					positive_prev->name = positive_next->name;
					positive_next->energy = swap_energy;
					positive_next->name = swap_name;
					do {
						positive_prev = positive_prev->prev;
					} while (positive_prev->energy < 0);
					if (positive_prev == positive_next) break;
					do {
						positive_next = positive_next->next;
					} while (positive_next->energy < 0);
				}
			}
			
			/*------Reverse negative values------*/
			loop_prev = 1;
			while (negative_prev->energy > 0) {
				negative_prev = negative_prev->prev;
				loop_prev++;
				if (loop_prev > this->serve_size) break;
			}
			loop_next = 1;
			while (negative_next->energy > 0) {
				negative_next = negative_next->next;
				loop_next++;
				if (loop_next > this->serve_size) break;
			}
			if (loop_next <= this->serve_size && loop_prev <= this->serve_size) {
				while (negative_prev != negative_next) {
					int swap_energy = negative_prev->energy;
					string swap_name = negative_prev->name;
					if (swap_name == this->cir_head->name) {
						this->cir_head = negative_next;
					}
					negative_prev->energy = negative_next->energy;
					negative_prev->name = negative_next->name;
					negative_next->energy = swap_energy;
					negative_next->name = swap_name;
					do {
						negative_prev = negative_prev->prev;
					} while (negative_prev->energy > 0);
					if (negative_prev == negative_next) break;
					do {
						negative_next = negative_next->next;
					} while (negative_next->energy > 0);
				}
			}
		}
		void UNLIMITED_VOID() {
			if (this->serve_size < 4) return;
			customer *start = this->cir_head;
			customer *end = start;
			int sub_total = start->energy;
			for (int i = 0; i < 3; i++) {
				end = end->next;
				sub_total += end->energy;
			}
			customer *start_tmp = start;
			customer *end_tmp = end;
			customer *start_rec = start;
			customer *end_rec = end;
			int tmp_total = sub_total;
			int smallest = tmp_total;
			int step_size = 4;
			while (end != start) {
				if (step_size > 4) {
					sub_total += end->energy;
				}
				tmp_total = sub_total;
				start_tmp = start;
				end_tmp = end;
				while (end_tmp->next != start) {
					tmp_total = tmp_total - start_tmp->energy + end_tmp->next->energy;
					start_tmp = start_tmp->next;
					end_tmp = end_tmp->next;
					if (tmp_total <= smallest) {
						smallest = tmp_total;
						start_rec = start_tmp;
						end_rec = end_tmp;
					}
				}
				end = end->next;
				step_size++;
			}
			customer *p = start_rec;
			while (p != end_rec->next) {
				p->print();
				p = p->next;
			}
		}
		void DOMAIN_EXPANSION() {
			if (this->total_size <= 0) return;
			int sum = 0;
			customer *tmp = this->seq_head;
			do {
				sum += tmp->energy;
				tmp = tmp->next;
			} while (tmp != NULL);
			tmp = this->seq_tail;
			string rm_name;
			if (sum >= 0) {
				do {
					if (tmp->energy < 0) {
						rm_name = tmp->name;
						tmp->print();
						tmp = tmp->prev;
						rmSeqList(rm_name);
						byeCustomer(rm_name);
						rmQueue(rm_name);
					} else {
						tmp = tmp->prev;
					}
				} while (tmp != NULL);
			} else {
				do {
					if (tmp->energy > 0) {
						rm_name = tmp->name;
						tmp->print();
						tmp = tmp->prev;
						rmSeqList(rm_name);
						byeCustomer(rm_name);
						rmQueue(rm_name);
					} else {
						tmp = tmp->prev;
					}
				} while (tmp != NULL);
			}
			while (this->serve_size < MAXSIZE && this->wait_size > 0) {
				this->RED(this->top_queue->name, this->top_queue->energy);
				this->dequeue();
			}
		}
		void LIGHT(int num) {
			if (this->serve_size <= 0) return;
			if (num > 0) {
				customer *tmp = this->cir_head;
				int loop = 1;
				while (loop <= this->serve_size && tmp != NULL) {
					tmp->print();
					tmp = tmp->next;
					loop++;
				}
			}
			if (num < 0) {
				customer *tmp = this->cir_head;
				int loop = 1;
				while (loop <= this->serve_size && tmp != NULL) {
					tmp->print();
					tmp = tmp->prev;
					loop++;
				}
			}
			if (num == 0) {
				customer *tmp = this->top_queue;
				while (tmp != NULL) {
					tmp->print();
					tmp = tmp->next;
				}
			}
		}

		~imp_res() {
			this->BLUE(MAXSIZE);
			this->BLUE(MAXSIZE);
		}
};