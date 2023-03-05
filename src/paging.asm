; paging.asm - set up paging
; created 2023-03-05 @ chatGPT

[bits 32]

; page directory and table constants
align 4096
page_directory:
    times 1024 dw 0
page_tables:
    times 1024 dw 0

; enable paging
global enable_paging
enable_paging:
    ; set the protection flag (bit 0) and paging flag (bit 31) in cr0
    mov eax, cr0
    or eax, 0x80010000
    mov cr0, eax

    ; load the address of the page directory into cr3
    mov eax, page_directory
    mov cr3, eax

    ret
