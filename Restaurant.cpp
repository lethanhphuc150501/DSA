#include "main.h"

int abs(int num) {
	if (num > 0) return num;
	else return -num;
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
		void PURPLE()
		{
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