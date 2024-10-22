#include "contiguous_list.h"
#include <iostream>
#include <chrono>

bool assert_equals_int(int, int);
bool assert_equals_bool(bool, bool);
bool assert_equals_array(Contiguous<int> &, int *);
int now_nanosecond();

void test_contiguous_list_is_empty();
void test_contiguous_list_push_back();

int main()
{
    test_contiguous_list_is_empty();
    test_contiguous_list_push_back();
    return 0;
}

// tool function

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

bool assert_equals_array(Contiguous<int> &c, int *array)
{
    for (int i = 0; i < c.length(); i++)
    {
        if (*c.index_at(i) != array[i])
        {
            std::cerr << "assert failed: " << *c.index_at(i) << " is not equals to " << array[i] << ", index at: " << i << std::endl;
            exit(1);
        }
    }
    return true;
}

int now_nanosecond()
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    int nanoseconds = ns.count();
    return nanoseconds;
}

// test function

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

void test_contiguous_list_push_back()
{
    std::cerr << "test_contiguous_list_push_back start" << std::endl;
    int now = now_nanosecond();

    Contiguous<int> c;

    c.push_back(1);
    int expect[] = {1};
    assert_equals_array(c, expect);

    c.push_back(2);
    int expect2[] = {1, 2};
    assert_equals_array(c, expect2);

    c.clear();
    int expect3[5000];
    for (int i = 0; i < 5000; i++)
    {
        expect3[i] = i;
        c.push_back(i);
    }
    assert_equals_array(c, expect3);

    int now2 = now_nanosecond();
    std::cerr << "test_contiguous_list_is_empty end cost: " << now2 - now << "ns" << std::endl;
}