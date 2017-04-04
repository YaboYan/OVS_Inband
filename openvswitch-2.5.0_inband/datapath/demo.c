/*
 * demo.c
 *
 *  Created on: Dec 19, 2016
 *      Author: root
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/netfilter.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/netdevice.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/inet.h>
#include <net/tcp.h>
#include <net/udp.h>
#include <net/icmp.h>
#include <linux/netfilter_ipv4.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("kenthy@163.com");

#define    ETH    "eth0"
unsigned char   SMAC[ETH_ALEN] = {0x00,0x0C,0x29,0x4F,0xDE,0xAC};
unsigned char   DMAC[ETH_ALEN] = {0x00,0x50,0x56,0xFA,0x70,0x2A};

static struct nf_hook_ops modify_ops;

static unsigned int modify(unsigned int hooknum, struct sk_buff ** skb,
                                  const struct net_device * in, const struct net_device * out,
                                  int (*okfn)(struct sk_buff *))
{
    struct sk_buff* nskb;
    struct iphdr* nip_hdr;
    unsigned int   nip_hdr_off;
    struct tcphdr* ntcp_hdr;
    unsigned int ntcp_hdr_off;
    struct ethhdr* neth_hdr;
    int ret = 0;

   nskb = skb_copy(*skb, GFP_ATOMIC);
   if(nskb == NULL)
     {
             printk("%s\n", "skb_copy return NULL");
             return NF_ACCEPT;
     }

  if( nskb->nh.iph->protocol != IPPROTO_TCP)
    {
            kfree_skb(nskb);
      return NF_ACCEPT;
     }

    nip_hdr = nskb->nh.iph;
    nip_hdr_off = nip_hdr->ihl << 2;   //covert to kb

    ntcp_hdr = (struct tcphdr *)((void *)nip_hdr + nip_hdr_off);
    ntcp_hdr_off = ntcp_hdr->doff << 2;
    if(!ntcp_hdr->syn)
            {
                    kfree_skb(nskb);
                    return NF_ACCEPT;
            }

    //evil!
    nip_hdr->daddr = in_aton("192.168.1.101");

    nip_hdr->check = 0;
    nip_hdr->check = ip_fast_csum((unsigned char *)nip_hdr, nip_hdr->ihl);

    nskb->csum = 0;
    nskb->csum = csum_partial((unsigned char *)(ntcp_hdr + ntcp_hdr_off),
                                      ntohs(nip_hdr->tot_len) - nip_hdr_off - ntcp_hdr_off, 0);

    ntcp_hdr->check = 0;
    ntcp_hdr->check = csum_tcpudp_magic(nip_hdr->saddr, nip_hdr->daddr,
                                        ntohs(nip_hdr->tot_len) - nip_hdr_off, nip_hdr->protocol,
                                        csum_partial((unsigned char *)ntcp_hdr, ntcp_hdr_off, nskb->csum));


    nskb->ip_summed = CHECKSUM_NONE;
    nskb->pkt_type  = PACKET_OTHERHOST;

    nskb->dev = dev_get_by_name(ETH);
    if(nskb->dev==NULL)
    {
            printk("%s\n", "dev_get_by_name return NULL");
            kfree_skb(nskb);
            return NF_ACCEPT;
            }

    nskb->mac.raw = skb_push (nskb, ETH_HLEN);
     { //eth headeri
      neth_hdr = (struct ethhdr *)nskb->mac.raw;
      memcpy (neth_hdr->h_dest, DMAC, ETH_ALEN);
      memcpy (neth_hdr->h_source, SMAC, ETH_ALEN);
      neth_hdr->h_proto = __constant_htons (ETH_P_IP);
    }


    dev_hold(nskb->dev);  //reference count ++
    printk("%s\n", "dev_hold ok");

    ret = dev_queue_xmit(nskb);
    printk("ret:%d\n", ret);
    return NF_STOLEN;
}


static int __init init(void)
{
  int  ret = 0;
  modify_ops.hook = modify;
  modify_ops.hooknum = NF_IP_LOCAL_OUT;
  modify_ops.pf = PF_INET;
  modify_ops.priority = NF_IP_PRI_FIRST;

  ret = nf_register_hook(&modify_ops);
  if (ret < 0)
   {
     printk("%s\n", "can't modify skb hook!");
     return ret;
   }

    printk("%s\n", "insmod modify skb module");
    return 0;
}

static void __exit fini(void)
{
    nf_unregister_hook(&modify_ops);
    printk("%s\n", "remove modify skb module.");
}

module_init(init);
module_exit(fini);

