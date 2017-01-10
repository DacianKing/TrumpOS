gdt_start: ; don't remove the labels, they're needed to compute sizes and jumps
    ; the GDT starts with a null 8-byte
    dd 0x0 ; 4 byte
    dd 0x0 ; 4 byte

; GDT for code segment. base = 0x00000000, length = 0xfffff
gdt_code:
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

; GDT for data segment. base and length identical to code segment
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

 usergdt_code:
  dw 0xffff    ; segment length, bits 0-15
  dw 0x0       ; segment base, bits 0-15
  db 0x0       ; segment base, bits 16-23
  db 11111010b ; flags (8 bits)
  db 11001111b ; flags (4 bits) + segment length, bits 16-19
  db 0x0       ; segment base, bits 24-31

  usergdt_data:
   dw 0xffff    ; segment length, bits 0-15
   dw 0x0       ; segment base, bits 0-15
   db 0x0       ; segment base, bits 16-23
   db 11110010b ; flags (8 bits)
   db 11001111b ; flags (4 bits) + segment length, bits 16-19
   db 0x0       ; segment base, bits 24-31


gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit), always one less of its true size
    dd gdt_start ; address (32 bit)

; define some constants for later use
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
USERCODE_SEG equ usergdt_code - gdt_start
USERDATA_SEG equ usergdt_data - gdt_start
