#include "contiguous_list.h"
#include <iostream>
#include <chrono>
#include <execinfo.h>
#include <cstdlib>

bool assert_equals_int(int, int);
bool assert_equals_bool(bool, bool);
bool assert_equals_array(Contiguous<int> &, int *);
int now_nanosecond();
void print_call_stack();
bool assert_is_null(void *p);
string duration_string(int);

void test_contiguous_list_is_empty();
void test_contiguous_list_push_back();
void test_contiguous_list_pop_back();
void test_contiguous_list_clear();
void test_contiguous_list_length();
void test_contiguous_list_index_at();
void test_contiguous_list_index_of();

int main()
{
    test_contiguous_list_is_empty();
    test_contiguous_list_push_back();
    test_contiguous_list_pop_back();
    test_contiguous_list_clear();
    test_contiguous_list_length();
    test_contiguous_list_index_at();
    test_contiguous_list_index_of();
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
    print_call_stack();
    exit(1);
}

bool assert_equals_bool(bool val1, bool val2)
{
    if (val1 == val2)
    {
        return true;
    }
    std::cerr << "assert failed: " << val1 << " is not equals to " << val2 << std::endl;
    print_call_stack();
    exit(1);
}

bool assert_equals_array(Contiguous<int> &c, int *array)
{
    for (int i = 0; i < c.length(); i++)
    {
        int a;
        c.index_at(i, &a);
        if (a != array[i])
        {
            std::cerr << "assert failed: " << a << " is not equals to " << array[i] << ", index at: " << i << std::endl;
            print_call_stack();
            exit(1);
        }
    }
    return true;
}

bool assert_is_null(void *p)
{
    if (p == nullptr)
    {
        return true;
    }
    std::cerr << "assert failed: " << p << " is not null" << endl;
    print_call_stack();
    exit(1);
}

void print_call_stack()
{
    void *buffer[100];
    char **strings;

    int nptrs = backtrace(buffer, 100);
    printf("Traceback: backtrace() returned %d addresses\n", nptrs);
    strings = backtrace_symbols(buffer, nptrs);
    for (int i = 0; i < nptrs; i++)
    {
        printf("%s\n", strings[i]);
    }
}

int now_nanosecond()
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    int nanoseconds = ns.count();
    return nanoseconds;
}

string duration_string(int nanoseconds)
{
    float value;
    char buffer[128];

    if (nanoseconds > 0 && nanoseconds <= 10e4)
    {
        value = nanoseconds / float(10e0);
        sprintf(buffer, "%.3f", value);
        return string(buffer) + "ns";
    }

    if (nanoseconds > 10e4 && nanoseconds <= 10e7)
    {
        value = nanoseconds / 10e6 * 10e6;
        value = nanoseconds / float(10e3);
        sprintf(buffer, "%.3f", value);
        return string(buffer) + "us";
    }

    if (nanoseconds > 10e7 && nanoseconds <= 10e10)
    {
        value = nanoseconds / 10e9 * 10e9;
        value = nanoseconds / float(10e6);
        sprintf(buffer, "%.3f", value);
        return string(buffer) + "ms";
    }

    value = nanoseconds / 10e12 * 10e12;
    value = nanoseconds / float(10e9);
    sprintf(buffer, "%.3f", value);
    return string(buffer) + "s";
}

// test function

void test_contiguous_list_is_empty()
{
    std::cerr << "test_contiguous_list_is_empty start" << std::endl;
    int now = now_nanosecond();

    Contiguous<int> c;
    assert_equals_bool(c.is_empty(), true);
    c.push_back(1);
    assert_equals_bool(c.is_empty(), false); // wrong
    c.pop_back(nullptr);
    assert_equals_bool(c.is_empty(), true);
    c.push_back(1);
    c.push_back(1);
    c.push_back(1);
    assert_equals_bool(c.is_empty(), false);
    c.clear();
    assert_equals_bool(c.is_empty(), true);

    int now2 = now_nanosecond();
    std::cerr << "test_contiguous_list_is_empty end cost: " << duration_string(now2 - now) << std::endl;
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
    std::cerr << "test_contiguous_list_is_empty end cost: " << duration_string(now2 - now) << std::endl;
}

void test_contiguous_list_pop_back()
{
    std::cerr << "test_contiguous_list_pop_back start" << std::endl;
    int now = now_nanosecond();

    Contiguous<int> c;
    c.push_back(1);
    int a;
    c.pop_back(&a);
    assert_equals_int(1, a);

    c.push_back(2);
    c.push_back(3);
    c.pop_back(&a);
    assert_equals_int(3, a);

    c.pop_back(&a);
    assert_equals_int(2, a);

    int now2 = now_nanosecond();
    std::cerr << "test_contiguous_list_pop_back end cost: " << duration_string(now2 - now) << std::endl;
}

void test_contiguous_list_clear()
{
    std::cerr << "test_contiguous_list_clear start" << std::endl;
    int now = now_nanosecond();

    Contiguous<int> c;
    c.clear();
    int expect[] = {};
    assert_equals_array(c, expect);

    c.push_back(1);
    c.clear();
    assert_equals_array(c, expect);
    for (int i = 0; i < 5000; i++)
    {
        c.push_back(i);
    }

    c.clear();
    assert_equals_array(c, expect);
    int now2 = now_nanosecond();
    std::cerr << "test_contiguous_list_clear end cost: " << duration_string(now2 - now) << std::endl;
}

void test_contiguous_list_length()
{
    std::cerr << "test_contiguous_list_length start" << std::endl;
    int now = now_nanosecond();

    Contiguous<int> c;
    assert_equals_int(c.length(), 0);

    c.push_back(1);
    assert_equals_int(c.length(), 1);

    c.pop_back(nullptr);
    assert_equals_int(c.length(), 0);

    c.pop_back(nullptr);
    assert_equals_int(c.length(), 0);

    for (int i = 0; i < 5000; i++)
    {
        c.push_back(i);
    }
    assert_equals_int(c.length(), 5000);

    c.clear();
    assert_equals_int(c.length(), 0);

    int now2 = now_nanosecond();
    std::cerr << "test_contiguous_list_length end cost: " << duration_string(now2 - now) << std::endl;
}

void test_contiguous_list_index_at()
{
    std::cerr << "test_contiguous_list_index_at start" << std::endl;
    int now = now_nanosecond();

    Contiguous<int> c;
    int a = 0;
    c.index_at(10, &a);
    assert_equals_int(a, 0);

    c.push_back(1);
    c.index_at(0, &a);
    assert_equals_int(a, 1);

    c.clear();

    for (int i = 0; i < 1000; i++)
    {
        c.push_back(i);
        for (int j = 0; j < i; j++)
        {
            int a = 0;
            c.index_at(j, &a);
            assert_equals_int(a, j);
        }
    }

    int now2 = now_nanosecond();
    std::cerr << "test_contiguous_list_index_at end cost: " << duration_string(now2 - now) << std::endl;
}

void test_contiguous_list_index_of()
{
    std::cerr << "test_contiguous_list_index_of start" << std::endl;
    int now = now_nanosecond();

    Contiguous<int> c;
    int index = c.index_of(10);
    assert_equals_int(index, -1);

    c.push_back(1);
    index = c.index_of(1);
    assert_equals_int(index, 0);

    c.clear();

    for (int i = 0; i < 1000; i++)
    {
        c.push_back(i);
        for (int j = 0; j < i; j++)
        {
            int a = 0;
            int index = c.index_of(j);
            assert_equals_int(index, j);
        }
    }

    int now2 = now_nanosecond();
    std::cerr << "test_contiguous_list_index_of end cost: " << duration_string(now2 - now) << std::endl;
}