// Ordered Single Linked List Functions 
#include <iostream>
using namespace std;
template<class T>
class Node {
public:
    T data;
    Node *next;

    Node(T data) {
        this->data = data;
        this->next = nullptr;
    }
};
template<class T>
class SingleLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int size;
public:
    SingleLinkedList () {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

void insert(const T& newItem) {
  Node<T>* current;
  Node<T>* trailCurrent;
  Node<T>* newNode;
  bool found;
  newNode = new Node<T>(newItem);
  newNode->next = NULL;
  if (head == NULL) {
    head = newNode;
    tail = newNode;
    size++;
  } else {
    current = head;
    found = false;
    while (current != NULL && !found)
      if (current->data >= newItem)
        found = true;
      else {
        trailCurrent = current;
        current = current->next;
      }
    if (current == head) {
      newNode->next = head;
      head = newNode;
      size++;
    } else {
      trailCurrent->next = newNode;
      newNode->next = current;
      if (current == NULL) tail = newNode;
      size++;
    }
  }
}

bool search(const T& searchItem) const {
  Node<T>* current;
  bool found = false;
  current = head;
  while (current != NULL && !found)
    if (current->data >= searchItem)
      found = true;
    else
      current = current->next;
    if (found) found = (current->data == searchItem);  
  return found;
}

void deleteNode(const T& deleteItem) {
  Node<T>* current;
  Node<T>* trailCurrent;
  bool found;
  if (head == NULL)
    cout << "Cannot delete from an empty list." << endl;
 else {
    current = head;
    found = false;
    while (current != NULL && !found){
      if (current->data >= deleteItem)
        found = true;
      else {
        trailCurrent = current;
        current = current->next;
      }
      
    }
    if (current == NULL)
      cout << "The item to be deleted is not in the list." << endl;
      
    else if (current->data == deleteItem) {
      if (head == current) {
        head = head->next;
        if (head == NULL) tail = NULL;
        delete current; }
        
        else {
        trailCurrent->next = current->next;
        if (current == tail) tail = trailCurrent;
        delete current;
      }
      
      size--;
      }
    else
      cout << "The item to be deleted is not in the list." << endl;
  }
}
  bool isEmpty() {
        return size == 0;
    }

 void print() {
        Node<T> *temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
    
};


int main() {
    SingleLinkedList<int> list;

    cout << "Ordered Single Linked List Operations:\n";
    cout << "1. Insert Element\n";
    cout << "2. Search for an Element\n";
    cout << "3. Delete an Element\n";
    cout << "4. Print the List\n";
    cout << "5. Exit\n";

    int choice, value;

    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                list.insert(value);
                cout << "Value inserted in sorted order.\n";
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (list.search(value))
                    cout << "Value found in the list.\n";
                else
                    cout << "Value not found in the list.\n";
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteNode(value);
                break;
            case 4:
                cout << "Current List: ";
                list.print();
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
