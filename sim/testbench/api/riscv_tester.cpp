#include "riscv_tester.hpp"
#include "Vtest_top___024root.h"
#include <iostream>

// utils
void RiscVTester::system_reset() {
  top->clk_i = 0;
  top->rst_i = 1;
  evaluate();

  tick();

  top->rst_i = 0;
  evaluate();

  clear_registers();
  evaluate();
}

void RiscVTester::evaluate() { top->eval(); }

// ===FRONTDOOR API===
void RiscVTester::tick() {
  top->clk_i = 1;
  evaluate();
  top->clk_i = 0;
  evaluate();
}

void RiscVTester::enable_rst() { top->rst_i = 1; }
void RiscVTester::disable_rst() { top->rst_i = 0; }

void RiscVTester::enable_irq_req_i() { top->irq_req_i = 1; }
void RiscVTester::disable_irq_req_i() { top->irq_req_i = 0; }

bool RiscVTester::get_irq_ret_o() { return top->irq_ret_o; }

// ===BACKDOOR API===
// registers
uint32_t RiscVTester::read_register(int index) {
  if ((index >= 0) && (index <= 31)) {
    return top->rootp->test_top__DOT__core__DOT__v9QOWb9Pd9__DOT__rf_mem[index];
  } else {
    std::cerr << "ERROR: invalid index" << std::endl;
    return 0;
  }
}

void RiscVTester::write_register(int index, uint32_t value) {
  top->rootp->test_top__DOT__core__DOT__v9QOWb9Pd9__DOT__rf_mem[index] = value;
}

void RiscVTester::clear_registers() {
  for (int i = 0; i < 32; i++) {
    write_register(i, 0);
  }
}

// pc
void RiscVTester::set_pc(uint32_t value) {
  top->rootp->test_top__DOT__core__DOT__KD = value;
}

uint32_t RiscVTester::get_pc() {
  return top->rootp->test_top__DOT__core__DOT__KD;
}

// illegal_instruction
bool RiscVTester::get_illegal_instruction_bit() {
  return top->rootp->test_top__DOT__core__DOT__ziZG3f3w85eBr;
}
