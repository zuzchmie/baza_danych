#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

class Osoba
{
protected:
    int id = 0;
    std::string name = " ";
    std::string surname = " ";

public:
    Osoba()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Osoba(int i, std::string n, std::string s) : id(i), name(n), surname(s)
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    virtual ~Osoba()
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class Klient : Osoba
{
protected:
    std::string email = " ";
    std::string number = " ";

public:
    Klient()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Klient(int i, std::string n, std::string s, std::string e, std::string num) : Osoba(i, n, s)
    {
        number = num;
        email = e;
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Klient()
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    std::string getSurname() const
    {
        return surname;
    }

    friend std::ostream &operator<<(std::ostream &str, const Klient &klient)
    {
        return str << "id: " << klient.id << " | name: " << klient.name << " | surname: "
                   << klient.surname << " | email: " << klient.email << " | number: "
                   << klient.number << std::endl;
    }
};

class Pracownik : Osoba
{
protected:
    std::string date = " ";
    std::string title = " ";
    int salary = 0;

public:
    Pracownik()
    {
    }
    Pracownik(int i, std::string n, std::string s, std::string d, std::string t, int sal) : Osoba(i, n, s)
    {
        date = d;
        title = t;
        salary = sal;
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Pracownik()
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    std::string getSurname() const
    {
        return surname;
    }
    friend std::ostream &operator<<(std::ostream &str, const Pracownik &pracownik)
    {
        return str << "id: " << pracownik.id << " | name: " << pracownik.name << " | surname: "
                   << pracownik.surname << " | date of employment: " << pracownik.date << " | job title: "
                   << pracownik.title << " | salary: " << pracownik.salary << std::endl;
    }
};

class BazaDanych
{
protected:
    std::string file;

public:
    BazaDanych()
    {
    }
    BazaDanych(std::string f) : file(f)
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    virtual ~BazaDanych()
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    virtual void GetData() = 0;
    virtual void Print() = 0;
    virtual void Find(const std::string &searchSurname) = 0;
};

class BazaKlientow : public BazaDanych, public Klient
{
private:
    std::vector<Klient> klient_list;

public:
    BazaKlientow(std::string f) : BazaDanych(f)
    {
    }
    BazaKlientow(int i, std::string n, std::string s, std::string e, std::string num)
        : Klient(i, n, s, e, num)
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~BazaKlientow()
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    void GetData() override
    {
        std::string line;

        std::ifstream file("klienci.dat");
        if (!file.is_open())
        {
            std::cerr << "file open error!" << std::endl;
        }
        std::getline(file, line);
        while (std::getline(file, line))
        {
            std::string token;
            std::istringstream ss(line);
            int count = 0;
            int id;
            std::string name, surname, email, number;
            // Klient newKlient;
            while (ss >> token)
            {
                switch (count)
                {
                case 0:
                    id = std::stoi(token);
                    break;
                case 1:
                    name = token;
                    break;
                case 2:
                    surname = token;
                    break;
                case 3:
                    email = token;
                    break;
                case 4:
                    number = token;
                    break;
                    /*default:
                    std::cerr << "error in switch!" << std::endl;
                    break;*/
                }
                count++;
            }
            if (count == 5)
            {
                // std::cout << "Poprawnie dodane dane" << std::endl;
                klient_list.emplace_back(id, name, surname, email, number);
            }
            else
            {
                std::cout << "error in line" << line << std::endl;
            }
        }

        file.close();
    }

    void Print() override
    {
        for (const auto &klient : klient_list)
        {
            std::cout << klient << std::endl;
        }
    }
    void Find(const std::string &searchSurname) override
    {
        auto it = std::find_if(klient_list.begin(), klient_list.end(),
                               [&searchSurname](const Klient &klient)
                               { return klient.getSurname() == searchSurname; });

        if (it != klient_list.end())
        {
            std::cout << "klient found: " << *it << std::endl;
        }
        else
        {
            std::cout << "not found" << std::endl;
        }
    }
};

class BazaPracownikow : public BazaDanych, public Pracownik
{
private:
    std::vector<Pracownik> pracownik_list;

public:
    BazaPracownikow(std::string f) : BazaDanych(f)
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    BazaPracownikow(int i, std::string n, std::string s, std::string d, std::string t, int sal)
        : Pracownik(i, n, s, d, t, sal)
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~BazaPracownikow()
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    void GetData() override
    {
        std::string line;
        std::ifstream file("pracownicy.dat");
        if (!file.is_open())
        {
            std::cerr << "error reading from the file" << std::endl;
        }
        std::getline(file, line); // pomijanie headera
        while (std::getline(file, line))
        {
            std::string token;
            std::istringstream ss(line);
            int id, salary;
            std::string name, surname, date, title;
            int count = 0;
            while (ss >> token)
            {
                switch (count)
                {
                case 0:
                    id = std::stoi(token);
                    break;
                case 1:
                    name = token;
                    break;
                case 2:
                    surname = token;
                    break;
                case 3:
                    date = token;
                    break;
                case 4:
                    title = token;
                    break;
                case 5:
                    salary = std::stoi(token);
                    break;
                }
                count++;
            }
            if (count == 6)
            {
                // std::cout << "Poprawnie dodane dane" << std::endl;
                pracownik_list.emplace_back(id, name, surname, date, title, salary);
            }
            else
            {
                std::cerr << "error in line " << line << std::endl;
            }
        }
        file.close();
    }

    void Print() override
    {
        for (const auto &pracownik : pracownik_list)
        {
            std::cout << pracownik << std::endl;
        }
    }
    void Find(const std::string &searchSurname) override
    {
        auto it = std::find_if(pracownik_list.begin(), pracownik_list.end(),
                               [&searchSurname](const Pracownik &pracownik)
                               { return pracownik.getSurname() == searchSurname; });

        if (it != pracownik_list.end())
        {
            std::cout << "klient found: " << *it << std::endl;
        }
        else
        {
            std::cout << "not found" << std::endl;
        }
    }
};

int main()
{
    std::string surname;
    BazaKlientow client_base("klienci.dat");
    client_base.GetData();
    std::cout << "--------------------------KLIENCI------------------------------\n\n";
    client_base.Print();
    std::cout << "Wpisz nazwisko osoby ktorej dane chcesz wyszukac: ";
    std::cin >> surname;
    client_base.Find(surname);

    BazaPracownikow worker_base("pracownicy.dat");
    worker_base.GetData();
    std::cout << "-------------------------PRACOWNICY----------------------------\n\n";
    worker_base.Print();
    std::cout << "Wpisz nazwisko osoby ktorej dane chcesz wyszukac: ";
    std::cin >> surname;
    worker_base.Find(surname);
}