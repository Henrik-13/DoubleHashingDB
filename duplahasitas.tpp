//Bálint Henrik
//511

#include "duplahasitas.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// felepitem Eratoszthenesz szitajat n-ig
int GetPrim(int n)
{
    vector<bool> Prim(n, true);
    Prim[0] = false;
    Prim[1] = false;
    int gyok = sqrt(n);
    for (int i = 2; i <= gyok; i++)
    {
        if(Prim[i])
        {
            int j = i * i;
            while (j <= n)
            {
                Prim[j] = false;
                j += i;
            }
            
        }
    }
    int prim = n - 1;
    while (!Prim[prim]) // kivalasztom az elso primszamot ami kisebb mint a hasitotabla merete
    {
        prim--;
    }
    Prim.clear();
    return prim;
}

template <typename T>
int inline hash1(DuplaHasitas<T> *h, int kulcs)        //1. hasitofuggveny
{
    return (kulcs % h->meret);
}

template <typename T>
int inline hash2(DuplaHasitas<T> *h, int kulcs)        //2. hasitofuggveny
{
    return (h->prim - (kulcs % h->prim));
}

template <typename T>
DuplaHasitas<T> *Letrehoz(int n)               //n elemu hasitotabla letrehozasa
{
    if(n < MIN_MERET)
    {
        cout << "A tabla minimum merete 5" << endl;
        return nullptr;
    }
    else if(n > MAX_MERET)
    {
        cout << "A tabla maximum merete 1000000" << endl;
        return nullptr;
    }
    DuplaHasitas<T> *h = new DuplaHasitas<T>;
    h->meret = n;
    h->db = 0;
    h->prim = GetPrim(n);
    h->kulcsok = new int[n];            //ebben a tombben taroljuk a kulcsokat
    h->hasitotabla = new T[n];
    for (int i = 0; i < n; i++)
    {
        h->kulcsok[i] = -1;             //az ures mezokon a kulcsok erteke -1
    }

    return h;
}

template <typename T>
void Felszabadit(DuplaHasitas<T> *h)           //hasitotabla felszabaditasa
{
    delete[] h->hasitotabla;
    delete[] h->kulcsok;
    delete h;
}

template <typename T>
bool inline Tele(DuplaHasitas<T>* h)           //tele van-e a hasitotabla
{
    return (h->meret == h->db);
}

template <typename T>
void Beszur(DuplaHasitas<T> *h, int kulcs, T elem)      //elem beszurasa
{
    if(Tele(h))
    {
        cout << "Tele van a tabla" << endl;
        return;
    }
    int index = hash1(h, kulcs);
    int offset = hash2(h, kulcs);
    while (h->kulcsok[index] > -1)            //addig megyek amig kapok egy ures helyet
    {
        index = (index + offset) % h->meret;
    }
    h->kulcsok[index] = kulcs;              //elmentem a kulcsot
    h->hasitotabla[index] = elem;           //elmentem az elemet   
    h->db++;
}

template <typename T>
void Torol(DuplaHasitas<T> *h, int kulcs)              //elem torlese kulcs alapjan
{
    if (Keres(h, kulcs) == -1)
        return;
    int index = hash1(h, kulcs);
    int offset = hash2(h, kulcs);
    while(h->kulcsok[index] != -1)
    {
        if(h->kulcsok[index] == kulcs)
        {
            h->kulcsok[index] = -2;           //a torolt elemek kulcsa -2 lesz
            h->db--;
            return;
        }
        else
            index = (index + offset) % h->meret;
    }
}

template <typename T>
int Keres(DuplaHasitas<T> *h, int kulcs)              //elem keresese kulcs alapjan
{                                                     //visszateriti az indexet ha megvan a tablaban, -1 - et ha nincs meg
    int index = hash1(h, kulcs);
    int offset = hash2(h, kulcs);
    int elso_poz = index;
    bool elso_iteracio = true;
    while (1)
    {
        if(h->kulcsok[index] == -1)
        {
            return -1;
        }
        else if(h->kulcsok[index] == kulcs)
        {
            return index;
        }
        else if(index == elso_poz and !elso_iteracio)       //ha vegigmentunk a tablan akkor kilepunk
        {
            return -1;
        }
        else
            index = (index + offset) % h->meret;
        elso_iteracio = false;
    }
    return -1;
}

template <typename T>
void Kiir(DuplaHasitas<T> *h)                      //kiirja a teljes hasitotabla tartalmat(kulcsokat)
{
    for (int i = 0; i < h->meret; i++)
        if(h->kulcsok[i] < 0)
            cout << "NULL ";
        else
            cout << h->kulcsok[i] << " ";
    cout << endl;
}
