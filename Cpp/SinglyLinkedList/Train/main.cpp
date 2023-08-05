#include <iostream>

using namespace std;

class Train {
public:
	class TrainCar;
private:
	TrainCar* head;
	TrainCar* tail;
	int size;
public:
	class TrainCar {
	private:
		int remainingSpace;
		TrainCar* next;
		friend class Train;
	public:
		TrainCar() { this->next = NULL; }
		TrainCar(int remainingSpace, TrainCar* next = NULL) {
			this->remainingSpace = remainingSpace;
			this->next = next;
		}
	};
	Train() {
		this->head = new TrainCar(0);
		this->tail = this->head;
		this->size = 1;
	}
	void add(int initSpace)
	{
		TrainCar* pNew = new TrainCar(initSpace);
		this->tail->next = pNew;
		this->tail = pNew;
		this->size++;
	}
	int allocate(int containerSize);
	int totalRemainingSpace();
};

int Train::allocate(int containerSize) {
	TrainCar* temp = this->head->next;
	TrainCar* min = new TrainCar(0);
	bool rec = false;
	int index = 0;
	for (int i = 1; i < this->size; i++)
	{
		if (temp->remainingSpace >= containerSize)
		{
			if (rec == false)
			{
				rec = true;
				min = temp;
				index = i;
			}
			else if (temp->remainingSpace < min->remainingSpace)
			{
				min = temp;
				index = i;
			}			
		}
		temp = temp->next;
	}
	if (rec == true)
	{
		min->remainingSpace -= containerSize;
		return index;
	}
	else
	{
		return -1;
	}
}

int Train::totalRemainingSpace() {
	int sum = 0;
	TrainCar* temp = this->head->next;
	for (int index = 1; index < this->size; index++)
	{
		sum += temp->remainingSpace;
		temp = temp->next;
	}
	return sum;
}

int main()
{
	Train* t = new Train();
	t->add(200); t->add(400); t->add(300); ; t->add(600); t->add(500);
	t->add(100);
	cout << t->allocate(390) << "\n";
	cout << t->allocate(590) << "\n";
	cout << t->totalRemainingSpace() << "\n";
	cout << t->allocate(510) << "\n";
	cout << t->allocate(10) << "\n";
	return 0;
}