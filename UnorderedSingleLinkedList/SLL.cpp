// Unordered Single Linked List Functions 
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
    void insertAtHead(T element) {
        Node<T> *newNode = new Node<T>(element);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void insertAtTail(T element) {
        Node<T> *newNode = new Node<T>(element);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->next = nullptr;
            tail = newNode;
        }
        size++;
    }
    
    
bool search(const T& searchItem) const {
  Node<T>* current;
  bool found = false;
  current = head;
  while (current != NULL && !found)
    if (current->data == searchItem)
      found = true;
    else
      current = current->next;
  return found;
}

void deleteNode(const T& deleteItem) {
  Node<T>* current;
  Node<T>* trailCurrent;
  bool found;
  if (head == NULL)
    cout << "Cannot delete from an empty list." << endl;
  else {
    if (head->data == deleteItem) {
      current = head;
      head = head->next;
      size--;
      if (head == NULL) tail = NULL;
      delete current;
    } else {
      found = false;
      trailCurrent = head;
      current = head->next;
      while (current != NULL && !found) {
        if (current->data != deleteItem) {
          trailCurrent = current;
          current = current->next;
        } else
          found = true;
      }
      if (found) {
        trailCurrent->next = current->next;
        size--;
        if (tail == current) tail = trailCurrent;
        delete current;
      } else
        cout << "The item to be deleted is not in " << "the list." << endl;
    }
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

    cout << "Single Linked List Operations:\n";
    cout << "1. Insert at Head\n";
    cout << "2. Insert at Tail\n";
    cout << "3. Search for an Element\n";
    cout << "4. Delete an Element\n";
    cout << "5. Print the List\n";
    cout << "6. Exit\n";

    int choice, value;

    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at head: ";
                cin >> value;
                list.insertAtHead(value);
                cout << "Value inserted at head.\n";
                break;
            case 2:
                cout << "Enter value to insert at tail: ";
                cin >> value;
                list.insertAtTail(value);
                cout << "Value inserted at tail.\n";
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (list.search(value))
                    cout << "Value found in the list.\n";
                else
                    cout << "Value not found in the list.\n";
                break;
            case 4:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteNode(value);
                break;
            case 5:
                cout << "Current List: ";
                list.print();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
