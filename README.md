# 基于Qt的简易学生管理系统

## 使用CLion+Qt6完成项目，运行该项目需要进行以下配置。

1. 安装[Qt6](https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4)
2. 安装[CLion](https://www.jetbrains.com/clion/)以及进行配置。
3. [配置参考教程](https://blog.csdn.net/weixin_39510813/article/details/115482634)

## 运行项目

1. 下载项目后需要修改**src/CmakeLists.txt**中的 `CMAKE_PREFIX_PATH`，设置为安装的Qt位置。

```bash
set(CMAKE_PREFIX_PATH "qt安装路径")
```

2. 该项目使用了QSQLITE，如果运行失败的话，可能是没有拷贝数据库驱动拷贝，需要手动拷贝。

```bash
找到Qt安装位置,找到sqldrivers文件夹,拷贝该文件夹到bin/plugins中
安装位置示例:Qt\6.3.0\mingw_64\plugins\sqldrivers
```

[原项目地址](http://c.biancheng.net/view/9431.html)
