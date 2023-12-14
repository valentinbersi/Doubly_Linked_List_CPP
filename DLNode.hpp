#ifndef DLNODE_HPP
#define DLNODE_HPP

template<class T>
class DLNode {
private:
    T element{};
    DLNode<T> *previous;
    DLNode<T> *next;

public:
    // Constructor.
    explicit DLNode(T element);

    // Constructor.
    DLNode(T element, DLNode<T> *previous, DLNode<T> *next);

    // Pre: -
    // Post: Returns a pointer to the previous node.
    [[nodiscard]] DLNode<T> *get_previous();

    // Pre: -
    // Post: Returns a pointer to the next node.
    [[nodiscard]] DLNode<T> *get_next();

    // Pre: -
    // Post: Sets the pointer to the previous node.
    void set_previous(DLNode<T> *new_previous);

    // Pre: -
    // Post: Sets the pointer to the next node.
    void set_next(DLNode<T> *new_next);

    // Pre: -
    // Post: Returns the stored element.
    [[nodiscard]] T get_element();

    // Destructor.
    ~DLNode();
};

template<class T>
DLNode<T>::DLNode(T element) {
    this->element = element;
    previous = nullptr;
    next = nullptr;
}

template<class T>
DLNode<T>::DLNode(T element, DLNode<T> *previous, DLNode<T> *next) {
    this->element = element;
    this->previous = previous;
    this->next = next;
}

template<class T>
DLNode<T> *DLNode<T>::get_previous() {
    return previous;
}

template<class T>
DLNode<T> *DLNode<T>::get_next() {
    return next;
}

template<class T>
void DLNode<T>::set_previous(DLNode<T> *new_previous) {
    previous = new_previous;
}

template<class T>
void DLNode<T>::set_next(DLNode<T> *new_next) {
    next = new_next;
}

template<class T>
T DLNode<T>::get_element() {
    return element;
}

template<class T>
DLNode<T>::~DLNode() {
    previous = nullptr;
    next = nullptr;
}

#endif //DLNODE_HPP
