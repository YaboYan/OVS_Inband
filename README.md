# What's this
Some people who have developed project about software defined network and OpenVSwitchd may find that openflow messages can still be transmitted to the switches after the ports have been shut down. This program solved this problem by sending the openflow messages to kernel space. Switches can automatically extract these packages from all the data running in the network and send them back to userspace where they are going to be handled.

This project is designed to test the data plane in fast failure restoration experiment, which is under SDN in-band control senario. The code of controller is still under preparation. It won't take long before it goes public.
# How to use

In order to run this program properly, you must follow the rules described bellow:

1.Switch 'S1' is a special switch to this program. If you want to create an in-band topo. this switch must exist and directly connect to the controller. Besides, you have to make sure that you create this switch before others. 

2.After you created your topo. You need to insert flow table manually for control messages to be transmitted. this program allocated one ip address for each switch, you can find these addresses at log files. Switch 'S1' has ip address '10.0.0.124'. 

3.When you insert the flow table properly, the controller still can not recognize all the switches. So you need to restart it to establish connections.

4.After all these steps you can start you own project on it. If you have any problems, you can contact me by email.

I run my program under linux with mininet. I use ryu as my controller.

If you don't know how to replace your old OpenVswitch, you can try fresh.sh.
# test file 
I put some test file in the 'demo' folder. You can use them to get a better understanding of this program. 

This is the first edition of the program. I will make some improvement to make it easier to use.
