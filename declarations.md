# Declarations 聲明

這邊的說明來自於 C9X rationale，是個不錯的文件，有興趣的同學可以看看，這邊節錄一些我覺得比較特別的說明

## Structure and union specifiers

其實 bit fields 有三種

- `int` 會產生 implementation-defined signedness (同 K&R)
- `signed int` 會產生 assuredly signed fields,
- `unsigned int` 會產生 unsigned fields.

bit fields 在每個 word 的邊界會有一些限制，這些限制在 C9X 中會被放寬，因為不管這些限制也有很多 bit fields 的性質都可以被實做出來。

所以 structure 的 layout 應該符合以下限制

- 開頭沒有缺
- members occupy increasing storage addresses
- 如果有需要，把缺的部分擺在尾巴，讓 structure 有夠大的空間去pack
tightly into arrays 並且維持正確的記憶體 alignment.

```note
The layout of structures is determined only to a limited extent:
- no hole may occur at the beginning;
- members occupy increasing storage addresses; and
- if necessary, a hole is placed on the end to make the structure big enough to pack
tightly into arrays and maintain proper alignment.
```

### 可以拿 Structure 實作 variable-size array (C9X 新功能)

```c
struct s {
  int n_items;
  // possibly other fields
  int items[1];
};
struct s *p;
size_t n, i;
// code that sets n omitted
p = malloc(sizeof(struct s) + (n - 1) * sizeof(int));
// code to check for failure omitted
p->n_items = n;
// example usage
for (i = 0; i < p->n_items; i++) p->items[i] = i;
```

[QM] 等待測試

## Type qualifiers

C89 的時候加了 `const` 跟 `volatile`， C9X 的時候加了 `restrict`，這些東西單獨使用(或是合併使用)，可以規範 compiler 如何存取  object 的 lvalue

有這些 type qualifiers

- const
- volatile
- restrict

The syntax and semantics of const were adapted from C++; the concept itself has appeared in other
languages. volatile and restrict are inventions of the Committee; and both follow the
30 syntactic model of const.
Type qualifiers were introduced in part to provide greater control over optimization. Several
important optimization techniques are based on the principle of “cacheing”: under certain
circumstances the compiler can remember the last value accessed (read or written) from a location,
35 and use this retained value the next time that location is read. (The memory, or “cache”, is typically a
hardware register.) If this memory is a machine register, for instance, the code can be smaller and
faster using the register rather than accessing external memory.
The basic qualifiers can be characterized by the restrictions they impose on access and cacheing:
