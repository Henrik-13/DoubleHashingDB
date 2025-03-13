//Bálint Henrik
//511

#ifndef DUPLAHASITAS_H_INCLUDED
#define DUPLAHASITAS_H_INCLUDED

#define MIN_MERET 5
#define MAX_MERET 1000000

template <typename T>
struct DuplaHasitas
{
    int *kulcsok;       //itt tarolom a kulcsokat
    int meret;          //a hasitotabla merete
    int db;             //a hasitotablaban levo elemek darabszama
    int prim;           //primszam, mely segitsegevel meghatarozzuk a 2. hasito fuggvenyt
    T *hasitotabla;     //hasitotabla ami T tipusu elemeket tarol
};

int GetPrim(int);       // ezzel a fuggvennyel hatarozzuk meg a primet

template <typename T>
int inline hash1(DuplaHasitas<T> *, int);      //1. hasitofuggveny

template <typename T>
int inline hash2(DuplaHasitas<T> *, int);      //2. hasitofuggveny


template <typename T>
DuplaHasitas<T> *Letrehoz(int);                //n elemu hasitotabla letrehozasa

template <typename T>
void Felszabadit(DuplaHasitas<T> *);           //hasitotabla felszabaditasa


template <typename T>
bool inline Tele(DuplaHasitas<T> *);           //tele van-e a hasitotabla


template <typename T>
void Beszur(DuplaHasitas<T> *, int, T);      //elem beszurasa a hasitotablaba, parameterek: kulcs, ertek

template <typename T>
void Torol(DuplaHasitas<T> *, int);            //elem torlese kulcs alapjan

template <typename T>
int Keres(DuplaHasitas<T> *, int);            //elem keresese kulcs alapjan


template <typename T>
void Kiir(DuplaHasitas<T> *);                  //kiirja a teljes hasitotabla tartalmat

#include "duplahasitas.tpp"

#endif // DUPLAHASITAS_H_INCLUDED
