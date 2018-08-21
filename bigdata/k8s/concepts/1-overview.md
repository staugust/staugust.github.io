# Overview of Kubernetes

## What is Kubernetes?
Kubernetes is a portable, extensible open-source platform for managing containerized workloads and services, that facilitates both declarative configuration and automation. 

### What can kubernetes do?
Kubernetes has a number of features. It can be thought as:
+ A container platform
+ A microservices platform
+ A portable cloud platform and a lot more.

Kubernetes provides a `container-centric` management environment. It orchestrates computing, networking, and storage infrastructure on behalf of user workloads. 

### What kubernetes not do?
Kubernetes is not a traditional, all-inclusive PaaS(Platform as a Service) system. Since Kubernetes operates at the container level rather than at the hardware level, it provides some generally applicable features common to PaaS offerings, such as deployment, scaling, load balancing, logging, and monitoring. However, Kubernetes is not monolithic, these default solutions are optional and pluggable. Kubernetes provides the building blocks for building developer platforms, but preserves user choice and flexibility where it is important. 
Kubernetes:
+ Does not limit the types of applications supported. 
+ Does not deploy source code and does not build your application. `Continuous Integration, Delivery, and Deployment`(`CI/CD`) workflows are determined by organization cultures and preferences as well as technical requirements.
+ Does not provide application-level services, such as middleware(e.g., message buses), data-processing frameworks(for example, Spark), databases(e.g., mysql), caches, nor cluster storage systems(e.g., Ceph) as built-in services. 
+ Does not dictate logging, monitoring, or alerting solutions. It provides some integrations as proof of concepts, and mechanisms to collect and export metrics. 
+ Does not provide nor mandate a configuration language/system(e.g., jsonnet). It provides a declarative API that may be targeted by arbitrary forms of declarative specifications.
+ Does not provide nor adopt any comprehensive machine configuration, maintenance, management or self-healing system. 

### Why containers?
The *Old Way* to deploy applications was to install the applications on a host using the operating-system package manager. The *New way* is to  deploy containers based on operating-system-level virtualization rather than hardware virtualization. These containers are isolated from each other and from the host: they have their own filesystems, they can’t see each others’ processes, and their computational resource usage can be bounded. 

Summary of container benefits:
+ Agile application creation and deployment
+ Continuous development, integration and deployment
+ Dev and Ops separation of concerns
+ Observability
+ Environmental consistency across development, testing, and production.
+ Cloud and OS distibution portability
+ Application-centric management
+ Loosely coupled, distributed, elastic, liberated micro-services
+ Resource isolation
+ Resource utilization



