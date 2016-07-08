# File-Leak-Virtual-Method FP

CodeSonar flags a `Leak` false positive error on the above code, assuming an opened file is never closed. However, it *is* closed after being passed to a virtual method of a class.

The FP pattern appears in situations with and without inheritance.

#### Non-inheritance requirements (single class):
* Must define everything in a user-defined namespace (except `main()`). ***(Needs verified--possibly define only certain parts in the namespace??)***
* Method **must** be defined in separate `cpp` file.
* Method **must** be declared `virtual`.
* Caller may use either a *pointer* or an *object* type to refer to the instance.

#### Inheritance requirements (two classes):

I assume the caller uses a *subclass* instance for the actual type. Otherwise, we revert to the single-class case above.

* Must define everything in a user-defined namespace (except `main()`). ***(Needs verified--possibly define only certain parts in the namespace??)***
* Method **must** be defined in separate `cpp` file.
* Method must be declared `virtual` in base class (method may or may not be pure virtual).
* (For *pointer* type in the caller) Caller may use either *base class* or *subclass* as the declared type.
* Caller may use either a *pointer* or an *object* type to refer to the instance (although if using an object type, the object ***must*** be declared as the subclass type...otherwise, it is a TP).