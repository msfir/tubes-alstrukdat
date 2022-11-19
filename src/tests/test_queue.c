#include <assert.h>

#include "adt.h"
#include "adt/queue/queue.h"

int main() {
    printf("--- Driver Test PriorityQueue ---");
    printf("\n");
    printf("\n");

    Queue q;
    CreateQueue(&q);

    assert(isEmptyQueue(q));

    enqueue(&q, StringFrom("Hello, World"));
    displayQueue(q);

    assert(queueLength(q) == 1);
    assert(is_string_equal(HEAD(q), StringFrom("Hello, World")));

    String val;

    dequeue(&q, &val);

    printf("%s\n", STR_VALUE(val));

    assert(isEmptyQueue(q));

    printf("\n");
    printf("All tests passed.\n");
    printf("\n");
    printf("--- Driver Test PriorityQueue ---");
    printf("\n");
    printf("\n");
    return 0;
}
