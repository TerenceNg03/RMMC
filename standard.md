# Rust Minus Minus (R-\-) Standard

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

#### 1.3 Pointer type

**\*** is used to mark a pointer type;
```rust
let a: i32 = 1;
let b: i32* = &a;
```
#### 1.4 Array type

**[typename, size]** is used for mark an array type.
```rust 
let array: [i32, 3] = {1,2,3};
let string: [char, ] = "Hello, world.";
let array2: [i32, ] = {1,2};
```

#### 1.5 Function type

**(T1, T2)->T3** defines a function type. Function parameters are default to be **immutable**. Use **mut** keyword to mark them as mutable.

```rust
# foo takes an i32 and a char as input and returns a boolean value
let foo: (i32, char)->bool = <a: i32, b: char; bool>{
	return a==b;
}; # assign a function literal to a function named "foo"

# inc can be changed later
# parameters a is mutable
var inc: auto = <mut a: i32>{
	a = a+1;
	return a;
}

# mutable parameters does not affect type check
inc = <a: i32>{ return a; } #ok
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

## 3. Functions and variables

#### 3.1 Variable declaration

All variables are **mutable**.  
**let** keyword is used for declaration. Type is **not optional**.  
"**;**" must be added at the end.

```rust 
let a: i32; # declaration
let b: i32 = 32; # declaration and initialization
let c: auto = 'c'; # use auto keyword
let d = 32; # Illegal
```

#### 3.2 Function declaration

Functions in Rust Minus Minus is treated as a normal data type. Thus it also use **let** keyword to define.

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
	let meow: ()->void = <void;void>{};
};

let main: auto = <;i32>{
	meow(); # error
	cat::meow(); # ok

	<;>{
		let meow: auto = cat::meow();
		meow(); # ok
	};

	<;>{
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


#### 5.2 Grammar

Every statement must be terminated by a "**;**".

#### 5.3 Comments

**#** is used to mark a single line comment.

```python 
# This is a line of comment. 
```

#### 5.4 Main function

A function called as "**main**" and has type of "**(i32, char\**)->i32**" is required as the entry point for the program.

```rust
let main: auto = <argc: i32, argv: char**; i32>{
	return 0;
}
```
