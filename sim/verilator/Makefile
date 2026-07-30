BUILD_DIR   := ../../build
OBJ_DIR     := $(BUILD_DIR)/obj_dir
RTL_DIR     := ../../rtl
TESTBENCH_DIR := ../testbench
TESTS_WITH_API_DIR := $(TESTBENCH_DIR)/tests

VERILATOR := verilator
CXX := g++

VERILATOR_FLAGS := --cc --top-module test_top \
                   -Wno-MODDUP -Wno-MULTITOP -Wno-IMPLICIT -Wno-WIDTHEXPAND -Wno-WIDTHTRUNC \
                   -Wno-CASEINCOMPLETE -Wno-COMBDLY -Wno-UNOPTFLAT \
                   --no-timing --build

CXXFLAGS := -I$(OBJ_DIR) \
            -I/usr/share/verilator/include \
            -I/usr/share/verilator/include/vltstd \
            -DVL_TIME_MULTIPLIER=1 \
            -std=c++17 \
            -O2

LDFLAGS := -lpthread

VERILOG_SRC := $(wildcard $(RTL_DIR)/*.sv) test_top.sv
TESTS_WITH_API_SRC := $(wildcard $(TESTS_WITH_API_DIR)/*.cpp)

MODEL_LIB := $(OBJ_DIR)/Vtest_top__ALL.a
TEST_WITH_API_EXE := $(BUILD_DIR)/test

all: $(TEST_WITH_API_EXE)

$(MODEL_LIB): $(VERILOG_SRC)
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(VERILATOR) $(VERILATOR_FLAGS) $(abspath $(VERILOG_SRC))

$(TEST_WITH_API_EXE): $(TESTS_WITH_API_SRC) $(MODEL_LIB)
	$(CXX) $(CXXFLAGS) $(TESTS_WITH_API_SRC) \
		$(MODEL_LIB) \
		/usr/share/verilator/include/verilated.cpp \
		/usr/share/verilator/include/verilated_threads.cpp \
		$(LDFLAGS) \
		-o $@

run: $(TEST_WITH_API_EXE)
	cd $(BUILD_DIR) && ./test

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
