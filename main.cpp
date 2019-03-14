#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;


struct List{
    int data;
    List * next;
};
void print( List *heap)
{
    cout<<"List: ";
    List *list = heap;
    while(list!=nullptr)
    {
        cout<<list->data<<" ";
        list= list->next;
    }
    cout<<"End"<<endl;
}

void merge(List *a, List *b, List **c) {
    List tmp;
    *c = NULL;
    if (a == NULL) {
        *c = b;
        return;
    }
    if (b == NULL) {
        *c = a;
        return;
    }
    if (a->data < b->data) {
        *c = a;
        a = a->next;
    } else {
        *c = b;
        b = b->next;
    }
    tmp.next = *c;
    while (a && b) {
        if (a->data < b->data) {
            (*c)->next = a;
            a = a->next;
        } else {
            (*c)->next = b;
            b = b->next;
        }
        (*c) = (*c)->next;
    }
    if (a) {
        while (a) {
            (*c)->next = a;
            (*c) = (*c)->next;
            a = a->next;
        }
    }
    if (b) {
        while (b) {
            (*c)->next = b;
            (*c) = (*c)->next;
            b = b->next;
        }
    }
    *c = tmp.next;
}

void split(List *src, List **low, List **high) {
    List *fast = NULL;
    List *slow = NULL;

    if (src == NULL || src->next == NULL) {
        (*low) = src;
        (*high) = NULL;
        return;
    }

    slow = src;
    fast = src->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    (*low) = src;
    (*high) = slow->next;
    slow->next = NULL;
}


void mergeSort(List **head) {
    List *low  = NULL;
    List *high = NULL;
    if ((*head == NULL) || ((*head)->next == NULL)) {
        return;
    }
    split(*head, &low, &high);
    mergeSort(&low);
    mergeSort(&high);
    merge(low, high, head);
}

int main()
{
    List *list = new List;
    List *head = list;
    std::srand(unsigned(std::time(0)));
    list->next = nullptr;
    list->data = rand()%50;

    for(int i=0; i<30; ++i)
    {
        list->next = new List;
        list = list->next;
        list->data =rand()%50;

    }
    list->next = nullptr;
    list = head;
    print(head);
    List **t = &head;
    mergeSort(t);

    print(*t);
    return 0;
}
