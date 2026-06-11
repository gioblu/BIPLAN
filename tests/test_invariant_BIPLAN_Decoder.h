#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Include the vulnerable decoder */
#include "../src/BIPLAN_Decoder.h"

START_TEST(test_biplan_buffer_overflow_protection)
{
    /* Invariant: Buffer reads never exceed declared destination buffer size */
    
    /* Test payloads: craft BIPLAN encoded data with oversized string_length */
    const unsigned char *payloads[] = {
        /* Valid case: small string within bounds */
        (const unsigned char *)"\x01\x05hello",
        /* Boundary: string_length = buffer size */
        (const unsigned char *)"\x01\x10" "0123456789ABCDEF",
        /* Exploit: string_length = 2x buffer size (256 bytes requested, 128 available) */
        (const unsigned char *)"\x01\x00\x01" "X",
        /* Exploit: string_length = 10x buffer size */
        (const unsigned char *)"\x01\x00\x0A" "Y",
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);
    
    for (int i = 0; i < num_payloads; i++) {
        unsigned char dest[128];
        memset(dest, 0xAA, sizeof(dest));
        unsigned char canary[16];
        memset(canary, 0xBB, sizeof(canary));
        
        /* Attempt decode - should not write beyond dest buffer */
        int result = BIPLAN_Decode(payloads[i], 16, dest, sizeof(dest));
        
        /* Verify canary is untouched (no overflow past dest) */
        for (int j = 0; j < sizeof(canary); j++) {
            ck_assert_msg(canary[j] == 0xBB, 
                "Buffer overflow detected at payload %d: canary corrupted", i);
        }
        
        /* Verify dest buffer boundaries remain intact */
        ck_assert_msg(dest[sizeof(dest) - 1] == 0xAA || dest[sizeof(dest) - 1] == 0x00,
            "Payload %d: destination buffer boundary violated", i);
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_biplan_buffer_overflow_protection);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}