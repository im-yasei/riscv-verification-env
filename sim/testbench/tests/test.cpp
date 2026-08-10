#include "riscv_tester.hpp"
#include <cstdint>
#include <functional>
#include <iostream>
#include <verilated.h>

int test_addi(RiscVTester &);
int test_sw(RiscVTester &);
int test_registers_backdoor_access(RiscVTester &);
int test_memory_backdoor_access(RiscVTester &);

std::function<int(RiscVTester &)> tests[] = {test_addi, test_sw,
                                             test_registers_backdoor_access,
                                             test_memory_backdoor_access};

int test_addi(RiscVTester &tester) {
  int errors = 0;
  std::cout << "===test_addi started===" << std::endl;

  tester.system_reset();

  for (;;) {
    if (tester.get_illegal_instruction_bit() == 1)
      break;
    tester.tick();
  }

  std::cout << "x5 = " << tester.read_register(5) << std::endl;

  if (tester.read_register(5) != 27) {
    errors++;
  }

  std::cout << "===test_addi completed===" << std::endl;

  if (errors > 0) {
    std::cerr << "\033[31mTEST FAILED\033[0m" << std::endl;
    std::cerr << "\033[31mERRORS: " << errors << "\033[0m\n" << std::endl;
  } else {
    std::cout << "\033[32mTEST PASSED\033[0m\n" << std::endl;
  }

  return errors;
}

int test_sw(RiscVTester &tester) {
  int errors = 0;
  std::cout << "===test_lw started===" << std::endl;

  tester.system_reset();

  for (;;) {
    if (tester.get_illegal_instruction_bit() == 1)
      break;
    tester.tick();
  }

  std::cout << "ram[0x0] = " << tester.read_word(0x0) << std::endl;

  if (tester.read_word(0x0) != 27) {
    errors++;
  }

  std::cout << "===test_lw completed===" << std::endl;

  if (errors > 0) {
    std::cerr << "\033[31mTEST FAILED\033[0m" << std::endl;
    std::cerr << "\033[31mERRORS: " << errors << "\033[0m\n" << std::endl;
  } else {
    std::cout << "\033[32mTEST PASSED\033[0m\n" << std::endl;
  }
  return errors;
}

int test_registers_backdoor_access(RiscVTester &tester) {
  int errors = 0;
  std::cout << "===test_registers_backdoor_access started===" << std::endl;

  tester.system_reset();
  tester.write_register(6, 0x11223344);

  std::cout << std::hex << "x6 = 0x" << tester.read_register(6) << std::endl;
  if (tester.read_register(6) != 0x11223344) {
    errors++;
  }

  std::cout << "===test_registers_backdoor_access completed===" << std::endl;

  if (errors > 0) {
    std::cerr << "\033[31mTEST FAILED\033[0m" << std::endl;
    std::cerr << "\033[31mERRORS: " << errors << "\033[0m\n" << std::endl;
  } else {
    std::cout << "\033[32mTEST PASSED\033[0m\n" << std::endl;
  }
  return errors;
}

int test_memory_backdoor_access(RiscVTester &tester) {
  int errors = 0;
  std::cout << "===test_memory_backdoor_access started===" << std::endl;

  tester.system_reset();

  tester.write_word(0x0, 0x11223344);
  if (tester.read_word(0x0) != 0x11223344) {
    errors++;
  }
  std::cout << "ram[0x0] = 0x" << tester.read_word(0x0) << std::endl;

  tester.write_hword(0x2, 0xaabb);
  if (tester.read_hword(0x2) != 0xaabb) {
    errors++;
  }
  std::cout << "ram[0x0] = 0x" << tester.read_word(0x0) << std::endl;

  tester.write_byte(0x1, 0xcc);
  if (tester.read_byte(0x1) != 0xcc) {
    errors++;
  }
  std::cout << "ram[0x0] = 0x" << tester.read_word(0x0) << std::endl;

  if (tester.read_word(0x0) != 0xaabbcc44) {
    errors++;
  }

  std::cout << "===test_memory_backdoor_access completed===" << std::endl;

  if (errors > 0) {
    std::cerr << "\033[31mTEST FAILED\033[0m" << std::endl;
    std::cerr << "\033[31mERRORS: " << errors << "\033[0m\n" << std::endl;
  } else {
    std::cout << "\033[32mTEST PASSED\033[0m\n" << std::endl;
  }
  return errors;
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  std::cout << "===SIMULATION STARTED===\n" << std::endl;

  RiscVTester tester;
  uint32_t test_mask = 0xffffffff;
  int errors = 0;

  if (argc > 1) {
    test_mask = std::stoul(argv[1], nullptr, 16);
  }

  for (auto &test : tests) {
    if (test_mask & 1) {
      errors += test(tester);
    }
    test_mask >>= 1;
  }

  std::cout << "===SIMULATION COMPLETED===" << std::endl;

  if (errors > 0) {
    std::cerr << "\033[31mSOME TESTS HAVE ERRORS\033[0m" << std::endl;
    std::cerr << "\033[31mTOTAL ERRORS: " << errors << "\033[0m" << std::endl;
  } else {
    std::cout << "\033[32mALL TESTS PASSED\033[0m" << std::endl;
  }

  return 0;
}
