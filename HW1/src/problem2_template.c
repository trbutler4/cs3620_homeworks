#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct elem {
    int value;
    struct elem *next;
    struct elem *prev;
} elem_t;

void print_list(elem_t *head) {
    elem_t *elem = head;
    while(elem != NULL) {
        printf("%d ", elem->value);
        elem = elem->next;
    }

    printf("\n");
}

void bubble_sort_copy_value(elem_t **head) {
    if (*head == NULL) return;

    // will need to tell if swaps happened
    int swap_flag;
    elem_t *current_elem = *head;
    elem_t *next_elem = current_elem->next;

    while (1 == 1){
        swap_flag = 0;
        while (current_elem->next != NULL){
            if (current_elem->value > next_elem->value){
                int temp = current_elem->value;
                current_elem->value = next_elem->value;
                next_elem->value = temp;
                swap_flag = 1;
            }
            current_elem = current_elem->next;
            next_elem = current_elem->next;
        }
        // no swaps found
        if (swap_flag == 0) break;
        current_elem = *head;
        next_elem = current_elem->next;
    }
}

void bubble_sort_copy_ref(elem_t **head) {
    if (*head == NULL) return;

    int swap_flag;
    elem_t *current_elem = *head;
    elem_t *next_elem = current_elem->next;

    while (1 == 1){
        swap_flag = 0;
        // while not at end of list
        while (current_elem->next != NULL){
            // need to swap elements
            if (current_elem->value > next_elem->value){
                elem_t *a = current_elem;
                elem_t *b = next_elem;
                elem_t *before_a = a->prev;
                elem_t *after_b = b->next;

                if (before_a == NULL && after_b == NULL){
                    // only two things in list
                    b->next = a;
                    b->prev = before_a;
                    a->next = after_b;
                    a->prev = b;
                    *head = b;

                    swap_flag = 1;
                    current_elem = b;
                }
                else if (before_a == NULL) {
                    // swapping at start of list
                    b->next = a;
                    b->prev = before_a;
                    a->next = after_b;
                    a->prev = b;
                    after_b->prev = a;
                    *head = b;

                    swap_flag = 1;
                    current_elem = b;
                }
                else if (after_b == NULL){
                    // swapping at end of list
                    before_a->next = b;
                    b->next = a;
                    b->prev = before_a;
                    a->next = after_b;
                    a->prev = b;

                    swap_flag = 1;
                    current_elem = b;
                }
                else{
                    // swapping in middle
                    before_a->next = b;
                    b->next = a;
                    b->prev = before_a;
                    a->next = after_b;
                    a->prev = b;
                    after_b->prev = a;

                    swap_flag = 1;
                    current_elem = b;
                }
            }
            current_elem = current_elem->next;
            next_elem = current_elem->next;
       }
        // no swaps found
        if (swap_flag == 0) break;

        // restart at head of list
        current_elem = *head;
        next_elem = current_elem->next;
    }
}

elem_t *build_list(int num_elements) {
    srand(1234);

    elem_t *head = NULL;
    for (int i = 0; i < num_elements; i++) {
        elem_t *e = (elem_t *) malloc(sizeof(elem_t));
        
        e->value = random() % 100;
        e->next = NULL;
        e->prev = NULL;

        if (head == NULL) {
            head = e;
        } else {
            e->next = head;
            head->prev = e;
            head = e;
        }
    }

    return head;
}

int main() {
    elem_t *head = build_list(100);

    print_list(head);
    printf("==================================\n");
    bubble_sort_copy_value(&head);

    print_list(head);
    printf("\n");

    head = build_list(100);

    print_list(head);
    printf("==================================\n");
    bubble_sort_copy_value(&head);
    print_list(head);
    printf("\n");
    bubble_sort_copy_ref(&head);
}
