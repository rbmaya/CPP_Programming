#include "tritset"
#include <gtest/gtest.h>

TEST(CalculateSize, RightSizeTest1){
    size_t trits_count = 1000;
#ifdef WIN_64
    ASSERT_EQ(calculate_size(trits_count), 63);
#endif

#ifdef unix
    ASSERT_EQ(calculate_size(trits_count), 63);
#endif

#ifdef WIN_32
    ASSERT_EQ(calculate_size(trits_count), 125);
#endif
}


TEST(CalculateShift, RightShiftTest1){
    size_t index1 = 100;
    size_t index2 = 0;

    ASSERT_EQ(calculate_shift(index2), 0);

    ASSERT_EQ(calculate_shift(index1), 8);
}


TEST(NegTest, LogicalTest){
    ASSERT_EQ(neg(False), True);
    ASSERT_EQ(neg(True), False);
    ASSERT_EQ(neg(Unknown), Unknown);
}


TEST(DisjTest, LogicalTest1){
    ASSERT_EQ(disj(False, False), False);
    ASSERT_EQ(disj(False, True), True);
    ASSERT_EQ(disj(False, Unknown), Unknown);
    ASSERT_EQ(disj(True, True), True);
    ASSERT_EQ(disj(True, Unknown), True);
    ASSERT_EQ(disj(Unknown, Unknown), Unknown);
}


TEST(KonjTest, LogicalTest1){
    ASSERT_EQ(konj(False, False), False);
    ASSERT_EQ(konj(False, True), False);
    ASSERT_EQ(konj(False, Unknown), False);
    ASSERT_EQ(konj(True, True), True);
    ASSERT_EQ(konj(True, Unknown), Unknown);
    ASSERT_EQ(konj(Unknown, Unknown), Unknown);
}


TEST(CapacityTest, LenArrayTest){
    TritSet set(1000);
    size_t allocLength = set.capacity();
    ASSERT_GE(allocLength, 1000*2 / 8 / sizeof(unsigned int));
}


TEST(ShrinkTest, MemAllocTest1){
    TritSet set(10);
    set[10000] = True;
    set[1000] = False;
    size_t allocLength = set.capacity();
    set[10000] = Unknown;
    set.shrink();
    ASSERT_GT(allocLength, set.capacity());
}


TEST(ShrinkTest, NoMemAllocTest1){
    TritSet set(10001);
    set[10000] = True;
    size_t allocLength = set.capacity();
    set.shrink();
    ASSERT_EQ(allocLength, set.capacity());
}


TEST(CardinalityEnumTest, RightCardTest1){
    TritSet set(9);
    set[0] = False;
    set[2] = False;
    set[4] = False;
    set[7] = True;
    set[5] = True;
    ASSERT_EQ(set.cardinality(False), 3);
    ASSERT_EQ(set.cardinality(True), 2);
    ASSERT_EQ(set.cardinality(Unknown), 1);
}

TEST(CardinalityAllTest, RightCardTest1){
    TritSet set(9);
    set[0] = False;
    set[2] = False;
    set[4] = False;
    set[7] = True;
    set[5] = True;
    unordered_map <Trit, int, hash<int>> card = set.cardinality();
    ASSERT_EQ(card[False], 3);
    ASSERT_EQ(card[True], 2);
    ASSERT_EQ(card[Unknown], 1);
}

TEST(TrimTest, ResizeMemTest1){
    TritSet set(1000);
    size_t allocLength = set.capacity();
    set.trim(500);
    ASSERT_LT(set.capacity(), allocLength);
    set.trim(0);
    ASSERT_EQ(set.capacity(), 1);
}

TEST(LogicalLengthTest, RightLenTest){
    TritSet set(1000);
    set[58] = True;
    ASSERT_EQ(set.length(), 59);
    set[58] = Unknown;
    ASSERT_EQ(set.length(), 1);
}


TEST(OperatorIndexTest, NoMemAllocTest1){
    TritSet set(10);
    size_t allocLength = set.capacity();
    set[10000] = Unknown;
    ASSERT_EQ(allocLength, set.capacity());
}


TEST(OperatorIndexTest, NoMemAllocTest2){
    TritSet set(10);
    size_t allocLength = set.capacity();
    cout << allocLength << endl;
    if (set[20000] == True) {};
    cout << set.capacity() << endl;
    ASSERT_EQ(allocLength, set.capacity());
}


TEST(OperatorIndexTest, NoMemAllocTest3){
    TritSet set(10);
    set[100000] = True;
    size_t allocLength = set.capacity();
    set[100000] = Unknown;
    set[1000] = True;
    ASSERT_EQ(allocLength, set.capacity());
}


TEST(OperatorIndexTest, MemAllocTest1){
    TritSet set(13);
    size_t allocLength = set.capacity();
    ASSERT_EQ(allocLength, 1);
    set[20] = True;
    ASSERT_EQ(set.capacity(), 2);
    ASSERT_LT(allocLength, set.capacity());
}

TEST(OperatorANDTest, MemAllocTest1){
    TritSet setA(1000);
    TritSet setB(2000);
    TritSet setC = setA & setB;
    ASSERT_EQ(setC.capacity(), setB.capacity());
}


TEST(OperatorANDTest, LogicalTest1){
    TritSet setA(9);
    setA[0] = Unknown;
    setA[1] = True;
    setA[2] = False;
    setA[3] = Unknown;
    setA[4] = True;
    setA[5] = False;
    setA[6] = Unknown;
    setA[7] = True;
    setA[8] = False;

    TritSet setB(9);

    setB[0] = False;
    setB[1] = False;
    setB[2] = False;
    setB[3] = Unknown;
    setB[4] = Unknown;
    setB[5] = Unknown;
    setB[6] = True;
    setB[7] = True;
    setB[8] = True;

    TritSet setC = setA & setB;
    ASSERT_TRUE(setC[0] == False);
    ASSERT_TRUE(setC[1] == False);
    ASSERT_TRUE(setC[2] == False);
    ASSERT_TRUE(setC[3] == Unknown);
    ASSERT_TRUE(setC[4] == Unknown);
    ASSERT_TRUE(setC[5] == False);
    ASSERT_TRUE(setC[6] == Unknown);
    ASSERT_TRUE(setC[7] == True);
    ASSERT_TRUE(setC[8] == False);
}


TEST(OperatorORTest, MemAllocTest1){
    TritSet setA(1000);
    TritSet setB(2000);
    TritSet setC = setA | setB;
    ASSERT_EQ(setC.capacity(), setB.capacity());
}


TEST(OperatorORTest, LogicalTest1){
    TritSet setA(9);
    setA[0] = Unknown;
    setA[1] = True;
    setA[2] = False;
    setA[3] = Unknown;
    setA[4] = True;
    setA[5] = False;
    setA[6] = Unknown;
    setA[7] = True;
    setA[8] = False;

    TritSet setB(9);

    setB[0] = False;
    setB[1] = False;
    setB[2] = False;
    setB[3] = Unknown;
    setB[4] = Unknown;
    setB[5] = Unknown;
    setB[6] = True;
    setB[7] = True;
    setB[8] = True;

    TritSet setC = setA | setB;
    ASSERT_TRUE(setC[0] == Unknown);
    ASSERT_TRUE(setC[1] == True);
    ASSERT_TRUE(setC[2] == False);
    ASSERT_TRUE(setC[3] == Unknown);
    ASSERT_TRUE(setC[4] == True);
    ASSERT_TRUE(setC[5] == Unknown);
    ASSERT_TRUE(setC[6] == True);
    ASSERT_TRUE(setC[7] == True);
    ASSERT_TRUE(setC[8] == True);
}


TEST(OperatorNOT_Test, MemAllocTest1){
    TritSet setA(1000);
    TritSet setB = ~setA;
    ASSERT_EQ(setA.capacity(), setB.capacity());
}


TEST(OperatorNOT_Test, LogicalTest){
    TritSet setA(3);
    setA[0] = False;
    setA[1] = True;
    setA[2] = Unknown;
    TritSet setB = ~setA;
    ASSERT_TRUE(setB[0] == True);
    ASSERT_TRUE(setB[1] == False);
    ASSERT_TRUE(setB[2] == Unknown);
}

TEST(Constructor, Copy){
    TritSet setA(10);
    setA[5] = True;
    setA[9] = False;
    TritSet setB(setA);
    EXPECT_TRUE(setB[5] == True);
    EXPECT_TRUE(setB[9] == False);
    EXPECT_TRUE(setA[5] == True);
}

TEST(Constructor, CopyMove){
    TritSet setA(TritSet(10));
    setA[9] = True;
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}