segment .data
mensaje_0 db "Error: División por 0", 0
segment .bss
__esp resd 1
_x resd 1
_y resd 1
_z resd 1
_j resd 1
segment .text
global main
extern scan_int, scan_boolean
extern print_int, print_boolean, print_string, print_blank, print_endofline
main:
mov dword [__esp], esp
push dword _x
call scan_int
add esp, 4
push dword _z
call scan_int
add esp, 4
push dword _x
pop dword ebx
mov dword eax, [ebx]
neg eax
push dword eax
pop dword ebx
mov [_j], ebx
push dword _j
pop dword ebx
mov dword eax, [ebx]
push dword eax
call print_int
call print_endofline
add esp, 4
push dword _x
push dword _z
pop dword ebx
mov dword edx, [ebx]
pop dword ebx
mov dword eax, [ebx]
sub eax, edx
push dword eax
call print_int
call print_endofline
add esp, 4
push dword _x
push dword 2
pop dword ecx
pop dword ebx
mov dword eax, [ebx]
cmp ecx, 0
je div0
cdq
idiv ecx
push dword eax
pop dword ebx
mov [_y], ebx
push dword _y
pop dword ebx
mov dword eax, [ebx]
push dword eax
call print_int
call print_endofline
add esp, 4
push dword _x
push dword _y
pop dword ebx
mov dword edx, [ebx]
pop dword ebx
mov dword eax, [ebx]
imul edx
push dword eax
call print_int
call print_endofline
add esp, 4
jmp fin
div0: push dword mensaje_0
    call print_string
    add esp, 4
    mov dword esp, [__esp]
    jmp near fin
fin: ret