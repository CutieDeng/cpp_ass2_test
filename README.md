# C++ Assignment 2 测试框架

## 如何使用

将你的代码文件 *assign2.cpp* 复制至该目录下，并在此运行命令：

### Windows （非 WSL）

```shell
g++ -std=c++2a test.cpp -o test.exe
.\test.exe
```

### Mac, WSL, Linux

```shell
g++ -std=c++2a test.cpp assign2.cpp -o test.out && ./test.out 
```



---

## 如何分析测试结果

### 框架自测试

前几次测试为框架自测试，负责对本框架的测试正确性能力进行测试，以及能否向标准输出流输出测试信息、测试结果等内容。

其中包括以下的测试内容：

- 「测试通过」输出测试
- 「测试失败」输出测试
- 内存泄漏检测测试
- 重复释放内存测试
- std::exception 系列异常抛出测试
- std::string 异常抛出测试
- `new tree_node[]` 调用测试
- **环境检测测试**
- Segmentation Fault 测试



在完成上述所有测试后，你应当检查这些测试是否都输出了理想的结果。

:warning: 如果你的代码在 *Segmentation Fault 测试* 中不幸 dump 了，请进入 `test.hpp` 找到其对应的测试方法，将其完全注释掉以使得框架能正常运转。

如果有新的需要留意的框架自测试代码，欢迎提交 pull request. 



### Ass2 实现代码测试

具体的测试代码随着库版本的可能不如框架自测代码那样稳定，便不具体逐一介绍。

你可以通过标准输出流自行阅读具体测试点的通过情况。

由于本框架其实并不建议测试者在没有通过测试的情形下通过源码来寻找 bug, 因此建议在测试过程中便输出足够的调试信息，以便进行调试。



---

## 如何编写测试

### 测试文件规范

如果你希望向该测试框架中新增测试，请遵守以下规范。

- 所有的测试代码都应当在 *test.hpp* 文件中。

- 所有的测试都以模版方法的形式组织， 你只需要新增一个方法签名为 

  ```C++
  template <> r_type test<__COUNTER__>() {}
  ```

  的方法，并在大括号里填写你的具体测试逻辑，你就可以在运行的代码中看到它。



这里是一个测试方法的样例。

```C++
template <> r_type test<__COUNTER__>() {
  std::cout << "Hello World\n" << std::endl; 
  return {}; 
}
```



尽管你可以在任意位置添加你的 `test` 方法，但你必须遵守这样两个规范：

- 不要在任何其它地方使用 *MACRO __COUNTER__*. 
- 请务必保证该方法有返回值。



<u>相信我，你的编译器会在你不听话的时候教训你的。</u>



### 测试方法返回值

正如你看到的方法签名一样，测试方法接受一个返回值，表示测试结果。

不同情况你应当返回不同的内容：

- 当你认为本次测试没有错误，应当汇报测试通过时，你应当使用 `return {}; ` 表示测试通过。
- 当你认为本次测试不成功，有出乎意料的结果出现，你应当使用 `return "Some thing you want to talk about"; ` 或定义一个 `std::string s; ` 并返回它：`return s; `. 



:warning: `return "";` 对本测试框架来说依旧表示的是测试失败，请不要误以为它能表示测试通过。



### 测试方法执行顺序

原则上，所有的测试方法都应当独立且互不相关。

请不要制造出不同执行顺带来不同结果的逻辑。

你不必定义任何 `static` 变量，更不允许定义 global 语境下的变量。没有任何理由值得你这样做！

所有的变量请定义在堆栈内。



在本框架下，各测试方法将会根据其在 *test.hpp* 中的顺序依次执行，输出内容，并执行结果。



### 测试代码规范

当你想要自己新增新的测试代码时，你应当留意以下几个规则：

原则上，本框架不希望有内存泄漏的情形出现，所以对于 `tree_node` 有着更严格的内存监近控。

如果一个测试中有没有释放的 `tree_node` 实例，当测试方法返回后——代码执行逻辑重回框架的操纵后，框架将会将这些实例释放掉——即，不会真正造成内存泄漏。



#### 内存约束规范

但由于如 BST 及其它类型意义不大——框架没有对其实现额处的监控，所以为了避免其出现 *momery leak*, 请不要在堆中为它们开辟内存空间。

<u>被本 repository 接受的代码会先经过此方面的严格审核。</u>

当你想要执行下面这样的代码逻辑时：

```C++
BST *bstp = new BST; 
invoke_a_method(bstp); 
```



不妨使用如下代码逻辑代替：

```C++
BST bst; 
invoke_a_method(&bst); 
```



#### 返回值规范

请留意：无论是函数返回语句，还是异常抛出语句，都是一种对原有代码执行结构的变化。

例如，当你写出这样的代码：

```C++
template <> 
r_type test<__COUNTER__>() {
  tree_node *node = nullptr; 
  int *child_direction = new int; 

  assign2_exception::exception e = 0; 
  e |= judge_child_direction(node, child_direction); 
  if (e != 1) {
    return "Error in part 2, case 1! \n"; 
  }
  delete node; 
  delete child_direction; 
  return {}; 
}
```



在条件 $e \ne 1$ 满足时，该方法将会返回，其后两句 `delete node`, `delete child_direction` 不会被执行到——将导致 *memory leak*. 



> 我知道很多人在学 C++ 的时候，听别人说指针很难不信，自己一学发现很快就上手了，觉得别人言过其实。
>
> 但上述这段代码便是我从其他同学的代码里借鉴修改而来——他原本的代码则是少了一句 `delete` 操作。
>
> 而像这样内存泄漏的错误，我粗读一遍，便能数出超过 10 处。
>
> 总而言之，**善游者溺，善骑者堕。**
>
> 请各同学在用指针前，不妨多想想，到底有没有必要。



返回值在测试方法中用来表示测试失败的直接原因——但如果你不喜欢这种方式，你也可以通过抛出一个 `std::runtime_error` 来达成同样的目标。

不过值得注意，这二者框架会有（没区别的）区别对待哦。





### 待测代码规范

待测代码指的是你自己实现的 *assign2.cpp* 代码。

本框架对待测代码有如下的约束，以便对代码进行测试，请自行检查是否遵守。

- 代码中仅允许包含对 `std::exception` 系列异常的抛出语句，你不应抛出任何除此之外的异常。
- 代码中不应当有出现 `new BST` 的操作。（按理说也不会有）
- 代码中如果要在超越栈生命周期语境下构造对象 `tree_node`, 只能使用 `new tree_node` 系列语句，不应当使用 `malloc`, `placement new`, 及其余带参 `new` 运算符。
  （如果你不理解，那么你就不必担心触犯此条）



> 在此我需要对 `std::exception` 系列异常进行更详细的解释。
>
> 此处指的是自定义或标准库定义的以 `std::exception`  为父类的异常类实例。
>
> 在本次 assignment 中，*assign2_exception.hpp* 所定义的类型 `assign2_exception::exception` 不在此列！请留意。
>
> 它只是一个 uint32_t 的别名罢了，甚至你可以对它做加减运算！



### 测试结果（错误信息）说明

以下是对错误信息汇报的更详细说明：

- 当程序出现禁止的代码调用（`new tree_node[]`, repeatedly `delete` a `tree_node`, 或 `delete[] tree_node` 操作），框架会退出本次测试方法的执行并回报相关的测试信息作为提示——这往往是由于错误的测试代码造成的，而不是错误的库代码！请慎重编写测试代码！
- 当程序正常执行 `test` 方法完毕，将会获得其返回值（`std::string` 类型）。若返回值不为空，则回报其返回值作为错误原因。注意，使用 `return {};` 来描述该 `test` 方法的正确执行，而不是使用 `return "";`. 
- 当程序有内存泄漏的情形发生时，即对于 `tree_node` 在堆空间的开辟的所有内存空间没有在本次 `test` 方法结束前全部释放，则判定为内存泄漏。`BST` 则不纳入内存泄漏的监控范围。（因为懒

**错误信息的汇报优先级从上至下递减。**

测试程序不会一次性汇报多个错误。



## 测试工具

本框架实现了一些基本的工具以便于开发者更好的编写测试。随着版本更新，此版内容也会尽快更新。



### 错误码格式化方法

该方法在 *test.hpp* 中被定义如下：`std::string transfer_exception(assign2_exception::exception e)`. 

你可以传入一个 `uint32_t` 并从中获得对应的 `std::string` 描述——用以描述该错误码对应的异常类型。

你会在插入失败时得到一个抛出的 `std::runtime_error`. 





### 错误码比对方法

该方法在 *test.hpp* 被定义：`r_type check_exception(exception actual, exception expect)`. 

你可以传入两个异常类型，便能快速得到一个 `r_type` 类型的返回值——以便于你直接将其返回——该方法在 actual 与 expect 不匹配时返回一串足够详细的信息以便他人分析自己的实现代码错误。

如下的代码可以帮助你了解 `r_type` 的一点用法：

```C++
r_type result; 
if (result) {
  // result 描述了错误信息。
  return result; 
} else {
  // 此时 result 里没有错误信息，等价于 return {}; 
  return {}; 
}
```



上述代码和 `return result;` 完全等价。



### 字符串格式化方法

该方法为 `format (the original string, ... all object can be transfer to a string)`. 

通过该方法，你可以快速构建一个内容错落有序的字符串信息。

该方法类似 `printf`, 但你统一地使用 `{}` 来表示你希望将你的对象信息格式化后插入到哪即可。

例如：`format ("{} {}{}", "Hello", "World", "\n");`. 

目前支持的对象格式化有：一般的基本类型；`tree_node` 类型。





### 获取该子树的大小

方法签名：`uint32_t get_node_size(tree_node const &)`. 

该方法会根据该点的左儿子、右儿子的信息来计算其子树大小情形！

你可以使用 `get_node_size(node) == node.tree_count` 来判断该实现代码是否正确的计算出了 `tree_count` 的相关信息。







### 移除 BST 所有节点方法

方法签名：`void destruct_tree(BST &bst)` 

由于通过 `insert_data` 得到的变长数组来进行内存的释放使用不便，并且存在内存泄漏的风险，所以特此增加此方法来回收树上所有节点的内存。

该方法会在清空树上所有节点时将该树的 `root` 置为 `nullptr` 以保证信息的一致性。





### 获得树上数据数方法

方法签名：`uint32_t size_of_tree(BST &)`

单纯通过根节点信息获取树的内容大小，没啥用的鸡肋方法——但可能你们用得上，我就写了。





### 树结构检查方法

方法签名：`r_type check_bst(BST const &);` 

该方法将会检查树的结构是否存在错误：

- 各结点信息关系内容不一致。
- 树比较器信息与点关系不一致。
- `tree_count` 计算结果不一致。





:smile_cat: 待实现的方法：树深度计算方法



### 比较器函数

- `compare_std` 从小到大顺序比较器
- `compare_reverse` 逆序比较器



---

Author: Cutie Deng

Mail: Dengzr2020@mail.sustech.edu.cn

欢迎致信询问更多内容。

















# C++ Ass2 测试框架 (旧版)

使用方式：

将你的代码文件 *assign2.cpp* 复制到该目录下，并在该目录下运行该命令：

```shell
g++ -std=c++20 test.cpp assign2.cpp -o test.out && ./test.out 
```

便可执行该测试。

对于没有直接使用 Windows 而没有使用 WSL, mac, Linux 的平台编译器，可能会因编译器没有支持 `inline` 的合并变量语义而导致代码链接失败，所以 Windows 平台下的同学请使用以下代码执行测试。 

```shell
g++ -std=c++2a test.cpp -o test.exe
.\test.exe
```





---

由于这个框架是一拍脑子写的，可能有点凌乱。

下面是该框架所遵守的约定：

- 当你通过堆内存构建生命周期不便控制的 tree_node 的结点时，应当使用 `new tree_node` 进行对象的创建。其它方法都不应当使用：使用 `malloc` 和 `placement new` 都会破坏该框架对 `tree_node` 对象的监视能力，导致对代码的正确性发生错误判断；使用 `new tree_node[]` 构建对象数组在本框架当前版本同样被禁止。
  本框架能够回收满足该约定的所有内存泄漏，并中止错误的 `delete` 方法运行。
- 在你的 `assign2` 实现方法中不应当出现未 handle 的异常控制，或 throw 出不继承自 `std::exception` 的异常。特别强调，不应当使用 `std::string` 作为异常的类型——因为我的框架已经用了它了。
  否则其造成的程序测试分析错误我不负责。



---

由于本框架原本只是作为一个实验性玩具，所以测试内容还有待补充。

下面是对开发者的讲解：

你只需要在文件 `test.hpp` 中补充你的测试单元，既可在运行中看到它。

操作如下：

在最后的代码 （见下文）上面填写你的模版方法 `r_type test<__COUNTER__>()` 的内容，便可看见它的运行结果。

```C++
namespace {
	constexpr int test_number {__COUNTER}; 
}
```



你可以观察我写的各测试 demo 来获得更多的启发。

请不要在其它任何一个地方再次用到 MACRO `__COUNTER__`. 

关于返回值，如果本次测试没有异常，建议使用 `return {};` 表示测试通过。

值得注意的是，即使程序执行到 `return {};`，程序并非就一定会汇报测试通过——它会在这之后进行内存泄漏的相关检查！

而当你显式认为本次测试有失败，你希望给出一点错误的信息汇报，你可能通过 `return "错误信息"` 来达成你的目标。



---

以下是对错误信息汇报的更详细说明：

- 当程序出现禁止的代码调用（`new tree_node[]`, repeatedly `delete` a `tree_node`, 或 `delete[] tree_node` 操作），框架会退出本次测试方法的执行并回报相关的测试信息作为提示——这往往是由于错误的测试代码造成的，而不是错误的库代码！请慎重编写测试代码！
- 当程序正常执行 `test` 方法完毕，将会获得其返回值（`std::string` 类型）。若返回值不为空，则回报其返回值作为错误原因。注意，使用 `return {};` 来描述该 `test` 方法的正确执行，而不是使用 `return "";`. 
- 当程序有内存泄漏的情形发生时，即对于 `tree_node` 在堆空间的开辟的所有内存空间没有在本次 `test` 方法结束前全部释放，则判定为内存泄漏。`BST` 则不纳入内存泄漏的监控范围。（因为懒

**错误信息的汇报优先级从上至下递减。**

测试程序不会一次性汇报多个错误。



---

尽管我尝试了很多办法，但似乎 C++ 的程式没有符合标准、通用的语法能够让其从 `segmentation fault` 错误中恢复。

如果可以，我希望有能人能为该测试框架加上对该错误的正确处理。

由于暂时不能处理该问题，所以测试者需要严格留意测试过程中自己的代码是否有不经空指针检验就直接访问对应的对象成员的情形。

请加上严格的测试条件，以避免测试程序不能完全执行完毕。

此外，你可以选择在自己的实现（也就是  `assign2.cpp` ）中在面对难以处理的情形下——将一个 `std::string`  丢出以获得本框架的支持。

**这不太好，但我允许你这么做。**

我会在一个 test example 中写一段示范代码来展示这个特性。

或者参考下面这段语法：（我希望丢出的内容是：今天阳光灿烂。）

```C++
throw std::string {"今天阳光灿烂"}; 
```



---

新版更新！

<div align="right">Sat Apr 2 10:32:03 CST 2022</div>

于本机平台框架能从 segmentation fault 中恢复了！

本机所用的编译器版本：

```
Apple clang version 13.1.6 (clang-1316.0.21.2)
Target: arm64-apple-darwin21.4.0
Thread model: posix
```



其它平台有待测试。



---

新的支持加入：

- 对于继承自 `std::exception` 的异常，本框架能够将其捕获并输出其造成错误的原因。



由于新支持的加入，我给出以下的测试代码、实现代码的建议。

在测试代码中，你可以使用 `throw std::string` 和 `throw std::runtime_error` 等方式进行异常的抛出处理。

但你应只使用 `catch std::runtime_error` 处理后一种异常（如果你喜欢），前一种异常原则上你不允许尝试捕获（但其实你可以转发它）。

由于异常抛出会导致代码执行顺序的错乱，建议请不要使用 `new` 语句进行 `BST` 对象的创建，而是直接在栈上构建。

示例代码：

```C++
template <> 
r_type test<__COUNTER__>() {
  BST bst {}; // 使用 {} 指示编译器对其进行强制初始化。
  
  tree_node *t; 
  auto error_code = inserted_into_BST(&bst, 520, &t); 
  
  // 执行你的测试代码，例如
  if (error_code == 0) 
    return "成功在没有初始化比较器的二叉搜索树上插入新节点。"; 
 	// ... 
}
```



---

Author: Cutie Deng

Mail: Dengzr2020@mail.sustech.edu.cn

欢迎致信询问更多内容。