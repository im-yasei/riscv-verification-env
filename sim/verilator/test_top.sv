module test_top (
    input  logic clk_i,
    input  logic rst_i,
    input  logic irq_req_i,
    output logic irq_ret_o
);

  logic [31:0] instr_addr;
  logic [31:0] instr;
  logic        core_stall;

  processor_core core (
      .clk_i       (clk_i),
      .rst_i       (rst_i),
      .stall_i     (core_stall),
      .instr_i     (instr),
      .mem_rd_i    (32'b0),
      .instr_addr_o(instr_addr),
      .mem_addr_o  (),
      .mem_size_o  (),
      .mem_req_o   (),
      .mem_we_o    (),
      .mem_wd_o    (),
      .irq_req_i   (irq_req_i),
      .irq_ret_o   (irq_ret_o)
  );

  instr_mem imem (
      .read_addr_i(instr_addr),
      .read_data_o(instr)
  );

endmodule
