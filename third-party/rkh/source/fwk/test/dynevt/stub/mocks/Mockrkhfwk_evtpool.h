/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCKRKHFWK_EVTPOOL_H
#define _MOCKRKHFWK_EVTPOOL_H

#include "rkhfwk_evtpool.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mockrkhfwk_evtpool_Init(void);
void Mockrkhfwk_evtpool_Destroy(void);
void Mockrkhfwk_evtpool_Verify(void);




#define rkh_evtPool_init_Expect(me, stoStart, stoSize, evtSize) rkh_evtPool_init_CMockExpect(__LINE__, me, stoStart, stoSize, evtSize)
void rkh_evtPool_init_CMockExpect(UNITY_LINE_TYPE cmock_line, RKHEvtPool* me, void* stoStart, rui32_t stoSize, RKH_ES_T evtSize);
#define rkh_evtPool_get_esize_ExpectAndReturn(me, cmock_retval) rkh_evtPool_get_esize_CMockExpectAndReturn(__LINE__, me, cmock_retval)
void rkh_evtPool_get_esize_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, RKHEvtPool* const me, rui8_t cmock_to_return);
#define rkh_evtPool_get_ExpectAndReturn(me, evt, cmock_retval) rkh_evtPool_get_CMockExpectAndReturn(__LINE__, me, evt, cmock_retval)
void rkh_evtPool_get_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, RKHEvtPool* const me, RKH_EVT_T* evt, RKH_EVT_T* cmock_to_return);
#define rkh_evtPool_put_Expect(me, evt) rkh_evtPool_put_CMockExpect(__LINE__, me, evt)
void rkh_evtPool_put_CMockExpect(UNITY_LINE_TYPE cmock_line, RKHEvtPool* const me, RKH_EVT_T* evt);
#define rkh_evtPool_get_nused_ExpectAndReturn(me, cmock_retval) rkh_evtPool_get_nused_CMockExpectAndReturn(__LINE__, me, cmock_retval)
void rkh_evtPool_get_nused_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, RKHEvtPool* const me, rui8_t cmock_to_return);
#define rkh_evtPool_get_nmin_ExpectAndReturn(me, cmock_retval) rkh_evtPool_get_nmin_CMockExpectAndReturn(__LINE__, me, cmock_retval)
void rkh_evtPool_get_nmin_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, RKHEvtPool* const me, rui8_t cmock_to_return);
#define rkh_evtPool_get_nblock_Expect(me) rkh_evtPool_get_nblock_CMockExpect(__LINE__, me)
void rkh_evtPool_get_nblock_CMockExpect(UNITY_LINE_TYPE cmock_line, RKHEvtPool* const me);

#endif
