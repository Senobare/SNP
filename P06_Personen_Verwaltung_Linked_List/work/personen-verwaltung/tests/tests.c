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
#include "person.h"
#include "list.h"

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
    clear_list(); // Clear list before each test
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
    person_t p1 = { .name = "Anna", .first_name = "Meier", .age = 1990 };
    person_t p2 = { .name = "Anna", .first_name = "Meier", .age = 1990 };
    person_t p3 = { .name = "Anna", .first_name = "Müller", .age = 1990 };

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
    person_t p1 = { .name = "Muster", .first_name = "Max", .age = 1985 };
    person_t p2 = { .name = "Meier", .first_name = "Lisa", .age = 1992 };

    // act
    bool result1 = insert_person(&p1);
    bool result2 = insert_person(&p2);

    // assert
    CU_ASSERT_TRUE(result1);
    CU_ASSERT_TRUE(result2);
    
    // Verify list order (sorted by last name, then first name, then age)
    node_t *current = anchor.next;
    CU_ASSERT_PTR_NOT_EQUAL(current, &anchor);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Meier");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Lisa");
    
    current = current->next;
    CU_ASSERT_PTR_NOT_EQUAL(current, &anchor);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Muster");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Max");
    
    current = current->next;
    CU_ASSERT_PTR_EQUAL(current, &anchor); // Should be back to anchor
    // END-STUDENTS-TO-ADD-CODE
}

static void test_list_remove(void)
{
    // BEGIN-STUDENTS-TO-ADD-CODE
    // arrange
    person_t p1 = { .name = "Ziegler", .first_name = "Anna", .age = 1993 };
    person_t p2 = { .name = "Huber", .first_name = "Ben", .age = 1991 };
    
    // Clear any existing list entries
    clear_list();
    
    // Insert test data (order matters for verification)
    CU_ASSERT_TRUE(insert_person(&p1));
    CU_ASSERT_TRUE(insert_person(&p2));

    // act - remove the second person
    bool removed = remove_person(&p2);

    // assert
    CU_ASSERT_TRUE(removed);
    
    // Verify only Ziegler remains
    node_t *current = anchor.next;
    CU_ASSERT_PTR_NOT_EQUAL(current, &anchor);
    
    // Check the remaining person's details
    if (current != &anchor) {
        CU_ASSERT_STRING_EQUAL(current->content.name, "Ziegler");
        CU_ASSERT_STRING_EQUAL(current->content.first_name, "Anna");
        CU_ASSERT_EQUAL(current->content.age, 1993);
        
        // Verify it's the only remaining node
        CU_ASSERT_PTR_EQUAL(current->next, &anchor);
    }
    // END-STUDENTS-TO-ADD-CODE
}

static void test_list_clear(void)
{
    // BEGIN-STUDENTS-TO-ADD-CODE
    // arrange
    person_t p1 = { .name = "Arnold", .first_name = "Tim", .age = 1988 };
    person_t p2 = { .name = "Keller", .first_name = "Sara", .age = 1994 };
    insert_person(&p1);
    insert_person(&p2);

    // act
    clear_list();

    // assert
    CU_ASSERT_PTR_EQUAL(anchor.next, &anchor); // List should be empty
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