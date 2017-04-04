# What's this
Some people who have developped project about software defined networking and OpenVSwitchd might find that openflow messages can still be transmitted to the switches after they shut the port down. This program solved this problem by sending the openflow messages to kernal layer. Switchs can automatically extract these packages from all the data running in the network and send them back to client layer which where they are going to be handled.
# How to use
In order to run this program poperly, you must follow the rules described bellow:
1.Switch 'S1' is a special switch to this program. If you want to create a in-band topo. this switch must exist and directly connect to the controller. Besides, you have to make sure that you create this switch before others. 
2.After you created your topo manually or by mininet. You need to insert flow table manually for the control messages to be transmitted. this program allocated one ip address for each switch, you can find these addresses at logo.  
3.The controller can't recongnize all the switches in the topo right now, so you need to restart the controller.
# test file 
I put some test file in the floder. T
