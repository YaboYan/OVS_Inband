# What's this
Some people who have developed project about software defined networking and OpenVSwitchd may find that openflow messages can still be transmitted to the switches after the port have been shut down. This program solved this problem by sending the openflow messages to kernel layer. Switches can automatically extract these packages from all the data running in the network and send them back to client layer where they are going to be handled.
# How to use
In order to run this program properly, you must follow the rules described bellow:

1.Switch 'S1' is a special switch to this program. If you want to create an in-band topo. this switch must exist and directly connect to the controller. Besides, you have to make sure that you create this switch before others. 

2.After you created your topo manually or by mininet. You need to insert flow table manually for the control messages to be transmitted. this program allocated one ip address for each switch, you can find these addresses at logo. Switch 'S1' has ip address '124.0.0.10'. 

3.The controller can't recognize all the switches in the topo right now, so you need to restart it to establish connections.

4.After all these steps you can start you own project on it. If you have any problems, you can contact me by email.

If you don't know how to replace your old OpenVswitch, you can try fresh.sh in the folder.
# test file 
I put some test file in the folder. You can use them to get a better understanding of this program. 
