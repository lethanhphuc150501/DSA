#include "main.h"

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

		void RED(string name, int energy)
		{
			// if (energy == 0) return;
			// if (this->serve_size == 0) {
			// 	customer *cus = new customer (name, energy, nullptr, nullptr);
			// 	this->serve_size = 1;
			// 	this->cir_head = cus;
			// 	this->wait_size = 0;
			// 	this->top_queue = NULL;
			// } else if (this->serve_size < MAXSIZE/2) {
			// 	customer *cus = new customer (name, energy, nullptr, nullptr);
				
			// }
			cout << name << " " << energy << endl;
			cout << MAXSIZE << endl;
			// this->status = 0;
			
		}
		void BLUE(int num)
		{
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