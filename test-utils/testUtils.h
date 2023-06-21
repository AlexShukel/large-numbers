//
// Created by alexs on 2023-05-14.
//

#ifndef ND1_TESTUTILS_H
#define ND1_TESTUTILS_H

#include "vector"

template<class T>
void expectVectorsEquality(const std::vector<T> &a, const std::vector<T> &b) {
    ASSERT_EQ(a.size(), b.size());

    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
}

#endif //ND1_TESTUTILS_H
