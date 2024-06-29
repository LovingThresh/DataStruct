#include <cassert>
#include <iostream>
#include <cstring>
#include "Exercise_1_2.h"
#include "Exercise_1_3.h"

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
        const std::vector<int> v = { 1, 2, 3, 4, 5 };
        assert(count(v) == 5);
    }

    void tes_case_2_extra()
    {
        const std::vector<int> v {};
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
        std::vector<int> v{ 1, 2, 3, 4, 5 };
        constexpr int value = 0;
        const std::vector<int> result = fill(v, value);
        for (const auto& element : result)
        {
            assert(element == value);
        }
    }

    void test_case_4_int()
    {
        const std::vector<int> va{ 1, 2, 3, 4, 5 };
        const std::vector<int> vb{ 1, 2, 3, 4, 5 };
        int result = 0;
        result = inner_product(va, vb, result);
        assert(result == 55);
    }

    void test_case_4_float()
    {
        const std::vector<float> va{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
        const std::vector<float> vb{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
        float result = 0.0f;
        result = inner_product(va, vb, result);
        assert(std::fabs(result - 66.55f) < epsilon);
    }

    void test_iota_normal_case() {
        // 准备测试数据
        std::vector<int> vec_normal(5); // 创建一个大小为5的向量
        constexpr int start_value = 3;            // 设定起始值

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

    void test_iota_overflow_case() {
        // 准备测试数据，这里使用uint8_t作为类型，容易达到其最大值导致溢出
        std::vector<uint8_t> vec_overflow(10); // 创建一个大小为10的向量
        constexpr uint8_t start_value = std::numeric_limits<uint8_t>::max() - 5;

        try {
            // 调用 iota 函数，期望抛出异常
            iota(vec_overflow, start_value);
            // 如果没有抛出异常，则说明测试失败
            std::cerr << "Test case 2 failed: No overflow error thrown." << '\n';
        }
        catch (const std::overflow_error&) {
            // 验证是否捕获到了正确的异常类型
            std::cout << "Test case 2 passed: Overflow error caught as expected." << '\n';
        }

    }

    void test_mismatch_normal_case()
    {
        // equal
        std::vector<int> vec1 { 1, 2, 3, 4, 5 };
        std::vector<int> vec2 { 1, 2, 3, 4, 5 };

        const auto result1 = mismatch(vec1, vec2);
        assert(result1 == no_mismatch);
        std::cout << "Test case passed: equal case." << '\n';

        // subsequence
        vec1 = { 1, 2, 3, 4};
        const auto result2 = mismatch(vec1, vec2);
        assert(result2 == 4);
        std::cout << "Test case passed: subsequence case." << '\n';

        // mismatch
        vec2 = { 1, 2, 4, 4, 5 };
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
                std::cerr << "There is some parameter less than 0." << '\n';
                std::cerr << "Test case 0 as Excepted: Exception 0 thrown." << '\n';
            }

            if (e == 1)
            {
                std::cerr << "All parameters are less than 0." << '\n';
                std::cerr << "Test case 1 as Excepted: Exception 1 thrown." << '\n';
            }

            if (e == 2)
            {
                std::cerr << "All parameters are equal to 0." << '\n';
                std::cout << "Test case 2 as Excepted: Exception 2 thrown." << '\n';
            }

        }
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

    return 0;
}
