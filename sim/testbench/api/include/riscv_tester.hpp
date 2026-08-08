#include "Vtest_top.h"
#include <cstdint>
#include <verilated.h>

class RiscVTester {
private:
  Vtest_top *top;

public:
  RiscVTester() { top = new Vtest_top; }
  ~RiscVTester() {
    top->final();
    delete top;
  }

  // utils
  void system_reset();
  void evaluate();

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

  // pc
  void set_pc(uint32_t value);
  uint32_t get_pc();

  // illegal_instruction
  bool get_illegal_instruction_bit();
};
