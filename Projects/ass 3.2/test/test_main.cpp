
#include <avr/delay.h>
#include <unity.h>

#include <fifo.h>

void test_reset(void)
{
    // 1 Setup
    Fifo f;
    f.put(1);
    f.put(2);
    f.put(3);
    f.reset();

    // validate empty
    TEST_ASSERT_TRUE(f.is_empty());
}

void test_normal_flow(void)
{
    // 1 Setup
    Fifo f;
    f.put(1);
    f.put(2);
    f.get();
    f.put(3);

    // 2-3 Execute and validate
    TEST_ASSERT_EQUAL(2, f.get());
    TEST_ASSERT_EQUAL(3, f.get());

    // 4 Cleanup
}

void test_underflow(void)

{
    // 1 Setup
    Fifo f;
    f.put(1);
    f.put(2);
    f.get();
    f.get();

    // 2-3 Execute and validate
    TEST_ASSERT_TRUE(f.is_empty());

    // 4 Cleanup
}

void test_overflow(void){

    // 1 Setup
    Fifo f;
    f.put(1);
    f.get();
    f.put(1);
    f.put(1);
    f.put(1);
    f.put(1);
    f.put(1);

    TEST_ASSERT_TRUE(f.is_full());

}

void test_overwrite(void){

    // 1 Setup
    Fifo f;
    // Put 5 values in buffer
    f.put(2);
    f.put(1);
    f.put(1);
    f.put(1);
    f.put(1);

    // Put 6th value, so the buffer should be overwritten
    f.put(1);

    TEST_ASSERT_EQUAL(f.get(), 1);


}

int main()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    _delay_ms(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    
    
    RUN_TEST(test_normal_flow);
    RUN_TEST(test_underflow);
    RUN_TEST(test_reset);
    RUN_TEST(test_overflow);
    RUN_TEST(test_overwrite);
    // Add more unit tests here

    UNITY_END(); // stop unit testing
}


