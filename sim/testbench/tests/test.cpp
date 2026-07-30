#include "Vtest_top.h"
#include "Vtest_top___024root.h"
#include <iostream>
#include <verilated.h>

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Vtest_top *top = new Vtest_top;

  std::cout << "SIMULATION STARTED" << std::endl;

  top->clk_i = 0;
  top->rst_i = 1;
  top->eval();

  for (int i = 0; i < 3; i++) {
    top->clk_i = !top->clk_i;
    top->eval();
  }

  top->rst_i = 0;
  top->eval();
 
  for(;;){
    if (top->rootp->test_top__DOT__core__DOT__ziZG3f3w85eBr == 1) break; // illegal_instr == 1
    top->clk_i = !top->clk_i;
    top->eval();
  }

  std::cout << "SIMULATION COMPLETED" << std::endl;

  if (top->rootp->test_top__DOT__core__DOT__v9QOWb9Pd9__DOT__rf_mem[5] == 27){
    std::cout << "TEST PASSED" << std::endl;
  } else {
    std::cout << "TEST FAILED" << std::endl;
  }

  std::cout << "x5 = " << top->rootp->test_top__DOT__core__DOT__v9QOWb9Pd9__DOT__rf_mem[5]
            << std::endl;

  top->final();
  delete top;
  return 0;
}
