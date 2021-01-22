#include "../include/List.hpp"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    List<int> list;

    cout << "is empty: " << list.empty() << endl;

    list.push_back(3);
    list.push_front(1);

    cout << "is empty: " << list.empty() << endl;

    cout << "front: " << list.front() << endl;
    cout << "back: " << list.back() << endl;

    list.pop_back();
    list.pop_front();

    cout << "is empty: " << list.empty() << endl;

    cout << "front: " << list.front() << endl;
    cout << "back: " << list.back() << endl;

    /* list.push_front(1); */
    /* cout << list.front() << endl; */

    cout << "made it to the end" << endl;
}

void foo()
{
    /* List<int>::iterator it; */
}
