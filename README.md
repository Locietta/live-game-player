# 康威生命游戏

> ported from gitee

## 项目说明

实现一个生命游戏（Conway life game）模拟器，支持用户进行游玩。

项目使用 C++语言，利用 FLTK 界面库和 MVVM 开发框架开发。

## 构建方式

采用 CMake 工具构建，可以在 win10 和 Linux 上编译（需要首先安装/编译 FLTK 界面库）

> 已在mingw/MSYS2, Arch Linux, ubuntu2004上测试编译通过

```cmake
cmake -S . -B build      # 生成config文件到build文件夹下
cmake --build build -j8  # 编译可执行文件到build文件下
```

采用预编译头技术加速编译

## 项目需求

- 随机生成生命游戏初始图

- 单步/多步模拟生命游戏

- 用户通过鼠标点击界面，更改游戏状态

## 工具

### 开发语言

使用 C++和 FLTK 界面库开发

### 项目管理

|   名称   |          工具          |
| :------: | :--------------------: |
| 版本控制 |    Git+GitHub/Gitee    |
| 持续集成 | Jenkins, GitHub Action |
| 构建工具 |         CMake          |
| 规范检查 |   clangd, clang-Tidy   |
| 静态分析 |       scan-build       |
| 单元测试 |         CTest          |

### 具体实现

#### 软件框架

软件整体采用 MVVM 模式框架，达到多人高效协同的效果。

#### 图形界面

采用 FLTK 界面库绘制图形界面

## 小组分工

王灵鑫：项目 Manager，app代码装配，管理持续集成、构建脚本和代码规范

陈德瀚：view模块，FLTK界面编写

杨林涛：view model, model 模块编写
