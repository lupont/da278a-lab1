#ifdef _DEBUG
#ifndef DBG_NEW
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <iostream>
using std::cout;

#include "../include/TestLevel.h"

#include "../include/List.hpp"


//template class List<int>;


void TestBasic();
void TestList();
void TestListIter();

int main() {
    if (true)
    {
#ifdef DBG_NEW
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

        TestBasic();
        /* cout << "Basic Test OK!" << std::endl; */
        
        TestList();
        /* cout << "List Test OK!" << std::endl; */

        TestListIter();
        /* cout << "ListIter Test OK!" << std::endl; */

        new int(7);
        std::cout << "There should be one memory leak!";
    }
    else
    {
        List<char> bar;
        bar.push_back('b');
        cout << bar << std::endl;
        bar.push_back('a');
        cout << bar << std::endl;
        bar.push_back('r');
        cout << bar << std::endl;
        bar.pop_back();
        cout << bar << std::endl;
        bar.pop_back();
        cout << bar << std::endl;
        bar.pop_back();
        cout << bar << std::endl;
    }
}

//template class List<int>;
