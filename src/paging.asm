global paging_init

section .bss
align 4096
page_directory:
    resb 4096
page_table:
    resb 4096

section .text

paging_init:
    ; map first 1MB with identity mapping
    mov eax, 0
    mov ebx, 0
.loop_identity_map:
    mov dword [page_table + ebx], eax
    or dword [page_table + ebx], 3   ; set present bit and read/write bit
    add eax, 4096
    add ebx, 4
    cmp ebx, 4096
    jl .loop_identity_map

    ; map higher half kernel
    mov eax, 0xC0100000   ; map physical address 0x100000 to virtual address 0xC0100000
    mov ebx, 0x100000
.loop_higher_half:
    mov dword [page_table + ebx], eax
    or dword [page_table + ebx], 3   ; set present bit and read/write bit
    add eax, 4096
    add ebx, 4
    cmp ebx, 0x200000
    jl .loop_higher_half

    ; create page directory entry for page table
    mov eax, page_table
    mov ebx, 0xC0000000 | 3   ; set present bit, read/write bit, and user/supervisor bit
    mov dword [page_directory + 768*4], ebx
    or dword [page_directory + 768*4], eax

    ; set up page directory
    mov ebx, page_directory
    mov eax, ebx
    or eax, 3   ; set present bit and read/write bit
    mov cr3, eax

    ; enable paging
    mov eax, cr0
    or eax, 0x80000000   ; set the paging bit in CR0
    mov cr0, eax

    ret
