## 

# Code Standard

##### Member variables

prefix '***m***' written in camelCase.

Examples:

```c++
const int mFoo;

float mBar;

static std::string mHeaderText;
```

Always use `const` when a variable shouldn't change value.



##### Function arguments

No prefix but a good name using **camelCase** that describes the object is required.

Examples:

```c++
void Foo(const Vector2ui& windowSize) -> Good!

void Bar(const int& int / number / bla) -> Bad!
```



### Classes & Structs

**Accessibility operators** should always be in the following order

1. public

2. protected

3. private



**Structs** should be used as pure POD (piece of data) objects. No constructors, functions or operators should be defined in the struct, in that case it should be a class. Defining helper functions outside the struct is allowed but should be in a namespace.

###### Example:

A POD struct:

```C++
struct Foo {

    int counter = 0;

    std::string name = "";

}
```

A bad struct:

```c++
struct Foo {

void DoSomethingCool(const std::string& newName);

int counter = 0;

private:

std::string name = "";

}
```



### Files and folders

New **folders** should use PascalCase:
`Source/Core/Engine/ECS`



New **files** should use camelCase:

`testClass.h`



### Namespaces

Classes inside of **Core (Engine)** should be put inside the namespace `RF` (RuneForge)

Classes inside of Editor should be put inside the namespace `RE` (RuneEditor)

Classes outside these should be put in a namespace in a categorizing way:

`Math::Vector3` `Utils::GenericHelperFunction`

It is important to keep the namespace as short as you can while still keeping a good description of the category, this is to not bloat the code more than is needed.

Global variables in source files should be put in an empty namespace.



### Globals

Uses the prefix '***g***' written in camelCase

constexpr int **g**SuperImportantInt = 42;

Globals should **<u>always</u>** be in a namespace.
