# Vitality OS

Vitality OS是在macOS下开发的、基于川和秀实所著《30天自制操作系统》的haribote OS所开发的32位图形界面操作系统。

注：尚在开发中，不确定哪些工具没有必要使用，工具适用于Windows系统请注意有选择性地使用。出于开发的需要也对Makefile变更了一些路径及文件名称。

这个README相当潦草，有待完善。

# 日志

### 第1天

- 用QEMU模拟
- 去掉了install功能，只支持模拟器模拟
- 调用wine加载exe可执行文档和二进制文档

### 第2天

- 编写适用于macOS的shell处理脚本
- 重写Makefile，使之适用于终端+wine执行

### 第3天

- 写入磁盘读取信息和映像格式信息
- 开始与C程序链接

### 第4天

- 开始绘制图形界面


### 第5天

- 引入字体文件
- 显示变量值（variables）
- 绘制鼠标图案
- 开始分配段（segments），初始化GDT与IDT
- 删除前几天产生的多余文档，修复vitality_0.2中Makefile的路径引用bug

# TODO List

- 改进Makefile的逻辑：在文件不全的情况下删除指定文档、改进脚本运行出错提示
- bootstrap.c所引用的sprintf函数有安全隐患，写一个更安全的版本
- 根据功能分割C文件