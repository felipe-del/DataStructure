#include "../test/doubly_linked_list_test.hpp"
#include "../test/dynamic_array_test.hpp"
#include "../test/singly_linked_list_test.hpp"
#include "../test/static_array_test.hpp"

int main() {
    testStaticArray();
    testDynamicArray();
    testSinglyLinkedList();
    testDoublyLinkedList();
    return 0;
}
