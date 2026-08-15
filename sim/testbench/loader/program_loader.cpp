#include "program_loader.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sys/types.h>

void ProgramLoader::load_binary(uint32_t base_addr,
                                const std::string &filename) {
  std::string filepath = "../tests/bin_tests/" + filename;

  std::ifstream file(filepath, std::ios::binary | std::ios::ate);
  if (!file) {
    std::cerr << "ERROR: cannot open file: " << filename << std::endl;
    return;
  }

  size_t size = file.tellg();
  size_t word_count = size / 4;

  if (size % 4 != 0) {
    std::cerr << "WARNING: file size (" << size
              << " bytes) is not a multiple of 4: " << filename << std::endl;

    size -= size % 4;
    word_count = size / 4;

    std::cerr << "INFO: will read only first " << size << " bytes" << std::endl;
  }

  if ((size + base_addr) > INSTR_MEM_SIZE_BYTES) {
    std::cerr << "WARNING: file " << filename << " contains " << word_count
              << " instructions (ROM capasity is " << INSTR_MEM_SIZE_WORDS
              << ")" << std::endl;

    size = INSTR_MEM_SIZE_BYTES - base_addr;
    word_count = INSTR_MEM_SIZE_WORDS - (base_addr >> 2);

    std::cerr << "INFO: will read only first " << word_count << " instructions"
              << std::endl;
  }

  file.seekg(0);

  std::vector<uint32_t> instructions(word_count);
  file.read(reinterpret_cast<char *>(instructions.data()), word_count * 4);

  for (int i = 0; i < word_count; i++) {
    uint32_t addr = base_addr + 4 * i;
    tester.write_instruction(addr, instructions[i]);
  }
}
