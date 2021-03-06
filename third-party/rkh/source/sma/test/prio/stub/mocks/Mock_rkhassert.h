/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_RKHASSERT_H
#define _MOCK_RKHASSERT_H

#include "rkhassert.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mock_rkhassert_Init(void);
void Mock_rkhassert_Destroy(void);
void Mock_rkhassert_Verify(void);




#define rkh_assert_Ignore() rkh_assert_CMockIgnore()
void rkh_assert_CMockIgnore(void);
#define rkh_assert_Expect(file, line) rkh_assert_CMockExpect(__LINE__, file, line)
void rkh_assert_CMockExpect(UNITY_LINE_TYPE cmock_line, const char* const file, int line);
typedef void (* CMOCK_rkh_assert_CALLBACK)(const char* const file, int line, int cmock_num_calls);
void rkh_assert_StubWithCallback(CMOCK_rkh_assert_CALLBACK Callback);
#define rkh_assert_IgnoreArg_file() rkh_assert_CMockIgnoreArg_file(__LINE__)
void rkh_assert_CMockIgnoreArg_file(UNITY_LINE_TYPE cmock_line);
#define rkh_assert_IgnoreArg_line() rkh_assert_CMockIgnoreArg_line(__LINE__)
void rkh_assert_CMockIgnoreArg_line(UNITY_LINE_TYPE cmock_line);

#endif
