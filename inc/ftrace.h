/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#define _GNU_SOURCE
#include <errno.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/user.h>
#include <unistd.h>

#include "utils/macro.h"
#include "utils/error.h"

void main_ftrace(char *const *av);
pid_t setup_ptrace(char *const *av);
void print_syscall(const struct user_regs_struct *regs);
void manage_opcode(long opcode, pid_t pid,
    const struct user_regs_struct *regs);
