#include <gtest/gtest.h>
#include "listStreams.h"

class ListStreams : public testing::Test {
public:
	ListStreams *l;
	int size = 0;

	void SetUp() {}
	void TearDown() {}
};

TEST_F(ListStreams, InitList) {
	l = new ListStreams;
	ASSERT_TRUE(l->isEmpty());
}

TEST_F(ListStreams, FillList) {
	for (int i = 0; i < 50; ++i) {
		l->push(std::string(1, 'A' + i), i);
		++size;
	}
	ListStreams::Iterator it = l->getHead();
	EXPECT_EQ(it->getSurname(), "A");
	EXPECT_EQ(it->getNumber(), 0);
	while (it)
		it = it->getNextBySurname();
	EXPECT_EQ(it->getSurname(), string(1, 'A' + 49));
	EXPECT_EQ(it->getNumber(), 49);
	ASSERT_EQ(size, 50);
}

TEST_F(ListStreams, FindNodes) {
	for (int i = 5; i < 10; ++i) {
		ASSERT_EQ(l->getSurname(i), string(1, 'A' + i));
		ASSERT_EQ(l->getNumber(string(1, 'A' + i)), i);
	}
}

TEST_F(ListStreams, ClearList) {
	l->clear();
	size = 0;
	ASSERT_EQ(l->isEmpty(), true);
}

TEST_F(ListStreams, PushAndPop) {
	l->push("N",size++);
	short int popped = l->pop(size);
	size = 0;

	ASSERT_EQ(popped, 0);
	ASSERT_EQ(l->pop(size), -1);
}
