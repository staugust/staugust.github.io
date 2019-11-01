# Docker Engine源码解析

## 各功能快速查看调用
从`api/server/router/router.go`中定义了`Router`接口, 可以查看实现了此类的各种各结构. 
从`dockerd/cmd/dockerd/daemon.go`的`initRouter`函数可以看到docker engine注册的router. 

```
routers := []router.Router{
  // we need to add the checkpoint router before the container router or the DELETE gets masked
  checkpointrouter.NewRouter(opts.daemon, decoder),
  container.NewRouter(opts.daemon, decoder),
  image.NewRouter(opts.daemon.ImageService()),
  systemrouter.NewRouter(opts.daemon, opts.cluster, opts.buildkit, opts.features),
  volume.NewRouter(opts.daemon.VolumesService()),
  build.NewRouter(opts.buildBackend, opts.daemon, opts.features),
  sessionrouter.NewRouter(opts.sessionManager),
  swarmrouter.NewRouter(opts.cluster),
  pluginrouter.NewRouter(opts.daemon.PluginManager()),
  distributionrouter.NewRouter(opts.daemon.ImageService()),
}
```
可见docker engine支持checkpoint, container, image, volume, build等Router, 恰好和docker命令的子命令相对应. 

分析各Router内部实现, 即可找到docker中命令在docker engine的实现. 比如说container相关的route:
```
// initRoutes initializes the routes in container router
func (r *containerRouter) initRoutes() {
	r.routes = []router.Route{
		// HEAD
		router.NewHeadRoute("/containers/{name:.*}/archive", r.headContainersArchive),
		// GET
		router.NewGetRoute("/containers/json", r.getContainersJSON),
		router.NewGetRoute("/containers/{name:.*}/export", r.getContainersExport),
		router.NewGetRoute("/containers/{name:.*}/changes", r.getContainersChanges),
		router.NewGetRoute("/containers/{name:.*}/json", r.getContainersByName),
		router.NewGetRoute("/containers/{name:.*}/top", r.getContainersTop),
		router.NewGetRoute("/containers/{name:.*}/logs", r.getContainersLogs),
		router.NewGetRoute("/containers/{name:.*}/stats", r.getContainersStats),
		router.NewGetRoute("/containers/{name:.*}/attach/ws", r.wsContainersAttach),
		router.NewGetRoute("/exec/{id:.*}/json", r.getExecByID),
		router.NewGetRoute("/containers/{name:.*}/archive", r.getContainersArchive),
		// POST
		router.NewPostRoute("/containers/create", r.postContainersCreate),
		router.NewPostRoute("/containers/{name:.*}/kill", r.postContainersKill),
		router.NewPostRoute("/containers/{name:.*}/pause", r.postContainersPause),
		router.NewPostRoute("/containers/{name:.*}/unpause", r.postContainersUnpause),
		router.NewPostRoute("/containers/{name:.*}/restart", r.postContainersRestart),
		router.NewPostRoute("/containers/{name:.*}/start", r.postContainersStart),
		router.NewPostRoute("/containers/{name:.*}/stop", r.postContainersStop),
		router.NewPostRoute("/containers/{name:.*}/wait", r.postContainersWait),
		router.NewPostRoute("/containers/{name:.*}/resize", r.postContainersResize),
		router.NewPostRoute("/containers/{name:.*}/attach", r.postContainersAttach),
		router.NewPostRoute("/containers/{name:.*}/copy", r.postContainersCopy), // Deprecated since 1.8, Errors out since 1.12
		router.NewPostRoute("/containers/{name:.*}/exec", r.postContainerExecCreate),
		router.NewPostRoute("/exec/{name:.*}/start", r.postContainerExecStart),
		router.NewPostRoute("/exec/{name:.*}/resize", r.postContainerExecResize),
		router.NewPostRoute("/containers/{name:.*}/rename", r.postContainerRename),
		router.NewPostRoute("/containers/{name:.*}/update", r.postContainerUpdate),
		router.NewPostRoute("/containers/prune", r.postContainersPrune),
		router.NewPostRoute("/commit", r.postCommit),
		// PUT
		router.NewPutRoute("/containers/{name:.*}/archive", r.putContainersArchive),
		// DELETE
		router.NewDeleteRoute("/containers/{name:.*}", r.deleteContainers),
	}
}
```
顺着这个线索, 就可以一步一步的查看docker中container相关的实现的逻辑. 



