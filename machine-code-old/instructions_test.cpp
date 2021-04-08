#include <iostream>
#include "instructions.h"

using namespace std;

void test() {
    InstructionsClass code;

    // code.PushValue(1000);
    // code.PopAndWrite(); // 1000

    code.PushValue(1000);
    code.PopAndStore(1);

    // code.PushVariable(10);
    // code.PopAndWrite(); // 2000

    // code.PushVariable(10);
    // code.PopAndStore(11);
    // code.PushVariable(10);
    // code.PushVariable(11);
    // code.PopPopAddPush();
    // code.PopAndWrite(); // 4000

    code.Finish();
    code.PrintAllMachineCodes();
    code.Execute();

    std::cout << "Success!" << std::endl;
}
// a
void base() {
    unsigned char mCode[] = { 0x55, 0x8B, 0xEC, 0X5d, 0XC3 };
    cout << "About to Execute the machine code...\n";
    void* ptr = mCode;
    void (*f)(void);
    f = (void (*)(void)) ptr;
    f(); // call the array as if it were a function
    cout << "There and back again!\n\n";
}

int main() {

    // base();

    test();

    return 0;
}
