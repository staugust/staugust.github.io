# Install kubernetes & minikube
Install kubernetes on `CentOS 7.4`.

## Install necessary components. 
+ Install kubernetes
Using command below to install kubernetes. 
```
yum install kubernetes
```
//There's no need to install minikube since I would configure kubernetes in cluster mode. 
//+ Install minikube
//```
//curl -Lo minikube https://storage.googleapis.com/minikube/releases/v0.25.2/minikube-linux-amd64 && chmod +x minikube && sudo mv minikube /usr/local/bin/
//```
+ Start docker daemon
```
systemctl start docker
```
+ Validate installation. 
First, let's check docker daemon status with commands below:
```
systemctl status docker.service 
systemctl status docker
service docker status
docker version
docker images
docker ps
```
+ Load docker images needed by k8s. 
TODO record all images that should be load. In this magic land, Chinese mainland, images should be download from google's dockerhub and then load into local machine. Another way is to build a dockerhub in your local cluster, then using that dockerhub instead. 

+ Install k8s packages
Then, we should install kubeadm, configure /etc/systemd/system/kubelet.service.d/*.conf , mark driver as `cgroupfs`. Those packages are `kubeadm`, `kubectl`, `kubelet`, `kubernetes-cni`. Besides, `ebtables` is a dependency of k8s. 

+ Access the apiserver using HTTPS
  - Use https with certs, and credentials for user. 
  - This is the recommended approach
  - Configuring certs can be tricky. 
  - How to generate & configure certs
    //TODO

  1. Preparing Certs
  How many certs should be prepared? 
  - The master needs a cert to act as an HTTPS server.
  - The kubelets optionally need certs to identify themselves as clients of the master, and when serving its own API over HTTPS. 



# Appendix 
## k8s software binaries 
  You can run `docker`, `kubelet`, `kube-proxy` outside of a container, the same way you would run any system daemon. For `etcd`, `kube-apiserver`, `kube-controller-manager`, `kube-scheduler`, running those as containers is recommended. Hence, docker images should be built to run those process. 
- `etcd`  
  + Use images hosted on Google Container Registry(GCR), such as `k8s.gcr.io/etcd:2.2.2`
  + Use images hosted on [Docker Hub](https://hub.docker.com/search/?q=etcd) or [Quay.io](https://quay.io/repository/coreos/etcd), such as `quay.io/coreos/etcd:v2.2.1`
  + Use etcd binary included in your OS distro. 
  + Build your own image
    - `cd /kubernetes/cluster/images/etcd; make`
  
- A container runner, one of `docker`, `rkt`
- Kubernetes 
  + kubelet
  + kube-proxy
  + kube-apiserver
  + kube-controller-manager
  + kube-scheduler

## Reference
+ [Getting started](https://kubernetes.io/docs/getting-started-guides/scratch/)
+ [k8s networking](https://kubernetes.io/docs/concepts/cluster-administration/networking/)




