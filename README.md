# Doubly_Linked_List
 My implementation of a Doubly Linked List in C++.

  Manual:

  - Constansts:
     - FORWARDS: when calling advance, use this constant to specify the direction. It can be called without an instance.
     - BACKWARDS: when calling advance, use this constant to specify the direction. It can be called without an instance.
   
     - FIRST_NODE: when calling reset_cursor, use this constant to specify the position.
     - LAST_NODE: when calling reset_cursor, use this constant to specify the position.
 
 - add(new_element): adds new_element to the end of the list.

 - remove(): removes the last element.

 - add(new_element, index): adds new_element before the element at the given index. If the index is equal to the size of the list, it just adds the element at the end.

 - remove(index): removes the index at the given position. If index is equal to the size of the list - 1, it just removes the last element.

 - first(): returns the first element of the list.

 - last(): returns the last element of the list.

 - element(index): returns the element at the given position.

 - can_advance(): returns true if it is possible advance (it means that the cursor isn´t nullptr).

 - advance(direction): returns the element being pointed by the cursor and then moves the cursor in the desired direction.

 - reset_cursor(position): resets the cursor to the beggining or the end. If the list is empty, the cursor is reseted to it's innitial state (this means, cursor = nullptr and cursor_index = -1).

 - size(): returns the number of elements in the list.

 - empty(): Returns true if the list is empty.
