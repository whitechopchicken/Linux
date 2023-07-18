记录 Linux 网络编程 
视频链接：https://www.bilibili.com/video/BV1iJ411S7UA?p=12&spm_id_from=pageDriver&vd_source=bb587b784ca91928dd7a259dce779437
开坑日期：2023.5.27   15集
打卡：5.28   5集 ，在 server.c 测试时，遇到nc 命令没反映的问题 。 
        nc 没有问题，是ip地址找错了。我在window 的cmd 里面 使用ipconfig 显示的ip都没用，在虚拟机终端用 ip addr show 找到的ens33的网络接口才是
        虚拟机测试测试成功。
        wsl 的Ubuntu 测试成功，同样使用 ip addr show ，找到eth0 的ip才正确。eixt
打卡：5.29  8集，到P28     ip地址转换函数 inet_pton   inet_ntop
打卡：5.30       到p35
打卡：5.31       到p38          服务器没响应，代码和视频里一样，但是我的server不通信，为啥？
打卡：7.05       到p38          又是ip地址找错了，直接在终端输入ip addr show，而不是windows里面的ipconfig！！ 
另外，可以使用netstat -tln 来检测服务器是否在监听指定的端口   复习了以前的知识。
                                没有回收子进程的话，用ps ajx命令，可以看到有几个server(defunxxx) 僵尸进程
                *如何回收子进程 ？1.注册信号捕捉函数==>写在父进程中
                                2.写回收子进程的函数 catch_child() 
                                因为子进程会给父进程发送 sigchild信号
打卡：7.15      多进程、多线程服务器，入门级别，抄写5遍                                