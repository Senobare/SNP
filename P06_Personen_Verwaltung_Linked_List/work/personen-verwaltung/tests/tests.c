/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Test suite for the given package.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <assert.h>
#include <CUnit/Basic.h>
#include "test_utils.h"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

/// @brief alias for EXIT_SUCCESS
#define OK   EXIT_SUCCESS
/// @brief alias for EXIT_FAILURE
#define FAIL EXIT_FAILURE

/// @brief The name of the STDOUT text file.
#define OUTFILE "stdout.txt"
/// @brief The name of the STDERR text file.
#define ERRFILE "stderr.txt"

#define TRACE_INDENT "\n                " ///< allow for better stdout formatting in case of error

// setup & cleanup
static int setup(void)
{
    remove_file_if_exists(OUTFILE);
    remove_file_if_exists(ERRFILE);
    return 0; // success
}

static int teardown(void)
{
    // Do nothing.
    // Especially: do not remove result files - they are removed in int setup(void) *before* running a test.
    return 0; // success
}

// tests
static void test_person_compare(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	// arrange
	person_t p1 = { .first_name = "Anna", .last_name = "Meier", .birth_year = 1990 };
	person_t p2 = { .first_name = "Anna", .last_name = "Meier", .birth_year = 1990 };
	person_t p3 = { .first_name = "Anna", .last_name = "Müller", .birth_year = 1990 };

	// act
	// assert
	CU_ASSERT(person_compare(&p1, &p2) == 0);
	CU_ASSERT(person_compare(&p1, &p3) < 0);
	CU_ASSERT(person_compare(&p3, &p1) > 0);
	// END-STUDENTS-TO-ADD-CODE
}

static void test_list_insert(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	// arrange
	list_t list;
	list_init(&list);
	person_t p1 = { .first_name = "Max", .last_name = "Muster", .birth_year = 1985 };
	person_t p2 = { .first_name = "Lisa", .last_name = "Meier", .birth_year = 1992 };

	// act
	list_insert(&list, &p1);
	list_insert(&list, &p2);

	// assert
	CU_ASSERT_PTR_NOT_NULL(list.head);
	CU_ASSERT_STRING_EQUAL(list.head->person.last_name, "Meier");
	CU_ASSERT_PTR_NOT_NULL(list.head->next);
	CU_ASSERT_STRING_EQUAL(list.head->next->person.last_name, "Muster");
	CU_ASSERT_PTR_NULL(list.head->next->next);
	// END-STUDENTS-TO-ADD-CODE
}

static void test_list_remove(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	// arrange
	list_t list;
	list_init(&list);
	person_t p1 = { .first_name = "Anna", .last_name = "Ziegler", .birth_year = 1993 };
	person_t p2 = { .first_name = "Ben", .last_name = "Huber", .birth_year = 1991 };
	list_insert(&list, &p1);
	list_insert(&list, &p2); // Huber, Ziegler

	// act
	int removed = list_remove(&list, "Huber");

	// assert
	CU_ASSERT_EQUAL(removed, 1);
	CU_ASSERT_PTR_NOT_NULL(list.head);
	CU_ASSERT_STRING_EQUAL(list.head->person.last_name, "Ziegler");
	CU_ASSERT_PTR_NULL(list.head->next);
	// END-STUDENTS-TO-ADD-CODE
}

static void test_list_clear(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	// arrange
	list_t list;
	list_init(&list);
	person_t p1 = { .first_name = "Tim", .last_name = "Arnold", .birth_year = 1988 };
	person_t p2 = { .first_name = "Sara", .last_name = "Keller", .birth_year = 1994 };
	list_insert(&list, &p1);
	list_insert(&list, &p2);

	// act
	list_clear(&list);

	// assert
	CU_ASSERT_PTR_NULL(list.head);
	// END-STUDENTS-TO-ADD-CODE
}

/**
 * @brief Registers and runs the tests.
 * @returns success (0) or one of the CU_ErrorCode (>0)
 */
int main(void)
{
    // setup, run, teardown
    TestMainBasic("lab test", setup, teardown
                  , test_person_compare
                  , test_list_insert
                  , test_list_remove
                  , test_list_clear
                  );
}
