root@ubuntu:~/Desktop# find usr/lib name libffi.so*
/usr/lib/x86 64-linux-gnu/libffi.so.7.1.0
/usr/lib/x86 64-linux-gnu/libffi.so.7

root@ubuntu:~/Desktop# ln -s /usr/lib/x86 64-linux-gnu/libffi.so.7 /usr/lib/x8664-linux-gnu/libffi.so.6
root@ubuntu:~/Desktop# find /usr/lib -name libffi.so*
/usr/lib/x86 64-linux-gnu/libffi.so.6
/usr/lib/x86 64-linux-gnu/libffi.so.7.1.0
/usr/lib/x86 64-linux-gnu/libffi.so.7