extern native_cpuid


native_cpuid:
  pushad
  xor eax,eax
  cpuid
  sub esp,12
  mov esp,edx
  mov esp,ecx
  mov esp,ebx
  popad
  ret
