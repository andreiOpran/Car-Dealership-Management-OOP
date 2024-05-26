/*

IDE: Visual Studio
Platform toolset: Visual Studio 2022 (v143)

*/

#include <iostream>
#include <cstring>
#include <string>
#include <typeinfo>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;


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

};


// --------- CLASA VEHICUL ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Vehicul : public IOInterfaceVehicul
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

// OPERATORUL >>
istream& Vehicul::citireVehicul(istream& in)
{
	istoricRulaj.clear();
	dotari.clear();

	cout << "Marca: ";
	in >> marca;
	cout << "Model: ";
	in >> model;
	cout << "An fabricatie: ";
	in >> anFabricatie;
	cout << "Numar inserari in istoricul rulajului: ";
	in >> nrInserariIstoricRulaj;
	if (nrInserariIstoricRulaj)
	{
		cout << "\nData si rulajul (km), separate printr-un spatiu:\n";
		for (int i = 0; i < nrInserariIstoricRulaj; i++)
		{
			cout << "Inserarea " << i + 1 << "/" << nrInserariIstoricRulaj << ": ";
			string data;
			int rulaj;
			in >> data >> rulaj;
			istoricRulaj.insert({ data, rulaj });
		}
	}
	cout << "Numar dotari: ";
	in >> nrDotari;
	if (nrDotari)
	{
		in.get();
		for (int i = 0; i < nrDotari; i++)
		{
			cout << "Dotarea " << i + 1 << "/" << nrDotari << ": ";
			string dotare;
			getline(in, dotare);
			dotari.insert(dotare);
		}
	}
	cout << "Pret: ";
	in >> pret;
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
	cout << "Consum: ";
	in >> consum;
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
	cout << "Tip hibrid (P - plug-in, M - mild): ";
	
	bool introducereTip = false;
	string tip;
	while (introducereTip == false)
	{
		in >> tip;
		if (tip == "P")
		{
			tipHibrid = 'P';
			introducereTip = true;
		}
		else
			if (tip == "M")
			{
				tipHibrid = 'M';
				introducereTip = true;
			}
			else
			{
				cout << "Tip hibrid invalid! Introduceti din nou tipul hibridului (P - plug-in, M - mild): ";
			}
	}
	if (tipHibrid == 'P')
	{
		cout << "Autonomie electric (km): ";
		in >> autonomieElectricPlugIn;
		cout << "Timp incarcare (ore): ";
		in >> timpIncarcarePlugIn;
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


// --------- CLASA CLIENT ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Client
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

};

// CONSTRUCTOR FARA PARAMETRI
Client::Client() : nume("Necunoscut"), nrVehiculeCumparate(0), vehiculeCumparate(), plataRamasa(0), istoricPlati() {}

// CONSTRUCTOR CU PARAMETRI
Client::Client(string nume, int nrVehiculeCumparate, vector <Vehicul*> vehiculeCumparate, double plataRamasa, map <string, double> istoricPlati) :
	nume(nume), nrVehiculeCumparate(nrVehiculeCumparate), vehiculeCumparate(vehiculeCumparate), plataRamasa(plataRamasa), istoricPlati(istoricPlati) {}

// COPY CONSTRUCTOR
Client::Client(const Client& obj) : nume(obj.nume), nrVehiculeCumparate(obj.nrVehiculeCumparate), vehiculeCumparate(obj.vehiculeCumparate), plataRamasa(obj.plataRamasa), istoricPlati(obj.istoricPlati) {}

// OPERATORUL =
Client& Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->nume = obj.nume;
		this->nrVehiculeCumparate = obj.nrVehiculeCumparate;
		this->vehiculeCumparate = obj.vehiculeCumparate;
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
istream& operator >>(istream& in, Client& obj)
{
	int index = 0;

	cout << "Nume: ";
	getline(in, obj.nume);
	cout << "Numar vehicule cumparate: ";
	in >> obj.nrVehiculeCumparate;
	obj.vehiculeCumparate.clear();
	for (int i = 0; i < obj.nrVehiculeCumparate; i++)
	{
		cout << "\nVehiculul " << i + 1 << ":\n";
		cout << "Tipul vehiculului (C - carburant, H - hibrid): ";
		bool introducereTip = false;
		string tip;
		cin.get();
		while (introducereTip == false)
		{
			getline(in, tip);
			if (tip == "C")
			{
				Vehicul* v = new VehiculCarburant();
				in >> *v;
				obj.vehiculeCumparate.push_back(v);
				introducereTip = true;
			}
			else
				if (tip == "H")
				{
					Vehicul* v = new VehiculHibrid();
					in >> *v;
					obj.vehiculeCumparate.push_back(v);
					introducereTip = true;
				}
				else
				{
					//throw "Tip vehicul invalid!";
					cout << "\nTip vehicul invalid! Introduceti din nou tipul vehiculului (C - carburant, H - hibrid): ";
				}
		}
	}
	cout << "Plata ramasa: ";
	in >> obj.plataRamasa;

	obj.istoricPlati.clear();

	cout << "Istoric plati:\n";
	cout << "Numar inserari in istoric plati: ";
	in >> index;
	if (index)
	{
		cout << "Data si suma platita, separate printr-un spatiu:\n";
		string data;
		double suma;
		for (int i = 0; i < index; i++)
		{
			in >> data >> suma;
			obj.istoricPlati.insert({ data, suma });
		}
	}
	return in;
}

// OPERATORUL <<
ostream& operator <<(ostream& out, const Client& obj)
{
	int index = 1;

	out << "\nNume: " << obj.nume << "\n";
	out << "Numar vehicule cumparate: " << obj.nrVehiculeCumparate << "\n";
	out << "Vehicule cumparate:\n";
	for (int i = 0; i < obj.nrVehiculeCumparate; i++)
	{
		out << "\nVehiculul " << i + 1 << ":\n";
		out << *obj.vehiculeCumparate[i];
	}
	out << "\nPlata ramasa: " << obj.plataRamasa << "\n";
	out << "Istoric plati:\n";
	for (pair<string, double> p : obj.istoricPlati)
	{
		out << "Plata " << index++ << ": " << p.first << " " << p.second << "\n";
	}
	return out;
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
};

// CONSTRUCTOR FARA PARAMETRI
Showroom::Showroom() : nume("Necunoscut"), nrVehiculeDisponibile(0), vehiculeDisponibile() {}

// CONSTRUCTOR CU PARAMETRI
Showroom::Showroom(string nume, int nrVehiculeDisponibile, list <Vehicul*> vehiculeDisponibile) :
	nume(nume), nrVehiculeDisponibile(nrVehiculeDisponibile), vehiculeDisponibile(vehiculeDisponibile) {}

// COPY CONSTRUCTOR
Showroom::Showroom(const Showroom& obj) : nume(obj.nume), nrVehiculeDisponibile(obj.nrVehiculeDisponibile), vehiculeDisponibile(obj.vehiculeDisponibile) {}

// OPERATORUL =
Showroom& Showroom::operator=(const Showroom& obj)
{
	if (this != &obj)
	{
		this->nume = obj.nume;
		this->nrVehiculeDisponibile = obj.nrVehiculeDisponibile;
		this->vehiculeDisponibile = obj.vehiculeDisponibile;
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
	cout << "Numar vehicule disponibile: ";
	in >> obj.nrVehiculeDisponibile;
	obj.vehiculeDisponibile.clear();
	for (int i = 0; i < obj.nrVehiculeDisponibile; i++)
	{
		cout << "\nVehiculul " << i + 1 << ":\n";
		cout << "Tipul vehiculului (C - carburant, H - hibrid): ";
		bool introducereTip = false;
		string tip;
		cin.get();
		while (introducereTip == false)
		{
			getline(in, tip);
			if (tip == "C")
			{
				Vehicul* v = new VehiculCarburant();
				in >> *v;
				obj.vehiculeDisponibile.push_back(v);
				introducereTip = true;
			}
			else
				if (tip == "H")
				{
					Vehicul* v = new VehiculHibrid();
					in >> *v;
					obj.vehiculeDisponibile.push_back(v);
					introducereTip = true;
				}
				else
				{
					//throw "Tip vehicul invalid!";
					cout << "\nTip vehicul invalid! Introduceti din nou tipul vehiculului (C - carburant, H - hibrid): ";
				}
		}
	}
	return in;
}

// OPERATORUL <<
ostream& operator <<(ostream& out, const Showroom& obj)
{
	int index = 1;

	out << "\nNume: " << obj.nume << "\n";
	out << "Numar vehicule disponibile: " << obj.nrVehiculeDisponibile << "\n";
	out << "Vehicule disponibile:\n";
	for (Vehicul* v : obj.vehiculeDisponibile)
	{
		out << "\nVehiculul " << index++ << ":\n";
		out << *v;
	}
	return out;
}


// --------- CLASA TRANZACTIE ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Tranzactie
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
};

// CONSTRUCTOR FARA PARAMETRI
Tranzactie::Tranzactie() : idTranzactie(++nrTranzactii + 1000), client(), vehiculCumparat(), sumaPlatita(0) {}

// CONSTRUCTOR CU PARAMETRI
Tranzactie::Tranzactie(Client client, Vehicul* vehiculCumparat, double sumaPlatita) :
	idTranzactie(++nrTranzactii + 2000), client(client), vehiculCumparat(vehiculCumparat), sumaPlatita(sumaPlatita) {}

// COPY CONSTRUCTOR
Tranzactie::Tranzactie(const Tranzactie& obj) : idTranzactie(obj.idTranzactie), client(obj.client), vehiculCumparat(obj.vehiculCumparat), sumaPlatita(obj.sumaPlatita) {}

// OPERATORUL =
Tranzactie& Tranzactie::operator=(const Tranzactie& obj)
{
	if (this != &obj)
	{
		this->client = obj.client;
		this->vehiculCumparat = obj.vehiculCumparat;
		this->sumaPlatita = obj.sumaPlatita;
	}
	return *this;
}

// DESTRUCTOR
Tranzactie::~Tranzactie() 
{
	delete vehiculCumparat;
}

// OPERATORUL >>
istream& operator >> (istream& in, Tranzactie& obj)
{
	cout << "Clientul:\n";
	in >> obj.client;
	cout << "Vehiculul cumparat:\n";
	cout << "Tipul vehiculului (C - carburant, H - hibrid): ";
	bool introducereTip = false;
	string tip;
	cin.get();
	while (introducereTip == false)
	{
		getline(in, tip);
		if (tip == "C")
		{
			Vehicul* v = new VehiculCarburant();
			in >> *v;
			obj.vehiculCumparat = v;
			introducereTip = true;
		}
		else
			if (tip == "H")
			{
				Vehicul* v = new VehiculHibrid();
				in >> *v;
				obj.vehiculCumparat = v;
				introducereTip = true;
			}
			else
			{
				//throw "Tip vehicul invalid!";
				cout << "\nTip vehicul invalid! Introduceti din nou tipul vehiculului (C - carburant, H - hibrid): ";
			}
	}
	cout << "Suma platita: ";
	in >> obj.sumaPlatita;
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

int Vehicul::nrVehicule = 0;
int Tranzactie::nrTranzactii = 0;

int main()
{

	
	return 0;
}
