#include "Vtest_top.h"
#include <cstdint>
#include <verilated.h>

#define INSTR_MEM_SIZE_BYTES 512
#define INSTR_MEM_SIZE_WORDS 128

class RiscVTester {
private:
  Vtest_top *top;
  void evaluate();

public:
  RiscVTester() { top = new Vtest_top; }
  ~RiscVTester() {
    top->final();
    delete top;
  }

  // utils
  void system_reset();

  // ===FRONTDOOR API===
  void tick();

  void enable_rst();
  void disable_rst();

  void enable_irq_req_i();
  void disable_irq_req_i();

  bool get_irq_ret_o();

  // ===BACKDOOR API===
  // registers
  uint32_t read_register(int index);
  void write_register(int index, uint32_t value);
  void clear_registers();

  // memory
  uint32_t read_word(uint32_t addr);
  void write_word(uint32_t addr, uint32_t value);

  uint16_t read_hword(uint32_t addr);
  void write_hword(uint32_t addr, uint16_t value);

  uint8_t read_byte(uint32_t addr);
  void write_byte(uint32_t addr, uint8_t value);

  void clear_ram();

  // instrcution memory
  void write_instruction(uint32_t addr, uint32_t instruction);
  void clear_rom();

  // pc
  void set_pc(uint32_t value);
  uint32_t get_pc();

  // illegal_instruction
  bool get_illegal_instruction_bit();
};
