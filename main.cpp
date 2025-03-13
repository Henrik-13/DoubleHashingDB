//Bálint Henrik
//511

#include "duplahasitas.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

#define TABLA_MERET 10007

using namespace std;


struct Elem
{
    int kulcs;
    long long ertek;
    int kor;
    char nev[30];
    char klub[30];
    int golok, golpasszok;
};

template <typename T>
void Beolvas(DuplaHasitas<T> *h, char *inputfile)       //beolvasas allomanybol
{
    char input[100] = "input/";
    strcat(input, inputfile);
    ifstream fin(input);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        Elem tmp;
        fin >> tmp.kulcs >> tmp.nev >> tmp.kor >> tmp.klub >> tmp.ertek;
        Beszur(h, tmp.kulcs, tmp);
    }
}

template <typename T>
void Szezon(DuplaHasitas<T> *h)         //szezon leszimulalasa
{
    int max_gol = 0, max_golpassz = 0, max_gol_i = 0, max_golpassz_i = 0, gc, maxgc = 0, maxgc_i = 0;
    for (int i = 0; i < TABLA_MERET; i++)
    {
        if(h->kulcsok[i] > 0)
        {
            h->hasitotabla[i].kor++;
            h->hasitotabla[i].golok = rand() % 100;         //random generalok minden jatekosnak golokat es golpasszokat
            h->hasitotabla[i].golpasszok = rand() % 50;
            gc = h->hasitotabla[i].golok + h->hasitotabla[i].golpasszok;
            if(gc > maxgc)                      //megnezem ki rugta a legtobb golt es ki adta a legtobb golpasszt es o kapja az aranylabdat
            {
                maxgc = gc;
                maxgc_i = i;
            }
            if (h->hasitotabla[i].golok > max_gol)
            {
                max_gol = h->hasitotabla[i].golok;
                max_gol_i = i;
            }
            if (h->hasitotabla[i].golpasszok > max_golpassz)
            {
                max_golpassz = h->hasitotabla[i].golpasszok;
                max_golpassz_i = i;
            }
            if (h->hasitotabla[i].kor > 40)      //aki 40 evnel idosebb az visszavonul
            {
                Torol(h, h->kulcsok[i]);
            }
            if(h->hasitotabla[i].kor <= 30)     //30 evnel fiatalabb jatekosoknak novekszik az erteke
            {
                h->hasitotabla[i].ertek += 5000000;
            }
            else                                //kulonben pedig csokken
            {
                if(h->hasitotabla[i].ertek > 5000000)
                    h->hasitotabla[i].ertek -= 5000000;
            }
        }
    }
    cout << "A legtobb golt rugo focista: ";
    cout << h->hasitotabla[max_gol_i].nev << " " << h->hasitotabla[max_gol_i].golok << " gol" << endl;
    cout << endl;
    cout << "A legtobb golpasszt kioszto focista: ";
    cout << h->hasitotabla[max_golpassz_i].nev << " " << h->hasitotabla[max_golpassz_i].golpasszok << " golpassz" << endl;
    cout << endl;
    cout << "Az idei Aranylabda gyoztese: ";
    cout << h->hasitotabla[maxgc_i].nev << " " << h->hasitotabla[maxgc_i].golok << " gol " << h->hasitotabla[maxgc_i].golpasszok << " golpassz" << endl;
    cout << endl;
    h->hasitotabla[maxgc_i].ertek += 10000000;
}

template <typename T>
void Hozzaadas(DuplaHasitas<T> *h)
{
    Elem tmp;
    cout << "Azonosito: ";
    cin >> tmp.kulcs;
    cout << "Jatekos neve: ";
    cin >> tmp.nev;
    cout << "Jatekos eletkora: ";
    cin >> tmp.kor;
    cout << "Jatekos klubcsapata: ";
    cin >> tmp.klub;
    cout << "Jatekos piaci erteke: ";
    cin >> tmp.ertek;
    if(!Tele(h))
    {
        Beszur(h, tmp.kulcs, tmp);
        cout << "A beszuras sikeres volt" << endl;
    }
    else
    {
        cout << "Az adatbazis tele van" << endl;
    }
}

template <typename T>
void Torles(DuplaHasitas<T> *h)
{
    int kulcs;
    cout << "Azonosito: ";
    cin >> kulcs;
    if(Keres(h, kulcs) == -1)
    {
        cout << "Ilyen azonositoju jatekos nincs az adatbazisban" << endl;
    }
    else
    {
        Torol(h, kulcs);
        cout << "A torles sikeres volt" << endl;
    }
}

template <typename T>
void KiirJatekosAdatok(DuplaHasitas<T> *h)
{
    int kulcs;
    cout << "Azonosito: ";
    cin >> kulcs;
    int index = Keres(h, kulcs);
    if (index == -1)
    {
        cout << "Ilyen azonositoju jatekos nincs az adatbazisban" << endl;
    }
    else
    {
        cout << h->hasitotabla[index].kulcs << " " << h->hasitotabla[index].nev << " " << h->hasitotabla[index].kor << " " << h->hasitotabla[index].klub << " " << h->hasitotabla[index].ertek << "$" << endl;
    }
}

template <typename T>
void FrissitErtek(DuplaHasitas<T> *h)
{
    int kulcs, ujertek;
    cout << "Azonosito: ";
    cin >> kulcs;
    cout << "Uj ertek: ";
    cin >> ujertek;
    int index = Keres(h, kulcs);
    if (index == -1)
    {
        cout << "Ilyen azonositoju jatekos nincs az adatbazisban" << endl;
        return;
    }
    else
    {
        h->hasitotabla[index].ertek = ujertek;
        cout << "A jatekos erteke frissitve lett" << endl;
    }
}

template <typename T>
void FrissitKlub(DuplaHasitas<T> *h)
{
    int kulcs;
    cout << "Azonosito: ";
    cin >> kulcs;
    char ujklub[30];
    cout << "Uj klub: ";
    cin >> ujklub;
    int index = Keres(h, kulcs);
    if (index == -1)
    {
        cout << "Ilyen azonositoju jatekos nincs az adatbazisban" << endl;
        return;
    }
    else
    {
        strcpy(h->hasitotabla[index].klub, ujklub);
        cout << "A jatekos klubcsapata frissitve lett" << endl;
    }
}

template <typename T>
void KiirAdatbazis(DuplaHasitas<T> *h)
{
    cout << "Jatekosok szama: " << h->db << endl;
    for (int i = 0; i < TABLA_MERET; i++)
    {
        if(h->kulcsok[i] > 0)
            cout << h->hasitotabla[i].kulcs << " " << h->hasitotabla[i].nev << " " << h->hasitotabla[i].kor << " " << h->hasitotabla[i].klub << " " << h->hasitotabla[i].ertek << "$" << endl;
    }
}

template <typename T>
void Szimulal(DuplaHasitas<T> *h)
{
    cout << "Udv! Ez egy focista adatbazis, ahol jatekosok adatai vannak eltarolva es szezonokat lehet szimulalni" << endl;
    cout << "Kezdeshez nyomj egy 1-est, kilepeshez egy 0-ast" << endl;
    int start;
    cin >> start;
    if(start != 1)
    {
        exit(0);
    }

    cout << "Nyomj egy 1-est, ha ures adatbazissal szeretnel kezdeni, 2-est, ha fajlbol szeretnel beolvasni egy adatbazist" << endl;
    int valasz;
    cin >> valasz;

    if(valasz == 1)
    {
        cout << "Letrejott az ures adatbazis" << endl;
    }
    else if(valasz == 2)
    {
        cout << "Melyik allomanybol szeretnel beolvasni?" << endl;
        cout << "Lehetosegek : be1.txt be2.txt be3.txt be4.txt be5.txt" << endl;
        cout << "Allomany neve: ";
        char input[100];
        cin >> input;
        Beolvas(h, input);
    }
    else 
    {
        exit(0);
    }

    int i = 1;
    while (1)
    {
        cout << i << ". szezon" << endl;
        cout << "Opciok:" << endl;
        cout << "(0): Kilepes" << endl;
        cout << "(1): Szezon leszimulalasa" << endl;
        cout << "(2): Uj Jatekos hozzaadaasa az adatbazishoz" << endl;
        cout << "(3): Jatekos torlese az adatbazisbol" << endl;
        cout << "(4): Jatekos adatainak kiirasa azonosito alapjan" << endl;
        cout << "(5): Jatekos piaci ertekenek frissitese" << endl;
        cout << "(6): Jatekos klubjanak frissitese" << endl;
        cout << "(7): Teljes adatbazis kiirasa" << endl;
        int eset;
        cin >> eset;
        switch(eset)
        {
            case 0:
                cout << "Koszonom, hogy jatszottal!" << endl;
                exit(0);
                break;
            case 1:
                Szezon(h);
                i++;
                break;
            case 2:
                Hozzaadas(h);
                break;
            case 3:
                Torles(h);
                break;
            case 4:
                KiirJatekosAdatok(h);
                break;
            case 5:
                FrissitErtek(h);
                break;
            case 6:
                FrissitKlub(h);
                break;
            case 7:
                KiirAdatbazis(h);
                break;
            default:
                break;
        }
    }
}

int main()
{
    srand(time(NULL));
    DuplaHasitas<Elem> *h = Letrehoz<Elem>(TABLA_MERET);
    Szimulal(h);
    Felszabadit(h);
    return 0;
}
