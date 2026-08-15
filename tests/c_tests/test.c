void main() {
  int a = 56;
  int b = 43;
  int result = a + b;

  asm volatile("mv a0, %0\n"
               "ecall"
               :
               : "r"(result)
               : "a0");
}
