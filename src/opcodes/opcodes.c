/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-ftrace-amoz.pay
** File description:
** TODO: add description
*/

#include "opcodes.h"
#include <sys/ptrace.h>

void manage_opcode(long opcode, const pid_t pid, user_regs regs)
{
    for (size_t i = 0; i < LEN(OPCODES); i++) {
        if (OPCODES[i].value == (opcode & OPCODES[i].mask)) {
            OPCODES[i].func(regs, pid);
        }
    }
}
