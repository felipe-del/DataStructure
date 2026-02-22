#include "../test/array_stack_test.hpp"
#include "../test/circular_linked_list_test.hpp"
#include "../test/circular_queue_test.hpp"
#include "../test/doubly_linked_list_test.hpp"
#include "../test/dynamic_array_test.hpp"
#include "../test/linked_stack_test.hpp"
#include "../test/MinStack.hpp"
#include "../test/queue_test.hpp"
#include "../test/singly_linked_list_test.hpp"
#include "../test/static_array_test.hpp"

int main() {
    testStaticArray();
    testDynamicArray();
    testSinglyLinkedList();
    testDoublyLinkedList();
    testCircularLinkedList();
    testArrayStack();
    testLinkedStack();
    testMinStack();
    testQueue();
    testCircularQueue();
    return 0;
}
