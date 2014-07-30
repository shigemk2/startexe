startexe
========

EXEファイル入門・集中講座

http://start-exe.connpass.com/event/6620/

EXEファイルの基礎を集中的に勉強する講座で、簡単なコンパイラの作成を目指します。

### 使い方
#### brainfuckのインタプリタ

```sh
$ gcc brainfuck.c -o brainfuck.exe
$ ./brainfuck.exe test.b
```

#### BF->Cのトランスレータ

```sh
$ gcc bftr-c.c -o bftr-c.exe
$ ./bftr-c.exe test.b // translate.cが生成される
$ gcc translate.c -o translate.exe
$ ./translate.exe
```

#### 資料

test.exeを作成するC
https://gist.github.com/7shi/bd16b8996b9a707c2cd5
