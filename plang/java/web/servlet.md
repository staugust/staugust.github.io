# [jsr340]([200~https://jcp.org/en/jsr/detail?id=340) Java Servlet 3.1 Specification 

# OverView 

## What is a servlet? 什么是Servlet? 
`servlet`是一种基于java技术的web组件, 由容器(containers)来管理, 并生成动态内容. 
`容器(containers)`, 有时又被称为servlet引擎(servlet engine), 是web server扩展, 以提供servlet相关功能. Servlets与Web clients通过由servlet container实现的request/response范式来交互. 

## What is a Servlet Container? 什么是Servlet容器? 
`Servlet Container`是web server或者application server的一部门, 用于提供支持发送request/responses, 解码基于MIME的requests, 格式化基于MIME的responses的网络服务. `Servlet Container`在它们的生命周期内也包括(contains)/管理(manages)servlets.
`Servlet Container`可以使web server内置的, 也可以通过web server的扩展api以插件/扩展的形式存在, 也可以由支持web的应用服务器提供. 
所有的servlet containers都必须支持HTTP作为requests/responses通信的协议, 但是基于HTTP的HTTPS协议则不是必须的. 需要支持HTTP/1.0和HTTP/1.1. 

## 一个例子
下述一个典型的事件序列:
1. A client(比如说web浏览器)发送一个http请求
1. web server接收到此request, 转交给servlet container. 
1. servlet container根据其配置决定调用哪个servlet来处理, 然后以代表request和response的对象作为参数, 调用servlet 
1. servlet通过request对象确定remote user, 以及相关的HTTP POST的数据和其他相关数据. servlet实现自己的逻辑, 然后将数据通过response对象发送给client
1. 一旦servlet处理完request, servlet container确保response已正确发送(properly flushed), 然后把控制权返回给web server

## servlet与其他技术的对比
从功能上来讲, servlet处理`Common Gateway Interface(CGI)`和专有服务器扩展，例如Netscape Server API(NSAPI)或Apache模块之间.
Servlet相比于其他的server extension mechanisms, 具有以下优势:
+ 通常比CGI脚本速度更快, 因为其使用了不同的进程模型
+ 使用标准的API, 被许多web server支持
+ 具有java编程语言的所有优势, 包括开发简单, 平台无关. 
+ 可以使用java平台上大量的API

# The Servlet Interface
`Servlet`接口是Java Servlet API的核心抽象. 所有的servlet要么实现`Servlet`接口, 要么继承实现`Servlet`的类. 在Java Servlet API中, 实现了`Servlet`接口的类有两个, `GenericServlet`和`HttpServlet`. 通常情况下, 开发者只需要扩展`HttpServlet`来实现servlets. 

## 请求处理方法 (request handling methods)
`Servlet`接口定义了一个`service`方法来处理客户端请求. servlet container处理每个request时, 都会调用路由到相应的servlet的此方法. 
web应用通常使用多线程来处理并发请求, 所以service方法可能在同一时间, 在多个线程内被调用.
通常，Web容器处理对同一个servlet的并发请求在不同线程上并发执行服务方法.

### http请求处理方法(HTTP Specific Request Handling Methods)
`HttpServlet`抽象子类添加了基本`Servlet`接口之外的其他方法，这些方法由`HttpServlet`类中的`service`方法自动调用，以帮助处理基于HTTP的请求. 这些方法是:
+ `doGet` 用于处理HTTP Get 请求
+ `doPost` 用于处理HTTP Post请求
+ `doPut` 用于处理HTTP Put请求
+ `doDelete` 用于处理HTTP Delete 请求
+ `doHead` 用于处理HTTP Head请求
+ `doOptions` 用于处理HTTP Options请求
+ `doTrace` 用于处理HTTP Trace请求. 

