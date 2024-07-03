#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczać pomiędzy #ifdef a #endif.
*/

#ifdef Kol_2

enum class Stan { dopuszczony = 0, niedopuszczony };

class Wlasciciel
{
private:
	const char* nazwa;
public:
	Wlasciciel(const char* nazwa)
		: nazwa(nazwa)
	{
		if (nazwa == nullptr) {
			throw invalid_argument("Nazwa właściciela nie może być pusta");
		}
	};
};

class Samochod
{
private:
	double WAR_POCZ = 1000;
	static Samochod* wzorzec;
protected:
	const char* rejestracja;
	int licznik;
	Stan stan;
	Wlasciciel* wlasciciel;
public:
	Samochod(const char* rejestracja, int licznik, Stan stan, Wlasciciel* wlasciciel)
		: rejestracja(rejestracja), licznik(licznik), stan(stan), wlasciciel(wlasciciel)
	{
		if (rejestracja == nullptr) {
			throw invalid_argument("Rejestracja nie może być pusta");
		}
		if (licznik < 0) {
			throw invalid_argument("Stan licznika nie może być ujemny");
		}
		if (stan != Stan::niedopuszczony && stan != Stan::dopuszczony) {
			throw invalid_argument("Stan jest nieprawidłowy");
		}
	};
	~Samochod() {};

	//Getery:
	const char* getRejestracja() const { return rejestracja; }
	int getLicznik() const { return licznik; }
	Stan getStan() const { return stan; }
	Wlasciciel* getWlasciciel() const { return wlasciciel; }
	static Samochod* getWzor() { return wzorzec; }
	//Setery
	void setLicznik(int licznik){
		if (licznik < 0) {
			throw invalid_argument("Stan licznika nie może być ujemny");
		}
		this->licznik = licznik;
	}
	static void InsWzor(Samochod* wzor) {
		wzorzec = wzor;
	}

	virtual double zasieg() const { return 800; }

	operator double() {
		double WSP_SPARW = 0;
		if (stan == Stan::dopuszczony) {
			WSP_SPARW = 1.0;
		}
		if (stan == Stan::niedopuszczony) {
			WSP_SPARW = 0.2;
		}
		double wartosc = (WAR_POCZ - 0.2 * licznik) * WSP_SPARW;
		wartosc = wartosc - (wartosc * 0,3);
		if (wartosc < 400) {
			return 400;
		}
		else {
			return wartosc;
		}
	}

	bool operator !=(const Samochod& samochod) const {
		if (abs(getLicznik() - samochod.getLicznik()) > 20000 || getStan() != samochod.getStan()) {
			return 0;
		}
		else {
			return 1;
		}
	}
};
class Samochod_Elektryczny : public Samochod
{
private:
	int bateria;
public:
	Samochod_Elektryczny(const char* rejestracja, int licznik, Stan stan, Wlasciciel* wlasciciel, int bateria)
		: Samochod(rejestracja, licznik, stan, wlasciciel), bateria(bateria)
	{
		if (bateria < 0) {
			throw invalid_argument("Bateria nie może mieć ujemnego naładowania");
		}
		if (bateria > 100) {
			throw invalid_argument("Bateria nie może mieć naładowania większego od 100%");
		}
	};
	~Samochod_Elektryczny() {};

	//Getery:
	int getBateria() const { return bateria; }
	//Setery
	void setBateria(int bateria) {
		this->bateria = bateria;
	}

	double zasieg() const override {
		if (stan == Stan::niedopuszczony) {
			throw invalid_argument("Niedopuszczony do jazdy");
		}
		return 2.5 * bateria;
	}
};
int main()
{
	setlocale(LC_ALL, "");
	try {
		Wlasciciel wlasciciel1("Adam");
		Wlasciciel wlasciciel2("Adam");
		Samochod samochody[] =
		{
			{"PL-300321", 70000, Stan::dopuszczony, &wlasciciel1},
			{"PL-302341", 3000, Stan::dopuszczony,&wlasciciel2},
			{"PL-302312", 80000, Stan::niedopuszczony,&wlasciciel1}
		};
		Samochod wzorcowy("PL-102030", 3000, Stan::dopuszczony, &wlasciciel2);
		Samochod_Elektryczny elektryk[] = {
			{"PL-302321", 100000, Stan::dopuszczony,&wlasciciel1, 30},
			{"PL-301321", 100000, Stan::dopuszczony,&wlasciciel1, 70},
			{"PL-303321", 100000, Stan::dopuszczony,&wlasciciel1, 0}
		};

		cout << "Zasieg samochodu: " << samochody[2].zasieg() << "\n";
		cout << "Zasieg elektryka 1: " << elektryk[0].zasieg() << "\n";
		cout << "Zasieg elektryka 2: " << elektryk[1].zasieg() << "\n";
		cout << "Zasieg elektryka 3: " << elektryk[2].zasieg() << "\n";

		cout << "Konwersja: " << static_cast<double>(samochody[2]) << "\n";

		if ((samochody[0] != samochody[2]) == 1) {
			cout << "Operator != Są identyczne";
		}
		else {
			cout << "Operator != Są różne";
		}
	}
	catch (const invalid_argument& e) {
		cerr << "Błąd: " << e.what();
	}
}

#endif
