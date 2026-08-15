# RISC-V verification environment
This project is based on the RTL code from the MPSU/APS course (https://github.com/MPSU/APS), licensed under CC-BY-SA-4.0. Original work by Andrei Solodovnikov, MIET.

A verification environment for a RISC-V processor system from MIET MPSU/APS course.

![processor_core](images/processor_core.svg?raw=true)
*processor_core*

![processor_system](images/processor_system.svg?raw=true)
*processor_system*

## Done
- Compile the RTL model into a C++ simulation model using Verilator and write a simple testbench that checks the registers after the test program `program.c` has run.
```
#program.c
01400293 # addi x5, x0, 20
00728293 # addi x5, x5, 7
00502023 # sw x5, 0(x0)
00000073 # ecall
```
- Implement a basic Test Harness API (RiscVTester class)
- Set up the RISC-V toolchain for compiling C tests instead of writing machine code
- Implement a program loader in C++ to replace Verilog $readmem (ProgramLoader class)

## To Do
- Implement a RISC-V reference model (GoldenModel class)
- Implement a Scoreboard to compare DUT and GoldenModel states (Scoreboard class)
- Set up CI with GitHub actions
- Integrate llvm-snippy into CI

## Quick start
### Required
- Verilator (5.x or later)
- GCC/G++
- GNU Make

### Build and run
```shell
cd sim/verilator/
make
make run # run all tests
make run mask=0x4 # run tests[2]
make run mask=0x3 # run tests[0] and tests[1]
```
