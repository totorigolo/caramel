/*
 * Multi-line comment.
 */

#include <stdio.h>
#include <stdint.h>


extern int32_t notes[];

int32_t main(int32_t, char argv[]) {
    int8_t tab1[5];
    int8_t tab2[] = {1, 2, 3};
    int8_t tab3[2] = {1, 2, 3, 4, 5};
    int32_t notes[] = {
            12,
            18,
            7,
            12,
            6,
            10,
            19,
            9,
    };
    return 0;
}