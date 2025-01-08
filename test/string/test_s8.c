#include "tomato_string.h"

const char text[] = "The FitnessGram™ Pacer Test is a multistage aerobic capacity test that progressively gets more difficult as it continues. The 20 meter pacer test will begin in 30 seconds. Line up at the start. The running speed starts slowly, but gets faster each minute after you hear this signal. [beep] A single lap should be completed each time you hear this sound. [ding] Remember to run in a straight line, and run as long as possible. The second time you fail to complete a lap before the sound, your test is over. The test will begin on the word start. On your mark, get ready, start.";

void run_test_001()
{
    s8 str = S8("text");
    s8_debug_print(str);
    s8_free(str);
    // s8_debug_print(str);
}


int main()
{
    run_test_001();
    // run_test_002();
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