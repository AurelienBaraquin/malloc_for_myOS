section .text
    global my_memset

my_memset:
    ; Vérifier si size (rdx) est 0
    test rdx, rdx
    jz .end_memset

    ; Initialiser les compteurs
    xor rcx, rcx  ; rcx sera notre compteur i

.loop_memset:
    ; Stocker la valeur (rsi) dans dest à l'adresse (rdi + rcx)
    mov byte [rdi + rcx], sil  ; sil est la partie basse de 8 bits de rsi

    ; Incrémenter le compteur
    inc rcx

    ; Vérifier si nous avons atteint size
    cmp rcx, rdx
    jl .loop_memset

.end_memset:
    ret
