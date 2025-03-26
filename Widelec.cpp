#include <mutex>
#include <iostream>

class Widelec{
    public:
        int no;
    private:
        std::mutex mtx;

    void jedz(std::string imie_dopelniacz){
        mtx.lock();
        std::cout << "Widelec " << no << " został wzięty przez <<" << imie_dopelniacz << ">>!";
    }

    void odloz(){
        std::cout << "Odłożono widelec numer " << no << ".";
        mtx.unlock();
    }
};