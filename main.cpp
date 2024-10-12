// Lab 22: Upgrade the DLL Class
// COMSC-210 - Ibrahim Alatig 

//    DoublyLinkedList           
// --------------------
// - head: Node*                   
// - tail: Node*                   
// -----------------------------
// + DoublyLinkedList()            
// + push_back(value: int): void   
// + push_front(value: int): void  
// + insert_after(value: int, position: int): void 
// + delete_pos(position: int): void 
// + pop_front(): void             
// + pop_back(): void              
// + delete_val(value: int): void
// + print(): void                 
// + print_reverse(): void         
// ~ DoublyLinkedList()            
//-------------------------------------
// - Node struct                   
// - data: int                   
// - prev: Node*                 
// - next: Node*                 
// + Node(val: int, p: Node* = nullptr, n: Node* = nullptr) 

#include <iostream>
#include <cstdlib> 

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;

public:
    // Constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; 
        temp->next = newNode;
    }

    void delete_pos(int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {
            cout << "Position exceeds list size. Node not deleted.\n";
            return;
        }
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }
        delete temp;
    }

    void pop_front() {
        if (!head) return; // Empty list
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // List is now empty
        }
        delete temp;
    }

    void pop_back() {
        if (tail == nullptr) return; // List is empty
        if (tail == head) { // Only one element
            delete tail;
            head = tail = nullptr;
            return;
        }
        Node* current = head;
        while (current->next != tail) {
            current = current->next; // Find the second-last node
        }
        delete tail; // Delete the last node
        tail = current; // Update tail to be the second last
        tail->next = nullptr; // Set new tail's next to nullptr

    }
    
    void delete_val(int value) {
        if (!head) return; // Empty list
        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;
        if (!temp) return; // Value not found
        if (temp->prev) {
            temp-> prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }
        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList list;

    // Generate a list with random integers
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);
    
    cout << "List forward: ";
    list.print();
    
    cout << "List backward: ";
    list.print_reverse();
    
    cout << "Deleting node at position 2: " << endl;
    list.delete_pos(2);
    list.print();
    
    cout << "Popping front: " << endl;
    list.pop_front();
    list.print();
    
    cout << "Popping back: " << endl;
    list.pop_back();
    list.print();
    
    cout << "Deleting value 45 (if exists): " << endl;
    list.delete_val(45);
    list.print();
    
    cout << "List forward after all operations: ";
    list.print();
    
    return 0;
}