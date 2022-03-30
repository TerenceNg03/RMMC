# Rust Minus Minus (R-\-) Standard

## 1. Types

#### 1.1 Built-in types

These types are built-int types.

```rust
i32 : 32-bit integer
char/u8 : 8-bit unsigned int
bool : boolean value
f32 : 32-bit float point
f64 : 64-bit float point
```
#### 1.2 Type casting

Use operator **(typename)** to cast. Implicit cast is allowed.
```rust
let a: i32 = 'c';
```

#### 1.3 Pointer type

**\*** is used to mark a pointer type;
```rust
let a: i32 = 1;
let b: *i32 = &a;
```
#### 1.4 Array type

**[  ]** is used for mark an array type.
```rust 
let array: i32[3] = {1,2,3};
let string: char[] = "Hello, world.";
let array2: i32[] = {1,2};
```

#### 1.5 Function type

**(T1, T2)->T3** defines a function type.

```rust
# foo takes an i32 and a char as input and returns a boolean value
let foo: (i32, char)->bool = <a: i32, b: char; bool>{
	return a==b;
}; # assign a function literal to a function named "foo"
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

## 4. Keywords, Grammar and trivial stuffs

#### 4.1 A list of keywords and operators

Keywords 

```python
let # declare a variable
for # not used 
while # while loop 
void # void type 
auto # auto type
nullptr # Null pointer (zero)
if else elif # branch control
i32 u8 char f32 f64 bool #built-int type 
true false # boolean values
```

Operators  

The same as [C programming language](https://en.cppreference.com/w/c/language/operator_precedence).

#### 4.2 Grammar

Every statement must be terminated by a "**;**".

#### 4.3 Comments

**#** is used to mark a single line comment.

```python 
# This is a line of comment. 
```

#### 4.4 Main function

A function called as "**main**" and has type of "**(i32, char\**)->i32**" is required as the entry point for the program.

```rust
let main: auto = <argc: i32, argv: char**; i32>{
	return 0;
}
```
