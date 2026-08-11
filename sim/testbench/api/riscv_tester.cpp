#include "riscv_tester.hpp"
#include "Vtest_top___024root.h"
#include <cstdint>
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
  clear_ram();
}

void RiscVTester::evaluate() { top->eval(); }

// ===FRONTDOOR API===
void RiscVTester::tick() {
  top->clk_i = 1;
  evaluate();
  top->clk_i = 0;
  evaluate();
}

void RiscVTester::enable_rst() {
  top->rst_i = 1;
  evaluate();
}
void RiscVTester::disable_rst() {
  top->rst_i = 0;
  evaluate();
}

void RiscVTester::enable_irq_req_i() {
  top->irq_req_i = 1;
  evaluate();
}
void RiscVTester::disable_irq_req_i() {
  top->irq_req_i = 0;
  evaluate();
}

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
  evaluate();
}

void RiscVTester::clear_registers() {
  for (int i = 0; i < 32; i++) {
    top->rootp->test_top__DOT__core__DOT__v9QOWb9Pd9__DOT__rf_mem[i] = 0;
  }
  evaluate();
}

// memory
uint32_t RiscVTester::read_word(uint32_t addr) {
  if ((addr & 0x3) != 0) {
    std::cerr << "ERROR: read_word invalid address" << std::endl;
    return 0;
  }

  return top->rootp->test_top__DOT__data_mem__DOT__ram[addr >> 2];
}

void RiscVTester::write_word(uint32_t addr, uint32_t value) {
  if ((addr & 0x3) != 0) {
    std::cerr << "ERROR: write_word invalid address" << std::endl;
    return;
  }

  top->rootp->test_top__DOT__data_mem__DOT__ram[addr >> 2] = value;
  evaluate();
}

uint16_t RiscVTester::read_hword(uint32_t addr) {
  if ((addr & 0x1) != 0) {
    std::cerr << "ERROR: read_hword invalid address" << std::endl;
    return 0;
  }

  uint32_t word = top->rootp->test_top__DOT__data_mem__DOT__ram[addr >> 2];
  uint16_t offset = addr & 0x3;
  uint16_t hword = (word >> (offset * 8)) & 0x0000ffff;

  return hword;
}

void RiscVTester::write_hword(uint32_t addr, uint16_t value) {
  if ((addr & 0x1) != 0) {
    std::cerr << "ERROR: write_hword invalid address" << std::endl;
    return;
  }

  uint32_t word = top->rootp->test_top__DOT__data_mem__DOT__ram[addr >> 2];
  uint16_t offset = addr & 0x3;
  uint32_t value32 = value;
  uint32_t mask = (offset == 0) ? 0xffff0000 : 0x0000ffff;

  word = word & mask;
  word = word | (value32 << (offset * 8));

  top->rootp->test_top__DOT__data_mem__DOT__ram[addr >> 2] = word;
  evaluate();
}

uint8_t RiscVTester::read_byte(uint32_t addr) {
  uint32_t word = top->rootp->test_top__DOT__data_mem__DOT__ram[addr >> 2];
  uint16_t offset = addr & 0x3;
  uint8_t byte = (word >> (offset * 8)) & 0xff;

  return byte;
}

void RiscVTester::write_byte(uint32_t addr, uint8_t value) {
  uint32_t word = top->rootp->test_top__DOT__data_mem__DOT__ram[addr >> 2];
  uint16_t offset = addr & 0x3;
  uint32_t value32 = value;

  word = word & ~(0xff << (offset * 8));
  word = word | (value32 << (offset * 8));

  top->rootp->test_top__DOT__data_mem__DOT__ram[addr >> 2] = word;
  evaluate();
}

void RiscVTester::clear_ram() {
  for (int i = 0; i < 32; i++) {
    top->rootp->test_top__DOT__data_mem__DOT__ram[i] = 0;
  }
  evaluate();
}

// pc
void RiscVTester::set_pc(uint32_t value) {
  top->rootp->test_top__DOT__core__DOT__KD = value;
  evaluate();
}

uint32_t RiscVTester::get_pc() {
  return top->rootp->test_top__DOT__core__DOT__KD;
}

// illegal_instruction
bool RiscVTester::get_illegal_instruction_bit() {
  return top->rootp->test_top__DOT__core__DOT__ziZG3f3w85eBr;
}
