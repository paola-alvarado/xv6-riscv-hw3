struct pstat {
  int pid;     // Process ID
  enum procstate state;  // Process state
  uint64 size;     // Size of process memory (bytes)
  int ppid;        // Parent process ID
  int  priority;    // HW3: base priority 0..49
  uint readytime;   // HW3: ticks when became RUNNABLE
  char name[16];   // Parent command name
};