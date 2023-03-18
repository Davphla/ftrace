/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-ftrace-amoz.pay
** File description:
** TODO: add description
*/

#pragma once

#include "ftrace.h"
#include "utils/macro.h"
#include <malloc.h>
#include <sys/queue.h>

typedef struct node_s {
    unsigned long context;
    SLIST_ENTRY(node_s) next;
} node_t;

SLIST_HEAD(head_s, node_s);

typedef const struct user_regs_struct *user_regs;

void asm_syscall(user_regs, pid_t pid);
void asm_call(user_regs, pid_t pid);
void asm_ret(user_regs, pid_t pid);

typedef struct modrm_s {
    int rm : 3;
    int reg : 3;
    int mod : 2;
} modrm_t;

static const struct opcodes_s {
    long value;
    int mask;
    void (*func)(user_regs, pid_t pid);
} OPCODES[] = {{0x050f, 0xFFFF, &asm_syscall}, {0x10FF, 0x38FF, &asm_call},
    {0xE8, 0xFF, &asm_call}, {0x9A, 0xFF, &asm_call},
    {0x18FF, 0x38FF, &asm_call}, {0xC3, 0xFF, &asm_ret}};

// {0xFF, 0xFF, &asm_call},
#pragma weak s_head
SINGLETON(struct head_s, {.slh_first = NULL}, head)

#define g_head s_head()

static inline void remove_context(void)
{
    node_t *first = SLIST_FIRST(g_head);

    if (first) {
        SLIST_REMOVE_HEAD(g_head, next);
        free(first);
    }
}

static inline void add_context(const unsigned long context)
{
    node_t *cur = malloc(sizeof(node_t));

    cur->context = context;
    SLIST_INSERT_HEAD(g_head, cur, next);
}

int manage_signal(int pid);
