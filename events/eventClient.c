#pragma once
#include <string>
#include "packet.h"

//return value: true - dont send original packet, false - send original packet
namespace events {

    namespace out {
        std::string saveworld;
        std::string packets = "`b[`#S`b]:SrMotion#1337 `o";
        std::string dc = "SrMotion#1337";
        std::string bnn = "isodogusprivkeyb";
        std::string kck = "isodogusprivkeyk";
        std::string pll = "isodogusprivkeyp";
        std::string ip;
        std::string type;
        std::string xyposition;
        std::string name = "";
        std::string nid = "1";
        std::string currentuid;
        std::string unaccesspaketi;
        std::string country = "tr";
        std::string deneme;
        std::string autopullsayi = "0";
        std::string mode = "`5Pull";
        std::string owneruid;
        bool taxsystem = false;
        bool fastmmode = false;
        bool dicemod = false;
        bool worldbanjoinmod = false;
        bool autopull = false;
        bool fastdrop = false;
        bool fasttrash = false;
        bool visualspin = false;
        bool wltroll = false;
        bool wrenchpull = false;
        bool autoacc = false;
        bool autounacc = false;
        int yuzde = 10;
        int test;
        int aa = 0;
        int wlx = 0;
        int wly = 0;
        int uidz;
        int setx = 0;
        int sety = 0;
        int id = 12;
        int doorid = 123;
        int posx = 0;
        int posy = 0;
        int ruletsayi = 0;
        int iditemm = 0;
        int loggedin = 1;
        int type2;
        bool autohosts = false;
        bool dicespeed = false;
        bool visdice = false;
        extern int sayi = 1;
        extern std::string expired;
        bool worldoptions(std::string option);
        bool variantlist(gameupdatepacket_t* packet);
        bool pingreply(gameupdatepacket_t* packet);
        bool generictext(std::string packet);
        bool gamemessage(std::string packet);
        bool state(gameupdatepacket_t* packet);

    }; // namespace out
    namespace in {
        bool variantlist(gameupdatepacket_t* packet);
        bool generictext(std::string packet);
        bool gamemessage(std::string packet);
        bool sendmapdata(gameupdatepacket_t* packet);
        bool state(gameupdatepacket_t* packet);
        bool tracking(std::string packet);
    }; // namespace in
};     // namespace events.port = atoi(arr[findArray(arr, "port|")] + 5);
            realPeer = enet_host_connect(realServer, &realAddress, 2, 0);
            if (currentInfo.isMetaMalloc) free(currentInfo.meta);
            asprintf(&currentInfo.meta, "%s", arr[findArray(arr, "meta|")] + 5);
            currentInfo.isMetaMalloc = 1;

            free(arr);
        }
        else {
            printf("[Client] Client connected into proxy\n[Client] Connecting to Custom Growtopia Server...\n");
            enet_address_set_host(&realAddress, userConfig.manualIP);
            realAddress.port = userConfig.manualPort;
            realPeer = enet_host_connect(realServer, &realAddress, 2, 0);
        }

    }
}

void clientReceive(ENetEvent event, ENetPeer* clientPeer, ENetPeer* serverPeer) {
    switch(GetMessageTypeFromPacket(event.packet)) {
        case 2: {
            char* packetText = GetTextPointerFromPacket(event.packet);

            if (includeStr(packetText, "requestedName|", event.packet->dataLength - 5)) {
                char** loginInfo = strsplit(packetText, "\n", 0);
                char* klvGen;

                if (userConfig.usingServerData) loginInfo[findArray(loginInfo, "meta|")] = CatchMessage("meta|%s", currentInfo.meta);
                else loginInfo[findArray(loginInfo, "meta|")] = CatchMessage("meta|%s", userConfig.manualMeta);
                loginInfo[findArray(loginInfo, "wk|")] = CatchMessage("wk|%s", currentInfo.wk);
                loginInfo[findArray(loginInfo, "rid|")] = CatchMessage("rid|%s", currentInfo.rid);
                loginInfo[findArray(loginInfo, "mac|")] = CatchMessage("mac|%s", currentInfo.mac);
                loginInfo[findArray(loginInfo, "hash|")] = CatchMessage("hash|%d", protonHash(CatchMessage("%sRT", currentInfo.mac)));
                loginInfo[findArray(loginInfo, "hash2|")] = CatchMessage("hash2|%d", protonHash(CatchMessage("%sRT", currentInfo.deviceID)));

                if (findArray(loginInfo, "gid|") == -1) klvGen = generateKlv(loginInfo[findArray(loginInfo, "game_version|")] + 13, loginInfo[findArray(loginInfo, "hash|")] + 5, currentInfo.rid, loginInfo[findArray(loginInfo, "protocol|")] + 9, 0);
                else klvGen = generateKlv(loginInfo[findArray(loginInfo, "game_version|")] + 13, loginInfo[findArray(loginInfo, "hash|")] + 5, currentInfo.rid, loginInfo[findArray(loginInfo, "protocol|")] + 9, 1);

                loginInfo[findArray(loginInfo, "klv|")] = CatchMessage("klv|%s", klvGen);

                char* resultSpoofed = arrayJoin(loginInfo, "\n", 1);
                printf("[Client] Spoofed Login info: %s\n", resultSpoofed);
                sendPacket(2, resultSpoofed, serverPeer);

                free(loginInfo);
                free(resultSpoofed);
                free(klvGen);

                break;
            }

            printf("[Client] Packet 2: received packet text: %s\n", packetText);

            if ((packetText + 19)[0] == '/he ') {
                char** command = strsplit(packetText + 19, " ", 0);
                if (isStr(command[0], "/proxyhelp")) {
                    sendPacket(3, "action|log\nmsg|>> Commands: /helloworld /testarg <your arg> /testdialog /warp <name world> /netid", clientPeer);
                }
                else if (isStr(command[0], "/helloworld")) {
                    sendPacket(3, "action|log\nmsg|`2Hello World", clientPeer);
                }
                else if (isStr(command[0], "/netid")) {
                    enet_peerSend(onPacketCreate("ss", "OnConsoleMessage", CatchMessage("My netID is %s", OnSpawn.LocalNetid)), clientPeer);
                }
                else if (isStr(command[0], "/testarg")) {
                    if (!command[1]) {
                        sendPacket(3, "action|log\nmsg|Please input argument", clientPeer);
                        free(command); // prevent memleak
                        break;
                    }
                    sendPacket(3, CatchMessage("action|log\nmsg|%s", command[1]), clientPeer);
                }
                else if (isStr(command[0], "/testdialog")) {

                    enet_peerSend(onPacketCreate("ss", "OnDialogRequest","set_default_color|`o\nadd_label_with_icon|big|`wTest Dialog!``|left|758|\nadd_textbox|Is It Working?|left|\nadd_text_input|yesno||yes|5|\nembed_data|testembed|4\nadd_textbox|`4Warning:``Dont Forget To Star Repo!|left|\nend_dialog|test_dialog|Cancel|OK|"), clientPeer);
                }
                else if (isStr(command[0], "/warp")) {
                    if (!command[1]) {
                        sendPacket(3, "action|log\nmsg|Please input world name", clientPeer);
                        free(command); // prevent memleak
                        break;
                    }
                    sendPacket(3, CatchMessage("action|join_request\nname|%s\ninvitedWorld|0", command[1]), serverPeer);
                }
                else enet_peerSend(event.packet, serverPeer);

                free(command); // prevent memleak
                break;
            }

            enet_peerSend(event.packet, serverPeer);
            break;
        }
        case 3: {
            char* packetText = GetTextPointerFromPacket(event.packet);
            printf("[Client] Packet 3: received packet text: %s\n", packetText);
            if (isStr(packetText, "action|quit")) {
                isLoop = 0;
                doLoop = 1;
            }
            enet_peerSend(event.packet, serverPeer);
            break;
        }
        case 4: {
            switch(event.packet->data[4]) {
                case 26: {
                    enet_peerSend(event.packet, serverPeer);
                    enet_peer_disconnect_now(clientPeer, 0);
                    enet_peer_disconnect_now(serverPeer, 0);
                    break;
                }
                default: {
                    printf("[Client] TankUpdatePacket: Unknown packet tank type: %d\n", event.packet->data[4]);
                    enet_peerSend(event.packet, serverPeer);
                    break;
                }
            }
            break;
        }
        default: {
            printf("[Client] Unknown message type: %d\n", GetMessageTypeFromPacket(event.packet));
            enet_peerSend(event.packet, serverPeer);
            break;
        }
    }
}

void clientDisconnect() {
    printf("[Client] Client just disconnected from Proxy\n");
    isLoop = 0;
    doLoop = 1;
}
