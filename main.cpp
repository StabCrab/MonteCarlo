#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>
void makeAndCount(int begin, int end, std::pair<double, double>* vertex, int& count, int D)
{
    for (int i = begin; i < end; ++i)
    {
        vertex[i] = std::make_pair(rand() % int(D), rand() % int(D));
        if (pow(D/2 - vertex[i].first, 2) + pow(D/2 - vertex[i].second, 2) < D * D / 4)
        {
            count++;
        }
    }
}
void calculatePi(double M, double D, int T)
{
    auto* vertex = new std::pair<double, double>[int(M)];
    srand(time(nullptr));
    int N = 0;
    std::vector<std::thread> thread;
    int count[T];
    for (int i = 0; i < T; ++i)
    {
        count[i] = 0;
        thread.push_back(std::thread(makeAndCount, M / T * i, M / T * (i + 1), vertex, std::ref(count[i]), D));
    }
    for (int i = 0; i < T; ++i)
    {
        thread[i].join();
        N += count[i];
    }
    double pi;
    pi = 4 * N / M;
    std::cout << pi;
}
int main()
{
    {
        calculatePi(100.0, 10.0, 4);
        std::cout << " " << "M = 100, D = 10 " << std::endl;
    }

    {
        calculatePi(1000.0, 100.0, 4);
        std::cout << " " << "M = 1000, D = 100 " << std::endl;
    }

    {
        calculatePi(10000.0, 1000.0, 4);
        std::cout << " " << "M = 10000, D = 1000 "  << std::endl;
    }

    {
        calculatePi(100000.0, 10000.0, 4);
        std::cout << " " << "M = 100000, D = 10000 " << std::endl;
    }

    {
        auto start = std::chrono::steady_clock::now();
        calculatePi(100000.0, 10000.0, 2);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << " " << "Two threads: "<< elapsed_seconds.count()<< "s" << std::endl;
    }

    {
        auto start = std::chrono::steady_clock::now();
        calculatePi(100000.0, 10000.0, 4);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << " " << "Four threads: "  << elapsed_seconds.count() << "s" << std::endl;
    }

    {
        auto start = std::chrono::steady_clock::now();
        calculatePi(100000.0, 10000.0, 10);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << " " << "Ten threads: "  << elapsed_seconds.count() << "s" << std::endl;
    }

}
