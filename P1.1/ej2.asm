segment .data
mensaje_0 db "Error: División por 0", 0
segment .bss
__esp resd 1
_b1 resd 1
segment .text
global main
extern scan_int, scan_boolean
extern print_int, print_boolean, print_string, print_blank, print_endofline
main:
mov dword [__esp], esp
push dword _b1
call scan_boolean
add esp, 4
push dword _b1
pop dword ebx
mov dword eax, [ebx]
cmp eax, 0
jne no0
inc eax
jmp nofin0
no0: dec eax
nofin0: push dword eax
call print_boolean
call print_endofline
add esp, 4
push dword _b1
pop dword ebx
mov dword eax, [ebx]
cmp eax, 0
jne no1
inc eax
jmp nofin1
no1: dec eax
nofin1: push dword eax
pop dword eax
cmp eax, 0
jne no2
inc eax
jmp nofin2
no2: dec eax
nofin2: push dword eax
call print_boolean
call print_endofline
add esp, 4
jmp fin
div0: push dword mensaje_0
    call print_string
    add esp, 4
    mov dword esp, [__esp]
    jmp near fin
fin: ret