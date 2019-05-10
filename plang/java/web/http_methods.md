# Http methods
目前互联网公司的应用架构基本都是前后端分离，后端的接口也基本上都是采用restful架构了，接下来就说说restful的使用。
使用restful架构最主要的是遵循rest的思想：“统一资源接口“。
REST全称：Representational State Transfer，翻译成中文就是“表述性状态转移”，表述的对象就是资源，在web的rertful架构中都是通过uri来一一对应资源，比如：/api/person/1。
URI既可以看成是资源的地址，也可以看成是资源的名称，代表的就是唯一的资源，但是不能表示对资源的操作，操作是结合标准的http方法（get、post、put等）来实现的。

下面说下restful的http方法：GET、HEAD、POST、PUT、DELETE、OPTIONS、TRACE、PATCH
根据RFC2616第九章说明，http方法的定义有两点：safe and Idempotent，即安全性和幂等性，可以结合这两点对以上方法进行说明

## GET
安全、幂等；
用于获取资源；

## HEAD
安全、幂等；
与get方法类似，但不返回message body内容，仅仅是获得获取资源的部分信息（content-type、content-length）；
restful框架中较少使用

## POST
非安全、非幂等；
用于创建子资源

## PUT
非安全、幂等；
用于创建、更新资源；

## DELETE
非安全、幂等；
删除资源；

## OPTIONS
安全、幂等；
用于url验证，验证接口服务是否正常；

## TEACE
安全、幂等；
维基百科“回显服务器收到的请求，这样客户端可以看到（如果有）哪一些改变或者添加已经被中间服务器实现。”
restful框架中较少使用

## PATCH
非安全、幂等；
用于创建、更新资源，于PUT类似，区别在于PATCH代表部分更新；
后来提出的接口方法，使用时可能去要验证客户端和服务端是否支持；

接下来说一下日常中的使用：
1.  post和put的区别：

post和put的区别在于uri，或者说post用于创建子资源，比如接口：POST /api/person/  会创建一个资源比如 /api/person/1或者/api/person/2 ... 或者/api/person/n，创建了新的uri，而put方法创建资源的uri是 PUT /api/person/1，这样就创建了一个资源，如果1已经存在那么就是更新，所以put并不是只是更新操作。再有post是非幂等的。
通常情况下，我们都会将post、get、put、delete对应到CRUD操作上，但实际上put并不是只能更新。

2. patch的使用：
patch是2010后成为的正式http方法，详见RFC5789，它是对put的补充，在没有patch之前，我们都是用put进行更新操作，这时候我们的接口中通常会有一个逻辑规则，如：如果对象的的一个字符属性为NULL，那么就是不更新该属性（字段）值，如果对象的字符属性是“”，那么就更新该属性（字段）的值，通过这种方式来避免全部覆盖的操作。现在有了patch就解决了这种判断，在put接口中不管属性是不是null，都进行更新，在patch接口中就对非null的进行更新；

3. uri的使用问题
    上边也介绍过了，uri即使代表资源的，通过不同的方法来区分操作，那么像如下的接口就已经违反了restful规范：
GET /api/getPerson/1
DELETE /api/delPerson/1
GET /api/person/get/1
DELETE /api/person/delete/1
    在复合规范的前提下，uri的定义应该也是实际使用中应该考虑的，比如uri包涵那些信息？如版本、资源分类、资源名称、表述格式等，对于设计上的不多说了，直接看下面的url：
/api/1.0/person/man/1.xml
/api/2.0/person/man/1.json
    这样的url很常见也很直观，对不同版本接口增加了版本信息，并且对数据的表述格式进行了显式指定，不是不好，但是按照“统一资源接口”的思想，资源的uri已经不唯一了。有说对于版本号，表述形式等可以放到http的accept中进行指定，但具体没有验证过，希望经验人士多多指教！

4. 查询问题的讨论：
按照rest建议，查询操作要使用get方法，但是实际情况中处理起来比较麻烦，如：报表统计查询，需要传递的参数很多，就SpingMVC来说，如果采用get方法，那么@RequestParam接收的参数非常多，接口很难看，通常会封装为java对象，希望通过@RqeustBody接收并处理，但这是不支持get方法，所以很蛋疼；
对于这种情况，最简单的方式就是改成post方式，而且很多公司都是这么干的，但又觉得违反了restful规范；不改成post方式的话可能就需要将传递的参数对象细腻转为json串，后端字符串接收后再转为对象，这样感觉耶不太好，url中显式输出参数信息，个别情况json串太长活着包含特殊字符等也都很麻烦。
希望经验人士多多指教！
--------------------- 
作者：冥加 
来源：CSDN 
原文：https://blog.csdn.net/mingjia1987/article/details/79651241 
版权声明：本文为博主原创文章，转载请附上博文链接！
