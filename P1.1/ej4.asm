segment .data
mensaje_0 db "Error: División por 0", 0
segment .bss
__esp resd 1
_b1 resd 1
_x resd 1
segment .text
global main
extern scan_int, scan_boolean
extern print_int, print_boolean, print_string, print_blank, print_endofline
main:
mov dword [__esp], esp
push dword _b1
call scan_boolean
add esp, 4
push dword _x
call scan_int
add esp, 4
push dword _x
push dword 3
pop dword edx
pop dword ebx
mov dword eax, [ebx]
cmp eax, edx
jle op0
push dword 1
jmp fin0
op0: push dword 0
fin0:
call print_boolean
call print_endofline
add esp, 4
push dword _x
push dword 3
pop dword edx
pop dword ebx
mov dword eax, [ebx]
cmp eax, edx
jl op1
push dword 1
jmp fin1
op1: push dword 0
fin1:
call print_boolean
call print_endofline
add esp, 4
push dword _x
push dword 3
pop dword edx
pop dword ebx
mov dword eax, [ebx]
cmp eax, edx
jge op2
push dword 1
jmp fin2
op2: push dword 0
fin2:
call print_boolean
call print_endofline
add esp, 4
push dword _x
push dword 3
pop dword edx
pop dword ebx
mov dword eax, [ebx]
cmp eax, edx
jg op3
push dword 1
jmp fin3
op3: push dword 0
fin3:
call print_boolean
call print_endofline
add esp, 4
push dword _x
push dword 3
pop dword edx
pop dword ebx
mov dword eax, [ebx]
cmp eax, edx
jne op4
push dword 1
jmp fin4
op4: push dword 0
fin4:
call print_boolean
call print_endofline
add esp, 4
push dword _x
push dword 3
pop dword edx
pop dword ebx
mov dword eax, [ebx]
cmp eax, edx
je op5
push dword 1
jmp fin5
op5: push dword 0
fin5:
call print_boolean
call print_endofline
add esp, 4
push dword _b1
push dword 0
pop dword edx
pop dword ebx
mov dword eax, [ebx]
and eax, edx
push dword eax
call print_boolean
call print_endofline
add esp, 4
push dword _b1
push dword 1
pop dword edx
pop dword ebx
mov dword eax, [ebx]
or eax, edx
push dword eax
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