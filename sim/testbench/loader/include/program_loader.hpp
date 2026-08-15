#include "riscv_tester.hpp"
#include <cstdint>

class ProgramLoader {
private:
  RiscVTester &tester;

public:
  explicit ProgramLoader(RiscVTester &t) : tester(t) {}
  ~ProgramLoader() = default;

  void load_binary(uint32_t addr, const std::string &filepath);
};
