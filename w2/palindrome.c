#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// ANSI colour codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

// -----------------------------------------------------------------------------
// Function Declaration
// -----------------------------------------------------------------------------
bool isPalindrome(char *str, int n);

// -----------------------------------------------------------------------------
// Test Suite Function Declarations
// -----------------------------------------------------------------------------
static void run_test(const char *test_name, bool condition);
static void print_test_suite_header(const char *suite_name);

// -----------------------------------------------------------------------------
// Test Case Declarations
// -----------------------------------------------------------------------------
static void test_empty_string(void);
static void test_single_char(void);
static void test_even_length_palindrome(void);
static void test_odd_length_palindrome(void);
static void test_non_palindrome(void);
static void test_case_sensitivity(void);

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_tests(void);

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main(void) {
    run_tests();
    return 0;
}

// -----------------------------------------------------------------------------
// Implementation of isPalindrome()
// Checks if the given string of length n is a palindrome (case sensitive)
// -----------------------------------------------------------------------------
bool isPalindrome(char *str, int n) {
    int i = 0, j = n - 1;
    while (i < j) {
        if (str[i] != str[j])
            return false;
        i++;
        j--;
    }
    return true;
}

// -----------------------------------------------------------------------------
// Test Suite Helper Functions
// -----------------------------------------------------------------------------
static void run_test(const char *test_name, bool condition) {
    if (condition) {
        printf("%sTest %s: PASSED%s\n", GREEN, test_name, RESET);
    } else {
        printf("%sTest %s: FAILED%s\n", RED, test_name, RESET);
    }
}

static void print_test_suite_header(const char *suite_name) {
    printf("\nTest Suite: %s\n", suite_name);
    printf("-----------------------\n");
}

// -----------------------------------------------------------------------------
// Test Cases for isPalindrome()
// -----------------------------------------------------------------------------

// Test 1: Empty string should be considered a palindrome.
static void test_empty_string(void) {
    print_test_suite_header("Empty String");
    // Passing 0 for the length of an empty string.
    run_test("Empty string is a palindrome", isPalindrome("", 0) == true);
}

// Test 2: A single character is always a palindrome.
static void test_single_char(void) {
    print_test_suite_header("Single Character");
    run_test("Single character 'a' is a palindrome", isPalindrome("a", 1) == true);
}

// Test 3: Even-length palindrome.
static void test_even_length_palindrome(void) {
    print_test_suite_header("Even Length Palindrome");
    char *s = "abba";
    run_test("\"abba\" is a palindrome", isPalindrome(s, strlen(s)) == true);
}

// Test 4: Odd-length palindrome.
static void test_odd_length_palindrome(void) {
    print_test_suite_header("Odd Length Palindrome");
    char *s = "racecar";
    run_test("\"racecar\" is a palindrome", isPalindrome(s, strlen(s)) == true);
}

// Test 5: A non-palindrome string.
static void test_non_palindrome(void) {
    print_test_suite_header("Non-Palindrome");
    char *s = "hello";
    run_test("\"hello\" is not a palindrome", isPalindrome(s, strlen(s)) == false);
}

// Test 6: Case sensitivity – 'Aba' is not a palindrome if case sensitive.
static void test_case_sensitivity(void) {
    print_test_suite_header("Case Sensitivity");
    char *s = "Aba";
    run_test("\"Aba\" is not a palindrome (case sensitive)", isPalindrome(s, strlen(s)) == false);
}

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_tests(void) {
    test_empty_string();
    test_single_char();
    test_even_length_palindrome();
    test_odd_length_palindrome();
    test_non_palindrome();
    test_case_sensitivity();
}
