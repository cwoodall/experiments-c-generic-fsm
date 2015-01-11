#include <stdio.h>
#include "fsm.h"

typedef enum {
  STATE_IDLE = 0,
  STATE_ACTIVE,
  NUM_STATES
} State;

typedef enum {
  EVENT_NONE = 0,
  EVENT_TRANSITION,
  NUM_EVENTS
} Event;

int idle_runner() {
  printf("Idle\n");
  
  return 0;
}

int idle_to_active() {
  printf("Transition To Active\n");
  
  return 0;
}

int active_runner() {
  printf("Active\n");
  
  return 0;
}

int active_to_idle() {
  printf("Transition To Idle\n");
  
  return 0;
}

int validEvent(int i) {
  return (i >= 0) && (i < NUM_EVENTS);
}

int validState(int i) {
  return (i >= 0) && (i < NUM_STATES);  
}

static FSMNode state_table[NUM_STATES][NUM_EVENTS] = 
  {
    [STATE_IDLE] = {
      [EVENT_NONE]       = {.next = STATE_IDLE,   .action = idle_runner},
      [EVENT_TRANSITION] = {.next = STATE_ACTIVE, .action = idle_to_active}
    },
    [STATE_ACTIVE] = {
      [EVENT_NONE]       = {.next = STATE_ACTIVE, .action = active_runner},
      [EVENT_TRANSITION] = {.next = STATE_IDLE,   .action = active_to_idle}
    }
  };

static FSM f = {
  .cur_state = STATE_IDLE,
  .isEventValid = validEvent,
  .isStateValid = validState,
  .n_events = NUM_EVENTS,
  .n_states = NUM_STATES,
  .table = (FSMNode *) state_table
};

int main(void) {
  char c;
  Event e;

  printf("Type any character to run state machine one step (except '\\n')\n");
  printf("Type 't' to trigger a transition event (EVENT_TRANSITION)\n");
  printf("Type 'e' to hand an invalid event to the state machine\n");
  printf("---------------------------------------------------------------\n\n");
  while (1) {
    // Generate Events
    c = getchar();
    if (c == '\n') {
      continue;
    } else if (c == 't') {
      e = EVENT_TRANSITION;
    } else if (c == 'e') {
      e = 213;
    } else {
      e = EVENT_NONE;
    }
    
    int ret = runFSM(&f, e);
    
    if (ret == -1) {
      printf("\nERROR! INVALID EVENT\n");
    } else if (ret == -2) {
      printf("\nERROR! INVALID STATE\n");
    }
  }
  return 0;
}
