#pragma once

#include "g_defs.h"
#include "g_error.h"
#include "g_term.h"

namespace gluon {

class Process;

// A single core process scheduler with timers, queues and stuff
class Scheduler {
private:
  Queue<Process *> m_low_q;     // lowest priority (background)
  Queue<Process *> m_normal_q;  // normal priority (8x low)
  Queue<Process *> m_high_q;    // highest (realtime) priority
  word_t           m_pid_counter = 1;
  Process         *m_current     = nullptr;

  Map<Term, Process *>  m_pid_to_proc;

  //
  // Scheduling algorithm
  //
  const word_t NORMAL_ADVANTAGE = 8;  // how often low prio gets to run
  word_t m_normal_count;

public:
  // Register process in one of queues according to its priority
  MaybeError add_runnable(Process *p);
  Process *next();
  MaybeError queue_by_priority(Process *p);
  Process *find(Term pid) const;
};

} // ns gluon
