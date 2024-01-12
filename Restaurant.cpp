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
		customer* cir_head;		// Head for circle list

		bool status;			// Note status = 1 when last action is removing a customer
		customer last_rm_cus;	// Use this info if status = 1

		int total_size;			// Number of all customer in the restaurant
		customer* seq_head;		// Head of sequence list
		customer* seq_tail;		// Tail of sequence list
		
		int wait_size;			// Number of customer waiting
		customer* top_queue;	// Head for waiting queue
		customer* bot_queue;	// Tail for waiting queue
	public:	
		imp_res() {
			this->serve_size = 0;
			this->cir_head = NULL;
			this->status = 0;
			this->total_size = 0;
			this->seq_head = NULL;
			this->seq_tail = NULL;
			this->wait_size = 0;
			this->top_queue = NULL;
		};

		void addSeqList(string name, int energy) {
			if (this->total_size == 0) {
				customer *cp_cus = new customer (name, energy, nullptr, nullptr);
				this->seq_head = cp_cus;
				this->seq_tail = cp_cus;
			} else {
				customer *cp_cus = new customer (name, energy, this->seq_tail, nullptr);
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
				delete tmp;
				this->seq_head = NULL;
				this->seq_tail = NULL;
				return;
			}
			if (name == this->seq_head->name) {
				customer* tmp = this->seq_head;
				this->seq_head = tmp->next;
				this->seq_head->prev = NULL;
				delete tmp;
				return;
			}
			if (name == this->seq_tail->name) {
				customer* tmp = this->seq_tail;
				this->seq_tail = tmp->prev;
				this->seq_tail->next = NULL;
				delete tmp;
				return;
			}
			customer* tmp = this->seq_head;
			while (tmp->name != name) {
				tmp = tmp->next;
			}
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
		}

		void enqueue(string name, int energy) {
			if (this->wait_size == 0) {
				customer *cus = new customer (name, energy, nullptr, nullptr);
				this->top_queue = cus;
				this->bot_queue = cus;
			} else {
				customer *cus = new customer (name, energy, this->bot_queue, nullptr);
				this->bot_queue->next = cus;
				this->bot_queue = cus;
			}
			this->wait_size += 1;
		}

		void dequeue() {
			if (this->wait_size <= 1) {
				customer *tmp = this->top_queue;
				this->wait_size = 0;
				delete tmp;
				this->top_queue = NULL;
				this->bot_queue = NULL;
			} else {
				customer *tmp = this->top_queue;
				this->wait_size -= 1;
				this->top_queue = tmp->next;
				this->top_queue->prev = NULL;
				delete tmp;
			}
		}

		void firstCustomer(string name, int energy) {
			customer *cus = new customer(name, energy, NULL, NULL);
			cus->next = cus;
			cus->prev = cus;
			this->serve_size = 1;
			this->cir_head = cus;
			this->status = false;
		}

		void serveCustomer(bool clockwise, string name, int energy, string name_ref) {
			customer *tmp = this->cir_head;
			while (tmp->name != name_ref) {		// unsafe, add variable to count number of loops later
				tmp = tmp->next;
			}
			if (clockwise == true) {
				customer *cus = new customer(name, energy, tmp, tmp->next);
				tmp->next->prev = cus;
				tmp->next = cus;
				this->cir_head = cus;
			} else {
				customer *cus = new customer(name, energy, tmp->prev, tmp);
				tmp->prev->next = cus;
				tmp->prev = cus;
				this->cir_head = cus;
			}
			this->serve_size += 1;
			this->status = false;
		}

		void byeCustomer(string name) {
			if (this->serve_size <= 1) {
				customer *tmp = this->cir_head;
				this->cir_head = NULL;
				this->serve_size = 0;
				delete tmp;
				this->status = false;
				return;
			}
			customer *rm_it = this->cir_head;
			while (rm_it->name != name) {		// unsafe, add variable to count number of loops later
				rm_it = rm_it->next;
			}
			if (rm_it == this->cir_head) {
				this->cir_head = this->cir_head->next;
			}
			customer *tmp = rm_it->next;
			rm_it->prev->next = tmp;
			tmp->prev = rm_it->prev;
			this->status = true;
			this->last_rm_cus.energy = rm_it->energy;
			this->last_rm_cus.name = rm_it->name;
			this->last_rm_cus.next = rm_it->next;
			this->last_rm_cus.prev = rm_it->prev;
			delete rm_it;
			this->serve_size -= 1;
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
				while (walker != NULL && abs(neo_energy) > abs(walker->energy)) {	// Insection Sort
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
				if (this->status == false) {
					if (energy >= this->cir_head->energy)
						this->serveCustomer(true, name, energy, this->cir_head->name);
					else
						this->serveCustomer(false, name, energy, this->cir_head->name);
				} else {
					this->serveCustomer(false, name, energy, this->last_rm_cus.next->name);
				}
			} else {
				customer *ref = this->status ? this->last_rm_cus.next : this->cir_head;
				customer *tmp = ref;
				int res = abs(energy) - abs(tmp->energy);
				for (int i = 0; i < this->serve_size; i++) {
					if (abs(res) < abs(abs(energy) - abs(tmp->energy))) {
						res = abs(energy) - abs(tmp->energy);
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
			cout << name << " " << energy << endl;
			cout << MAXSIZE << endl;			
		}
		void BLUE(int num) {
			if (num >= this->serve_size) {
				while (this->serve_size > 0) {
					string rm_name = this->cir_head->name;
					this->byeCustomer(rm_name);
					this->rmSeqList(rm_name);
				}
			} else {
				for (int i = 0; i < num; i++) {
					string rm_name = this->seq_head->name;
					this->byeCustomer(rm_name);
					this->rmSeqList(rm_name);
				}
			}
			while (this->serve_size < MAXSIZE && this->wait_size > 0) {
				this->RED(this->top_queue->name, this->top_queue->energy);
				this->dequeue();
			}
			cout << "blue "<< num << endl;
		}
		void PURPLE() {
			customer *highest = this->top_queue;
			customer *tmp = this->top_queue;
			while (tmp != NULL) {
				if (abs(highest->energy) < abs(tmp->energy)) highest = tmp;
				tmp = tmp->next;
			}
			int swap_total = this->ShellSort(highest);
			tmp = this->top_queue;
			int s_energy = 0;
			customer *seq_tmp = this->seq_head;
			while (tmp != highest) {
				if (abs(tmp->energy) == abs(tmp->next->energy)) {
					s_energy = abs(tmp->energy);
					seq_tmp = this->seq_head;
find_in_seqlist:
					while (seq_tmp != NULL && abs(seq_tmp->energy) != s_energy) {
						seq_tmp = seq_tmp->next;
					}
					if (seq_tmp == NULL) {
						cout << "Error: Invalid customer in waiting queue\n";
						return;
					}
					tmp->energy = seq_tmp->energy;
					tmp->name = seq_tmp->name;
					if (tmp->next != highest && abs(tmp->next->energy) == s_energy) {
						tmp = tmp->next;
						seq_tmp = seq_tmp->next;
						goto find_in_seqlist; 
					}
				}
				tmp = tmp->next;
			}
			if (abs(tmp->energy) == s_energy) {
				do {
					seq_tmp = seq_tmp->next;
				} while (seq_tmp != NULL && abs(seq_tmp->energy) != s_energy);
				if (seq_tmp != NULL) {
					tmp->energy = seq_tmp->energy;
					tmp->name = seq_tmp->name;
				}
			}
			BLUE(swap_total % MAXSIZE);
			cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
		}
};