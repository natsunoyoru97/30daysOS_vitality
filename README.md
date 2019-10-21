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

### 第6天

- 分割c文件，添加头文件（*.h）
- 简化Makefile逻辑，增加一般规则
- 初始化PIC
- 添加键盘操作的中断处理

### 第7天

- 建立FIFO缓冲区（fifo.c），以存储多个中断处理发送的值
- 获取按键编码
- 获取鼠标数据

### 第8天

- 获取鼠标数据（鼠标按键状态，x，y）
- 使鼠标可以移动

### 第9天

- 增加内存管理功能，支持检查内存容量与剩余内存量

### 第10天

- 修复第9天遗留的bug：显示的总内存只有4MB
- 增加叠加处理

# TODO List

- 改进Makefile的逻辑：在文件不全的情况下删除指定文档、改进脚本运行出错提示
- bootstrap.c所引用的sprintf函数有安全隐患，写一个更安全的版本
- 继续完成对鼠标操作的中断处理
- 实时渲染桌面状态，使得鼠标操作不会影响桌面的canvas
- 增加针对USB的安装指令
- 补充说明文档，以全局角度讲解OS的实现、如何在macOS环境下配置及一些延伸问题
