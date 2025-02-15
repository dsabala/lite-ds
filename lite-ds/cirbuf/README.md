# Cirbuf Module

The Cirbuf module provides a straightforward implementation of a circular buffer.

### Design Principles:
- loosely inspired by the [Boost circular_buffer](https://www.boost.org/doc/libs/1_84_0/doc/html/circular_buffer/implementation.html):
  - offers intuitive behavior
  - automatically overwrites the oldest data when new elements are pushed into a full buffer
