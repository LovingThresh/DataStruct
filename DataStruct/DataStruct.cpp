#include <cassert>
#include <iostream>
#include <cstring>
#include "Exercise_1_2.hpp"
#include "Exercise_1_3.hpp"
#include "Exercise_1_4.hpp"

constexpr float epsilon = 1e-6f;

namespace test_1_2
{
    void test_case_1()
    {
        int a = 1;
        int b = 2;
        swap(a, b);
        assert(a == 2);
        assert(b == 1);
    }

    void test_case_2()
    {
        const std::vector<int> v = {1, 2, 3, 4, 5};
        assert(count(v) == 5);
    }

    void tes_case_2_extra()
    {
        const std::vector<int> v{};
        try
        {
            count(v);
        }
        catch (const char* e)
        {
            assert(strcmp(e, "n should not < 1") == 0);
        }
    }

    void test_case_3()
    {
        std::vector<int> v{1, 2, 3, 4, 5};
        constexpr int value = 0;
        const std::vector<int> result = fill(v, value);
        for (const auto& element : result)
        {
            assert(element == value);
        }
    }

    void test_case_4_int()
    {
        const std::vector<int> va{1, 2, 3, 4, 5};
        const std::vector<int> vb{1, 2, 3, 4, 5};
        int result = 0;
        result = inner_product(va, vb, result);
        assert(result == 55);
    }

    void test_case_4_float()
    {
        const std::vector<float> va{1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
        const std::vector<float> vb{1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
        float result = 0.0f;
        result = inner_product(va, vb, result);
        assert(std::fabs(result - 66.55f) < epsilon);
    }

    void test_iota_normal_case()
    {
        // 准备测试数据
        std::vector<int> vec_normal(5); // 创建一个大小为5的向量
        constexpr int start_value = 3; // 设定起始值

        // 调用 iota 函数
        iota(vec_normal, start_value);

        // 验证结果
        assert(vec_normal[0] == 3);
        assert(vec_normal[1] == 4);
        assert(vec_normal[2] == 5);
        assert(vec_normal[3] == 6);
        assert(vec_normal[4] == 7);

        std::cout << "Test case 1 passed: Normal case." << '\n';
    }

    void test_iota_overflow_case()
    {
        // 准备测试数据，这里使用uint8_t作为类型，容易达到其最大值导致溢出
        std::vector<uint8_t> vec_overflow(10); // 创建一个大小为10的向量
        constexpr uint8_t start_value = std::numeric_limits<uint8_t>::max() - 5;

        try
        {
            // 调用 iota 函数，期望抛出异常
            iota(vec_overflow, start_value);
            // 如果没有抛出异常，则说明测试失败
            std::cerr << "Test case 2 failed: No overflow error thrown." << '\n';
        }
        catch (const std::overflow_error&)
        {
            // 验证是否捕获到了正确的异常类型
            std::cout << "Test case 2 passed: Overflow error caught as expected." << '\n';
        }
    }

    void test_mismatch_normal_case()
    {
        // equal
        std::vector<int> vec1{1, 2, 3, 4, 5};
        std::vector<int> vec2{1, 2, 3, 4, 5};

        const auto result1 = mismatch(vec1, vec2);
        assert(result1 == no_mismatch);
        std::cout << "Test case passed: equal case." << '\n';

        // subsequence
        vec1 = {1, 2, 3, 4};
        const auto result2 = mismatch(vec1, vec2);
        assert(result2 == 4);
        std::cout << "Test case passed: subsequence case." << '\n';

        // mismatch
        vec2 = {1, 2, 4, 4, 5};
        const auto result3 = mismatch(vec1, vec2);
        assert(result3 == 2);

        std::cout << "Test case passed: Normal case." << '\n';
    }
}

namespace test_1_3
{
    void test_abc_exception()
    {
        try
        {
            constexpr int a = 0;
            constexpr int b = 0;
            constexpr int c = 0;
            abc(a, b, c);
        }
        catch (int e)
        {
            if (e == 0)
            {
                std::cout << "There is some parameter less than 0." << '\n';
                std::cout << "Test case 0 as Excepted: Exception 0 thrown." << '\n';
            }

            if (e == 1)
            {
                std::cout << "All parameters are less than 0." << '\n';
                std::cout << "Test case 1 as Excepted: Exception 1 thrown." << '\n';
            }

            if (e == 2)
            {
                std::cout << "All parameters are equal to 0." << '\n';
                std::cout << "Test case 2 as Excepted: Exception 2 thrown." << '\n';
            }
        }
    }
}

namespace test_1_4
{
    void test_make2_array_normal()
    {
        try
        {
            int** x;
            constexpr int rows = 5;
            constexpr int columns = 6;
            constexpr int init_value = 0;
            make_2_array(x, rows, columns);
            init_2_array(x, rows, columns, init_value);
            print_array(x, 5, 6);
            delete_2_array(x, rows);
        }
        catch (std::bad_alloc&)
        {
            std::cerr << "Could not create x" << '\n';
        }
    }

    void test_make2_array_case2()
    {
        const int* y = new int [6]{1, 3, 3, 6, 5, 6};
        try
        {
            int** x;
            constexpr int rows = 6;
            constexpr int init_value = 1;
            make_2_array(x, rows, y);
            init_2_array(x, rows, y, init_value);
            print_array(x, rows, y);
            delete_2_array(x, rows);
            delete [] y;
        }
        catch (std::bad_alloc&)
        {
            std::cout << "Error: Could not create x" << '\n';
            delete [] y;
        }
        catch (std::invalid_argument&)
        {
            std::cout << "Error: Could not create y" << '\n';
            delete [] y;
        }
    }

    void test_increase_length()
    {
        auto arr = new int[5]{1, 2, 3, 4, 5};
        const int* new_arr = change_length_1d(arr, 5, 8);
        assert(new_arr != nullptr);
        assert(arr == nullptr);
        for (int i = 0; i < 5; ++i)
        {
            assert(new_arr[i] == i+1);
        }
        for (int i = 5; i < 8; ++i)
        {
            assert(new_arr[i] == 0);
        }
        delete[] new_arr;
    }

    void test_decrease_length()
    {
        auto arr2 = new int[8]{1, 2, 3, 4, 5, 6, 7, 8};
        const int* new_arr2 = change_length_1d(arr2, 8, 5);
        assert(new_arr2 != nullptr);
        assert(arr2 == nullptr);
        for (int i = 0; i < 5; ++i)
        {
            assert(new_arr2[i] == i+1);
        }
        delete[] new_arr2;
    }

    void test_same_length()
    {
        auto arr3 = new int[5]{1, 2, 3, 4, 5};
        const int* new_arr3 = change_length_1d(arr3, 5, 5);
        assert(new_arr3 != nullptr);
        assert(arr3 == nullptr);
        for (int i = 0; i < 5; ++i)
        {
            assert(new_arr3[i] == i+1);
        }
        delete[] new_arr3;
    }

    void test_length_to_zero()
    {
        auto arr4 = new int[3]{1, 2, 3};
        const int* new_arr4 = change_length_1d(arr4, 3, 0);
        assert(new_arr4 == nullptr);
        assert(arr4 == nullptr);
    }

    void test_increase_2d_length()
    {
        auto arr = new int*[1];
        arr[0] = new int[2]{1, 2};

        constexpr int old_rows = 1, old_columns = 2;
        constexpr int new_rows = 3, new_columns = 4;

        int** new_arr = change_length_2d(arr, old_rows, old_columns, new_rows, new_columns);

        assert(new_arr != nullptr);
        assert(arr == nullptr);

        // Check original elements
        assert(new_arr[0][0] == 1);
        assert(new_arr[0][1] == 2);

        // Check new elements are initialized to 0
        for (int i = 0; i < new_rows; ++i)
        {
            for (int j = old_columns; j < new_columns; ++j)
            {
                assert(new_arr[i][j] == 0);
            }
        }
        for (int i = old_rows; i < new_rows; ++i)
        {
            for (int j = 0; j < new_columns; ++j)
            {
                assert(new_arr[i][j] == 0);
            }
        }

        for (int i = 0; i < new_rows; ++i)
        {
            delete[] new_arr[i];
        }
        delete[] new_arr;
    }

    void test_decrease_2d_length()
    {
        auto arr = new int*[3];
        arr[0] = new int[3]{1, 2, 3};
        arr[1] = new int[3]{4, 5, 6};
        arr[2] = new int[3]{7, 8, 9};

        constexpr int old_rows = 3, old_columns = 3;
        constexpr int new_rows = 2, new_columns = 2;

        int** new_arr = change_length_2d(arr, old_rows, old_columns, new_rows, new_columns);

        assert(new_arr != nullptr);
        assert(arr == nullptr);

        // Check remaining elements
        assert(new_arr[0][0] == 1);
        assert(new_arr[0][1] == 2);
        assert(new_arr[1][0] == 4);
        assert(new_arr[1][1] == 5);

        for (int i = 0; i < new_rows; ++i)
        {
            delete[] new_arr[i];
        }
        delete[] new_arr;
    }

    void test_same_2d_length()
    {
        auto arr = new int*[2];
        arr[0] = new int[2]{1, 2};
        arr[1] = new int[2]{3, 4};

        constexpr int old_rows = 2, old_columns = 2;
        constexpr int new_rows = 2, new_columns = 2;

        int** new_arr = change_length_2d(arr, old_rows, old_columns, new_rows, new_columns);

        assert(new_arr != nullptr);
        assert(arr == nullptr);

        // Check elements remain the same
        assert(new_arr[0][0] == 1);
        assert(new_arr[0][1] == 2);
        assert(new_arr[1][0] == 3);
        assert(new_arr[1][1] == 4);

        for (int i = 0; i < new_rows; ++i)
        {
            delete[] new_arr[i];
        }
        delete[] new_arr;
    }

    void test_2d_length_to_zero()
    {
        auto arr = new int*[2];
        arr[0] = new int[2]{1, 2};
        arr[1] = new int[2]{3, 4};

        constexpr int old_rows = 2, old_columns = 2;
        constexpr int new_rows = 0, new_columns = 0;

        int** new_arr = change_length_2d(arr, old_rows, old_columns, new_rows, new_columns);

        assert(new_arr == nullptr);
        assert(arr == nullptr);
    }
}

int main()
{
    test_1_2::test_case_1();
    std::cout << "test case 1 passed!" << '\n';
    std::cout << "---------------------------" << '\n';

    test_1_2::test_case_2();
    test_1_2::tes_case_2_extra();
    std::cout << "test case 2 passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_2::test_case_3();
    std::cout << "test case 3 passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_2::test_case_4_int();
    std::cout << "test case 4-int passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_2::test_case_4_float();
    std::cout << "test case 4-float passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_2::test_iota_normal_case();
    std::cout << "test iota normal case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_2::test_iota_overflow_case();

    std::cout << "---------------------------" << '\n';
    test_1_2::test_mismatch_normal_case();
    std::cout << "All test mismatch case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_3::test_abc_exception();
    std::cout << "All test abc exception case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_make2_array_normal();
    std::cout << "test make 2 array case 1 passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_make2_array_case2();
    std::cout << "test make 2 array case 2 passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_increase_length();
    std::cout << "test increase length case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_decrease_length();
    std::cout << "test decrease length case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_same_length();
    std::cout << "test same length case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_length_to_zero();
    std::cout << "test length to zero case passed!" << '\n';
    std::cout << "All test cases to change 1D length passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_increase_2d_length();
    std::cout << "test 2d increase length case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_decrease_2d_length();
    std::cout << "test decrease 2d length case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_same_2d_length();
    std::cout << "test same 2d length case passed!" << '\n';

    std::cout << "---------------------------" << '\n';
    test_1_4::test_2d_length_to_zero();
    std::cout << "test 2d length to zero case passed!" << '\n';

    std::cout << "All test cases to change 2D length passed!" << '\n';

    return 0;
}
