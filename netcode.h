/*
    netcode.io reference implementation

    Copyright © 2016, The Network Protocol Company, Inc.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

        1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

        2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
           in the documentation and/or other materials provided with the distribution.

        3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived 
           from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef NETCODE_H
#define NETCODE_H

#include <stdint.h>

#if    defined(__386__) || defined(i386)    || defined(__i386__)  \
    || defined(__X86)   || defined(_M_IX86)                       \
    || defined(_M_X64)  || defined(__x86_64__)                    \
    || defined(alpha)   || defined(__alpha) || defined(__alpha__) \
    || defined(_M_ALPHA)                                          \
    || defined(ARM)     || defined(_ARM)    || defined(__arm__)   \
    || defined(WIN32)   || defined(_WIN32)  || defined(__WIN32__) \
    || defined(_WIN32_WCE) || defined(__NT__)                     \
    || defined(__MIPSEL__)
  #define NETCODE_LITTLE_ENDIAN 1
#else
  #define NETCODE_BIG_ENDIAN 1
#endif

#define NETCODE_PLATFORM_WINDOWS    1
#define NETCODE_PLATFORM_MAC        2
#define NETCODE_PLATFORM_UNIX       3

#if defined(_WIN32)
#define NETCODE_PLATFORM NETCODE_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define NETCODE_PLATFORM NETCODE_PLATFORM_MAC
#else
#define NETCODE_PLATFORM NETCODE_PLATFORM_UNIX
#endif

#define NETCODE_SERVER_INFO_BYTES 4096
#define NETCODE_KEY_BYTES 32
#define NETCODE_MAC_BYTES 16
#define NETCODE_NONCE_BYTES 8
#define NETCODE_MAX_SERVERS_PER_CONNECT 16

#define NETCODE_CLIENT_STATE_CONNECT_TOKEN_EXPIRED              -7
#define NETCODE_CLIENT_STATE_INVALID_SERVER_INFO                -6
#define NETCODE_CLIENT_STATE_CONNECTION_TIMED_OUT               -5
#define NETCODE_CLIENT_STATE_CONNECTION_CONFIRM_TIMEOUT         -4
#define NETCODE_CLIENT_STATE_CONNECTION_RESPONSE_TIMEOUT        -3
#define NETCODE_CLIENT_STATE_CONNECTION_REQUEST_TIMEOUT         -2
#define NETCODE_CLIENT_STATE_CONNECTION_DENIED                  -1
#define NETCODE_CLIENT_STATE_DISCONNECTED                       0
#define NETCODE_CLIENT_STATE_SENDING_CONNECTION_REQUEST         1
#define NETCODE_CLIENT_STATE_SENDING_CONNECTION_RESPONSE        2
#define NETCODE_CLIENT_STATE_WAITING_FOR_CONNECTION_CONFIRM     3
#define NETCODE_CLIENT_STATE_CONNECTED                          4

#define NETCODE_SOCKET_IPV6         1
#define NETCODE_SOCKET_IPV4         2

#define NETCODE_MAX_CLIENTS         256
#define NETCODE_MAX_PACKET_SIZE     1200

int netcode_init();

void netcode_term();

struct netcode_client_t * netcode_client_create( char * address, double time );

void netcode_client_destroy( struct netcode_client_t * client );

void netcode_client_connect( struct netcode_client_t * client, uint8_t * server_info );

void netcode_client_update( struct netcode_client_t * client, double time );

void netcode_client_send_packet( struct netcode_client_t * client, uint8_t * packet_data, int packet_bytes );

void netcode_client_disconnect( struct netcode_client_t * client );

int netcode_client_state( struct netcode_client_t * client );

int netcode_generate_server_info( int num_server_addresses, char ** server_addresses, int expire_seconds, uint64_t client_id, uint64_t protocol_id, uint8_t * private_key, uint8_t * server_info );

struct netcode_server_t * netcode_server_create( char * bind_address, char * public_address, uint64_t protocol_id, uint8_t * private_key, double time );

void netcode_server_start( struct netcode_server_t * server, int max_clients );

void netcode_server_update( struct netcode_server_t * client, double time );

void netcode_server_destroy( struct netcode_server_t * server );

void netcode_sleep( double seconds );

double netcode_time();

#endif // #ifndef NETCODE_H
