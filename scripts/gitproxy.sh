#!/bin/bash
case $1 in
on)
 git config --global http.proxy 'socks5://127.0.0.1:1443'
 git config --global https.proxy 'socks5://127.0.0.1:1443'
 ;;

off)
  git config --global --unset http.proxy
	#git config --global --remove-section http
  git config --global --unset https.proxy
	#git config --global --remove-section https
  ;;

status)
   git config --get http.proxy
   git config --get https.proxy
   ;;
esac
exit 0
