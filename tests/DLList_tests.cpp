#include "gtest/gtest.h"
#include "DLList.hpp"

class DLList_tests : public ::testing::Test {
protected:
    DLList<int> list{};
    int element{};
};

// first() and last() are tested here.
TEST_F(DLList_tests, Add) {
    list.add(2);
    EXPECT_EQ(list.first(), 2);
    EXPECT_EQ(list.last(), 2);

    list.add(1);
    list.add(3);
    EXPECT_EQ(list.first(), 2);
    EXPECT_EQ(list.last(), 3);
}

TEST_F(DLList_tests, remove) {
    list.add(1);
    list.add(3);

    element = list.remove();
    EXPECT_EQ(element, 3);
    EXPECT_EQ(list.first(), 1);
    EXPECT_EQ(list.last(), 1);
}

TEST_F(DLList_tests, RemoveHandlesEmptyList) {
    list.add(1);
    list.remove();
    EXPECT_THROW(list.remove(), EmptyException);
}

TEST_F(DLList_tests, Element) {
    list.add(1);
    list.add(2, 0);
    list.add(3);
    list.remove(0);

    EXPECT_EQ(list.element(0), 1);
    EXPECT_EQ(list.element(1), 3);
    EXPECT_EQ(list.element(0), list.first());
    EXPECT_EQ(list.element(1), list.last());
}

TEST_F(DLList_tests, ElementHandlesIndexOutOfBounds) {
    list.add(1);
    list.add(2);
    list.add(3);

    EXPECT_THROW(list.element(3), IndexException);
    EXPECT_THROW(list.element(4), IndexException);
    EXPECT_NO_THROW(list.element(2));
}

TEST_F(DLList_tests, IndexAdd) {
    list.add(1, 0);
    list.add(2, 1);
    list.add(3, 1);

    EXPECT_EQ(list.first(), 1);
    EXPECT_EQ(list.element(1), 3);
    EXPECT_EQ(list.last(), 2);
}

TEST_F(DLList_tests, IndexAddHandlesIndexOutOfBounds) {
    list.add(1);
    list.add(2);
    list.add(3);

    EXPECT_THROW(list.add(4, 4), IndexException);
    EXPECT_THROW(list.add(5, 5), IndexException);
    EXPECT_NO_THROW(list.add(6, 3));
}

TEST_F(DLList_tests, RemoveIndex) {
    list.add(1);
    list.add(2);
    list.add(3, 1);
    list.add(4, 1);

    element = list.remove(2);
    EXPECT_EQ(element, 3);

    element = list.remove(2);
    EXPECT_EQ(element, 2);

    element = list.remove(0);
    EXPECT_EQ(element, 1);

    EXPECT_EQ(list.first(), 4);
    EXPECT_EQ(list.last(), 4);
}

TEST_F(DLList_tests, RemoveIndexHandlesIndexOutOfBounds) {
    list.add(1);
    list.add(2);
    list.add(3);

    EXPECT_THROW(list.remove(3), IndexException);
    EXPECT_THROW(list.remove(4), IndexException);
    EXPECT_NO_THROW(list.remove(2));
}

TEST_F(DLList_tests, Empty) {
    EXPECT_TRUE(list.empty());

    list.add(1);
    EXPECT_FALSE(list.empty());

    list.remove();
    EXPECT_TRUE(list.empty());
}

TEST_F(DLList_tests, Size) {
    EXPECT_EQ(list.size(), 0);

    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.size(), 3);

    list.remove();
    EXPECT_EQ(list.size(), 2);
}

TEST_F(DLList_tests, CanAdvance) {
    EXPECT_FALSE(list.can_advance());

    list.add(1);
    list.add(2);

    list.reset_cursor(list.FIRST_NODE);
    EXPECT_TRUE(list.can_advance());

    list.reset_cursor(list.LAST_NODE);
    EXPECT_TRUE(list.can_advance());
}

TEST_F(DLList_tests, Advance) {
    list.add(1);
    list.add(2);
    list.add(3, 0);
    list.add(4, 2);

    list.reset_cursor(list.FIRST_NODE);
    EXPECT_EQ(list.advance(DLList<int>::FORWARDS), 3);
    EXPECT_EQ(list.advance(DLList<int>::FORWARDS), 1);

    list.reset_cursor(list.LAST_NODE);
    EXPECT_EQ(list.advance(DLList<int>::BACKWARDS), 2);
    EXPECT_EQ(list.advance(DLList<int>::BACKWARDS), 4);
}

TEST_F(DLList_tests, AdvanceHandlesCanNotAdvance) {
    EXPECT_THROW(list.advance(DLList<int>::FORWARDS), CursorException);

    list.add(1);
    list.add(2);

    list.reset_cursor(list.FIRST_NODE);
    EXPECT_NO_THROW(list.advance(DLList<int>::BACKWARDS));
    EXPECT_THROW(list.advance(DLList<int>::BACKWARDS), CursorException);

    list.reset_cursor(list.LAST_NODE);
    EXPECT_NO_THROW(list.advance(DLList<int>::FORWARDS));
    EXPECT_THROW(list.advance(DLList<int>::FORWARDS), CursorException);
}

TEST_F(DLList_tests, ResetCursor) {
    list.add(1);
    list.reset_cursor(list.FIRST_NODE);
    EXPECT_TRUE(list.can_advance());

    list.remove();
    list.reset_cursor(list.FIRST_NODE);
    EXPECT_FALSE(list.can_advance());

    list.reset_cursor(list.LAST_NODE);
    EXPECT_FALSE(list.can_advance());
}

TEST_F(DLList_tests, FirstHandlesEmptyList) {
    EXPECT_THROW(list.first(), EmptyException);
}

TEST_F(DLList_tests, LastHandlesEmptyList) {
    EXPECT_THROW(list.last(), EmptyException);
}