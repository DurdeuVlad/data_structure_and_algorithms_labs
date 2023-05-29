#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5
typedef struct _queue
{
    int vec[CAPACITY];
    int size;
    int head, tail;
} Queue;

void enqueue(Queue *my_queue, int key){
    if(my_queue->size==CAPACITY)return;

    int new_tail = my_queue->tail+1;
    if(new_tail>=CAPACITY)new_tail=0;
    my_queue->vec[my_queue->tail] = key;
    my_queue->tail = new_tail;
    my_queue->size++;
}

int dequeue(Queue *my_queue){
    if(my_queue->size==0)return -1;

    int value = my_queue->vec[my_queue->head];

    int new_head = my_queue->head+1;
    if(new_head>=CAPACITY)new_head=0;
    my_queue->head = new_head;
    my_queue->size--;
    return value;
}

void afisare(Queue queue)
{
    int i=queue.head;
    for(int size=0;size<queue.size;size++){
        printf("%d ", queue.vec[i]);
        i=(i+1)% CAPACITY;
    }

}


int main()
{
    Queue queue;
    queue.head=0;
    queue.tail=0;
    queue.size=0;
    printf("%d\n", dequeue(&queue));
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);
    enqueue(&queue, 4);
    enqueue(&queue, 5);
    afisare(queue);

    printf("\n scoatem: %d", dequeue(&queue));
    printf(" si %d\n", dequeue(&queue));
    enqueue(&queue, 6);
    enqueue(&queue, 7);
    afisare(queue);

    printf("\n scoatem: %d", dequeue(&queue));
    printf(" si %d\n", dequeue(&queue));
    enqueue(&queue, 8);
    enqueue(&queue, 9);
    afisare(queue);
    return 0;
}
