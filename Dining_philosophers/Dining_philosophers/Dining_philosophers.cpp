#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>

int NUM_PHILOSOPHERS = 5;
std::mutex printMutex; // Global mutex to synchronize console output

class Fork {
private:
    std::mutex mtx;
public:
    void lock() { mtx.lock(); }
    void unlock() { mtx.unlock(); }
};

class Philosopher {
private:
    int id;
    Fork& firstFork;
    Fork& secondFork;

public:
    Philosopher(int id, Fork& left, Fork& right) : id(id),
        firstFork(id == NUM_PHILOSOPHERS - 1 ? right : left),
        secondFork(id == NUM_PHILOSOPHERS - 1 ? left : right) {
    }

    void dine() {
        while (true) {
            think();
            eat();
        }
    }

    void think() {
        printMessage("is thinking.");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 500));
    }

    void eat() {
        printMessage("is hungry.");

        firstFork.lock();
        secondFork.lock();

        printMessage("is eating.");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 500));

        firstFork.unlock();
        secondFork.unlock();
    }

    void printMessage(const std::string& message) {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << "\033[" << (id + 1) << ";1H"
            << "Philosopher " << id << " " << message << "    " << std::flush;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_philosophers>\n";
        return 1;
    }

    int NUM_PHILOSOPHERS = std::atoi(argv[1]);

    if (NUM_PHILOSOPHERS < 2) {
        std::cerr << "The number of philosophers must be at least 2.\n";
        return 1;
    }

    std::vector<Fork> forks(NUM_PHILOSOPHERS);
    std::vector<std::thread> philosophers;

    std::cout << "\033[2J";

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers.emplace_back(&Philosopher::dine, Philosopher(i, forks[i], forks[(i + 1) % NUM_PHILOSOPHERS]));
    }

    for (auto& phil : philosophers) {
        phil.join();
    }

    return 0;
}