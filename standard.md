# Rust Minus Minus (R-\-) Standard

Todo:
 - [  ] **unique** keyword for heap memory
 - [  ] **move(  )** keyword for rebind identifier

## 1. Types

#### 1.1 Built-in types

These types are built-int types.

```rust
i8 i16 i32 i64: 8/16/32/64-bit integer
u8 u16 u32 u64: 8/16/32/64-bit unsigned integer
bool: boolean value
f32 f64: 32/64-bit float point
```
#### 1.2 Type casting

Use operator **as** to cast. Implicit cast is allowed.
```rust
let a: i32 = 'c'; #ok
let b: bool = 9 as bool; #ok
```

#### 1.3 Pointer and Reference type

**\*** is used to mark a pointer type.  **&** is used to create a reference.
```rust
let a: i32 = 1;
let b: i32* = &a; # warning
let c: &i32 = a; # ok
var d: i32 = 1;
let e: i32* = &d; # ok
```
#### 1.4 Array type

**[typename, size]** is used for mark an array type.
```rust 
let array: [i32, 3] = {1,2,3};
let string: [char, ] = "Hello, world.";
let array2: [i32, ] = {1,2};
```

##### 1.4.1 Variable length array

**[typename, variable]** is used as declare a variable length array. Variable length array is treated as an incomplete type like **auto**. You can not pass variable length array to function or nest it into other types.

```rust 
let i: i32 = 0;
var vla1: [i32, i];
var val2: [[i32, i], 9]; # compile error
type arr  [i32, i]; # compile error
type my_struct comp{
	a: [i32, i]; # compile error
};
let fun: auto = <a: [i32,i]; void>{}; # compile error
```

#### 1.5 Function type

**(T1, T2)->T3** defines a function type. Function parameters are default to be **immutable**. Use **mut** keyword to mark them as mutable. Mutable variable does not affect type-checking generally. But it affects function parameters' type-checking to prevent immutable refernce being changed.

```rust
# foo takes an i32 and a char as input and returns a boolean value
let foo: (i32, char)->bool = <a: i32, b: char; bool>{
	return a==b;
}; # assign a function literal to a function named "foo"

# inc can be changed later
# parameters a is mutable
var inc: (mut i32)->i32 = <mut a: i32; i32>{
	a = a+1;
	return a;
}

inc = <a: i32; i32>{ return a; } # compile error
```

#### 1.6 Custom Types

**type** keyword create an alias name for a data type. **comp** (short for **compound**) is used to compose a custom data type.
```rust
type int i32; # alias int for i32
type type_name comp {
	a: i32;
	b: bool;
	fun: (i32, u32)->bool;
};

# make the alias exportable
type export int i32;
```


## 2. Flow Control 

#### 2.1 If-else statement

**if else elif** are keywords. **if** must be followed by a pair of  **{  }**.  
"**;**" must be added at the end.
```python
if(a){ a = 1; }
else { a = 2; }; #ok

if(a) { a = 1; }; #ok

if(a) { a = 1; }
elif(a+1) { a = 2; }; # ok

if(a) a = 2; # Illegal grammar
if(a) {a = 1;} else if(a==1) { a = 2;}; # Illegal grammar
```

#### 2.2 Loop

**for while** are keywords but **for** is not used.   
"**;**" must be added at the end.
```rust 
let i: i32 = 5;
while (i>0){
	i = i - 1;
};
```

#### 2.4 Jump 

**break** **continue** **return** are used to control jump in program.

```rust
var i: i32 = 0;
while(1){
	if(i>10){break;};
	i = i+1;
	if(i>3){continue;}
	else {i = i+2;};
};

let to_unsigned: auto = <m: i32; u32>{
	return m as u32;
};
```

## 3. Functions and variables

#### 3.1 Variable declaration

All variables are **immutable** if declared by **let**. Use **var** to declare mutable ones. Type is **not optional**.  
"**;**" must be added at the end.

```rust 
let a: i32; # declaration
let b: i32 = 32; # declaration and initialization
let c: auto = 'c'; # use auto keyword
let d = 32; # Illegal
```

#### 3.2 Function declaration

Functions in Rust Minus Minus is treated as a normal data type. Thus it also use **let** or **var** keyword to define. **Changing itself in function body is undefined behavior.** Also See [1.5 Function Type](#1.5-function-type).

```rust 
# foo takes an i32 and a char as input and returns a boolean value
let foo: (i32, char)->bool = <a: i32, b: char; bool>{
	return a==b;
}; # assign a function literal to a function named "foo"

# auto keyword is useful here
let bar: auto = <ptr1: char*, ptr2: char*; bool>{
	return ptr1[0]==ptr2[0];
};
```
## 4. Namespace and module system

#### 4.1 Namespace

**::** operator is used to identify namespace.  
**mod** keyword is used to declare a namespace.  
**use** keyword is used to add a namespace into search space.

```rust 
mod cat {
	let meow: (void)->void = <void;void>{};
};

let main: auto = <;i32>{
	meow(); # error
	cat::meow(); # ok

	<void;void>{
		let meow: auto = cat::meow();
		meow(); # ok
	};

	<void;void>{
		use cat;
		meow(); # ok
	};
};
```

#### 4.2 Import and Export

Use **import** keyword to import modules from standard library or from a local file.

```python
import std::io; # import a library
import "src/hello_world.rmm"; # import a file
```

**from** keyword is used to import only a specific function.

```python
import std::io;
from std::string import strlen;

let _s1: [u8,] = "Hello";
let s1: u8* = &_s1[0];
std::string::strcat(s1, s1); # error not imported

puts("some sting"); # error
std::io::puts("some string"); # ok
```
Only variable marked as **export** can be imported.

```rust 
# foo can not be imported
let foo: auto = <a: i32*; i32>{
	*a = *a + 1;
};

# bar can be imported
let export bar: auto = <void ;void>{
	let a: i32 = 0;
	_foo();
};
```


## 5. Keywords, Grammar and trivial stuffs

#### 5.1 A list of keywords and operators

Keywords 

```python
let # declare a immutable variable
var # declare a mutable variable
mut # declare a parameter is mutable
for # not used 
while # while loop 
void # void type 
auto # auto type
nullptr # Null pointer (zero)
if else elif # branch control
i8..i64 u8..u64 f32 f64 bool #built-int type 
true false # boolean values
import # import modules
from # specific where to import
export # specific what to export
mod # namespace specifier
type # type name alias
comp # compound type
```

Operators  

The same as [C programming language](https://en.cppreference.com/w/c/language/operator_precedence).

| Precedence | Operator | Associativity |
| :----: | :---- | :----: |
| 1 | **::** Scope selector | Left-to-right |
| 2 | **(  )**	Function call <br> **[  ]** Array subscripting <br> **. ->**	Member access| Left-to-right |
| 3 | **+ -** Unary plus and minus <br> **! ~** Logical NOT and bitwise NOT <br> **\***	Indirection (dereference) <br> **&** Address-of| 	Right-to-left |
| 4 |  **as**	Type cast | Left-to-right | 
| 5 | **\* / %**	Multiplication, division, and remainder | Left-to-right |
| 6 | **+ -**	Addition and subtraction | Left-to-right |
| 7 | **<< >>**	Bitwise left shift and right shift | Left-to-right |
| 8 | **< <=**	For relational operators < and ≤ respectively <br> **> >=**	For relational operators > and ≥ respectively | Left-to-right |
| 9 | **== !=**	For relational = and ≠ respectively | Left-to-right |
| 10 | **&**	Bitwise AND | Left-to-right |
| 11 | **^**	Bitwise XOR (exclusive or) | Left-to-right |
| 12 | **\|**	Bitwise OR (inclusive or) | Left-to-right |
| 13 | **\|\|**	Logical OR | Left-to-right |
| 14 | **a?b:c** Ternary conditional | Right-to-left |
| 15 | **,**	Comma | Left-to-right |


#### 5.2  Mutability

Mutability is **a trait of variable** and is **not** in **type system**. All non-const (const is not implemented for now) variables are guaranteed to have a real memory location. It is possible (and defined behavior) to change a immutable variable's value by using a pointer. However, this is not recommended. Trying to get the address of immutable variable will cause a warning. Immutable pointers do can change the content. But immutable reference can not. All immutable variable must be initialized. **Mutability is preserved when [passed to a function](#1.5-function-type)**.

```rust
let a: i32; # compile error
let b: i32 = 0; # good
let c: *i32 = &b; # warning: trying to get the address of immutable variable
let d: &i32 = b; # good
```

#### 5.3 Comments

**#** is used to mark a single line comment.

```python 
# This is a line of comment. 
```

#### 5.4 Main function

A function called as "**main**" is required as the entry point for the program. Main function's return type must be either **void** or **i32**. Its parameter list must either **i32, \*\*char** (can be immutable) or **void**. Main itself must be immutable.

```rust
let main: auto = <argc: i32, argv: **char; i32>{
	return 0;
};
```
