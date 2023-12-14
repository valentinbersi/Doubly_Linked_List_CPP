#ifndef DLLIST_HPP
#define DLLIST_HPP

#include <exception>
#include <cstdlib>
#include "DLNode.hpp"

class IndexException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Index out of bounds";
    }
};

class EmptyException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Empty list";
    }
};

class CursorException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Cursor isn´t pointing to any element";
    }
};

template<class T>
class DLList {
private:
    DLNode<T> *first_node;
    DLNode<T> *last_node;
    DLNode<T> *cursor;
    int cursor_index;
    size_t _size;

    const int INVALID_INDEX = -1;
    const int FIRST_INDEX = 0;
    const size_t EMPTY = 0;
    const size_t ONE_ELEMENT = 1;
    const size_t FIRST_ELEMENT = 0;

    // Pre: index must be less than size.
    // Post: returns a pointer to the node associated with the given index.
    [[nodiscard]] DLNode<T> *get_node(size_t index);

public:
    // When calling advance, use this constant to specify the direction.
    static const bool FORWARDS = true;

    // When calling advance, use this constant to specify the direction.
    static const bool BACKWARDS = false;

    // When calling reset_cursor, use this constant to specify the position.
    const bool FIRST_NODE = true;

    // When calling reset_cursor, use this constant to specify the position.
    const bool LAST_NODE = false;

    // Constructor.
    DLList();

    // Copy constructor.
    DLList(const DLList &list);

    // Copy assignment operator
    DLList<T> &operator=(const DLList &list);

    // Pre: -
    // Post: adds the element at the end of the list.
    void add(T new_element);

    // Pre: list can´t be empty.
    // Post: removes the last element.
    T remove();

    // Pre: index must be less than or equal to the size of the list.
    // Post: adds the element before the element at the given position. If the index is equal to the size of the list,
    // it just adds the element at the end.
    void add(T element, size_t index);

    // Pre: index must be less than the size of the list.
    // Post: removes the index at the given position. If index is equal to the size of the list - 1, it just removes
    // the last element.
    T remove(size_t index);

    // Pre: the list can´t be empty.
    // Post: returns the first element of the list.
    [[nodiscard]] T first();

    // Pre: the list can´t be empty.
    // Post: returns the last element of the list.
    [[nodiscard]] T last();

    // Pre: index must be less than the size of the list.
    // Post: returns the element at the given position
    [[nodiscard]] T element(size_t index);

    // Pre: -
    // Post: returns true if it is possible advance (it means that the cursor isn´t nullptr).
    [[nodiscard]] bool can_advance();

    // Pre: the cursor must be able to advance
    // Post: returns the element being pointed by the cursor and then moves the cursor in the desired direction.
    // NOTE: next == true means that the cursor will be moved forwards, otherwise it will be moved backwards.
    T advance(bool next);

    // Pre: -
    // Post: Resets the cursor to the beggining or the end. If the list is empty, the cursor is reseted to ist innitial
    // state (this means, cursor = nullptr and cursor_index = -1).
    void reset_cursor(bool beginning);

    // Pre: -
    // Post: Returns the number of elements in the list.
    [[nodiscard]] size_t size();

    // Pre: -
    // Post: Returns true if the list is empty.
    [[nodiscard]] bool empty();

    // Destructor.
    ~DLList();
};

template<class T>
DLNode<T> *DLList<T>::get_node(size_t index) {
    if (index >= size()) {
        throw IndexException();
    }

    if (index == static_cast<size_t>(FIRST_INDEX)) {
        return first_node;
    }
    if (index == size() - 1) {
        return last_node;
    }
    if (index == static_cast<size_t>(cursor_index)) {
        return cursor;
    }

    DLNode<T> *aux;
    bool movement_direction;
    size_t steps_to_move;

    if (index < static_cast<size_t>(cursor_index)) {
        if (index < static_cast<size_t>(cursor_index) / 2) {
            aux = first_node;
            movement_direction = FORWARDS;
            steps_to_move = index;

        } else {
            aux = cursor;
            movement_direction = BACKWARDS;
            steps_to_move = static_cast<size_t>(cursor_index) - index;
        }
    } else {
        if (index < (index + size() - 1) / 2) {
            aux = cursor;
            movement_direction = FORWARDS;
            steps_to_move = index - static_cast<size_t>(cursor_index);

        } else {
            aux = last_node;
            movement_direction = BACKWARDS;
            steps_to_move = size() - 1 - index;
        }
    }

    if (movement_direction) {
        for (size_t _ = 0; _ < steps_to_move; _++) {
            aux = aux->get_next();
        }

    } else {
        for (size_t _ = 0; _ < steps_to_move; _++) {
            aux = aux->get_previous();
        }
    }

    return aux;
}

template<class T>
DLList<T>::DLList() {
    first_node = nullptr;
    last_node = nullptr;
    cursor = nullptr;
    cursor_index = INVALID_INDEX;
    _size = EMPTY;
}

template<class T>
DLList<T>::DLList(const DLList &list) {
    first_node = nullptr;
    last_node = nullptr;
    cursor = nullptr;
    cursor_index = INVALID_INDEX;
    _size = EMPTY;

    for (DLNode<T> *node = list.first_node; list.can_advance(); node = node->get_next()) {
        add(node->get_element());
    }
}

template<class T>
DLList<T> &DLList<T>::operator=(const DLList &list) {
    DLList<T> aux(list);

    while (!empty()) {
        remove();
    }

    first_node = nullptr;
    last_node = nullptr;
    cursor = nullptr;
    cursor_index = INVALID_INDEX;
    _size = EMPTY;

    for (DLNode<T> *node = aux.first_node; aux.can_advance(); node = node->get_next()) {
        add(node->get_element());
    }

    return *this;
}

template<typename T>
void DLList<T>::add(T new_element) {
    if (empty()) {
        first_node = new DLNode<T>(new_element);
        last_node = first_node;
        cursor = first_node;
        cursor_index = FIRST_INDEX;
    } else {
        auto *new_node = new DLNode<T>(new_element, last_node, nullptr);
        last_node->set_next(new_node);
        last_node = new_node;
    }

    _size++;
}

template<typename T>
T DLList<T>::remove() {
    if (empty()) {
        throw EmptyException();
    }

    DLNode<T> *removed_node;
    T removed_element;

    if (size() > ONE_ELEMENT) {
        removed_node = last_node;
        last_node = last_node->get_previous();
        last_node->set_next(nullptr);
    } else {
        removed_node = last_node;
        first_node = nullptr;
        last_node = nullptr;
        cursor = nullptr;
        cursor_index = INVALID_INDEX;
    }

    removed_element = removed_node->get_element();
    _size--;
    if (cursor == removed_node) {
        reset_cursor(LAST_NODE);
    }
    delete removed_node;

    return removed_element;
}

template<typename T>
void DLList<T>::add(T new_element, size_t index) {
    if (index > size()) {
        throw IndexException();
    }

    DLNode<T> *new_node;
    if (empty()) {
        first_node = new DLNode<T>(new_element);
        last_node = first_node;
        cursor = first_node;
        cursor_index = FIRST_INDEX;

    } else if (index == FIRST_INDEX) {
        new_node = new DLNode<T>(new_element, nullptr, first_node);
        first_node->set_previous(new_node);
        first_node = new_node;
        cursor_index++;
    } else if (index == size()) {
        new_node = new DLNode<T>(new_element, last_node, nullptr);
        last_node->set_next(new_node);
        last_node = new_node;
    } else {
        DLNode<T> *next_node = get_node(index);
        new_node = new DLNode<T>(new_element, next_node->get_previous(), next_node);
        new_node->get_previous()->set_next(new_node);
        next_node->set_previous(new_node);

        if (index <= static_cast<size_t>(cursor_index)) {
            cursor_index++;
        }
    }

    _size++;
}

template<typename T>
T DLList<T>::remove(size_t index) {
    if (index >= size()) {
        throw IndexException();
    }

    T removed_element;
    DLNode<T> *removed_node;

    if (size() > ONE_ELEMENT) {
        if (index == FIRST_INDEX) {
            removed_node = first_node;
            first_node = first_node->get_next();
            first_node->set_previous(nullptr);

        } else if (index == size() - 1) {
            removed_node = last_node;
            last_node = last_node->get_previous();
            last_node->set_next(nullptr);

        } else {
            removed_node = get_node(index);
            removed_node->get_next()->set_previous(removed_node->get_previous());
            removed_node->get_previous()->set_next(removed_node->get_next());
        }
    } else {
        removed_node = last_node;
        first_node = nullptr;
        last_node = nullptr;
        cursor = nullptr;
        cursor_index = INVALID_INDEX;
    }

    removed_element = removed_node->get_element();
    _size--;

    if (cursor == removed_node) {
        (index < size() / 2) ? reset_cursor(FIRST_NODE) : reset_cursor(LAST_NODE);

    } else if (static_cast<size_t>(cursor_index) < index && cursor_index != INVALID_INDEX) {
        cursor_index--;
    }

    delete removed_node;

    return removed_element;
}

template<typename T>
T DLList<T>::first() {
    if (empty()) {
        throw EmptyException();
    }

    return first_node->get_element();
}

template<typename T>
T DLList<T>::last() {
    if (empty()) {
        throw EmptyException();
    }

    return last_node->get_element();
}

template<typename T>
T DLList<T>::element(size_t index) {
    if (index >= size()) {
        throw IndexException();
    }

    return get_node(index)->get_element();
}

template<typename T>
bool DLList<T>::can_advance() {
    return cursor;
}

template<typename T>
T DLList<T>::advance(bool next) {
    if (!can_advance()) {
        throw CursorException();
    }

    T element = cursor->get_element();

    if (next) {
        cursor = cursor->get_next();
        cursor_index++;
    } else {
        cursor = cursor->get_previous();
        cursor_index--;
    }

    return element;
}

template<typename T>
void DLList<T>::reset_cursor(bool beginning) {
    if (empty()) {
        cursor = nullptr;
        cursor_index = INVALID_INDEX;
    } else if (beginning) {
        cursor = first_node;
        cursor_index = FIRST_INDEX;
    } else {
        cursor = last_node;
        cursor_index = static_cast<int>(size()) - 1;
    }
}

template<typename T>
size_t DLList<T>::size() {
    return _size;
}

template<typename T>
bool DLList<T>::empty() {
    return !_size;
}

template<typename T>
DLList<T>::~DLList() {
    while (!empty()) {
        remove();
    }
}

#endif //DLList_HPP
