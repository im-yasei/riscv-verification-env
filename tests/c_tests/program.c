void main() {
  asm volatile("li x5, 20\n"
               "addi x5, x5, 7\n"
               "sw x5, 0(x0)\n"
               "ecall");
}
