/**
 *  \file       test_ssp.c
 *  \brief      Unit test for ssp module (only for learning test).
 */

/* -------------------------- Development history -------------------------- */
/* -------------------------------- Authors -------------------------------- */
/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unity_fixture.h"
#include "ssp.h"
#include "tree_actions.h"
#include "Mocktree_actions.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(ssp);

/* ---------------------------- Local variables ---------------------------- */
SSP_DCLR_NORMAL_NODE root, node_no, node_ok;
SSP_DCLR_TRN_NODE node_trn;

SSP_CREATE_NORMAL_NODE(root);
SSP_CREATE_BR_TABLE(root)
SSPBR("ok",     NULL,       &node_ok),
SSPBR("no",     NULL,       &node_no),
SSP_END_BR_TABLE

SSP_CREATE_NORMAL_NODE(node_ok);
SSP_CREATE_BR_TABLE(node_ok)
SSPBR("frm",    pattFrm,    &node_trn),
SSPBR("error",  NULL,       NULL),
SSP_END_BR_TABLE

SSP_CREATE_TRN_NODE(node_trn, collect);
SSP_CREATE_BR_TABLE(node_trn)
SSPBR("ok",     pattOk,     &root),
SSPBR("+",      NULL,       &root),
SSP_END_BR_TABLE

SSP_CREATE_NORMAL_NODE(node_no);
SSP_CREATE_BR_TABLE(node_no)
SSPBR("+",      NULL,       &root),
SSPBR("-",      pattFrm,    &node_trn),
SSP_END_BR_TABLE

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static SSPResult
parseAndCheck(const char *str, int mode, SSPResult expectedResult)
{
    SSPResult result;
    const char *p;
    int i;

    for (i = strlen(str), p = str; i > 0; --i, ++p)
    {
        result = ssp_doSearch(*p);
        if (mode == 1)
        {
            TEST_ASSERT_EQUAL(expectedResult, result);
        }
    }
    return result;
}

static SSPResult
parseString(const char *str)
{
    return parseAndCheck(str, 0, 0);
}

static SSPResult
parseStringInTransparentNode(const char *str)
{
    return parseAndCheck(str, 1, SSP_UNMATCH);
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(ssp)
{
    ssp_init(&root);
    Mocktree_actions_Init();
}

TEST_TEAR_DOWN(ssp)
{
    Mocktree_actions_Verify();
    Mocktree_actions_Destroy();
}

TEST(ssp, OutOfTree)
{
    SSPResult result;

    result = ssp_doSearch('\r');
    TEST_ASSERT_EQUAL(SSP_UNMATCH, result);
}

TEST(ssp, StartSearch)
{
    SSPResult result;

    result = ssp_doSearch('n');
    TEST_ASSERT_EQUAL(SSP_INIT_SEARCH, result);
}

TEST(ssp, FoundPattern)
{
    SSPResult result;

    result = ssp_doSearch('n');
    result = ssp_doSearch('o');
    TEST_ASSERT_EQUAL(SSP_MATCH, result);
}

TEST(ssp, FoundLongPattern)
{
    SSPResult result;

    result = parseString("oker");
    TEST_ASSERT_EQUAL(SSP_SEARCH_CONTINUES, result);
}

TEST(ssp, RepeatsCharInPattern)
{
    SSPResult result;

    result = parseString("oooo");
    TEST_ASSERT_EQUAL(SSP_DUPLICATED_CHAR, result);
}

TEST(ssp, BreakSearchPattern)
{
    SSPResult result;

    result = parseString("ol");
    TEST_ASSERT_EQUAL(SSP_UNMATCH, result);
}

TEST(ssp, OnFoundPatternCallsAction)
{
    SSPResult result;

    pattFrm_Expect(3);
    result = parseString("okfrm");
    TEST_ASSERT_EQUAL(SSP_MATCH, result);
}

TEST(ssp, CallsActionInTransparentNode)
{
    SSPResult result;

    pattFrm_Expect(3);
    collect_Expect('0');
    collect_Expect('1');

    result = parseString("okfrm");
    TEST_ASSERT_EQUAL(SSP_MATCH, result);

    result = parseStringInTransparentNode("01");
    TEST_ASSERT_EQUAL(SSP_UNMATCH, result);
}

TEST(ssp, FoundPatternInTransparentNode)
{
    SSPResult result;

    pattFrm_Expect(3);
    collect_Expect('0');
    collect_Expect('1');
    collect_Expect('o');
    collect_Expect('k');
    pattOk_Expect(2);

    result = parseString("okfrm");
    result = parseStringInTransparentNode("01");
    result = parseString("ok");
    TEST_ASSERT_EQUAL(SSP_MATCH, result);
}

TEST(ssp, TravelingDifferentNodeTypes)
{
    SSPResult result;

    pattFrm_Expect(1);
    collect_Expect('a');
    collect_Expect('b');
    collect_Expect('c');
    collect_Expect('+');
    pattFrm_Expect(3);
    collect_Expect('a');
    collect_Expect('b');
    collect_Expect('c');
    collect_Expect('o');
    collect_Expect('k');
    pattOk_Expect(2);

    result = parseString("\r\nno-abc+okfrmabcokno");
    TEST_ASSERT_EQUAL(SSP_MATCH, result);
}

/* ------------------------------ End of file ------------------------------ */
