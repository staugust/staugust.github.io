# Authenticating

Kubernetes clusters have two categories of users: service accounts managed by Kubernetes, and normal users. 

`Normal users` are assumed to be managed by an outside, independent service. An admin distributing private keys, a user store like Keystone or Google Accounts, even a file while a list of usernames and passwords. In this regard, Kubernetes does not have objects which represent normal user accounts. Regular users cannot be added to a cluster through an API call. 

`Service accouts` are users managed by Kubernetes API. They are bound to specific namespaces, and created automatically by the API server or manually through API calls. Service accounts are tied to a set of credentials stores as `Secrets`, which are mounted into pods allowing in-cluster processes to talk to Kubernetes API. 

Every process inside or outside the cluster must authenticate when making requests to the API server, or be treated as an anonymous user. 

## Authentication Strategies


