cmake_minimum_required(VERSION 3.9)
project(PrinProg1)

set(CMAKE_CXX_STANDARD 11)

add_executable(PrinProg1
        compile.dSYM/Contents/Resources/DWARF/compile
        compile.dSYM/Contents/Info.plist
        tests/test-dummy
        tests/test0
        tests/test1
        tests/test2
        tests/test3
        tests/test4
        compile.sol
        Compiler.c
        Instr.h
        InstrUtils.c
        InstrUtils.h
        Interpreter.c
        Makefile
        optimize.sol
        Optimizer.c
        Utils.c
        Utils.h)
