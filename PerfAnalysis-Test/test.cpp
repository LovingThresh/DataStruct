#include "pch.h"

namespace PerformanceAnalysisTest {

    // 测试 indexOfMax 函数，测试更多边界情况
    TEST(PerformanceAnalysisTest, IndexOfMaxTest_MoreCases) {
        // 测试空数组
        int* emptyArr = nullptr;  // 使用 nullptr 表示空数组
        EXPECT_EQ(indexOfMax(emptyArr, 0), 0);  // 没有元素时，应该返回0

        // 测试数组中所有元素相同
        int sameArr[] = { 2, 2, 2, 2 };
        EXPECT_EQ(indexOfMax(sameArr, 4), 0);  // 所有元素相同，返回第一个元素的索引

        // 测试负数数组
        int negativeArr[] = { -5, -10, -3, -8 };
        EXPECT_EQ(indexOfMax(negativeArr, 4), 2);  // 最大值是 -3，应该返回索引2
    }

    // 测试 ployEval 函数，测试更多多项式情况
    TEST(PerformanceAnalysisTest, PloyEvalTest_MoreCases) {
        // 测试多项式 4 + 3x + 2x^2 + 1x^3，当 x = 2 时
        int coeff1[] = { 4, 3, 2, 1 };  // 对应 4 + 3x + 2x^2 + 1x^3
        EXPECT_EQ(ployEval(coeff1, 3, 2), 26);  // 计算值 26

        // 测试常数多项式，1 (常数项)
        int coeff2[] = { 1 };
        EXPECT_EQ(ployEval(coeff2, 0, 100), 1);  // 任何 x 都应该返回 1

        // 测试多项式 1 + 2x + 1x^2，当 x = -1 时
        int coeff3[] = { 1, 2, 1 };  // 对应 1 + 2x + 1x^2
        EXPECT_EQ(ployEval(coeff3, 2, -1), 0);  // 应该返回 0
    }

    // 测试 horner 方法，测试更多多项式情况
    TEST(PerformanceAnalysisTest, HornerTest_MoreCases) {
        // 多项式 1x^3 + 2x^2 + 3x + 4，当 x = 2 时
        int coeff1[] = { 4, 3, 2, 1 };  // 系数从高次到低次 {1x^3, 2x^2, 3x, 4}
        EXPECT_EQ(horner(coeff1, 3, 2), 26);  // 计算值应该是 26

        // 测试常数多项式，P(x) = 1
        int coeff2[] = { 1 };  // 只有常数项
        EXPECT_EQ(horner(coeff2, 0, 100), 1);  // 无论 x 是多少，结果都应该是 1

        // 测试多项式 1x^2 + 2x + 1，当 x = -1 时
        int coeff3[] = { 1, 2, 1 };  // 系数从高次到低次 {1x^2, 2x, 1}
        EXPECT_EQ(horner(coeff3, 2, -1), 0);  // 应该返回 0
    }

    // 测试 selectionSort 方法，测试更多情况
    TEST(PerformanceAnalysisTest, SelectionSortTest_MoreCases) {
        // 测试空数组
        int* emptyArr = nullptr;  // 使用 nullptr 表示空数组
        selectionSort(emptyArr, 0);
        EXPECT_EQ(sizeof(emptyArr) / sizeof(int), 2);  // 应该保持空

        // 测试已经排序的数组
        int sortedArr[] = { 1, 2, 3, 4, 5 };
        selectionSort(sortedArr, 5);
        EXPECT_EQ(sortedArr[0], 1);
        EXPECT_EQ(sortedArr[1], 2);
        EXPECT_EQ(sortedArr[2], 3);
        EXPECT_EQ(sortedArr[3], 4);
        EXPECT_EQ(sortedArr[4], 5);  // 保持不变

        // 测试含负数的数组
        int negativeArr[] = { -1, -3, -2, 0, 2 };
        selectionSort(negativeArr, 5);
        EXPECT_EQ(negativeArr[0], -3);
        EXPECT_EQ(negativeArr[1], -2);
        EXPECT_EQ(negativeArr[2], -1);
        EXPECT_EQ(negativeArr[3], 0);
        EXPECT_EQ(negativeArr[4], 2);
    }

    // 测试 bubbleSort 方法，测试更多情况
    TEST(PerformanceAnalysisTest, BubbleSortTest_MoreCases) {
        // 测试空数组
        int* emptyArr = nullptr;  // 使用 nullptr 表示空数组
        bubbleSort(emptyArr, 0);
        EXPECT_EQ(sizeof(emptyArr) / sizeof(int), 2);  // 应该保持空

        // 测试数组中所有元素相同
        int sameArr[] = { 2, 2, 2, 2 };
        bubbleSort(sameArr, 4);
        EXPECT_EQ(sameArr[0], 2);
        EXPECT_EQ(sameArr[1], 2);
        EXPECT_EQ(sameArr[2], 2);
        EXPECT_EQ(sameArr[3], 2);  // 保持不变

        // 测试含负数的数组
        int negativeArr[] = { -1, -3, -2, 0, 2 };
        bubbleSort(negativeArr, 5);
        EXPECT_EQ(negativeArr[0], -3);
        EXPECT_EQ(negativeArr[1], -2);
        EXPECT_EQ(negativeArr[2], -1);
        EXPECT_EQ(negativeArr[3], 0);
        EXPECT_EQ(negativeArr[4], 2);
    }

    // 测试 insertionSort 方法，测试更多情况
    TEST(PerformanceAnalysisTest, InsertionSortTest_MoreCases) {
        // 测试空数组
        int* emptyArr = nullptr;  // 使用 nullptr 表示空数组
        insertionSort(emptyArr, 0);
        EXPECT_EQ(sizeof(emptyArr) / sizeof(int), 2);  // 应该保持空

        // 测试数组中所有元素相同
        int sameArr[] = { 2, 2, 2, 2 };
        insertionSort(sameArr, 4);
        EXPECT_EQ(sameArr[0], 2);
        EXPECT_EQ(sameArr[1], 2);
        EXPECT_EQ(sameArr[2], 2);
        EXPECT_EQ(sameArr[3], 2);  // 保持不变

        // 测试含负数的数组
        int negativeArr[] = { -1, -3, -2, 0, 2 };
        insertionSort(negativeArr, 5);
        EXPECT_EQ(negativeArr[0], -3);
        EXPECT_EQ(negativeArr[1], -2);
        EXPECT_EQ(negativeArr[2], -1);
        EXPECT_EQ(negativeArr[3], 0);
        EXPECT_EQ(negativeArr[4], 2);
    }
}
