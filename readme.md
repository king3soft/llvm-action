LLVM 是一个强大的编译器值得学习, 一定要学习, 肯定要学习.

https://github.com/apachecn/apachecn-c-cpp-zh-pt2/blob/master/docs/learn-llvm12/00.md

## windows编译教程

https://mp.weixin.qq.com/s/e3dGnzwIeGHHXFN27UIw8Q




## 优秀的编译好的可以直接用的
https://github.com/mstorsjo/llvm-mingw/releases

```shell
root@ubuntu:~/Desktop# find usr/lib name libffi.so*
/usr/lib/x86 64-linux-gnu/libffi.so.7.1.0
/usr/lib/x86 64-linux-gnu/libffi.so.7

root@ubuntu:~/Desktop# ln -s /usr/lib/x86 64-linux-gnu/libffi.so.7 /usr/lib/x8664-linux-gnu/libffi.so.6
root@ubuntu:~/Desktop# find /usr/lib -name libffi.so*
/usr/lib/x86 64-linux-gnu/libffi.so.6
/usr/lib/x86 64-linux-gnu/libffi.so.7.1.0
/usr/lib/x86 64-linux-gnu/libffi.so.7
```
