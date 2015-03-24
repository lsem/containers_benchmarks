#include <iostream>
#include <vector>
#include <list>
#include <set>

using std::list;
using std::vector;
using std::string;
using std::set;


namespace helpers
{
    template <class Container, class Value>
    struct stlext
    {
        static typename Container::const_iterator
        lowerBound( const Container &c, Value value) { return std::lower_bound(c.cbegin(), c.cend(), value); }
    };

    template <class Value>
    struct stlext<set<Value>, Value>
    {
        static typename set<Value>::const_iterator
        lowerBound (const set<Value> &c, Value value) { return c.lower_bound(value); }
    };

    unsigned executeProcedureMeasuredMicroseconds(std::function<void()> func)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        func();
        auto finishTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count();
    }

    template<class Container>
    void printContainer(const Container &c, const string &title)
    {
        std::cout << title << "\t" << std::endl;
        for (const auto & v : c)
            std::cout << v << ",";
        std::cout << std::endl;
    }
}


template<class Container>
void do_test_insert_random_position(Container &container, unsigned actions)
{
    while (actions--)
    {
        const auto nextElement = rand() % 10000;
        const auto insertPosition = helpers::stlext<Container, typename Container::value_type>::lowerBound(container, nextElement);
        container.insert(insertPosition, nextElement);
    }
}


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "N argument missing. Aborting\n";
        return 1;
    }

    bool verbose = false;
    if (argc > 3)
    {
        if (string(argv[3]) == "-v")
            verbose = true;
    }

    auto N = std::atoi(argv[1]);
    const auto M = std::atoi(argv[2]);

    for (auto round = 0; round < M; ++round)
    {
        vector<int> v;
        list<int> l;
        set<int> s;

        v.reserve(N);

        const auto vectorElapsedMicro = helpers::executeProcedureMeasuredMicroseconds([&]() {
            do_test_insert_random_position(v, N);
        });
        std::cout << round + 1 <<  "," << N << ": vector elapsed microseconds: " << vectorElapsedMicro << std::endl;

        const auto listElapsedMicro = helpers::executeProcedureMeasuredMicroseconds([&]() { 
	        do_test_insert_random_position(l, N);
        });
        
        std::cout << round + 1 << "," << N << ": list elapsed microseconds: " << listElapsedMicro << std::endl;

        const auto setElapsedMicro = helpers::executeProcedureMeasuredMicroseconds([&]() {
            do_test_insert_random_position(s, N);
        });
        std::cout << round + 1 << "," << N << ": set elapsed microseconds: " << setElapsedMicro << std::endl;


        if (verbose)
        {
            helpers::printContainer(v, "vector");
            helpers::printContainer(l, "list");
            helpers::printContainer(s, "set");
        }

        N *= 2;

        std::cout << std::endl;
    }

    return 0;
}
