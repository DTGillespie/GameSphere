void delay(unsigned int count)
{
  while(count--) {
    __asm__ volatile("nop");
  }
}