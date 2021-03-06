/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCKTREE_ACTIONS_H
#define _MOCKTREE_ACTIONS_H

#include "tree_actions.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mocktree_actions_Init(void);
void Mocktree_actions_Destroy(void);
void Mocktree_actions_Verify(void);




#define none_Expect(pos) none_CMockExpect(__LINE__, pos)
void none_CMockExpect(UNITY_LINE_TYPE cmock_line, unsigned char pos);
#define pattFrm_Expect(pos) pattFrm_CMockExpect(__LINE__, pos)
void pattFrm_CMockExpect(UNITY_LINE_TYPE cmock_line, unsigned char pos);
#define pattOk_Expect(pos) pattOk_CMockExpect(__LINE__, pos)
void pattOk_CMockExpect(UNITY_LINE_TYPE cmock_line, unsigned char pos);
#define collect_Expect(c) collect_CMockExpect(__LINE__, c)
void collect_CMockExpect(UNITY_LINE_TYPE cmock_line, unsigned char c);

#endif
