#include "fsm.h"

static inline FSMNode *getNode(FSM *f, int state, int event) {
  int index = (state * f->n_events) + event;
  return &(f->table[index]);
}

int runFSM(FSM *fsm, int e) {
  int next_state;
  if (!(fsm->isEventValid(e))) {
    return -1;
  }

  next_state = getNode(fsm, fsm->cur_state, e)->next;
  if (!(fsm->isStateValid(next_state))) {
    return -2;
  }

  getNode(fsm, fsm->cur_state, e)->action();
  
  fsm->cur_state = next_state;

  return 0;
}
