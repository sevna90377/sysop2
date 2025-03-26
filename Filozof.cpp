#include <string>
#include <iostream>

class Filozof {
    private:
        bool zyje;
        std::string imie;
        bool lewy, prawy;

    public:

    Filozof(std::string imie) : imie(imie), lewy(false), prawy(false), zyje(false) {}

    void tchnij_zycie(){
        zyje = true;
        std::cout << "Filozof <<" << imie << ">> wita wszystkich przy stole.";
        
        int czas;
        bool czynnosc;
        while(zyje){
            czas = rand() % 10 + 1;
            if(rand()%2 == 0){
                rozmyslaj(czas);
            }else{
                jedz(czas);
            }
        }
    }

    void zabij(){
        zyje = false;
    }

    void jedz(int czas){
        std::cout << "\033[" << line << ";1H" // Przesunięcie kursora do `line`, kolumna 1
        << "Filozof " << imie << " je" 
        << std::flush; // Wypisz natychmiast
    }

    void rozmyslaj(int czas){
        for (int i = 0)
    }

};