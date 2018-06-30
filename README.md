# LaziLionComplier
## 要求
- 用lex写出一个类C或者类PASCAL或自定义语言的词法分析器，用YACC的分析方法完成对某一个的语法分析，并生成语法树和中间代码（如果生成目标代码：可加分）。 (25分)
- 实验目的：掌握词法分析、语法分析和代码生成方法。 

## 完成情况
1. [x] [语法树](https://www.lysator.liu.se/c/ANSI-C-grammar-y.html)(语法是这个网站中的简化版本，语法树见课本)
2. [x] IR tree（参见课本）
3. [x] 符号表(生命周期、类型检查）
4. [x] 可视化
5. [ ] 数组、指针
6. [ ] 错误恢复
7. [ ] 执行器（后端）

## 编译环境
<b style="color:red">bison包必须在3.0.x 版本或以上，2.x版本编译有问题。</b>
linux各种发行版应该都可以，mac上也没有问题。windows未测试。
## 编译这个项目
```sh build.sh```
结果会生成build/visualize.out文件，由于前端不是完整的程序，是一堆.o文件，跑不起来。（即便链接起来加上入口main跑IR tree也只存在于内存中）。
为了查看IR tree和语法树，可以用我们自己写的文本可视化工具（具体代码文件为format.*和visualize.cc），中间会夹杂着一些日志（还有报错信息）。
## 可视化
```sh visualze.sh```
## 运行
可以用上面的可视化脚本，但是脚本只会把./src/test/test.c，翻译成src/test/test.ir，事实上可以运行
```./build/visualize.out < $source```，就可以看到$source文件翻译出来的语法树和IR了。

## IR tree 变成 IR code
没有把IR tree变成IR code，计划用后端直接跑IR tree。不过我们已经做完了把IR tree变成code的准备，就是把所有的CJUMP后面都紧跟着false分支，这样就可以把所有CJUMP替换为if condition goto true_label了。

## 运行结果
源文件(src/test/test.c)
```
int f(int b, int d) {
    int a;
    int c;
    c = a + 10;
    return 10;
}

int main() {
    int a;
    int b;
    b = 20;
    a = b;
    int c;
    c = k * 2;
    if (a + b == c) {
        c = 1;
    } else {

    }

    int h;
    if (h == 1) {
        int k;
    }
    b = k;
    while (c != 2) {
        c = 2;
    }
    int q;
    q = f(a + b, 20);
    return 0;
}

```
语法树，太长不贴（在src/test/test.ir中）  
错误信息（在语法树转ir时顺便检查了一些生命周期）  
```Error: Cannot find variable k```  
第一次引用k时k未定义所以出错。
IR tree（在src/test/test.ir中）：
```
ir root
+--Seq
   |--Seq
   |  |--Label: function-label1
   |  +--Seq
   |     |--Eseq
   |     |  |--Move
   |     |  |  |--Temp: c
   |     |  |  +--BinOp: PLUS
   |     |  |     |--Temp: a
   |     |  |     +--Const: 10
   |     |  +--Temp: c
   |     +--Const: 10
   +--Seq
      |--Label: function-label2
      +--Seq
         |--Seq
         |  |--Seq
         |  |  |--Seq
         |  |  |  |--Seq
         |  |  |  |  |--Seq
         |  |  |  |  |  |--Seq
         |  |  |  |  |  |  |--Seq
         |  |  |  |  |  |  |  |--Eseq
         |  |  |  |  |  |  |  |  |--Move
         |  |  |  |  |  |  |  |  |  |--Temp: b
         |  |  |  |  |  |  |  |  |  +--Const: 20
         |  |  |  |  |  |  |  |  +--Temp: b
         |  |  |  |  |  |  |  +--Eseq
         |  |  |  |  |  |  |     |--Move
         |  |  |  |  |  |  |     |  |--Temp: a
         |  |  |  |  |  |  |     |  +--Temp: b
         |  |  |  |  |  |  |     +--Temp: a
         |  |  |  |  |  |  +--Eseq
         |  |  |  |  |  |     |--Move
         |  |  |  |  |  |     |  |--Temp: c
         |  |  |  |  |  |     |  +--BinOp: MUL
         |  |  |  |  |  |     |     |--Temp: k
         |  |  |  |  |  |     |     +--Const: 2
         |  |  |  |  |  |     +--Temp: c
         |  |  |  |  |  +--Seq
         |  |  |  |  |     |--Cjump, Operator: NEQ
         |  |  |  |  |     |  |--BinOp: EQ
         |  |  |  |  |     |  |  |--BinOp: PLUS
         |  |  |  |  |     |  |  |  |--Temp: a
         |  |  |  |  |     |  |  |  +--Temp: b
         |  |  |  |  |     |  |  +--Temp: c
         |  |  |  |  |     |  |--Const: 0
         |  |  |  |  |     |  |--Label: label3
         |  |  |  |  |     |  +--Label: label4
         |  |  |  |  |     +--Seq
         |  |  |  |  |        |--Seq
         |  |  |  |  |        |  |--Label: label4
         |  |  |  |  |        |  +--NULL
         |  |  |  |  |        +--Seq
         |  |  |  |  |           |--Label: label3
         |  |  |  |  |           +--Eseq
         |  |  |  |  |              |--Move
         |  |  |  |  |              |  |--Temp: c
         |  |  |  |  |              |  +--Const: 1
         |  |  |  |  |              +--Temp: c
         |  |  |  |  +--Seq
         |  |  |  |     |--Cjump, Operator: NEQ
         |  |  |  |     |  |--BinOp: EQ
         |  |  |  |     |  |  |--Temp: h
         |  |  |  |     |  |  +--Const: 1
         |  |  |  |     |  |--Const: 0
         |  |  |  |     |  |--Label: label5
         |  |  |  |     |  +--Label: label6
         |  |  |  |     +--Seq
         |  |  |  |        |--Label: label6
         |  |  |  |        +--Seq
         |  |  |  |           |--Label: label5
         |  |  |  |           +--NULL
         |  |  |  +--Eseq
         |  |  |     |--Move
         |  |  |     |  |--Temp: b
         |  |  |     |  +--Temp: k
         |  |  |     +--Temp: b
         |  |  +--Seq
         |  |     |--Seq
         |  |     |  |--Label: label7
         |  |     |  +--Cjump, Operator: EQ
         |  |     |     |--BinOp: NEQ
         |  |     |     |  |--Temp: c
         |  |     |     |  +--Const: 2
         |  |     |     |--Const: 0
         |  |     |     |--Label: label8
         |  |     |     +--NULL
         |  |     +--Seq
         |  |        |--Eseq
         |  |        |  |--Move
         |  |        |  |  |--Temp: c
         |  |        |  |  +--Const: 2
         |  |        |  +--Temp: c
         |  |        +--Label: label8
         |  +--Eseq
         |     |--Move
         |     |  |--Temp: q
         |     |  +--Call function:f
         |     |     +--Eseq
         |     |        |--Exp
         |     |        |  +--BinOp: PLUS
         |     |        |     |--Temp: a
         |     |        |     +--Temp: b
         |     |        +--Const: 20
         |     +--Temp: q
         +--Const: 0
```
