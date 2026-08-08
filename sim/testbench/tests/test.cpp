#include "riscv_tester.hpp"
#include <iostream>
#include <verilated.h>

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  RiscVTester tester;

  std::cout << "===SIMULATION STARTED===" << std::endl;

  tester.system_reset();

  for (;;) {
    std::cout << std::hex << "0x" << tester.get_pc() << std::dec
              << " x5=" << tester.read_register(5) << std::endl;
    if (tester.get_illegal_instruction_bit() == 1)
      break;
    tester.tick();
  }

  std::cout << "===SIMULATION COMPLETED===" << std::endl;

  if (tester.read_register(5) == 27) {
    std::cout << "TEST PASSED" << std::endl;
  } else {
    std::cerr << "TEST FAILED" << std::endl;
  }

  std::cout << "x5 = " << tester.read_register(5) << std::endl;

  return 0;
}
