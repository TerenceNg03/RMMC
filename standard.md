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

**\*** is used to mark a pointer type.  **&** is used to create a reference.
```rust
let a: i32 = 1;
let b: i32* = &a; # warning
var d: i32 = 1;
let e: i32* = &d; # ok
```
#### 1.4 Array type

**[typename, size]** is used for mark an array type.
```rust 
let array: [i32, 3] = [1,2,3];
let string: [char, ] = "Hello, world.";
let array2: [i32, ] = [1,2];
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

**(T1, T2)->T3** defines a function type. Function parameters are default to be **immutable**. Use **mut** keyword to mark them as mutable. Since function parameters are variables, they also have variable traits. Allowed traits are **ref**, **mut** and **unique**.

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

**comp** (short for **compound**) is used to compose a custom data type. Another custom type is **union**. See [Union Section](#7.-union-and-match) for details.
```rust
comp my_comp {
	ref a: i32;
	unique b: bool;
	fun: (i32, u32)->bool;
};

# declare as exportable
export comp my_comp2 {
	ref a: i32;	
};

# initialization
let i: i32 = 1;
let a: my_comp = my_comp {
	a = i;
	b = true;
	fun = <a: i32, b: u32; bool>{
		return a == b as i32;
	};
};
```

#### 1.7 Type Alias

**type** keyword is used for make an alias for a known type.

```rust 
type int i32; # alias int for i32

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

Variable must be initialized before being used. Otherwise will rise a compile error. It is possible to declare one and initialize it later. But for **Global variables** they must be initialized as soon as they are declared. 

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

let main: auto = <void ;i32>{
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

## 5. Lifetime, Reference and Auto memory managment

#### 5.1 Lifetime and Reference

The lifetime of a variable is defined as the scope where the variable is available.See [Rust's definition of lifetime](https://doc.rust-lang.org/rust-by-example/scope/lifetime.html).

In RMM, keyword **ref** is used to indicate that a variable is a reference. Mutable reference can only reference a mutable variable. A reference is like a pointer but it is **guaranteed to be always valid**.

```rust 
let a: i32 = 0;
let ref b: i32 = a; # ok
var ref c: i32 = a; # compile error
```

Reference is **a trait of variable**. That means it is not a type nor does it affect type checking. If a variable has this trait, it has some limitations.

 - Can not be moved as it does not has the ownership.
 - Return a reference will return the value. This is because reference is a variable trait and you can not return a variable.
 - Can not reference a immutable variable if the reference is mutable.
#### 5.2 The Reference Validator

To make sure every reference is valid. RMM use a reference validator that checks variable lifetime. A reference can only reference a variable that has a lifetime no shorter than the reference it self.

```rust 
# Invalid in rust
let main: auto = <void; i32>{
	var i: i32 = a;
	let ref r1: auto = a;
	var ref r2: auto = a;
}

```

Reference can not be referenced. Instead, assign a reference variable to a reference variable just duplicate itself.

```rust 
let inc: auto = <mut ref a: i32; void>{
	a = a+1;
};

# assign a to inc's parameter
let dummy: auto = <mut ref a: i32; void>{
	inc(a);

# Recursion
let recursive_fun: auto = <mut ref a: i32; void>{
	if(a>0){
		recursive_fun(a-1);
	}else{
		return a;
	};
};

let main: auto = <void; void>{
	var a: i32 = 9;	
	dummy(a);
	recursive_fun(a);
};
```
#### 5.3 Reference Validator's Algorithm

```
CHECKED_FUNCTION = {}

FUNCTION get_lifetime(var)BEGIN
	FOR all assgin as pass BEGIN
		IF(assigned to another reference r)BEGIN
			var.lifetime += r.lifetime
		END
		IF(passed to a function f as parameter para)BEGIN
			// Detect recursive call
			IF( f.para in CHECKED_FUNCTION )BREAK
			ELSE BEGIN
				ADD f.para to CHECKED_FUNCTION
				var.lifetime += get_lifetime(f.para)
			END
		END
	END
END

FUNCTION get_lifetime(ref) BEGIN
	IF ref is lvalue BEGIN // is a variable
		RETURN get_lifetime(var)
	END
	ELSE // return by a function BEGIN
		CASE: is function's local variable
			//not allowed to return by the function
			RETURN
		CASE: is passed by parameter
			RETURN get_lifetime(PARAMETER[i])
		CASE: is global variable
			RETURN get_lifetime(var)
	END
END

FUNCTION validate_ref(var, r)BEGIN
	IF(get_lifetime(var) >= get_lifetime(r))BEGIN
		RETURN true
	END
	ELSE BEGIN
		RETURN false
	END
END
```

#### 5.4 Transfer of ownership

**move** keyword is used to transfer ownership. Once a variable is moved, it can not be used again. What **move** does is that it rebind the value to another variable. Thus **move** is just a renaming (if move to another scope copy would be applied) and have zero overhead (given not moved to another scope).

```rust 
let main: auto = <void; void>{
	let a: i32 = 9;
	var b:i32;
	if(false){
		b = move a; # compile error : move before die
	};``
};

let correct: auto = <void; mut unique i32>{
	var unique a: i32 = 0;	
	return move a; # ok
};
```

A variable can only be moved when its lifetime ends since **move** will cause all reference to it become invalid. Otherwise, you should use a **union** to contain the value which can hold an empty value.

A **ref** can never be moved due to it does not have required ownership.

#### 5.5 Auto memory management

**unique** keyword is used to alloc memory on heap. **unique** variable can not be copied to another **unique** variable. Assign to a normal variable will copy the value. To transfer the ownership, use keyword **move**. Once the lifetime of a unique variable ends, its memory is freed.

```rust
let create_string: auto = <void; unique [u8, 9]>{
	let unique string: [u8, 9] = "Hello";
	return string; # compile error can not copy unique value
	return move string; # ok
};
```

**Note: If unique failed to alloc memory, it will terminate the program. If you need to prevent such behaviors, you can use `std::mem::alloc` to manually alloc memory. Then free it with `std::mem::free`. This should only be necessary for some embedding systems whose memory is extremely limited.**

## 6. Mutability

Mutability is **a trait of variable** and is **not** in **type system**. It is an undefined behavior to change a immutable variable's value by using a pointer. However, this is not recommended. Trying to get the address of immutable variable will cause a warning. Immutable pointers do can change the content. But immutable reference can not. All immutable variable must be initialized. **Mutability is preserved when [passed to a function](#1.5-function-type)**.

```rust
let a: i32; # ok
let b: i32 = 0; # ok
let c: *i32 = &b; # warning: trying to get the address of immutable variable
let d: &i32 = b; # ok
```

## 7. Union and Match

**union** and **match** keywords are used to create a union. A union is **internally tagged** to prevent undefined behavior. A union's member can only be accessed by **match** keyword which gets its value. By default match copy the value to a variable name the same as the union member. If use **move** on the variable, match will move the value and leave the union holds no value as it is not initialized.

```rust 
union my_union {
	unique a: i23;
	b: i32;
};

export union my_union2{
	a: i32;
};

let main: auto = <void; void>{
	var o: my_union; # This cause union hold no value
	var o: my_union = my_union {a: 32}; # alloc memory for a
	var i: i32;
	var ref r: i32;
	match (o) {
		a: {
			i = b; # compile error, b not valid in this scope
			i = a; # ok 
			r = a; # compile error can not reference a union member
		};
		move b: {
			# now o no longer holds b
			# it holds no value
		};
		: {
			# No value 
		};
	};
	o.b = 1; # union switch to b, a's memory is freed
}
```

## 8. Trivial stuffs

#### 8.1 Operators Precedence

Almost the same as [C programming language](https://en.cppreference.com/w/c/language/operator_precedence).

| Precedence | Operator | Associativity |
| :----: | :---- | :----: |
| 1 | **::** Scope selector | Left-to-right |
| 2 | **(  )**	Function call <br> **[  ]** Array subscripting <br> **. ->**	Member access| Left-to-right |
| 3 | **+ -** Unary plus and minus <br> **! ~** Logical NOT and bitwise NOT <br> **\***	Indirection (dereference) <br> **&** Address-of <br> **move** Move a variable| 	Right-to-left |
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

#### 8.2 Comments

**#** is used to mark a single line comment.

```python 
# This is a line of comment. 
```

#### 8.3 Main function

A function called as "**main**" is required as the entry point for the program. Main function's return type must be either **void** or **i32**. Its parameter list must either **i32, \*\*char** (can be immutable) or **void**. Main itself must be immutable.

```rust
let main: auto = <argc: i32, argv: **char; i32>{
	return 0;
};
```
