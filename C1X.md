# ISO 9899:201x 翻譯

## Introduction

- 有些功能已經逐步廢棄了，沒有被刪掉是因為這個功能被廣泛的使用。請不要拿這些功能來寫程式。[6.11] [7.31]

- 這份 C1X ISO 文件可以分成四個主要的部份
  - preliminary elements (clauses 1-4)
  - the characteristics of environments that translate and execute C programs (clause 5);
  - the language syntax, constraints, and semantics (clause 6);
  - the library facilities (clause 7).

- 會提供
  - Examples 描述各種可能的形式，
  - Footnotes 強調這個rule的結果，或這東西在其他哪裡出現
  - References refer to other related subclauses.
  - Recommendations 給一些實作的建議
  - Annexes 提供更多的資訊跟總結
  - bibliography 誰對這個 ISO文件有貢獻

5 The language clause (clause 6) is derived from ''The C Reference Manual''.

6 The library clause (clause 7) is based on the 1984 /usr/group Standard.

## Scope

這份文件專注於定義 C 語言的程式，並且定義

- C 語言的 representation
- C 語言的文法(syntax) 與限制
- C 語言的語意(semantic)規則，跟如何編譯(interpreting)
- input 如何被 C 語言處理
- output 如何被 C 語言處理
- 實作上會遇到什麼限制(restrictions)

這份文件已下無關

- 資料處理系統(data-processing system)中，C語言被transformed的機制
- 資料處理系統(data-processing system)中，C語言被invoked的機制
- input 如何被 C 語言處理的機制
- output 如何被 C 語言處理的機制
- 程式的大小與複雜度

備註:

- 這個 ISO 標準是為了要，推廣所謂的跨平台的C語言程式(portability)
- 英文中的 data-processing systems 應該就是這種可以跑 C語言的平台

## 名詞定義(Terms, definitions, and symbols)

- 這一個章節會定義各種名詞。
- 沒有被定義到的名詞要去 ISO/IEC 2382-1 找答案。
- 沒有被定義到的數學符號要去  ISO 31-11 找答案

### access [3.1]

讀取或修改 object 的值

```c
<execution-time action> to read or modify the value of an object
```

重點

- 讀取(read) 跟修改(modify) 只能是其中一個
- 輸入跟之前一樣的值，這個也叫做modify
- Expressions that are not evaluated do not access objects. [QM]什麼意思

### alignment [3.2]

具有特定型態的物件，以某個byte的倍數作為記憶體的排列邊界

```c
requirement that objects of a particular type 
be located on storage boundaries with addresses 
that are particular multiples of a byte address
```

> **不負責的解說:**
> 就是 struct abc {int a, char b} 記憶體排列的意思

### argument [3.3]

也叫做

- actual argument
- actual parameter 已經被棄用了。

這個專指一個用逗號分開的列表，這個列表會被括號包圍。

- 這個括號會放在function call的後面
- 或是 preprocessing tokens，在 function like 的 macro 後面

> **不負責的解說:**

```c
int func(int a, int b, int c)
#define ADD_MACRO(x,y,z) ((x)+(y)+(z))
```

這邊 a, b, c, x, y, z 都是叫做 argument

### behavior[3.4]

外在的表現或是行為

```c
external appearance or action
```

可以分成

- **implementation-defined behavior [3.4.1]**
  - unspecified behavior where each implementation documents how the choice is made
  - 例如， signed integer 向右邊移動的時候，要補1還是補0 這種問題
- **locale-specific behavior [3.4.2]**
  - behavior that depends on local conventions of nationality, culture, and language that each implementation documents
  - 例如，islower 這個功能，輸入中文字之後要回傳 true 還是 false ?
- **undefined behavior[3.4.3]**
  - behavior, upon use of a nonportable or erroneous program construct or of erroneous data, for which this International Standard imposes no requirements
  - NOTE Possible undefined behavior ranges from ignoring the situation completely with unpredictable results, to behaving during translation or program execution in a documented manner characteristic of the environment (with or without the issuance of a diagnostic message), to terminating a translation or execution (with the issuance of a diagnostic message).
  - 例如，當 integer overflow 的時候，會有什麼行為?
- **unspecified behavior[3.4.4]**
  - 未指定的值，或是未指定的行為，指的就是 ISO 文件中提供兩個或多個以上的實作，並且沒有強制要求一定要使用哪一種實作(instance)
  - 例如，function 的 arguments 要從哪一個開始評估(evaluated)

### bit [3.5]

- 在執行環境中的一個資料儲存的單位。
- 大小剛好可以儲存一個物件。
- 可能可以讓物件表達出 1 或 0 這兩個數值

```c
unit of data storage in the execution environment 
large enough to hold an object that may have one of two values
```

2 NOTE It need not be possible to express the address of each individual bit of an object.

### byte[3.6]

```c
addressable unit of data storage 
large enough to hold any member of the basic character set 
of the execution environment
```

2 NOTE 1 It is possible to express the address of each individual byte of an object uniquely.

3 NOTE 2 A byte is composed of a contiguous sequence of bits, the number of which is implementation- defined. The least significant bit is called the low-order bit; the most significant bit is called the high-order bit.

### character[3.7]

```c
<abstract> member of a set of elements 
used for the organization, control, or representation of data
```

根據大小，有分成

- character [3.7.1]
  - single-byte character <C> bit representation that fits in a byte
  - 剛好是一個 byte 的大小
- multibyte character [3.7.2]
  - sequence of one or more bytes representing a member of the extended character set of either the source or the execution environment
  - 連續的一個或多個bytes 的大小
  - basic character set 被包含於 extended character set
- wide character [3.7.3]
  - value representable by an object of type wchar_t, capable of representing any character in the current locale

### constraint [3.8]

限制。有可能是語法上(syntactic)或語意上(semantic)的限制

```c
restriction, either syntactic or semantic, 
by which the exposition of language elements is to be interpreted
```

### correctly rounded result [3.9]

根據現在的rounding mode，與format最接近的數值，這個數值會有指定的範圍與精準度

```c
representation in the result format that is nearest in value, 
subject to the current rounding mode, 
to what the result would be given unlimited range and precision
```

### diagnostic message [3.10]

一個實作輸出的訊息

```c
message belonging to an implementation-defined subset of 
the implementation's message output
```

### forward reference[3.11]

```c
reference to a later subclause of this International Standard that 
contains additional information relevant to this subclause
```

### implementation[3.12]

一個特別的軟體。運行在某個translation environment

```c
particular set of software, 
running in a particular translation environment under particular control options, that 
performs translation of programs 
for, and supports execution of functions in a particular execution environment
```

### implementation limit[3.13]

軟體實作上的限制

```c
restriction imposed upon programs by the implementation
```

### memory location[3.14]

有兩種可能
1 memory location
either an object of scalar type, or a maximal sequence of adjacent bit-fields all having nonzero width
2 NOTE 1 Two threads of execution can update and access separate memory locations without interfering with each other.

3 NOTE 2 A bit-field and an adjacent non-bit-field member are in separate memory locations. The same applies to two bit-fields, if one is declared inside a nested structure declaration and the other is not, or if the two are separated by a zero-length bit-field declaration, or if they are separated by a non-bit-field member declaration. It is not safe to concurrently update two non-atomic bit-fields in the same structure if all members declared between them are also (non-zero-length) bit-fields, no matter what the sizes of those intervening bit-fields happen to be.

4 EXAMPLE A structure declared as

          struct {
                char a;
                int b:5, c:11, :0, d:8;
                struct { int ee:8; } e;
          }
contains four separate memory locations: The member a, and bit-fields d and e.ee are each separate memory locations, and can be modified concurrently without interfering with each other. The bit-fields b and c together constitute the fourth memory location. The bit-fields b and c cannot be concurrently modified, but b and a, for example, can be.
Contents

3.15
1 object
region of data storage in the execution environment, the contents of which can represent values

2 NOTE When referenced, an object may be interpreted as having a particular type; see 6.3.2.1.

Contents

3.16
1 parameter
formal parameter formal argument (deprecated) object declared as part of a function declaration or definition that acquires a value on entry to the function, or an identifier from the comma-separated list bounded by the parentheses immediately following the macro name in a function-like macro definition

Contents

3.17
1 recommended practice
specification that is strongly recommended as being in keeping with the intent of the standard, but that may be impractical for some implementations

Contents

3.18
1 runtime-constraint
requirement on a program when calling a library function

2 NOTE 1 Despite the similar terms, a runtime-constraint is not a kind of constraint as defined by 3.8, and need not be diagnosed at translation time.

3 NOTE 2 Implementations that support the extensions in annex K are required to verify that the runtime- constraints for a library function are not violated by the program; see K.3.1.4.
Contents

3.19
1 value
precise meaning of the contents of an object when interpreted as having a specific type

Contents

3.19.1
1 implementation-defined value
unspecified value where each implementation documents how the choice is made

Contents

3.19.2
1 indeterminate value
either an unspecified value or a trap representation

Contents

3.19.3
1 unspecified value
valid value of the relevant type where this International Standard imposes no requirements on which value is chosen in any instance

2 NOTE An unspecified value cannot be a trap representation.

Contents

3.19.4
1 trap representation
an object representation that need not represent a value of the object type

Contents

3.19.5
1 perform a trap
interrupt execution of the program such that no further operations are performed

2 NOTE In this International Standard, when the word ''trap'' is not immediately followed by ''representation'', this is the intended usage.2)

Footnotes

2) For example, ''Trapping or stopping (if supported) is disabled...'' (F.8.2). Note that fetching a trap representation might perform a trap but is not required to (see 6.2.6.1).

Contents

3.20
1 [^ x ^]
ceiling of x: the least integer greater than or equal to x

2 EXAMPLE [^2.4^] is 3, [^-2.4^] is -2.

Contents

3.21
1 [_ x _]
floor of x: the greatest integer less than or equal to x

2 EXAMPLE [_2.4_] is 2, [_-2.4_] is -3.
Contents
