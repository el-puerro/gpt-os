; src/paging.asm
; created 2023-03-06 @ ChatGPT

global paging_init

section .text

paging_init:
	; set up page directory
	mov eax, 0x1000     ; allocate a page for the page directory
	mov cr3, eax        ; load the page directory address into CR3
	mov eax, 0x101000   ; set eax to point to the beginning of the page directory
	mov ebx, 0x103     ; set ebx to point to the beginning of the page table
	mov ecx, 1024      ; loop through all entries in the page directory
.loop_pd:
	mov edx, ebx        ; load the value at ebx into edx
	or edx, 3          ; set the present bit and read/write bit
	mov [eax], edx      ; store the value back into memory
	add eax, 4         ; advance to next entry in page directory
	add ebx, 4096      ; advance to next page table
	dec ecx            ; decrement loop counter
	jnz .loop_pd       ; loop if not done

	; set up page table
	mov eax, 0x103000   ; set eax to point to the beginning of the page table
	mov ebx, 0          ; clear ebx
	mov ecx, 1024       ; loop through all entries in the page table
.loop_pt:
	mov edx, ebx        ; load the value at ebx into edx
	or edx, 3          ; set the present bit and read/write bit
	mov [eax], edx      ; store the value back into memory
	add eax, 4          ; advance to next entry in page table
	add ebx, 4096       ; advance to next physical page
	dec ecx             ; decrement loop counter
	jnz .loop_pt        ; loop if not done

	; enable paging
	mov eax, cr0
	or eax, 0x80000000  ; set the paging bit in CR0
	mov cr0, eax

	ret
