//
//  main.cpp
//  EmojicodeCompiler
//
//  Created by Theo Weidmann on 05/09/2017.
//  Copyright © 2017 Theo Weidmann. All rights reserved.
//

#include <cstdint>
#include <cinttypes>
#include <cstdlib>
#include <cstdio>

extern "C" int64_t fn_1f3c1();

extern "C" int ejcRunTimeClassValueTypeMeta = 0;

extern "C" int8_t* ejcAlloc(int64_t size) {
    return static_cast<int8_t*>(malloc(size));
}

extern "C" void ejcErrNoValue(int64_t line, int64_t character) {
    printf("💣 Fatal Error: Unwrapped an optional that contained no value. (line %" PRId64 ", character %"
           PRId64 ")\n", line, character);
    abort();
}

int main(int argc, char **argv) {
    auto code = fn_1f3c1();
    return static_cast<int>(code);
}
