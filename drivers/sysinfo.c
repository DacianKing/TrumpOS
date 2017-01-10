/*

void cpuid(unsigned int *eax, unsigned int *ebx,unsigned int *ecx, unsigned int *edx) //shamelessly taken from linux kernel
{
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}
*/
