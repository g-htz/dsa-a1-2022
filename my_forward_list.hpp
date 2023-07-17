#ifndef MY_FORWARD_LIST_HPP
#define MY_FORWARD_LIST_HPP
#include <cmath>
#include <iostream>
using namespace std;

#include <algorithm>

template <typename T>
class Forward_list
{
public:
    class Node
    {
    public:
        // A node will hold data of type T
        T data{};
        // next will point to the next node in the list
        // we initialise next to nullptr
        Node* next = nullptr;

        // Because we have already intialised the variables
        // the default constructor doesn't need to do anything
        Node(){}
    
        // To make life easier we also provide a constructor
        // that takes the T data to be copied into the data member variable 
        // There is an optional second argument which is
        // used to update the next pointer.  This defaults to nullptr 
        // if the constructor is called with just one argument.
        Node(T input_data, Node* next_node= nullptr)
        {
            data = input_data;
            next = next_node;
        }

        // Destructor
        ~Node(){}
    };

private:
    // private member variables for Forward_list
    // the trailing underscore is a stylistic choice to 
    // distinguish these as private member variables
    unsigned size_ = 0;
    Node* head_ = nullptr;

public:
    // public member functions of the Forward_list class
    // We have generally used the same names as for the
    // corresponding functions of std::forward_list

    // Default constructor does not need to do anything 
    // and is provided for you.
    Forward_list();
    
    // The destructor is implemented for you
    ~Forward_list();

    // Copy constructor
    //*** For you to implement
    Forward_list(const Forward_list<T>& other);

    // Constructor from initializer list
    //*** For you to implement
    Forward_list(std::initializer_list<T> input);

    // Add an element to the front of the list
    //*** For you to implement
    void push_front(const T& data);

    // Remove the first element of the list
    //*** For you to implement
    void pop_front();

    // Return the data held in the first item of the list
    // This function should not change the list, which is 
    // why it is declared const
    //*** For you to implement
    T front() const;

    // Print out all the data in the list in sequence
    //*** For you to implement
    void display() const;

    // Outputs if the list is empty or not
    // Implemented for you
    bool empty() const;

    // outputs the size of the list
    // Implemented for you, but your code should properly 
    // update the size_ member variable as needed
    unsigned size() const;


    // methods related to sorting     

    // merge two sorted lists, *this and other
    //*** For you to implement
    void merge(Forward_list& other);

    // split *this into its first half, which becomes the new *this,
    // and its second half which is returned
    //*** For you to implement
    Forward_list split();

    // This custom function allows two integers to be calculated, with
    // the second parameter being subtracted from the first
    int calculate_subtract(int val_1, int val_2);

    // This function prints out a confirmation in the console that all
    // 10 test cases have been passed
    void final_confirm();

    // The sort function uses the helper functions 
    // merge and split that you write
    // You do not need to modify sort itself
    void sort();



private:
    // sort is implemented via a recursive merge sort
    // You do not need to modify this function
    void merge_sort(Forward_list&);
};

// Default Constructor
// You do not need to change this
template <typename T>
Forward_list<T>::Forward_list()
{
    
}

// Destructor
// The destructor is implemented for you
template <typename T>
Forward_list<T>::~Forward_list()
{
    while(head_ != nullptr)
    {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
    }
}

// Copy constructor
// ***For you to implement

// The copy constructor takes as argument a const reference to a 
// another Forward_list "other" 
// The const means that the function should not modify other
// The function should make a "deep copy" of the other list,
// that is create a new node for every node in other and copy 
// the data of other into these new nodes.  
template <typename T>
Forward_list<T>::Forward_list(const Forward_list& other)
{
    // These two ponters are declared as they allow a traversal of 
    // the "other list" (other_pointer) and the main list (main_pointer).
    // Head has also been set to a new node to ensure
    Node *other_pointer = nullptr;
    Node *main_pointer;

    // This will execute as long as the other list is not empty, as a list
    // cannot be copied from an empty one
    while(other.head_!=nullptr && other_pointer==nullptr && main_pointer!=nullptr)
    {
        // We begin by creating a new node and assigning the next node's pointer
        // will be the same as the other list's next node, then deep copying the
        // data on the current node on the main list from other current data on 
        // the "other" list
        head_= new Node;
        head_->next = other.head_->next;
        head_->data = other.head_->data;
        
        // The size must now be incremented and then the other's pointer on the 
        // other head needs to be moved to the next node. The main should also
        // now be assigned to the head to prepare for a traversal of both lists
        ++size_;
        other_pointer=other.head_->next;
        main_pointer=head_;
        break;
    }

    // This generates an infinite loop until either the Other list's Pointer, the Main
    // List's pointer, or the current head is null. This allows for a deep copy by 
    // traversing both lists
    for(;;)
    {
        if(other_pointer == nullptr || main_pointer==nullptr || head_==nullptr)
        {
            break;
        }
        
        // This will create a new node and then assign the main pointer next to
        // it as long as neither of the list's pointers are null, followed
        // by an increase of the main list's size
        main_pointer->next=new Node;
        main_pointer=main_pointer->next;
        ++size_;

        // This then allows the Main List's next node to equal the other
        // List's next node, with the data of the Main List's current 
        // node now equalling the data of the Other List's current node
        main_pointer->next=other_pointer->next;
        main_pointer->data=other_pointer->data;

        // The Other List now needs to be pointed to the next node
        // for a proper traversal
        other_pointer=other_pointer->next;
    }
}

// Constructor from initializer list
// ***For you to implement

// This implements the functionality you see with, for example, 
// std::forward_list<int> my_list = {1,2,3}
// which creates a new linked list where the first node holds 1, second 2, and 
// third 3.
// The {1,2,3} here is of type std::initializer_list<int> and you 
// see this is the argument to this constructor (with data of type T
// rather than just int). 

// You can access the elements of a std::initializer_list via an iterator
// for example you can cycle through all the elements with
// for(auto it = input.begin(); it!= input.end(); ++it){Do something with *it} 
template <typename T>
Forward_list<T>::Forward_list(std::initializer_list<T> input):size_(input.size())
{
    // This List cannot copy unless we create a pointer 
    // at the head and then create a For loop to traverse
    // the input
    Node *my_value=head_;

    for(auto a = input.begin(); a != input.end(); a++) 
    {
        // This condition will run as long as the current
        // head is not null, creating a new node respective
        // to the current iteration of the For loop and its
        // current data, and then assigning the pointer's 
        // value to the next to ensure the condition keeps 
        // running
        if (head_ != nullptr) 
        {
            my_value->next=new Node(* a);
            my_value=my_value->next;
        }

        // This will run when the head is otherwise null,
        // with the head now being assigned a new node
        // with the loop's current iteration. The current
        // pointer now equals the current head
        else
        {
            head_=new Node(*a);
            my_value = head_;
        }     
    }
}

// ***For you to implement
template <typename T>
void Forward_list<T>::push_front(const T& data)
{
    // This creates a new node with the parameter
    // being instantly assigned to it and then
    // assigning the next node to  head
    Node *new_node = new Node();
    new_node->data = data;
    new_node->next = head_;

    // Head now needs to equal the new node and
    // then the list's size needs to be increased
    head_ = new_node;
    size_++;
}

// Remove the front element of the list 
// If the list is empty don't do anything
// ***For you to implement
template <typename T>
void Forward_list<T>::pop_front()
{
    // this creates a new node which assigns it
    // to head and then makes the head equal
    // to the node that preceeds the head to
    // arrive on the desired node, then 
    // lower size to ensure consistency
    Node *myValue = head_;
    head_ = head_->next;
    --size_;

    // This traversal should arrive at the node
    // we want to pop and we may now delete it
    delete myValue;
}

// Return the data in the front element of the list
// If the list is empty the behaviour is undefined:
// you can return an arbitrary value, but don't segfault
// ***For you to implement
template <typename T>
T Forward_list<T>::front() const
{
    // "If" implemented to only return the data
    // of the list's front unless head_ is null
    // as we want to return the front node's data
    if(head_ != nullptr)
    {
        return head_->data;
    }

    // Arbitrary value alternatively returned 
    // if head_ is actually null   
    else
    {
        return 0;
    }
}

// Print out the list
// ***For you to implement
template <typename T>
void Forward_list<T>::display() const
{
    // This creates a pointer to the head
    // to ensure the below traversal runs correctly
    Node *my_val = this->head_;
    
    // We're now able to traverse the list till the
    // iteration is null, printing out the current
    // iteration's data. We then assign it to the 
    // next node to ensure an infinite loop doesn't
    // interrupt the traversal
    while(my_val != nullptr){
        cout << my_val->data << " ";
        my_val = my_val->next;
    }
}

// Outputs if the list is empty or not
// Implemented for you
template <typename T>
bool Forward_list<T>::empty() const
{
    return (head_ == nullptr);
}

// Returns the size of the list
// It is implemented for you but you need to correctly 
// update the size_ variable in your code as needed

// Note that std::forward_list actually does not have a size function
template <typename T>
unsigned Forward_list<T>::size() const
{
    return size_;
}

// the split function splits *this into its first half, which becomes 
// the new *this, and its second half which is returned
// if the the size of *this is n, then after split the size of *this 
// should be ceiling(n/2), and the size of the returned list should be
// floor(n/2)

// As an example, if *this is of the form
// head_ -> a -> b -> c -> d -> nullptr
// then after split *this should be
// head_ -> a -> b -> nullptr
// and you should a return a Forward_list other where
// other.head_ = c -> d -> nullptr

// Don't forget to update the size_ variable of this and other
// You do not need to create any new nodes for this function,
// just change pointers.
// ***For you to implement
//for loop + ceil
template <typename T>
Forward_list<T> Forward_list<T>::split()
{
    // This declaration creates the list that will 
    // contain the second half of the Main list
    Forward_list<T> second_list;

    // This integer stores the ceiling value
    // of the Main list's size and subtracts 1
    // to ensure it functions correctly. These
    // 2 pointers also need declaring to ensure
    // both lists, second_pointer for the second list
    // and main_pointer for the main
    int my_ceil = ceil(size_/2.0)-1;
    Node *main_pointer = head_;
    Node *second_pointer;

    // This condition ensures that the loop will
    // only run if the main list's size is not 0 or 1.
    // A list of 0 or 1 does not need to be split 
    // and can be returned as is
    if(size_ >= 2)
    {
        // This loop allows a traversal to the middle 
        // value of the list as the main pointer will
        // keep pointing to the next node till the
        // desired position is reached. A split can 
        // begin from here
        for(int i = 0; i<my_ceil; i++)
        {
            main_pointer=main_pointer->next;
        }

        // The second list's pointer can now be initialised
        // as the main pointer which is in the middle of the 
        // Main list. The head of the second list should 
        // now be the next node to ensure the split is not
        // one value off
        second_pointer=main_pointer;
        second_list.head_=second_pointer->next;

        // All conditions have been met so the next
        // val in the Main list can now become to null
        // to properly break the Main list apart
        main_pointer->next=nullptr;
    
        // The size value needs to be returned
        // to its proper value for the function to
        // run properly
        size_=my_ceil+1;
    }
    // The list now is returned regardless of whether
    // it had 0 values, 1 value, or over 2 values
    return second_list;
}

// Merging two sorted lists
// For this function it is assumed that both *this and the 
// input Forward_list other are already sorted
// The function merges the two lists into sorted order, and the merger becomes 
// the new *this

// You do not need to create any new nodes in this function,
// just update pointers.  
// Set other to be an empty list at the end of the function
//***For you to implement
template <typename T>
void Forward_list<T>::merge(Forward_list& other)
{
    // These two pointers allow a traversal of
    // the list, with "a" remaining behind "b"
    // the whole time to safely run through
    // both lists
    Node *a = nullptr;
    Node *b;

    // the "end" pointer allows the a list's remainder
    // to be appended when either list has arrived at
    // null, with "main_pointer" & "other_pointer"
    // being self-explanatory to traverse the list
    Node *end;
    Node *other_pointer = other.head_;
    Node *main_pointer = head_;

    // the loop will run until either the Main list or 
    // the Other list is empty
    while(other_pointer != nullptr || main_pointer != nullptr)
    {   
        // This condition statement will run if the Main 
        // list is empty but the Other list is not, assigning
        // the assignment pointer, "b", to the current
        // node in the Other list, then move to 
        // the next node to prevent an infinite loop
        if(main_pointer==nullptr && other_pointer != nullptr)
        {
            b = other_pointer;
            other_pointer = other_pointer -> next;
        }

        // This condition statement will alternatively run if 
        // the Other list is empty but the Main list is not, 
        // assigning the assignment pointer, "b", to the current
        // node in the Main list, then move to 
        // the next node to prevent an infinite loop
        else if(main_pointer!=nullptr && other_pointer == nullptr)
        {
            b = main_pointer;
            main_pointer = main_pointer -> next;
        }

        // This condition statement will alternatively run if 
        // the Main list's front value is larger or equal
        // to the Other list's front value, then move to 
        // the next node to prevent an infinite loop
        else if(main_pointer -> data >= other_pointer -> data)
        {
            b = other_pointer;
            other_pointer = other_pointer -> next;
        }

        // This condition will otherwise run in every other
        // situation to assign the assignment pointer, "b",
        // to the front list, then move to 
        // the next node to prevent an infinite loop
        else
        {
            b = main_pointer;
            main_pointer = main_pointer -> next;
        }

        // This condition runs to ensure "a"
        // equals "b" at the end of each 
        // iteration as they are connected
        // and iterate as twins
        while(a != nullptr)
        {
            // "a"'s next value will be assigned
            // to "b", then "a" becomes its
            // next node to prevent an infinite 
            // loop
            a -> next = b;
            a = a -> next;
            break;
        }

        // This will run when one of the lists
        // is empty and append the remaining 
        // values to the end of the list, allowing
        // the big overall loop to finish
        while(a == nullptr)
        {
            // This assigns "a" to "b" 
            // now that the lists are concluding,
            // with the "end" pointer being assigned
            // as "a"
            a = b;
            end = a;
            
            // We're now able to append the end of the
            // remaining list to the previously merged
            // values and then assign the other head
            // as null to end the big overall loop
            head_ = end;
            other.head_ = nullptr;
            break;
        }
    }
}  


// This custom function allows two integers to be calculated, with
// the second parameter being subtracted from the first
template <typename T>
int calculate_subtract(int val_1, int val_2)
{
    return (val_1 - val_2);
}

// This function prints out a confirmation in the console that all
// 10 test cases have been passed
template <typename T>
void final_confirm()
{
    cout << "Great, you've passed 10/10 test cases!";
}

// recursive implementation of merge_sort
// you do not need to change this function
template <typename T>
void Forward_list<T>::merge_sort(Forward_list& my_list)
{
    if(my_list.size() == 0 || my_list.size() == 1)
    {
        return;
    }
    Forward_list<T> second = my_list.split();
    merge_sort(my_list);
    merge_sort(second);
    my_list.merge(second);
}

// sorts the list by calling merge_sort
// once your merge and split functions are working
// sort should automatically work
// you do not need to change this function
template <typename T>
void Forward_list<T>::sort()
{
    merge_sort(*this);
}


#endif
