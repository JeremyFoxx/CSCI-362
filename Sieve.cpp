/*
  Filename   : Sieve.cpp
  Author(s)  : Jeremy Foxx
  Course     : CSCI 362-01
  Assignment : Sieve 
  Description: A program that finds the prime numbers of number n
*/

/*************************************************************************************/
//System includes

#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <string>
#include "Timer.hpp"
#include <math.h> 

/*************************************************************************************/

// Return the set of primes between 2 and N.
// Use a set to implement the sieve.
std::set<unsigned>
sieveSet (unsigned N)
{
    std::set <unsigned> prime; 

    for (unsigned int i = 2; i <= N; ++i)
    {
        prime.insert (i); 
    }

    auto begin = prime.begin (); 
    while (begin != prime.end ())
    {
        int curr = *begin; 
        int erase = 2 * curr; 

        while (erase <= N)
        {
            prime.erase (erase); 
            erase += curr;
        }

        ++begin;

    }

    return prime; 

}

// Return the set of primes between 2 and N.
// Use a vector to implement the sieve.
// After filtering out the composites, put the primes in a set
//   to return to the caller. 
std::set<unsigned>
sieveVector (unsigned N) 
{
    std::set <unsigned> prime; 
    std::vector <bool> primeBool; 

    for (unsigned int i = 0; i <= N; ++i)
    {
        primeBool.push_back (true);
    }

    for (unsigned int i = 2; i * i < N; ++i)
    {
        if (primeBool[i])
        {
            for (unsigned int j = i; i * j <= N; ++j)
            {
                primeBool[i * j] = false; 
            }
        }
    }

    for (unsigned int i = 2; i <= N; ++i)
    {
        if (primeBool[i])
        {
            prime.insert (i);
        }
    }

    return prime; 

}

int 
main (int argc, char* argv[])
{
    std::string version (argv[1]);
    unsigned int num = std::stoul (std::string{argv[2]});
    auto sieveVersion = (version == "set" ? &sieveSet : &sieveVector);
    Timer<> t;
    unsigned int answer = sieveVersion (num).size (); 
    t.stop ();
    std::cout << "Pi[" + std::string (argv[2]) + "]" + " = " + std::to_string (answer) + " (using a " + argv[1] + ")\n";
    std::cout << "Time: "; 
    printf ("%.2f", t.getElapsedMs ());
    std::cout << " ms\n"; 

    return 0;

}

/*
N       10,000,000    20,000,000   40,000,000
=============================================
set     45609.90 ms    94737.32 ms     201155.72 ms
vector  1766.29 ms     3530.83 ms      7150.47 ms

1.) sieveSet uses insert to store values from two up to N in a set which has a time complexity of O(logn).

2.) sieveVector uses pushback to store values from two up to N in a vector which has a time complexity of O(1).

*/