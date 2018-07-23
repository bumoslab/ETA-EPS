# Edge component

We test our edge component on both container(Docker) and unikernel(Rumprun)

## Edge component on Rumprun unikernel ##
Since rumprun unikernel doesn't support ARM achitecture, so please run edge componenet on x86_64 architecture.

### Prerequistite ###

xen: [compile from source](https://wiki.xenproject.org/wiki/Compiling_Xen_From_Sourca)

rumprun: [wiki](https://github.com/rumpkernel/wiki/wiki/Repo:-rumprun), [source code](https://github.com/rumpkernel/rumprun.git)

Note: we only test our edge component with xenpv mod on xen-4.10, although I think it should work with hvm mode and can run directly on bare metal linux.

### Build edge_server image ###
Change the variable PATH_TO_RUMPRUN to the path of rumprun

```
CC=$PATH_TO_RUMPRUN/rumprun/bin/x86_64-rumprun-netbsd-gcc make
$PATH_TO_RUMPRUN/rumprun/bin/rumprun-bake xen_pv edge.bin main
```

### Run edge_server on Rumprun ###

```
sudo ${PATH_TO_RUMPRUN}/rumprun/bin/rumprun xen -i -I newnet,xenif,bridge=xenbr0,mac=00:16:3a:00:00:00 -W newnet,inet,static,10.32.135.12/16 -M 64 -N edge_server -- edge.bin 0.0.0.0 8080
```

### Destroy edge component ###
```
sudo xl list
sudo xl destroy vmId
```

## Edge component on container(Docker) ##

```
make clean
make
make install
```

### Run edge_server on Docker ###
Please has docker installed on you system
```
cd docker
./build-docker.sh
```

### Destroy edge component ###
```
sudo docker ps
sudo docker stop containerid
```
