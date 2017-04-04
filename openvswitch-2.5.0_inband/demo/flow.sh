#!/bin/sh
ovs-ofctl add-flow s3 "table=0,eth_type:0x0800,priority=3,nw_src=125.0.0.10,nw_dst=124.0.0.10,actions=output:2" 
ovs-ofctl add-flow s1 "table=0,eth_type:0x0800,priority=3,nw_src=124.0.0.10,nw_dst=125.0.0.10,actions=output:2"
ovs-ofctl add-flow s1 "table=0,eth_type:0x0800,priority=3,nw_src=124.0.0.10,nw_dst=126.0.0.10,actions=output:2"
ovs-ofctl add-flow s3 "table=0,eth_type:0x0800,priority=3,nw_src=124.0.0.10,nw_dst=126.0.0.10,actions=output:3"
ovs-ofctl add-flow s3 "table=0,eth_type:0x0800,priority=3,nw_src=126.0.0.10,nw_dst=124.0.0.10,actions=output:2"
ovs-ofctl add-flow s2 "table=0,eth_type:0x0800,priority=3,nw_src=126.0.0.10,nw_dst=124.0.0.10,actions=output:1"
#ovs-ofctl add-flow s1 "table=0,eth_type:0x0800,priority=3,nw_src=10.0.0.124,nw_dst=10.0.0.125,actions=output:2"
#ovs-ofctl add-flow s1 "table=0,eth_type:0x0800,priority=3,nw_src=10.0.0.124,nw_dst=10.0.0.126,actions=output:2"
#ovs-ofctl add-flow s0 "table=0,eth_type:0x0800,priority=3,nw_src=10.0.0.125,nw_dst=10.0.0.124,actions=output:2" 

