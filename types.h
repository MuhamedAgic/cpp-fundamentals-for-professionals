// enums, enum class, enum struct, some examples
// 0, NULL and nullptr and their examples
// aviod assigning 0 or NULL to pointers
// pointers and references

// There is a lot of overlap between pointers and references 
// but the two have some stark differences as well.
// A reference is never NULL.Therefore, it must always be initialized by having 
// an existing variable assigned to it.
// The following lines would not work:
// 
// int& ref;
// int& ref = NULL;
// 
// References behave like constant pointers.
// A reference always refers to its initial variable.
// The value of the variable can change but the reference cannot be assigned to another variable.
// Like pointers, a reference can only be initialized by a variable of the same type.