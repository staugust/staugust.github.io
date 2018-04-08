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
Then, we should 





# Appendix 
+ [Getting started](https://kubernetes.io/docs/getting-started-guides/scratch/)
+ [k8s networking](https://kubernetes.io/docs/concepts/cluster-administration/networking/)
