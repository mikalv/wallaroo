# Buffy

## Usage

Buffy must be imported as a library.

When you run a client, use the following command line parameters:

```-l``` sets process as leader.  
```-w <count>``` tells the leader how many workers to wait for.  
```-n <node_name>``` sets the name for the process in the Buffy cluster.
```--source <comma-delimited source_addresses>``` sets the addresses for the sink
```--sink <comma-delimited sink_addresses>``` sets the addresses for the sink

To run the Double Divide app, you need to kick off three processes.  The first arg is
the leader address.

1. Leader  
```./app-name 127.0.0.1:6000 --source 127.0.0.1:7000 --sink 127.0.0.1:8000 -l -w 2 -n LeaderNode```

2. Workers  
```./app-name 127.0.0.1:6000 --source 127.0.0.1:7000 --sink 127.0.0.1:8000 -n Worker1```
```./app-name 127.0.0.1:6000 --source 127.0.0.1:7000 --sink 127.0.0.1:8000 -n Worker2```

The address passed in is the leader's address.