
#include <unity.h>

void test_hoge() { TEST_ASSERT_TRUE(1); }


void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_hoge);
    UNITY_END();
}

void loop() {}