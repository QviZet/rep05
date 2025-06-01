#include "Transaction.h"
#include "Account.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;

class MockAcc : public Account{
public:
    MockAcc(int a, int b):Account(a, b){}
    MOCK_METHOD(int,GetBalance,(),(const, override));
    MOCK_METHOD(void,ChangeBalance,(int diff),(override));
    MOCK_METHOD(void,Lock,(),(override));
    MOCK_METHOD(void,Unlock,(),(override));
};

class MockTr : public Transaction{
public:
    MockTr() : Transaction() {};
	MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

// ..................................tests for Account.............

TEST(Account, GetBalance){
    Account acc1(1, 10);
    int balance = acc1.GetBalance();
    EXPECT_EQ(balance, 10);
}

TEST(Account,ChangeBalance){
    Account acc1(1, 10);
    ASSERT_THROW(acc1.ChangeBalance(20), std::runtime_error);
    acc1.Lock();
    acc1.ChangeBalance(20);
    int balance = acc1.GetBalance(); 
    EXPECT_EQ(balance, 10 + 20);
}

TEST(Account, Lock){
    Account acc1(1, 10);
    ASSERT_NO_THROW(acc1.Lock());
}

TEST(Account, Unlock){
    Account acc1(1, 10);
    acc1.Lock();
    ASSERT_NO_THROW(acc1.ChangeBalance(20));
    acc1.Unlock();
    ASSERT_THROW(acc1.ChangeBalance(15), std::runtime_error);
}

// ..................................tests for Transaction.............

TEST(Transaction, Make){
    Account acc1(1, 200);
    Account acc2(2, 300);
    Transaction tr1;
    tr1.set_fee(10);
    bool suc = tr1.Make(acc1, acc2, 150);
    EXPECT_TRUE(suc);
}

TEST(Transaction, SaveToDataBase){
    Transaction tr1;
    Account acc1(1, 200);
    Account acc2(2, 300);
    bool suc = tr1.Make(acc1, acc2, 150);
    EXPECT_TRUE(suc);
}

// ..................................tests generation.............

TEST(MockAcc, Lock){
    MockAcc acc1(1, 200);
    MockAcc acc2(2, 300);
    Transaction tr1;

    EXPECT_CALL(acc1, Lock()).Times(::testing::AtLeast(1));
    bool suc = tr1.Make(acc1, acc2, 150);
}

TEST(MockAcc, Unlock){
    MockAcc acc1(1, 200);
    MockAcc acc2(2, 300);
    Transaction tr1;

    EXPECT_CALL(acc1, Unlock()).Times(::testing::AtLeast(1));
    bool suc = tr1.Make(acc1, acc2, 150);
}

TEST(MockAcc, GetBalance){
    MockAcc acc1(1, 200);
    MockAcc acc2(2, 300);
    Transaction tr1;

    EXPECT_CALL(acc1, GetBalance()).Times(::testing::AtLeast(1));
    bool suc = tr1.Make(acc1, acc2, 150);
}

TEST(MockAcc, ChangeBalance){
    MockAcc acc1(1, 200);
    MockAcc acc2(2, 300);
    Transaction tr1;

    ON_CALL(acc1, GetBalance()).WillByDefault(::testing::Return(200));
    ON_CALL(acc2, GetBalance()).WillByDefault(::testing::Return(300));
    EXPECT_CALL(acc1, ChangeBalance(_)).Times(::testing::AtLeast(1));
    bool suc = tr1.Make(acc1, acc2, 150);
}

int main(int argc, char** argv) {
    ::testing::FLAGS_gmock_verbose = "error";
	::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
