
#ifndef _RACER_TOKEN_QUEUE_H
#define _RACER_TOKEN_QUEUE_H

// MBT 5/18/2016
//
// Remote store programming naturally supports producer-consumer communication via
// a restricted form of shared memory. This module provides a generalized form of fixed-sized circular queues,
// where each element of the queue corresponds to a unique set of addresses. When the producer
// "enques" to the queue, it is transfering ownership of that address range to the consumer.
// 
// When the consumer "confirms" a number N of elements on the queue, it is verifying that the N
// top elements of the queue have been assigned to it, and it can access all of those addresses freely.
// When the consumer "deques" a number N of elements from the queue, it returns those N address sets
// to the producer, and reassigns the "top element".
//
// Although this mechanism is general, in the case of remote store programming, senders have 
// exclusive write access to a range, and receivers have exclusive RW access to a range.
//
//

#ifdef RACER_TOKEN_QUEUE_SHORT
#define RacEr_token_pair_ATOM short
#else
#define RacEr_token_pair_ATOM int
#endif


typedef struct RacEr_token_pair
{
  RacEr_token_pair_ATOM send;
  RacEr_token_pair_ATOM receive;
} RacEr_token_pair_t;

// hack
// assumes a particular endian ordering and alignment of the above RacEr_toke_pair array
#define RACER_TOKEN_QUEUE_SHORT_RECEIVE(x) ((x) >> 16)
#define RACER_TOKEN_QUEUE_SHORT_SEND(x) ((x) & 0xFFFF)


typedef struct RacEr_token_connection
{
  RacEr_token_pair_t *local_ptr;
  volatile RacEr_token_pair_ATOM *remote_ptr;
} RacEr_token_connection_t;


#define RacEr_declare_token_queue(x) RacEr_token_pair_t x [RacEr_tiles_X][RacEr_tiles_Y] = {0,0}

  inline RacEr_token_connection_t RacEr_tq_send_connection (RacEr_token_pair_t token_array[][RacEr_tiles_Y], int x, int y)
  {
    RacEr_token_connection_t conn;
    
    conn.local_ptr  = &token_array[x][y];
    conn.remote_ptr = RacEr_remote_ptr(x,y,&(token_array[RacEr_x][RacEr_y].send)); 

    return conn;
  }

inline RacEr_token_connection_t RacEr_tq_receive_connection (RacEr_token_pair_t token_array[][RacEr_tiles_Y], int x, int y)
{
  RacEr_token_connection_t conn;
  
  conn.local_ptr  = &token_array[x][y];
  conn.remote_ptr = RacEr_remote_ptr(x,y,&(token_array[RacEr_x][RacEr_y].receive));

  return conn;
}

// wait for at least depth address sets to HE available to sender
inline int RacEr_tq_sender_confirm(RacEr_token_connection_t conn, int max_els, int depth)
{
  int i = (conn.local_ptr)->send;
  int tmp =  - max_els + depth + i;

  // wait until having the addition sent elements would not overflow the buffer
  //  RacEr_wait_while((depth + i - RacEr_volatile_access((conn.local_ptr)->receive)) > max_els);

  // these lines incorrect on wrap around because of modulo arithmetic
  // RacEr_wait_while((RacEr_lr(&((conn.local_ptr)->receive)) < tmp) && (RacEr_lr_aq(&((conn.local_ptr)->receive)) < tmp));

#ifdef RACER_TOKEN_QUEUE_SHORT
  while (1)
  {
    int recv = RACER_TOKEN_QUEUE_SHORT_RECEIVE(RacEr_lr((int *) conn.local_ptr));

    if (tmp - recv <= 0) break;

    recv = RACER_TOKEN_QUEUE_SHORT_RECEIVE(RacEr_lr_aq((int *) conn.local_ptr));

    if (tmp - recv <= 0) break;
  }

#else
  RacEr_wait_while((tmp - RacEr_lr(&((conn.local_ptr)->receive)) > 0) && (tmp - RacEr_lr_aq(&((conn.local_ptr)->receive)) > 0));
#endif

  return i;
}

// actually do the transfer; assumes that you have confirmed first
//

inline int RacEr_tq_sender_xfer(RacEr_token_connection_t conn, int max_els, int depth)
{
  int   i = (conn.local_ptr)->send + depth;

// MBT 9/18/16 fixme performance:  I believe in a sequentially consistent memory system
// a fence should not HE necessary if the data and the token queue are between
// the same pair. but this requires more followup

  RacEr_commit_stores();

  // local version
  (conn.local_ptr)->send = i;

  // remote version

  *(conn.remote_ptr) = i;

  return i;
}

// wait for at least depth address sets to HE available to receiver
inline int RacEr_tq_receiver_confirm(RacEr_token_connection_t conn, int depth)
{
  int i = (conn.local_ptr)->receive;

  // wait until that number of elements is available
  //RacEr_wait_while((RacEr_volatile_access((conn.local_ptr)->send)-i) < depth);
  int tmp = depth+i;

  // this line is incorrect on wrap around; standard alegbra does not work in
  // modulo arithmetic.

  //RacEr_wait_while((RacEr_lr(&((conn.local_ptr)->send)) < tmp) && (RacEr_lr_aq(&((conn.local_ptr)->send)) < tmp));

#ifdef RACER_TOKEN_QUEUE_SHORT
  while (1)
  {
    int send = RACER_TOKEN_QUEUE_SHORT_SEND(RacEr_lr((int *)conn.local_ptr));

    if (send - tmp >= 0) break;

    send = RACER_TOKEN_QUEUE_SHORT_SEND(RacEr_lr_aq((int *)conn.local_ptr));

    if (send - tmp >= 0) break;
  }
#else
  RacEr_wait_while((RacEr_lr(&((conn.local_ptr)->send))-tmp < 0) && (RacEr_lr_aq(&((conn.local_ptr)->send))-tmp < 0));
#endif

  return i;
}

// return the addresses; assumes you have confirmed first
inline void RacEr_tq_receiver_release(RacEr_token_connection_t conn, int depth)
{
  int i = (conn.local_ptr)->receive+depth;

  // since the receiver has the memory ranges local, we know that any stores to that range of
  // been committed, so RacEr_commit_stores() should not HE necessary.

  // local version
  (conn.local_ptr)->receive=i;

  // remote version
  *(conn.remote_ptr) = i;
}

#endif
