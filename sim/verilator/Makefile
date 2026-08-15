BUILD_DIR   := ../../build
OBJ_DIR     := $(BUILD_DIR)/obj_dir
RTL_DIR     := ../../rtl
TESTBENCH_DIR := ../testbench
TESTS_WITH_API_DIR := $(TESTBENCH_DIR)/tests
API_DIR := $(TESTBENCH_DIR)/api
LOADER_DIR := $(TESTBENCH_DIR)/loader
C_TESTS_DIR    := ../../tests/c_tests
ELF_TESTS_DIR  := ../../tests/elf_tests
BIN_TESTS_DIR  := ../../tests/bin_tests
ASM_TESTS_DIR  := ../../tests/asm_tests

C_TESTS_SRC    := $(wildcard $(C_TESTS_DIR)/*.c)
C_TESTS_ELF    := $(addprefix $(ELF_TESTS_DIR)/, $(notdir $(C_TESTS_SRC:.c=.elf)))
C_TESTS_BIN    := $(addprefix $(BIN_TESTS_DIR)/, $(notdir $(C_TESTS_SRC:.c=.bin)))
C_TESTS_ASM    := $(addprefix $(ASM_TESTS_DIR)/, $(notdir $(C_TESTS_SRC:.c=.s)))

VERILATOR := verilator
CXX := g++
RISCV_GCC := riscv64-elf-gcc
RISCV_OBJCOPY := riscv64-elf-objcopy


VERILATOR_FLAGS := --cc --top-module test_top \
                   -Wno-MODDUP -Wno-MULTITOP -Wno-IMPLICIT -Wno-WIDTHEXPAND -Wno-WIDTHTRUNC \
                   -Wno-CASEINCOMPLETE -Wno-COMBDLY -Wno-UNOPTFLAT -Wno-BLKANDNBLK\
                   --no-timing --build

CXXFLAGS := -I$(OBJ_DIR) \
						-I$(API_DIR)/include \
						-I$(LOADER_DIR)/include \
            -I/usr/share/verilator/include \
            -I/usr/share/verilator/include/vltstd \
            -DVL_TIME_MULTIPLIER=1 \
            -std=c++17 \
            -O2

RISCV_CFLAGS := -march=rv32i -mabi=ilp32 -static -nostdlib -O2

LDFLAGS := -lpthread

VERILOG_SRC := $(RTL_DIR)/memory_pkg.sv \
               $(RTL_DIR)/alu_opcodes_pkg.sv \
               $(RTL_DIR)/csr_pkg.sv \
               $(RTL_DIR)/decoder_pkg.sv \
               $(RTL_DIR)/peripheral_pkg.sv \
               $(filter-out %_pkg.sv, $(wildcard $(RTL_DIR)/*.sv)) \
               test_top.sv

API_SRC := $(API_DIR)/riscv_tester.cpp
LOADER_SRC := $(LOADER_DIR)/program_loader.cpp
TESTS_WITH_API_SRC := $(wildcard $(TESTS_WITH_API_DIR)/*.cpp)

ALL_SRC := $(API_SRC) $(TESTS_WITH_API_SRC) $(LOADER_SRC)

MODEL_LIB := $(OBJ_DIR)/Vtest_top__ALL.a
TEST_WITH_API_EXE := $(BUILD_DIR)/test

all: $(TEST_WITH_API_EXE) c-tests

$(MODEL_LIB): $(VERILOG_SRC)
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(VERILATOR) $(VERILATOR_FLAGS) $(abspath $(VERILOG_SRC))

$(TEST_WITH_API_EXE): $(ALL_SRC) $(MODEL_LIB)
	$(CXX) $(CXXFLAGS) $(ALL_SRC) \
		$(MODEL_LIB) \
		/usr/share/verilator/include/verilated.cpp \
		/usr/share/verilator/include/verilated_threads.cpp \
		$(LDFLAGS) \
		-o $@

c-tests: $(C_TESTS_BIN) $(C_TESTS_ELF) $(C_TESTS_ASM)

$(ELF_TESTS_DIR)/%.elf: $(C_TESTS_DIR)/%.c
	mkdir -p $(ELF_TESTS_DIR)
	$(RISCV_GCC) $(RISCV_CFLAGS) -o $@ $<

$(BIN_TESTS_DIR)/%.bin: $(ELF_TESTS_DIR)/%.elf
	mkdir -p $(BIN_TESTS_DIR)
	$(RISCV_OBJCOPY) -O binary $< $@

$(ASM_TESTS_DIR)/%.s: $(C_TESTS_DIR)/%.c
	mkdir -p $(ASM_TESTS_DIR)
	$(RISCV_GCC) -march=rv32i -mabi=ilp32 -S -O2 -o $@ $<

run: $(TEST_WITH_API_EXE)
	@cd $(BUILD_DIR) && ./test $(mask)

clean-tests:
	rm -rf $(ELF_TESTS_DIR) $(BIN_TESTS_DIR) $(ASM_TESTS_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean c-tests clean-tests
