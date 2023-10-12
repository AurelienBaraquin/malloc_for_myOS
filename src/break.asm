section .text
global program_break

program_break:
    mov rax, 12         ; syscall number for brk
    syscall
    cmp rax, -1         ; Vérifie si l'appel système a renvoyé -1 (erreur)
    jnz .success        ; Si ce n'est pas -1, passe à .success

    ; Gestion de l'erreur
    mov rdi, rax        ; Charge la valeur de retour (erreur) dans rdi
    call handle_error   ; Appelle la fonction de gestion d'erreur
    ret

.success:
    ret

handle_error:
    mov rax, 60         ; syscall number for exit
    xor rdi, rdi        ; Exit code 0 (ou un autre code d'erreur)
    syscall
    ret