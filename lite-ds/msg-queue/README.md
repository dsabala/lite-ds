# Message Queue Module

The Message Queue module is a straightforward FIFO buffer that supports messages of a fixed, predefined size.

### Design Principles:
- loosely inspired by the [RTEMS message queues](https://docs.rtems.org/docs/5.3/c-user/message_manager.html),
  but does not allow pushing messages smaller than the size specified during initialization
- unlike the Cirbuf module, it does not permit overwriting the oldest message
