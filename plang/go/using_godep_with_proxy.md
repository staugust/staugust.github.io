# How to use godep inside GFW with Shadowsocks proxy

## Set up Shadowsocks proxy 
Get a host outside GFW, then configure a Shadowsocks server. 
This step is not necessary if you have a Shadowsocks server which has already worked well. 

## Configure local shadowsocks 
Add new server, with server address, port, password, crypto method, and in the right-bottom, set your local proxy listening port. 
Remember the proxy listening port, we will it later. 

## Set git proxy 
First, let set git proxy, since when using godep to update dependencies, it would use git to download dependencies. 
Here is a simple example, please replace 1443 to your proxy listening port set in step `Configure local shadowsocks`.

```
git config --global http.proxy 'socks5://127.0.0.1:1443'
git config --global https.proxy 'socks5://127.0.0.1:1443'
```
## Set proxy env
Shadowsocks for windows supports both http & sock5 protocol, you can use the shadowsocks listening port here. 
```
export HTTP_PROXY=127.0.0.1:1443
```
---

That's all, enjoy your godep journey. 
