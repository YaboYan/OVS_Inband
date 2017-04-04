#!/usr/bin/python

from mininet.util import dumpNodeConnections
from mininet.cli import CLI
from mininet.net import Mininet
from mininet.node import OVSSwitch,Controller,RemoteController
from mininet.log import setLogLevel,info
from mininet.node import CPULimitedHost,OVSSwitch
from mininet.link import TCLink
from mininet.topo import Topo

class SimpleTopo(Topo):
      def __init__(self):
       Topo.__init__(self)     
       h1=self.addHost('h1',ip='10.0.0.1/8',mac='00:00:00:00:00:01')
       h2=self.addHost('h2',ip='10.0.0.2/8',mac='00:00:00:00:00:02')
       h3=self.addHost('h3',ip='10.0.0.3/8',mac='00:00:00:00:00:03')
       h4=self.addHost('h4',ip='10.0.0.4/8',mac='00:00:00:00:00:04')
       s1=self.addSwitch('s1',protocals='OpenFlow13')
       s2=self.addSwitch('s2',protocals='OpenFlow13')
       s3=self.addSwitch('s3',protocals='OpenFlow13')

  #     self.addLink(h1,s1,bw= 5, delay='10ms')
       self.addLink(h4,s1,bw= 5, delay='10ms')
       self.addLink(h1,s3,bw= 5, delay='10ms')
       self.addLink(s3,s1,bw= 5, delay='10ms')
       self.addLink(s2,s3,bw= 5, delay='10ms')
       self.addLink(h2,s2,bw= 5, delay='10ms')
       self.addLink(h3,s2,bw= 5, delay='10ms')

       
       

if __name__ == '__main__':  
    setLogLevel( 'info' )   
    topo=SimpleTopo()
#    s00=OVSSwitch('s00',protocals='OpenFlow13')
    net=Mininet(topo=topo,host=CPULimitedHost,switch=OVSSwitch,link=TCLink,controller=None)  
    c0 = RemoteController( 'c0', ip='your_controller_ip', port=yuor_controller_port )  
    net.addController(c0)  
    net.start()  
    CLI( net )  
    net.stop()  
       
