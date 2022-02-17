# 函式呼叫

## 前言

看起來就是 call function 簡單的東西，也是可以充滿學問的。看完這邊你應該知道

- calling convention
  - stack(-based) buffer overflow 攻擊
  - Return-oriented programming (ROP) 攻擊
- application binary interface (ABI)
- stack 是什麼 heap 是什麼?
- stack(-based) buffer overflow 攻擊?
- Return-oriented programming (ROP) 型態的

實作

- calling convention 的熟悉
- C 程式如何處理函式呼叫、跨越函式間的跳躍 (如 setjmp 和 longjmp)

## 議題

### function prototype

早期 C 語言沒有規範一定要使用 function prototype

**什麼是 function prototype?**
在呼叫 funciton 之前，先定義這個 function 的

```c
int foo(int a, int b);  // function prototype

int main(void){
    printf("%d\n",foo());
}

int foo(int a, int b){
    // function foo 實作
}
```

**使用 function prototype有什麼好處?**

- 現代的編譯器會幫忙檢查

### 從 c code 到執行檔

這中間

原來 C preprocessor 以獨立程式的形式存在，所以當我們用 gcc 或 cl (Microsoft 開發工具裡頭的 C 編譯器) 編譯給定的 C 程式時，會呼叫 cpp (伴隨在 gcc 專案的 C preprocessor) 一類的程式，先行展開巨集 (macro) 或施加條件編譯等操作，再來才會出動真正的 C 語言編譯器 (在 gcc 中叫做 cc1)。值得注意的是，1972-1973 年間被稱為 “Very early C compilers” 的實作中，不存在 C preprocessor (!)，當時 dmr 等人簡稱 C compiler 為 cc，此慣例被沿用至今，而無論原始程式碼有幾個檔案，在編譯前，先用 cat (該程式的作用是 “concatenate and print file”) 一類的工具，將檔案串接為單一檔案，再來執行 “cc” 以便輸出對應的組合語言，之後就可透過 assembler (組譯器，在 UNIX 稱為 as) 轉換為目標碼，搭配 linker (在 UNIX 稱為 ld) 則輸出執行擋。

因此，在早期的 C 語言編譯器，強制規範 function prototype 及函式宣告的順序是完全沒有必要的，要到 1974 年 C preprocessor 才正式出現在世人面前，儘管當時的實作仍相當陽春，可參見 dmr 撰寫的〈The Development of the C Language〉，C 語言的標準化則是另一段漫長的旅程，來自 Bell Labs 的火種，透過 UNIX 來到研究機構和公司行號，持續影響著你我所處的資訊社會。

在早期的 C 語言中，若一個函式之前沒有聲明 (declare)，一旦函式名稱出現在表達式中，後面跟著 ( 左括號，那它會被解讀為回傳型態為 int 的函式，並且對它的參數沒有任何假設。但這樣行為可能會導致問題，考慮以下程式碼:
