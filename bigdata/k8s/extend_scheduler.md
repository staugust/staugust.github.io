# Three ways to add new scheduling rules to Kubernetes. 

There are three ways to add new scheduling rules (predicates and priority functions) to Kubernetes: (1) by adding these rules to the scheduler and recompiling, described here, (2) implementing your own scheduler process that runs instead of, or alongside of, the standard Kubernetes scheduler, (3) implementing a "scheduler extender" process that the standard Kubernetes scheduler calls out to as a final pass when making scheduling decisions.


See [scheduler_extender](https://github.com/kubernetes/community/blob/master/contributors/design-proposals/scheduling/scheduler_extender.md)
