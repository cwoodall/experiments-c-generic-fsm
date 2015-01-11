#ifndef FSM_H
#define FSM_H

typedef int (*StateFunction)(void);
typedef int (*ValidatorFunction)(int);

typedef struct FSMNode FSMNode;
struct FSMNode {
  int next;
  StateFunction action;
};

typedef struct FSM FSM;
struct FSM {
  int cur_state;
  ValidatorFunction isEventValid;
  ValidatorFunction isStateValid;  
  int n_events;
  int n_states;
  FSMNode *table;
};

int runFSM(FSM *f, int e);

#endif // FSM_H
