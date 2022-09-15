# Ethereal Framework

A cheat production framework.

一个基于面向对象的辅助制作框架

原本只是我一个项目里的东西，觉得写的还行就提出来重写成一个框架了

想要上手这个框架需要您有一点面向对象的开发基础，并懂得一点设计模式

本人只是个学生，不是专门干计算机这行的，代码中难免会有错误或者表达不当的地方，请大手子们不要骂，一切以你为准

框架本着能不用第三方库就不用第三方库，小巧简洁，能用就行的原则，很多东西都是本人手写的，所以性能上肯定比不过其他的优秀代码库，当然您可以自行更换

虽然这是一整个框架，但是我还是选择了模块化开发的方式，每一个模块都可单独提取出来用(有些模块会依赖其他模块，要一并提取)，无论是内部还是外部的开发都能很好地胜任，远离shit山代码

每个模块的示例请看Main.cpp

# Credits

Reflect Injector --- 雅音宫羽

# Thirdparty

[Minhook](https://github.com/TsudaKageyu/minhook)

# Features

* Event
  - 基于可扩展的Event类, Handler为onXXX(const Event& e)的设计思想
  - 基于观察者模式编写，解耦您的代码
* Logger
  - 日志模块，简单易用，小巧精悍
* Memory
  - 对特定进程的内存进行操作，如需对接自己的驱动等可继承AbstractMemoryManager另起实现类
* Injector
  - 把Dll注入进特定进程，目前提供有Reflect的注入方式(反射注入，支持x86/x64)，如需对接自己的驱动等可继承AbstractInjector另起实现类
* Hook
  - 基于Minhook库重新封装的Hook模块
  
