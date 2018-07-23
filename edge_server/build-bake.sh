
#!/bin/bash
# CC=~/Desktop/unikernel/rumprun/rumprun/bin/x86_64-rumprun-netbsd-gcc make client
CC=~/Desktop/unikernel/rumprun/rumprun/bin/x86_64-rumprun-netbsd-gcc make
sleep 1

# ~/Desktop/unikernel/rumprun/rumprun/bin/rumprun-bake xen_pv edge.bin sslclient
~/Desktop/unikernel/rumprun/rumprun/bin/rumprun-bake xen_pv edge.bin main
