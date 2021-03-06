/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "Mock_rkhfwk_dynevt.h"

static const char* CMockString_e = "e";
static const char* CMockString_esize = "esize";
static const char* CMockString_rkh_dynEvt_init = "rkh_dynEvt_init";
static const char* CMockString_rkh_fwk_ae = "rkh_fwk_ae";
static const char* CMockString_rkh_fwk_gc = "rkh_fwk_gc";
static const char* CMockString_rkh_fwk_registerEvtPool = "rkh_fwk_registerEvtPool";
static const char* CMockString_rkh_fwk_reserve = "rkh_fwk_reserve";
static const char* CMockString_sender = "sender";
static const char* CMockString_ssize = "ssize";
static const char* CMockString_sstart = "sstart";

typedef struct _CMOCK_rkh_dynEvt_init_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;

} CMOCK_rkh_dynEvt_init_CALL_INSTANCE;

typedef struct _CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  void* Expected_sstart;
  rui32_t Expected_ssize;
  RKH_ES_T Expected_esize;
  int IgnoreArg_sstart;
  int IgnoreArg_ssize;
  int IgnoreArg_esize;

} CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE;

typedef struct _CMOCK_rkh_fwk_ae_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  RKH_EVT_T* ReturnVal;
  RKH_ES_T Expected_esize;
  RKH_SIG_T Expected_e;
  void* Expected_sender;
  int IgnoreArg_esize;
  int IgnoreArg_e;
  int IgnoreArg_sender;

} CMOCK_rkh_fwk_ae_CALL_INSTANCE;

typedef struct _CMOCK_rkh_fwk_gc_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  RKH_EVT_T* Expected_e;
  void* Expected_sender;
  int IgnoreArg_e;
  int IgnoreArg_sender;

} CMOCK_rkh_fwk_gc_CALL_INSTANCE;

typedef struct _CMOCK_rkh_fwk_reserve_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  RKH_EVT_T* Expected_e;
  int IgnoreArg_e;

} CMOCK_rkh_fwk_reserve_CALL_INSTANCE;

static struct Mock_rkhfwk_dynevtInstance
{
  int rkh_dynEvt_init_IgnoreBool;
  CMOCK_rkh_dynEvt_init_CALLBACK rkh_dynEvt_init_CallbackFunctionPointer;
  int rkh_dynEvt_init_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE rkh_dynEvt_init_CallInstance;
  int rkh_fwk_registerEvtPool_IgnoreBool;
  CMOCK_rkh_fwk_registerEvtPool_CALLBACK rkh_fwk_registerEvtPool_CallbackFunctionPointer;
  int rkh_fwk_registerEvtPool_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE rkh_fwk_registerEvtPool_CallInstance;
  int rkh_fwk_ae_IgnoreBool;
  RKH_EVT_T* rkh_fwk_ae_FinalReturn;
  CMOCK_rkh_fwk_ae_CALLBACK rkh_fwk_ae_CallbackFunctionPointer;
  int rkh_fwk_ae_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE rkh_fwk_ae_CallInstance;
  int rkh_fwk_gc_IgnoreBool;
  CMOCK_rkh_fwk_gc_CALLBACK rkh_fwk_gc_CallbackFunctionPointer;
  int rkh_fwk_gc_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE rkh_fwk_gc_CallInstance;
  int rkh_fwk_reserve_IgnoreBool;
  CMOCK_rkh_fwk_reserve_CALLBACK rkh_fwk_reserve_CallbackFunctionPointer;
  int rkh_fwk_reserve_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE rkh_fwk_reserve_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void Mock_rkhfwk_dynevt_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.rkh_dynEvt_init_IgnoreBool)
    Mock.rkh_dynEvt_init_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_rkh_dynEvt_init);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_dynEvt_init_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.rkh_dynEvt_init_CallbackFunctionPointer != NULL)
    Mock.rkh_dynEvt_init_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.rkh_fwk_registerEvtPool_IgnoreBool)
    Mock.rkh_fwk_registerEvtPool_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_rkh_fwk_registerEvtPool);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_fwk_registerEvtPool_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.rkh_fwk_registerEvtPool_CallbackFunctionPointer != NULL)
    Mock.rkh_fwk_registerEvtPool_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.rkh_fwk_ae_IgnoreBool)
    Mock.rkh_fwk_ae_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_rkh_fwk_ae);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_fwk_ae_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.rkh_fwk_ae_CallbackFunctionPointer != NULL)
    Mock.rkh_fwk_ae_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.rkh_fwk_gc_IgnoreBool)
    Mock.rkh_fwk_gc_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_rkh_fwk_gc);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_fwk_gc_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.rkh_fwk_gc_CallbackFunctionPointer != NULL)
    Mock.rkh_fwk_gc_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.rkh_fwk_reserve_IgnoreBool)
    Mock.rkh_fwk_reserve_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_rkh_fwk_reserve);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.rkh_fwk_reserve_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.rkh_fwk_reserve_CallbackFunctionPointer != NULL)
    Mock.rkh_fwk_reserve_CallInstance = CMOCK_GUTS_NONE;
}

void Mock_rkhfwk_dynevt_Init(void)
{
  Mock_rkhfwk_dynevt_Destroy();
}

void Mock_rkhfwk_dynevt_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.rkh_dynEvt_init_CallbackFunctionPointer = NULL;
  Mock.rkh_dynEvt_init_CallbackCalls = 0;
  Mock.rkh_fwk_registerEvtPool_CallbackFunctionPointer = NULL;
  Mock.rkh_fwk_registerEvtPool_CallbackCalls = 0;
  Mock.rkh_fwk_ae_CallbackFunctionPointer = NULL;
  Mock.rkh_fwk_ae_CallbackCalls = 0;
  Mock.rkh_fwk_gc_CallbackFunctionPointer = NULL;
  Mock.rkh_fwk_gc_CallbackCalls = 0;
  Mock.rkh_fwk_reserve_CallbackFunctionPointer = NULL;
  Mock.rkh_fwk_reserve_CallbackCalls = 0;
}

void rkh_dynEvt_init(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_dynEvt_init_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_rkh_dynEvt_init);
  cmock_call_instance = (CMOCK_rkh_dynEvt_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_dynEvt_init_CallInstance);
  Mock.rkh_dynEvt_init_CallInstance = CMock_Guts_MemNext(Mock.rkh_dynEvt_init_CallInstance);
  if (Mock.rkh_dynEvt_init_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (Mock.rkh_dynEvt_init_CallbackFunctionPointer != NULL)
  {
    Mock.rkh_dynEvt_init_CallbackFunctionPointer(Mock.rkh_dynEvt_init_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void rkh_dynEvt_init_CMockIgnore(void)
{
  Mock.rkh_dynEvt_init_IgnoreBool = (int)1;
}

void rkh_dynEvt_init_CMockExpect(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_dynEvt_init_CALL_INSTANCE));
  CMOCK_rkh_dynEvt_init_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_dynEvt_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_dynEvt_init_CallInstance = CMock_Guts_MemChain(Mock.rkh_dynEvt_init_CallInstance, cmock_guts_index);
  Mock.rkh_dynEvt_init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  UNITY_CLR_DETAILS();
}

void rkh_dynEvt_init_StubWithCallback(CMOCK_rkh_dynEvt_init_CALLBACK Callback)
{
  Mock.rkh_dynEvt_init_IgnoreBool = (int)0;
  Mock.rkh_dynEvt_init_CallbackFunctionPointer = Callback;
}

void rkh_fwk_registerEvtPool(void* sstart, rui32_t ssize, RKH_ES_T esize)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_rkh_fwk_registerEvtPool);
  cmock_call_instance = (CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_fwk_registerEvtPool_CallInstance);
  Mock.rkh_fwk_registerEvtPool_CallInstance = CMock_Guts_MemNext(Mock.rkh_fwk_registerEvtPool_CallInstance);
  if (Mock.rkh_fwk_registerEvtPool_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (!cmock_call_instance->IgnoreArg_sstart)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_registerEvtPool,CMockString_sstart);
    UNITY_TEST_ASSERT_EQUAL_PTR(cmock_call_instance->Expected_sstart, sstart, cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_ssize)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_registerEvtPool,CMockString_ssize);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_ssize), (void*)(&ssize), sizeof(rui32_t), cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_esize)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_registerEvtPool,CMockString_esize);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_esize), (void*)(&esize), sizeof(RKH_ES_T), cmock_line, CMockStringMismatch);
  }
  if (Mock.rkh_fwk_registerEvtPool_CallbackFunctionPointer != NULL)
  {
    Mock.rkh_fwk_registerEvtPool_CallbackFunctionPointer(sstart, ssize, esize, Mock.rkh_fwk_registerEvtPool_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_rkh_fwk_registerEvtPool(CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE* cmock_call_instance, void* sstart, rui32_t ssize, RKH_ES_T esize)
{
  cmock_call_instance->Expected_sstart = sstart;
  cmock_call_instance->IgnoreArg_sstart = 0;
  memcpy(&cmock_call_instance->Expected_ssize, &ssize, sizeof(rui32_t));
  cmock_call_instance->IgnoreArg_ssize = 0;
  memcpy(&cmock_call_instance->Expected_esize, &esize, sizeof(RKH_ES_T));
  cmock_call_instance->IgnoreArg_esize = 0;
}

void rkh_fwk_registerEvtPool_CMockIgnore(void)
{
  Mock.rkh_fwk_registerEvtPool_IgnoreBool = (int)1;
}

void rkh_fwk_registerEvtPool_CMockExpect(UNITY_LINE_TYPE cmock_line, void* sstart, rui32_t ssize, RKH_ES_T esize)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE));
  CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_fwk_registerEvtPool_CallInstance = CMock_Guts_MemChain(Mock.rkh_fwk_registerEvtPool_CallInstance, cmock_guts_index);
  Mock.rkh_fwk_registerEvtPool_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_rkh_fwk_registerEvtPool(cmock_call_instance, sstart, ssize, esize);
  UNITY_CLR_DETAILS();
}

void rkh_fwk_registerEvtPool_StubWithCallback(CMOCK_rkh_fwk_registerEvtPool_CALLBACK Callback)
{
  Mock.rkh_fwk_registerEvtPool_IgnoreBool = (int)0;
  Mock.rkh_fwk_registerEvtPool_CallbackFunctionPointer = Callback;
}

void rkh_fwk_registerEvtPool_CMockIgnoreArg_sstart(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_registerEvtPool_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_sstart = 1;
}

void rkh_fwk_registerEvtPool_CMockIgnoreArg_ssize(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_registerEvtPool_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_ssize = 1;
}

void rkh_fwk_registerEvtPool_CMockIgnoreArg_esize(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_registerEvtPool_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_registerEvtPool_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_esize = 1;
}

RKH_EVT_T* rkh_fwk_ae(RKH_ES_T esize, RKH_SIG_T e, const void* const sender)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_fwk_ae_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_rkh_fwk_ae);
  cmock_call_instance = (CMOCK_rkh_fwk_ae_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_fwk_ae_CallInstance);
  Mock.rkh_fwk_ae_CallInstance = CMock_Guts_MemNext(Mock.rkh_fwk_ae_CallInstance);
  if (Mock.rkh_fwk_ae_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.rkh_fwk_ae_FinalReturn;
    Mock.rkh_fwk_ae_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (!cmock_call_instance->IgnoreArg_esize)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_ae,CMockString_esize);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_esize), (void*)(&esize), sizeof(RKH_ES_T), cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_e)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_ae,CMockString_e);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_e), (void*)(&e), sizeof(RKH_SIG_T), cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_sender)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_ae,CMockString_sender);
    UNITY_TEST_ASSERT_EQUAL_PTR(cmock_call_instance->Expected_sender, sender, cmock_line, CMockStringMismatch);
  }
  if (Mock.rkh_fwk_ae_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.rkh_fwk_ae_CallbackFunctionPointer(esize, e, sender, Mock.rkh_fwk_ae_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_rkh_fwk_ae(CMOCK_rkh_fwk_ae_CALL_INSTANCE* cmock_call_instance, RKH_ES_T esize, RKH_SIG_T e, const void* const sender)
{
  memcpy(&cmock_call_instance->Expected_esize, &esize, sizeof(RKH_ES_T));
  cmock_call_instance->IgnoreArg_esize = 0;
  memcpy(&cmock_call_instance->Expected_e, &e, sizeof(RKH_SIG_T));
  cmock_call_instance->IgnoreArg_e = 0;
  cmock_call_instance->Expected_sender = (void*)sender;
  cmock_call_instance->IgnoreArg_sender = 0;
}

void rkh_fwk_ae_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RKH_EVT_T* cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_fwk_ae_CALL_INSTANCE));
  CMOCK_rkh_fwk_ae_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_ae_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_fwk_ae_CallInstance = CMock_Guts_MemChain(Mock.rkh_fwk_ae_CallInstance, cmock_guts_index);
  Mock.rkh_fwk_ae_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.rkh_fwk_ae_IgnoreBool = (int)1;
}

void rkh_fwk_ae_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, RKH_ES_T esize, RKH_SIG_T e, const void* const sender, RKH_EVT_T* cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_fwk_ae_CALL_INSTANCE));
  CMOCK_rkh_fwk_ae_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_ae_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_fwk_ae_CallInstance = CMock_Guts_MemChain(Mock.rkh_fwk_ae_CallInstance, cmock_guts_index);
  Mock.rkh_fwk_ae_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_rkh_fwk_ae(cmock_call_instance, esize, e, sender);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void rkh_fwk_ae_StubWithCallback(CMOCK_rkh_fwk_ae_CALLBACK Callback)
{
  Mock.rkh_fwk_ae_IgnoreBool = (int)0;
  Mock.rkh_fwk_ae_CallbackFunctionPointer = Callback;
}

void rkh_fwk_ae_CMockIgnoreArg_esize(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_ae_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_ae_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_ae_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_esize = 1;
}

void rkh_fwk_ae_CMockIgnoreArg_e(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_ae_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_ae_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_ae_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_e = 1;
}

void rkh_fwk_ae_CMockIgnoreArg_sender(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_ae_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_ae_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_ae_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_sender = 1;
}

void rkh_fwk_gc(RKH_EVT_T* e, const void* const sender)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_fwk_gc_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_rkh_fwk_gc);
  cmock_call_instance = (CMOCK_rkh_fwk_gc_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_fwk_gc_CallInstance);
  Mock.rkh_fwk_gc_CallInstance = CMock_Guts_MemNext(Mock.rkh_fwk_gc_CallInstance);
  if (Mock.rkh_fwk_gc_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (!cmock_call_instance->IgnoreArg_e)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_gc,CMockString_e);
    UNITY_TEST_ASSERT_EQUAL_PTR(cmock_call_instance->Expected_e, e, cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_sender)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_gc,CMockString_sender);
    UNITY_TEST_ASSERT_EQUAL_PTR(cmock_call_instance->Expected_sender, sender, cmock_line, CMockStringMismatch);
  }
  if (Mock.rkh_fwk_gc_CallbackFunctionPointer != NULL)
  {
    Mock.rkh_fwk_gc_CallbackFunctionPointer(e, sender, Mock.rkh_fwk_gc_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_rkh_fwk_gc(CMOCK_rkh_fwk_gc_CALL_INSTANCE* cmock_call_instance, RKH_EVT_T* e, const void* const sender)
{
  cmock_call_instance->Expected_e = e;
  cmock_call_instance->IgnoreArg_e = 0;
  cmock_call_instance->Expected_sender = (void*)sender;
  cmock_call_instance->IgnoreArg_sender = 0;
}

void rkh_fwk_gc_CMockIgnore(void)
{
  Mock.rkh_fwk_gc_IgnoreBool = (int)1;
}

void rkh_fwk_gc_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_EVT_T* e, const void* const sender)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_fwk_gc_CALL_INSTANCE));
  CMOCK_rkh_fwk_gc_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_gc_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_fwk_gc_CallInstance = CMock_Guts_MemChain(Mock.rkh_fwk_gc_CallInstance, cmock_guts_index);
  Mock.rkh_fwk_gc_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_rkh_fwk_gc(cmock_call_instance, e, sender);
  UNITY_CLR_DETAILS();
}

void rkh_fwk_gc_StubWithCallback(CMOCK_rkh_fwk_gc_CALLBACK Callback)
{
  Mock.rkh_fwk_gc_IgnoreBool = (int)0;
  Mock.rkh_fwk_gc_CallbackFunctionPointer = Callback;
}

void rkh_fwk_gc_CMockIgnoreArg_e(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_gc_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_gc_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_gc_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_e = 1;
}

void rkh_fwk_gc_CMockIgnoreArg_sender(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_gc_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_gc_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_gc_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_sender = 1;
}

void rkh_fwk_reserve(RKH_EVT_T* e)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_rkh_fwk_reserve_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_rkh_fwk_reserve);
  cmock_call_instance = (CMOCK_rkh_fwk_reserve_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.rkh_fwk_reserve_CallInstance);
  Mock.rkh_fwk_reserve_CallInstance = CMock_Guts_MemNext(Mock.rkh_fwk_reserve_CallInstance);
  if (Mock.rkh_fwk_reserve_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (!cmock_call_instance->IgnoreArg_e)
  {
    UNITY_SET_DETAILS(CMockString_rkh_fwk_reserve,CMockString_e);
    UNITY_TEST_ASSERT_EQUAL_PTR(cmock_call_instance->Expected_e, e, cmock_line, CMockStringMismatch);
  }
  if (Mock.rkh_fwk_reserve_CallbackFunctionPointer != NULL)
  {
    Mock.rkh_fwk_reserve_CallbackFunctionPointer(e, Mock.rkh_fwk_reserve_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_rkh_fwk_reserve(CMOCK_rkh_fwk_reserve_CALL_INSTANCE* cmock_call_instance, RKH_EVT_T* e)
{
  cmock_call_instance->Expected_e = e;
  cmock_call_instance->IgnoreArg_e = 0;
}

void rkh_fwk_reserve_CMockIgnore(void)
{
  Mock.rkh_fwk_reserve_IgnoreBool = (int)1;
}

void rkh_fwk_reserve_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_EVT_T* e)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_rkh_fwk_reserve_CALL_INSTANCE));
  CMOCK_rkh_fwk_reserve_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_reserve_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.rkh_fwk_reserve_CallInstance = CMock_Guts_MemChain(Mock.rkh_fwk_reserve_CallInstance, cmock_guts_index);
  Mock.rkh_fwk_reserve_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_rkh_fwk_reserve(cmock_call_instance, e);
  UNITY_CLR_DETAILS();
}

void rkh_fwk_reserve_StubWithCallback(CMOCK_rkh_fwk_reserve_CALLBACK Callback)
{
  Mock.rkh_fwk_reserve_IgnoreBool = (int)0;
  Mock.rkh_fwk_reserve_CallbackFunctionPointer = Callback;
}

void rkh_fwk_reserve_CMockIgnoreArg_e(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_rkh_fwk_reserve_CALL_INSTANCE* cmock_call_instance = (CMOCK_rkh_fwk_reserve_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.rkh_fwk_reserve_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_e = 1;
}

