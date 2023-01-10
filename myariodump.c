#include <stdio.h>
#include <pcap.h>
#include <stdbool.h>


// Radiotap header
struct ieee80211_radiotap_header {
        u_int8_t        it_version;     /* set to 0 */
        u_int8_t        it_pad;
        u_int16_t       it_len;         /* entire length */
        u_int32_t       it_present;     /* fields present */
} __attribute__((__packed__));


// Frame Control Field
struct control
{
        uint16_t protocol:2,
        type:2,
        subtype:4,
        to_ds:1,
        from_ds:1,
        more_frag:1,
        retry:1,
        power_mgmt:1,
        more_data:1,
        wep:1,
        order:1;
};


// Beacon Frame
struct dot11_header
{

        struct control ctrl;
        uint16_t duration_id;
        uint8_t destination[6];
        uint8_t source[6];
        uint8_t bssid[6];
        uint16_t sequence_nubmer;
};


// ESSID Header
struct essid
{
    uint8_t essid_number;
    uint8_t essid_length;
};


// How to use
void usage()
{
        printf("syntax: airodump <interface>\n");
        printf("sample: airodump mon0\n");
}


int main(int argc, char *argv[])
{
        // Check Interface Input
        if(argc !=2)
        {
                usage();
                return -1;
        }


        // Make Packet Capture Descriptor
        char* interface =argv[1];
        char errbuf[PCAP_ERRBUF_SIZE];
        pcap_t* pcd = pcap_open_live(interface,BUFSIZ,1,1000,errbuf);
        if(pcd==NULL)
        {
                fprintf(stderr,"cannot open interface %s: %s\n",pcd,errbuf);
                return -1;
        }


        // Read Packet
        printf("BSSID             ESSID\n");

        while(true)
        {
                struct pcap_pkthdr *packet_header;
                const unsigned char *packet_data;
                int res = pcap_next_ex(pcd,&packet_header, &packet_data);

                // Timeout
                if(res == 0)
                        continue;

                // Error or EOF
                if(res == -1 || res == -2)
                        break;

                struct ieee80211_radiotap_header *radiotap = (struct ieee80211_radiotap_header *) packet_data;
                struct dot11_header *dot11 = (struct dot11_header *) (packet_data+radiotap->it_len);

                // Check Beacon Frame
                if(dot11->ctrl.type != 0x00 || dot11->ctrl.subtype!=0x08)
                        continue;

                // Print BSSID
                uint8_t *bssid = dot11->bssid;
                for(int i=0;i<5;i++)
                        printf("%02x:",bssid[i]);
                printf("%02x",bssid[5]);
                printf(" ");

                // Print ESSID
                struct essid *essid = (struct essid *)(packet_data+radiotap->it_len+sizeof(struct dot11_header)+12);
                uint8_t essid_length = essid->essid_length;

                for(int i=0;i<essid_length;i++)
                {
                        printf("%c",*((uint8_t *)(essid)+2+i));

                }
                printf("\n");
        }
}
