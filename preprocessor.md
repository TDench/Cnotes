# C Preprocessor

## 什麼是Preprocessor ?

C的Preprocessor ，會在程式compiled之前，先執行。他會完成的任務如

- inclusion 其他檔案
- 定義 symbolic constants 或 macros
- conditional compilation of program code
- conditional execution of preprocessor directives.

一般來說是 # 開頭的， 用 /**/ 寫comment。C大概是有擁有最多legacy code的程式了，當一個專業的C 程式員，你會遇到很多年前寫的code要怎麼辦的問題，這章節會教你怎麼解決這些問題，然後有一些新的技術可以換掉那些舊程式碼。

## 本文英文對照

Preprocessor = 前處理器
Directive = 指令

## #Include 前處理器指令

Preprocessor Directive 前處理指令。我們在前面用到很多include的概念了，通常有分兩種

```c
#include <stdio.h>
#include "userdefined.h"
```

- 如果是用<>括號起來的。  
  代表他是standard library headers。會依照系統或安裝環境不一樣，他會去找到他相對應的檔案在哪裡。
- 如果是用 "" 括號起來的。  
  代表這個是user 自己定義的header檔案，他會先搜尋同一個目錄下有沒有這個檔案。如果再current directory沒有照到的話，他會去搜尋是先定義好的或這是系統的位置。這些header檔案通常會包含
  - structure and union 的宣告
  - typedef
  - enumerations
  - function prototypes.

## #define 的功能

定義以下這些

- 常數 (Symbolic Constant)

-

### #define 一個 Symbolic Constant

可以用#define這個 directive 創建一個symbolic constant。把一個常數代表程一個符號。用法如下

```c
#define PI 3.1415926
```

- 通常來說只會用大寫跟_  來命名。

在空格之後的東西都會拿來取代，如果今天打成`3.1416.`，以後取代之後，都會出現一個點，這個要十分小心。最好的方法是用 `const double PI = 3.1415;` 如果你有多的記憶體空間的話。

### #define一個Macro

macro可以不要argument，但這樣看起來像定義一個常數。這個arguments會被塞到文字裡面，然後expanded。

```c
#define CIRCLE_AREA(x) ((PI)*(x)*(x))

area = CIRCLE_AREA(4);
area = ((3.14159) * (4) * (4));  // expanded 成這樣
// 然後在compile運算。
```

也就是說寫成CIRCLE_AREA(x) 在compile前會展開成。

記得要塞括號，因為它就只是文字取代的功能，如果這樣子的話

```c
area = CIRCLE_AREA(c + 2);
area = ((3.14159) * (c + 2) * (c + 2)); // 有掛號的話。
area = 3.14159 * c + 2 * c + 2; // 如果沒有掛號的話
```

基本上這個東西就是跟文字取代一樣的功能。所以不要對它太期待他會有智慧的運算。現在很少用inline的 function call了。以前這個東西是定義為了減少function call的。

那如果我需要兩個argument呢

```c
#define RECTANGLE_AREA(x, y) ((x) * (y))
rectArea = RECTANGLE_AREA(a + 4, b + 7);
rectArea = ((a + 4) * (b + 7)); // 這樣就會自動展開成這樣
```

### 如果你的Macro太長，可以使用 \  延長

```c
#define do_two_stuff \
  { \
    do_stuff_here \
    do_more_stuff \
  }
```

### 如果想要刪除define過的東西，可以用#undef刪除

### 如果Express會改到輸入的參數的話，不要用macro

有時候standard library 的 function 會被定義成。例如stdio.h 裡面的

```c
#define getchar() getc(stdin)
```

## Conditional Compilation

preprocessor 的directives也是可以control的。例如

```c
#if !defined(MY_CONSTANT)
#define MY_CONSTANT 0
#endif

// 還有
#ifdef
#ifndef

#if 
#elif
#else
#endif
```

通常是拿來檢查，避免header 被重複included。

也有一些無聊的用途，例如拿來當Comment Out

```c
#if 0
 隨便亂寫
#endif
```

可以拿來DEBUG

```c
#ifdef DEBUG
printf("Variable x = %d\n", x);
#endif
```

## #error

```c
#error tokens
#error 1 - Out of range error 
// 這樣寫有 6個token

#include <stdio.h>
#define PI 2.0

#ifndef PI
#error you should includ PI
#endif

#define CIRCLE_AREA(x) ((PI) * (x) * (x))

int main()
{
    printf("%f", CIRCLE_AREA(3));
}
```

## #pragma directive

編譯指示 #pragma 是用來告知編譯器某些特殊指示，例如不要輸出錯誤訊息，抑制警告訊息，或者加上記憶體漏洞檢查機制等。這些指示通常不是標準的 C 語言所具備的，而是各家編譯器廠商或開發者所制定的，以便讓編譯器可以具有某些特殊的選項。

## # and ## Operators

== #x 代表放在一個string 的意思==

```c
#define HELLO(x) puts("Hello, " #x);

HELLO("John")
puts("Hello, " "John");
```

 那個## 就是把兩個連在一起的意思

```c
#define TOKENCONCAT(x, y) x ## y
TOKENCONCAT(O, K)  //就是 OK

```

## #Line Numbers

這個 #Line 會告訴 compiler 幫忙記得，接下來那行是第幾行

例如:

```c
#line 40
    printf("%d", __LINE__); 
// result : __LINE__ 40 
```

## 一些已經被定義好的符號

```c
__LINE__
The line number of the current source-code line (an integer constant).
__FILE__
The name of the source file (a string).
__DATE__  
(a string of the form "Mmm dd yyyy" such as "Jan 19 2002")
__TIME__
The time the source file was compiled (a string literal of the form "hh:mm:ss").
__STDC__
The value 1 if the compiler supports Standard C; 0 otherwise. Requires the
compiler flag /Za in Visual C++.
```

## Assertions 斷言

可以拿來檢查哪裡有bug。assert macro是定義在 assert.h 裡面的。如果出來的結果是 false(0) ，那assert就會print出 error然後 abort ( abort 是一個 stdlib.h 裡面的 function)。來中止程式。
