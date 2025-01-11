#include "tomato_string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// clang-format off
const char text[] = "The FitnessGram Pacer Test is a multistage aerobic capacity test that progressively gets more difficult as it continues. The 20 meter pacer test will begin in 30 seconds. Line up at the start. The running speed starts slowly, but gets faster each minute after you hear this signal. [beep] A single lap should be completed each time you hear this sound. [ding] Remember to run in a straight line, and run as long as possible. The second time you fail to complete a lap before the sound, your test is over. The test will begin on the word start. On your mark, get ready, start.";
// clang-format on

void run_test_001()
{
    // s8 str = S8("text");
    s8 str = s8_from(((sizeof("text") / sizeof(("text")[0])) - 1), ("text"));
    assert(s8_debug_print(str) == 25);
    s8_free(str);
}

void run_test_002()
{
    s8 str = S8("text");
    assert(s8_print(str) == 4);
    s8_free(str);
}

int main()
{
    printf("\nTest 001:\n");
    run_test_001();
    printf("\nTest 002:\n");
    run_test_002();
    printf("\nTest 003:\n");
    // run_test_003();
    // run_test_004();
    // run_test_005();
    // run_test_006();
    // run_test_007();
    // run_test_008();
    // run_test_009();
    // run_test_010();
    // run_test_011();
    // run_test_012();
    // run_test_013();
    // run_test_014();
    // run_test_015();
    // run_test_016();
    // run_test_017();
    return 0;
}