#include <iostream>

using namespace std;

class Base {
public:
	static int people_on_base;
	static int vehicles_on_base;
	static double petrol_on_base;
	static double goods_on_base;

	static void Output() {
		cout << "People on base: " << people_on_base << endl;
		cout << "Vehicles on base: " << vehicles_on_base << endl;
		cout << "Petrol on base: " << petrol_on_base << endl;
		cout << "Goods on base: " << goods_on_base << endl;
	}
};

int Base::people_on_base = 5;
int Base::vehicles_on_base = 3;
double Base::petrol_on_base = 75.3;
double Base::goods_on_base = 34.2;

class Vehicle {
protected:
	double petrol_a;
	double tank;
public:
	Vehicle(double petrol_amount, double tank_amount) : petrol_a(petrol_amount), tank(tank_amount) {
	}
	double getTankVolume() {
		cout << "Tank volume: ";
		return tank;
	}
	double getPetrolAmount() {
		cout << "Petrol amount: ";
		return petrol_a;
	}
	void arrive() {
		Base::people_on_base++;
		Base::vehicles_on_base++;
		cout << "Arrived" << endl;
	}
	bool leave() {
		if (Base::people_on_base > 0 && Base::vehicles_on_base > 0 && Base::petrol_on_base >= (tank - petrol_a)) {
			Base::petrol_on_base -= tank - petrol_a;
			petrol_a = tank;
			Base::vehicles_on_base--;
			Base::people_on_base--;
			return true;
		}
		else {
			return false;
		}
	}
};

class Bus : public Vehicle {
private:
	int people_amount;
	int max_people_amount;
public:
	Bus(int people, int max_people, double petrol, double max_petrol) : people_amount(people), max_people_amount(max_people), Vehicle(petrol, max_petrol) {}
	int getPeopleCount() {
		cout << "People amount: ";
		return people_amount;
	}
	int getMaxPeople() {
		cout << "Max people amount: ";
		return max_people_amount;
	}
	void arrive() {
		Vehicle::arrive();
		Base::people_on_base += people_amount;
	}
	bool leave() {
		if (Base::people_on_base > 0 && Base::vehicles_on_base > 0 && Base::petrol_on_base >= (tank - petrol_a) && Base::people_on_base >= (max_people_amount - people_amount)) {
			Base::petrol_on_base -= tank - petrol_a;
			petrol_a = tank;
			Base::vehicles_on_base--;
			Base::people_on_base--;
			Base::people_on_base -= max_people_amount - people_amount;
			people_amount = max_people_amount;
			return true;
		}
		else {
			return false;
		}
	}
};

class Truck : public Vehicle {
private:
	double load_amount;
	double max_load_amount;
public:
	Truck(double load, double max_load, double petrol, double max_petrol) : Vehicle(petrol, max_petrol) {
		load_amount = load;
		max_load_amount = max_load;
	}
	double getCurrentLoad() {
		cout << "Load amount: ";
		return load_amount;
	}
	double getMaxLoad() {
		cout << "Max load amount: ";
		return max_load_amount;
	}
	double get() {
		return tank;
	}
	void arrive() {
		Vehicle::arrive();
		Base::goods_on_base += load_amount;
	}
	bool leave() {
		if (Base::people_on_base > 0 && Base::vehicles_on_base > 0 && Base::petrol_on_base >= (tank - petrol_a) && Base::goods_on_base >= max_load_amount - load_amount) {
			Base::petrol_on_base -= tank - petrol_a;
			petrol_a = tank;
			Base::vehicles_on_base--;
			Base::people_on_base--;
			Base::goods_on_base -= max_load_amount - load_amount;
			load_amount = max_load_amount;
			return true;
		}
		else {
			return false;
		}
	}
};

int main() {
	Vehicle v1(10.0, 50.0);
	Bus b1(20, 50, 15.0, 60.0);
	Truck t1(5.0, 20.0, 20.0, 80.0);

	v1.arrive();
	b1.arrive();
	t1.arrive();
	Base::Output();

	if (v1.leave()) {
		cout << "Vehicle left the base." << endl;
	}
	else {
		cout << "Vehicle could not leave the base." << endl;
	}

	if (b1.leave()) {
		cout << "Bus left the base." << endl;
	}
	else {
		cout << "Bus could not leave the base." << endl;
	}
	if (t1.leave()) {
		cout << "Truck left the base." << endl;
	}
	else {
		cout << "Truck could not leave the base." << endl;
	}

	Base::Output();
}