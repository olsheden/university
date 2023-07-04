# Task description
    The task is to implement the CMailServer class, which will simulate the operation of a simple mail server.

    We assume that the server mediates the sending of e-mail inside an organization. Each email is represented by an instance of the CMail class, containing a sender address, a recipient address, and a message body (all strings). The mail server can send the message and can detect the content of sent and received mail (outbox and inbox) for individual e-mail addresses. The list of sent and received mail is provided for individual e-mail addresses in the form of an iterator, the iterator instance offers methods that can be used to move through the list of e-mails and to access the content of individual e-mails. The CMailServer class itself must handle copying correctly, its copy is for archiving and auditing purposes.

    The task is aimed at practicing the understanding of the shallow and deep copy of the object. It has mandatory, voluntary and bonus parts. To fulfill the mandatory part of the task, it is enough to create a functional class that will meet the required interface. In order to handle the optional and bonus parts, you need to rethink data storage so that access to mailboxes is fast and memory is not unnecessarily wasted during copying.

    The task is to practice working with copying objects. For this reason, parts of the standard C++ library, especially the STL and the C++ std::string data type, are suppressed in the task. Only the C string (cstring) library interface is available. For implementation, it may be convenient to create your own simple std::string replacement. You can be inspired by the solution from the pro-seminar.

    The required CMail class has the following interface:

    constructor (from, to, body)
    creates an email instance with the from/to/body folders populated according to the parameters. You can assume that email addresses are relatively short (tens to hundreds of characters) and that the message body can be relatively long (even several megabytes),
    operator ==
    compares the content of two CMail instances, the method returns true if the instances are identical (all from folders match, including the email content).
    operator <<
    displays information about mail to the specified stream. The format is obvious from the sample.
    The required CMailServer class has the following interface:

    implicit constructor
    creates an empty instance,
    destructor
    release the resources allocated by the instance,
    copy constructor, operator =
    creates identical copies of the instance according to standard rules,
    sendMail ( mail )
    sends the email passed in the parameters, effectively placing it in the sender's and recipient's corresponding mailboxes. The email is always placed at the end of the existing list. There is no need to create a recipient or a sender, the mailbox is automatically created after processing the first e-mail that contains the given e-mail address,
    outbox ( email )
    makes available mail sent from the specified address. The return value is a CMailIterator instance that will allow browsing emails sent from the email address. If an unknown email address is specified, the result is an iterator for an empty email list. The returned iterator must capture the state of the mailbox at the time it was created. Thus, if the content of the browsed clipboard changes during the use of the iterator, this change will not be reflected in the values returned by the iterator. This behavior is demonstrated in a sample run, for example, for an i5 iterator.
    inbox (email)
    makes available the mail received at the specified address. Otherwise, the method works the same as the outbox method.
    email addresses
    the task can contain arbitrary strings, when comparing them we distinguish between lower and uppercase letters (case sensitive) - in this the task differs from the real world, where e-mail addresses have a prescribed formal form and where lowercase and uppercase letters are usually insensitive.
    The required CMailIterator class has the following interface:

    bool operator
    operator determines whether the iterator refers to a valid e-mail (returns true) or whether it has reached beyond the last e-mail in the list (i.e. the e-mail can no longer be read, returns false),
    operator!
    works the same as the previous operator, only returns the opposite return value
    operator *
    the unary operator * accesses the email at the current position. The return value is a CMail instance (or a constant reference to CMail). You don't have to deal with the situation that the e-mail after the end of the list would be made available - the test environment always first checks the validity of the iterator and only then, if necessary, makes the referenced e-mail available.
    operator ++
    the ++ prefix operator moves the iterator to the next email in the list. Emails are iterated through in the order they were sent/received. By repeatedly calling this iterator, it is possible to move from the first e-mail received/sent by the specified e-mail address to the last one (then the cast-to-bool operator must return false).
    copy constructor, = operator, destructor
    depending on the implementation method, the automatically generated variant may not be sufficient. The test environment does not explicitly copy iterators anywhere, but copying occurs when the return value is passed by the inbox and outbox methods.