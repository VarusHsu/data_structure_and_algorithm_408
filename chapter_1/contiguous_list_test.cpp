#include "contiguous_list.h"
#include <iostream>
#include <chrono>

bool assert_equals_int(int, int);
bool assert_equals_bool(bool, bool);
void test_contiguous_list_is_empty();
int now_nanosecond();

int main()
{
    test_contiguous_list_is_empty();
    return 0;
}

void test_contiguous_list_is_empty()
{
    std::cerr << "test_contiguous_list_is_empty start" << std::endl;
    int now = now_nanosecond();

    Contiguous<int> c;
    assert_equals_bool(c.is_empty(), true);
    c.push_back(1);
    assert_equals_bool(c.is_empty(), false);
    c.pop_back();
    assert_equals_bool(c.is_empty(), true);
    c.push_back(1);
    c.push_back(1);
    c.push_back(1);
    assert_equals_bool(c.is_empty(), false);
    c.clear();
    assert_equals_bool(c.is_empty(), true);

    int now2 = now_nanosecond();
    std::cerr << "test_contiguous_list_is_empty end cost: " << now2 - now << "ns" << std::endl;
}

bool assert_equals_int(int val1, int val2)
{
    if (val1 == val2)
    {
        return true;
    }
    std::cerr << "assert failed: " << val1 << " is not equals to " << val2 << std::endl;
    exit(1);
}

bool assert_equals_bool(bool val1, bool val2)
{
    if (val1 == val2)
    {
        return true;
    }
    std::cerr << "assert failed: " << val1 << " is not equals to " << val2 << std::endl;
    exit(1);
}

int now_nanosecond()
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    int nanoseconds = ns.count();
    return nanoseconds;
}