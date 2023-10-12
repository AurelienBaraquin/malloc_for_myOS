section .text
    global my_memcpy

my_memcpy:
    ; Vérifier si size (rdx) est 0
    test rdx, rdx
    jz .end_memcpy

    ; Initialiser les compteurs
    xor rcx, rcx  ; rcx sera notre compteur i

.loop_memcpy:
    ; Charger un octet de src à l'adresse (rsi + rcx)
    mov al, byte [rsi + rcx]

    ; Stocker cet octet dans dest à l'adresse (rdi + rcx)
    mov byte [rdi + rcx], al

    ; Incrémenter le compteur
    inc rcx

    ; Vérifier si nous avons atteint size
    cmp rcx, rdx
    jl .loop_memcpy

.end_memcpy:
    ret
