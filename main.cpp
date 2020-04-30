#include <iostream>
#include <fstream>


using namespace std;

struct nod
{
    int cheie;
    int culoare;
    nod *parinte;
    nod *c_stanga;
    nod *c_dreapta;
};



class RBT

{
    nod *radacina;
    nod *x;
    public:
        RBT()
        {
            radacina = NULL;
        }
    
    
    void inserare(const int & data);
    
    void fix_incalcare(nod *);
    
    void rotire_stanga(nod *);
    
    void rotire_dreapta(nod *);
    
    void afisare();
    
    void afis(nod *);
    
    void cautare(int k);
    
    void cautare_del(int k, int &ok2);

    void succesor(int x);

    void succ(int x, long long int &k , nod * pt);
    
    void predecesor(int x);
    
    void pred(int x, long long int &k , nod * pt);
    
    void afisare_interval(int x, int y);
    
    void stergere(int x);
    
    nod *suc_del(nod *);
    
    void fixare_stergere(nod *);
    
    void stergere_noduri(int x);
    
};   
    

    
void RBT :: inserare(const int & data)
{
    cout << "Nodul cu cheia " << data << " a fost inserat\n";
    nod *p,*aux;
    nod *nod_inserat = new nod;
    nod_inserat -> cheie = data;
    nod_inserat -> c_stanga = NULL;
    nod_inserat -> c_dreapta = NULL;
    nod_inserat -> culoare = 1;
    aux = NULL;
    p=radacina;
    
    if(radacina == NULL)
    {
        radacina = nod_inserat;
        nod_inserat -> parinte = NULL;
    }
    else
    {
        while(p != NULL)
        {
            aux=p;
            if(p -> cheie < nod_inserat -> cheie)
            {
                p = p -> c_dreapta;
            }
            else
            {
                p = p -> c_stanga;
            }
        }
        nod_inserat -> parinte = aux;
        if(aux -> cheie < nod_inserat -> cheie)
        {
            aux -> c_dreapta = nod_inserat;
        }
        else
        {
            aux -> c_stanga = nod_inserat;
        }
    }
    fix_incalcare(nod_inserat);
}
    
void RBT :: fix_incalcare(nod * pt)
{   
    nod * aux;
    if(radacina == pt)
    {
        pt -> culoare = 0;
        return;
    }
    while(pt -> parinte != NULL && pt->parinte->culoare == 1)
    {
       nod *y = pt->parinte -> parinte;
       if(y -> c_stanga == pt -> parinte)
       {
            if(y -> c_dreapta != NULL)
            {
                aux = y -> c_dreapta;
                if(aux -> culoare == 1)
                {
                    pt -> parinte -> culoare = 0;
                    aux -> culoare = 1;
                    y -> culoare = 1;
                    pt = y;
                }
            }
            else
            {
                if(pt -> parinte -> c_dreapta == pt)
                {
                    pt = pt -> parinte;
                    rotire_dreapta(pt);
                }
                pt -> parinte -> culoare = 0;
                y -> culoare = 1;
                rotire_dreapta(y);
            }
       }
       else
       {
            if(y -> c_stanga != NULL)
            {
                aux = y -> c_stanga;
                if(aux -> culoare == 1)
                {
                    pt -> parinte -> culoare = 0;
                    aux -> culoare = 0;
                    y -> culoare = 1;
                    pt = y;
                }
            }
            else
            {
                if(pt -> parinte -> c_stanga == pt)
                {
                   pt = pt -> parinte;
                   rotire_dreapta(pt);
                }
                pt -> parinte -> culoare = 0;
                y -> culoare = 1;
                rotire_stanga(y);
            }
        }
       radacina -> culoare = 0;
    }
} 

void RBT :: rotire_stanga(nod * pt) 
{   
    
    cout << "rotire_stanga\n";
    if(pt -> c_dreapta == NULL)
    {
        return;
    }
    else
    {
        nod * pt_dreapta = pt -> c_dreapta; 
        if (pt_dreapta -> c_stanga != NULL) 
        {   
            pt -> c_dreapta = pt_dreapta -> c_stanga;
            pt_dreapta -> c_stanga -> parinte = pt;
        }  
      
        else
        {
            pt -> c_dreapta = NULL;
        }
        if(pt -> parinte != NULL)
        {
            pt_dreapta -> parinte = pt -> parinte;
        }
        if(pt -> parinte == NULL)
        {
            radacina = pt_dreapta;
        }
        else
        {
            if(pt == pt -> parinte -> c_stanga)
            {
                pt -> parinte -> c_stanga = pt_dreapta;
            }
            else
            {
                pt -> parinte -> c_dreapta = pt_dreapta;
            }
        }
        pt_dreapta -> c_stanga = pt;
        pt -> parinte = pt_dreapta;
    }
}  
    
    
    
void RBT :: rotire_dreapta(nod * pt) 
{   
    cout << "rotire_dreapta\n";
    if(pt -> c_stanga == NULL)
    {
        return;
    }
    else
    {
        nod * pt_stanga = pt -> c_stanga; 
      
      
        if (pt_stanga -> c_dreapta != NULL) 
        {   
            pt -> c_stanga = pt_stanga -> c_dreapta;
            pt_stanga -> c_dreapta -> parinte = pt;
        }  
      
        else
        {
            pt -> c_stanga = NULL;
        }
        if(pt -> parinte != NULL)
        {
            pt_stanga -> parinte = pt -> parinte;
        }
        if(pt -> parinte == NULL)
        {
            radacina = pt_stanga;
        }
        else
        {
            if(pt == pt -> parinte -> c_stanga)
            {
                pt -> parinte -> c_stanga = pt_stanga;
            }
            else
            {
                pt -> parinte -> c_dreapta = pt_stanga;
            }
        }
        pt_stanga -> c_dreapta = pt;
        pt -> parinte = pt_stanga;
    }
}

void RBT :: afisare()
{
    afis(radacina);
}

void RBT :: afis(nod *x)
{   
    
    if(x != NULL)
    {
        afis(x -> c_stanga);
        cout << "\nNodul " << x -> cheie;
        if(x -> culoare == 0)
        {
            cout << " , culoare: negru";
        }
        else
        {
            cout << " , culoare: rosu";
        }
        if( x == radacina)
        {
            cout << " ESTE RADACINA";
            
        }
        else
        {
            cout << " are parinte pe " << x -> parinte -> cheie;
        }
        if(x -> c_dreapta == NULL && x -> c_stanga == NULL)
        {
            cout << " si nu are copii \n";
        }
        else
        if(x -> c_dreapta == NULL)
        {
            cout << " si are copil stanga pe " << x -> c_stanga -> cheie;
        }
        else
        if(x -> c_stanga == NULL)
        {
            cout << " si are copil dreapta pe " << x -> c_dreapta -> cheie;
        }
        else
        {
            cout<< " si are copii pe "<< x -> c_stanga -> cheie << " si pe " << x -> c_dreapta -> cheie << "\n"; 
        }
        afis(x -> c_dreapta);
    }
}


void RBT :: cautare(int k)
{
    nod *pt = radacina;
    int ok = 0;
    while(pt != NULL && ok == 0)
    {
        if(pt -> cheie == k)
        {
            ok = 1;
        }
        if(ok == 0)
        {
            if(pt -> cheie < k)
            {
                pt = pt -> c_dreapta;
            }
            else
            {
                pt = pt -> c_stanga;
            }
        }
    }
    
    if(ok == 0)
    {
        cout << "Nodul "<< k << " nu a fost gasit\n";
    }
    else
    {
        cout << "Nodul "<< k << " a fost gasit\n";
    }
}


void RBT :: cautare_del(int k, int  &ok2)
{
    nod *pt = radacina;
    int ok = 0;
    while(pt != NULL && ok == 0)
    {
        if(pt -> cheie == k)
        {
            ok = 1;
        }
        if(ok == 0)
        {
            if(pt -> cheie < k)
            {
                pt = pt -> c_dreapta;
            }
            else
            {
                pt = pt -> c_stanga;
            }
        }
    }
    
    if(ok == 0)
    {
        ok2 = -1;
    }
    else
    {
        ok2 = 1;
    }
}


void RBT :: succ(int x, long long int & k, nod * pt)
{
    if (pt == NULL)
    {
        return;
    }
    else
    {
        succ(x, k, pt -> c_stanga);
        if (pt -> cheie > x && pt -> cheie < k)
        {
            k = pt -> cheie;
        }
        succ(x, k, pt -> c_dreapta);
    }
}



void RBT :: succesor(int x)
{
    int ok;
    cautare_del(x, ok);
    if(ok == -1)
    {
        cout << "Nodul nu exista";
    }
    else
    {
        long long int k = 9223372036854775807;
        nod *pt = radacina;
        succ(x, k, pt);
        if (k == 9223372036854775807)
        {
            cout << "Nu exista succesor pentru nodul " << x << "\n";
        }
        else
        {
            cout << "Succesorul nodului " << x << " este " << k << "\n";
        }
    }
    
}
void RBT :: pred(int x, long long int & k, nod * pt)
{
    if (pt == NULL)
    {
        return;
    }
    else
    {
        pred(x, k, pt -> c_stanga);
        if (pt -> cheie < x && pt -> cheie > k)
        {
            k = pt -> cheie;
        }
        pred(x, k, pt -> c_dreapta);
    }
}


void RBT :: predecesor(int x)
{
    int ok;
    cautare_del(x, ok);
    if(ok == -1)
    {
        cout << "Nodul nu exista";
    }
    else
    {
        long long int k = -9223372036854775807;
        nod *pt = radacina;
        pred(x, k, pt);
        if (k == -9223372036854775807)
        {
            cout << "Nu exista predecesor pentru nodul " << x << "\n";
        }
        else
        {
            cout << "Predecesorul nodului " << x << " este " << k << "\n";
        }
    }
 
} 
    
void RBT :: afisare_interval(int x, int y)
{   
    nod *pt = radacina;
    
    if(pt == NULL)
    {
        return;
    }
    
    else
    {
        cout << "Nodurile in intervalul " << "(" << x << ", " << y << ")" << ": ";
        while(x < y)
        {   
            long long int k = 9223372036854775807;
            cout << x << ", ";
            succ(x, k, pt);
            x=k;
        }
        
    }
}

void RBT :: stergere(int x)
{
     nod *pt;
     pt = radacina;
     nod *nod_sters = NULL;
     nod *aux = NULL;
     int ok;
     cautare_del(x, ok);
    
    
     if(ok==0)
     {
            cout<<"Nodul nu exista ";
            return;
     }
     else
     {
         if(pt->c_stanga == NULL || pt -> c_dreapta == NULL)
              nod_sters = pt;
         else{
            nod_sters = suc_del(pt);
         }
         if(nod_sters -> c_stanga != NULL)
              aux = nod_sters -> c_stanga;
         else
         {
              if(nod_sters -> c_dreapta != NULL)
                   aux = nod_sters -> c_dreapta;
              else
                   aux = NULL;
         }
         if(aux != NULL)
              aux -> parinte = nod_sters -> parinte;
         if(nod_sters -> parinte == NULL)
              radacina = aux;
         else
         {
             if(nod_sters == nod_sters -> parinte -> c_stanga)
                nod_sters -> parinte -> c_stanga = aux;
             else
                nod_sters -> parinte -> c_dreapta = aux;
         }
         if(nod_sters != pt)
         {
             pt -> culoare = nod_sters -> culoare;
             pt -> cheie = nod_sters -> cheie;
         }
         if(nod_sters -> culoare == 0)
         {
         }
     }
}


void RBT :: fixare_stergere(nod *pt)
{
    nod *s;
    while(pt != radacina && pt -> culoare == 0)
    {
          if(pt -> parinte -> c_stanga == pt)
          {
                  s = pt -> parinte -> c_dreapta;
                  if(s -> culoare == 1)
                  {
                         s -> culoare = 0;
                         pt -> parinte -> culoare = 1;
                         rotire_stanga(pt -> parinte);
                         s = pt -> parinte -> c_dreapta;
                  }
                  if( s -> c_dreapta -> culoare == 0 && s -> c_stanga -> culoare == 0)
                  {
                         s -> culoare = 1;
                         pt = pt -> parinte;
                  }
                  else
                  {
                      if(s -> c_dreapta -> culoare == 0)
                      {
                             s -> c_stanga -> culoare == 0;
                             s -> culoare = 1;
                             rotire_dreapta(s);
                             s = pt -> parinte -> c_dreapta;
                      }
                      s -> culoare = pt -> parinte -> culoare;
                      pt -> parinte -> culoare = 0;
                      s -> c_dreapta -> culoare = 0;
                      rotire_stanga(pt -> parinte);
                      pt = radacina;
                  }
          }
          else
          {
                  s = pt -> parinte -> c_stanga;
                  if(s -> culoare == 1)
                  {
                        s -> culoare = 0;
                        pt -> parinte -> culoare = 1;
                        rotire_dreapta(pt -> parinte);
                        s = pt -> parinte -> c_stanga;
                  }
                  if(s -> c_stanga -> culoare == 0 && s -> c_dreapta -> culoare == 0)
                  {
                        s -> culoare = 1;
                        pt = pt -> parinte;
                  }
                  else
                  {
                        if(s -> c_stanga -> culoare == 0)
                        {
                              s -> c_dreapta -> culoare = 0;
                              s -> culoare = 1;
                              rotire_stanga(s);
                              s = pt -> parinte -> c_stanga;
                        }
                        s -> culoare = pt -> parinte -> culoare;
                        pt -> parinte -> culoare = 0;
                        s -> c_stanga -> culoare = 0;
                        rotire_dreapta(pt -> parinte);
                        pt = radacina;
                  }
          }
       pt -> culoare = 0;
       radacina -> culoare = 0;
    }
}

nod * RBT :: suc_del(nod *pt)
{
    nod *x = NULL;
    if(pt -> c_stanga != NULL)
    {
        x = pt -> c_stanga;
        while(x -> c_dreapta != NULL)
        {
            x = x -> c_dreapta;
        }
    }
    else
    {
        x = pt -> c_dreapta;
        while(x -> c_stanga != NULL)
        {
            x = x -> c_stanga;
        } 
    }
    return x;
}

void RBT :: stergere_noduri(int x) 
{
    int ok, nr = 0;
    cautare_del(x, ok);
    while (ok == 1)
    {
        ok=-1;
        nr++;
        stergere(x);
        cautare_del(x,ok);
    }
    cout << "Nodul " << x << " cu " << nr << " aparitii, a fost sters";
}


int main()
{
    RBT arbore;
    arbore.inserare(1);
    arbore.inserare(2);
    arbore.inserare(3);
    arbore.inserare(4);
    arbore.inserare(5);
    arbore.inserare(6);
    arbore.inserare(7);
    arbore.afisare();
    arbore.cautare(5);
    arbore.cautare(8);
    arbore.succesor(4);
    arbore.predecesor(6);
    arbore.afisare_interval(1,5);
    arbore.stergere(7);
    arbore.afisare();
    return 0;
}


