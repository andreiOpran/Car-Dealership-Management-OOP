/*

IDE: Visual Studio
Platform toolset: Visual Studio 2022 (v143)

*/

#include <iostream>
#include <cstring>
#include <string>
#include <string>
#include <typeinfo>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <sstream>

using namespace std;



// --------- CLASA OBSERVER ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T>
class Observer
{
public:
	virtual void notify(const T&, const string&) = 0;
};

// --------- CLASA CONSOLEOBSERVER ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T>
class ConsoleObserver : public Observer<T>
{
	void notify(const T& obj, const string& message) override
	{
		cout << endl << message << endl;
	}
};

// --------- CLASA SUBJECT ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T>
class Subject
{
protected:

	static vector<Observer<T>*> observers;

public:

	static void addObserver(Observer<T>* observer)
	{
		observers.push_back(observer);
	}

	static void notifyObservers(const T& obj, const string& message)
	{
		for (Observer<T>* observer : observers)
		{
			observer->notify(obj, message);
		}
	}

};

// --------- CLASA MYEXCEPTION ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class MyException : public exception
{
public:
	virtual const char* what() const throw() {
		return "\nIntrodu doar cifre!\n";
	}
} myEx;


class Vehicul;

// --------- CLASA IOINTERFACEVEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class IOInterfaceVehicul
{
public:
	virtual ostream& afisareVehicul(ostream&) const = 0;
	virtual istream& citireVehicul(istream&) = 0;
};

// --------- CLASA INTERFACEVEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class InterfaceVehicul
{
	virtual double valoareaRealaVehicul() const = 0;
	virtual double costFolosireSiIntretinere() const = 0;
	virtual Vehicul* clone() const = 0;
};


// --------- CLASA VEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Vehicul : public IOInterfaceVehicul, public InterfaceVehicul
{

protected:

	const int idVehicul;
	static int nrVehicule;
	string marca;
	string model;
	int anFabricatie;
	
	int nrInserariIstoricRulaj;
	map <string, int> istoricRulaj; // data, rulaj in km
	
	int nrDotari;
	set <string> dotari; // am folosit set pentru a nu avea duplicate

	double pret;

	// ?
	//int nrInserariIstoricDaune;
	//list <string> istoricDaune; // descriere dauna

public:

	// CONSTRUCTOR FARA PARAMETRI
	Vehicul();

	// CONSTRUCTOR CU PARAMETRI
	Vehicul(string, string, int, int, map <string, int>, int, set <string>, double);

	// COPY CONSTRUCTOR
	Vehicul(const Vehicul&);

	// OPERATORUL =
	Vehicul& operator=(const Vehicul&);

	// DESTRUCTOR
	virtual ~Vehicul();

	// OPERATORUL >>
	istream& citireVehicul(istream&) override;

	// OPERATORUL <<
	ostream& afisareVehicul(ostream&) const override;

	// FUNCTIE VALOARE REALA VEHICUL
	virtual double valoareaRealaVehicul() const override;

	// FUNCTIE COST FOLOSIRE SI INTRETINERE
	virtual double costFolosireSiIntretinere() const override;

	// FUNCTIE CLONE
	virtual Vehicul* clone() const override;

	// GET PRET
	double getPret() const;

	// SET PRET
	void setPret(double pret);

	// SET MARCA
	void setMarca(string marca);

	// SET MODEL
	void setModel(string model);

	// SET AN FABRICATIE
	void setAnFabricatie(int anFabricatie);

	// INSERARE IN ISTORIC RULAJ
	void inserareIstoricRulaj(string data, int rulaj);
	
	// INSERARE DOTARE
	void inserareDotare(string dotare);
	
	// GET MARCA
	string getMarca() const
	{
		return marca;
	}

	// GET MODEL
	string getModel() const
	{
		return model;
	}

};

// CONSTRUCTOR FARA PARAMETRI
Vehicul::Vehicul() : idVehicul(++nrVehicule + 1000), marca("Necunoscut"), model("Necunoscut"),
anFabricatie(0), nrInserariIstoricRulaj(0), istoricRulaj(), nrDotari(0), dotari(), pret(0) {}

// CONSTRUCTOR CU PARAMETRI
Vehicul::Vehicul(string marca, string model, int anFabricatie, int nrInserariIstoricRulaj, map <string, int> istoricRulaj, int nrDotari, set <string> dotari, double pret) :
				idVehicul(++nrVehicule + 1000), marca(marca), model(model), anFabricatie(anFabricatie), nrInserariIstoricRulaj(nrInserariIstoricRulaj), istoricRulaj(istoricRulaj),
				nrDotari(nrDotari), dotari(dotari), pret(pret) {}

// COPY CONSTRUCTOR
Vehicul::Vehicul(const Vehicul& obj) : idVehicul(obj.idVehicul), marca(obj.marca), model(obj.model), anFabricatie(obj.anFabricatie), nrInserariIstoricRulaj(obj.nrInserariIstoricRulaj), 
										istoricRulaj(obj.istoricRulaj), nrDotari(obj.nrDotari), dotari(obj.dotari), pret(obj.pret) {}

// OPERATORUL =
Vehicul& Vehicul::operator=(const Vehicul& obj)
{
	if (this != &obj)
	{
		this->marca = obj.marca;
		this->model = obj.model;
		this->anFabricatie = obj.anFabricatie;
		this->nrInserariIstoricRulaj = obj.nrInserariIstoricRulaj;
		this->istoricRulaj = obj.istoricRulaj;
		this->nrDotari = obj.nrDotari;
		this->dotari = obj.dotari;
		this->pret = obj.pret;
	}
	return *this;
}

// DESTRUCTOR
Vehicul::~Vehicul() {}


int stoiExceptionCitire(const string& sir)
{
	try
	{
		size_t lastChar;
		int numar = stoi(sir, &lastChar);
		if (lastChar != sir.length())
		{
			throw invalid_argument("");
		}
		return numar;
	}
	catch (const invalid_argument& e)
	{
		throw myEx;
		return 0;
	}
	catch (...)
	{
		throw range_error("");
		return 0;
	}
}

double stodExceptionCitire(const string& sir)
{
	try
	{
		size_t lastChar;
		double numar = stod(sir, &lastChar);
		if (lastChar != sir.length())
		{
			throw invalid_argument("");
		}
		return numar;
	}
	catch (const invalid_argument& e)
	{
		throw myEx;
		return 0;
	}
	catch (...)
	{
		throw range_error("");
		return 0;
	}
}

// OPERATORUL >>
istream& Vehicul::citireVehicul(istream& in)
{
	istoricRulaj.clear();
	dotari.clear();

	cout << "Marca: ";
	in >> marca;
	cout << "Model: ";
	in >> model;
	

	//int anFabricatie;
	
	while (true)
	{
		string sir;
		cout << "An fabricatie: ";
		getline(in, sir);
		if(sir == "")
			getline(in, sir);
		try
		{
			anFabricatie = stoiExceptionCitire(sir);
			if (to_string(anFabricatie) != sir)
				throw myEx;
			else
				if(anFabricatie < 1700)
				throw out_of_range("\nAnul de fabricatie nu poate fi mai mic ca 1700!\n");
			break;
		}
		catch (MyException& e)
		{
			cout << e.what();
		}
		catch (const out_of_range& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nComanda invalida.\n";
		}
	}



	/*cout << "Numar inserari in istoricul rulajului: ";
	in >> nrInserariIstoricRulaj;*/

	while (true)
	{
		string sir;
		cout << "Numar inserari in istoricul rulajului: ";
		getline(in, sir);
		if (sir == "")
			getline(in, sir);
		try
		{
			nrInserariIstoricRulaj = stoiExceptionCitire(sir);
			if (to_string(nrInserariIstoricRulaj) != sir)
				throw myEx;
			else
				if (nrInserariIstoricRulaj < 0)
					throw out_of_range("\nNumarul de inserari in istoricul rulajului nu poate fi negativ!\n");
			break;
		}
		catch (MyException& e)
		{
			cout << e.what();
		}
		catch (const out_of_range& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nComanda invalida.\n";
		}
	}

	if (nrInserariIstoricRulaj)
	{
		//cout << "\nData si rulajul (km), separate printr-un spatiu:\n";
		for (int i = 0; i < nrInserariIstoricRulaj; i++)
		{
			cout << "\nInserarea " << i + 1 << "/" << nrInserariIstoricRulaj << ": ";
			string data;
			int rulaj;
			/*in >> data >> rulaj;
			istoricRulaj.insert({ data, rulaj });*/

			while (true)
			{
				string comandaStr;
				cout << "\nData: ";
				in >> data;
				cout << "\nRulaj (km): ";
				getline(in, comandaStr);
				if(comandaStr == "")
					getline(in, comandaStr);
				try
				{
					rulaj = stoiExceptionCitire(comandaStr);
					if (to_string(rulaj) != comandaStr)
						throw myEx;
					else
						if (rulaj < 0)
							throw out_of_range("\nRulajul nu poate fi negativ!\n");
					break;
				}
				catch (MyException& e)
				{
					cout << e.what();
				}
				catch (const out_of_range& e)
				{
					cout << e.what();
				}
				catch (...)
				{
					cout << "\nComanda invalida.\n";
				}
			}
			istoricRulaj.insert({ data, rulaj });
		}
	}
	/*cout << "Numar dotari: ";
	in >> nrDotari;*/

	while (true)
	{
		string sir;
		cout << "Numar dotari: ";
		getline(in, sir);
		if (sir == "")
			getline(in, sir);
		try
		{
			nrDotari = stoiExceptionCitire(sir);
			if (to_string(nrDotari) != sir)
				throw myEx;
			else
				if (nrDotari < 0)
					throw out_of_range("\nNumarul de dotari nu poate fi negativ!\n");
			break;
		}
		catch (MyException& e)
		{
			cout << e.what();
		}
		catch (const out_of_range& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nComanda invalida.\n";
		}

	}

	if (nrDotari)
	{
		//in.get();
		for (int i = 0; i < nrDotari; i++)
		{
			cout << "Dotarea " << i + 1 << "/" << nrDotari << ": ";
			string dotare;
			getline(in, dotare);
			dotari.insert(dotare);
		}
	}
	/*cout << "Pret: ";
	in >> pret;*/

	while (true)
	{
		string sir;
		cout << "Pret: ";
		getline(in, sir);
		if (sir == "")
			getline(in, sir);
		try
		{
			pret = stodExceptionCitire(sir);
			
				if (pret < 0)
					throw out_of_range("\nPretul nu poate fi negativ!\n");
			break;
		}
		catch (MyException& e)
		{
			cout << e.what();
		}
		catch (const out_of_range& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nComanda invalida.\n";
		}
	}

	return in;
}
istream& operator >>(istream& in, Vehicul& obj)
{
	return obj.citireVehicul(in);
}

// OPERATORUL <<
ostream& Vehicul::afisareVehicul(ostream& out) const
{
	int poz = 1;

	out << "\nID: " << idVehicul << "\n";
	out << "Marca: " << marca << "\n";
	out << "Model: " << model << "\n";
	out << "An fabricatie: " << anFabricatie << "\n";
	out << "Istoric rulaj:\n";
	for (pair<string, int> p : istoricRulaj)
	{
		out << poz++ << ". " << p.first << " " << p.second << " km\n";
	}
	poz = 1;
	out << "Dotari:\n";
	for(string s : dotari)
	{
		out << "Dotarea " << poz++ << ": " << s << "\n";
	}
	out << "Pret: " << pret << "\n";
	return out;
}
ostream& operator <<(ostream& out, const Vehicul& obj)
{
	return obj.afisareVehicul(out);
}

// FUNCTIE VALOARE REALA VEHICUL
double Vehicul::valoareaRealaVehicul() const
{
	int vechime = 2024 - anFabricatie;
	double indiceVechime = 1 - (0.1 * vechime);
	double indiceMarca = marca == "Audi" || marca == "Mercedes-Benz" || marca == "BMW" ? 1.2 : 1.0;
	if (pret * indiceVechime * indiceMarca > pret)
		return pret;
	else
		return pret * indiceVechime * indiceMarca;
}

// FUNCTIE COST FOLOSIRE SI INTRETINERE
double Vehicul::costFolosireSiIntretinere() const
{
	double cost = 0;
	for (pair<string, int> p : istoricRulaj)
	{
		if (p.second > 200000)
			cost += 0.1 * pret;
	}
	return cost;
}

// FUNCTIE CLONE
Vehicul* Vehicul::clone() const
{
	return new Vehicul(*this);
}

// GET PRET
double Vehicul::getPret() const
{
	return pret;
}

// SET PRET
void Vehicul::setPret(double pret)
{
	this->pret = pret;
}

// SET MARCA
void Vehicul::setMarca(string marca)
{
	this->marca = marca;
}

// SET MODEL
void Vehicul::setModel(string model)
{
	this->model = model;
}

// SET AN FABRICATIE
void Vehicul::setAnFabricatie(int anFabricatie)
{
	this->anFabricatie = anFabricatie;
}

// INSERARE IN ISTORIC RULAJ
void Vehicul::inserareIstoricRulaj(string data, int rulaj)
{
	istoricRulaj.insert({ data, rulaj });
}

// INSERARE DOTARE
void Vehicul::inserareDotare(string dotare)
{
	dotari.insert(dotare);
}



// --------- CLASA VEHICULCARBURANT ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class VehiculCarburant : public Vehicul 
{
protected:

	string tipCarburant;
	double consum;

public:

	// CONSTRUCTOR FARA PARAMETRI
	VehiculCarburant();

	// CONSTRUCTOR CU PARAMETRI
	VehiculCarburant(string, string, int, int, map <string, int>, int, set <string>, double, string, double);

	// COPY CONSTRUCTOR
	VehiculCarburant(const VehiculCarburant&);

	// OPERATORUL =
	VehiculCarburant& operator=(const VehiculCarburant&);

	// DESTRUCTOR
	~VehiculCarburant();

	// OPERATORUL >>
	istream& citireVehicul(istream&) override;

	// OPERATORUL <<
	ostream& afisareVehicul(ostream&) const override;

	// FUNCTIE VALOARE REALA VEHICUL
	double valoareaRealaVehicul() const override;

	// FUNCTIE COST FOLOSIRE SI INTRETINERE
	double costFolosireSiIntretinere() const override;

	// FUNCTIE CLONE
	Vehicul* clone() const override;

	// SET TIP CARBURANT
	void setTipCarburant(string tipCarburant);

	// SET CONSUM
	void setConsum(double consum);
	
};

// CONSTRUCTOR FARA PARAMETRI
VehiculCarburant::VehiculCarburant() : Vehicul(), tipCarburant("Necunoscut"), consum(0) {}
// CONSTRUCTOR CU PARAMETRI
VehiculCarburant::VehiculCarburant(string marca, string model, int anFabricatie, int nrInserariIstoricRulaj, map <string, int> istoricRulaj, int nrDotari, set <string> dotari, double pret, string tipCarburant, double consum) :
	Vehicul(marca, model, anFabricatie, nrInserariIstoricRulaj, istoricRulaj, nrDotari, dotari, pret), tipCarburant(tipCarburant), consum(consum) {}

// COPY CONSTRUCTOR
VehiculCarburant::VehiculCarburant(const VehiculCarburant& obj) : Vehicul(obj), tipCarburant(obj.tipCarburant), consum(obj.consum) {}

// OPERATORUL =
VehiculCarburant& VehiculCarburant::operator=(const VehiculCarburant& obj)
{
	if (this != &obj)
	{
		Vehicul::operator=(obj);
		this->tipCarburant = obj.tipCarburant;
		this->consum = obj.consum;
	}
	return *this;
}

// DESTRUCTOR
VehiculCarburant::~VehiculCarburant() {}

// OPERATORUL >>
istream& VehiculCarburant::citireVehicul(istream& in)
{
	Vehicul::citireVehicul(in);
	cout << "Tip carburant: ";
	in >> tipCarburant;
	/*cout << "Consum: ";
	in >> consum;*/

	while (true)
	{
		string sir;
		cout << "Consum: ";
		getline(in, sir);
		if (sir == "")
			getline(in, sir);
		try
		{
			consum = stodExceptionCitire(sir);
			if (consum < 0)
				throw out_of_range("\nConsumul nu poate fi negativ!\n");
			break;
		}
		catch (MyException& e)
		{
			cout << e.what();
		}
		catch (const out_of_range& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nComanda invalida.\n";
		}
	}

	return in;
}
istream& operator >>(istream& in, VehiculCarburant& obj)
{
	return obj.citireVehicul(in);
}

// OPERATORUL <<
ostream& VehiculCarburant::afisareVehicul(ostream& out) const
{
	Vehicul::afisareVehicul(out);
	out << "Tip carburant: " << tipCarburant << "\n";
	out << "Consum: " << consum << "\n";
	return out;
}
ostream& operator <<(ostream& out, const VehiculCarburant& obj)
{
	return obj.afisareVehicul(out);
}

// FUNCTIE VALOARE REALA VEHICUL
double VehiculCarburant::valoareaRealaVehicul() const
{
	double valoare = Vehicul::valoareaRealaVehicul();
	if (tipCarburant == "benzina")
		valoare += 0.1 * valoare;
	else
		if (tipCarburant == "motorina")
			valoare += 0.2 * valoare;
	return valoare;
}

// FUNCTIE COST FOLOSIRE SI INTRETINERE
double VehiculCarburant::costFolosireSiIntretinere() const
{
	double cost = Vehicul::costFolosireSiIntretinere();
	if (consum > 10)
		cost += 0.1 * pret;
	return cost;
}

// FUNCTIE CLONE
Vehicul* VehiculCarburant::clone() const
{
	return new VehiculCarburant(*this);
}

// SET TIP CARBURANT
void VehiculCarburant::setTipCarburant(string tipCarburant)
{
	this->tipCarburant = tipCarburant;
}

// SET CONSUM
void VehiculCarburant::setConsum(double consum)
{
	this->consum = consum;
}

// --------- CLASA VEHICULHIBRID ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class VehiculHibrid : public VehiculCarburant
{
	char tipHibrid; // P - plug-in, M - mild
	double autonomieElectricPlugIn; // doar pentru tipul P
	double timpIncarcarePlugIn; // doar pentru tipul P

public:

	// CONSTRUCTOR FARA PARAMETRI
	VehiculHibrid();

	// CONSTRUCTOR CU PARAMETRI
	VehiculHibrid(string, string, int, int, map <string, int>, int, set <string>, double, string, double, char, double, double);

	// COPY CONSTRUCTOR
	VehiculHibrid(const VehiculHibrid&);

	// OPERATORUL =
	VehiculHibrid& operator=(const VehiculHibrid&);

	// DESTRUCTOR
	~VehiculHibrid();

	// OPERATORUL >>
	istream& citireVehicul(istream&) override;

	// OPERATORUL <<
	ostream& afisareVehicul(ostream&) const override;

	// FUNCTIE VALOARE REALA VEHICUL
	double valoareaRealaVehicul() const override;

	// FUNCTIE COST FOLOSIRE SI INTRETINERE
	double costFolosireSiIntretinere() const override;
	
	// FUNCTIE CLONE
	Vehicul* clone() const override;

	// SET AUTONOMIE ELECTRIC PLUG-IN
	void setAutonomieElectric(double autonomieElectricPlugIn);

	// SET TIMP INCARCARE PLUG-IN
	void setTimpIncarcare(double timpIncarcarePlugIn);

	// SET TIP HIBRID
	void setTipHibrid(char tipHibrid);

	// GET TIP HIBRID
	char getTipHibrid() const;
};

// CONSTRUCTOR FARA PARAMETRI
VehiculHibrid::VehiculHibrid() : VehiculCarburant(), tipHibrid('N'), autonomieElectricPlugIn(0), timpIncarcarePlugIn(0) {}

// CONSTRUCTOR CU PARAMETRI
VehiculHibrid::VehiculHibrid(string marca, string model, int anFabricatie, int nrInserariIstoricRulaj, map <string, int> istoricRulaj,
	int nrDotari, set <string> dotari, double pret, string tipCarburant, double consum, char tipHibrid, double autonomieElectricPlugIn, double timpIncarcarePlugIn) :
	VehiculCarburant(marca, model, anFabricatie, nrInserariIstoricRulaj, istoricRulaj, nrDotari, dotari, pret, tipCarburant, consum), tipHibrid(tipHibrid),
	autonomieElectricPlugIn(autonomieElectricPlugIn), timpIncarcarePlugIn(timpIncarcarePlugIn)
{
	if (tipHibrid == 'M')
	{
		autonomieElectricPlugIn = 0;
		timpIncarcarePlugIn = 0;
	}
	else
		if (tipHibrid != 'P')
		{
			// ?
			throw "Tip hibrid invalid!";
		}
}

// COPY CONSTRUCTOR
VehiculHibrid::VehiculHibrid(const VehiculHibrid& obj) : VehiculCarburant(obj), tipHibrid(obj.tipHibrid), autonomieElectricPlugIn(obj.autonomieElectricPlugIn), 
															timpIncarcarePlugIn(obj.timpIncarcarePlugIn) {}

// OPERATORUL =
VehiculHibrid& VehiculHibrid::operator=(const VehiculHibrid& obj)
{
	if (this != &obj)
	{
		VehiculCarburant::operator=(obj);
		this->tipHibrid = obj.tipHibrid;
		this->autonomieElectricPlugIn = obj.autonomieElectricPlugIn;
		this->timpIncarcarePlugIn = obj.timpIncarcarePlugIn;
	}
	return *this;
}

// DESTRUCTOR
VehiculHibrid::~VehiculHibrid() {}

// OPERATORUL >>
istream& VehiculHibrid::citireVehicul(istream& in)
{
	VehiculCarburant::citireVehicul(in);
	
	
	while (true)
	{
		cout << "Tip hibrid (P - plug-in, M - mild): ";
		string aux;
		getline(in, aux);
		if (aux == "")
			getline(in, aux);
		try 
		{
			tipHibrid = aux[0];
			if(aux.length() != 1 || (tipHibrid != 'P' && tipHibrid != 'M'))
				throw invalid_argument("\nTip hibrid invalid!\n");
			break;
		}
		catch (const invalid_argument& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nComanda invalida.\n";
		}
		

	}

	if (tipHibrid == 'P')
	{
		/*cout << "Autonomie electric (km): ";
		in >> autonomieElectricPlugIn;*/

		while (true)
		{
			string sir;
			cout << "Autonomie electric (km): ";
			getline(in, sir);
			if (sir == "")
				getline(in, sir);
			try
			{
				autonomieElectricPlugIn = stodExceptionCitire(sir);
				if (autonomieElectricPlugIn < 0)
					throw out_of_range("\nAutonomia electrica nu poate fi negativa!\n");
				break;
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}

		/*cout << "Timp incarcare (ore): ";
		in >> timpIncarcarePlugIn;*/

		while (true)
		{
			string sir;
			cout << "Timp incarcare (ore): ";
			getline(in, sir);
			if (sir == "")
				getline(in, sir);
			try
			{
				timpIncarcarePlugIn = stodExceptionCitire(sir);
				if (timpIncarcarePlugIn < 0)
					throw out_of_range("\nTimpul de incarcare nu poate fi negativ!\n");
				break;
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}
	}
	else
	{
		autonomieElectricPlugIn = 0;
		timpIncarcarePlugIn = 0;
	}
	return in;
}

// OPERATORUL <<
ostream& VehiculHibrid::afisareVehicul(ostream& out) const
{
	VehiculCarburant::afisareVehicul(out);
	out << "Tip hibrid: " << tipHibrid << "\n";
	if (tipHibrid == 'P')
	{
		out << "Autonomie electric: " << autonomieElectricPlugIn << " km\n";
		out << "Timp incarcare: " << timpIncarcarePlugIn << " ore\n";
	}
	return out;
}

// FUNCTIE VALOARE REALA VEHICUL
double VehiculHibrid::valoareaRealaVehicul() const
{
	double valoare = VehiculCarburant::valoareaRealaVehicul();
	if (tipHibrid == 'P')
		valoare += 0.1 * valoare;
	return valoare;
}

// FUNCTIE COST FOLOSIRE SI INTRETINERE
double VehiculHibrid::costFolosireSiIntretinere() const
{
	double cost = VehiculCarburant::costFolosireSiIntretinere();
	if (tipHibrid == 'P')
		cost += 0.1 * pret;
	return cost;
}

// FUNCTIE CLONE
Vehicul* VehiculHibrid::clone() const
{
	return new VehiculHibrid(*this);
}

// SET AUTONOMIE ELECTRIC PLUG-IN
void VehiculHibrid::setAutonomieElectric(double autonomieElectricPlugIn)
{
	this->autonomieElectricPlugIn = autonomieElectricPlugIn;
}

// SET TIMP INCARCARE PLUG-IN
void VehiculHibrid::setTimpIncarcare(double timpIncarcarePlugIn)
{
	this->timpIncarcarePlugIn = timpIncarcarePlugIn;
}

// SET TIP HIBRID
void VehiculHibrid::setTipHibrid(char tipHibrid)
{
	
	if (tipHibrid == 'M')
	{
		this->tipHibrid = tipHibrid;
		autonomieElectricPlugIn = 0;
		timpIncarcarePlugIn = 0;
	}
	else
		if (tipHibrid == 'P')
		{
			cout << "Autonomie electric (km): ";
			cin >> autonomieElectricPlugIn;
			cout << "Timp incarcare (ore): ";
			cin >> timpIncarcarePlugIn;
			this->tipHibrid = tipHibrid;
		}
		else
		{
			// ?
			throw "Tip hibrid invalid!";
		}
}

// GET TIP HIBRID
char VehiculHibrid::getTipHibrid() const
{
	return tipHibrid;
}


// --------- CLASA SHOWROOM ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Showroom
{
	string nume;
	int nrVehiculeDisponibile;
	list <Vehicul*> vehiculeDisponibile; // am folosit list deoarece se pot elimina vehicule eficient in cazul unei vanzari

public:

	// CONSTRUCTOR FARA PARAMETRI
	Showroom();

	// CONSTRUCTOR CU PARAMETRI
	Showroom(string, int, list <Vehicul*>);

	// COPY CONSTRUCTOR
	Showroom(const Showroom&);

	// OPERATORUL =
	Showroom& operator=(const Showroom&);

	// DESTRUCTOR
	~Showroom();

	// OPERATORUL >>
	friend istream& operator >>(istream&, Showroom&);

	// OPERATORUL <<
	friend ostream& operator <<(ostream&, const Showroom&);

	// FUNCTIE MAJORARE PRET VEHICUL CU 10% LA INDEX DAT
	void majorarePretVehicul(int);

	// GET NUME SHOWROOM
	string getNumeShowroom() const;

	// OPERATIA SHOWROOM + VEHICUL
	Showroom operator+(Vehicul*);

	// OPERATIA SHOWROOM - VEHICUL
	Showroom operator-(int);

	// SET NUME
	void setNume(string nume);

	// GET VEHICULE DISPONIBILE
	list <Vehicul*> getVehicule() const;
};

// CONSTRUCTOR FARA PARAMETRI
Showroom::Showroom() : nume("Necunoscut"), nrVehiculeDisponibile(0), vehiculeDisponibile() {}

// CONSTRUCTOR CU PARAMETRI
Showroom::Showroom(string nume, int nrVehiculeDisponibile, list <Vehicul*> vehiculeDisponibile) :
	nume(nume), nrVehiculeDisponibile(nrVehiculeDisponibile), vehiculeDisponibile(vehiculeDisponibile) {}

// COPY CONSTRUCTOR
Showroom::Showroom(const Showroom& obj) : nume(obj.nume), nrVehiculeDisponibile(obj.nrVehiculeDisponibile)
{
	this->vehiculeDisponibile.clear();
	for (Vehicul* v : obj.vehiculeDisponibile)
	{
		this->vehiculeDisponibile.push_back(v->clone());
	}
}

// OPERATORUL =
Showroom& Showroom::operator=(const Showroom& obj)
{
	if (this != &obj)
	{
		this->nume = obj.nume;
		this->nrVehiculeDisponibile = obj.nrVehiculeDisponibile;
		for (Vehicul* v : this->vehiculeDisponibile)
		{
			delete v;
		}
		vehiculeDisponibile.clear();
		for (Vehicul* v : obj.vehiculeDisponibile)
		{
			this->vehiculeDisponibile.push_back(v->clone());
		}
	}
	return *this;
}

// DESTRUCTOR
Showroom::~Showroom()
{
	for (Vehicul* v : vehiculeDisponibile)
	{
		delete v;
	}
	vehiculeDisponibile.clear();
}

// OPERATORUL >>
istream& operator >>(istream& in, Showroom& obj)
{
	int index = 0;

	cout << "Nume: ";
	getline(in, obj.nume);
	/*cout << "Numar vehicule disponibile: ";
	in >> obj.nrVehiculeDisponibile;*/

	while (true)
	{
		string sir;
		cout << "Numar vehicule disponibile: ";
		getline(in, sir);
		if (sir == "")
			getline(in, sir);
		try
		{
			obj.nrVehiculeDisponibile = stoiExceptionCitire(sir);
			if (to_string(obj.nrVehiculeDisponibile) != sir)
				throw myEx;
			else
				if (obj.nrVehiculeDisponibile < 0)
					throw out_of_range("\nNumarul de vehicule disponibile nu poate fi negativ!\n");
			break;
		}
		catch (MyException& e)
		{
			cout << e.what();
		}
		catch (const out_of_range& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nComanda invalida.\n";
		}
	}

	obj.vehiculeDisponibile.clear();
	for (int i = 0; i < obj.nrVehiculeDisponibile; i++)
	{
		cout << "\nVehiculul " << i + 1 << ":\n";
		cout << "Tipul vehiculului (C - carburant, H - hibrid): ";
		string tip;
		cin.get();
		getline(in, tip);
		if (tip == "C")
		{
			Vehicul* v = new VehiculCarburant();
			in >> *v;
			obj.vehiculeDisponibile.push_back(v);
		}
		else
			if (tip == "H")
			{
				Vehicul* v = new VehiculHibrid();
				in >> *v;
				obj.vehiculeDisponibile.push_back(v);
			}
			else
			{
				// ?
				throw "Tip vehicul invalid!";
			}


		// ?
		//bool introducereTip = false;
		//while (introducereTip == false)
		//{
		//	getline(in, tip);
		//	if (tip == "C")
		//	{
		//		Vehicul* v = new VehiculCarburant();
		//		in >> *v;
		//		obj.vehiculeDisponibile.push_back(v);
		//		introducereTip = true;
		//	}
		//	else
		//		if (tip == "H")
		//		{
		//			Vehicul* v = new VehiculHibrid();
		//			in >> *v;
		//			obj.vehiculeDisponibile.push_back(v);
		//			introducereTip = true;
		//		}
		//		else
		//		{
		//			//throw "Tip vehicul invalid!";
		//			cout << "\nTip vehicul invalid! Introduceti din nou tipul vehiculului (C - carburant, H - hibrid): ";
		//		}
		//}
	}
	return in;
}

// OPERATORUL <<
ostream& operator <<(ostream& out, const Showroom& obj)
{
	int index = 1;

	out << "\nNume: " << obj.nume << "\n";
	out << "Numar vehicule disponibile: " << obj.nrVehiculeDisponibile << "\n";
	if (obj.vehiculeDisponibile.size())
	{
		out << "Vehicule disponibile:\n";
		for (Vehicul* v : obj.vehiculeDisponibile)
		{
			out << "\nVehiculul " << index++ << ":\n";
			out << *v;
		}
	}
	return out;
}


// FUNCTIE MAJORARE PRET VEHICUL CU 10% LA INDEX DAT
void Showroom::majorarePretVehicul(int index)
{
	list <Vehicul*>::iterator it = vehiculeDisponibile.begin();
	advance(it, index - 1);
	(*it)->setPret((*it)->getPret() * 1.1);
}

// GET NUME SHOWROOM
string Showroom::getNumeShowroom() const
{
	return nume;
}

// OPERATIA SHOWROOM + VEHICUL*
Showroom Showroom::operator+(Vehicul* obj)
{
	Showroom copie = *this;
	copie.vehiculeDisponibile.push_back(obj->clone()); // clone ?
	copie.nrVehiculeDisponibile++;
	return copie;
}

// OPERATIA SHOWROOM - VEHICUL* (SE VA TRANSMITE CA PARAMETRU INDEX-UL VEHICULULUI DIN VECTORUL DE VEHICULE DISPONIBILE)
Showroom Showroom::operator-(int index)
{
	try {
		if (index > nrVehiculeDisponibile)
		{
			throw 1;
		}
		if (index < 0)
		{
			throw 2;
		}
		Showroom copie = *this;
		list<Vehicul*>::iterator it = copie.vehiculeDisponibile.begin();
		std::advance(it, index);
		delete* it;
		copie.vehiculeDisponibile.erase(it);
		copie.nrVehiculeDisponibile--;
		return copie;
	}
	catch (int var)
	{
		if (var == 1)
		{
			cout << "\n****************************************************************EROARE****************************************************************\n";
			cout << "\nEroare!\nIn operatia de stergere al unui vehicul din showroom, index-ul introdus este mai mare decat numarul de vehicule disponibile.\nVectorul de vehicule din " << this->getNumeShowroom() << " a ramas nemodificat.\n";
			cout << "\n****************************************************************EROARE****************************************************************\n";
			return *this;
		}
		else
			if (var == 2)
			{
				cout << "\n*********************************************EROARE*********************************************\n";
				cout << "\nEroare!\nIn operatia de stergere al unui vehicul din showroom index-ul introdus este negativ.\nVectorul de vehicule din " << this->getNumeShowroom() << " a ramas nemodificat.\n";
				cout << "\n*********************************************EROARE*********************************************\n";
				return *this;
			}
	}
	return *this;
}

// SET NUME
void Showroom::setNume(string nume)
{
	this->nume = nume;
}

// GET VEHICULE DISPONIBILE
list <Vehicul*> Showroom::getVehicule() const
{
	return vehiculeDisponibile;
}


// --------- CLASA INFOVEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T>
class InfoVehicul
{
public:

	template <class T>
	void info(T obj)
	{
		cout << "\nInformatii vehicul:\n\nUn vehicul este o masina sau un mijloc de transport care permite oamenilor sa se deplaseze de la un loc la altul.\nCcestea pot fi autoturisme, camioane, autobuze, motociclete, biciclete sau chiar nave si avioane.\nVehiculele sunt esentiale pentru mobilitatea noastra in societatea moderna, facilitand transportul de persoane si bunuri.\n";
	}

	template <>
	void info(VehiculCarburant obj)
	{
		cout << "\nUn vehicul cu carburant utilizeaza combustibili lichizi, precum benzina sau motorina, pentru a functiona.\nAceste tipuri de vehicule sunt echipate cu motoare cu ardere interna care transforma energia chimica a carburantului in energie mecanica,\npropulsand vehiculul pe drumurile publice. Desi exista si vehicule hibride care combina motoare electrice cu motoare cu ardere interna,\ncele cu carburant ramân o optiune populara pentru transportul personal si comercial.\n";
		cout << obj;
		cout << "Valoarea reala a vehiculului: " << obj.valoareaRealaVehicul() << "\n";
		cout << "Costul folosirii si intretinerii vehiculului: " << obj.costFolosireSiIntretinere() << "\n";
	}

	template <>
	void info(VehiculHibrid obj)
	{
		cout << "\nUn vehicul hibrid este un vehicul care utilizeaza doua sau mai multe surse de energie pentru a functiona.\nAcestea includ motoare electrice, motoare cu ardere interna si alte surse de energie regenerabila, precum energia solara sau hidrogenul.\nVehiculele hibride sunt o optiune populara pentru cei care doresc sa reduca emisiile de gaze cu efect de sera si sa economiseasca combustibil.\n";
		cout << "In showroom-urile noastre se gasesc vehicule hibride de tipul plug-in si mild.\nPlug-in reprezinta vehiculele hibride care pot fi incarcate la priza si pot merge doar pe baza motorului electric,\nin timp ce mild hibridele sunt echipate cu motoare electrice care asista motoarele cu ardere interna pentru a reduce consumul de combustibil.\nAstfel, vehiculele plug-in beneficiaza si de specificatiile timp incarcare si autonomie electric.\n";
		cout << obj;
		cout << "Valoarea reala a vehiculului: " << obj.valoareaRealaVehicul() << "\n";
		cout << "Costul folosirii si intretinerii vehiculului: " << obj.costFolosireSiIntretinere() << "\n";
	}

	template <>
	void info(Showroom obj)
	{
		cout << "\nUn showroom auto este un spatiu comercial specializat in vanzarea de vehicule noi si second-hand.\nAcestea pot fi autoturisme, camioane, autobuze, motociclete, biciclete sau chiar nave si avioane.\nShowroom-urile auto ofera o varietate de servicii, precum vanzarea de vehicule, finantare, asigurari, service si piese de schimb.\n";
		cout << obj;
		int suma = 0;
		list <Vehicul*> vehicule = obj.getVehicule();
		for (Vehicul* v : vehicule)
		{
			suma += v->getPret();
		}
		cout << "\nValoarea totala a vehiculelor din showroom: " << suma << "\n";
	}
    
};

// --------- CLASA COLECTIEVEHICULE ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//template <class T = Vehicul>
//class ColectieVehicule
//{
//	vector <T*> vehicule;
//
//public:
//
//	// CONSTRUCTOR FARA PARAMETRI
//	ColectieVehicule();
//
//	// CONSTRUCTOR CU PARAMETRI
//	ColectieVehicule(vector <T*>);
//
//	// COPY CONSTRUCTOR
//	ColectieVehicule(const ColectieVehicule&);
//
//	// OPERATORUL =
//	ColectieVehicule& operator=(const ColectieVehicule&);
//
//	// DESTRUCTOR
//	~ColectieVehicule();
//
//	// OPERATORUL >>
//	friend istream& operator >>(istream&, ColectieVehicule&);
//
//	// OPERATORUL <<
//	friend ostream& operator <<(ostream&, const ColectieVehicule&);
//
//	// FUNCTIE ADAUGARE VEHICUL
//	void adaugareVehicul(T*);
//
//	// FUNCTIE STERGERE VEHICUL
//	void stergereVehicul(int);
//};
//
//// CONSTRUCTOR FARA PARAMETRI
//template <class T>
//ColectieVehicule<T>::ColectieVehicule() : vehicule() {}
//
//// CONSTRUCTOR CU PARAMETRI
//template <class T>
//ColectieVehicule<T>::ColectieVehicule(vector <T*> vehicule) : vehicule(vehicule) {}
//
//// COPY CONSTRUCTOR
//template <class T>
//ColectieVehicule<T>::ColectieVehicule(const ColectieVehicule& obj)
//{
//	this->vehicule.clear();
//	for (T* v : obj.vehicule)
//	{
//		this->vehicule.push_back(v->clone());
//	}
//}
//
//// OPERATORUL =
//template <class T>
//ColectieVehicule<T>& ColectieVehicule<T>::operator=(const ColectieVehicule& obj)
//{
//	if (this != &obj)
//	{
//		for (T* v : this->vehicule)
//		{
//			delete v;
//		}
//		this->vehicule.clear();
//		for (T* v : obj.vehicule)
//		{
//			this->vehicule.push_back(v->clone());
//		}
//	}
//	return *this;
//}
//
//// DESTRUCTOR
//template <class T>
//ColectieVehicule<T>::~ColectieVehicule()
//{
//	for (T* v : vehicule)
//	{
//		delete v;
//	}
//	vehicule.clear();
//}
//
//// OPERATORUL >>
//template <class T>
//istream& operator >>(istream& in, ColectieVehicule<T>& obj)
//{
//	int index = 0;
//
//	cout << "Numar vehicule: ";
//	in >> index;
//	obj.vehicule.clear();
//	for (int i = 0; i < index; i++)
//	{
//		cout << "\nVehiculul " << i + 1 << ":\n";
//		cout << "Tipul vehiculului (C - carburant, H - hibrid): ";
//		bool introducereTip = false;
//		string tip;
//		in.get();
//		while (introducereTip == false)
//		{
//			getline(in, tip);
//			if (tip == "C")
//			{
//				T* v = new VehiculCarburant();
//				in >> *v;
//				obj.vehicule.push_back(v);
//				introducereTip = true;
//			}
//			else
//				if (tip == "H")
//				{
//					T* v = new VehiculHibrid();
//					in >> *v;
//					obj.vehicule.push_back(v);
//					introducereTip = true;
//				}
//				else
//				{
//					cout << "\nTip vehicul invalid! Introduceti din nou tipul vehiculului (C - carburant, H - hibrid): ";
//				}
//		}
//	}
//	return in;
//}
//
//// OPERATORUL <<
//template <class T>
//ostream& operator <<(ostream& out, const ColectieVehicule<T>& obj)
//{
//	int index = 1;
//
//	out << "\nNumar vehicule: " << obj.vehicule.size() << "\n";
//	for (T* v : obj.vehicule)
//	{
//		out << "\nVehiculul " << index++ << ":\n";
//		out << *v;
//	}
//	return out;
//}
//
//// FUNCTIE ADAUGARE VEHICUL
//template <class T>
//void ColectieVehicule<T>::adaugareVehicul(T* v)
//{
//	vehicule.push_back(v);
//}
//
//// FUNCTIE STERGERE VEHICUL
//template <class T>
//void ColectieVehicule<T>::stergereVehicul(int index)
//{
//	if (index < 0 || index >= vehicule.size())
//	{
//		cout << "Index invalid!\n";
//		return;
//	}
//	delete vehicule[index];
//	vehicule.erase(vehicule.begin() + index);
//}


// --------- CLASA CLIENT ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Client : public Subject<Client>
{
	string nume;
	int nrVehiculeCumparate;
	vector <Vehicul*> vehiculeCumparate; // am folosit vector deoarece se pot adauga vehicule eficient in cazul unei vanzari, dar si pentru a putea accesa vehiculele cumparate cu index
	double plataRamasa;
	map <string, double> istoricPlati; // data, suma platita

public:

	// CONSTRUCTOR FARA PARAMETRI
	Client();

	// CONSTRUCTOR CU PARAMETRI
	Client(string, int, vector <Vehicul*>, double, map <string, double>);

	// COPY CONSTRUCTOR
	Client(const Client&);

	// OPERATORUL =
	Client& operator=(const Client&);

	// DESTRUCTOR
	~Client();

	// OPERATORUL >>
	friend istream& operator >>(istream&, Client&);

	// OPERATORUL <<
	friend ostream& operator <<(ostream&, const Client&);

	// SET NUME
	void setNume(string nume);

	// SET PLATA RAMASA
	void setPlataRamasa(double plataRamasa);

	// INSERARE PLATA IN ISTORIC PLATI
	void inserareIstoricPlati(string data, double suma);

	// GET VEHICULE CUMPARATE
	vector <Vehicul*> getVehicule() const;

	// OPERATIA CLIENT + VEHICUL*
	Client operator+(Vehicul*);

	// GET PLATA RAMASA
	double getPlataRamasa() const;
};

// CONSTRUCTOR FARA PARAMETRI
Client::Client() : nume("Necunoscut"), nrVehiculeCumparate(0), vehiculeCumparate(), plataRamasa(0), istoricPlati()
{
	//notifyObservers(*this, "\nClientul cu numele " + nume + " a fost creat cu succes.\n");
}

// CONSTRUCTOR CU PARAMETRI
Client::Client(string nume, int nrVehiculeCumparate, vector <Vehicul*> vehiculeCumparate, double plataRamasa, map <string, double> istoricPlati) :
	nume(nume), nrVehiculeCumparate(nrVehiculeCumparate), vehiculeCumparate(vehiculeCumparate), plataRamasa(plataRamasa), istoricPlati(istoricPlati) 
{
	notifyObservers(*this, "\nClientul cu numele " + nume + " a fost creat cu succes.\n");
}

// COPY CONSTRUCTOR
Client::Client(const Client& obj) : nume(obj.nume), nrVehiculeCumparate(obj.nrVehiculeCumparate), plataRamasa(obj.plataRamasa),
istoricPlati(obj.istoricPlati)
{
	this->vehiculeCumparate.clear();
	for (int i = 0; i < nrVehiculeCumparate; i++)
	{
		this->vehiculeCumparate.push_back(obj.vehiculeCumparate[i]->clone());
	}
}

// OPERATORUL =
Client& Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->nume = obj.nume;
		this->nrVehiculeCumparate = obj.nrVehiculeCumparate;
		for (int i = 0; i < this->vehiculeCumparate.size(); i++)
		{
			delete this->vehiculeCumparate[i];
		}
		vehiculeCumparate.clear();
		for (int i = 0; i < obj.vehiculeCumparate.size(); i++)
		{
			this->vehiculeCumparate.push_back(obj.vehiculeCumparate[i]->clone());
		}
		this->plataRamasa = obj.plataRamasa;
		this->istoricPlati = obj.istoricPlati;
	}
	return *this;
}

// DESTRUCTOR
Client::~Client() 
{
	for (int i = 0; i < nrVehiculeCumparate; i++)
	{
		delete vehiculeCumparate[i];
	}
	vehiculeCumparate.clear();
}


// OPERATORUL >>
istream& operator>>(istream& in, Client& obj)
{
	int index = 0;

	cout << "Nume: ";
	getline(in, obj.nume);
	/*cout << "Numar vehicule cumparate: ";
	in >> obj.nrVehiculeCumparate;*/

	while (true)
	{
		string sir;
		cout << "Numar vehicule cumparate: ";
		getline(in, sir);
		if (sir == "")
			getline(in, sir);
		try
		{
			obj.nrVehiculeCumparate = stoiExceptionCitire(sir);
			if (to_string(obj.nrVehiculeCumparate) != sir)
				throw myEx;
			else
				if (obj.nrVehiculeCumparate < 0)
					throw out_of_range("\nNumarul de vehicule cumparate nu poate fi negativ!\n");
			break;
		}
		catch (MyException& e)
		{
			cout << e.what();
		}
		catch (const out_of_range& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nComanda invalida.\n";
		}
	}

	obj.vehiculeCumparate.clear();
	for (int i = 0; i < obj.nrVehiculeCumparate; i++)
	{
		cout << "\nVehiculul " << i + 1 << ":\n";
		
		//string tip;
		//cin.get();
		//getline(in, tip);
		//if (tip == "C")
		//{
		//	Vehicul* v = new VehiculCarburant();
		//	in >> *v;
		//	obj.vehiculeCumparate.push_back(v);
		//}
		//else
		//	if (tip == "H")
		//	{
		//		Vehicul* v = new VehiculHibrid();
		//		in >> *v;
		//		obj.vehiculeCumparate.push_back(v);
		//	}
		//	else
		//	{
		//		// ?
		//		throw "Tip vehicul invalid!";
		//	}
		string aux;

		while (true)
		{
			cout << "Tipul vehiculului (C - carburant, H - hibrid): ";
			
			getline(in, aux);
			if (aux == "")
				getline(in, aux);
			try
			{
				if (aux != "C" && aux != "H")
					throw myEx;
				break;
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}
		if (aux == "C")
		{
			Vehicul* v = new VehiculCarburant();
			in >> *v;
			obj.vehiculeCumparate.push_back(v);
		}
		else
			if (aux == "H")
			{
				Vehicul* v = new VehiculHibrid();
				in >> *v;
				obj.vehiculeCumparate.push_back(v);
			}
			

	}



		/*cout << "Plata ramasa: ";
		in >> obj.plataRamasa;*/

		while (true)
		{
			string sir;
			cout << "Plata ramasa: ";
			getline(in, sir);
			if (sir == "")
				getline(in, sir);
			try
			{
				obj.plataRamasa = stodExceptionCitire(sir);
					if (obj.plataRamasa < 0)
						throw out_of_range("\nPlata ramasa nu poate fi negativa!\n");
				break;
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}

		obj.istoricPlati.clear();

		cout << "Istoric plati:\n";
		/*cout << "Numar inserari in istoric plati: ";
		in >> index;*/

		while (true)
		{
			string sir;
			cout << "Numar inserari in istoric plati: ";
			getline(in, sir);
			if (sir == "")
				getline(in, sir);
			try
			{
				index = stoiExceptionCitire(sir);
				if (to_string(index) != sir)
					throw myEx;
				else
					if (index < 0)
						throw out_of_range("\nNumarul de inserari in istoric plati nu poate fi negativ!\n");
				break;
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}

		if (index)
		{
			/*cout << "Data si suma platita, separate printr-un spatiu:\n";
			string data;
			double suma;
			for (int i = 0; i < index; i++)
			{
				in >> data >> suma;
				obj.istoricPlati.insert({ data, suma });
			}*/
			
			for (int i = 0; i < index; i++)
			{
				cout << "\nInserarea " << i + 1 << "/" << index << ": ";
				string data;
				double suma;

				while (true)
				{
					string comandaStr;
					cout << "\nData: ";
					in >> data;
					cout << "Suma: ";
					getline(in, comandaStr);
					if (comandaStr == "")
						getline(in, comandaStr);
					try
					{
						suma = stodExceptionCitire(comandaStr);
							if (suma < 0)
								throw out_of_range("\nSuma platita nu poate fi negativa!\n");
						break;
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}
				obj.istoricPlati.insert({ data, suma });
			}

		}
		Client::notifyObservers(obj, "\nClientul cu numele " + obj.nume + " a fost creat cu succes.\n");
		return in;
}


// OPERATORUL <<
ostream& operator <<(ostream& out, const Client& obj)
{
	int index = 1;

	out << "\nNume: " << obj.nume << "\n";
	out << "Numar vehicule cumparate: " << obj.nrVehiculeCumparate << "\n";
	if (obj.vehiculeCumparate.size())
	{
		out << "Vehicule cumparate:\n";
		for (int i = 0; i < obj.nrVehiculeCumparate; i++)
		{
			out << "\nVehiculul " << i + 1 << ":\n";
			out << *obj.vehiculeCumparate[i];
		}
	}
	out << "\nPlata ramasa: " << obj.plataRamasa << "\n";
	out << "Istoric plati:\n";
	for (pair<string, double> p : obj.istoricPlati)
	{
		out << "Plata " << index++ << ": " << p.first << " " << p.second << "\n";
	}
	return out;
}

// SET NUME
void Client::setNume(string nume)
{
	this->nume = nume;
}

// SET PLATA RAMASA
void Client::setPlataRamasa(double plataRamasa)
{
	this->plataRamasa = plataRamasa;
}

// INSERARE PLATA IN ISTORIC PLATI
void Client::inserareIstoricPlati(string data, double suma)
{
	if (suma > plataRamasa)
	{
		throw  invalid_argument("\nSuma platita este mai mare decat plata ramasa!\n");
		return;
	}
	else
		if (suma < 0)
		{
			throw invalid_argument("\nSuma platita este mai mica decat 0!\n");
			return;
		}
	istoricPlati.insert({ data, suma });
	plataRamasa -= suma;
}

// GET VEHICULE CUMPARATE
vector <Vehicul*> Client::getVehicule() const
{
	return vehiculeCumparate;
}

// OPERATIA CLIENT + VEHICUL*
Client Client::operator+(Vehicul* obj)
{
	Client copie = *this;
	copie.vehiculeCumparate.push_back(obj);
	copie.nrVehiculeCumparate++;
	return copie;
}

// GET PLATA RAMASA
double Client::getPlataRamasa() const 
{
	return plataRamasa;
}


// --------- CLASA TRANZACTIE ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Tranzactie : public Subject<Tranzactie>
{
	const int idTranzactie;
	static int nrTranzactii;
	Client client;
	Vehicul* vehiculCumparat;
	double sumaPlatita;

public:

	// CONSTRUCTOR FARA PARAMETRI
	Tranzactie();

	// CONSTRUCTOR CU PARAMETRI
	Tranzactie(Client, Vehicul*, double);

	// COPY CONSTRUCTOR
	Tranzactie(const Tranzactie&);

	// OPERATORUL =
	Tranzactie& operator=(const Tranzactie&);

	// DESTRUCTOR
	~Tranzactie();

	// OPERATORUL >>
	friend istream& operator >>(istream&, Tranzactie&);

	// OPERATORUL <<
	friend ostream& operator <<(ostream&, const Tranzactie&);

	// GET CLIENT
	Client getClient() const;

	// GET VEHICUL CUMPARAT
	Vehicul* getVehiculCumparat() const;

	// SET SUMA PLATITA
	void setSumaPlatita(double sumaPlatita);

	// SET CLIENT
	void setClient(Client client);

	// SET VEHICUL CUMPARAT
	void setVehiculCumparat(Vehicul* vehiculCumparat);
};

// CONSTRUCTOR FARA PARAMETRI
Tranzactie::Tranzactie() : idTranzactie(++nrTranzactii + 1000), client(), vehiculCumparat(), sumaPlatita(0) {}

// CONSTRUCTOR CU PARAMETRI
Tranzactie::Tranzactie(Client client, Vehicul* vehiculCumparat, double sumaPlatita) :
	idTranzactie(++nrTranzactii + 2000), client(client), vehiculCumparat(vehiculCumparat), sumaPlatita(sumaPlatita) 
{
	Client c1;
	Tranzactie::notifyObservers(*this, "\nTranzactia cu ID-ul " + to_string(idTranzactie) + " a fost creata cu succes.\n");
}

// COPY CONSTRUCTOR
Tranzactie::Tranzactie(const Tranzactie& obj) : idTranzactie(obj.idTranzactie), client(obj.client), sumaPlatita(obj.sumaPlatita)
{
	
	if (obj.vehiculCumparat)
	{
		this->vehiculCumparat = obj.vehiculCumparat->clone();
	}
	else
	{
		this->vehiculCumparat = nullptr;
	}
}

// OPERATORUL =
Tranzactie& Tranzactie::operator=(const Tranzactie& obj)
{
	if (this != &obj)
	{
		this->client = obj.client;
		if (this->vehiculCumparat)
		{
			delete this->vehiculCumparat;
		}
		if (obj.vehiculCumparat)
		{
			this->vehiculCumparat = obj.vehiculCumparat->clone();
		}
		else
		{
			this->vehiculCumparat = nullptr;
		}
		this->sumaPlatita = obj.sumaPlatita;
	}
	return *this;
}

// DESTRUCTOR
Tranzactie::~Tranzactie() 
{
	// ?
	// incearca sa stearga ceva ce a fost sters deja
	delete vehiculCumparat;
}

// OPERATORUL >>
istream& operator >> (istream& in, Tranzactie& obj)
{
	cout << "Clientul:\n";
	in >> obj.client;
	cout << "Vehiculul cumparat:\n";
	cout << "Tipul vehiculului (C - carburant, H - hibrid): ";
	string tip;
	cin.get();
	getline(in, tip);
	if (tip == "C")
	{
		Vehicul* v = new VehiculCarburant();
		in >> *v;
		obj.vehiculCumparat = v;
	}
	else
		if (tip == "H")
		{
			Vehicul* v = new VehiculHibrid();
			in >> *v;
			obj.vehiculCumparat = v->clone();
		}
		else
		{
			// ?
			throw "Tip vehicul invalid!";
		}


	// ?
	//bool introducereTip = false;
	//while (introducereTip == false)
	//{
	//	getline(in, tip);
	//	if (tip == "C")
	//	{
	//		Vehicul* v = new VehiculCarburant();
	//		in >> *v;
	//		obj.vehiculCumparat = v;
	//		introducereTip = true;
	//	}
	//	else
	//		if (tip == "H")
	//		{
	//			Vehicul* v = new VehiculHibrid();
	//			in >> *v;
	//			obj.vehiculCumparat = v;
	//			introducereTip = true;
	//		}
	//		else
	//		{
	//			//throw "Tip vehicul invalid!";
	//			cout << "\nTip vehicul invalid! Introduceti din nou tipul vehiculului (C - carburant, H - hibrid): ";
	//		}
	//}

	cout << "Suma platita: ";
	in >> obj.sumaPlatita;

	Tranzactie::notifyObservers(obj, "\nTranzactia cu ID-ul " + to_string(obj.idTranzactie) + " a fost creata cu succes.\n");

	return in;
}

// OPERATORUL <<
ostream& operator <<(ostream& out, const Tranzactie& obj)
{
	out << "\nID tranzactie: " << obj.idTranzactie << "\n";
	out << "Clientul:\n" << obj.client;
	out << "Vehiculul cumparat:\n" << *obj.vehiculCumparat;

	out << "Suma platita: " << obj.sumaPlatita << "\n";
	return out;
}

// GET CLIENT
Client Tranzactie::getClient() const
{
	return client;
}

// GET VEHICUL CUMPARAT
Vehicul* Tranzactie::getVehiculCumparat() const
{
	return vehiculCumparat;
}

// SET SUMA PLATITA
void Tranzactie::setSumaPlatita(double sumaPlatita)
{
	this->sumaPlatita = sumaPlatita;
}

// SET CLIENT
void Tranzactie::setClient(Client client)
{
	this->client = client;
}

// SET VEHICUL CUMPARAT
void Tranzactie::setVehiculCumparat(Vehicul* vehiculCumparat)
{
	this->vehiculCumparat = vehiculCumparat;
}


// --------- CLASA SINGLETON ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Singleton
{
	static Singleton* instance;
	
	vector <Tranzactie*> tranzactii;
	vector <Showroom> showroomuri;
	vector <Client> clienti;
	vector <Vehicul*> vehicule;
	
public:

	// CONSTRUCTOR FARA PARAMETRI
	Singleton() = default;

	// COPY CONSTRUCTOR
	Singleton(const Singleton&) = delete;

	// OPERATORUL =
	Singleton& operator=(const Singleton&) = delete;


	// GET INSTANCE
	static Singleton* getInstance();
	
	// CREARE OBIECTE DIN MENIU
	template <class T>
	T creareObject();

	// CREARE OBIECTE DIN MENIU VEHICUL*
	template <>
	Vehicul* creareObject();

	// CREARE OBIECTE DIN MENIU TRANZACTIE*
	template <>
	Tranzactie* creareObject();

	// AFISARE OBIECTE DIN MENIU
	template <class T>
	void printObject(const T obj);

	// AFISARE OBIECTE DIN MENIU VEHICUL*
	template <>
	void printObject(const Vehicul* obj);

	// MODIFICARE OBIECTE DIN MENIU
	void modificareObject(Tranzactie& obj);

	void modificareObject(Showroom& obj);

	void modificareObject(Client& obj);

	// MODIFICARE OBIECTE DIN MENIU VEHICUL*
	void modificareObject(Vehicul*& obj);

	// ADAUGARE OBIECTE DEJA CREATE IN VECTORII MENIULUI
	void adaugareObiect(Tranzactie* obj);

	void adaugareObiect(Showroom obj);

	void adaugareObiect(Client obj);

	// ADAUGARE OBIECTE DEJA CREATE IN VECTORII MENIULUI VEHICUL*
	void adaugareObiect(Vehicul*);

	// FUNCTIA STOIEXCEPTION
	int stoiException(const string&);

	// FUNCTIA STODEXCEPTION
	double stodException(const string&);

	// START MENU
	void startMenu();
};

// GET INSTANCE
Singleton* Singleton::getInstance()
{
	if (Singleton::instance != NULL)
		return Singleton::instance;
	else
	{
		instance = new Singleton();
		return instance;
	}
}

// CREARE OBIECTE DIN MENIU
template <class T>
T Singleton::creareObject()
{
	T obj;
	cin >> obj;
	return obj;
}

// CREARE OBIECTE DIN MENIU VEHICUL*
template <>
Vehicul* Singleton::creareObject()
{
	Vehicul* obj;
	cout << "Tipul vehiculului (C - carburant, H - hibrid): ";
	string tip;
	getline(cin, tip);
	if (tip == "C")
	{
		obj = new VehiculCarburant();
		cin >> *obj;
	}
	else
		if (tip == "H")
		{
			obj = new VehiculHibrid();
			cin >> *obj;
		}
		else
		{
			throw invalid_argument("\nTip vehicul invalid!\n");
		}
	return obj;
}

// CREARE OBIECTE DIN MENIU TRANZACTIE*
template <>
Tranzactie* Singleton::creareObject()
{
	Tranzactie* obj = new Tranzactie();
	cin >> *obj;
	return obj;
}

// AFISARE OBIECTE DIN MENIU
template <class T>
void Singleton::printObject(const T obj)
{
	cout << obj;
}

// AFISARE OBIECTE DIN MENIU VEHICUL*
template <>
void Singleton::printObject(const Vehicul* obj)
{
	cout << *obj;
}

// MODIFICARE OBIECTE DIN MENIU VEHICUL*
void Singleton::modificareObject(Vehicul*& obj)
{
	if (typeid(*obj) == typeid(VehiculCarburant))
	{
		VehiculCarburant* objCarburant = dynamic_cast<VehiculCarburant*>(obj);
		obj = dynamic_cast<VehiculCarburant*>(obj);
		int k = 1;
		while (k == 1)
		{
			int comanda;
			cout << "\n1. Modificare marca\n";
			cout << "2. Modificare model\n";
			cout << "3. Modificare an fabricatie\n";
			cout << "4. Inserare informatie in istoric rulaj\n";
			cout << "5. Inserare informatie in dotari\n";
			cout << "6. Modificare pret\n";
			cout << "7. Modificare tip carburant\n";
			cout << "8. Modificare consum\n";
			cout << "\n9. Iesire din submeniu\n";
				
			while (true)
			{
				string comandaStr;
				cout << endl << "> ";
				getline(cin, comandaStr);
				if (comandaStr == "")
					getline(cin, comandaStr);
				try
				{
					comanda = stoiException(comandaStr);
					if (comanda < 1 || comanda > 9)
						throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
					else
						if (to_string(comanda) != comandaStr)
							throw myEx;
					break;
				}
				catch (const out_of_range& e)
				{
					cout << e.what();
				}
				catch (MyException& e)
				{
					cout << e.what();
				}
				catch (...)
				{
					cout << "\nComanda invalida.\n";
				}
			}

			switch (comanda)
			{

			case 1:
			{
				string marca;
				cout << "Marca noua: ";
				cin.get();
				getline(cin, marca);
				objCarburant->setMarca(marca);
				break;
			}
			case 2:
			{
				string model;
				cout << "Model nou: ";
				cin.get();
				getline(cin, model);
				objCarburant->setModel(model);
				break;
			}
			case 3:
			{
				int anFabricatie;

				while (true)
				{
					string comandaStr;
					cout << "\nAn fabricatie nou: ";
					getline(cin, comandaStr);
					if (comandaStr == "")
						getline(cin, comandaStr);
					try
					{
						anFabricatie = stoiException(comandaStr);
						if (anFabricatie < 1700)
							throw out_of_range("\nAnul de fabricatie nu poate fi mai mic ca 1700!\n");
						else
							if (to_string(anFabricatie) != comandaStr)
								throw myEx;

						objCarburant->setAnFabricatie(anFabricatie);
						break;
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}
				break;
			}
			case 4:
			{
				string data;
				int rulaj;

				while (true)
				{
					string comandaStr;
					cout << "\nData: ";
					cin >> data;
					cout << "\nRulaj: ";
					getline(cin, comandaStr);
					if (comandaStr == "")
						getline(cin, comandaStr);
					try
					{
						rulaj = stoiException(comandaStr);
						objCarburant->inserareIstoricRulaj(data, rulaj);
						break;
					}
					catch (const invalid_argument& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}
				break;
			}
			case 5:
			{
				string dotare;
				cout << "Dotare noua: ";
				cin.get();
				getline(cin, dotare);
				objCarburant->inserareDotare(dotare);
				break;
			}
			case 6:
			{
				double pret;

				while (true)
				{
					string comandaStr;
					cout << "\nPret nou: ";
					getline(cin, comandaStr);
					if (comandaStr == "")
						getline(cin, comandaStr);
					try
					{
						pret = stodException(comandaStr);
						if (pret < 0)
							throw out_of_range("\nPretul nu poate fi negativ!\n");
						objCarburant->setPret(pret);
						break;
					}
					catch (const invalid_argument& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
					
				}

				break;
			}
			case 7:
			{
				string tipCarburant;
				cout << "Tip carburant nou: ";
				cin.get();
				getline(cin, tipCarburant);
				objCarburant->setTipCarburant(tipCarburant);
				break;
			}
			case 8:
			{
				double consum;

				while (true)
				{
					string comandaStr;
					cout << "\nConsum nou: ";
					getline(cin, comandaStr);
					if (comandaStr == "")
						getline(cin, comandaStr);
					try
					{
						consum = stodException(comandaStr);
						if (consum < 0)
							throw out_of_range("\nConsumul nu poate fi negativ!\n");
						objCarburant->setConsum(consum);
						break;
					}
					catch (const invalid_argument& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (const out_of_range& e)

					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}

				
				break;
			}
			case 9:
			{

				k = 0;
				break;
			}
			default:
			{
				cout << "\nComanda invalida.\n";
				break;
			}

			}

		}
	}
	else
		if (typeid(*obj) == typeid(VehiculHibrid))
		{
			VehiculHibrid* objHibrid = dynamic_cast<VehiculHibrid*>(obj);
			obj = dynamic_cast<VehiculHibrid*>(obj);
			int k = 1;
			while (k == 1)
			{
				int comanda;
				cout << "\n1. Modificare marca\n";
				cout << "2. Modificare model\n";
				cout << "3. Modificare an fabricatie\n";
				cout << "4. Inserare informatie in istoric rulaj\n";
				cout << "5. Inserare informatie in dotari\n";
				cout << "6. Modificare pret\n";
				cout << "7. Modificare tip carburant\n";
				cout << "8. Modificare consum\n";
				cout << "9. Modificare tip hibrid\n";
				cout << "10. Modificare autonomie electrica (doar pentru Plug-In Hybrid)\n";
				cout << "11. Modificare timp incarcare (doar pentru Plug-In Hybrid)\n";
				cout << "\n12. Iesire din submeniu\n";
				
				while (true)
				{
					string comandaStr;
					cout << endl << "> ";
					getline(cin, comandaStr);
					if (comandaStr == "")
						getline(cin, comandaStr);
					try
					{
						comanda = stoiException(comandaStr);
						if (comanda < 1 || comanda > 12)
							throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
						else
							if (to_string(comanda) != comandaStr)
								throw myEx;
						break;
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (const invalid_argument& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}

				switch (comanda)
				{

				case 1:
				{
					string marca;
					cout << "Marca noua: ";
					cin.get();
					getline(cin, marca);
					objHibrid->setMarca(marca);
					break;
				}
				case 2:
				{
					string model;
					cout << "Model nou: ";
					cin.get();
					getline(cin, model);
					objHibrid->setModel(model);
					break;
				}
				case 3:
				{
					int anFabricatie;

					while (true)
					{
						string comandaStr;
						cout << "\nAn fabricatie nou: ";
						getline(cin, comandaStr);
						if (comandaStr == "")
							getline(cin, comandaStr);
						try
						{
							anFabricatie = stoiException(comandaStr);
							if (anFabricatie < 1700)
								throw out_of_range("\nAnul de fabricatie nu poate fi mai mic ca 1700!\n");
							else
								if (to_string(anFabricatie) != comandaStr)
									throw myEx;

							objHibrid->setAnFabricatie(anFabricatie);
							break;
						}
						catch (const out_of_range& e)
						{
							cout << e.what();
						}
						catch (MyException& e)
						{
							cout << e.what();
						}
						catch (...)
						{
							cout << "\nComanda invalida.\n";
						}
					}
					break;
				}
				case 4:
				{
					string data;
					double rulaj;

					while (true)
					{
						string comandaStr;
						cout << "\nData: ";
						cin >> data;
						cout << "\nRulaj: ";
						getline(cin, comandaStr);
						if (comandaStr == "")
							getline(cin, comandaStr);
						try
						{
							rulaj = stodException(comandaStr);
							objHibrid->inserareIstoricRulaj(data, rulaj);
							break;
						}
						catch (const invalid_argument& e)
						{
							cout << e.what();
						}
						catch (MyException& e)
						{
							cout << e.what();
						}
						catch (...)
						{
							cout << "\nComanda invalida.\n";
						}
					}
					break;
				}
				case 5:
				{
					string dotare;
					cout << "Dotare noua: ";
					cin.get();
					getline(cin, dotare);
					objHibrid->inserareDotare(dotare);
					break;
				}
				case 6:
				{
					double pret;

					while (true)
					{
						string comandaStr;
						cout << "\nPret nou: ";
						getline(cin, comandaStr);
						if (comandaStr == "")
							getline(cin, comandaStr);
						try
						{
							pret = stodException(comandaStr);
							if (pret < 0)
								throw out_of_range("\nPretul nu poate fi negativ!\n");
							objHibrid->setPret(pret);
							break;
						}
						catch (const invalid_argument& e)
						{
							cout << e.what();
						}
						catch (MyException& e)
						{
							cout << e.what();
						}
						catch (const out_of_range& e)
						{
							cout << e.what();
						}
						catch (...)
						{
							cout << "\nComanda invalida.\n";
						}

					}

					break;
				}
				case 7:
				{
					string tipCarburant;
					cout << "Tip carburant nou: ";
					cin.get();
					getline(cin, tipCarburant);
					objHibrid->setTipCarburant(tipCarburant);
					break;
				}
				case 8:
				{
					double consum;

					while (true)
					{
						string comandaStr;
						cout << "\nConsum nou: ";
						getline(cin, comandaStr);
						if (comandaStr == "")
							getline(cin, comandaStr);
						try
						{
							consum = stodException(comandaStr);
							if (consum < 0)
								throw out_of_range("\nConsumul nu poate fi negativ!\n");
							objHibrid->setConsum(consum);
							break;
						}
						catch (const invalid_argument& e)
						{
							cout << e.what();
						}
						catch (MyException& e)
						{
							cout << e.what();
						}
						catch (const out_of_range& e)
						{
							cout << e.what();
						}
						catch (...)
						{
							cout << "\nComanda invalida.\n";
						}
					}


					break;
				}
				case 9:
				{
					char tipHibrid;

					while (true)
					{
						string comandaStr;
						cout << "\nTip hibrid nou (M - Mild Hybrid, P - Plug-In Hybrid): ";
						getline(cin, comandaStr);
						if (comandaStr == "")
							getline(cin, comandaStr);
						try
						{
							tipHibrid = comandaStr[0];
							if(comandaStr.size() > 1)
								throw invalid_argument("\nTip hibrid invalid!\n");
							else
							if (tipHibrid != 'M' && tipHibrid != 'P')
								throw invalid_argument("\nTip hibrid invalid!\n");

							objHibrid->setTipHibrid(tipHibrid);
							break;
						}
						catch (const invalid_argument& e)
						{
							cout << e.what();
						}
					}
					break;
				}
				case 10:
				{
					try {
						if (objHibrid->getTipHibrid() == 'P')
						{
							double autonomieElectrica;

							while (true)
							{
								string comandaStr;
								cout << "Autonomie electrica noua: ";
								getline(cin, comandaStr);
								if (comandaStr == "")
									getline(cin, comandaStr);
								try
								{
									autonomieElectrica = stodException(comandaStr);
									if (autonomieElectrica < 0)
										throw out_of_range("\nAutonomia electrica nu poate fi negativa!\n");
									objHibrid->setAutonomieElectric(autonomieElectrica);
									break;
								}
								catch (const invalid_argument& e)
								{
									cout << e.what();
								}
								catch (MyException& e)
								{
									cout << e.what();
								}
								catch (const out_of_range& e)
								{
									cout << e.what();
								}
								catch (...)
								{
									cout << "\nComanda invalida.\n";
								}
							}
						}
						else
							throw invalid_argument("\nAutonomia electrica se poate modifica doar pentru Plug-In Hybrid!\nVehiculul selectat este Mild Hybrid.\n");
					}
					catch (const invalid_argument& e)
					{
						cout << e.what();
					}
					break;

				}
				case 11:
				{
					try {
						if (objHibrid->getTipHibrid() == 'P')
						{
							double timpIncarcare;
							
							while (true)
							{
								string comandaStr;
								cout << "Timp incarcare nou: ";
								getline(cin, comandaStr);
								if (comandaStr == "")
									getline(cin, comandaStr);
								try
								{
									timpIncarcare = stodException(comandaStr);
									if (timpIncarcare < 0)
										throw out_of_range("\nTimpul incarcare nu poate fi negativ!\n");
									objHibrid->setTimpIncarcare(timpIncarcare);
									break;
								}
								catch (const invalid_argument& e)
								{
									cout << e.what();
								}
								catch (MyException& e)
								{
									cout << e.what();
								}
								catch (const out_of_range& e)
								{
									cout << e.what();
								}
								catch (...)
								{
									cout << "\nComanda invalida.\n";
								}
							}
						}
						else
							throw invalid_argument("\nTimpul incarcare se poate modifica doar pentru Plug-In Hybrid!\nVehiculul selectat este Mild Hybrid.\n");
					}
					catch (const invalid_argument& e)
					{
						cout << e.what();
					}
					break;
				}
				case 12:
				{
					k = 0;
					break;
				}
				default:
				{
					cout << "\nComanda invalida.\n";
					break;
				}

				}
			}

		}
}

// MODIFICARE OBIECTE DIN MENIU
void Singleton::modificareObject(Client& obj)
{
		int k = 1;
		while (k == 1)
		{
		int comanda;
		cout << "\n1. Modificare nume\n";
		cout << "2. Modificare vehicule cumparate\n";
		cout << "3. Modificare plata ramasa\n";
		cout << "4. Inserare informatie in istoric plati\n";
		cout << "\n5. Iesire din submeniu\n";
		
		while (true)
		{
			string comandaStr;
			cout << endl << "> ";
			getline(cin, comandaStr);
			if (comandaStr == "")
				getline(cin, comandaStr);
			try
			{
				comanda = stoiException(comandaStr);
				if (comanda < 1 || comanda > 5)
					throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
				else
					if (to_string(comanda) != comandaStr)
						throw myEx;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}


		switch (comanda)
		{

		case 1:
		{
			string nume;
			cout << "Nume nou: ";
			cin.get();
			getline(cin, nume);
			obj.setNume(nume);
			break;
		}
		case 2:
		{
			vector<Vehicul*> vehiculeObj = obj.getVehicule();
			if (vehiculeObj.size())
			{
				int index;

				while (true)
				{
					string comandaStr;
					cout << "Indexul vehiculului cumparat de modificat: ";
					getline(cin, comandaStr);
					if (comandaStr == "")
						getline(cin, comandaStr);
					try
					{
						index = stoiException(comandaStr);
						if (index - 1 < 0 || index - 1 >= vehiculeObj.size())
							throw out_of_range("\nIndex invalid!\n");
						else
							if (to_string(index) != comandaStr)
								throw myEx;
						
						Vehicul* vehicul = vehiculeObj[index - 1];
						modificareObject(vehicul);


						break;
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
						cout << "Trebuie sa introduci un index care apartine intervalului [1, " << vehiculeObj.size() << "].\n\n";
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}
			}
			else
			{
				cout << "\nClientul nu are vehicule cumparate.\n";
				break;
			}

			/*int index;
			cout << "Indexul vehiculului cumparat de modificat: ";
			cin >> index;
			
			vector<Vehicul*> vehiculeObj = obj.getVehicule();
			if (index - 1 < 0 || index - 1 >= vehiculeObj.size())
			{
				throw "Index invalid!\n";
				break;
			}
			else
			{
				Vehicul* vehicul = vehiculeObj[index - 1];
				modificareObject(vehicul);
			}*/
			break;
			
		}
		case 3:
		{
			double plataRamasa;
			
			while (true)
			{
				string comandaStr;
				cout << "Plata ramasa noua: ";
				getline(cin, comandaStr);
				if (comandaStr == "")
					getline(cin, comandaStr);
				try
				{
					plataRamasa = stodException(comandaStr);
					if (plataRamasa < 0)
						throw out_of_range("\nPlata ramasa nu poate fi negativa!\n");
					obj.setPlataRamasa(plataRamasa);
					break;
				}
				catch (const invalid_argument& e)
				{
					cout << e.what();
				}
				catch (MyException& e)
				{
					cout << e.what();
				}
				catch (const out_of_range& e)
				{
					cout << e.what();
				}
				catch (...)
				{
					cout << "\nComanda invalida.\n";
				}
			}
		
			break;
		}
		case 4:
		{
			string data;
			double suma;
			
			while (true)
			{
				string comandaStr;
				cout << "\nData: ";
				cin >> data;
				cout << "\nSuma platita: ";
				getline(cin, comandaStr);
				if (comandaStr == "")
					getline(cin, comandaStr);
				try
				{
					suma = stodException(comandaStr);
					try {
						obj.inserareIstoricPlati(data, suma);
					}
					catch (const invalid_argument& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
					
					break;
				}
				catch (const invalid_argument& e)
				{
					cout << e.what();
				}
				catch (MyException& e)
				{
					cout << e.what();
				}
				catch (...)
				{
					cout << "\nComanda invalida.\n";
				}
			}
			break;
		}
		case 5:
		{
			k = 0;
			break;
		}
		default:
		{
			cout << "\nComanda invalida.\n";
			break;
		}
		}
	}

}

void Singleton::modificareObject(Showroom& obj)
{
		int k = 1;
		while (k == 1)
		{
		int comanda;
		cout << "\n1. Modificare nume\n";
		cout << "2. Modificare vehicule disponibile\n";
		cout << "\n3. Iesire din submeniu\n";
		
		while (true)
		{
			string comandaStr;
			cout << endl << "> ";
			getline(cin, comandaStr);
			if (comandaStr == "")
				getline(cin, comandaStr);
			try
			{
				comanda = stoiException(comandaStr);
				if (comanda < 1 || comanda > 3)
					throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
				else
					if (to_string(comanda) != comandaStr)
						throw myEx;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}

		switch (comanda)
		{

		case 1:
		{
			string nume;
			cout << "Nume nou: ";
			cin.get();
			getline(cin, nume);
			obj.setNume(nume);
			break;
		}
		case 2:
		{
			int index;

			while (true)
			{
				string comandaStr;
				cout << "Indexul vehiculului de modificat: ";
				getline(cin, comandaStr);
				if (comandaStr == "")
					getline(cin, comandaStr);
				try
				{
					index = stoiException(comandaStr);
					if (index - 1 < 0 || index - 1 >= obj.getVehicule().size())
						throw out_of_range("\nIndex invalid!\n");
					else
						if (to_string(index) != comandaStr)
							throw myEx;

					list <Vehicul*> vehiculeObj = obj.getVehicule();
					list<Vehicul*>::iterator it = vehiculeObj.begin();
					advance(it, index - 1);
					modificareObject(*it);

					break;
				}
				catch (const out_of_range& e)
				{
					cout << e.what();
					cout << "Trebuie sa introduci un index care apartine intervalului [1, " << obj.getVehicule().size() << "].\n\n";
				}
				catch (MyException& e)
				{
					cout << e.what();
				}
				catch (...)
				{
					cout << "\nComanda invalida.\n";
				}
			}
			break;
		}
		case 3:
		{
			k = 0;
			break;
		}
		default:
		{
			cout << "\nComanda invalida.\n";
			break;
		}

		}
	}
}

void Singleton::modificareObject(Tranzactie& obj)
{
	int k = 1;
	while (k == 1)
	{
		int comanda;
		cout << "\n1. Modificare client\n";
		cout << "2. Modificare vehicul cumparat\n";
		cout << "3. Modificare suma platita\n";
		cout << "\n4. Iesire din submeniu\n";
		
		while (true)
		{
			string comandaStr;
			cout << endl << "> ";
			getline(cin, comandaStr);
			if (comandaStr == "")
				getline(cin, comandaStr);
			try
			{
				comanda = stoiException(comandaStr);
				if (comanda < 1 || comanda > 4)
					throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
				else
					if (to_string(comanda) != comandaStr)
						throw myEx;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}

		switch (comanda)
		{

		case 1:
		{
			Client aux;
			aux = obj.getClient();
			modificareObject(aux);
			obj.setClient(aux);
			break;
		}
		case 2:
		{
			Vehicul* aux;
			aux = obj.getVehiculCumparat();
			/*cout << typeid(*obj.getVehiculCumparat()).name();
			cout << *aux;*/
			modificareObject(aux);

			obj.setVehiculCumparat(aux);
			break;
		}
		case 3:
		{
			double sumaPlatita;

			while (true)
			{
				string comandaStr;
				cout << "Suma platita noua: ";
				getline(cin, comandaStr);
				if (comandaStr == "")
					getline(cin, comandaStr);
				try
				{
					sumaPlatita = stodException(comandaStr);
					if (sumaPlatita < 0)
						throw out_of_range("\nSuma platita nu poate fi negativa!\n");
					obj.setSumaPlatita(sumaPlatita);
					break;
				}
				catch (const invalid_argument& e)
				{
					cout << e.what();
				}
				catch (MyException& e)
				{
					cout << e.what();
				}
				catch (const out_of_range& e)
				{
					cout << e.what();
				}
				catch (...)
				{
					cout << "\nComanda invalida.\n";
				}
			}
			break;
		}
		case 4:
		{
			k = 0;
			break;
		}
		default:
		{
			cout << "\nComanda invalida.\n";
			break;
		}

		}
	}
}



// ADAUGARE OBIECTE DEJA CREATE IN VECTORII MENIULUI
void Singleton::adaugareObiect(Tranzactie* obj)
{
    tranzactii.push_back(obj);
}

void Singleton::adaugareObiect(Showroom obj)
{
	showroomuri.push_back(obj);
}

void Singleton::adaugareObiect(Client obj)
{
	clienti.push_back(obj);
}

// ADAUGARE OBIECTE DEJA CREATE IN VECTORII MENIULUI VEHICUL*
void Singleton::adaugareObiect(Vehicul* obj)
{
	Vehicul* v = obj->clone();
	vehicule.push_back(v);
}

// AFISARE VEHICULE DIN SHOWROOM SAU CLIENT
template <class T = Showroom>
void afisareVehicule(T obj)
{
	auto deAfisat = obj.getVehicule();
	int index = 1;
	for (Vehicul* vehicul : deAfisat)
	{
		cout << "\nVehiculul " << index++ << ":\n";
		cout << *vehicul;
	}
}

// FUNCTIA STOIEXCEPTION
int Singleton::stoiException(const string& sir)
{
	try
	{
		size_t lastChar;
		int numar = stoi(sir, &lastChar);
		if (lastChar != sir.length())
		{
			throw invalid_argument("");
		}
		return numar;
	}
	catch (const invalid_argument& e)
	{
		throw myEx;
		return 0;
	}
	catch (...)
	{
		throw range_error("");
		return 0;
	}
}

// FUNCTIA STODEXCEPTION
double Singleton::stodException(const string& sir)
{
	try
	{
		size_t lastChar;
		double numar = stod(sir, &lastChar);
		if (lastChar != sir.length())
		{
			throw invalid_argument("");
		}
		return numar;
	}
	catch (const invalid_argument& e)
	{
		throw myEx;
		return 0;
	}
	catch (...)
	{
		throw range_error("");
		return 0;
	}
}

Singleton* Singleton::instance = NULL;

// START MENU
void Singleton::startMenu()
{
	bool okAfisareEndlInceput = true;
	int k = 1, comanda;
	while (k == 1)
	{
		if (okAfisareEndlInceput == false)
		{
			cout << endl;
			cout << "// ------------------------------------------------------------------------------------------------------------------ //" << endl << endl;
		}
		if (okAfisareEndlInceput == true)
		{
			cout << "\n// --------------- DEALER AUTO --------------- // \n\n";
			cout << endl;
			okAfisareEndlInceput = false;
		}
		cout << "1. Intrare in submeniul Modele de vehicule\n";
		cout << "2. Intrare in submeniul Clienti\n";
		cout << "3. Intrare in submeniul Showroom\n";
		cout << "4. Intrare in submeniul Tranzactii\n";
		cout << "5. Generare tranzactie noua, folosind datele din submeniurile Clienti si Showroom\n";
		cout << "\n6. Iesire din program\n";
		
		while (true)
		{
			string comandaStr;
			cout << endl << "> ";
			getline(cin, comandaStr);
			if(comandaStr == "")
				getline(cin, comandaStr);
			try
			{
				comanda = stoiException(comandaStr);
				if (comanda < 1 || comanda > 6)
					throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
				else
					if (to_string(comanda) != comandaStr)
						throw myEx;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
			catch (MyException& e)
			{
				cout << e.what();
			}
			catch (...)
			{
				cout << "\nComanda invalida.\n";
			}
		}

		switch (comanda)

		{

		case 1:
		{
			int ramaiInVehicul = 1;
			while (ramaiInVehicul == 1)
			{
				int comandaVehicul;
				cout << endl;
				cout << "// ------------------------------------------------------------------------------------------------------------------ //";
				cout << endl << endl;
				cout << "1. Adaugare model de vehicul\n";
				cout << "2. Afisare tuturor modelelor de vehicule\n";
				cout << "3. Afisare detaliata al unui vehicul - detalii motor, valoarea reala, costul de folosire si intretinere\n";
				cout << "4. Stergere vehicul\n";
				cout << "5. Modificare model vehicul\n";
				cout << "\n6. Iesire din submeniul Modele de vehicule\n";
				
				while (true)
				{
					string comandaVehiculStr;
					cout << endl << "> ";
					getline(cin, comandaVehiculStr);
					if (comandaVehiculStr == "")
						getline(cin, comandaVehiculStr);
					try
					{
						comandaVehicul = stoiException(comandaVehiculStr);
						if (comandaVehicul < 1 || comandaVehicul > 6)
							throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
						else
							if (to_string(comandaVehicul) != comandaVehiculStr)
								throw myEx;
						break;
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}

				switch (comandaVehicul)
				{

				case 1:
				{
					Vehicul* v;
					try
					{
						 v = creareObject<Vehicul*>();
						 adaugareObiect(v);
						 cout << "\nVehiculul a fost adaugat cu succes.\n";
					}
					catch (const invalid_argument& e)
					{
						cout << e.what();
						cout << "Vehiculul nu a fost adaugat.\n";
					}
					break;

				}
				case 2:
				{
					int index = 1;
					for (Vehicul* v : vehicule)
					{
						cout << "\n\nVehiculul " << index++ << ":\n";
						if(typeid(*v) == typeid(VehiculCarburant))
							printObject(*(dynamic_cast<VehiculCarburant*>(v)));
						else
							if (typeid(*v) == typeid(VehiculHibrid))
								printObject(*(dynamic_cast<VehiculHibrid*>(v)));
							else
								printObject(v);
					}
					if(vehicule.size() == 0)
						cout << "\nNu exista vehicule de afisat.\n";
					break;
				}
				case 3:
				{
					if (vehicule.size() != 0)
					{
						int index = 1;
						for (Vehicul* v : vehicule)
						{
							cout << "\nVehiculul " << index++ << ":\n";
							cout << v->getMarca() << " " << v->getModel() << "\n";
						}

						index = 0;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul vehiculului: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								index = stoiException(comandaStr);
								if (index < 1 || index > vehicule.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunui vehicul!\n");
								else
									if (to_string(index) != comandaStr)
										throw myEx;

								if (typeid(*vehicule[index - 1]) == typeid(VehiculCarburant))
								{
									InfoVehicul <VehiculCarburant> infoCarburant;
									infoCarburant.info(dynamic_cast<VehiculCarburant&>(*vehicule[index - 1]));
								}
								else
									if (typeid(*vehicule[index - 1]) == typeid(VehiculHibrid))
									{
										InfoVehicul <VehiculHibrid> infoHibrid;
										infoHibrid.info(dynamic_cast<VehiculHibrid&>(*vehicule[index - 1]));
									}

								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << vehicule.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}
					}
					else
						cout << "\nNu exista vehicule de afisat.\n";
					break;
				}
				case 4:
				{
					int index = 1;
					if (vehicule.size() != 0)
					{
						for (Vehicul* v : vehicule)
						{
							cout << "\n\nVehiculul " << index++ << ":\n";
							if (typeid(*v) == typeid(VehiculCarburant))
								printObject(*(dynamic_cast<VehiculCarburant*>(v)));
							else
								if (typeid(*v) == typeid(VehiculHibrid))
									printObject(*(dynamic_cast<VehiculHibrid*>(v)));
								else
									printObject(v);
						}
						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul vehiculului de sters: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > vehicule.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunui vehicul!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								delete vehicule[comanda - 1];
								vehicule.erase(vehicule.begin() + comanda - 1);
								cout << "\nVehiculul a fost sters cu succes.\n";
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << vehicule.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";

							}
						}
						
					}
					else
						cout << "\nNu exista vehicule de sters.\n";
					break;
				}
				case 5:
				{
					int index = 1;
					if (vehicule.size() != 0)
					{
						for (Vehicul* v : vehicule)
						{
							cout << "\n\nVehiculul " << index++ << ":\n";
							if (typeid(*v) == typeid(VehiculCarburant))
								printObject(*(dynamic_cast<VehiculCarburant*>(v)));
							else
								if (typeid(*v) == typeid(VehiculHibrid))
									printObject(*(dynamic_cast<VehiculHibrid*>(v)));
								else
									printObject(v);
						}

						int comanda;
						
						while (true)
						{
								string comandaStr;
								cout << "\nIndexul vehiculului de modificat: ";
								getline(cin, comandaStr);
								if (comandaStr == "")
									getline(cin, comandaStr);
								try
								{
									comanda = stoiException(comandaStr);
									if (comanda < 1 || comanda > vehicule.size())
										throw out_of_range("\nNumarul introdus nu corespunde niciunui vehicul!\n");
									else
										if (to_string(comanda) != comandaStr)
											throw myEx;
									modificareObject(vehicule[comanda - 1]);
									cout << "\nVehiculul a fost modificat cu succes.\n";
									break;
								}
								catch (const out_of_range& e)
								{
									cout << e.what();
									cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << vehicule.size() << "].\n";
								}
								catch (MyException& e)
								{
									cout << e.what();
								}
								catch (...)
								{
									cout << "\nComanda invalida.\n";
								}
						}
					}
					else
						cout << "\nNu exista vehicule de modificat.\n";
					break;
				}
				case 6:
				{
					ramaiInVehicul = 0;
					break;
				}
				default:
				{
					cout << "\nComanda invalida.\n";
					break;
				}

				}
			}
			break;
		}
		case 2:
		{
			int ramaiInClient = 1;
			while (ramaiInClient == 1)
			{
				int comandaClient;
				cout << endl;
				cout << "// ------------------------------------------------------------------------------------------------------------------ //";
				cout << endl << endl;
				cout << "1. Adaugare client\n";
				cout << "2. Afisare clienti\n";
				cout << "3. Stergere client\n";
				cout << "4. Modificare client\n";
				cout << "\n5. Iesire din submeniul Clienti\n";


				while (true)
				{
					string comandaClientStr;
					cout << endl << "> ";
					getline(cin, comandaClientStr);
					if (comandaClientStr == "")
						getline(cin, comandaClientStr);
					try
					{
						comandaClient = stoiException(comandaClientStr);
						if (comandaClient < 1 || comandaClient > 5)
							throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
						else
							if (to_string(comandaClient) != comandaClientStr)
								throw myEx;
						break;
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}

				switch (comandaClient)
				{

				case 1:
				{
					// cin.get();
					Client c = creareObject<Client>();
					adaugareObiect(c);
					//cout << "\nClientul a fost adaugat cu succes.\n";
					break;
				}
				case 2:
				{
					int index = 1;
					for (Client c : clienti)
					{
						cout << "\n\nClientul " << index++ << ":\n";
						printObject(c);
					}
					if (clienti.size() == 0)
						cout << "\nNu exista clienti de afisat.\n";
					break;
				}
				case 3:
				{
					int index = 1;
					if (clienti.size() != 0)
					{
						for (Client c : clienti)
						{
							cout << "\n\nClientul " << index++ << ":\n";
							printObject(c);
						}

						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul clientului de sters: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > clienti.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunui client!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								clienti.erase(clienti.begin() + comanda - 1);
								cout << "\nClientul a fost sters cu succes.\n";
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << clienti.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}
					}
					else
						cout << "\nNu exista clienti de sters.\n";
					break;
				}
				case 4:
				{
					int index = 1;
					if (clienti.size() != 0)
					{
						for (Client c : clienti)
						{
							cout << "\n\nClientul " << index++ << ":\n";
							printObject(c);
						}

						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul clientului de modificat: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > clienti.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunui client!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								modificareObject(clienti[comanda - 1]);
								cout << "\nClientul a fost modificat cu succes.\n";
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << clienti.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}
						
					}
					else
						cout << "\nNu exista clienti de modificat.\n";
					break;
				}
				case 5:
				{
					ramaiInClient = 0;
					break;
				}
				default:
				{
					cout << "\nComanda invalida.\n";
					break;
				}

				}
			}
			break;
		}
		case 3:
		{
			int ramaiInShowroom = 1;
			while (ramaiInShowroom == 1)
			{
				int comandaShowroom;
				cout << endl;
				cout << "// ------------------------------------------------------------------------------------------------------------------ //";
				cout << endl << endl;
				cout << "1. Adaugare showroom\n";
				cout << "2. Afisare showroomuri\n";
				cout << "3. Stergere showroom\n";
				cout << "4. Modificare showroom\n";
				cout << "5. Adaugare vehicul din lista cu modele de vehicule\n";
				cout << "6. Afisare detaliata a unui showroom - vehicule disponibile, numar de vehicule, valoarea totala a vehiculelor\n";
				cout << "\n7. Iesire din submeniul Showroom\n";
				
				while (true)
				{
					string comandaShowroomStr;
					cout << endl << "> ";
					getline(cin, comandaShowroomStr);
					if (comandaShowroomStr == "")
						getline(cin, comandaShowroomStr);
					try
					{
						comandaShowroom = stoiException(comandaShowroomStr);
						if (comandaShowroom < 1 || comandaShowroom > 7)
							throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
						else
							if (to_string(comandaShowroom) != comandaShowroomStr)
								throw myEx;
						break;
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}

				switch (comandaShowroom)
				{

				case 1:
				{
					//cin.get();
					Showroom s = creareObject<Showroom>();
					adaugareObiect(s);
					cout << "\nShowroomul a fost adaugat cu succes.\n";
					break;
				}
				case 2:
				{
					int index = 1;
					for (Showroom s : showroomuri)
					{
						cout << "\n\nShowroomul " << index++ << ":\n";
						printObject(s);
					}
					if(showroomuri.size() == 0)
						cout << "\nNu exista showroomuri de afisat.\n";
					break;
				}
				case 3:
				{
					int index = 1;
					for (Showroom s : showroomuri)
					{
						cout << "\n\nShowroomul " << index++ << ":\n";
						printObject(s);
					}
					if(showroomuri.size() == 0)
						cout << "\nNu exista showroomuri de sters.\n";
					else
					{
						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul showroomului de sters: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > showroomuri.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunui showroom!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								showroomuri.erase(showroomuri.begin() + comanda - 1);
								cout << "\nShowroomul a fost sters cu succes.\n";
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << showroomuri.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}
					}
					break;
				}
				case 4:
				{
					int index = 1;
					for (Showroom s : showroomuri)
					{
						cout << "\n\nShowroomul " << index++ << ":\n";
						printObject(s);
					}

					if(showroomuri.size() == 0)
						cout << "\nNu exista showroomuri de modificat.\n";
					else
					{
						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul showroomului de modificat: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > showroomuri.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunui showroom!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								modificareObject(showroomuri[comanda - 1]);
								cout << "\nShowroomul a fost modificat cu succes.\n";
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << showroomuri.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}
					}
					break;
				}
				
				case 5:
				{
					int index = 1;
					for (Showroom s : showroomuri)
					{
						cout << "\n\nShowroomul " << index++ << ":\n";
						printObject(s);
					}

					if(showroomuri.size() == 0)
						cout << "\nNu exista showroomuri la care sa se adauge vehicule.\n";
					else
					{
						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul showroomului la care se va adauga vehiculul: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > showroomuri.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunui showroom!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << showroomuri.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}

						list <Vehicul*> vehiculeObj = showroomuri[comanda - 1].getVehicule();

						if (vehiculeObj.size())
						{
							int indexVehicul = 1;
							for (Vehicul* v : vehicule)
							{
								cout << "\n\nVehiculul " << indexVehicul++ << ":\n";
								if (typeid(*v) == typeid(VehiculCarburant))
									printObject(*(dynamic_cast<VehiculCarburant*>(v)));
								else
									if (typeid(*v) == typeid(VehiculHibrid))
										printObject(*(dynamic_cast<VehiculHibrid*>(v)));
									else
										printObject(v);
							}

							indexVehicul = 0;

							while (true)
							{
								cout << "\nIndexul vehiculului de adaugat: ";
								string comandaStr;
								getline(cin, comandaStr);
								if (comandaStr == "")
									getline(cin, comandaStr);
								try
								{
									indexVehicul = stoiException(comandaStr);
									if (indexVehicul < 1 || indexVehicul > vehicule.size())
										throw out_of_range("\nNumarul introdus nu corespunde niciunui vehicul!\n");
									else
										if (to_string(indexVehicul) != comandaStr)
											throw myEx;
									break;
								}
								catch (const out_of_range& e)
								{
									cout << e.what();
									cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << vehicule.size() << "].\n";
								}
								catch (MyException& e)
								{
									cout << e.what();
								}
								catch (...)
								{
									cout << "\nComanda invalida.\n";
								}
							}

							Vehicul* v = vehicule[indexVehicul - 1]->clone();
							showroomuri[comanda - 1] = showroomuri[comanda - 1] + v;
							cout << "\nVehiculul a fost adaugat cu succes.\n";
						}
						else
						{
							cout << "\nNu exista vehicule disponibile in showroomul selectat.\n";
							break;
						}
					}

					break;
				}
				case 6:
				{

					int index = 1;
					for (Showroom s : showroomuri)
					{
						cout << "\n\nShowroomul " << index++ << ": ";
						cout << s.getNumeShowroom() << "\n";
					}
					if (showroomuri.size() == 0)
					{
						cout << "\nNu exista showroomuri de afisat.\n";
						break;
					}
					else
					{
						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul showroomului la care doriti sa aflati informatii detaliate: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > showroomuri.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunui showroom!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								
								
								InfoVehicul <Showroom> infoShowroom;
								infoShowroom.info(showroomuri[comanda - 1]);
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << showroomuri.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}
					}

					break;
				}
				case 7:
				{
					ramaiInShowroom = 0;
					break;
				}
				default:
				{
					cout << "\nComanda invalida.\n";
					break;
				}

				}
			}
			break;
		}
		case 4:
		{
			int ramaiInTranzactii = 1;
			while (ramaiInTranzactii == 1)
			{
				int comandaTranzactii;
				cout << endl;
				cout << "// ------------------------------------------------------------------------------------------------------------------ //";
				cout << endl << endl;
				cout << "1. Adaugare tranzactie\n";
				cout << "2. Afisare tranzactii\n";
				cout << "3. Stergere tranzactie\n";
				cout << "4. Modificare tranzactie\n";
				cout << "\n5. Iesire din submeniul Tranzactii\n";
				
				while (true)
				{
					string comandaTranzactiiStr;
					cout << endl << "> ";
					getline(cin, comandaTranzactiiStr);
					if (comandaTranzactiiStr == "")
						getline(cin, comandaTranzactiiStr);
					try
					{
						comandaTranzactii = stoiException(comandaTranzactiiStr);
						if (comandaTranzactii < 1 || comandaTranzactii > 5)
							throw out_of_range("\nNumarul introdus nu corespunde niciunei comenzi!\n");
						else
							if (to_string(comandaTranzactii) != comandaTranzactiiStr)
								throw myEx;
						break;
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}

				switch (comandaTranzactii)
				{

				case 1:
				{
					//cin.get();
                    Tranzactie* t = creareObject<Tranzactie*>();
                    adaugareObiect(t);
					//cout << "\nTranzactia a fost adaugata cu succes.\n";
					break;
				}
				case 2:
				{
					int index = 1;
					for(Tranzactie* t : tranzactii)
					{
						cout << "\n\nTranzactia " << index++ << ":\n";
						printObject(*t);
					}
					if(tranzactii.size() == 0)
						cout << "\nNu exista tranzactii de afisat.\n";
					break;
				}
				case 3:
				{
					int index = 1;
					for (Tranzactie* t : tranzactii)
					{
						cout << "\n\nTranzactia " << index++ << ":\n";
						printObject(*t);
					}

					if (tranzactii.size() == 0)
					{
						cout << "\nNu exista tranzactii de sters.\n";
						break;
					}
					else
					{
						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul tranzactiei de sters: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > tranzactii.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunei tranzactii!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								tranzactii.erase(tranzactii.begin() + comanda - 1);
								cout << "\nTranzactia a fost stearsa cu succes.\n";
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << tranzactii.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}
					}					
					break;
				}
				case 4:
				{
					int index = 1;
					for (Tranzactie* t : tranzactii)
					{
						cout << "\n\nTranzactia " << index++ << ":\n";
						printObject(*t);
					}

					if (tranzactii.size() == 0)
					{
						cout << "\nNu exista tranzactii de modificat.\n";
						break;
					}
					else
					{
						int comanda;

						while (true)
						{
							string comandaStr;
							cout << "\nIndexul tranzactiei de modificat: ";
							getline(cin, comandaStr);
							if (comandaStr == "")
								getline(cin, comandaStr);
							try
							{
								comanda = stoiException(comandaStr);
								if (comanda < 1 || comanda > tranzactii.size())
									throw out_of_range("\nNumarul introdus nu corespunde niciunei tranzactii!\n");
								else
									if (to_string(comanda) != comandaStr)
										throw myEx;
								modificareObject(*tranzactii[comanda - 1]);
								cout << "\nTranzactia a fost modificata cu succes.\n";
								break;
							}
							catch (const out_of_range& e)
							{
								cout << e.what();
								cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << tranzactii.size() << "].\n";
							}
							catch (MyException& e)
							{
								cout << e.what();
							}
							catch (...)
							{
								cout << "\nComanda invalida.\n";
							}
						}
					}

					break;
				}
				case 5:
				{
					ramaiInTranzactii = 0;
					break;
				}
				default:
				{
					cout << "\nComanda invalida.\n";
					break;
				}

				}
			}
			break;
		}
		case 5:
		{
			
			int indexShowroom = 1;
			for (Showroom s : showroomuri)
			{
				cout << "\n\nShowroomul " << indexShowroom++ << ":\n";
				printObject(s);
			}
			if (showroomuri.size())
			{
				indexShowroom = 0;
				while (true)
				{
					string comandaStr;
					cout << "\nIndexul showroomului: ";
					getline(cin, comandaStr);
					if (comandaStr == "")
						getline(cin, comandaStr);
					try
					{
						indexShowroom = stoiException(comandaStr);
						if (indexShowroom < 1 || indexShowroom > showroomuri.size())
							throw out_of_range("\nNumarul introdus nu corespunde niciunui showroom!\n");
						else
							if (to_string(indexShowroom) != comandaStr)
								throw myEx;
						break;
					}
					catch (const out_of_range& e)
					{
						cout << e.what();
						cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << showroomuri.size() << "].\n";
					}
					catch (MyException& e)
					{
						cout << e.what();
					}
					catch (...)
					{
						cout << "\nComanda invalida.\n";
					}
				}

				list <Vehicul*> vehiculeObj = showroomuri[indexShowroom - 1].getVehicule();
				int indexVehicul = 1;
				for (Vehicul* v : vehiculeObj)
				{
					cout << "\n\nVehiculul " << indexVehicul++ << ":\n";
					if (typeid(*v) == typeid(VehiculCarburant))
						printObject(*(dynamic_cast<VehiculCarburant*>(v)));
					else
						if (typeid(*v) == typeid(VehiculHibrid))
							printObject(*(dynamic_cast<VehiculHibrid*>(v)));
						else
							printObject(v);
				}

				if (vehiculeObj.size())
				{

					indexVehicul = 0;
					while (true)
					{
						string comandaStr;
						cout << "\nIndexul vehiculului de cumparat: ";
						getline(cin, comandaStr);
						if (comandaStr == "")
							getline(cin, comandaStr);
						try
						{
							indexVehicul = stoiException(comandaStr);
							if (indexVehicul < 1 || indexVehicul > vehiculeObj.size())
								throw out_of_range("\nNumarul introdus nu corespunde niciunui vehicul!\n");
							else
								if (to_string(indexVehicul) != comandaStr)
									throw myEx;
							break;
						}
						catch (const out_of_range& e)
						{
							cout << e.what();
							cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << vehiculeObj.size() << "].\n";
						}
						catch (MyException& e)
						{
							cout << e.what();
						}
						catch (...)
						{
							cout << "\nComanda invalida.\n";
						}
					}

					int indexClient = 1;
					for (Client c : clienti)
					{
						cout << "\n\nClientul " << indexClient++ << ":\n";
						printObject(c);
					}

					if (clienti.size())
					{
						indexClient = 0;

						while (true)
						{
								string comandaStr;
								cout << "\nIndexul clientului care cumpara vehiculul: ";
								getline(cin, comandaStr);
								if (comandaStr == "")
									getline(cin, comandaStr);
								try
								{
									indexClient = stoiException(comandaStr);
									if (indexClient < 1 || indexClient > clienti.size())
										throw out_of_range("\nNumarul introdus nu corespunde niciunui client!\n");
									else
										if (to_string(indexClient) != comandaStr)
											throw myEx;
									
									int sumaPlatita;
									while (true)
									{
										string comandaStr;
										cout << "\nSuma platita: ";
										getline(cin, comandaStr);
										if (comandaStr == "")
											getline(cin, comandaStr);
										try
										{
											sumaPlatita = stoiException(comandaStr);
											if (sumaPlatita < 0)
												throw out_of_range("\nSuma platita nu poate fi negativa!\n");
											else
												if (to_string(sumaPlatita) != comandaStr)
													throw myEx;

											Vehicul* auxVehicul;
											list<Vehicul*>::iterator it = vehiculeObj.begin();
											advance(it, indexVehicul - 1);
											auxVehicul = *it;
											Tranzactie* t = new Tranzactie(clienti[indexClient - 1], auxVehicul->clone(), sumaPlatita);
											Vehicul* auxVehicul2;
											list <Vehicul*>::iterator it2 = vehiculeObj.begin();
											advance(it2, indexVehicul - 1);
											auxVehicul2 = *it2;
											clienti[indexClient - 1] = clienti[indexClient - 1] + auxVehicul2->clone();
											showroomuri[indexShowroom - 1] = showroomuri[indexShowroom - 1] - (indexVehicul - 1);
											adaugareObiect(t);
											clienti[indexClient - 1].setPlataRamasa(clienti[indexClient - 1].getPlataRamasa() + sumaPlatita);

											break;
										}
										catch (const out_of_range& e)
										{
											cout << e.what();
										}
										catch (MyException& e)
										{
											cout << e.what();
										}
										catch (...)
										{
											cout << "\nComanda invalida.\n";
										}
									}


									break;
								}
								catch (const out_of_range& e)
								{
									cout << e.what();
									cout << "Trebuie sa introduceti un index care apartine intervalului [1, " << clienti.size() << "].\n";
								}
								catch (MyException& e)
								{
									cout << e.what();
								}
								catch (...)
								{
									cout << "\nComanda invalida.\n";
								}
						}
					}
					else
					{
						cout << "\nNu exista vreun client care sa ia parte la procesul de vanzare.\n";
						break;
					}
					
				}
				else
				{
					cout << "\nShowroom-ul nu are vehicule disponibile.\n";
					break;
				}
			}
			else
			{
				cout << "\nNu exista showroomuri, astfel nu se poate genera o tranzactie.\n";
				break;
			}
					

			break;
		}
		case 6:
		{
			cout << "\nIesirea din program a fost finalizata cu succes. La revedere!\n";
			k = 0;
			break;
		}
		default:
		{
			cout << "\nComanda invalida.\n";
			break;
		}

		break;
		}

	}
}



int Vehicul::nrVehicule = 0;
int Tranzactie::nrTranzactii = 0;

template <class T>
vector <Observer<T>*> Subject<T>::observers;

int main()
{

	map<string, int> istoricRulaj1;
	istoricRulaj1["01-01-2017"] = 20000;
	istoricRulaj1["01-01-2020"] = 50000;
	set<string> dotari1;
	dotari1.insert("Aer conditionat");
	dotari1.insert("Servodirectie");
	map<string, int> istoricRulaj2;
	istoricRulaj2["01-01-2020"] = 10000;
	istoricRulaj2["01-01-2021"] = 30000;
	set<string> dotari2;
	dotari2.insert("Aer conditionat");
	dotari2.insert("Servodirectie");
	dotari2.insert("Geamuri electrice");
	VehiculCarburant v1("Dacia", "Logan", 2016, 2, istoricRulaj1, 2, dotari1, 6000, "Benzina", 12.6);
	VehiculHibrid v2("Toyota", "Prius", 2020, 2, istoricRulaj2, 3, dotari2, 12000, "Benzina", 7.5, 'P', 50, 8);
	Vehicul* pv1 = v1.clone();
	Vehicul* pv2 = v2.clone();

	Client c1("Popescu Ion", 0, {}, 0, {{"01-01-2024", 5000}, {"01-02-2024", 5000}});
	Client c2("Marin Gheorghe", 0, {}, 0, { {"01-01-2024", 1000}, {"01-02-2024", 1000} });

	Showroom s1("Showroom masini", 0, {});
	s1 = s1 + pv1;
	s1 = s1 + pv2;

	ConsoleObserver<Client> clientObserver;
	Subject<Client>::addObserver(&clientObserver);

	ConsoleObserver<Tranzactie> tranzactieObserver;
	Subject<Tranzactie>::addObserver(&tranzactieObserver);

	Singleton* s = Singleton::getInstance();

	s->adaugareObiect(pv1);
	s->adaugareObiect(pv2);
	s->adaugareObiect(c1);
	s->adaugareObiect(c2);
	s->adaugareObiect(s1);

	s->startMenu();

	delete pv1;
	delete pv2;
	return 0;
}
