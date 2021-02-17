#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Proizvod{
    int id;
    int kol;
    double cena;
public:
    Proizvod(int i=0, int k=0, double c=0.):  id(i), kol(k), cena(c) { }
    virtual string stampa()const {
        return string("[") + to_string(id) + string("," )  + to_string(kol) + string(" ,") + to_string(cena) + string("]");
    }
     bool operator == (const Proizvod &p){
        return (id == p.id);
    }
    bool operator != (const Proizvod &p){
        return !(id == p.id);
    }
    virtual double zarada(int kol) const =0;

    friend ostream& operator << (ostream& out, const Proizvod &p){
        out << p.stampa();
        return out;
    }
    double ck()const {
        return cena;

    }
    void setKol(int k){
        kol+=k;
    }
    int getKol()const{
        return kol;
    }
    int getId()const{
        return id;
    }
};

class AlkoholnoPice : public Proizvod{
    double alc;
public:
    AlkoholnoPice(double a=0., int i=0, int k=0, double c=0.): alc(a), Proizvod(i, k , c) { }
    string stampa()const  {
        return string("(%") + to_string(alc) + ")" + Proizvod::stampa() ;
    }
    double zarada(int kol)const {
        return Proizvod::ck() * kol * alc;
    }

};
class BezalkoholnoPice : public Proizvod{
    double litra;
    char tip;
public:
    BezalkoholnoPice(double l, char t, int i=0, int k=0, double c=0.): litra(l), tip(t), Proizvod(i, k , c) { }
    string stampa()const{
        return string("(") + tip + "," + to_string(litra) + "l )" + Proizvod::stampa() ;
    }
    double zarada(int kol)const{
        if(tip=='S')
            return Proizvod::ck()*kol + litra/2. ;
        if(tip=='V')
            return Proizvod::ck()*kol + litra/4. ;
        return Proizvod::ck()*kol * litra;
    }
};
class DiskontPica{
    vector<Proizvod*> magacin;
    double zarada=0.;
public:
    DiskontPica()=default; // defaultni konstruktor
    void dodaj(Proizvod* p) {
            for(auto a: magacin)    //proverava da li postoji isti elemenat, ako postoji povecava kolicinu
                if(*a == *p){
                    a->setKol(p->getKol());

                    return;
                }
            magacin.push_back(p);   // u suprotnom dodaje na kraj niza
    }
    void prodaj(int id, int kolicina){
            for(auto a: magacin)
                    if(a->getId() == id){
                        if(a->getKol() >= kolicina){
                            a->setKol(-kolicina);
                            zarada+=a->zarada(kolicina);
                        }
                    }
    }

    friend ostream& operator<<(ostream& out, const DiskontPica &d){
    out << "Zarada:" << d.zarada << endl;
        for(auto p: d.magacin)
            out << (*p) << endl;
        return out;
    }
};

int main()
{
    DiskontPica d;
    cout << d << endl;
    d.dodaj(new AlkoholnoPice(0.3, 1, 3, 20));
    d.dodaj(new AlkoholnoPice(0.5, 1, 4, 20));
    d.dodaj(new BezalkoholnoPice(1, 'S',2, 10, 30));
    d.dodaj(new BezalkoholnoPice(2, 'V',4, 10, 80));
    cout << d << endl;

    d.prodaj(1,4);
    d.prodaj('S',11);
    d.prodaj('V',11);
    cout << d << endl;
    /*AlkoholnoPice p(0.3, 1, 3, 500);
    AlkoholnoPice s(0.4, 1, 3, 600);
    cout << p.stampa() << endl;
    cout <<  (p == s) << endl;
    cout << p;*/
    return 0;
}
