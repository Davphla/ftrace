/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-ftrace-amoz.pay
** File description:
** TODO: add description
*/

#include "opcodes.h"

void asm_ret(UNUSED user_regs regs, UNUSED const pid_t pid)
{
    node_t *cur;

    cur = SLIST_FIRST(g_head);
    if (cur) {
        printf("Leaving function func_%#lx@%s\n", cur->context, "a.out");
        remove_context();
    }
}
