# Install Kubernetes via kubeadm

## Init master

### Init api server
` kubeadm init --apiserver-advertise-address=192.168.61.32 --pod-network-cidr=172.16.0.0/16 --kubernetes-version=v1.9.7 --ignore-preflight-errors=Swap`
### Install network plugin (calico)

`kubectl apply -f https://docs.projectcalico.org/v3.1/getting-started/kubernetes/installation/hosted/kubeadm/1.7/calico.yaml`

### Delete taint on node
`kubectl taint nodes --all node-role.kubernetes.io/master-`

### Other node join to cluster

`kubeadm join --token 6a57a2.ae5703cc4ba6c14f 192.168.61.32:6443 --discovery-token-ca-cert-hash sha256:fee72f929c2475a1c86a5e712bc73a6b8366ebde95cf53ee9d38e2d4a8538755`



# Reset Kubernetes cluster

## Drain & Delete all node (master node included)

```
kubectl drain ${node.name} --delete-local-data --force --ignore-daemonsets

kubectl delete node ${node.name}
```

Then reset cluster on master node:
```
kubeadm reset 
rm -rf /var/lib/cni
```
On computing node, delete two files and stop service kubelet
```
rm -rf /etc/kubernetes/pki/ca.crt
rm -rf /etc/kubernetes/kubelet.conf
systemctl stop kubelet
```



